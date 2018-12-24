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


//���˵��������ݿ���
void Insert_orders(int tb_id,int order_id, int tb_peo, char* datetime, double total_price)
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
		"INSERT INTO orders (order_id, tb_id,total_price, cust_pay, odd_change,datetime, tb_peo)"
		"    VALUES  "
		"    ('%d','%d','%f',0,0,'%s','%d') "
		,order_id, tb_id,total_price, datetime, tb_peo 
		);

    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if(SQLITE_OK != rc)
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
    }

    sqlite3_close(db);
}




//���˵�ID������̨ID
int Tbid_order(int id)
{
	sqlite3 * db = NULL;
	char *zErrMsg = 0;
	int rc = sqlite3_open("canyin.db", &db);
	if( rc != 0)
	{
		printf("error!\n");
		return -1;
	}
	sqlite3_stmt* stmt = NULL;

	// ��������SQL���, :1��ʾid, :2��ʾname
	char sql[512];
	sprintf(sql,
		"SELECT * FROM orders WHERE ORDER_ID="
		"('%d')"
		,id
		);

	// ��ʼ��SQL Statement����
	rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if(rc != SQLITE_OK)
	{
		printf("failed to prepare: %s \n", sqlite3_errmsg(db));
		return -1;
	}

	// ִ��SQL
	int tb_id = -1;
	while(1)
	{
		rc = sqlite3_step(stmt);
		
		if(rc == SQLITE_ROW)
		{
			tb_id = sqlite3_column_int(stmt, 1);
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

	// ����Statement����
	sqlite3_finalize(stmt);
	return tb_id;
}


//�����˵���Ϣ
void Update_orders(int id, double pay, double change)
{
	sqlite3 * db = NULL;
	char *zErrMsg = 0;
	int rc = sqlite3_open("canyin.db", &db);
	if( rc != 0)
	{
		return;
	}
	
	char sql[512];
	sprintf(sql,"UPDATE orders SET CUST_PAY=%f, ODD_CHANGE=%f WHERE ORDER_ID=%d",pay, change, id);


	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
	if(SQLITE_OK != rc)
	{
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
	}
	sqlite3_close(db);
	return;
}

//�ɶ������ ���� �����۸�
double Select_orders_price(int id)
{
	sqlite3 * db = NULL;
	int rc = sqlite3_open("canyin.db", &db);
	if( rc != 0)
	{
		printf("error!\n");
		return -1;
	}
	sqlite3_stmt* stmt = NULL;

	// ��������SQL���, :1��ʾid, :2��ʾname
	char sql[512];
	sprintf(sql,"SELECT * FROM orders WHERE ORDER_ID="
		"('%d')"
		,id
		);

	// ��ʼ��SQL Statement����
	rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if(rc != SQLITE_OK)
	{
		printf("failed to prepare: %s \n", sqlite3_errmsg(db));
		return -1;
	}

	// ִ��SQL
	double price = -1;
	while(1)
	{
		rc = sqlite3_step(stmt);
		
		if(rc == SQLITE_ROW)
		{
			price = sqlite3_column_double(stmt, 2);
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

	// ����Statement����
	sqlite3_finalize(stmt);
	return price;
}