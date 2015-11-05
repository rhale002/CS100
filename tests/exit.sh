#!/bin/bash

#tests exit and commands with exit
echo 'ls -a; echo hello&& exit || echo world; git status' | bin/rshell
echo 'exit; ls -a;echo hello&& mkdir DELETE||echo world;git status' | bin/rshell
echo 'ls -a; echo hello&& mkdir DELETE&& exit; git status' | bin/rshell
echo 'ls -a; echo hello&& mkdir DELETE|| echo world; exit' | bin/rshell
echo 'ls -a; echo hello&& mkdir DELETE|| echo world; exit&&' | bin/rshell
echo 'ls -a; exit ; ls -a; ls -a; ls -a' | bin/rshell
echo 'ls -a && exit&& mkdir DELETE&& echo world&& git status' | bin/rshell
echo 'ls -a || echo hello|| exit|| echo world|| git status' | bin/rshell
echo 'ls -a || echo hello|| mkdir DELETE&& echo world|| exit' | bin/rshell
echo 'ls -a && echo hello|| mkdir DELETE|| echo world|| git status' | bin/rshell
echo 'mkdir DELETE||exit||mkdir DELETE||exit|| ls ' | bin/rshell
echo 'mkdir DELETE&&mkdir DELETE&&mkdir DELETE&&mkdir DELETE&& ls ' | bin/rshell
echo 'rmdir DELETE&&exit||rmdir DELETE&&exit&& ls' | bin/rshell