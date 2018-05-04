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

# remove the top-level build directory
if [ -d "$WEBSERVER_DEVEL_BUILD" ]; then
  rm -fr $WEBSERVER_DEVEL_BUILD
  echo "deleted $WEBSERVER_DEVEL_BUILD"
  exit
fi
echo "no directory exists at $WEBSERVER_DEVEL_BUILD"

