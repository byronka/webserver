#!/usr/local/bin/bash

#will stop script processing on an error
set -e

#shows commands as they run.
set -x

#pulls in constants we need, like build directory
source s/constants.sh

echo deleting all .o files
rm $BUILD_DIRECTORY/*.o
echo all .o files deleted
