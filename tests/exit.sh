#!/bin/bash

#tests exit and commands with exit
echo 'ls -a; echo hello&& exit || echo world; git status' | bin/rshell