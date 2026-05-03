from lxml import etree
import model

NS = {
    'core': 'http://www.gtk.org/introspection/core/1.0',
    'c':    'http://www.gtk.org/introspection/c/1.0',
    'glib': 'http://www.gtk.org/introspection/glib/1.0',
}








def parse_parameter(param):
    name = param.get('name')
    the_type = model.GType.new(param, NS)
    direction = x if (x := param.get('direction')) is not None else 'in'
    transfer_ownership = x if (x := param.get('transfer-ownership')) is not None else 'none'
    nullable = (True if y == "1" else False) if (y := param.get('nullable')) is not None or (y := param.get('allow-none')) else False

    return model.GFunctionParam(name, the_type, transfer_ownership, direction, nullable)

def parse_parameters(params, method=False):
    parameters = []
    if params is None:
        return parameters
    if method:
        instance_param = parse_parameter(params.find('core:instance-parameter', NS))
        parameters.append(instance_param)
    
    for param in params.findall('core:parameter', NS):
        parameters.append(parse_parameter(param))

    return parameters


def parse_function(fun, method=False, virtual=False):
    name = fun.get('name')
    c_name = fun.get('{%s}identifier' % NS['c'])
    return_value = fun.find('core:return-value', NS)
    transfer_ownership = x if (x := return_value.get('transfer-ownership')) is not None else 'none'
    nullable = True if return_value.get('nullable') == "1" else False
    return_type = model.GType.new(return_value, NS)
    if virtual:
        invoker = fun.get('invoker')
    else:
        invoker = ''

    parameters = parse_parameters(fun.find('core:parameters', NS),method=method)
    function = model.GFunction(name, c_name, parameters, return_type, transfer_ownership, nullable, invoker)
    return function

def parse_property(prop):
    name = prop.get('name')
    the_type = model.GType.new(prop, NS)
    writeable = (True if x == '1' else False) if (x := prop.get('writeable')) is not None else False
    transfer_ownership = x if (x := prop.get('transfer-ownership')) is not None else 'none'
    construct_only = (True if x == '1' else False) if (x := prop.get('construct-only')) is not None else False

    out = model.GProperty(name, the_type, transfer_ownership)
    if not writeable:
        out.make_read_only()
    if construct_only:
        out.make_construct_only()
    
    return prop

def parse_signal(sig):
    name = sig.get('name')
    return_value = sig.get('return-value')
    return_type = model.GType.new(return_value, NS)
    detailed = (True if x == '1' else False) if (x := sig.get('detailed')) is not None else False

    parameters = parse_parameters(sig.get('parameters'))

    signal = model.GSignal(name, return_type, parameters)
    if detailed:
        signal.make_detailed()

    return signal

def parse_field(field):
    private = (True if x == '1' else False) if (x := field.get('private')) is not None else False
    unreadable = (True if x == '0' else False) if (x := field.get('readable')) is not None else False
    if private or unreadable:
        return None
    
    name = field.get('name')
    the_type = model.GType.new(field, NS)
    writable = (True if x == '1' else False) if (x := field.get('writable')) is not None else False

    field = model.GField(name, the_type)
    if writable:
        field.make_writable()

    return field

def parse_class(cls):
    name = cls.get('name')
    parent = cls.get('parent')
    g_type = cls.get('{%s}type-name' % NS['glib'])
    c_type = cls.get('{%s}type' % NS['c'])

    the_type = model.GNormalType()
    the_type.abstract = True
    the_type.c_type = c_type
    the_type.g_type = g_type
    the_type.koka_type = model.pascal_to_koka(g_type)

    out = model.GClass(name, parent, the_type)

    constructors = []
    for constructor in cls.findall('core:constructor', NS):
        try:
            constructors.append(parse_function(constructor))
        except model.NotRepresentable:
            pass
    out.constructors = constructors
    
    methods = []
    for method in cls.findall('core:method', NS):
        try:
            methods.append(parse_function(method, method=True))
        except model.NotRepresentable:
            pass
    for method in cls.findall('core:virtual-method', NS):
        try:
            methods.append(parse_function(method, method=True, virtual=True))
        except model.NotRepresentable:
            pass
    out.methods = methods
    
    functions = []
    for function in cls.findall('core:function', NS):
        try:
            functions.append(parse_function(function))
        except model.NotRepresentable:
            pass
    out.functions = functions

    properties = []
    for property in cls.findall('core:property', NS):
        properties.append(parse_property(property))
    out.properties = properties

    signals = []
    for signal in cls.findall('core:signal', NS):
        signals.append(parse_signal(signal))
    out.signals = signals

    fields = []
    for field in cls.findall('core:field', NS):
        field = parse_field(field)
        if field is not None:
            fields.append(field)
    out.fields = fields

    implements = set()
    for implement in cls.findall('core:implements', NS):
        implements.add(implement.get('name'))
    out.implements = implements

    return out



def parse_classes(namespace):
    out = {}
    for cls in namespace.findall('core:class', NS):
        cls = parse_class(cls)
        out[cls.name] = cls
    return out


def parse_file(path: str):
    tree = etree.parse(path)
    root = tree.getroot()
    ns = root.find('core:namespace', NS)

    file = model.GFile(ns.get('name'))

    classes = parse_classes(ns)
    file.set_classes(classes)

    return file

import sys
if __name__ == '__main__':
    parse_file(sys.argv[1])