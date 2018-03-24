#!/usr/bin/env bash

#####################
# Boilerplate BEGIN #
#####################
# Some stuff that's included in all scripts.

SCRIPT=$(readlink -f "$0")
CURRENT_DIR=$(dirname "$SCRIPT")
source $CURRENT_DIR/script_standards.sh
#there are two types of LOG_MODE: ERROR and DEBUG.
#ERROR only shows errors occuring.
#DEBUG shows many more messages about what's going on.
LOG_MODE=ERROR

###################
# Boilerplate END #
###################





##############################
# Command Execution BEGIN    #
##############################

set -e

#wipe out the current code. 
$CURRENT_DIR/delete_build.sh

# compile source files to object files if they need compiling.
$CURRENT_DIR/compile_source.sh STANDARD

# if the build directory doesn't exist, create it.
if [ ! -d "$WEBSERVER_DEVEL_EXEC" ]; then
  if [ $LOG_MODE == "DEBUG" ]; then
    echo "executables directory didn't exist.  creating it..."
  fi
  mkdir -p $WEBSERVER_DEVEL_EXEC

  if [ $LOG_MODE == "DEBUG" ]; then
    echo "executable directory created"
  fi
fi

# note that if we build statically, we will need the static c libraries.
# you might not have them. you might need to run "sudo yum install glibc-static"

# linking the objects for non-test use
$WEBSERVER_C_COMPILER -static $WEBSERVER_DEVEL_OBJECTS/business_library.o $WEBSERVER_DEVEL_OBJECTS/pant_size.o -o $WEBSERVER_DEVEL_EXEC/pant_size

set +e
