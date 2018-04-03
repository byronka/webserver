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

# remove the top-level build directory
if [ -d "$WEBSERVER_DEVEL_BUILD" ]; then
  rm -fr $WEBSERVER_DEVEL_BUILD
fi

