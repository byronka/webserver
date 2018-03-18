#!/usr/local/bin/bash

#halts script processing on error
set -e

#shows commands as we run them
set -x

#get some constants like BUILD_DIRECTORY
source s/constants.sh

echo deleting tests...
rm $BUILD_DIRECTORY/tests
echo tests deleted.
