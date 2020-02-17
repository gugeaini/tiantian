#pragma once

#include <list>
#include <fstream>
#include <iostream>
#include <string>
#include"framework.h"

#define _F_LOGIN "./login.ini"
#define _F_STOCK "./stock.txt"

using namespace std;

struct msg
{
	int id;			//��Ʒid
	string name;	//��Ʒ��
	int price;		//��Ʒ�۸�
	int num;		//��Ʒ����
};	

class CInfoFile
{
public:
	CInfoFile();
	~CInfoFile();

	//��ȡ��¼��Ϣ
	void ReadLogin(CString &name, CString &pwd);

	//�޸�����
	void WritePwd(char* name, char* pwd);

	//��ȡ��Ʒ����
	void ReadDocline();

	//��Ʒд���ļ�
	void WriteDocline();

	//�������Ʒ
	void Addline(int id, CString name, int num, int price);

	//ɾ����Ʒ
	void Dleline(CString name);

	list<msg> ls;	//�洢��Ʒ����
	int num;			//������¼��Ʒ����
};

