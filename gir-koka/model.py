def convert_to_koka(name):
    out = ''
    for c in name:
        if c == '.':
            out = '-'
        else:
            out += c.lower()
    return out

def pascal_to_koka(name, capitals=set(list("ABCDEFGHIJKLMNOPQRSTUVWXYZ"))):
    first_char = True
    output = ''
    for c in name:
        if first_char and c in capitals:
            output += c.lower()
        elif c in capitals:
            output += '-' + c.lower()
        else:
            output += c
        first_char = False
    return output


class NotRepresentable(Exception):
    def __init__(self, *args):
        super().__init__(*args)

class GType:
    
    @staticmethod
    def new(parent, NS):
        node = parent.find('core:type', NS)
        if node is None:
            node = parent.find('core:array', NS)
            if node is not None:
                param = GNormalType(node.find('core:type', NS), NS)
                return GArrayType(param)
            raise NotRepresentable
        else:
            return GNormalType(node, NS)

class GNormalType(GType):
    c_type: str
    g_type: str
    koka_type: str
    abstract = False
    
    def __init__(self, ty=None, NS=None):
        super().__init__()
        if ty is None and NS is None:
            return
        self.abstract = False
        self.c_type = ty.get('{%s}type' % NS['c'])
        self.g_type = ty.get('name')
        match self.g_type:
            case 'none':
                self.koka_type = '()'
            case 'utf':
                self.koka_type = 'string'
            case 'gboolean':
                self.koka_type = 'bool'
            case 'gint':
                self.koka_type = 'int32'
            case 'gint32':
                self.koka_type = 'int32'
            case 'guint':
                self.koka_type = 'int32'
            case 'guint32':
                self.koka_type = 'int32'
            case 'gint64':
                self.koka_type = 'int64'
            case 'gfloat':
                self.koka_type = 'float32'
            case 'gdouble':
                self.koka_type = 'float64'
            case the_ty:
                self.abstract = True
                self.koka_type = pascal_to_koka(the_ty)

    def get_koka_type(self):
        return self.koka_type

    def get_c_type(self):
        return self.c_type
    
    def get_g_type(self):
        return self.g_type
    
    def is_abstract(self):
        return self.abstract

class GArrayType(GType):
    param_type: GType
    
    def __init__(self, param_type):
        super().__init__()
        self.param_type = param_type

    def get_koka_type(self):
        return f'vector<{self.param_type.get_koka_type()}>'


class GFunctionParam:
    the_type: GType
    name: str
    direction: str = 'in'
    transfer_ownership: bool = False
    nullable: bool = False

    def __init__(self, name, the_type, transfer_ownership, direction, nullable):
        self.name = name
        self.the_type = the_type
        self.transfer_ownership = transfer_ownership
        self.direction = direction
        self.nullable = nullable

class GFunction:
    name: str
    c_name: str
    return_type: GType
    return_type_nullable = False
    return_type_transfers_ownership = "none"
    parameters = []
    invoker: str

    def __init__(self, name, c_name, parameters, return_type, transfer_ownership, return_nullable=False, invoker=''):
        self.name = name
        self.c_name = c_name
        self.parameters = parameters
        self.return_type = return_type
        self.return_type_transfers_ownership = transfer_ownership
        self.return_type_nullable = return_nullable
        self.invoker = invoker


class GProperty:
    name: str
    the_type: GType
    writable: bool = True
    construct_only: bool = False
    transfer_ownership = "none"

    def __init__(self, name, the_type, transfer_ownership):
        self.name = name
        self.the_type = the_type
        self.transfer_ownership = transfer_ownership

    def make_read_only(self):
        self.writable = False

    def make_construct_only(self):
        self.construct_only = True

class GSignal:
    name: str
    return_type: GType
    return_type_nullable = False
    parameters = []
    detailed: bool = False

    def __init__(self, name, return_type, parameters):
        self.name = name
        self.return_type = return_type
        self.parameters = parameters
    
    def make_detailed(self):
        self.detailed = True

class GField:
    name: str
    the_type: GType
    writable: bool = False

    def __init__(self, name, the_type):
        self.name = name
        self.the_type = the_type

    def make_writable(self):
        self.writable = True

class GImplements:
    name: str
    get_type: str

    def __init__(self, name, get_type):
        self.name = name
        self.get_type = get_type

class GClass:
    name: str
    parent: str
    the_type: GType
    constructors = []
    methods = []
    functions = []
    properties = []
    signals = []
    fields = []
    implements = {}

    def __init__(self, name, parent, the_type):
        self.name = name
        self.parent = parent
        self.the_type = the_type


class GFile:
    namespace: str
    
    def __init__(self, namespace: str):
        self.namespace = namespace

    def set_classes(self, classes):
        self.classes = classes