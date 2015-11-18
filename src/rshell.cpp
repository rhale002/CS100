#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include "rshell.h"

using namespace std;

//Function which finds all the connectors in a char string and puts
//them in a queue
queue<char> findConnectors(char cmdCharString[])
{
    queue<char> connectorQueue;
    
    //Create a pointer pointing to the first occurance of a connector
    char* connectorPointer = strpbrk(cmdCharString, "|;&#");
    //Create a bool for keeping track of doubles
    bool conDoubCatcher = false;
    bool hashCatcher = false;
    
    //Loop to find all connectors and put them in the queue
    while (connectorPointer != NULL && hashCatcher == false)
    {
        //Store the characters for each connector
        if (!conDoubCatcher)
        {
            //Push connector character into command queue
            if ((*connectorPointer == '&' || *connectorPointer == '|') &&
                (*connectorPointer == *(connectorPointer + 1)))
            {
                connectorQueue.push(*connectorPointer);
                conDoubCatcher = true;
            }
            //Do not store single & or | and throw error
            else if ((*connectorPointer == '&' || *connectorPointer == '|') &&
                (*connectorPointer != *(connectorPointer + 1)))
            {
                cout << "ERROR: Invalid connector: " << *connectorPointer 
                    << endl;
                exit(1);
            }
            else if (*connectorPointer == '#' && *(connectorPointer - 1) == ' ')
            {
                connectorQueue.push(*connectorPointer);
                hashCatcher = true;
            }
            else if (*connectorPointer == ';')
                connectorQueue.push(*connectorPointer);
            
        }
        else
            conDoubCatcher = false;
        //Go to the next occurance of a connector character
        connectorPointer = strpbrk(connectorPointer + 1, "|;&#");
    }
    //return queue with all found connectors
    return connectorQueue;
}

//Read through input until first non whitespace char and if hash then return
//true else return false
bool firstCharHash(string cmdString)
{
    if (cmdString.find_first_not_of(" \t\r\n") != string::npos &&
        cmdString.at(cmdString.find_first_not_of(" \t\r\n")) == '#')
        return true;
    return false;
}

//Finds the commands and stores them in a queue for later use
queue<char*> findCommands(char cmdCharString[])
{
    queue<char*> commandQueue;
    
    //Create pointers for finding commands and connectors
    char* conPointer = strpbrk(cmdCharString, "|;&#");
    char* cmdCharPointer = NULL;
    
    //point at commands based on # placement
    if (conPointer != NULL && *conPointer == '#' && *(conPointer - 1) != ' ')
    {
        cmdCharPointer = strtok(cmdCharString, "|;&");
    }
    else
    {
        cmdCharPointer = strtok(cmdCharString, "|;&#");
    }

    //Go through command cString and find commands
    while (cmdCharPointer != NULL)
    {
        //Get rid of space in begining of command
        while (*cmdCharPointer == ' ')
            cmdCharPointer++;
        
        //Add the command to the queue
        commandQueue.push(cmdCharPointer);
        
        //Add commands based on # placement 
        if (conPointer != NULL)
        {
            conPointer = strpbrk(conPointer + 1, "|;&#");
            
            if (conPointer != NULL)
            {
                if(*conPointer == '#' && *(conPointer - 1) != ' ')
                    cmdCharPointer = strtok(NULL, "|;&");
                else
                    cmdCharPointer = strtok(NULL, "|;&#");
            }
            else
                cmdCharPointer = strtok(NULL, "|;&#");
        }
        else
            cmdCharPointer = strtok(NULL, "|;&#");
    }
    
    return commandQueue;
}

//Checks for starting connector with no previous command
void checkForStartingConnectors(char cmdCharString[])
{
    char* cmdCharPointer = cmdCharString;
    while (*cmdCharPointer == ' ')
            cmdCharPointer++;
            
    if (cmdCharPointer != NULL && (cmdCharPointer + 1) != NULL && 
        ((*cmdCharPointer == '&' && *(cmdCharPointer + 1) == '&') || 
        (*cmdCharPointer == '|' && *(cmdCharPointer + 1) == '|')))
    {
        cout << "ERROR: syntax error near unexpected token \'" 
            << *cmdCharPointer << *cmdCharPointer << "\'" << endl;
        exit(1);
    }
    if (cmdCharPointer != NULL && *cmdCharPointer == ';')
    {
        cout << "ERROR: syntax error near unexpected token \'" 
            << *cmdCharPointer << "\'" << endl;
        exit(1);
    }
}

//Creates a queue with the seperate arguments for a command
queue<char*> seperateCommand(char command[])
{
    queue<char*> sepComQueue;
    
    char* cmdCharPointer = strtok(command, " ");
    while (cmdCharPointer != NULL)
    {
        sepComQueue.push(cmdCharPointer);
        cmdCharPointer = strtok(NULL, " ");
    }
    
    return sepComQueue;
}

//Fills the 2D array with all arguments for running the command
void fillArgsArray(char** args, queue<char*> sepComQueue)
{
    unsigned i;
    for (i = 0; !sepComQueue.empty(); i++)
    {
        args[i] = sepComQueue.front();
        sepComQueue.pop();
    }
    args[i] = NULL;
}

//Runs the command and returns true if success else return false
bool runCommand(char** args)
{
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
}

//Function to run the shell
void rshell()
{
    while(true)
    {
        //Output Command prompt
        cout << "$ ";
        
        //Take in command and store it in a c-string
        string cmdString;
        getline(cin, cmdString);
        char* cmdCharString = new char[cmdString.size() + 1];
        strcpy(cmdCharString, cmdString.c_str());
        
        //For making testing with files better looking
        cout << endl;
        
        //Check for bad starting connectors
        checkForStartingConnectors(cmdCharString);
        
        //Catches specific case for Connector followed by # with no command
        //in between
        char* findHash = strpbrk(cmdCharString, "#");
        if (findHash != NULL && findHash != cmdCharString)
        {
            findHash--;
            while (*findHash == ' ' && findHash != cmdCharString)
                findHash--;
            if (*findHash == '&' || *findHash == '|')
            {
                cout << "ERROR: Command string ends in " << *findHash 
                    << *findHash << " and has no following command" << endl;
                exit(1);
            }
        }
        
        //Check for two connectors with no command inbetween
        char* findDoubleConnectors = strpbrk(cmdCharString, ";&|");
        while (findDoubleConnectors != NULL 
            && findDoubleConnectors != cmdCharString)
        {
            bool skipChecking = false;
            char* temp = findDoubleConnectors;
            if(*temp == ';')
                temp--;
            else if((*temp == '|' || *temp == '&') && (*(temp - 1) == *temp))
                temp = temp - 2;
            else if((*temp == '|' || *temp == '&') && (*(temp - 1) != *temp))
                skipChecking = true;
                
            while (*temp == ' ' && temp != cmdCharString && !skipChecking)
                temp--;
            if ((*temp == '&' || *temp == '|') && !skipChecking)
            {
                cout << "Syntax error near unexpected token \'" << *temp 
                    << *temp << "\'" << endl;
                exit(1);
            }
            else if(*temp == ';' && !skipChecking)
            {
                cout << "Syntax error near unexpected token \'" << *temp << "\'" 
                    << endl;
                exit(1);
            }
            findDoubleConnectors = strpbrk(findDoubleConnectors + 1, ";&|");
        }
        
        //Create a queue filled with connectors in order using findConnectors()
        queue<char> connectorCharQueue = findConnectors(cmdCharString);
            
        //Create a queue filled with commands in order using findCommands()
        queue<char*> commandQueue = findCommands(cmdCharString);
        
        //Makes sure the string doesn't end in a '&&' or '||' connector
        if (commandQueue.size() <= connectorCharQueue.size() 
            && (connectorCharQueue.back() == '|' 
            || connectorCharQueue.back() == '&'))
        {
            cout << "ERROR: Command string ends in " 
                << connectorCharQueue.back() << connectorCharQueue.back() 
                << " and has no following command" << endl;
            exit(1);
        }
        
        //Create a queue of connector* based on the connectorCharQueue
        queue<connector*> connectorQueue;
        while (!connectorCharQueue.empty() && connectorCharQueue.front() != '#')
        {
            if (connectorCharQueue.front() == '&')
            {
                andConnector* p = new andConnector();
                connectorQueue.push(p);
            }
            else if (connectorCharQueue.front() == '|')
            {
                orConnector* p = new orConnector();
                connectorQueue.push(p);
            }
            else
            {
                semiColonConnector* p = new semiColonConnector();
                connectorQueue.push(p);
            }
            connectorCharQueue.pop();
        }
        
        //Create bool to store whether command execution was a success
        bool ynSuccess = true;
        
        //Create a bool for checking if the first non space character is a hash
        bool firstHash = firstCharHash(cmdString);
        
        //Run commands until we run out of commands to call
        //Don't run if first char is a hash
        while (!commandQueue.empty() && !firstHash)
        {
            //Creates a queue with the seperate arguments for a command
            queue<char*> sepComQueue = seperateCommand(commandQueue.front());
            
            //Take one out of the queue of commands which need to be run
            commandQueue.pop();
            
            //Create a 2D array and store all arguments for command
            unsigned argsSize = sepComQueue.size() + 1;
            char** args = new char*[argsSize];
            fillArgsArray(args, sepComQueue);
            
            //If command is exit then exit
            if(strcmp(*args, "exit") == 0)
                exit(0);
            
            //Run the command and store whether it was a success
            ynSuccess = runCommand(args);
            
            //Handles connectors
            if (!connectorQueue.empty())
            {
                while (!connectorQueue.empty() && !commandQueue.empty() &&
                    !(connectorQueue.front()->isGoodOrNot(ynSuccess)))
                {
                    commandQueue.pop();
                    connector* p = connectorQueue.front();
                    delete p;
                    connectorQueue.pop();
                }
                
                connector* p = connectorQueue.front();
                delete p;
                connectorQueue.pop();
                
                //Special case to check for semi colon followed by # with
                //no command in between and at the end of command string
                if (connectorQueue.empty() && connectorCharQueue.front() == '#')
                {
                    char* sCHashCatcherString = new char[cmdString.size() + 1];
                    strcpy(sCHashCatcherString, commandQueue.front());
                    char* semiColonHashCatcher 
                        = strtok(sCHashCatcherString, " ");
                    if (semiColonHashCatcher == NULL)
                    {
                        delete[] sCHashCatcherString;
                        exit(0);
                    }
                    delete[] sCHashCatcherString;
                }
            }
            else if (!connectorCharQueue.empty())
            {
                if (connectorCharQueue.front() == '#')
                    exit(0); 
            }
            
            delete[] args;
        }
        delete[] cmdCharString;
    }
}