#!/usr/bin/env sh

SCRIPT=$(readlink -f "$0")
CURRENT_DIR=$(dirname "$SCRIPT")

$CURRENT_DIR/run_and_delete_tests.sh
