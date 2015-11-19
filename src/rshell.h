#ifndef __RSHELL_H__ 
#define __RSHELL_H__

#include<string>
#include<queue>

using namespace std;

//Virtual class for connectors
class connector
{
    protected:
        //Store whether or not the last command was successful
        bool ynSuccess;
        
    public:
        connector(bool ynSuccess)
        :ynSuccess(ynSuccess)
        {}
        
        virtual ~connector()
        {}
    
        virtual bool isGoodOrNot(bool ynSuccess) = 0;
};

//Class which inherits from connector made for &&
class andConnector : public connector
{
    public:
        andConnector()
        : connector(true)
        {}
    
        andConnector(bool ynSuccess)
        : connector(ynSuccess)
        {}
        
        virtual ~andConnector()
        {}
        
        //If last command was successful then return true else return false
        virtual bool isGoodOrNot(bool ynSuccess)
        {
            this->ynSuccess = ynSuccess;
            return this->ynSuccess;
        }
};

//Class which inherits from connector made for ||
class orConnector : public connector
{
    public:
        orConnector()
        : connector(true)
        {}
        
        orConnector(bool ynSuccess)
        : connector(ynSuccess)
        {}
        
        virtual ~orConnector()
        {}
        
        //If last command was successful then return false else return true
        virtual bool isGoodOrNot(bool ynSuccess)
        {
            this->ynSuccess = !ynSuccess;
            return this->ynSuccess;
        }
};

//Class which inherits from connector made for ;
class semiColonConnector : public connector
{
    public:
        semiColonConnector()
        : connector(true)
        {}
        
        semiColonConnector(bool ynSuccess)
        : connector(ynSuccess)
        {}
        
        virtual ~semiColonConnector()
        {}
        
        //Always return true;
        virtual bool isGoodOrNot(bool ynSuccess)
        {
            this->ynSuccess = true;
            return this->ynSuccess;
        }
};

//Function to run the shell
void rshell();

#endif