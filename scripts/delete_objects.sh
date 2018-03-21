#!/usr/bin/env sh

# reference some boilerplate stuff - constants and more.
SCRIPT=$(readlink -f "$0")
CURRENT_DIR=$(dirname "$SCRIPT")
source $CURRENT_DIR/script_standards.sh

echo deleting all .o files
rm $WEBSERVER_DEVEL_BUILD/*.o
echo all .o files deleted

source $CURRENT_DIR/closedown.sh
