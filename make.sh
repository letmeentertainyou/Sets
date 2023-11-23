# This takes a language name as an arg, and then uses the appropriate build
# tool to compile it into the dist folder. The dist folder exists so that my
# binaries don't get shipped to github.

compile() {
    # Make the dist dir.
    mkdir -p dist
    
    # Compile the code.
    $1 -o dist/main $2

    # Check if the compilation was successful.
    if [ $? == 0 ]; then
        echo Compiled $2 into dist/main with no issues.
    fi
}

if [ $1 == "-c" ]; then
    compile gcc c/main.c

elif [ $1 == "-r" ]; then
    compile rustc rust/set.rs

elif [ $1 == "-g" ]; then
    compile "go build" go/set.go

else
    echo "Argument not recognized try -c, -r or -g."
fi
