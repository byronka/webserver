#!/usr/bin/env sh

# reference some boilerplate stuff - constants and more.
SCRIPT=$(readlink -f "$0")
CURRENT_DIR=$(dirname "$SCRIPT")
source $CURRENT_DIR/script_standards.sh

if [ -d "$WEBSERVER_DEVEL_BUILD" ]; then
  rm -fr $WEBSERVER_DEVEL_BUILD
fi

source $CURRENT_DIR/closedown.sh
