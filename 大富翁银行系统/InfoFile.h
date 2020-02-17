#pragma once

#include <list>
#include <fstream>
#include <iostream>
#include <string>

#define _F_LOGIN "./login.ini"
#define _F_STOCK "./stock.txt"

using namespace std;

struct msg
{
	int id;			//银行id
	string name;	//用户名
	int price;		//用户存款
	int num;        //用户贷款
	int quota;		//用户信用额度
};	

class CInfoFile
{
public:
	CInfoFile();
	~CInfoFile();

	//读取登录信息
	void ReadLogin(CString &name, CString &pwd);

	//修改密码
	void WritePwd(char* name, char* pwd);

	//读取商品数据
	void ReadDocline();

	//商品写入文件
	void WriteDocline();

	//添加新商品
	void Addline(CString name, int num, int price);

	list<msg> ls;	//存储商品容器
	int num;			//用来记录商品个数
};

