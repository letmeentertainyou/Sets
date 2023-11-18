# This takes a language name as an arg, and then uses the appropriate build
# tool to compile it into the dist folder. The dist folder exists so that my
# binaries don't get shipped to github.

if [ $1 == "c" ]; then
    gcc c/main.c -o dist/main
fi

#if [ $1 == "r" ]; then
#    cargo build rust/main.rs -o dist/main
#fi

#if [ $1 == "g" ]; then
#    go build go/main.go -o dist/main
#fi