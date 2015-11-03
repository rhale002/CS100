#tests commands with ;, &&, or ||
echo 'ls -a; echo hello&& mkdir DELETE|| echo world; git status' | bin/rshell
echo 'ls -a; ls -a ; ls -a; ls -a; ls -a' | bin/rshell
echo 'ls -a && echo hello&& mkdir DELETE&& echo world&& git status' | bin/rshell