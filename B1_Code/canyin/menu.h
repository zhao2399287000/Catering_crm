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
int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
    int i = 0;
    for(i = 0; i < argc; i++)
    {
        printf("%s = %s\n",azColName[i], argv[i]?argv[i]:"NULL");
    }

    printf("\n");
    return 0;
}
//将添加时输入的数据存入到数据库中
void Insert_menu(char* name, float price)
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
		"INSERT INTO menu (fd_name, fd_price) "
		"    VALUES  "
		"    ('%s', '%f') "
		,name, price
		);

    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if(SQLITE_OK != rc)
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
    }

    sqlite3_close(db);

}
//从菜单中查找出对应菜名的菜价
double Select_menu(char *name)
{
	sqlite3 * db = NULL;
	int rc = sqlite3_open("canyin.db", &db);
	if( rc != 0)
	{
		printf("error!\n");
		return -1;
	}
	sqlite3_stmt* stmt = NULL;

	// 带参数的SQL语句, :1表示id, :2表示name
	char sql[512];
	sprintf(sql,
		"SELECT * FROM menu WHERE FD_NAME="
		"('%s')"
		,name
		);

	// 初始化SQL Statement对象
	rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if(rc != SQLITE_OK)
	{
		printf("failed to prepare: %s \n", sqlite3_errmsg(db));
		return -1;
	}
	
	double price = -1;
	// 执行SQL
	while(1)
	{
		rc = sqlite3_step(stmt);
		
		if(rc == SQLITE_ROW)
		{
			price = sqlite3_column_double(stmt, 1);
			
			sqlite3_finalize(stmt);
			return price;
		}
		else if(rc == SQLITE_DONE)
		{
			break;
		}
		else
		{
			printf("error: %s \n", sqlite3_errmsg(db));
			break;
		}		

	}

	// 销毁Statement对象
	sqlite3_finalize(stmt);
	return -1;
}
//删除菜单
void Delete_menu_table(char *name)
{
    sqlite3* db;
    char *zErrMsg = 0;
    int rc;
    char sql[512];

    rc = sqlite3_open("canyin.db", &db);
    if(rc)
    {
        fprintf(stderr, "Can't open database:%s\n", sqlite3_errmsg(db));
        return;
    }

    sprintf(sql,"DELETE FROM menu WHERE FD_NAME='%s'",name);

    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if(SQLITE_OK != rc)
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
    }

    sqlite3_close(db);
}