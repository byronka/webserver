#!/usr/bin/env sh

# reference some boilerplate stuff - constants and more.
SCRIPT=$(readlink -f "$0")
CURRENT_DIR=$(dirname "$SCRIPT")
source $CURRENT_DIR/script_standards.sh

$CURRENT_DIR/build_server.sh

echo running server...
$WEBSERVER_DEVEL_BUILD/server
echo work finished.

source $CURRENT_DIR/closedown.sh
