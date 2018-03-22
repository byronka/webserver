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

$CURRENT_DIR/build_server.sh

echo running server...
$WEBSERVER_DEVEL_BUILD/server
echo work finished.

