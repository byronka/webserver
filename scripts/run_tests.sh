#!/usr/bin/env sh

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

link_business_tests() {
  echo linking files for testing business...
  cc \
    $WEBSERVER_DEVEL_BUILD/business_library.o \
    $WEBSERVER_DEVEL_BUILD/business_library_test.o \
    -o $WEBSERVER_DEVEL_BUILD/business_tests 
  echo business tests linked.
}

link_mocked_server_tests() {
  echo linking files for mocked server testing...
  cc \
    $WEBSERVER_DEVEL_BUILD/server_library.o \
    $WEBSERVER_DEVEL_BUILD/server_library_test.o \
    -o $WEBSERVER_DEVEL_BUILD/server_tests 
  echo server tests linked.
}

link_integration_test() {
  echo linking files for integrated server testing...
  cc \
    $WEBSERVER_DEVEL_BUILD/server_library.o \
    $WEBSERVER_DEVEL_BUILD/server_library_test_integration.o \
    -o $WEBSERVER_DEVEL_BUILD/server_tests_integrated
  echo server tests linked.
}

run_tests() {
  echo running tests...
  $WEBSERVER_DEVEL_BUILD/server_tests
  $WEBSERVER_DEVEL_BUILD/server_tests_integrated
  $WEBSERVER_DEVEL_BUILD/business_tests
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
echo starting to link files for testing...
link_business_tests
link_mocked_server_tests
link_integration_test
run_tests
set +e

##############################
# Command Execution BEGIN    #
##############################

