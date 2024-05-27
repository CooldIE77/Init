#pragma once
#include<vector>
#include"StuInfo.h"
#define SQL_MAX 256
class SQLInterface
{
public:
	MYSQL_RES* res;
	MYSQL_ROW row;
	MYSQL m_sqlCon; //�������ݿ�
	char sql[SQL_MAX];

	bool Connect_MySQL();
	vector<StuInfo> SQLInterface::GetInfo();
	bool AddInfo(StuInfo Info);  //���ѧ����Ϣ
	bool DelInfo(StuInfo Info);  //ɾ��ѧ����Ϣ
	bool UpdateInfo(StuInfo old_Info, StuInfo new_Info);  //�޸�ѧ����Ϣ
	vector<StuInfo> FindInfo(CString name);    //������Ϣ
	void Close_MySQL();  //�ر����ݿ�
};

