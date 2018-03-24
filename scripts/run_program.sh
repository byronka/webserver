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

$CURRENT_DIR/build_program.sh

$WEBSERVER_DEVEL_EXEC/pant_size $1

