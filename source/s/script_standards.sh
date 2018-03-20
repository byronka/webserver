#!/usr/bin/env sh

#check that the base directory has been set in the environment.
#if not, tell the user to run the command first.
# this is necessary so we are then able to run our scripts
# from anywhere.
if [ -z "$WEBSERVER_ENV_VARIABLES" ]; then
  echo "You need to run set_environment_variables.sh in the top folder"
  echo "It sets a few necessary environment variables.  See that file."
  exit 1
fi  

#following will cause the script to halt if any program returns
#a non-zero (error) exit.
set -e

#show commands as they run
#set -x


