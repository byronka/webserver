#!/usr/local/bin/bash

if [ ! -d "build" ]; then
  mkdir build
fi
echo building objects, linking, and running tests..
clang -c server_library_test.c -o build/server_library_test.o
clang -c server_library.c -o build/server_library.o
echo objects built
clang \
  build/server_library.o \
  build/server_library_test.o \
  -o build/tests 
echo objects linked
build/tests
echo tests run
