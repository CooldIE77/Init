#include "pch.h"
#include "SQLInterface.h"

bool SQLInterface::Connect_MySQL()
{
	mysql_init(&m_sqlCon);

	if (!mysql_real_connect(&m_sqlCon, "localhost",
		"root", "dong20040824", "stuinfo", 3306, NULL, 0)) {
		AfxMessageBox("����ʧ��");
		return false;
	}
	else {
		AfxMessageBox("���ӳɹ�");
		mysql_query(&m_sqlCon, "SET NAMES 'GB2312'"); //m_sqlCon��MYSQL����
	}
	return true;

}

vector<StuInfo> SQLInterface::GetInfo()
{
	vector<StuInfo> Info;
	snprintf(sql, SQL_MAX, "select *from info1");
	//��ѯ����
	int ret = mysql_real_query(&m_sqlCon, sql, (unsigned long)strlen(sql));
	//�жϽ��
	if (ret) {
		AfxMessageBox("��ѯʧ��");
		return Info;
	}
	//��ȡ�����
	res = mysql_store_result(&m_sqlCon);
	//��ȡ��ѯ����һ������
	while (row = mysql_fetch_row(res)) {
		StuInfo stu = StuInfo(row[0], row[1], atoi(row[2]), stod(row[3]), stod(row[4]), stod(row[5]));
		Info.push_back(stu);

	}
	mysql_free_result(res);
	return Info;
}

bool SQLInterface::AddInfo(StuInfo Info)
{
	snprintf(sql, SQL_MAX, "INSERT INTO info1 VALUES('%s','%s','%d',%lf,'%lf','%lf')",
		Info.s_name.c_str(), Info.s_sex.c_str(), Info.s_class_,
		Info.s_score1, Info.s_score2,Info.s_score3);

	//��ѯ����
	int ret = mysql_real_query(&m_sqlCon, sql, (unsigned long)strlen(sql));
	//�жϽ��
	if (ret) {
		AfxMessageBox("���ʧ��");
		return false;
	}
	return true;

}

bool SQLInterface::DelInfo(StuInfo Info)
{
	snprintf(sql, SQL_MAX, "DELETE FROM info1 WHERE name='%s';", Info.s_name.c_str());
	//��ѯ����
	int ret = mysql_real_query(&m_sqlCon, sql, (unsigned long)strlen(sql));
	//�жϽ��
	if (ret) {
		AfxMessageBox("ɾ��ʧ��");
		return false;
	}
	return true;

}

bool SQLInterface::UpdateInfo(StuInfo old_Info, StuInfo new_Info)
{
	snprintf(sql, SQL_MAX, "UPDATE info1 set name='%s',sex='%s',class_=%d,score1=%lf,score2=%lf,score3=%lf WHERE name='%s';"
		, new_Info.s_name.c_str(),new_Info.s_sex.c_str(), new_Info.s_class_, new_Info.s_score1, new_Info.s_score2, new_Info.s_score3,old_Info.s_name.c_str());
	//��ѯ����
	int ret = mysql_real_query(&m_sqlCon, sql, (unsigned long)strlen(sql));
	//�жϽ��
	if (ret) {
		AfxMessageBox("�޸�ʧ��");
		return false;
	}
	return true;
}

vector<StuInfo> SQLInterface::FindInfo(CString name)
{
	vector<StuInfo> result;
	snprintf(sql, SQL_MAX, "SELECT * FROM info1 WHERE name='%s';",name);
	//��ѯ����
	int ret = mysql_real_query(&m_sqlCon, sql, (unsigned long)strlen(sql));
	//�жϽ��
	if (ret) {
		AfxMessageBox("��ѯʧ��");
		return result;
	}
	//��ȡ�����
	res = mysql_store_result(&m_sqlCon);
	//��ȡ��ѯ����һ������
	while (row = mysql_fetch_row(res)) {
		StuInfo stu = StuInfo(row[0], row[1], atoi(row[2]), stod(row[3]), stod(row[4]), stod(row[5]));
		result.push_back(stu);

	}
	mysql_free_result(res);
	return result;
}

void SQLInterface::Close_MySQL()
{
	mysql_close(&m_sqlCon);
}


