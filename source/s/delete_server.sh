#!/usr/local/bin/bash

#shows commands as we run them
set -x

#halts script processing on an error.
set -e

echo deleting server executable
rm build/server
echo server executable deleted
