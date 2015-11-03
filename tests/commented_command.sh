#!/bin/bash

#tests commands with comments
echo 'ls -a; echo hello&& mkdir DELETE # echo world; git status' | bin/rshell
echo '#ls -a; echo hello&& mkdir DELETE|| echo world; git status' | bin/rshell
echo '   #ls -a; echo hello&& mkdir DELETE|| echo world; git status' |bin/rshell
echo 'ls -a; echo hello&& mkdir DELETE|| echo world #git status' |bin/rshell
echo 'ls -a; echo hello&& mkdir DELETE|| echo world; git status#' |bin/rshell
echo 'ls -a; echo hello&& mkdir DELETE # echo world; git status' | bin/rshell

#Having hash signs in echo arguments is cray. Otherwise works.
echo 'ls -a; echo hello# mkdir DELETE|| echo world; git status' |bin/rshell

#Doesn't give error for hash being next to argument
echo 'ls -a# echo hello&& mkdir DELETE|| echo world; git status' | bin/rshell