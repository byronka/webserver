#!/usr/local/bin/bash

#halts script processing on error
set -e

#shows commands as we run them
set -x

echo deleting tests...
rm build/tests
echo tests deleted.
