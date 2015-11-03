#!/bin/bash

#tests commands with ;, &&, or ||
echo 'ls -a; echo hello&& mkdir DELETE|| echo world; git status' | bin/rshell
echo 'ls -a ;echo hello &&mkdir DELETE ||echo world ;git status' | bin/rshell
echo \
'ls -a    ;   echo hello    &&    mkdir DELETE   ||   echo world  ; git status'\
| bin/rshell
echo 'ls -a; ls -a ; ls -a; ls -a; ls -a' | bin/rshell
echo 'ls -a && echo hello&& mkdir DELETE&& echo world&& git status' | bin/rshell
echo 'ls -a || echo hello|| mkdir DELETE|| echo world|| git status' | bin/rshell
echo 'ls -a || echo hello|| mkdir DELETE&& echo world|| git status' | bin/rshell
echo 'ls -a && echo hello|| mkdir DELETE|| echo world|| git status' | bin/rshell
echo 'mkdir DELETE||mkdir DELETE||mkdir DELETE||mkdir DELETE|| ls ' | bin/rshell
echo 'mkdir DELETE&&mkdir DELETE&&mkdir DELETE&&mkdir DELETE&& ls ' | bin/rshell
echo 'rmdir DELETE&&mkdir DELETE||rmdir DELETE&&mkdir DELETE&& ls' | bin/rshell


#NOTICE ME: Doesn't work with single & or | because they are meant
#to do something we don't handle
#echo 'ls -a; echo hello& mkdir DELETE| echo world; git status' | bin/rshell
