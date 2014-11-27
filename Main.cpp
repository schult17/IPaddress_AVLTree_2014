#include "DBentry.h"
#include "TreeDB.h"
#include "TreeNode.h"

#include <sstream>
 
int main()
{
    string command, line;
    
    TreeDB maple;
    
    do
    {
        string name, status;
        unsigned int IPaddress = 0;
        
        cout << "> ";
        
        getline(cin, line);
        
        if(cin.eof()){break;}
        
        stringstream inputStream(line);
        
        inputStream >> command;
        
        if(command == "insert")
        {
            bool temp = false;
            
            inputStream >> name >> IPaddress >> status;
            
            if(status == "active")
            {
                temp = true;
            }
            else if(status == "inactive")
            {
                temp = false;
            }
            
            DBentry* newEntry = new DBentry(name, IPaddress, temp);
            
            if(maple.insert(newEntry))
            {
                cout << "Success" << endl;
            }
            else
            {
                cout << "Error: entry already exists" << endl;
            }
        
        }
        else if(command == "find")
        {
            inputStream >> name;
            DBentry* find = maple.find(name);
            
            if(find == NULL)
            {
                cout << "Error: entry does not exist" << endl;
            }
            else
            {
                cout << *find << endl;
            }
            
        }
        else if(command == "remove")
        {
            inputStream >> name;
            
            if(maple.remove(name))
            {
                cout << "Success" << endl;
            }
            else
            {
                cout << "Error: entry does not exist" << endl;
            }
        }
        else if(command == "printall")
        {
            cout << maple;
        }
        else if(command == "printprobes")
        {
            inputStream >> name;
            
            DBentry* find = maple.find(name);
            
            if(find == NULL)
            {
                cout << "Error: entry does not exist" << endl;
            }
            else
            {
                maple.printProbes();
            }
        }
        else if(command == "removeall")
        {
            maple.clear();
            cout << "Success" << endl;
        }
        else if(command == "countactive")
        {
            maple.countActive();
        }
        else if(command == "updatestatus")
        {
            bool activeSet = false;
            
            inputStream >> name >> status;
            
            if(status == "active")
            {
                activeSet = true;
            }
            else if(status == "inactive")
            {
                activeSet = false;
            }
            
            DBentry* find = maple.find(name);
            
            if(find == NULL)
            {
                cout << "Error: entry does not exist" << endl;
            }
            else
            {
                find->setActive(activeSet);
                cout << "Success" << endl;
            }
        }
        else
        {
            //not needed
            cout << "Error: invalid command" << endl;
        }
        
    }while(!cin.eof());
    
    return 0;
}
