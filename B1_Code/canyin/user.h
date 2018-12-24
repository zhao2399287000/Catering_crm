#include <stdio.h>
#include <iostream>
#include <windows.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <conio.h>
#include <iomanip>
#include <time.h>
#include <string>
#include <math.h>
/* SQLite3 Support */
#include "sqlite3.h"
#pragma comment(lib, "sqlite3.lib")
using namespace std;



//从数据库中查找所注册的用户名和密码
void select_user()
{
    sqlite3* db;
    char *zErrMsg = 0;
    int rc;
    char *sql;

    rc = sqlite3_open("canyin.db", &db);
    if(rc)
    {
        fprintf(stderr, "Can't open database:%s\n", sqlite3_errmsg(db));
//        exit(0);
        return;
    }

    sql = "select * from  user;";

    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if(SQLITE_OK != rc)
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
    }

    sqlite3_close(db);
}

//判断注册是否合法
void insert_user(char* name, char* password)
{
   sqlite3* db;
   char *zErrMsg = 0;
   int rc;

   rc = sqlite3_open("canyin.db", &db);
   if(rc)
   {
       fprintf(stderr, "Can't open database:%s\n", sqlite3_errmsg(db));
       return;
   }
   char sql[512];
	sprintf(sql, 
		"INSERT INTO user (name, password) "
		"    VALUES  "
		"    ('%s', '%s') "
		, name
		, password
		);

    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if(SQLITE_OK != rc)
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
    }

    sqlite3_close(db);

}




