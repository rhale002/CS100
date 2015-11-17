#!/bin/bash

#tests multi commands

#Test various spacing
echo --------------------------------------------------------------------------
echo Test various spacing
echo --------------------------------------------------------------------------
echo 'ls -a; echo hello&& mkdir DELETE|| echo world; git status' | bin/rshell
echo 'ls -a ;echo hello &&mkdir DELETE ||echo world ;git status' | bin/rshell
echo \
'ls -a    ;   echo hello    &&    mkdir DELETE   ||   echo world  ; git status'\
| bin/rshell

#test some basic command combinations
echo 
echo --------------------------------------------------------------------------
echo Test basic command combinations
echo --------------------------------------------------------------------------
echo 'ls -a; ls -a ; ls -a; ls -a; ls -a' | bin/rshell
echo
echo 'ls -a && echo hello&& mkdir DELETE&& echo world&& git status' | bin/rshell
echo
echo 'ls -a || echo hello|| mkdir DELETE|| echo world|| git status' | bin/rshell
echo
echo 'ls -a || echo hello|| mkdir DELETE&& echo world|| git status' | bin/rshell
echo
echo 'ls -a && echo hello|| mkdir DELETE|| echo world|| git status' | bin/rshell
echo
echo 'mkdir DELETE||mkdir DELETE||mkdir DELETE||mkdir DELETE|| ls ' | bin/rshell
echo
echo 'mkdir DELETE&&mkdir DELETE&&mkdir DELETE&&mkdir DELETE&& ls ' | bin/rshell
echo
echo 'rmdir DELETE&&mkdir DELETE||rmdir DELETE&&mkdir DELETE&& ls' | bin/rshell

#Test single character connectors
echo 
echo --------------------------------------------------------------------------
echo Test single character connectors
echo --------------------------------------------------------------------------
echo 'ls -a; echo hello& mkdir DELETE| echo world; git status' | bin/rshell
echo
echo 'ls -a; echo hello& mkdir DELETE|| echo world; git status' | bin/rshell
echo
echo 'ls -a; echo hello&& mkdir DELETE| echo world; git status' | bin/rshell

#Test ending connectors
echo 
echo --------------------------------------------------------------------------
echo Test ending connectors
echo --------------------------------------------------------------------------
echo 'ls -a; echo hello&& mkdir DELETE|| echo world; git status &&' | bin/rshell
echo
echo 'ls -a; echo hello&& mkdir DELETE|| echo world; git status ||' | bin/rshell
echo
echo 'ls -a; echo hello&& mkdir DELETE|| echo world; git status ;' | bin/rshell

#Test bad command
echo 
echo --------------------------------------------------------------------------
echo Test bad commands
echo --------------------------------------------------------------------------
echo 'vohuenqw; echo hello&& mkdir DELETE|| echo world; git status' | bin/rshell
echo
echo 'ls -a; qwevqwnofv&& mkdir DELETE|| echo world; git status' | bin/rshell
echo
echo 'ls -a; echo hello&& mkdir DELETE|| wffno3qhio; git status' | bin/rshell
echo
echo 'ls -a; echo hello&& fdaosfwe|| echo world; git status' | bin/rshell
echo
echo 'ls -a; echo hello&& mkdir DELETE|| echo world; fjwoqnf' | bin/rshell

#Test starting connectors
echo 
echo --------------------------------------------------------------------------
echo Test starting connectors
echo --------------------------------------------------------------------------
echo '&& ls -a; echo hello&& mkdir DELETE|| echo world; git status' | bin/rshell
echo
echo '|| ls -a; echo hello&& mkdir DELETE|| echo world; git status' | bin/rshell
echo
echo '; ls -a; echo hello&& mkdir DELETE|| echo world; git status' | bin/rshell
echo
echo ' &&ls -a; echo hello&& mkdir DELETE|| echo world; git status' | bin/rshell
echo
echo ' ||ls -a; echo hello&& mkdir DELETE|| echo world; git status' | bin/rshell
echo
echo ' ;ls -a; echo hello&& mkdir DELETE|| echo world; git status' | bin/rshell

#Test with two connectors but no commands inbetween
echo 
echo --------------------------------------------------------------------------
echo Test with two connecots but no commands inbetween
echo --------------------------------------------------------------------------
echo 'ls -a&&&& echo hello&& mkdir DELETE|| echo world; git status' | bin/rshell
echo
echo 'ls -a; echo hello |||| mkdir DELETE|| echo world; git status' | bin/rshell
echo
echo 'ls -a; echo hello&& mkdir DELETE|| echo world ;; git status' | bin/rshell

