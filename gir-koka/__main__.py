import sys
from codegen import koka
import parse

def main():
    path = sys.argv[1]
    print(path)
    file = parse.parse_file(path)
    koka.generate_koka(file, '')


if __name__ == '__main__':
    main()