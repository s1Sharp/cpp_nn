import os
import sys

def main():
    torch_lib_dir = sys.argv[1]
    for file in os.listdir(torch_lib_dir):
        if not file.endswith(".so") or not file.endswith(".a"):
            src = os.path.join(torch_lib_dir, file)
            if '.so' in file:
                filename, *_ = file.split('.')
                dst = os.path.join(torch_lib_dir, filename + '.so')
            if '.a' in file:
                filename, *_ = file.split('.')
                dst = os.path.join(torch_lib_dir, filename + '.a')
            if not os.path.exists(dst):
                os.symlink(src, dst)

if __name__=='__main__':
    main()
