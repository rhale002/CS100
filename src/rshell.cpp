#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>
#include <cctype>
#include <stack>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include "rshell.h"

using namespace std;

//Function which finds all the connectors in a char string and puts
//them in a queue
queue<char> findConnectors(char cmdCharString[], bool &b)
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
                b = false;
                return connectorQueue;
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
bool checkForStartingConnectors(char cmdCharString[])
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
        return false;
    }
    if (cmdCharPointer != NULL && *cmdCharPointer == ';')
    {
        cout << "ERROR: syntax error near unexpected token \'" 
            << *cmdCharPointer << "\'" << endl;
        return false;
    }
    return true;
}

//Catches specific case for Connector followed by # with no command
//in between
bool checkForConnectorHash(char cmdCharString[])
{
    char* findHash = strpbrk(cmdCharString, "#");
    if (findHash != NULL && findHash != cmdCharString)
    {
        findHash--;
        while (*findHash == ' ' && findHash != cmdCharString)
            findHash--;
        if (*findHash == '&' || *findHash == '|')
        {
            cout << "ERROR: Command string ends in " << *findHash << *findHash
                << " and has no following command" << endl;
            return false;
        }
    }
    return true;
}

//Check for two connectors with no command inbetween
bool checkForTwoConnectorsNoCmd(char cmdCharString[])
{
    char* findDoubleConnectors = strpbrk(cmdCharString, ";&|");
    while (findDoubleConnectors != NULL && 
        findDoubleConnectors != cmdCharString)
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
            cout << "Syntax error near unexpected token \'" << *temp << *temp 
                << "\'" << endl;
            return false;
        }
        else if(*temp == ';' && !skipChecking)
        {
            cout << "Syntax error near unexpected token \'" << *temp << "\'" 
                << endl;
            return false;
        }
        findDoubleConnectors = strpbrk(findDoubleConnectors + 1, ";&|");
    }
    return true;
}

//Catches case in which empty command string is input
bool checkForEmptyString(char cmdCharString[], const string cmdString)
{
    char* emptyStringCatcherString = new char[cmdString.size() + 1];
    strcpy(emptyStringCatcherString, cmdCharString);
    char* emptyStringCatcher = strtok(emptyStringCatcherString, " ");
    if(emptyStringCatcher == NULL)
    {
        delete[] emptyStringCatcherString;
        return false;
    }
    delete[] emptyStringCatcherString;
    
    return true;
}

//Check for Semicolon followed by a hash with nothing inbetween
void checkForSemiHashNoSpace(char cmdCharString[],
    queue<char> &connectorCharQueue)
{
    bool foundIt = false;
    char* semiHash = strpbrk(cmdCharString, ";");
    while(semiHash != NULL && foundIt == false)
    {
        if((semiHash + 1) != NULL && *(semiHash + 1) == '#')
        {
            connectorCharQueue.push('#');
            foundIt = true;
        }
        else
            semiHash = strpbrk(semiHash + 1, ";");
    }
}

//Checks for matching ( and )
bool checkForMatchingParen(char cmdCharString[])
{
    char* findParen = strpbrk(cmdCharString, "#()");
    unsigned leftParen = 0;
    unsigned rightParen = 0;
    
    while (findParen != NULL && *findParen != '#')
    {
        if (*findParen == '(')
            leftParen++;
        else if (*findParen == ')')
            rightParen++;
        findParen = strpbrk(findParen + 1, "#()");
    }
    if (leftParen != rightParen)
    {
        cout << "ERROR: Number of \'(\' does not equal number of \')\'" << endl;
        return false;
    }
    return true;
}

//Checks for ending ) not followed by connector or another )
bool checkForEndingParenFollowedByConnector(char cmdCharString[])
{
    char* check = strpbrk(cmdCharString, "#)");
    
    while (check != NULL && *check != '#')
    {
        char* temp = check + 1;
        
        while (temp != NULL && isspace(*temp))
            temp++;
        
        if(temp != NULL && *temp != '&' && *temp != ')' && *temp != ';' 
            && *temp != '|' && *temp != '#' && isspace(*temp))
        {
            cout << "syntax error near unexpected token \')\'" << endl;
            return false;
        }
        check = strpbrk(check + 1, "#)");
    }
    return true;
}

//Checks for ( that does not have a connector or ( behind it
bool checkForBeginingParen(char cmdCharString[])
{
    char* check = cmdCharString;
    
    while (check != NULL && *check == ' ')
        check++;
    check++;
    
    check = strpbrk(check, "(");
    
    while (check != NULL)
    {
        char* temp = check - 1;
        
        while (*temp == ' ' || *temp == '\t' || *temp == '\n' 
            || *temp == '\v' || *temp == '\f' || *temp == '\r')
            temp--;
            
        if (*temp != '&' && *temp != '|' && *temp != ';' && *temp != '#' 
            && *temp != '(')
        {
            cout << "syntax error near unexpected token \'(\'" << endl;
            return false;
        }
        check = strpbrk(check + 1, "(");
    }
    return true;
}

//Checks for empty parentheses, and parentheses which end in a connector
bool checkForEmptyParen(char cmdCharString[])
{
    char* check = strpbrk(cmdCharString, "#)");
    
    while (check != NULL && *check != '#')
    {
        char* temp = check;
        temp--;
        while (isspace(*temp))
            temp--;
        
        if (*temp == '&' || *temp == '|' || *temp == ';' || *temp == '(')
        {
            cout << "syntax error near unexpected token \')\'" << endl;
            return false;
        }
        check = strpbrk(check + 1, ")");
    }
    
    return true;
}

//Creates a queue with the seperate arguments for a command
queue<char*> seperateCommand(char command[], bool &keepGoing)
{
    queue<char*> sepComQueue;
    
    //Check for [ ] symbolic test command
    char* findBracket = command;
    while(findBracket != NULL && isspace(*findBracket))
        findBracket++;
    if(findBracket != NULL && *findBracket == '[')
    {
        findBracket++;
        if(findBracket == NULL || *findBracket != ' ')
        {
            findBracket--;
            //If [ not followed by space then error
            char* errorOutput = strtok(findBracket, " ");
            cout << errorOutput << ": command not found" << endl;
            keepGoing = true;
        }
        else
        {
            findBracket--;
            //replace the begining bracket with a space
            *findBracket = ' ';
            
            //Push the word "test" onto the queue for later use as the test command
            char* test = new char[5];
            strcpy(test, "test");
            sepComQueue.push(test);
            
            //Check for end bracket
            findBracket = strpbrk(command, "#]");
            if(findBracket != NULL && *findBracket == ']')
            {
                findBracket--;
                if(*findBracket != ' ')
                {
                    //Else throw and error and exit
                    cout << "[: missing \']\' " << endl;
                    keepGoing = true;
                }
                else
                {
                    findBracket++;
                    //If end bracket exists then replace with space
                    *findBracket = ' ';
                }
            }
            else
            {
                //Else throw and error and exit
                cout << "[: missing \']\' " << endl;
                keepGoing = true;
            }
        }
    }
    
    //Seperate the commands and push them into the queue
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
        
        //Check for various cases where command shouldn't be run
        if (!checkForStartingConnectors(cmdCharString) 
            || !checkForConnectorHash(cmdCharString) 
            || !checkForTwoConnectorsNoCmd(cmdCharString)
            || !checkForEmptyString(cmdCharString, cmdString)
            || !checkForMatchingParen(cmdCharString)
            || !checkForEndingParenFollowedByConnector(cmdCharString)
            || !checkForBeginingParen(cmdCharString)
            || !checkForEmptyParen(cmdCharString));
        else
        {
            bool b = true;
            
            //Create a queue filled with connectors in order
            //using findConnectors()
            queue<char> connectorCharQueue = findConnectors(cmdCharString, b);
            
            if (b)
            {
                //Check for Semicolon followed by a hash with nothing inbetween
                checkForSemiHashNoSpace(cmdCharString, connectorCharQueue);
                
                //Create a queue filled with commands in order using
                //findCommands()
                queue<char*> commandQueue = findCommands(cmdCharString);
                
                //Makes sure the string doesn't end in a '&&' or '||' connector
                if (commandQueue.size() <= connectorCharQueue.size() 
                    && (connectorCharQueue.back() == '|' 
                    || connectorCharQueue.back() == '&'))
                {
                    cout << "ERROR: Command string ends in " 
                        << connectorCharQueue.back() 
                        << connectorCharQueue.back() 
                        << " and has no following command" << endl; 
                }
                else
                {
                    //Create a queue of connector* based on the
                    //connectorCharQueue
                    queue<connector*> connectorQueue;
                    
                    //Connectors to point at
                    semiColonConnector semiConnectorobject;
                    andConnector andConnectorObject;
                    orConnector orConnectorObject;
                    
                    //fill the queue
                    while (!connectorCharQueue.empty() 
                        && connectorCharQueue.front() != '#')
                    {
                        if (connectorCharQueue.front() == '&')
                        {
                            connectorQueue.push(&andConnectorObject);
                        }
                        else if (connectorCharQueue.front() == '|')
                        {
                            connectorQueue.push(&orConnectorObject);
                        }
                        else
                        {
                            connectorQueue.push(&semiConnectorobject);
                        }
                        connectorCharQueue.pop();
                    }
                    
                    //Create bool to store whether command execution was
                    //a success
                    bool ynSuccess = true;
                    
                    //Create a bool for checking if the first non space 
                    //character is a hash
                    bool keepGoing = firstCharHash(cmdString);
                    
                    //Stack of bools for keeping track of parentheses
                    stack<bool> parenStack;
                    
                    //Run commands until we run out of commands to call
                    //Don't run if first char is a hash
                    while (!commandQueue.empty() && !keepGoing)
                    {
                        //Handle Parentheses skipping/recording
                        char* parenFinder = strpbrk(commandQueue.front(), "(");
                        while (parenFinder != NULL && *parenFinder == '(')
                        {
                            parenStack.push(true);
                            *parenFinder = ' ';
                            parenFinder = strpbrk(parenFinder + 1, "(");
                        }
                        parenFinder = strpbrk(commandQueue.front(), ")");
                        while (parenFinder != NULL && *parenFinder == ')')
                        {
                            parenStack.pop();
                            *parenFinder = ' ';
                            parenFinder = strpbrk(parenFinder + 1, ")");
                        }
                        
                        //handle parentheses block skipping
                        if (!parenStack.empty() && !ynSuccess 
                            && !connectorQueue.empty() 
                            && !commandQueue.empty() 
                            && !(connectorQueue.front()
                                ->isGoodOrNot(ynSuccess)))
                        {
                            commandQueue.pop();
                            
                            //Handles connectors
                            if (!connectorQueue.empty())
                            {
                                while (!connectorQueue.empty() 
                                    && !commandQueue.empty() 
                                    && !(connectorQueue.front()
                                        ->isGoodOrNot(ynSuccess)))
                                {
                                    parenFinder 
                                        = strpbrk(commandQueue.front(), "(");
                                    while (parenFinder != NULL 
                                        && *parenFinder == '(')
                                    {
                                        parenStack.push(true);
                                        *parenFinder = ' ';
                                        parenFinder 
                                            = strpbrk(parenFinder + 1, "(");
                                    }
                                    parenFinder 
                                        = strpbrk(commandQueue.front(), ")");
                                    while (parenFinder != NULL 
                                        && *parenFinder == ')')
                                    {
                                        parenStack.pop();
                                        *parenFinder = ' ';
                                        parenFinder 
                                            = strpbrk(parenFinder + 1, ")");
                                    }
                                    
                                    commandQueue.pop();
                                    connectorQueue.pop();
                                }
                                connectorQueue.pop();
                                
                                //Special case to check for semi colon followed
                                //by # with no command in between and at the
                                //end of command string
                                if (connectorQueue.empty() 
                                    && connectorCharQueue.front() == '#')
                                {
                                    char* sCHashCatcherString 
                                        = new char[cmdString.size() + 1];
                                    strcpy(sCHashCatcherString,
                                        commandQueue.front());
                                    char* semiColonHashCatcher 
                                        = strtok(sCHashCatcherString, " ");
                                    if (semiColonHashCatcher == NULL 
                                        || *semiColonHashCatcher == '#')
                                    {
                                        delete[] sCHashCatcherString;
                                        keepGoing = true;
                                    }
                                    else
                                    {
                                        delete[] sCHashCatcherString;
                                    }
                                }
                            }
                            else if (!connectorCharQueue.empty())
                            {
                                if (connectorCharQueue.front() == '#')
                                    keepGoing = true;
                            }
                        }
                        //Do commands normally
                        else
                        {
                            //Creates a queue with the seperate arguments for
                            //a command
                            queue<char*> sepComQueue 
                                = seperateCommand(commandQueue.front()
                                    , keepGoing);
                            
                            if (!keepGoing)
                            {
                                //Take one out of the queue of commands which
                                //need to be run
                                commandQueue.pop();
                                
                                //Create a 2D array and store all arguments for 
                                //command
                                unsigned argsSize = sepComQueue.size() + 1;
                                char** args = new char*[argsSize];
                                fillArgsArray(args, sepComQueue);
                                
                                //If command is exit then exit
                                if (strcmp(*args, "exit") == 0)
                                {
                                    delete[] cmdCharString;
                                    delete[] args;
                                    
                                    kill(-getppid(), 2);
                                    return;
                                }
                                
                                //Run the command and store whether it was a
                                //success
                                ynSuccess = runCommand(args);
                                
                                //Handles connectors
                                if (!connectorQueue.empty())
                                {
                                    while (!connectorQueue.empty() 
                                        && !commandQueue.empty() 
                                        && !(connectorQueue.front()
                                            ->isGoodOrNot(ynSuccess)))
                                    {
                                        //Handle Parentheses skipping/recording
                                        parenFinder 
                                            = strpbrk(commandQueue.front()
                                                , "(");
                                        while (parenFinder != NULL 
                                            && *parenFinder == '(')
                                        {
                                            parenStack.push(true);
                                            *parenFinder = ' ';
                                            parenFinder 
                                                = strpbrk(parenFinder + 1, "(");
                                        }
                                        parenFinder 
                                            = strpbrk(commandQueue.front()
                                                , ")");
                                        while (parenFinder != NULL 
                                            && *parenFinder == ')')
                                        {
                                            parenStack.pop();
                                            *parenFinder = ' ';
                                            parenFinder 
                                                = strpbrk(parenFinder + 1, ")");
                                        }
                                        
                                        commandQueue.pop();
                                        connectorQueue.pop();
                                    }
                                    connectorQueue.pop();
                                    
                                    //Special case to check for semi colon 
                                    //followed by # with no command in between
                                    //and at the end of command string
                                    if (connectorQueue.empty() 
                                        && connectorCharQueue.front() == '#')
                                    {
                                        char* sCHashCatcherString 
                                            = new char[cmdString.size() + 1];
                                        strcpy(sCHashCatcherString,
                                            commandQueue.front());
                                        char* semiColonHashCatcher 
                                            = strtok(sCHashCatcherString, " ");
                                        if (semiColonHashCatcher == NULL 
                                            || *semiColonHashCatcher == '#')
                                        {
                                            delete[] sCHashCatcherString;
                                            keepGoing = true;
                                        }
                                        else
                                        {
                                            delete[] sCHashCatcherString;
                                        }
                                    }
                                }
                                else if (!connectorCharQueue.empty())
                                {
                                    if (connectorCharQueue.front() == '#')
                                        keepGoing = true;
                                }
                                delete[] args;
                            }
                        }
                    }
                }
            }
        }
        delete[] cmdCharString;
    }
}