#tests commands with ;, &&, or ||
echo 'ls -a; echo hello&& mkdir DELETE|| echo world; git status' | bin/rshell
echo 'ls -a; ls -a ; ls -a; ls -a; ls -a' | bin/rshell
echo 'ls -a && echo hello&& mkdir DELETE&& echo world&& git status' | bin/rshell
echo 'ls -a || echo hello|| mkdir DELETE|| echo world|| git status' | bin/rshell
#NOTICE ME: Doesn't work with single ands or ors because they are meant
#to do something we don't handle
echo 'ls -a; echo hello& mkdir DELETE| echo world; git status' | bin/rshell
