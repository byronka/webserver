#!/usr/bin/env sh

# reference some boilerplate stuff - constants and more.
SCRIPT=$(readlink -f "$0")
CURRENT_DIR=$(dirname "$SCRIPT")
source $CURRENT_DIR/script_standards.sh

$WEBSERVER_DEVEL_SCRIPT/run_tests.sh 
$WEBSERVER_DEVEL_SCRIPT/delete_tests.sh

source $CURRENT_DIR/closedown.sh
