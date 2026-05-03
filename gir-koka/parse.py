from lxml import etree
import model

NS = {
    'core': 'http://www.gtk.org/introspection/core/1.0',
    'c':    'http://www.gtk.org/introspection/c/1.0',
    'glib': 'http://www.gtk.org/introspection/glib/1.0',
}








def parse_parameter(param):
    name = param.get('name')
    the_type = model.GType(param.get('type'), NS)
    direction = x if (x := param.get('direction')) is not None else 'in'
    transfer_ownership = param.get('transfer-ownership')
    nullable = (True if y == "1" else False) if (y := param.get('nullable')) is not None or (y := param.get('allow-none')) else False

    return model.GFunctionParam(name, the_type, transfer_ownership, direction, nullable)

def parse_parameters(params, method=False):
    parameters = []
    if params is None:
        return parameters
    if method:
        instance_param = parse_parameter(params.get('instance-parameter'))
        parameters.append(instance_param)
    
    for param in params.findall('core:parameter'):
        parameters.append(parse_parameter(param))

    return parameters


def parse_function(fun, method=False, virtual=False):
    name = fun.get('name')
    c_name = fun.get('c:identifier')
    return_value = fun.get('return-value')
    transfer_ownership = return_value.get('transfer-ownership')
    nullable = True if return_value.get('nullable') == "1" else False
    return_type = model.GType(return_value.get('type'), NS)
    if virtual:
        invoker = fun.get('invoker')
    else:
        invoker = ''

    parameters = parse_parameters(fun.get('parameters'),method=method)
    function = model.GFunction(name, c_name, parameters, return_type, transfer_ownership, nullable, invoker)
    return function

def parse_property(prop):
    name = prop.get('name')
    the_type = model.GType(prop.get('type'), NS)
    writeable = (True if x == '1' else False) if (x := prop.get('writeable')) is not None else False
    transfer_ownership = prop.get('transfer-ownership')
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
    return_type = model.GType(return_value.get('type'), NS)
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
    the_type = model.GType(field.get('type'), NS)
    writable = (True if x == '1' else False) if (x := field.get('writable')) is not None else False

    field = model.GField(name, the_type)
    if writable:
        field.make_writable()

    return field

def parse_class(cls):
    name = cls.get('name')
    parent = cls.get('parent')
    g_type = cls.get('{%s}type-name' % NS['glib'])
    the_type = model.GType(g_type, NS)

    out = model.GClass(name, parent, the_type)

    constructors = []
    for constructor in cls.findall('core:constructor', NS):
        constructors.append(parse_function(constructor))
    out.constructors = constructors
    
    methods = []
    for method in cls.findall('core:method', NS):
        methods.append(parse_function(method, method=True))
    for method in cls.findall('core:virtual-method', NS):
        methods.append(parse_function(method, method=True, virtual=True))
    out.methods = methods
    
    functions = []
    for function in cls.findall('core:function', NS):
        functions.append(parse_function(function))
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
        field = parse_field()
        if field is not None:
            fields.append(field)
    out.fields = fields

    implements = set()
    for implement in cls.findall('core:implements'):
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