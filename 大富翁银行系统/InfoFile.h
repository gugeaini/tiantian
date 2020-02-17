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
	int id;			//����id
	string name;	//�û���
	int price;		//�û����
	int num;        //�û�����
	int quota;		//�û����ö��
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
	void Addline(CString name, int num, int price);

	list<msg> ls;	//�洢��Ʒ����
	int num;			//������¼��Ʒ����
};

