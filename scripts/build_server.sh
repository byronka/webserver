#!/usr/bin/env sh

# reference some boilerplate stuff - constants and more.
SCRIPT=$(readlink -f "$0")
CURRENT_DIR=$(dirname "$SCRIPT")
source $CURRENT_DIR/script_standards.sh

#compile source files to object files if they need compiling.
$CURRENT_DIR/compile_source.sh

#linking the objects for non-test use
cc \
  $WEBSERVER_DEVEL_BUILD/server_library.o \
  $WEBSERVER_DEVEL_BUILD/business_library.o \
  $WEBSERVER_DEVEL_BUILD/server.o \
  -o $WEBSERVER_DEVEL_BUILD/server
echo work finished.

source $CURRENT_DIR/closedown.sh
