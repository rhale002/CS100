#!/bin/bash

#tests test command

#Test with no flags
echo --------------------------------------------------------------------------
echo Test with no flags
echo --------------------------------------------------------------------------
echo 'test bin && echo hello' | bin/rshell
echo
echo 'test djsafj && echo hello' | bin/rshell
echo
echo 'test bin || echo hello' | bin/rshell
echo
echo 'test fhkwjs || echo hello' | bin/rshell
echo
echo 'test bin # echo hello' | bin/rshell
echo
echo 'test fghsdj # echo hello' | bin/rshell
echo
echo '#test bin && echo hello' | bin/rshell

#Test with -e flag
echo 
echo --------------------------------------------------------------------------
echo Test with -e flag
echo --------------------------------------------------------------------------
echo 'test -e bin && echo hello' | bin/rshell
echo
echo 'test -e djsafj && echo hello' | bin/rshell
echo
echo 'test -e bin || echo hello' | bin/rshell
echo
echo 'test -e fhkwjs || echo hello' | bin/rshell
echo
echo 'test -e bin # echo hello' | bin/rshell
echo
echo 'test -e fghsdj # echo hello' | bin/rshell
echo
echo '#test -e bin && echo hello' | bin/rshell

#Test with -f flag
echo 
echo --------------------------------------------------------------------------
echo Test with -f flag
echo --------------------------------------------------------------------------
echo 'test -f bin && echo hello' | bin/rshell
echo
echo 'test -f LICENSE && echo hello' | bin/rshell
echo
echo 'test -f bin || echo hello' | bin/rshell
echo
echo 'test -f LICENSE || echo hello' | bin/rshell
echo
echo 'test -f bin # echo hello' | bin/rshell
echo
echo 'test -f LICENSE # echo hello' | bin/rshell
echo
echo '#test -f LICENSE && echo hello' | bin/rshell


#Test with -d flag
echo 
echo --------------------------------------------------------------------------
echo Test with -d flag
echo --------------------------------------------------------------------------
echo 'test -d bin && echo hello' | bin/rshell
echo
echo 'test -d LICENSE && echo hello' | bin/rshell
echo
echo 'test -d bin || echo hello' | bin/rshell
echo
echo 'test -d LICENSE || echo hello' | bin/rshell
echo
echo 'test -d bin # echo hello' | bin/rshell
echo
echo 'test -d LICENSE # echo hello' | bin/rshell
echo
echo '#test -d LICENSE && echo hello' | bin/rshell


#Test with weird combinations
echo 
echo --------------------------------------------------------------------------
echo Test with weird combinations
echo --------------------------------------------------------------------------
echo 'test -d -f && echo hello' | bin/rshell
echo
echo 'test -d -f || echo hello' | bin/rshell
echo
echo 'test -f -f && echo hello' | bin/rshell
echo
echo 'test -f -f || echo hello' | bin/rshell
echo
echo 'test -e -f && echo hello' | bin/rshell
echo
echo 'test -e -f || echo hello' | bin/rshell
echo
echo 'test && echo hello' | bin/rshell
echo
echo 'test || echo hello' | bin/rshell
echo
echo 'test -e && echo hello' | bin/rshell
echo
echo 'test -e || echo hello' | bin/rshell
echo
echo 'test -d && echo hello' | bin/rshell
echo
echo 'test -d || echo hello' | bin/rshell
echo
echo 'test -f && echo hello' | bin/rshell
echo
echo 'test -f || echo hello' | bin/rshell
echo
echo 'test dfjl fsdjk && echo hello' | bin/rshell
echo
echo 'test dfjl fsdjk || echo hello' | bin/rshell
echo
echo 'test dfjl fsdjk dsfajl && echo hello' | bin/rshell
echo
echo 'test dfjl fsdjk dsfajl || echo hello' | bin/rshell
echo
echo 'test -dfjl fsdjk dsfajl && echo hello' | bin/rshell
echo
echo 'test -dfjl fsdjk dsfajl || echo hello' | bin/rshell
echo
echo 'test -dfjl fsdjk dsfajl dsafj && echo hello' | bin/rshell
echo
echo 'test -dfjl fsdjk dsfajl sdaff || echo hello' | bin/rshell

