WEBSERVER
=========

this program will provide the functions necessary for a web
application.  It will be fast, and simple.  It won't necessarily be
easy.

1. server
2. database

Start your process by running the following command from the top
directory:

./set_environment_variables.

This will run a script that injects certain necessary variables into
the environment and will return you in a subshell.


Simple
------
In order to avoid unecessary complexity in this development
environment, the following choices were made:
1) _Minimal dependencies_: very few extra dependencies were used for
this code.  We have no database.  No database connector.  No web
server, no plugins, no unit test framework, no IoC framework, no build
framework, no dependency or package manager.
2) _Heavy on the unit tests and documentation_.
// The following line sets the configuration when using Vim
// vim: ai:tw=70
