import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent.parent))

import model

def kebob_to_snake(name: str) -> str:
    return name.replace('-', '_')

class KokaFile:
    namespace: str
    module: str
    cls: model.GClass
    imports = []
    chunks = []

    def __init__(self, namespace, module, cls):
        self.namespace = namespace
        self.module = module
        self.cls = cls

    def __str__(self):
        return f'module {self.module}\n{'\n'.join(map(lambda x: f'import {x}', self.imports))}\n{'\n'.join(self.chunks)}'


def generate_signal(signal: model.GSignal, output: KokaFile) -> str:
    params = []
    for param in signal.parameters:
        params.append(f'{model.pascal_to_koka(param.name)}: {param.the_type.get_koka_type()}')
    
    match signal.return_type.get_koka_type():
        case '()':
            call_back = f'({', '.join(params)}) -> io ()'
        case 'bool':
            call_back = f'({', '.join(params)}) -> io bool'

    output = f'pub extern {output.module}/connect-{signal.name}(self: {output.cls.name}, cb: {call_back}) : ()\n'
    output += f'  c inline "kk_signal_connect_{kebob_to_snake(signal.name)}(#1, #2, kk_context())"'

    return output

def generate_function(fun: model.GFunction, output: KokaFile) -> str:
    output = f'pub extern {output.module}/{model.pascal_to_koka(fun.name)}('

    params = []
    args = []
    index = 1
    for param in fun.parameters:
        params.append(f'{model.pascal_to_koka(param.name)}: {param.the_type.get_koka_type()}')
        args.append(f'#{index}')
        index += 1

    args.append('kk_context()')

    output += ', '.join(params)

    if fun.return_type_nullable:
        return_type = f'maybe<{fun.return_type.get_koka_type()}>'
    else:
        return_type = fun.return_type.get_koka_type()
    output += f') : {return_type}\n'

    output += f'  c inline "kk_{fun.c_name}({', '.join(args)})"'

    return output

def generate_class(namespace: str, cls: model.GClass) -> KokaFile:
    output = KokaFile(namespace, model.pascal_to_koka(cls.name), cls)

    output.chunks.append(f'// Type\n\npub abstract type {cls.the_type.get_koka_type()}\n\n')
    output.chunks.append(f'// Constructors\n\n{'\n\n'.join(map(lambda c: generate_function(c, output), cls.constructors))}\n\n')
    output.chunks.append(f'// Methods\n\n{'\n\n'.join(map(lambda m: generate_function(m, output), cls.methods))}')
    output.chunks.append(f'// Functions\n\n{'\n\n'.join(map(lambda f: generate_function(f, output), cls.functions))}')
    output.chunks.append(f'// Signals\n\n{'\n\n'.join(map(lambda s: generate_signal(s, output), cls.signals))}')

    return output

def generate_classes(namespace, classes):
    for cls in classes.values():
        print(generate_class(namespace, cls))
    pass

def generate_koka(file: model.GFile, path):
    generate_classes(file.namespace, file.classes)
    pass