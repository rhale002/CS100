#ifndef __RSHELL_H__ 
#define __RSHELL_H__

#include<string>
#include<queue>

using namespace std;

//Virtual class for connectors
class connector
{
    public:
        virtual bool isGoodOrNot(bool ynSuccess) = 0;
};

//Class which inherits from connector made for &&
class andConnector : public connector
{
    public:
        //If last command was successful then return true else return false
        virtual bool isGoodOrNot(bool ynSuccess)
        {
            return ynSuccess;
        }
};

//Class which inherits from connector made for ||
class orConnector : public connector
{
    public:
        //If last command was successful then return false else return true
        virtual bool isGoodOrNot(bool ynSuccess)
        {
            return !ynSuccess;
        }
};

//Class which inherits from connector made for ;
class semiColonConnector : public connector
{
    public:
        //Always return true;
        virtual bool isGoodOrNot(bool ynSuccess)
        {
            return true;
        }
};

//Function to run the shell
void rshell();

#endif