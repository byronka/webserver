#!/usr/bin/env sh

# reference some boilerplate stuff - constants and more.
SCRIPT=$(readlink -f "$0")
CURRENT_DIR=$(dirname "$SCRIPT")
source $CURRENT_DIR/script_standards.sh

$CURRENT_DIR/compile_source.sh

#link all the files we need for the tests we want to run.
cc \
  $WEBSERVER_DEVEL_BUILD/server_library.o \
  $WEBSERVER_DEVEL_BUILD/server_library_test.o \
  -o $WEBSERVER_DEVEL_BUILD/tests 
echo objects linked
$WEBSERVER_DEVEL_BUILD/tests
echo tests run

source $CURRENT_DIR/closedown.sh
