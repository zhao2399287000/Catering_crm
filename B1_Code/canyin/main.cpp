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


//创建初始化数据库
void creat_table();
//光标定位函数
void gotoxy(int,int);
//开始欢迎界面：注册、登陆、退出
void Start();  
//注册界面
void Register();
//登陆界面
void Login();
//检查用户名和密码是否匹配
void chack_mima(char *, char *);
//登陆成功欢迎界面
void Welcome();
//显示菜单
void Select_menu();
//添加菜品的名称和价格
void Add_menu();
//删除菜品的名称和价格
void Delete_menu();
//结账界面
void Jiezhang();
//显示桌台信息
void Select_tables();
//开台，可以通过创建订单给已占用的桌子加菜
//也可以给空闲桌子点菜，还可以查看未付款和结账
void Kaitai();
//显示点菜显示窗口
void Diancai();
//显示未付款的账单
void Select_orders_nopay();
//显示添加桌子的窗口
void Tables_jia();
//查询金额主页面
void Select_price();
//删除桌子界面
void Delete_tables_num();
//查看总订单
void Select_allorders();
//查看某一天的消费金额
void Select_orders_day(char *);
//查看某一月的消费金额
void Select_orders_mouth(char *);
//显示餐厅的人员信息
void Personnel();
//添加餐厅的人员信息
void AppendPersonnel();
//修改餐厅的人员信息
void RevisePersonnel();
//删除餐厅的人员信息
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

    rc = sqlite3_open("canyin.db", &db);  // 打开数据库
    if(rc)
    {
        fprintf(stderr, "Can't open database:%s\n", sqlite3_errmsg(db));
        return;
    }

    sql = "create table user(NAME TEXT NOT NULL, PASSWORD TEXT NOT NULL)";

    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg); // 执行上面sql中的命令
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

    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg); // 执行上面sql中的命令
    if(SQLITE_OK != rc)
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
    }

	sql = "create table tables(ID INT NOT NULL, \
		  OPEN INT, \
		  TB_PEO INT\
		  )";

    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg); // 执行上面sql中的命令
    if(SQLITE_OK != rc)
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
    }

	sql = "create table ORDER_MENU(ID INT NOT NULL, \
		  FD_NAME TEXT\
		  )";

    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg); // 执行上面sql中的命令
    if(SQLITE_OK != rc)
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
    }

	sql = "create table MENU(\
		  FD_NAME TEXT, \
		  FD_PRICE REAL, \
		  ID INT\
		  )";

    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg); // 执行上面sql中的命令
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
void Start()                                                                            //欢迎界面，注册和登录
{
    system("cls");
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << setw(110) << "╭══════════════════╮" << endl;
    cout << setw(110) << "║                                    ║" << endl;
    cout << setw(110) << "║                                    ║" << endl;
    cout << setw(110) << "║            注册账号(1)：           ║" << endl;
    cout << setw(110) << "║                                    ║" << endl;
    cout << setw(110) << "║                                    ║" << endl;
    cout << setw(110) << "║            登录账号(2)：           ║" << endl;
    cout << setw(110) << "║                                    ║" << endl;
    cout << setw(110) << "║                                    ║" << endl;
    cout << setw(110) << "║            退出系统(3)：           ║" << endl;
    cout << setw(110) << "║                                    ║" << endl;
    cout << setw(110) << "║                                    ║" << endl;
    cout << setw(110) << "╰══════════════════╯" << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << setw(100) << "请输入您接下来的操作(1-3)：";
    int x;
    cin >> x;
    if(x == 1)
        Register();
    if(x == 2)
        Login();
    if(x == 3)
        exit(1);
}

void Register()                                                                         //注册界面，注册账号
{
	char name[20], password[20], password2[20];
    char c;
    //清屏并且打印新的界面
    system ("cls");
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << setw(110) << "╭══════════════════╮" << endl;
    cout << setw(110) << "║                                    ║" << endl;
    cout << setw(110) << "║    用户名：                        ║" << endl;
    cout << setw(110) << "║                                    ║" << endl;
    cout << setw(110) << "║    输入密码：                      ║" << endl;
    cout << setw(110) << "║                                    ║" << endl;
    cout << setw(110) << "║    确认密码：                      ║" << endl;
    cout << setw(110) << "║                                    ║" << endl;
    cout << setw(110) << "╰══════════════════╯" << endl;
	//光标定位 输入用户名
    gotoxy(87, 10);
	cin>>name;
	
    gotoxy(87, 12);
    int i = 0;
    //控制输入密码，并用*将密码隐藏
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
    //确认输入密码，并用*将密码隐藏
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
    //判断两次输入密码是否一样，当一样的时候讲密码和用户名存入，不然重新注册
    gotoxy(75, 18);
    if(strcmp(password,password2) == 0)
    {
		insert_user(name, password);
        cout << "注册成功，按任意键返回登陆界面！" << endl;
        getchar();
        getchar();
        Login();
    }
    else
    {
        cout << "两次输入密码不一样，请重新注册！" << endl;
        getchar();
        getchar();
        Register();
    }
}

void Login()                                                                            //登录界面，登录账号
{
    char name[100], password[100], c;
    //清屏并且打印新的界面
    system ("cls");
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << setw(110) << "╭══════════════════╮" << endl;
    cout << setw(110) << "║                                    ║" << endl;
    cout << setw(110) << "║                                    ║" << endl;
    cout << setw(110) << "║    登陆账号：                      ║" << endl;
    cout << setw(110) << "║                                    ║" << endl;
    cout << setw(110) << "║                                    ║" << endl;
    cout << setw(110) << "║    登陆密码：                      ║" << endl;
    cout << setw(110) << "║                                    ║" << endl;
    cout << setw(110) << "║                                    ║" << endl;
    cout << setw(110) << "╰══════════════════╯" << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    //输入登陆的用户名
    gotoxy(87, 11);
    scanf("%s",&name);
    //输入登陆的密码，密码用*隐藏
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
    gotoxy(75, 20); //光标下移；
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
	// 带参数的SQL语句, :1表示id, :2表示name
	char sql[512];
	sprintf(sql,
		"SELECT * FROM user WHERE name="
		"('%s')"
		,name
		);

	// 初始化SQL Statement对象
	rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if(rc != SQLITE_OK)
	{
		printf("failed to prepare: %s \n", sqlite3_errmsg(db));
		return;
	}

	// 绑定参数
	//sqlite3_bind_text(stmt, 1, name, -1, NULL);

	// 执行SQL
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

	// 销毁Statement对象
	sqlite3_finalize(stmt);
	if(flag == true)
	{
		gotoxy(80, 20);
		cout<<"登陆成功，欢迎使用！"<<endl;
		getchar();
        getchar();
		Welcome();
	}
	else
	{
		gotoxy(66, 20);
		cout<<"账户名或者密码错误，按任意键重新输入，按ESC返回开始界面！"<<endl;
		char c;
		c = getch();
		if(c == 27)
			Start();
		else
			Login();
	}
}

void Welcome()                                                                          //选择界面，选择接下来的操作
{
    system ("cls");
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << setw(110) << "╭══════════════════╮" << endl;
    cout << setw(110) << "║                                    ║" << endl;
    cout << setw(110) << "║           菜单管理(1)：            ║" << endl;
    cout << setw(110) << "║                                    ║" << endl;
    cout << setw(110) << "║           桌台管理(2)：            ║" << endl;
    cout << setw(110) << "║                                    ║" << endl;
    cout << setw(110) << "║           人员管理(3)：            ║" << endl;
	cout << setw(110) << "║                                    ║" << endl;
    cout << setw(110) << "║           营业查询(4)：            ║" << endl;
    cout << setw(110) << "║                                    ║" << endl;
    cout << setw(110) << "║           注销退出(5)：            ║" << endl;
    cout << setw(110) << "║                                    ║" << endl;
    cout << setw(110) << "╰══════════════════╯" << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << setw(100) << "请输入您接下来的操作(1-4)：";
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
    cout << setw(123) << "═════════════════════════════════" << endl;
	sqlite3 * db = NULL;
	int rc = sqlite3_open("canyin.db", &db);
	if( rc != 0)
	{
		printf("error!\n");
		return;
	}
	sqlite3_stmt* stmt = NULL;

	// 带参数的SQL语句, :1表示id, :2表示name
	char sql[512] ="SELECT * FROM menu";

	// 初始化SQL Statement对象
	rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if(rc != SQLITE_OK)
	{
		printf("failed to prepare: %s \n", sqlite3_errmsg(db));
		return;
	}

	// 执行SQL
	cout << setw(130) << "                                                                        " << endl;
	cout << setw(130) << "     序号                 菜目名称               菜目价格               " << endl;
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

	// 销毁Statement对象
	sqlite3_finalize(stmt);
	cout << endl;
	cout << endl;
	cout << setw(123) << "═════════════════════════════════" << endl;
	cout << setw(130) << "                                                                        " << endl;
	cout << setw(130) << "                                                                        " << endl;
	cout << setw(130) << "     添加菜目(1)           删除菜目(2)          返回菜单(3)             " << endl;
	cout << setw(130) << "                                                                        " << endl;
	cout << setw(130) << "                                                                        " << endl;
	cout << setw(100) << "                    请输入您的操作(1-4):";
	int x;
	do
	{
		cin>>x;
		if(x > 3 || x < 1)
			cout<<"请输入正确的指令:"<<endl;
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
    cout << setw(123) << "═════════════════════════════════" << endl;
	cout << setw(130) << "                                                                        " << endl;
	cout << setw(130) << "                  请输入要添加的菜品名称和菜目价格                      " << endl;
	cout << setw(130) << "                                                                        " << endl;
	cout << setw(130) << "          菜目名称                            菜目价格                  " << endl;
	cout << setw(130) << "                                                                        " << endl;
	float price;
	char name[100];
	int temp = 13;
	gotoxy(150, 41);
	cout << "按ESC返回上一级页面!" << endl;
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
    cout << setw(123) << "═════════════════════════════════" << endl;
	cout << setw(130) << "                                                                        " << endl;
	cout << setw(130) << "                        请输入要删除的菜品名称                          " << endl;
	cout << setw(130) << "                                                                        " << endl;
	cout << setw(130) << "                                                                        " << endl;
	float price;
	char name[100];
	int temp = 12;
	char c;
	gotoxy(150, 41);
	cout << "按ESC返回上一级页面!" << endl;
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
    cout << setw(123) << "═════════════════════════════════" << endl;
	sqlite3 * db = NULL;
	int rc = sqlite3_open("canyin.db", &db);
	if( rc != 0)
	{
		printf("error!\n");
		return;
	}
	sqlite3_stmt* stmt = NULL;

	// 带参数的SQL语句, :1表示id, :2表示name
	char sql[512] ="SELECT * FROM tables";

	// 初始化SQL Statement对象
	rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if(rc != SQLITE_OK)
	{
		printf("failed to prepare: %s \n", sqlite3_errmsg(db));
		return;
	}

	// 执行SQL
	cout << setw(130) << "                                                                        " << endl;
	cout << setw(130) << "   订单编号                  桌台状态                   容纳人数         " << endl;
	while(1)
	{
		rc = sqlite3_step(stmt);
		
		if(rc == SQLITE_ROW)
		{
			int id = sqlite3_column_int(stmt, 0);
			int open = sqlite3_column_int(stmt, 1);
			int tb_peo = sqlite3_column_int(stmt, 2);	//桌台人数
			if(open == 0)
			{
				cout << setw(130) << "                                                                        " << endl;
				cout << "                                                                " << id << "                        空闲   " <<  "                    "<<tb_peo<< endl;
			}
			else
			{
				cout << setw(130) << "                                                                        " << endl;
				cout << "                                                                " << id << "                        占用   "<<   "                    "<<tb_peo<< endl;
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

	// 销毁Statement对象
	sqlite3_finalize(stmt);
	cout << endl;
	cout << endl;
	cout << setw(123) << "═════════════════════════════════" << endl;
	cout << setw(130) << "                                                                        " << endl;
	cout << setw(130) << "                                                                        " << endl;
	cout << setw(130) << "     客人开台(1)      添加桌子(2)      删除桌子(3)      返回菜单(4)     " << endl;
	cout << setw(130) << "                                                                        " << endl;
	cout << setw(130) << "                                                                        " << endl;
	cout << setw(100) << "                    请输入您的操作(1-4):";
	int x;
	do
	{
		cin>>x;
		if(x > 4 || x < 1)
			cout<<"请输入正确的指令:"<<endl;
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
    cout << setw(123) << "═════════════════════════════════" << endl;
	cout << setw(130) << "                                                                        " << endl;
	cout << setw(130) << " 创建订单(1)       查看未付款(2)     客人结账(3)     返回菜单(4)        " << endl;
	cout << setw(130) << "                                                                        " << endl;
	cout << setw(130) << "                                                                        " << endl;
	cout << setw(100) << "                    请输入您的操作(1-4):";
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
    cout << setw(123) << "═════════════════════════════════" << endl;
	cout << setw(130) << "                                                                        " << endl;
	cout << setw(130) << "                  请输入订单编号、餐桌编号、就餐日期                    " << endl;
	cout << setw(130) << "                                                                        " << endl;
	cout << setw(130) << "       订单编号         餐桌编号         就餐人数        就餐日期       " << endl;
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
		cout << setw(130) <<"此餐桌最大可容："<<max_num<<"人就餐！"<<endl;
		getchar();
		getchar();
		Diancai();
	}

	Update_tables(tb_id, 1);
	cout << setw(130) << "                                                                        " << endl;
	cout << setw(130) << "                       请输入你要选择点的菜品名称                       " << endl;
	cout << setw(130) << "                                                                        " << endl;
	char menu_name[100];
	double total_price = 0;
	char c;
	int temp = 17;
	gotoxy(150, 41);
	cout << "点菜完成按ESC完成订单!" << endl;
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
				cout << "菜目中没有此菜单！" << endl;
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
			cout << "订单创建成功，按任意键返回上级页面" << endl;
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

	// 带参数的SQL语句, :1表示id, :2表示name
	char sql[512] ="SELECT * FROM orders WHERE CUST_PAY=0";

	// 初始化SQL Statement对象
	rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if(rc != SQLITE_OK)
	{
		printf("failed to prepare: %s \n", sqlite3_errmsg(db));
		return;
	}

	// 执行SQL
	system ("cls");
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << setw(130) << "════════════════════════════════════" << endl;
	cout << setw(130) << "                                                                        " << endl;
	cout << setw(130) << "  订单编号        餐桌编号     就餐人数      消费金额       就餐日期    " << endl;
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
	cout << "按ESC返回上一级页面!" << endl;
	// 销毁Statement对象
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
    cout << setw(130) << "════════════════════════════════════" << endl;
	cout << setw(130) << "                                                                        " << endl;
	cout << setw(130) << "                                                                        " << endl;
	cout << setw(130) << "      请输入要结账的订单编号                   请输入客人付款           " << endl;
	cout << setw(130) << "                                                                        " << endl;
	char c;
	int num;
	double money;
	int temp = 13;
	gotoxy(150, 41);
	cout << "按ESC返回上一级页面!" << endl;
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
				cout<<setw(130) <<"付款不足！"<<endl;
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
    cout << setw(123) << "═════════════════════════════════" << endl;
	cout << setw(130) << "                                                                        " << endl;
	cout << setw(130) << "          请输入要添加的桌台的编号          桌台容纳的人数              " << endl;
	cout << setw(130) << "                                                                        " << endl;
	cout << setw(130) << "                                                                        " << endl;
	int tmp, temp_peo;
	int temp = 13;
	char c;
	gotoxy(150, 41);
	cout << "按ESC返回上一级页面!" << endl;
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
    cout << setw(123) << "═════════════════════════════════" << endl;
	cout << setw(130) << "                                                                        " << endl;
	cout << setw(130) << "                        请输入要删除的桌子编号                          " << endl;
	cout << setw(130) << "                                                                        " << endl;
	cout << setw(130) << "                                                                        " << endl;
	float price;
	int num;
	int temp = 12;
	char c;
	gotoxy(150, 41);
	cout << "按ESC返回上一级页面!" << endl;
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
    cout << setw(110) << "╭══════════════════╮" << endl;
    cout << setw(110) << "║                                    ║" << endl;
    cout << setw(110) << "║           查看总订单(1)：          ║" << endl;
    cout << setw(110) << "║                                    ║" << endl;
    cout << setw(110) << "║           查看日营业(2)：          ║" << endl;
    cout << setw(110) << "║                                    ║" << endl;
    cout << setw(110) << "║           查看月营业(3)：          ║" << endl;
    cout << setw(110) << "║                                    ║" << endl;
    cout << setw(110) << "║           返回菜单(4)：            ║" << endl;
    cout << setw(110) << "║                                    ║" << endl;
    cout << setw(110) << "╰══════════════════╯" << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << setw(100) << "请输入您接下来的操作(1-4)：";
	int x;
	char temp[100];
	cin >> x;
	if(x == 1)
		Select_allorders();
	if(x == 2)
	{
		cout << setw(94) << "请输入您要查询的日期:";
		cin >> temp;
			Select_orders_day(temp);
	}
	if(x == 3)
	{
		cout << setw(94) << "请输入您要查询的月份:";
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

	// 初始化SQL Statement对象
	rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if(rc != SQLITE_OK)
	{
		printf("failed to prepare: %s \n", sqlite3_errmsg(db));
		return;
	}

	// 执行SQL
	system ("cls");
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << setw(140) << "════════════════════════════════════════════" << endl;
	cout << endl;
	cout << setw(140) << "   订单编号     餐桌编号     就餐人数     消费金额     实付款     找零     创建日期     " << endl;
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

	// 带参数的SQL语句, :1表示id, :2表示name
	char sql[512];
	sprintf(sql,
		"SELECT * FROM orders WHERE DATETIME ="
		"('%s')"
		,datetime
		);

	// 初始化SQL Statement对象
	rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if(rc != SQLITE_OK)
	{
		printf("failed to prepare: %s \n", sqlite3_errmsg(db));
		return;
	}

	double sum = 0;
	// 执行SQL
	system ("cls");
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << setw(140) << "════════════════════════════════════════════" << endl;
	cout << endl;
	cout << setw(140) << "   订单编号     餐桌编号     就餐人数     消费金额     实付款     找零     创建日期     " << endl;
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

	// 销毁Statement对象
	sqlite3_finalize(stmt);
	gotoxy(150, 40);
	cout << "今日的营业额为：" << sum << endl;
	gotoxy(150, 41);
	cout << "按ESC返回上一级页面!" << endl;
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

	// 带参数的SQL语句, :1表示id, :2表示name
	char sql[512];
	sprintf(sql,
		"SELECT * FROM orders WHERE DATETIME LIKE '"
		"%s-%%'"
		,datetime
		);
	//cout<<sql<<endl;

	// 初始化SQL Statement对象
	rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if(rc != SQLITE_OK)
	{
		printf("failed to prepare: %s \n", sqlite3_errmsg(db));
		return;
	}
	double sum = 0;
	// 执行SQL
	system ("cls");
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << setw(140) << "════════════════════════════════════════════" << endl;
	cout << endl;
	cout << setw(140) << "   订单编号     餐桌编号     就餐人数     消费金额     实付款     找零     创建日期     " << endl;
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

	// 销毁Statement对象
	sqlite3_finalize(stmt);
	gotoxy(150, 40);
	cout << "本月的营业额为：" << sum << endl;
	gotoxy(150, 41);
	cout << "按ESC返回上一级页面!" << endl;
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
    cout << setw(117) << "╭═════════════════════════════╮" << endl;
    cout << setw(117) << "║                                                          ║" << endl;
    cout << setw(117) << "║   编号          姓名            性别           电话      ║" << endl;
    cout << setw(117) << "║                                                          ║" << endl;
    cout << setw(57) << "║";
    while(i < s)
    {
        if((i + 1) % 4 != 0 || i == 0)
            cout << setw(6) << temp[i] << "         ";
        else
        {
            cout << temp[i] << "  ║" << endl;
            if(i != s - 1)
            cout << setw(57) << "║";
        }
        i++;
    }
    cout << setw(117) << "║                                                          ║" << endl;
    cout << setw(117) << "╰═════════════════════════════╯" << endl;
    gotoxy(64, 21);
    cout << "添加(1)     修改(2)     删除(3)     返回(4)";
    gotoxy(75, 24);
    cout << "请输入您的操作(1-4)：";
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
    cout << setw(117) << "╭═════════════════════════════╮" << endl;
    cout << setw(117) << "║                                                          ║" << endl;
    cout << setw(117) << "║     请输入添加的餐厅人员的编号、姓名、性别、电话：       ║" << endl;
    cout << setw(117) << "║                                                          ║" << endl;
    cout << setw(117) << "║   编号          姓名            性别           电话      ║" << endl;
    cout << setw(117) << "║                                                          ║" << endl;
    cout << setw(117) << "║                                                          ║" << endl;
    cout << setw(117) << "║                                                          ║" << endl;
    cout << setw(117) << "║                                                          ║" << endl;
    cout << setw(117) << "║                                                          ║" << endl;
    cout << setw(117) << "║                                                          ║" << endl;
    cout << setw(117) << "║                                                          ║" << endl;
    cout << setw(117) << "║                                                          ║" << endl;
    cout << setw(117) << "║                                                          ║" << endl;
    cout << setw(117) << "║                                                          ║" << endl;
    cout << setw(117) << "║                                                          ║" << endl;
    cout << setw(117) << "║                                                          ║" << endl;
    cout << setw(117) << "║                                                          ║" << endl;
    cout << setw(117) << "╰═════════════════════════════╯" << endl;
    ofstream outfile("Personnel.dat",ios::app);
    if(!outfile)
    {
        cerr << "open error!" << endl;
        exit(1);
    }
	gotoxy(150, 41);
	cout << "按ESC返回上一级页面!" << endl;
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
    cout << setw(117) << "╭═════════════════════════════╮" << endl;
    cout << setw(117) << "║                                                          ║" << endl;
    cout << setw(117) << "║     请输入修改的餐厅人员的编号、姓名、性别、电话：       ║" << endl;
    cout << setw(117) << "║                                                          ║" << endl;
    cout << setw(117) << "║   编号          姓名            性别           电话      ║" << endl;
    cout << setw(117) << "║                                                          ║" << endl;
    cout << setw(117) << "║                                                          ║" << endl;
    cout << setw(117) << "║                                                          ║" << endl;
    cout << setw(117) << "║                                                          ║" << endl;
    cout << setw(117) << "║                                                          ║" << endl;
    cout << setw(117) << "║                                                          ║" << endl;
    cout << setw(117) << "║                                                          ║" << endl;
    cout << setw(117) << "║                                                          ║" << endl;
    cout << setw(117) << "║                                                          ║" << endl;
    cout << setw(117) << "║                                                          ║" << endl;
    cout << setw(117) << "║                                                          ║" << endl;
    cout << setw(117) << "║                                                          ║" << endl;
    cout << setw(117) << "║                                                          ║" << endl;
    cout << setw(117) << "╰═════════════════════════════╯" << endl;
    char c, tempper[100][100];
    char tempnum[100], tempname[100], tempsex[100], temptel[100];
    int temp = 10;
	gotoxy(150, 41);
	cout << "按ESC返回上一级页面!" << endl;
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
    cout << setw(110) << "╭══════════════════╮" << endl;
    cout << setw(110) << "║                                    ║" << endl;
    cout << setw(110) << "║         请输入删除的员工编号       ║" << endl;
    cout << setw(110) << "║                                    ║" << endl;
    cout << setw(110) << "║              员工编号              ║" << endl;
    cout << setw(110) << "║                                    ║" << endl;
    cout << setw(110) << "║                                    ║" << endl;
    cout << setw(110) << "║                                    ║" << endl;
    cout << setw(110) << "║                                    ║" << endl;
    cout << setw(110) << "║                                    ║" << endl;
    cout << setw(110) << "║                                    ║" << endl;
    cout << setw(110) << "║                                    ║" << endl;
    cout << setw(110) << "║                                    ║" << endl;
    cout << setw(110) << "║                                    ║" << endl;
    cout << setw(110) << "║                                    ║" << endl;
    cout << setw(110) << "║                                    ║" << endl;
    cout << setw(110) << "║                                    ║" << endl;
    cout << setw(110) << "║                                    ║" << endl;
    cout << setw(110) << "╰══════════════════╯" << endl;
    char c, tempstr[100][100], num[100];
	gotoxy(150, 41);
	cout << "按ESC返回上一级页面!" << endl;
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



