//
//  Database.cpp
//  Test
//
//  Created by Abhishek Aryan on 07/05/17.
//
//

#include "Database.hpp"


USING_NS_CC;

Database* Database::singleton = NULL;

Database::Database()
{
    database = NULL;
}

Database* Database::getInstance()
{
    if (singleton == NULL)
        singleton = new Database();
    return singleton;
}

sqlite3* Database::getDatabase()
{
    return Database::getInstance()->database;
}

bool Database::open()
{
    std::string filePath = CCFileUtils::sharedFileUtils()->getWritablePath() + "db.sqlite3";
    if (sqlite3_open(filePath.c_str(), &Database::getInstance()->database) != SQLITE_OK)
    {
        sqlite3_close(Database::getInstance()->database);
        CCLOG("Failed to open database: %s", filePath.c_str());
        return false;
    }
    
    return true;
}

void Database::close()
{
    sqlite3_close(Database::getInstance()->database);
}

bool Database::execute(CCString *aSql)
{
    char *errorMsg;
    
    if (sqlite3_exec(Database::getInstance()->database, aSql->getCString(), NULL, NULL, &errorMsg) != SQLITE_OK)
    {
        CCString *status = CCString::createWithFormat("Error executing SQL statement: %s", errorMsg);
        CCLOG("%s", status->getCString());
        return false;
    }
    
    return true;
}



//sqlite3 *pdb=NULL;
//std::string path=FileUtils::getInstance()->fullPathForFilename("activeschool.db3");
//
//std::string sql;
//int result;
//result=sqlite3_open(path.c_str(),&pdb);
//if(result!=SQLITE_OK)
//CCLOG("open database failed,  number%d",result);
//
//
//
////#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
//std::string dbPath  = FileUtils::getInstance()->getWritablePath();
//dbPath  += "/save.db3";
//
//FILE* file = fopen(dbPath.c_str(), "r");
//if (file == nullptr)
//{
//    ssize_t size;
//    const char* data = (char*) FileUtils::getInstance()->getFileData("dict.db", "rb", &size);
//    file = fopen(dbPath.c_str(), "wb");
//    fwrite(data, size, 1, file);
//    CC_SAFE_DELETE_ARRAY(data);
//}
//fclose(file);
////#endif
//
//
//
//
//std::string filePath = CCFileUtils::sharedFileUtils()->getWritablePath() + "db.sqlite3";
//if (sqlite3_open(filePath.c_str(), &Database::getInstance()->database) != SQLITE_OK)
//{
//    sqlite3_close(Database::getInstance()->database);
//    CCLOG("Failed to open database: %s", filePath.c_str());
//    return false;
//}
