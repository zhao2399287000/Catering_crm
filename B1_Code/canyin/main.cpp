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
#include "menu.h"
#include "orders.h"
#include "tables.h"
#include "user.h"

/* SQLite3 Support */
#include "sqlite3.h"
#pragma comment(lib, "sqlite3.lib")
using namespace std;


//������ʼ�����ݿ�
void creat_table();
//��궨λ����
void gotoxy(int,int);
//��ʼ��ӭ���棺ע�ᡢ��½���˳�
void Start();  
//ע�����
void Register();
//��½����
void Login();
//����û����������Ƿ�ƥ��
void chack_mima(char *, char *);
//��½�ɹ���ӭ����
void Welcome();
//��ʾ�˵�
void Select_menu();
//��Ӳ�Ʒ�����ƺͼ۸�
void Add_menu();
//ɾ����Ʒ�����ƺͼ۸�
void Delete_menu();
//���˽���
void Jiezhang();
//��ʾ��̨��Ϣ
void Select_tables();
//��̨������ͨ��������������ռ�õ����ӼӲ�
//Ҳ���Ը��������ӵ�ˣ������Բ鿴δ����ͽ���
void Kaitai();
//��ʾ�����ʾ����
void Diancai();
//��ʾδ������˵�
void Select_orders_nopay();
//��ʾ������ӵĴ���
void Tables_jia();
//��ѯ�����ҳ��
void Select_price();
//ɾ�����ӽ���
void Delete_tables_num();
//�鿴�ܶ���
void Select_allorders();
//�鿴ĳһ������ѽ��
void Select_orders_day(char *);
//�鿴ĳһ�µ����ѽ��
void Select_orders_mouth(char *);
//��ʾ��������Ա��Ϣ
void Personnel();
//��Ӳ�������Ա��Ϣ
void AppendPersonnel();
//�޸Ĳ�������Ա��Ϣ
void RevisePersonnel();
//ɾ����������Ա��Ϣ
void DeletePersonnel();
int main()
{
	creat_table();
	Start();
	system("pause");
	return 0;
}


void creat_table()
{
    sqlite3* db;
    char *zErrMsg = 0;
    int rc;
    char *sql;

    rc = sqlite3_open("canyin.db", &db);  // �����ݿ�
    if(rc)
    {
        fprintf(stderr, "Can't open database:%s\n", sqlite3_errmsg(db));
        return;
    }

    sql = "create table user(NAME TEXT NOT NULL, PASSWORD TEXT NOT NULL)";

    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg); // ִ������sql�е�����
    if(SQLITE_OK != rc)
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
    }

	sql = "create table orders(ORDER_ID INT PRIMARY KEY NOT NULL, \
		  TB_ID INT NOT NULL, \
		  TOTAL_PRICE REAL, \
		  CUST_PAY REAL, \
		  ODD_CHANGE REAL, \
		  DATETIME TEXT, \
		  TB_PEO INT\
		  )";

    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg); // ִ������sql�е�����
    if(SQLITE_OK != rc)
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
    }

	sql = "create table tables(ID INT NOT NULL, \
		  OPEN INT, \
		  TB_PEO INT\
		  )";

    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg); // ִ������sql�е�����
    if(SQLITE_OK != rc)
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
    }

	sql = "create table ORDER_MENU(ID INT NOT NULL, \
		  FD_NAME TEXT\
		  )";

    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg); // ִ������sql�е�����
    if(SQLITE_OK != rc)
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
    }

	sql = "create table MENU(\
		  FD_NAME TEXT, \
		  FD_PRICE REAL, \
		  ID INT\
		  )";

    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg); // ִ������sql�е�����
    if(SQLITE_OK != rc)
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
    }

    sqlite3_close(db);
}


void gotoxy(int x,int y)
{
    COORD c;
    c.X = x - 1;
    c.Y = y - 1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
 }
void Start()                                                                            //��ӭ���棬ע��͵�¼
{
    system("cls");
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << setw(110) << "�q�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�r" << endl;
    cout << setw(110) << "�U                                    �U" << endl;
    cout << setw(110) << "�U                                    �U" << endl;
    cout << setw(110) << "�U            ע���˺�(1)��           �U" << endl;
    cout << setw(110) << "�U                                    �U" << endl;
    cout << setw(110) << "�U                                    �U" << endl;
    cout << setw(110) << "�U            ��¼�˺�(2)��           �U" << endl;
    cout << setw(110) << "�U                                    �U" << endl;
    cout << setw(110) << "�U                                    �U" << endl;
    cout << setw(110) << "�U            �˳�ϵͳ(3)��           �U" << endl;
    cout << setw(110) << "�U                                    �U" << endl;
    cout << setw(110) << "�U                                    �U" << endl;
    cout << setw(110) << "�t�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�s" << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << setw(100) << "���������������Ĳ���(1-3)��";
    int x;
    cin >> x;
    if(x == 1)
        Register();
    if(x == 2)
        Login();
    if(x == 3)
        exit(1);
}

void Register()                                                                         //ע����棬ע���˺�
{
	char name[20], password[20], password2[20];
    char c;
    //�������Ҵ�ӡ�µĽ���
    system ("cls");
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << setw(110) << "�q�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�r" << endl;
    cout << setw(110) << "�U                                    �U" << endl;
    cout << setw(110) << "�U    �û�����                        �U" << endl;
    cout << setw(110) << "�U                                    �U" << endl;
    cout << setw(110) << "�U    �������룺                      �U" << endl;
    cout << setw(110) << "�U                                    �U" << endl;
    cout << setw(110) << "�U    ȷ�����룺                      �U" << endl;
    cout << setw(110) << "�U                                    �U" << endl;
    cout << setw(110) << "�t�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�s" << endl;
	//��궨λ �����û���
    gotoxy(87, 10);
	cin>>name;
	
    gotoxy(87, 12);
    int i = 0;
    //�����������룬����*����������
    while((c = getch()) != '\r')
    {
        if(c != 8)
        {
            password[i++] = c;
            putchar('*');
        }
        if(c == 8 && i != 0)
        {
            i--;
            gotoxy(87 + i, 12);
            cout << " ";
            gotoxy(87 + i, 12);
        }
    }
    password[i++] = '\0';
    //ȷ���������룬����*����������
    gotoxy(87, 14);
    i = 0;
    while((c = getch()) != '\r')
    {
        if(c != 8)
        {
            password2[i++] = c;
            putchar('*');
        }
        if(c == 8 && i != 0)
        {
            i--;
            gotoxy(87 + i, 14);
            cout << " ";
            gotoxy(87 + i, 14);
        }
    }
    password2[i++] = '\0';
    //�ж��������������Ƿ�һ������һ����ʱ��������û������룬��Ȼ����ע��
    gotoxy(75, 18);
    if(strcmp(password,password2) == 0)
    {
		insert_user(name, password);
        cout << "ע��ɹ�������������ص�½���棡" << endl;
        getchar();
        getchar();
        Login();
    }
    else
    {
        cout << "�����������벻һ����������ע�ᣡ" << endl;
        getchar();
        getchar();
        Register();
    }
}

void Login()                                                                            //��¼���棬��¼�˺�
{
    char name[100], password[100], c;
    //�������Ҵ�ӡ�µĽ���
    system ("cls");
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << setw(110) << "�q�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�r" << endl;
    cout << setw(110) << "�U                                    �U" << endl;
    cout << setw(110) << "�U                                    �U" << endl;
    cout << setw(110) << "�U    ��½�˺ţ�                      �U" << endl;
    cout << setw(110) << "�U                                    �U" << endl;
    cout << setw(110) << "�U                                    �U" << endl;
    cout << setw(110) << "�U    ��½���룺                      �U" << endl;
    cout << setw(110) << "�U                                    �U" << endl;
    cout << setw(110) << "�U                                    �U" << endl;
    cout << setw(110) << "�t�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�s" << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    //�����½���û���
    gotoxy(87, 11);
    scanf("%s",&name);
    //�����½�����룬������*����
    gotoxy(87, 14);
    int i = 0;
    while((c = getch()) != '\r')
    {
        if(c != 8)
        {
            password[i++] = c;
            putchar('*');
        }
        if(c == 8 && i != 0)
        {
            i--;
            gotoxy(87 + i, 14);
            cout << " ";
            gotoxy(87 + i, 14);
        }
    }
    password[i++] = '\0';
    gotoxy(75, 20); //������ƣ�
    chack_mima(name,password);
}

void chack_mima(char *name, char *password)
{
	sqlite3 *db = NULL;
	
	int rc = sqlite3_open("canyin.db", &db);
	if( rc != 0)
	{
		printf("error!\n");
		return;
	}
	sqlite3_stmt* stmt = NULL;
	// ��������SQL���, :1��ʾid, :2��ʾname
	char sql[512];
	sprintf(sql,
		"SELECT * FROM user WHERE name="
		"('%s')"
		,name
		);

	// ��ʼ��SQL Statement����
	rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if(rc != SQLITE_OK)
	{
		printf("failed to prepare: %s \n", sqlite3_errmsg(db));
		return;
	}

	// �󶨲���
	//sqlite3_bind_text(stmt, 1, name, -1, NULL);

	// ִ��SQL
	bool flag = false;
	while(1)
	{
		rc = sqlite3_step(stmt);
		
		if(rc == SQLITE_ROW)
		{
			char* password2 = (char*) sqlite3_column_text(stmt, 1);

			if(strcmp(password2, password) == 0)
			{
				flag = true;
			}
			else
			{
				flag = false;
			}
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
	if(flag == true)
	{
		gotoxy(80, 20);
		cout<<"��½�ɹ�����ӭʹ�ã�"<<endl;
		getchar();
        getchar();
		Welcome();
	}
	else
	{
		gotoxy(66, 20);
		cout<<"�˻�������������󣬰�������������룬��ESC���ؿ�ʼ���棡"<<endl;
		char c;
		c = getch();
		if(c == 27)
			Start();
		else
			Login();
	}
}

void Welcome()                                                                          //ѡ����棬ѡ��������Ĳ���
{
    system ("cls");
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << setw(110) << "�q�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�r" << endl;
    cout << setw(110) << "�U                                    �U" << endl;
    cout << setw(110) << "�U           �˵�����(1)��            �U" << endl;
    cout << setw(110) << "�U                                    �U" << endl;
    cout << setw(110) << "�U           ��̨����(2)��            �U" << endl;
    cout << setw(110) << "�U                                    �U" << endl;
    cout << setw(110) << "�U           ��Ա����(3)��            �U" << endl;
	cout << setw(110) << "�U                                    �U" << endl;
    cout << setw(110) << "�U           Ӫҵ��ѯ(4)��            �U" << endl;
    cout << setw(110) << "�U                                    �U" << endl;
    cout << setw(110) << "�U           ע���˳�(5)��            �U" << endl;
    cout << setw(110) << "�U                                    �U" << endl;
    cout << setw(110) << "�t�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�s" << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << setw(100) << "���������������Ĳ���(1-4)��";
    int x;
    cin >> x;
	if(x == 1)
		Select_menu();
    if(x == 2)
        Select_tables();
	if(x == 3)
        Personnel();
	if(x == 4)
		Select_price();
    if(x == 5)
        Start();
}
void Select_menu()
{
	system ("cls");
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << setw(123) << "�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T" << endl;
	sqlite3 * db = NULL;
	int rc = sqlite3_open("canyin.db", &db);
	if( rc != 0)
	{
		printf("error!\n");
		return;
	}
	sqlite3_stmt* stmt = NULL;

	// ��������SQL���, :1��ʾid, :2��ʾname
	char sql[512] ="SELECT * FROM menu";

	// ��ʼ��SQL Statement����
	rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if(rc != SQLITE_OK)
	{
		printf("failed to prepare: %s \n", sqlite3_errmsg(db));
		return;
	}

	// ִ��SQL
	cout << setw(130) << "                                                                        " << endl;
	cout << setw(130) << "     ���                 ��Ŀ����               ��Ŀ�۸�               " << endl;
	int i = 0;
	while(1)
	{
		i++;
		rc = sqlite3_step(stmt);
		
		if(rc == SQLITE_ROW)
		{
			char* name = (char*)sqlite3_column_text(stmt, 0);
			double price = sqlite3_column_double(stmt, 1);
			cout << setw(130) << "                                                                        " << endl;

			cout << "                                                                " << i << "                    " << name 
				 << "                    " << price << endl;
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
	cout << endl;
	cout << endl;
	cout << setw(123) << "�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T" << endl;
	cout << setw(130) << "                                                                        " << endl;
	cout << setw(130) << "                                                                        " << endl;
	cout << setw(130) << "     ��Ӳ�Ŀ(1)           ɾ����Ŀ(2)          ���ز˵�(3)             " << endl;
	cout << setw(130) << "                                                                        " << endl;
	cout << setw(130) << "                                                                        " << endl;
	cout << setw(100) << "                    ���������Ĳ���(1-4):";
	int x;
	do
	{
		cin>>x;
		if(x > 3 || x < 1)
			cout<<"��������ȷ��ָ��:"<<endl;
	}while(x > 3 || x < 1);
	if(x == 1)
	{
		Add_menu();
	}
	if(x == 2)
	{
		Delete_menu();
	}
	if(x == 3)
		Welcome();
}
void Add_menu()
{
	system ("cls");
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << setw(123) << "�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T" << endl;
	cout << setw(130) << "                                                                        " << endl;
	cout << setw(130) << "                  ������Ҫ��ӵĲ�Ʒ���ƺͲ�Ŀ�۸�                      " << endl;
	cout << setw(130) << "                                                                        " << endl;
	cout << setw(130) << "          ��Ŀ����                            ��Ŀ�۸�                  " << endl;
	cout << setw(130) << "                                                                        " << endl;
	float price;
	char name[100];
	int temp = 13;
	gotoxy(150, 41);
	cout << "��ESC������һ��ҳ��!" << endl;
	char c;
	while((c = getch()))
    {
        if(c != 27)
        {
            gotoxy(70, temp);
            scanf("%s", name);
            gotoxy(107, temp);
            scanf("%f", &price);
			Insert_menu(name,price);
			temp++;
        }
		else
			Select_menu();
	}
}




void Delete_menu()
{
	system ("cls");
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << setw(123) << "�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T" << endl;
	cout << setw(130) << "                                                                        " << endl;
	cout << setw(130) << "                        ������Ҫɾ���Ĳ�Ʒ����                          " << endl;
	cout << setw(130) << "                                                                        " << endl;
	cout << setw(130) << "                                                                        " << endl;
	float price;
	char name[100];
	int temp = 12;
	char c;
	gotoxy(150, 41);
	cout << "��ESC������һ��ҳ��!" << endl;
	while((c = getch()))
    {
        if(c != 27)
        {
            gotoxy(90, temp);
            scanf("%s", name);
			double x = Select_menu(name);
			if(x != -1)
				Delete_menu_table(name);
			temp++;
        }
		else
			Select_menu();
	}
}







void Select_tables()
{
	system ("cls");
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << setw(123) << "�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T" << endl;
	sqlite3 * db = NULL;
	int rc = sqlite3_open("canyin.db", &db);
	if( rc != 0)
	{
		printf("error!\n");
		return;
	}
	sqlite3_stmt* stmt = NULL;

	// ��������SQL���, :1��ʾid, :2��ʾname
	char sql[512] ="SELECT * FROM tables";

	// ��ʼ��SQL Statement����
	rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if(rc != SQLITE_OK)
	{
		printf("failed to prepare: %s \n", sqlite3_errmsg(db));
		return;
	}

	// ִ��SQL
	cout << setw(130) << "                                                                        " << endl;
	cout << setw(130) << "   �������                  ��̨״̬                   ��������         " << endl;
	while(1)
	{
		rc = sqlite3_step(stmt);
		
		if(rc == SQLITE_ROW)
		{
			int id = sqlite3_column_int(stmt, 0);
			int open = sqlite3_column_int(stmt, 1);
			int tb_peo = sqlite3_column_int(stmt, 2);	//��̨����
			if(open == 0)
			{
				cout << setw(130) << "                                                                        " << endl;
				cout << "                                                                " << id << "                        ����   " <<  "                    "<<tb_peo<< endl;
			}
			else
			{
				cout << setw(130) << "                                                                        " << endl;
				cout << "                                                                " << id << "                        ռ��   "<<   "                    "<<tb_peo<< endl;
			}
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
	cout << endl;
	cout << endl;
	cout << setw(123) << "�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T" << endl;
	cout << setw(130) << "                                                                        " << endl;
	cout << setw(130) << "                                                                        " << endl;
	cout << setw(130) << "     ���˿�̨(1)      �������(2)      ɾ������(3)      ���ز˵�(4)     " << endl;
	cout << setw(130) << "                                                                        " << endl;
	cout << setw(130) << "                                                                        " << endl;
	cout << setw(100) << "                    ���������Ĳ���(1-4):";
	int x;
	do
	{
		cin>>x;
		if(x > 4 || x < 1)
			cout<<"��������ȷ��ָ��:"<<endl;
	}while(x > 4 || x < 1);
	if(x == 1)
		Kaitai();
	if(x == 2)
		Tables_jia();
	if(x == 3)
		Delete_tables_num();
	if(x == 4)
		Welcome();
}

void Kaitai()
{
	system ("cls");
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << setw(123) << "�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T" << endl;
	cout << setw(130) << "                                                                        " << endl;
	cout << setw(130) << " ��������(1)       �鿴δ����(2)     ���˽���(3)     ���ز˵�(4)        " << endl;
	cout << setw(130) << "                                                                        " << endl;
	cout << setw(130) << "                                                                        " << endl;
	cout << setw(100) << "                    ���������Ĳ���(1-4):";
	int order;
	cin>>order;
	if(order == 1)
		Diancai();
	if(order == 2)
		Select_orders_nopay();
	if(order == 3)
		Jiezhang();
	else
		Select_tables();
}

void Diancai()
{
	system ("cls");
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << setw(123) << "�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T" << endl;
	cout << setw(130) << "                                                                        " << endl;
	cout << setw(130) << "                  �����붩����š�������š��Ͳ�����                    " << endl;
	cout << setw(130) << "                                                                        " << endl;
	cout << setw(130) << "       �������         �������         �Ͳ�����        �Ͳ�����       " << endl;
	cout << setw(130) << "                                                                        " << endl;
	int tb_id, order_id, tb_peo;
	char datetime[20];
    gotoxy(69, 13);
    scanf("%d", &order_id);
    gotoxy(86, 13);
    scanf("%d", &tb_id);
	gotoxy(103, 13);
	scanf("%d", &tb_peo);
	gotoxy(117, 13);
	scanf("%s", datetime);
	int max_num = Tb_peo(tb_id);
	if(max_num < tb_peo)
	{
		cout<<endl;
		cout<<endl;
		cout << setw(130) <<"�˲��������ݣ�"<<max_num<<"�˾Ͳͣ�"<<endl;
		getchar();
		getchar();
		Diancai();
	}

	Update_tables(tb_id, 1);
	cout << setw(130) << "                                                                        " << endl;
	cout << setw(130) << "                       ��������Ҫѡ���Ĳ�Ʒ����                       " << endl;
	cout << setw(130) << "                                                                        " << endl;
	char menu_name[100];
	double total_price = 0;
	char c;
	int temp = 17;
	gotoxy(150, 41);
	cout << "�����ɰ�ESC��ɶ���!" << endl;
	while((c = getch()))
    {
        if(c != 27)
        {
            gotoxy(90, temp);
            scanf("%s", menu_name);
			double price = Select_menu(menu_name);
			if(price == -1)
			{
				gotoxy(110, temp);
				cout << "��Ŀ��û�д˲˵���" << endl;
				temp++;
				continue;
			}
			total_price += price;
			temp++;
        }
		else
		{
			Insert_orders(tb_id, order_id, tb_peo, datetime, total_price);
			gotoxy(80, temp + 10);
			cout << "���������ɹ���������������ϼ�ҳ��" << endl;
			getchar();
			getchar();
			Kaitai();
		}
	}
}

void Select_orders_nopay()
{
	sqlite3 * db = NULL;
	int rc = sqlite3_open("canyin.db", &db);
	if( rc != 0)
	{
		printf("error!\n");
		return;
	}
	sqlite3_stmt* stmt = NULL;

	// ��������SQL���, :1��ʾid, :2��ʾname
	char sql[512] ="SELECT * FROM orders WHERE CUST_PAY=0";

	// ��ʼ��SQL Statement����
	rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if(rc != SQLITE_OK)
	{
		printf("failed to prepare: %s \n", sqlite3_errmsg(db));
		return;
	}

	// ִ��SQL
	system ("cls");
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << setw(130) << "�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T" << endl;
	cout << setw(130) << "                                                                        " << endl;
	cout << setw(130) << "  �������        �������     �Ͳ�����      ���ѽ��       �Ͳ�����    " << endl;
	cout << setw(130) << "                                                                        " << endl;
	while(1)
	{
		rc = sqlite3_step(stmt);
		
		if(rc == SQLITE_ROW)
		{
			int order_id = sqlite3_column_int(stmt, 0);
			int tb_id = sqlite3_column_int(stmt, 1);
			int tb_peo = sqlite3_column_int(stmt, 6);
			double price = sqlite3_column_double(stmt, 2);
			char* datetime =  (char*)sqlite3_column_text(stmt, 5);
			cout << setw(130) << "                                                              " << endl;
			cout << "                                                               " << order_id << "               " << tb_id << "             " << tb_peo << "            " 
				<< price << "          " << datetime << endl;
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
	gotoxy(150, 41);
	cout << "��ESC������һ��ҳ��!" << endl;
	// ����Statement����
	sqlite3_finalize(stmt);
	char c;
	c = getch();
	if(c == 27)
		Kaitai();
}

void Jiezhang()
{
	system ("cls");
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << setw(130) << "�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T" << endl;
	cout << setw(130) << "                                                                        " << endl;
	cout << setw(130) << "                                                                        " << endl;
	cout << setw(130) << "      ������Ҫ���˵Ķ������                   ��������˸���           " << endl;
	cout << setw(130) << "                                                                        " << endl;
	char c;
	int num;
	double money;
	int temp = 13;
	gotoxy(150, 41);
	cout << "��ESC������һ��ҳ��!" << endl;
	while((c = getch()))
    {
        if(c != 27)
        {
            gotoxy(73, temp);
            scanf("%d", &num);
			int tb_id = Tbid_order(num);
			Update_tables(tb_id,0);
			gotoxy(110, temp);
			scanf("%lf", &money);
			double price = Select_orders_price(num);
			price = money - price;
			if(price < 0)
			{
				cout<<endl;
				cout<<endl;
				cout<<setw(130) <<"����㣡"<<endl;
				getchar();
				getchar();
				Jiezhang();
			}
			Update_orders(num, money,price); 
			temp++;
        }
		else
			Kaitai();
	}
}

void Tables_jia()
{
	system ("cls");
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << setw(123) << "�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T" << endl;
	cout << setw(130) << "                                                                        " << endl;
	cout << setw(130) << "          ������Ҫ��ӵ���̨�ı��          ��̨���ɵ�����              " << endl;
	cout << setw(130) << "                                                                        " << endl;
	cout << setw(130) << "                                                                        " << endl;
	int tmp, temp_peo;
	int temp = 13;
	char c;
	gotoxy(150, 41);
	cout << "��ESC������һ��ҳ��!" << endl;
	while((c = getch()))
    {
        if(c != 27)
        {
            gotoxy(80, temp);
            scanf("%d", &tmp);
			gotoxy(110, temp);
            scanf("%d", &temp_peo);
			Insert_tables(tmp, temp_peo);
			temp++;
        }
		else
			Select_tables();
	}
}

void Delete_tables_num()
{
	system ("cls");
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << setw(123) << "�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T" << endl;
	cout << setw(130) << "                                                                        " << endl;
	cout << setw(130) << "                        ������Ҫɾ�������ӱ��                          " << endl;
	cout << setw(130) << "                                                                        " << endl;
	cout << setw(130) << "                                                                        " << endl;
	float price;
	int num;
	int temp = 12;
	char c;
	gotoxy(150, 41);
	cout << "��ESC������һ��ҳ��!" << endl;
	while((c = getch()))
    {
        if(c != 27)
        {
            gotoxy(93, temp);
            scanf("%d", &num);
			bool x = Is_tables(num);
			if(x != false)
				Delete_tables(num);
			temp++;
        }
		else
			Select_tables();
	}
}


void Select_price()
{
	system ("cls");
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << setw(110) << "�q�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�r" << endl;
    cout << setw(110) << "�U                                    �U" << endl;
    cout << setw(110) << "�U           �鿴�ܶ���(1)��          �U" << endl;
    cout << setw(110) << "�U                                    �U" << endl;
    cout << setw(110) << "�U           �鿴��Ӫҵ(2)��          �U" << endl;
    cout << setw(110) << "�U                                    �U" << endl;
    cout << setw(110) << "�U           �鿴��Ӫҵ(3)��          �U" << endl;
    cout << setw(110) << "�U                                    �U" << endl;
    cout << setw(110) << "�U           ���ز˵�(4)��            �U" << endl;
    cout << setw(110) << "�U                                    �U" << endl;
    cout << setw(110) << "�t�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�s" << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << setw(100) << "���������������Ĳ���(1-4)��";
	int x;
	char temp[100];
	cin >> x;
	if(x == 1)
		Select_allorders();
	if(x == 2)
	{
		cout << setw(94) << "��������Ҫ��ѯ������:";
		cin >> temp;
			Select_orders_day(temp);
	}
	if(x == 3)
	{
		cout << setw(94) << "��������Ҫ��ѯ���·�:";
		cin >> temp;
			Select_orders_mouth(temp);
	}
	if(x == 4)
		Welcome();
}


void Select_allorders()
{
	sqlite3 * db = NULL;
	int rc = sqlite3_open("canyin.db", &db);
	if( rc != 0)
	{
		printf("error!\n");
		return;
	}
	sqlite3_stmt* stmt = NULL;

	char sql[512] ="SELECT * FROM orders";

	// ��ʼ��SQL Statement����
	rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if(rc != SQLITE_OK)
	{
		printf("failed to prepare: %s \n", sqlite3_errmsg(db));
		return;
	}

	// ִ��SQL
	system ("cls");
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << setw(140) << "�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T" << endl;
	cout << endl;
	cout << setw(140) << "   �������     �������     �Ͳ�����     ���ѽ��     ʵ����     ����     ��������     " << endl;
	cout << endl;
	while(1)
	{
		rc = sqlite3_step(stmt);
		
		if(rc == SQLITE_ROW)
		{
			int order_id = sqlite3_column_int(stmt, 0);
			int tb_id = sqlite3_column_int(stmt, 1);
			int tb_peo = sqlite3_column_int(stmt, 6);
			double price = sqlite3_column_double(stmt, 2);
			double pay = sqlite3_column_double(stmt, 3);
			double change = sqlite3_column_double(stmt, 4);
			char* datetime =  (char*)sqlite3_column_text(stmt, 5);
			cout << endl;
			cout << "                                                          " << order_id << "            " << tb_id << "            " << tb_peo << "            " 
				<< price<< "          " << pay<< "        " << change << "       " << datetime << endl;
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

	sqlite3_finalize(stmt);
	char c;
	c = getch();
	if(c == 27)
		Select_price();
}


void Select_orders_day(char *datetime)									//1.11 new
{
	sqlite3 * db = NULL;
	int rc = sqlite3_open("canyin.db", &db);
	if( rc != 0)
	{
		printf("error!\n");
		return;
	}
	sqlite3_stmt* stmt = NULL;

	// ��������SQL���, :1��ʾid, :2��ʾname
	char sql[512];
	sprintf(sql,
		"SELECT * FROM orders WHERE DATETIME ="
		"('%s')"
		,datetime
		);

	// ��ʼ��SQL Statement����
	rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if(rc != SQLITE_OK)
	{
		printf("failed to prepare: %s \n", sqlite3_errmsg(db));
		return;
	}

	double sum = 0;
	// ִ��SQL
	system ("cls");
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << setw(140) << "�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T" << endl;
	cout << endl;
	cout << setw(140) << "   �������     �������     �Ͳ�����     ���ѽ��     ʵ����     ����     ��������     " << endl;
	cout << endl;
	while(1)
	{
		rc = sqlite3_step(stmt);
		
		if(rc == SQLITE_ROW)
		{
			int order_id = sqlite3_column_int(stmt, 0);
			int tb_id = sqlite3_column_int(stmt, 1);
			int tb_peo = sqlite3_column_int(stmt, 6);
			double price = sqlite3_column_double(stmt, 2);
			double pay = sqlite3_column_double(stmt, 3);
			double change = sqlite3_column_double(stmt, 4);
			char* datetime =  (char*)sqlite3_column_text(stmt, 5);
			cout << endl;
			cout << "                                                          " << order_id << "            " << tb_id << "            " << tb_peo << "            " 
				<< price<< "          " << pay<< "        " << change << "       " << datetime << endl;
			sum += price;
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
	gotoxy(150, 40);
	cout << "���յ�Ӫҵ��Ϊ��" << sum << endl;
	gotoxy(150, 41);
	cout << "��ESC������һ��ҳ��!" << endl;
		char c;
	c = getch();
	if(c == 27)
		Select_price();
}


void Select_orders_mouth(char *datetime)									//1.11 new
{
	sqlite3 * db = NULL;
	int rc = sqlite3_open("canyin.db", &db);
	if( rc != 0)
	{
		printf("error!\n");
		return;
	}
	sqlite3_stmt* stmt = NULL;

	// ��������SQL���, :1��ʾid, :2��ʾname
	char sql[512];
	sprintf(sql,
		"SELECT * FROM orders WHERE DATETIME LIKE '"
		"%s-%%'"
		,datetime
		);
	//cout<<sql<<endl;

	// ��ʼ��SQL Statement����
	rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if(rc != SQLITE_OK)
	{
		printf("failed to prepare: %s \n", sqlite3_errmsg(db));
		return;
	}
	double sum = 0;
	// ִ��SQL
	system ("cls");
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << setw(140) << "�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T" << endl;
	cout << endl;
	cout << setw(140) << "   �������     �������     �Ͳ�����     ���ѽ��     ʵ����     ����     ��������     " << endl;
	cout << endl;
	while(1)
	{
		rc = sqlite3_step(stmt);
		
		if(rc == SQLITE_ROW)
		{
			int order_id = sqlite3_column_int(stmt, 0);
			int tb_id = sqlite3_column_int(stmt, 1);
			int tb_peo = sqlite3_column_int(stmt, 6);
			double price = sqlite3_column_double(stmt, 2);
			double pay = sqlite3_column_double(stmt, 3);
			double change = sqlite3_column_double(stmt, 4);
			char* datetime =  (char*)sqlite3_column_text(stmt, 5);
			cout << endl;
			cout << "                                                          " << order_id << "            " << tb_id << "            " << tb_peo << "            " 
				<< price<< "          " << pay<< "        " << change << "       " << datetime << endl;
			sum += price;
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
	gotoxy(150, 40);
	cout << "���µ�Ӫҵ��Ϊ��" << sum << endl;
	gotoxy(150, 41);
	cout << "��ESC������һ��ҳ��!" << endl;
		char c;
	c = getch();
	if(c == 27)
		Select_price();
}
	

void Personnel()
{
    system("cls");
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    char c, temp[100][256];
    int s = 0;
    ifstream readf("Personnel.dat",ios::out);
    if(!readf)
    {
        cerr << "open error!" << endl;
        exit(1);
    }
    while(readf)
    {
        int j = 0;
        while(readf.get(c))
        {
            if(c == '\n')
                break;
            temp[s][j++] = c;
        }
        temp[s++][j++] = '\0';
    }
    readf.close();
    int i = 0;
    cout << setw(117) << "�q�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�r" << endl;
    cout << setw(117) << "�U                                                          �U" << endl;
    cout << setw(117) << "�U   ���          ����            �Ա�           �绰      �U" << endl;
    cout << setw(117) << "�U                                                          �U" << endl;
    cout << setw(57) << "�U";
    while(i < s)
    {
        if((i + 1) % 4 != 0 || i == 0)
            cout << setw(6) << temp[i] << "         ";
        else
        {
            cout << temp[i] << "  �U" << endl;
            if(i != s - 1)
            cout << setw(57) << "�U";
        }
        i++;
    }
    cout << setw(117) << "�U                                                          �U" << endl;
    cout << setw(117) << "�t�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�s" << endl;
    gotoxy(64, 21);
    cout << "���(1)     �޸�(2)     ɾ��(3)     ����(4)";
    gotoxy(75, 24);
    cout << "���������Ĳ���(1-4)��";
    int x;
    cin >> x;
    if(x == 1)
        AppendPersonnel();
    if(x == 2)
        RevisePersonnel();
    if(x == 3)
        DeletePersonnel();
    if(x == 4)
        Welcome();
}


void AppendPersonnel()
{
    system ("cls");
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << setw(117) << "�q�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�r" << endl;
    cout << setw(117) << "�U                                                          �U" << endl;
    cout << setw(117) << "�U     ��������ӵĲ�����Ա�ı�š��������Ա𡢵绰��       �U" << endl;
    cout << setw(117) << "�U                                                          �U" << endl;
    cout << setw(117) << "�U   ���          ����            �Ա�           �绰      �U" << endl;
    cout << setw(117) << "�U                                                          �U" << endl;
    cout << setw(117) << "�U                                                          �U" << endl;
    cout << setw(117) << "�U                                                          �U" << endl;
    cout << setw(117) << "�U                                                          �U" << endl;
    cout << setw(117) << "�U                                                          �U" << endl;
    cout << setw(117) << "�U                                                          �U" << endl;
    cout << setw(117) << "�U                                                          �U" << endl;
    cout << setw(117) << "�U                                                          �U" << endl;
    cout << setw(117) << "�U                                                          �U" << endl;
    cout << setw(117) << "�U                                                          �U" << endl;
    cout << setw(117) << "�U                                                          �U" << endl;
    cout << setw(117) << "�U                                                          �U" << endl;
    cout << setw(117) << "�U                                                          �U" << endl;
    cout << setw(117) << "�t�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�s" << endl;
    ofstream outfile("Personnel.dat",ios::app);
    if(!outfile)
    {
        cerr << "open error!" << endl;
        exit(1);
    }
	gotoxy(150, 41);
	cout << "��ESC������һ��ҳ��!" << endl;
    char c, tempnum[100], tempname[100], tempsex[100], temptel[100];
    int temp = 10;
    while((c = getch()))
    {
        if(c != 27)
        {
            gotoxy(62, temp);
            scanf("%s", tempnum);

            gotoxy(75, temp);
            scanf("%s", tempname);

            gotoxy(91, temp);
            scanf("%s", tempsex);

            gotoxy(105, temp);
            scanf("%s", temptel);
            outfile  << endl << tempnum;
            outfile  << endl << tempname;
            outfile  << endl << tempsex;
            outfile  << endl << temptel;
            temp++;
        }
        else
        {
            outfile.close();
            Personnel();
        }
    }
}


void RevisePersonnel()
{
    system ("cls");
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << setw(117) << "�q�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�r" << endl;
    cout << setw(117) << "�U                                                          �U" << endl;
    cout << setw(117) << "�U     �������޸ĵĲ�����Ա�ı�š��������Ա𡢵绰��       �U" << endl;
    cout << setw(117) << "�U                                                          �U" << endl;
    cout << setw(117) << "�U   ���          ����            �Ա�           �绰      �U" << endl;
    cout << setw(117) << "�U                                                          �U" << endl;
    cout << setw(117) << "�U                                                          �U" << endl;
    cout << setw(117) << "�U                                                          �U" << endl;
    cout << setw(117) << "�U                                                          �U" << endl;
    cout << setw(117) << "�U                                                          �U" << endl;
    cout << setw(117) << "�U                                                          �U" << endl;
    cout << setw(117) << "�U                                                          �U" << endl;
    cout << setw(117) << "�U                                                          �U" << endl;
    cout << setw(117) << "�U                                                          �U" << endl;
    cout << setw(117) << "�U                                                          �U" << endl;
    cout << setw(117) << "�U                                                          �U" << endl;
    cout << setw(117) << "�U                                                          �U" << endl;
    cout << setw(117) << "�U                                                          �U" << endl;
    cout << setw(117) << "�t�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�s" << endl;
    char c, tempper[100][100];
    char tempnum[100], tempname[100], tempsex[100], temptel[100];
    int temp = 10;
	gotoxy(150, 41);
	cout << "��ESC������һ��ҳ��!" << endl;
    ifstream readf("Personnel.dat",ios::out);
    if(!readf)
    {
        cerr << "open error!" << endl;
        exit(1);
    }
    int s = 0;
    while(readf)
    {
        int j = 0;
        while(readf.get(c))
        {
            if(c == '\n')
                break;
            tempper[s][j++] = c;
        }
        tempper[s++][j++] = '\0';
    }
    readf.close();
    ofstream writef("Personnel.dat",ios::in);
    if(!writef)
    {
        cerr << "open error!" << endl;
        exit(1);
    }
    while((c = getch()))
    {
        if(c != 27)
        {
            gotoxy(62, temp);
            scanf("%s", tempnum);

            gotoxy(75, temp);
            scanf("%s", tempname);

            gotoxy(91, temp);
            scanf("%s", tempsex);

            gotoxy(105, temp);
            scanf("%s", temptel);
            for(int i = 0; i < s - 4; i = i+ 4)
            {
                if(strcmp(tempnum, tempper[i]) == 0)
                {
                    strcpy(tempper[i], tempnum);
                    strcpy(tempper[i + 1], tempname);
                    strcpy(tempper[i + 2], tempsex);
                    strcpy(tempper[i + 3], temptel);

                }
                writef << tempper[i] << endl;
                writef << tempper[i + 1] << endl;
                writef << tempper[i + 2] << endl;
                writef << tempper[i + 3] << endl;
            }
            if(strcmp(tempnum, tempper[s - 4]) == 0)
            {
                strcpy(tempper[s - 4], tempnum);
                strcpy(tempper[s - 3], tempname);
                strcpy(tempper[s - 2], tempsex);
                strcpy(tempper[s - 1], temptel);
            }
            writef << tempper[s - 4] << endl;
            writef << tempper[s - 3] << endl;
            writef << tempper[s - 2] << endl;
            writef << tempper[s - 1];
            temp++;

        }
        else
        {
            writef.close();
            Personnel();
        }
    }
}


void DeletePersonnel()
{
    system ("cls");
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << setw(110) << "�q�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�r" << endl;
    cout << setw(110) << "�U                                    �U" << endl;
    cout << setw(110) << "�U         ������ɾ����Ա�����       �U" << endl;
    cout << setw(110) << "�U                                    �U" << endl;
    cout << setw(110) << "�U              Ա�����              �U" << endl;
    cout << setw(110) << "�U                                    �U" << endl;
    cout << setw(110) << "�U                                    �U" << endl;
    cout << setw(110) << "�U                                    �U" << endl;
    cout << setw(110) << "�U                                    �U" << endl;
    cout << setw(110) << "�U                                    �U" << endl;
    cout << setw(110) << "�U                                    �U" << endl;
    cout << setw(110) << "�U                                    �U" << endl;
    cout << setw(110) << "�U                                    �U" << endl;
    cout << setw(110) << "�U                                    �U" << endl;
    cout << setw(110) << "�U                                    �U" << endl;
    cout << setw(110) << "�U                                    �U" << endl;
    cout << setw(110) << "�U                                    �U" << endl;
    cout << setw(110) << "�U                                    �U" << endl;
    cout << setw(110) << "�t�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�s" << endl;
    char c, tempstr[100][100], num[100];
	gotoxy(150, 41);
	cout << "��ESC������һ��ҳ��!" << endl;
    int temp = 10;
    while((c = getch()))
    {
        if(c != 27)
        {
            gotoxy(87, temp);
            scanf("%s", num);
            ifstream readf("Personnel.dat",ios::out);
            if(!readf)
            {
                cerr << "open error!" << endl;
                exit(1);
            }
            int s = 0;
            while(readf)
            {
                int j = 0;
                while(readf.get(c))
                {
                    if(c == '\n')
                        break;
                    tempstr[s][j++] = c;
                }
                tempstr[s++][j++] = '\0';
            }
            readf.close();
            ofstream writef("Personnel.dat",ios::trunc);
            if(!writef)
            {
                cerr << "open error!" << endl;
                exit(1);
            }
            for(int i = 0; i < s - 4; i = i + 4)
            {
                if(strcmp(num, tempstr[i]) == 0)
                {
                    continue;
                }
                else
                {
                    writef << tempstr[i] << endl;
                    writef << tempstr[i + 1] << endl;
                    writef << tempstr[i + 2] << endl;
                    writef << tempstr[i + 3] << endl;
                }
            }
            if(strcmp(num, tempstr[s - 4]) != 0)
           {
               writef << tempstr[s - 4] << endl;
               writef << tempstr[s - 3] << endl;
               writef << tempstr[s - 2] << endl;
               writef << tempstr[s - 1];
            }
            writef.close();
            temp++;
        }
        else
        {
            Personnel();
        }
    }
}



