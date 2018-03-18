#!/usr/local/bin/bash

#shows commands as we run them
set -x

#halts script processing on an error.
set -e

#get some constants like BUILD_DIRECTORY
source s/constants.sh

echo deleting server executable
rm $BUILD_DIRECTORY/server
echo server executable deleted
