#!/usr/bin/env sh

# reference some boilerplate stuff - constants and more.
SCRIPT=$(readlink -f "$0")
CURRENT_DIR=$(dirname "$SCRIPT")
source $CURRENT_DIR/script_standards.sh

$CURRENT_DIR/compile_source.sh

#linking the objects for non-test use
cc \
  $WEBSERVER_DEVEL_BUILD/server_library.o 
  $WEBSERVER_DEVEL_BUILD/server.o \
  -o $WEBSERVER_DEVEL_BUILD/server
echo objects linked

source $CURRENT_DIR/closedown.sh
