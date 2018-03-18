#!/usr/local/bin/bash

#following will cause the script to halt if any program returns
#a non-zero (error) exit.
set -e

#include things like BUILD_DIRECTORY
source constants.sh

if [ ! -d "$BUILD_DIRECTORY" ]; then
  mkdir $BUILD_DIRECTORY
fi
echo building objects, linking, and running tests..
clang -c server_library_test.c -o $BUILD_DIRECTORY/server_library_test.o
clang -c server_library.c -o $BUILD_DIRECTORY/server_library.o
echo objects built
clang \
  $BUILD_DIRECTORY/server_library.o \
  $BUILD_DIRECTORY/server_library_test.o \
  -o $BUILD_DIRECTORY/tests 
echo objects linked
$BUILD_DIRECTORY/tests
echo tests run
