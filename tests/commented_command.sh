#!/bin/bash

#tests commands with comments

#Test various hash placement
echo 'ls -a; echo hello&& mkdir DELETE # echo world; git status' | bin/rshell
echo 'ls -a; echo hello&& mkdir DELETE|| echo world #git status' |bin/rshell
echo 'ls -a; echo hello&& mkdir DELETE|| echo world; git status#' |bin/rshell
echo 'ls -a; echo hello&& mkdir DELETE # echo world; git status' | bin/rshell

#Test starting hashes
echo '#ls -a; echo hello&& mkdir DELETE|| echo world; git status' | bin/rshell
echo '   #ls -a; echo hello&& mkdir DELETE|| echo world; git status' |bin/rshell


#test hashes right next to other commands
echo 'ls -a; echo hello# mkdir DELETE|| echo world; git status' |bin/rshell
echo 'ls -a# echo hello&& mkdir DELETE|| echo world; git status' | bin/rshell
echo 'ls -a# && echo hello&& mkdir DELETE|| echo world; git status' | bin/rshell
echo 'ls -a# || echo hello&& mkdir DELETE|| echo world; git status' | bin/rshell

#Test starting connectors
echo '&&ls -a; echo hello# mkdir DELETE|| echo world; git status' | bin/rshell
echo '||ls -a; echo hello&& mkdir DELETE# echo world; git status' | bin/rshell
echo ';ls -a; echo hello&& mkdir DELETE|| # echo world; git status' | bin/rshell

#Test hashes next to connectors with no commands in between
echo 'ls -a; echo hello&& mkdir DELETE|| # echo world; git status' | bin/rshell
echo 'ls -a; echo hello&& # mkdir DELETE|| echo world; git status' | bin/rshell
echo 'ls -a; echo hello&& mkdir DELETE; # echo world; git status' | bin/rshell