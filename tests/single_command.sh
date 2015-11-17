#!/bin/bash

#tests single commands

#Test various basic commands
echo --------------------------------------------------------------------------
echo Test various basic commands
echo --------------------------------------------------------------------------
echo 'ls' | bin/rshell
echo
echo 'ls -a' | bin/rshell
echo
echo 'ls -al' | bin/rshell
echo
echo 'echo hello' | bin/rshell
echo
echo 'echo hello world' | bin/rshell
echo
echo 'echo hello world! This' | bin/rshell
echo
echo 'echo hello world! This program' | bin/rshell
echo
echo 'echo Hello world! This program works!' | bin/rshell
echo
echo 'date' | bin/rshell
echo
echo 'cal' | bin/rshell
echo
echo 'mkdir DeleteMe' | bin/rshell
echo
echo 'echo DeleteMe Directory created' | bin/rshell
echo
echo 'rmdir DeleteMe' | bin/rshell
echo
echo 'echo DeleteMe Directory removed' | bin/rshell

#test ending connectors
echo 
echo --------------------------------------------------------------------------
echo Test ending connectors
echo --------------------------------------------------------------------------
echo 'echo hello &&' | bin/rshell
echo
echo 'ls -a ||' | bin/rshell
echo
echo 'ls -a ;' | bin/rshell

#Test bad command
echo 
echo --------------------------------------------------------------------------
echo Test bad command
echo --------------------------------------------------------------------------
echo 'sdanov3ewojn' | bin/rshell

#Test single character connectors
echo 
echo --------------------------------------------------------------------------
echo Test single character connectors
echo --------------------------------------------------------------------------
echo 'ls |' | bin/rshell
echo
echo 'ls &' | bin/rshell
echo
echo 'ls ;' | bin/rshell

#Test Starting connectors
echo 
echo --------------------------------------------------------------------------
echo Test starting connectors
echo --------------------------------------------------------------------------
echo '&& ls' | bin/rshell
echo
echo '|| ls' | bin/rshell
echo
echo '; ls' | bin/rshell

#Test for empty command string
echo 
echo --------------------------------------------------------------------------
echo Test empty command string
echo --------------------------------------------------------------------------
echo '' | bin/rshell
echo
echo '             ' | bin/rshell
echo
echo '                                 ' | bin/rshell

#Test for lots of space then command
echo 
echo --------------------------------------------------------------------------
echo Test for lots of space then command
echo --------------------------------------------------------------------------
echo '               ls -a' | bin/rshell