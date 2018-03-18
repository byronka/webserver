#!/usr/local/bin/bash

echo building objects, linking, and running tests..
clang -c *.c && clang *.o -o tests && ./tests
