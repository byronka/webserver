#!/usr/bin/env sh

SCRIPT=$(readlink -f "$0")
CURRENT_DIR=$(dirname "$SCRIPT")

$CURRENT_DIR/delete_tests.sh
