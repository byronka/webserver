#!/usr/bin/env sh


# reference some boilerplate stuff - constants and more.
SCRIPT=$(readlink -f "$0")
CURRENT_DIR=$(dirname "$SCRIPT")
source $CURRENT_DIR/script_standards.sh


#setting variable to count number of objects built
COUNT_OF_OBJECTS_BUILT=0

#setting some aliases to have shorter command strings.
SRC=$WEBSERVER_DEVEL_SOURCE
BLD=$WEBSERVER_DEVEL_BUILD

# if the build directory doesn't exist, create it.
if [ ! -d "$WEBSERVER_DEVEL_BUILD" ]; then
  mkdir $WEBSERVER_DEVEL_BUILD
fi

echo building objects, linking, and running tests..

# a handy-dandy function that builds objects if, and *only* if
# the objct file either doesn't exist or if the source file is
# newer than the object file.
build() {
  # if the built file doesn't exist, built it and return
  if [ ! -f "$BLD/$1.o" ]; then
    echo "building $1.c because it didn't exist"
    cc -c $SRC/$1.c -o $BLD/$1.o
    COUNT_OF_OBJECTS_BUILT=$((COUNT_OF_OBJECTS_BUILT + 1))
    return
  fi

  if [ "$SRC/$1.c" -nt "$BLD/$1.o" ]; then
    echo "building $1.c because the source file is newer that the object file"
    cc -c $SRC/$1.c -o $BLD/$1.o
    COUNT_OF_OBJECTS_BUILT=$((COUNT_OF_OBJECTS_BUILT + 1))
    return
  fi
}

build "server_library_test"
build "server_library"
build "server"

echo $COUNT_OF_OBJECTS_BUILT objects built

