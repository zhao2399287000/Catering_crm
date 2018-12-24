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
//更新账单，桌子的状态变为占用
void Update_tables(int id, int flag)
{
	sqlite3 * db = NULL;
	char *zErrMsg = 0;
	int rc = sqlite3_open("canyin.db", &db);
	if( rc != 0)
	{
		printf("error!\n");
		return;
	}
	
	char sql[512];
	if(flag == 1)
	{
		sprintf(sql,
			"UPDATE TABLES SET OPEN=1 WHERE ID="
			"('%d')"
			,id			
			);
	}
	else
	{
		sprintf(sql,
			"UPDATE TABLES SET OPEN=0 WHERE ID="
			"('%d')"
			,id			
			);
	}
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
	if(SQLITE_OK != rc)
	{
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
	}
	sqlite3_close(db);
	return;
}
//将桌台信息插入数据库
void Insert_tables(int id, int tb_peo)		//添加tb_peo之后的插入
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
		"INSERT INTO tables (id, open,tb_peo) "
		"    VALUES  "
		"    ('%d',0, '%d') "
		, id, tb_peo
		);

    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if(SQLITE_OK != rc)
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
    }

    sqlite3_close(db);

}
//由桌台id返回桌台可容纳人数 用于检验就餐人数
int Tb_peo(int tb_id)
{
	sqlite3 * db = NULL;
	int rc = sqlite3_open("canyin.db", &db);
	if( rc != 0)
	{
		printf("error!\n");
		return -1;
	}
	sqlite3_stmt* stmt = NULL;

	char sql[512];
	sprintf(sql,"SELECT * FROM tables where id=%d",tb_id);

	rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if(rc != SQLITE_OK)
	{
		printf("failed to prepare: %s \n", sqlite3_errmsg(db));
		return -1;
	}

	int flag = -1;
	while(1)
	{
		rc = sqlite3_step(stmt);
		
		if(rc == SQLITE_ROW)
		{
			flag = sqlite3_column_int(stmt, 2);
		}
		else if(rc == SQLITE_DONE)
			break;
		else
		{
			printf("error: %s \n", sqlite3_errmsg(db));
			break;
		}		

	}

	sqlite3_finalize(stmt);
	return flag;
}

//删除桌子
void Delete_tables(int id)
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

    sprintf(sql,"DELETE FROM tables WHERE ID=%d",id);

    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if(SQLITE_OK != rc)
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
    }

    sqlite3_close(db);
}

//检验桌子是否存在
bool Is_tables(int id)
{
	sqlite3 * db = NULL;
	int rc = sqlite3_open("canyin.db", &db);
	if( rc != 0)
	{
		printf("error!\n");
		return false;
	}
	sqlite3_stmt* stmt = NULL;

	char sql[512];
	sprintf(sql,"SELECT * FROM tables WHERE id=%d",id);

	rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if(rc != SQLITE_OK)
	{
		printf("failed to prepare: %s \n", sqlite3_errmsg(db));
		return false;
	}

	bool flag = false;
	while(1)
	{
		rc = sqlite3_step(stmt);
		
		if(rc == SQLITE_ROW)
			flag = true;
		else if(rc == SQLITE_DONE)
			break;
		else
		{
			printf("error: %s \n", sqlite3_errmsg(db));
			break;
		}		
	}

	sqlite3_finalize(stmt);
	return flag;
}