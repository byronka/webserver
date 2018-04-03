#!/usr/bin/env bash

#####################
# Boilerplate BEGIN #
#####################
# Some stuff that's included in all scripts.

SCRIPT=$(readlink -f "$0")
CURRENT_DIR=$(dirname "$SCRIPT")
source $CURRENT_DIR/script_standards.sh

###################
# Boilerplate END #
###################






##############################
# Function definitions BEGIN #
##############################

# if the test executable directory doesn't exist, create it.
create_test_build_directory_if_necessary() {
  if [ ! -d "$WEBSERVER_DEVEL_TESTS" ]; then
    echo "test build directory didn't exist.  creating it..."
    mkdir $WEBSERVER_DEVEL_TESTS
    echo "test build directory created"
  fi
}

link_business_tests() {
  echo linking files for testing business...
  $WEBSERVER_C_COMPILER \
    $WEBSERVER_DEVEL_OBJECTS/business_library.o \
    $WEBSERVER_DEVEL_OBJECTS/business_library_test.o \
    -o $WEBSERVER_DEVEL_TESTS/business_tests 
  echo business tests linked.
}

link_mocked_server_tests() {
  echo linking files for mocked server testing...
  $WEBSERVER_C_COMPILER \
    $WEBSERVER_DEVEL_OBJECTS/server_library.o \
    $WEBSERVER_DEVEL_OBJECTS/server_library_test.o \
    -o $WEBSERVER_DEVEL_TESTS/server_tests 
  echo server tests linked.
}

link_integration_test() {
  echo linking files for integrated server testing...
  $WEBSERVER_C_COMPILER \
    $WEBSERVER_DEVEL_OBJECTS/server_library.o \
    $WEBSERVER_DEVEL_OBJECTS/server_library_test_integration.o \
    -o $WEBSERVER_DEVEL_TESTS/server_tests_integrated
  echo server tests linked.
}

run_tests() {
  echo running tests...
  for mytest in \
    server_tests \
    server_tests_integrated \
    business_tests \
    ; do \
    echo 
    echo running $WEBSERVER_DEVEL_TESTS/$mytest
    echo
    $WEBSERVER_DEVEL_TESTS/$mytest
  done

  echo work finished.
}

##############################
# Function definitions END   #
##############################





##############################
# Command Execution BEGIN    #
##############################

set -e
#wipe out the current code. 
$CURRENT_DIR/delete_build.sh

$CURRENT_DIR/compile_source.sh DEBUG
create_test_build_directory_if_necessary
echo starting to link files for testing...
echo
link_business_tests
link_mocked_server_tests
link_integration_test
run_tests
set +e

##############################
# Command Execution END      #
##############################

