#!/usr/bin/env sh

# reference some boilerplate stuff - constants and more.
SCRIPT=$(readlink -f "$0")
CURRENT_DIR=$(dirname "$SCRIPT")
source $CURRENT_DIR/script_standards.sh

echo deleting tests...
rm $WEBSERVER_DEVEL_BUILD/server_tests
rm $WEBSERVER_DEVEL_BUILD/business_tests
echo tests deleted.

source $CURRENT_DIR/closedown.sh
