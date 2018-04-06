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





###############################
# Variable Declarations BEGIN #
###############################
# variables we'll use later in the script.

#setting variable to count number of objects built
COUNT_OF_OBJECTS_BUILT=0

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
COMPILE_MODE=$1

#############################
# Variable Declarations END #
#############################





##############################
# Function definitions BEGIN #
##############################

# if the build directory doesn't exist, create it.
create_build_directory_if_necessary() {
  if [ ! -d "$WEBSERVER_DEVEL_OBJECTS" ]; then
    if [ $LOG_MODE == "DEBUG" ]; then
      echo "objects build directory didn't exist.  creating it..."
    fi
    mkdir -p $WEBSERVER_DEVEL_OBJECTS
    if [ $LOG_MODE == "DEBUG" ]; then
      echo "build directory created"
    fi
  fi
}

#compile a c source file to an object in the build directory
build() {
  $WEBSERVER_C_COMPILER $CC_PARAMS --std=gnu99 -c $WEBSERVER_DEVEL_SOURCE/$1.c -o $WEBSERVER_DEVEL_OBJECTS/$1.o
  COUNT_OF_OBJECTS_BUILT=$((COUNT_OF_OBJECTS_BUILT + 1))
}

# a function that builds objects if, and *only* if
# the object file either doesn't exist or if the source file is
# newer than the object file.
# parameters: takes the name of a source file, with the .c suffix removed.
# results: builds an object file if needed, otherwise does nothing.
build_if_not_exist() {
  # if the built file doesn't exist, build it and return
  if [ ! -f "$WEBSERVER_DEVEL_OBJECTS/$1.o" ]; then
    if [ $LOG_MODE == "DEBUG" ]; then
      echo "building $1.c because it didn't exist"
    fi
    build $1
    return
  fi

  if [ "$WEBSERVER_DEVEL_SOURCE/$1.c" -nt "$WEBSERVER_DEVEL_OBJECTS/$1.o" ]; then
    if [ $LOG_MODE == "DEBUG" ]; then
      echo "building $1.c because the source file is newer that the object file"
    fi
    build $1
    return
  fi
}


loop_through_source_files_and_build_if_needed() {
  if [ $LOG_MODE == "DEBUG" ]; then
    echo building objects...
  fi
  for f in $WEBSERVER_DEVEL_SOURCE/*.c; do build_if_not_exist $(basename -s .c $f); done
}


# mainly used to switch between normal and debug modes of compilation
set_compiler_parameters() {
  if [ -z "$COMPILE_MODE" ]; then
    if [ $LOG_MODE == "DEBUG" ]; then
      echo "COMPILE_MODE was not provided. Setting to STANDARD"
    fi
    COMPILE_MODE="STANDARD"
  fi

  if [ $COMPILE_MODE == "STANDARD" ]; then
    CC_PARAMS=" -c "
  elif [ $COMPILE_MODE == "DEBUG" ]; then
    CC_PARAMS=" -c -g -DDEBUG "
  else
    echo "ERROR: ran to the end of the build modes without selecting one."
    echo "ERROR: needed to be passed either STANDARD or DEBUG for the compile mode"
    exit 4
  fi

  if [ $LOG_MODE == "DEBUG" ]; then
    echo COMPILE_MODE is $COMPILE_MODE
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
if [ $LOG_MODE == "DEBUG" ]; then
  echo $COUNT_OF_OBJECTS_BUILT objects built
fi
set +e

##############################
# Command Execution END      #
##############################

