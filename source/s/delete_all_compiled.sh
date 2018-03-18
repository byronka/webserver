#!/usr/local/bin/bash

#show commands as they run
set -x

#pull in constants, like BUILD_DIRECTORY
source constants.sh

if [ -d "$BUILD_DIRECTORY" ]; then
  rm -fr $BUILD_DIRECTORY
fi
