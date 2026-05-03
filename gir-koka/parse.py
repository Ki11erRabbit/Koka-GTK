from lxml import etree
import model

NS = {
    'core': 'http://www.gtk.org/introspection/core/1.0',
    'c':    'http://www.gtk.org/introspection/c/1.0',
    'glib': 'http://www.gtk.org/introspection/glib/1.0',
}








def parse_parameter(param):
    name = param.get('name')
    the_type = model.GType(param.get('type').get('name'), NS)
    direction = x if (x := param.get('direction')) is not None else 'in'
    transfer_ownership = param.get('transfer-ownership')
    nullable = (True if y == "1" else False) if (y := param.get('nullable')) is not None or (y := param.get('allow-none')) else False

    return model.GFunctionParam(name, the_type, transfer_ownership, direction, nullable)

def parse_parameters(params, method=False):
    parameters = []
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
    return_type = model.GType(return_value.get('name'), NS)
    if virtual:
        invoker = fun.get('invoker')
    else:
        invoker = ''

    parameters = parse_parameters(fun.get('parameters'),method=method)
    function = model.GFunction(name, c_name, parameters, return_type, transfer_ownership, nullable, invoker)
    return function


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
        pass
    out.properties = properties

    signals = []
    for signal in cls.findall('core:signal', NS):
        pass
    out.signals = signals

    fields = []
    for field in cls.findall('core:field', NS):
        pass
    out.fields = fields

    implements = set()
    for implement in cls.findall('core:implements'):
        implements.add(implement)
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