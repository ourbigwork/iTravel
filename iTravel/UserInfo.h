#pragma once
#ifndef USER_INFO
#define USER_INFO
#include<iostream>
#include "pch.h"
#include "FileHelper.h"
using namespace std;
struct User_like {
	std::string Where;
	std::string What;	
};
istream& operator>>(istream& in, User_like&p)
	{
		in >> p.Where>>p.What;             //��
		return in;
	}
ostream& operator<<(ostream& out, const User_like& p)
	{
	out << p.Where << std::endl;
	out << p.What << std::endl;            //д,һ��Ҫ���з�������
	return out;
	}
User_like like;
User_like readd;
struct Key_Data {
	std::string nicknamee;//�û���
	std::string phonee;//�绰����
	std::string passwordd;//����
};
struct FeedbackWords {
	//�û�����
	std::string words;
	std::string customername;
};
istream& operator>>(istream& in, FeedbackWords&p)
{
	in >> p.customername >> p.words;             //du
	return in;
}
ostream& operator<<(ostream& out, const FeedbackWords& p)
{
	out << p.customername << std::endl; 
	out<< p.words << std::endl;           //xie
	return out;
}
FeedbackWords myfeedback;
struct Replywords {
	//����Ա����
	std::string customername;
	std::string words;
};
istream& operator>>(istream& in, Replywords&p)
{
	in >> p.customername >> p.words;             //du
	return in;
}
ostream& operator<<(ostream& out, const Replywords& p)
{
	out << p.customername << std::endl;
	out << p.words << std::endl;           //xie
	return out;
}
FeedbackWords myreply;
//ʹ������
class User {
public:
	User(const User&) = delete;         //�⼸����ɶ����
	User(const User&&) = delete;
	User(const std::string& filename);
	void Login();
	void Show();
	void Regist();
	void Change();
	void Logout();
	std::string getUser()const { return Username; }
protected:
	std::string Phone, Username, password;
	int type;//	1 - ��ͨ�û���2  - ����Ա
	userDataFileHelper file;
};
//�û���
class Customer :public User{
public:
	void Regist();  //������ʼ���ļ�
	void show();         //������Ϣ��ʾ
	void ilike();        //������Ը��,Ҫ���ĵ�����������ӵĶ���ת���ɴ���д���ĵ�
	void showlike();     //��ʾ��Ը����Ҫ���ĵ����������ĵ���Ĵ��Ŷ�ȡ����,��ɿ��ӵ�
	void comment();      //�������ۣ�ҲҪ���ĵ���������д�Ķ��������ĵ�
	void feedback();     //�����Ա��������
	void read();         //�鿴����Ա�Ļظ�
protected:
	std::string preferencef, preferencep;
};
//����Ա��
class Admin :public User{
public:
	void set();
	void changeinformation();    //�޸ľ�����ʳ��Ϣ
	void reply();                //�����û�����������,���Ķ�һ���ĵ���֮��Ѵ�����д����һ���ĵ�reply
};
#endif