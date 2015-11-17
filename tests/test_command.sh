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
#multiple flags 
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

#No arguments after flag
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
echo 'test' | bin/rshell

#Too many arguments
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

#Hash signs
echo
echo 'test # && echo hello' | bin/rshell
echo
echo 'test #&& echo hello' | bin/rshell

#Bad flags
echo
echo 'test -fnsjofh bin && echo hello' | bin/rshell
echo
echo 'test -fnsjofh bin || echo hello' | bin/rshell

#Test [ ] symbolic test commands
echo 
echo --------------------------------------------------------------------------
echo Test [ ] symbolic test commands
echo --------------------------------------------------------------------------
#basic Tests
echo '[bin] && echo hello' | bin/rshell
echo
echo '[bin] || echo hello' | bin/rshell
echo
echo '[-e bin] && echo hello' | bin/rshell
echo
echo '[-e bin] || echo hello' | bin/rshell
echo
echo '[-f bin] && echo hello' | bin/rshell
echo
echo '[-f bin] || echo hello' | bin/rshell
echo
echo '[-f LICENSE] && echo hello' | bin/rshell
echo
echo '[-f LICENSE] || echo hello' | bin/rshell
echo
echo '[-d bin] && echo hello' | bin/rshell
echo
echo '[-d bin] || echo hello' | bin/rshell
echo
echo '[-d LICENSE] && echo hello' | bin/rshell
echo
echo '[-d LICENSE] || echo hello' | bin/rshell

#Test spacing
echo
echo '     [bin]    &&      echo     hello    ' | bin/rshell
echo
echo '     [bin]    ||      echo     hello    ' | bin/rshell
echo
echo '     [   bin   ]    &&      echo     hello    ' | bin/rshell
echo
echo '     [   bin   ]    ||      echo     hello    ' | bin/rshell

#test no ending [ ]
echo
echo '[bin || echo hello' | bin/rshell
echo
echo '[bin # || echo hello' | bin/rshell

#Test hash inside of [ ]
echo
echo '[bin#] || echo hello' | bin/rshell
echo
echo '[bin#  ] || echo hello' | bin/rshell
echo
echo '[bin   #   ] || echo hello' | bin/rshell
echo
echo '[ # bin] || echo hello' | bin/rshell
echo
echo '[#bin] || echo hello' | bin/rshell
echo
echo '#[bin] || echo hello' | bin/rshell


