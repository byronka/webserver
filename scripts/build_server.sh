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





###############################
# Variable Declarations BEGIN #
###############################
# variables we'll use later in the script.

#setting some aliases to have shorter command strings.
SRC=$WEBSERVER_DEVEL_SOURCE
BLD=$WEBSERVER_DEVEL_BUILD
CC=$WEBSERVER_C_COMPILER 

#############################
# Variable Declarations END #
#############################





##############################
# Command Execution BEGIN    #
##############################

set -e

#wipe out the current code. 
$CURRENT_DIR/delete_build.sh

# compile source files to object files if they need compiling.
$CURRENT_DIR/compile_source.sh STANDARD

# linking the objects for non-test use
$CC $BLD/server_library.o $BLD/business_library.o $BLD/server.o -o $BLD/server
echo work finished.

set +e
