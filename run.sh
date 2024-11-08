if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    if [ $# -lt 1 ]; then
        echo "Usage: ./run.sh <input_file_1>.asc <input_file_2>.asc ..."
        exit 1
    fi
 
    gcc spimcore.c project.c -o spimcore || { exit 1; }
    
    for file in "$@"; do
        if [[ "$file" == *.asc ]]; then
            ./spimcore "$file" || { exit 1; }
        else
            echo "The input file '$file' must have a .asc file extension"
        fi 
    done
elif [[ "$OSTYPE" == "msys" || "$OSTYPE" == "cygwin" || "$OSTYPE" == "win32" ]]; then     
    if [ $# -lt 1 ]; then
        echo "Usage: run.sh <input_file_1>.asc <input_file_2>.asc ..."
        exit 1
    fi

    gcc spimcore.c project.c -o spimcore || { exit 1; }
    
    for file in "$@"; do
        if [[ "$file" == *.asc ]]; then
            spimcore.exe "$file" || { exit 1; }
        else
            echo "The input file '$file' must have a .asc file extension"
        fi 
    done
elif [[ "$OSTYPE" == "darwin" ]]; then
    if ! xcode-select -p > /dev/null 2>&1; then
        xcode-select --install
        echo "Please follow the installation instructions to use gcc command on macOS."
        echo "Rerun this script once it has finished installing."
        exit 1
    fi

    if [ $# -lt 1 ]; then
        echo "Usage: run.sh <input_file_1>.asc <input_file_2>.asc ..."
        exit 1
    fi

    gcc spimcore.c project.c -o spimcore || { exit 1; }
    
    for file in "$@"; do
        if [[ "$file" == *.asc ]]; then
            ./spimcore "$file" || { exit 1; }
        else
            echo "The input file '$file' must have a .asc file extension"
            exit 1
        fi 
    done
fi