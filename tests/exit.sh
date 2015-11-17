#!/bin/bash

#tests exit and commands with exit
echo --------------------------------------------------------------------------
echo Test exit and commands with exit
echo --------------------------------------------------------------------------
echo 'ls -a; echo hello&& exit || echo world; git status' | bin/rshell
echo
echo 'exit; ls -a;echo hello&& mkdir DELETE||echo world;git status' | bin/rshell
echo
echo 'ls -a; echo hello&& mkdir DELETE&& exit; git status' | bin/rshell
echo
echo 'ls -a; echo hello&& mkdir DELETE|| echo world; exit' | bin/rshell
echo
echo 'ls -a; echo hello&& mkdir DELETE|| echo world; exit&&' | bin/rshell
echo
echo 'ls -a; exit ; ls -a; ls -a; ls -a' | bin/rshell
echo
echo 'ls -a && exit&& mkdir DELETE&& echo world&& git status' | bin/rshell
echo
echo 'ls -a || echo hello|| exit|| echo world|| git status' | bin/rshell
echo
echo 'ls -a || echo hello|| mkdir DELETE&& echo world|| exit' | bin/rshell
echo
echo 'ls -a && echo hello|| mkdir DELETE|| echo world|| git status' | bin/rshell
echo
echo 'mkdir DELETE||exit||mkdir DELETE||exit|| ls ' | bin/rshell
echo
echo 'mkdir DELETE&&mkdir DELETE&&mkdir DELETE&&mkdir DELETE&& ls ' | bin/rshell
echo
echo 'rmdir DELETE&&exit||rmdir DELETE&&exit&& ls' | bin/rshell