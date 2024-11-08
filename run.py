import sys
import platform
import subprocess

def check_mac_xcode():
    try:
        subprocess.run(['xcode-select', '-p'], check=True, capture_output=True)
        return True
    except subprocess.CalledProcessError:
        print("Please follow the installation instructions to use gcc command on macOS.")
        print("Rerun this script once it has finished installing.")
        try:
            subprocess.run(['xcode-select', '--install'], check=True)
        except subprocess.CalledProcessError:
            print("Failed to install Xcode command line tools")
        return False

def compile_program():
    try:
        subprocess.run(['gcc', 'spimcore.c', 'project.c', '-o', 'spimcore'], check=True)
        return True
    except subprocess.CalledProcessError:
        return False

def run_project(input_file):
    try:
        if platform.system() == 'Windows':
            subprocess.run(['spimcore.exe', input_file], check=True)
        else:
            subprocess.run(['./spimcore', input_file], check=True)
        return True
    except subprocess.CalledProcessError:
        return False

def main():
    if len(sys.argv) < 2:
        print("Usage: python run.py <input_file_1>.asc <input_file_2>.asc ...")
        sys.exit(1)

    if platform.system() == 'Darwin':  # macOS
        if not check_mac_xcode():
            sys.exit(1)

    if not compile_program():
        sys.exit(1)

    for input_file in sys.argv[1:]:
        if not input_file.endswith('.asc'):
            print(f"The input file '{input_file}' must have a .asc file extension")
            sys.exit(1)
        
        if not run_project(input_file):
            sys.exit(1)

if __name__ == "__main__":
    main()
