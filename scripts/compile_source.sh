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

#setting variable to count number of objects built
COUNT_OF_OBJECTS_BUILT=0

#setting some aliases to have shorter command strings.

#the source file directory
SRC=$WEBSERVER_DEVEL_SOURCE

# the build directory
BLD=$WEBSERVER_DEVEL_BUILD

# the compiler we want to use
CC=$WEBSERVER_C_COMPILER 

# the parameters we want to send to the compiler
# possibilities: 
# -c : create an object file
# -g : add debugging info
# -DDEBUG : add a token "DEBUG" that will alter the behavior of 
#    the code in some instances
# --std=gnu99 : use the GNU version of the C99 standard
CC_PARAMS=""

# The comple mode - either STANDARD or DEBUG.
# main difference being that in DEBUG, we add debugging symbols.
# This variable will be adjusted by a function later, set_compiler_parameters
RUN_MODE=$1
echo RUN_MODE is $RUN_MODE

#############################
# Variable Declarations END #
#############################





##############################
# Function definitions BEGIN #
##############################

# if the build directory doesn't exist, create it.
create_build_directory_if_necessary() {
  if [ ! -d "$WEBSERVER_DEVEL_BUILD" ]; then
    echo "build directory didn't exist.  creating it..."
    mkdir $WEBSERVER_DEVEL_BUILD
    echo "build directory created"
  fi
}

#compile a c source file to an object in the build directory
build() {
  $CC $CC_PARAMS --std=gnu99 -c $SRC/$1.c -o $BLD/$1.o
  COUNT_OF_OBJECTS_BUILT=$((COUNT_OF_OBJECTS_BUILT + 1))
}

# a function that builds objects if, and *only* if
# the object file either doesn't exist or if the source file is
# newer than the object file.
# parameters: takes the name of a source file, with the .c suffix removed.
# results: builds an object file if needed, otherwise does nothing.
build_if_not_exist() {
  # if the built file doesn't exist, build it and return
  if [ ! -f "$BLD/$1.o" ]; then
    echo "building $1.c because it didn't exist"
    build $1
    return
  fi

  if [ "$SRC/$1.c" -nt "$BLD/$1.o" ]; then
    echo "building $1.c because the source file is newer that the object file"
    build $1
    return
  fi
}


loop_through_source_files_and_build_if_needed() {
  echo building objects...
  for f in $WEBSERVER_DEVEL_SOURCE/*.c; do build_if_not_exist $(basename -s .c $f); done
}


# mainly used to switch between normal and debug modes of compilation
set_compiler_parameters() {
  if [ $RUN_MODE == "STANDARD" ]; then
    CC_PARAMS=" -c "
  elif [ $RUN_MODE == "DEBUG" ]; then
    CC_PARAMS=" -c -g -DDEBUG "
  else
    echo "ERROR: needed to be passed either STANDARD or DEBUG for the compile mode"
  fi
}

##############################
# Function definitions END   #
##############################





##############################
# Command Execution BEGIN    #
##############################

set -e
create_build_directory_if_necessary
set_compiler_parameters
loop_through_source_files_and_build_if_needed
echo $COUNT_OF_OBJECTS_BUILT objects built
set +e

##############################
# Command Execution BEGIN    #
##############################

