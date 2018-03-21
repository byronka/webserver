#!/usr/bin/env sh

CC=$WEBSERVER_C_COMPILER 

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
  echo "build directory didn't exist.  creating it..."
  mkdir $WEBSERVER_DEVEL_BUILD
  echo "build directory created"
fi

# a handy-dandy function that builds objects if, and *only* if
# the objct file either doesn't exist or if the source file is
# newer than the object file.
# parameters: takes the name of a source file
# results: builds an object file if needed, otherwise does nothing.
build() {
  # if the built file doesn't exist, built it and return
  if [ ! -f "$BLD/$1.o" ]; then
    echo "building $1.c because it didn't exist"
    set -x
    $CC --std=gnu99 -c $SRC/$1.c -o $BLD/$1.o
    set +x
    COUNT_OF_OBJECTS_BUILT=$((COUNT_OF_OBJECTS_BUILT + 1))
    return
  fi

  if [ "$SRC/$1.c" -nt "$BLD/$1.o" ]; then
    echo "building $1.c because the source file is newer that the object file"
    set -x
    $CC --std=gnu99 -c $SRC/$1.c -o $BLD/$1.o
    set +x
    COUNT_OF_OBJECTS_BUILT=$((COUNT_OF_OBJECTS_BUILT + 1))
    return
  fi
}

#refer to the build function above to see what is happening here...
echo building objects...
build "server_library_test"
build "server_library"
build "business_library"
build "business_library_test"
build "server"

echo $COUNT_OF_OBJECTS_BUILT objects built

