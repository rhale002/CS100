# rshell
Homework 1

Class: CS 100

Robyn Haley

#Description of Program
rshell is a program which simulates a shell such as bash. It does so through the use of C++ code. The program was written for my CS 100 class at UCR. The program used the execvp function in the unistd.h library to execute any input commands. The program only works for basic connectors such and "&&", "||", and ";" at the moment. It also only supports commands which execvp is capable of running.

#How to Run
Type "make all" into a terminal where the files and directories are to compile rshell and move it into a created bin folder. To execute the program, you may simply run the executable "rshell" which is stored within the created "bin" directory. Once executed it will output a "$" and prompt you to enter a command. Once a command is entered use \n to execute it. The command will then be executed by rshell just as it would if the command was input into a shell such as bash. rshell also supports a command "exit" which will exit out of the shell upon reaching the command. 

#Known Bugs/Errors
While no bugs are currently known due to extensive testing and patching, rshell does not support a few things such as single '&' or '|' characters used between commands. The program also does not support any commands not already supported by the execvp function which is described in detail here: http://linux.die.net/man/3/execvp . Please contact me (Robyn Haley) at rhale002@ucr.edu if a bug is found and I will look into it. 

#Included Files and Directories
src

    main.cpp
        Description: Runs rshell.
        
    rshell.h
        Description: Contains all code for rshell including functions and classes.
tests

    single_command.sh
        Description: Used to test single commands within rshell.
        
    multi_command.sh
        Description: Used to test multi commands within rshell.
        
    commented_command.sh
        Description: Used to test commands which include comments within rshell.
        
    exit.sh
        Description: Used to test commands which include the "exit" function within rshell.
        
    base_test.sh
        Description: Used to test a basic command which was used for testing.
        
LICENSE

    Description: Contains license information for rshell project.

Makefile

    Description: Used to create a bin folder and move the rshell executable into it. Also includes a clean which removes the bin folder and its contents.

#Sample Code
Here is a quick example of the code which is used to run the entered commands:

    //Create bool to store whether command execution was a success
    bool ynSuccess = true;
    
    pid_t pid;
    int status;
    
    //Run fork and get parent id
    //If an error while forking occurs then say so and exit
    if ((pid = fork()) < 0) 
    {
        cout << "ERROR: forking child process failed" << endl;
        exit(1);
    }
    else if (pid == 0) 
    {
        //Run the command
        if(execvp(*args, args) < 0)
            perror(NULL);
    }
    else 
    {
        //Wait for completion
        while (wait(&status) != pid);
        
        //Tests if command executed properly and if not sets success to false
        if (WIFEXITED(status))
        {
            if (WEXITSTATUS(status) != 0)
            {
                ynSuccess = false;
            }
        }
        else
        {
            ynSuccess = false;
        }
    }
    
    return ynSuccess;
    
This code is taken from the "bool runCommand(char** args)" function within rshell which takes in a command as a char** and executes it. The function also keeps track of whether the function succeeeded or not for later use with connectors for multi command strings. 
      
#License
Read LICENSE file for more information.


