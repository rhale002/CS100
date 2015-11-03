#!/bin/bash

#tests commands with comments
echo 'ls -a; echo hello&& mkdir DELETE # echo world; git status' | bin/rshell
echo '#ls -a; echo hello&& mkdir DELETE|| echo world; git status' | bin/rshell
echo '   #ls -a; echo hello&& mkdir DELETE|| echo world; git status' |bin/rshell