//
//  Database.hpp
//  Test
//
//  Created by Abhishek Aryan on 07/05/17.
//
//

#ifndef Database_hpp
#define Database_hpp

#include "cocos2d.h"
#include <stdio.h>
#include "sqlite3.h"

class Database
{
private:
    Database();
    static Database *singleton;
    
    sqlite3 *database;
    
    static Database* getInstance();
    
public:
    static sqlite3* getDatabase();
    
    static bool open();
    static bool create(std::string aTableName);
    static void close();
    
    static bool execute(cocos2d::CCString *aSql);
};



#endif /* Database_hpp */
