#!/bin/bash

#tests commands with comments

#Test various hash placement
echo --------------------------------------------------------------------------
echo Test various hash placement
echo --------------------------------------------------------------------------
echo 'ls -a; echo hello&& mkdir DELETE # echo world; git status' | bin/rshell
echo
echo 'ls -a; echo hello&& mkdir DELETE|| echo world #git status' |bin/rshell
echo
echo 'ls -a; echo hello&& mkdir DELETE|| echo world; git status#' |bin/rshell
echo
echo 'ls -a; echo hello&& mkdir DELETE # echo world; git status' | bin/rshell

#Test starting hashes
echo 
echo --------------------------------------------------------------------------
echo Test starting hashes
echo --------------------------------------------------------------------------
echo '#ls -a; echo hello&& mkdir DELETE|| echo world; git status' | bin/rshell
echo
echo '   #ls -a; echo hello&& mkdir DELETE|| echo world; git status' |bin/rshell


#test hashes right next to other commands
echo 
echo --------------------------------------------------------------------------
echo Test hashes right next to other commands
echo --------------------------------------------------------------------------
echo 'ls -a; echo hello# mkdir DELETE|| echo world; git status' |bin/rshell
echo
echo 'ls -a# echo hello&& mkdir DELETE|| echo world; git status' | bin/rshell
echo
echo 'ls -a# && echo hello&& mkdir DELETE|| echo world; git status' | bin/rshell
echo
echo 'ls -a# || echo hello&& mkdir DELETE|| echo world; git status' | bin/rshell

#Test starting connectors
echo 
echo --------------------------------------------------------------------------
echo Test starting connectors
echo --------------------------------------------------------------------------
echo '&&ls -a; echo hello# mkdir DELETE|| echo world; git status' | bin/rshell
echo
echo '||ls -a; echo hello&& mkdir DELETE# echo world; git status' | bin/rshell
echo
echo ';ls -a; echo hello&& mkdir DELETE|| # echo world; git status' | bin/rshell

#Test hashes next to connectors with no commands in between
echo 
echo --------------------------------------------------------------------------
echo Test hashes next to connectors with no commands in between
echo --------------------------------------------------------------------------
echo 'ls -a; echo hello&& mkdir DELETE|| # echo world; git status' | bin/rshell
echo
echo 'ls -a; echo hello&& # mkdir DELETE|| echo world; git status' | bin/rshell
echo
echo 'ls -a; echo hello&& mkdir DELETE; # echo world; git status' | bin/rshell