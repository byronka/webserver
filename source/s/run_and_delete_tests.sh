#!/usr/local/bin/bash

#show commands as we run them
set -x

#stop on error
set -e

./run_tests.sh 
./delete_tests.sh
