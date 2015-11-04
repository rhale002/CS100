#!/bin/bash

#tests exit and commands with exit
echo 'ls -a; echo hello&& exit || echo world; git status' | bin/rshell
echo 'exit; ls -a;echo hello&& mkdir DELETE||echo world;git status' | bin/rshell
echo 'ls -a; echo hello&& mkdir DELETE&& exit; git status' | bin/rshell
echo 'ls -a; echo hello&& mkdir DELETE|| echo world; exit' | bin/rshell
echo 'ls -a; echo hello&& mkdir DELETE|| echo world; exit&&' | bin/rshell