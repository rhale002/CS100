# rshell
Homework 1

Class: CS 100

Robyn Haley

#Description of Program
rshell is a program which simulates a shell such as bash. It does so through the use of C++ code. The program was written for my CS 100 class at UCR. The program used the execvp function in the unistd.h library to execute any input commands. The program only works for basic connectors such and "&&", "||", and ";" at the moment. It also only supports commands which execvp is capable of running. The program also supports the commands "test" and its symbolic representation "[ ]". The program also now supports the precedence operators "( )"

#How to Run
Type "make all" into a terminal where the files and directories are to compile rshell and move it into a created bin folder. To execute the program, you may simply run the executable "rshell" which is stored within the created "bin" directory. Once executed it will output a "$" and prompt you to enter a command. Once a command is entered use \n to execute it. The command will then be executed by rshell just as it would if the command was input into a shell such as bash. rshell also supports a command "exit" which will exit out of the shell upon reaching the command. 

#Known Bugs/Errors
The code does not support single connector operators such as '|' and '&'. The code also does not support the use of " " to distinguish test within say and echo operation. The program also does not support any commands not already supported by the execvp function which is described in detail here: http://linux.die.net/man/3/execvp . Please contact me (Robyn Haley) at rhale002@ucr.edu if a bug is found and I will look into it. 

#Included Files and Directories
src

    main.cpp
        Description: Runs rshell.
        
    rshell.h
        Description: Contains the connector classes and function declarations for rshell
    
    rshell.cpp
        Description: Contains all the definitions for the functions declared within rshell.h
tests

    single_command.script
        Description: Script showing all tests of single commands
        
    multi_command.script
        Description: Script showing all tests of multi commands
        
    commented_command.script
        Description: Script showing all tests of commented commands
        
    exit.script
        Description: Script showing all tests of the exit command
        
    base_test.script
        Description: Script showing my first basic test command
        
    precedence_test.script
        Description: Script showing all tests used to test (precedence)
        
    test_command.script
        description: Script showing all test used to test test and its symbolic representation [ ] 
        
Makefile

    Description: Used to create a bin folder and move the rshell executable into it. Also includes a clean which removes the bin folder and its contents.
    
LICENSE

    Description: Contains license information for rshell project.

README.md
    
    Description: The file you are now looking at which describes the program.

#Sample Code
Here is a quick example of the code which is used to run the entered commands:

    //Create bool to store whether command execution was a success
    bool ynSuccess = true;
    
    //If command is test do this
    if (strcmp(*args, "test") == 0)
    {
        struct stat buf;
        
        //Catch cases for too many arguments
        if (args [1] != NULL && args[1][0] == '-' && args[2] != NULL 
            && args[3] != NULL && args[4] == NULL)
        {
            cout << "test: " << args[2] << ": binary operator expected" << endl;
            return false;
        }
        else if (args[1] != NULL && args[1][0] == '-' && args[2] != NULL 
            && args[3] != NULL && args[4] != NULL)
        {
            cout << "test: too many arguments" << endl;
            return false;
        }
        //If flag is -e then check if file exists and react accordingly
        else if (args[1] != NULL && strcmp(args[1], "-e") == 0)
        {
            if (args[2] == NULL)
            {
                return true;     
            }
            
            //Act normally
            ynSuccess = (stat(args[2], &buf) == 0);
            return ynSuccess;
        }
        //If command has -f flag then check if file is a regular 
        //file and react accordingly
        else if (args[1] != NULL && strcmp(args[1], "-f") == 0)
        {
            //Catch case where only flag is given
            if(args[2] == NULL)
            {
                return true;     
            }
            
            //Act normally
            ynSuccess = (stat(args[2], &buf) == 0);
            if (ynSuccess)
            {
                if (S_ISREG(buf.st_mode))
                    return true;
            }
            return false;
        }
        //If command has -d flag then check if file is a directory 
        //and react accordingly
        else if (args[1] != NULL && strcmp(args[1], "-d") == 0)
        {
            //Catch case where only flag is given
            if (args[2] == NULL)
            {
                return true;     
            }
            
            //Act normally
            ynSuccess = (stat(args[2], &buf) == 0);
            if(ynSuccess)
            {
                if (S_ISDIR(buf.st_mode))
                    return true;
            }
            return false;
        }
        //If command has no flag then act as if it has a -e flag
        else if (args[2] == NULL)
        {
            //Catch case no arguments for test are given
            if (args[1] == NULL)
            {
                return true;
            }
            
            //Act normally
            ynSuccess = (stat(args[1], &buf) == 0);
            return ynSuccess;
        }
        //catch if too many arguments
        else if (args[1] != NULL && args[1][0] != '-' && args[2] != NULL 
            && args[3] == NULL)
        {
            cout << "test: " << args[1] << ": binary operator expected" << endl;
            return false;
        }
        else if (args[1] != NULL && args[2] != NULL && args[3] != NULL)
        {
            cout << "test: too many arguments" << endl;
            return false;
        }
        //If they gave a bad flag then throw an error and return false
        else
        {
            //Catches case where # follows plain test command
            if(args[1] == NULL)
            {
                return true;
            }
            cout << "test: " << args[1] << ": unary operator expected" << endl;
            return false;
        }
    }
    
    pid_t pid;
    int status;
    
    //Run fork and get parent id
    //If an error while forking occurs then say so and exit
    if ((pid = fork()) < 0) 
    {
        cout << "ERROR: forking child process failed" << endl;
        exit(1);
    }
    else if (pid > 0) 
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
    else 
    {
        //Run the command
        if(execvp(*args, args) < 0)
        {
            perror(NULL);
            ynSuccess = false;
            kill(getpid(), 2);
        }
    }
    
    return ynSuccess;
    
This code is taken from the "bool runCommand(char** args)" function within rshell which takes in a command as a char** and executes it. The function also keeps track of whether the function succeeeded or not for later use with connectors for multi command strings. The function also now supports the running of test commands and [ ] commands.
      
#License
Read LICENSE file for more information.


