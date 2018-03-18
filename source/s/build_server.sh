#!/usr/local/bin/bash

#following will cause the script to halt if any program returns
#a non-zero (error) exit.
set -e

#show commands as they run
set -x

#things like build directory, etc.
source s/constants.sh

if [ ! -d "$BUILD_DIRECTORY" ]; then
  mkdir $BUILD_DIRECTORY
fi
echo building objects, linking, and running server..
clang -c server_library.c -o $BUILD_DIRECTORY/server_library.o
clang -c server.c -o $BUILD_DIRECTORY/server.o
echo objects built
clang \
  $BUILD_DIRECTORY/server_library.o \
  $BUILD_DIRECTORY/server.o \
  -o $BUILD_DIRECTORY/server
echo objects linked

