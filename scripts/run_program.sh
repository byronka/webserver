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

$CURRENT_DIR/build_program.sh

echo running server...
$WEBSERVER_DEVEL_EXEC/pant_size $1
echo work finished.

