#!/usr/bin/env sh

# reference some boilerplate stuff - constants and more.
SCRIPT=$(readlink -f "$0")
CURRENT_DIR=$(dirname "$SCRIPT")
source $CURRENT_DIR/script_standards.sh

$CURRENT_DIR/compile_source_for_test.sh

echo starting to link files for testing...

echo linking files for testing business...
cc \
  $WEBSERVER_DEVEL_BUILD/business_library.o \
  $WEBSERVER_DEVEL_BUILD/business_library_test.o \
  -o $WEBSERVER_DEVEL_BUILD/business_tests 
echo business tests linked.

echo linking files for mocked server testing...
cc \
  $WEBSERVER_DEVEL_BUILD/server_library.o \
  $WEBSERVER_DEVEL_BUILD/server_library_test.o \
  -o $WEBSERVER_DEVEL_BUILD/server_tests 
echo server tests linked.

echo linking files for integrated server testing...
cc \
  $WEBSERVER_DEVEL_BUILD/server_library.o \
  $WEBSERVER_DEVEL_BUILD/server_library_test_integration.o \
  -o $WEBSERVER_DEVEL_BUILD/server_tests_integrated
echo server tests linked.

echo running tests...
$WEBSERVER_DEVEL_BUILD/server_tests
$WEBSERVER_DEVEL_BUILD/server_tests_integrated
$WEBSERVER_DEVEL_BUILD/business_tests
echo work finished.

source $CURRENT_DIR/closedown.sh
