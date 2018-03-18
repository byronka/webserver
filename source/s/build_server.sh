#!/usr/local/bin/bash

#following will cause the script to halt if any program returns
#a non-zero (error) exit.
set -e

if [ ! -d "build" ]; then
  mkdir build
fi
echo building objects, linking, and running server..
clang -c server_library.c -o build/server_library.o
clang -c server.c -o build/server.o
echo objects built
clang \
  build/server_library.o \
  build/server.o \
  -o build/server
echo objects linked

