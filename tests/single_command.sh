#!/bin/bash

#tests single commands
echo 'ls' | bin/rshell
echo 'ls -a' | bin/rshell
echo 'ls -al' | bin/rshell
echo 'echo hello' | bin/rshell
echo 'echo hello world' | bin/rshell
echo 'echo hello world! This' | bin/rshell
echo 'echo hello world! This program' | bin/rshell
echo 'echo Hello world! This program works!' | bin/rshell
echo 'date' | bin/rshell
echo 'cal' | bin/rshell
echo 'mkdir DeleteMe' | bin/rshell
echo 'echo DeleteMe Directory created' | bin/rshell
echo 'rmdir DeleteMe' | bin/rshell
echo 'echo DeleteMe Directory removed' | bin/rshell
echo 'echo hello &&' | bin/rshell
echo 'ls -a ||' | bin/rshell
echo 'ls -a ;' | bin/rshell

