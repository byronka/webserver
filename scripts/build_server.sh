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
# Command Execution BEGIN    #
##############################

set -e

#wipe out the current code. 
$CURRENT_DIR/delete_build.sh

# compile source files to object files if they need compiling.
$CURRENT_DIR/compile_source.sh STANDARD

# if the build directory doesn't exist, create it.
if [ ! -d "$WEBSERVER_DEVEL_EXEC" ]; then
  echo "executables directory didn't exist.  creating it..."
  mkdir -p $WEBSERVER_DEVEL_EXEC
  echo "executable directory created"
fi

# note that if we build statically, we will need the static c libraries.
# you might not have them. you might need to run "sudo yum install glibc-static"

# linking the objects for non-test use
$WEBSERVER_C_COMPILER -static $WEBSERVER_DEVEL_OBJECTS/server_library.o $WEBSERVER_DEVEL_OBJECTS/business_library.o $WEBSERVER_DEVEL_OBJECTS/server.o -o $WEBSERVER_DEVEL_EXEC/server
echo work finished.

set +e
