#!/bin/bash

#tests multi commands

#Test various spacing
echo 'ls -a; echo hello&& mkdir DELETE|| echo world; git status' | bin/rshell
echo 'ls -a ;echo hello &&mkdir DELETE ||echo world ;git status' | bin/rshell
echo \
'ls -a    ;   echo hello    &&    mkdir DELETE   ||   echo world  ; git status'\
| bin/rshell

#test some basic command combinations
echo 'ls -a; ls -a ; ls -a; ls -a; ls -a' | bin/rshell
echo 'ls -a && echo hello&& mkdir DELETE&& echo world&& git status' | bin/rshell
echo 'ls -a || echo hello|| mkdir DELETE|| echo world|| git status' | bin/rshell
echo 'ls -a || echo hello|| mkdir DELETE&& echo world|| git status' | bin/rshell
echo 'ls -a && echo hello|| mkdir DELETE|| echo world|| git status' | bin/rshell
echo 'mkdir DELETE||mkdir DELETE||mkdir DELETE||mkdir DELETE|| ls ' | bin/rshell
echo 'mkdir DELETE&&mkdir DELETE&&mkdir DELETE&&mkdir DELETE&& ls ' | bin/rshell
echo 'rmdir DELETE&&mkdir DELETE||rmdir DELETE&&mkdir DELETE&& ls' | bin/rshell

#Test single character connectors
echo 'ls -a; echo hello& mkdir DELETE| echo world; git status' | bin/rshell
echo 'ls -a; echo hello& mkdir DELETE|| echo world; git status' | bin/rshell
echo 'ls -a; echo hello&& mkdir DELETE| echo world; git status' | bin/rshell

#Test ending connectors
echo 'ls -a; echo hello&& mkdir DELETE|| echo world; git status &&' | bin/rshell
echo 'ls -a; echo hello&& mkdir DELETE|| echo world; git status ||' | bin/rshell
echo 'ls -a; echo hello&& mkdir DELETE|| echo world; git status ;' | bin/rshell

#Test bad command
echo 'vohuenqw; echo hello&& mkdir DELETE|| echo world; git status' | bin/rshell
echo 'ls -a; qwevqwnofv&& mkdir DELETE|| echo world; git status' | bin/rshell
echo 'ls -a; echo hello&& mkdir DELETE|| wffno3qhio; git status' | bin/rshell
echo 'ls -a; echo hello&& fdaosfwe|| echo world; git status' | bin/rshell
echo 'ls -a; echo hello&& mkdir DELETE|| echo world; fjwoqnf' | bin/rshell

#Test starting connectors
echo '&& ls -a; echo hello&& mkdir DELETE|| echo world; git status' | bin/rshell
echo '|| ls -a; echo hello&& mkdir DELETE|| echo world; git status' | bin/rshell
echo '; ls -a; echo hello&& mkdir DELETE|| echo world; git status' | bin/rshell
echo ' &&ls -a; echo hello&& mkdir DELETE|| echo world; git status' | bin/rshell
echo ' ||ls -a; echo hello&& mkdir DELETE|| echo world; git status' | bin/rshell
echo ' ;ls -a; echo hello&& mkdir DELETE|| echo world; git status' | bin/rshell

#Test with two connectors but no commands inbetween
echo 'ls -a&&&& echo hello&& mkdir DELETE|| echo world; git status' | bin/rshell
echo 'ls -a; echo hello |||| mkdir DELETE|| echo world; git status' | bin/rshell
echo 'ls -a; echo hello&& mkdir DELETE|| echo world ;; git status' | bin/rshell

