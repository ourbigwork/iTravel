#pragma once
#ifndef USER_INFO
#define USER_INFO
#include "pch.h"
#include "FileHelper.h"
struct User_like {
	std::string Where;
	std::string What;
};
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
struct Replywords {
	//����Ա����
	std::string customername;
	std::string words;
};
//�û���
class User {
public:
	User(const User&) = delete;
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
class Customer :public User{
public:
	Customer() = default;//Ĭ�Ϲ��캯��
	void show();         //������Ϣ��ʾ
	void ilike();        //������Ը��,Ҫ���ĵ�����������ӵĶ���ת���ɴ���д���ĵ�
	void showlike();     //��ʾ��Ը����Ҫ���ĵ����������ĵ���Ĵ��Ŷ�ȡ����,��ɿ��ӵ�
	void comment();      //�������ۣ�ҲҪ���ĵ���������д�Ķ��������ĵ�
	void feedback();     //�����Ա��������
	void read();         //�鿴����Ա�Ļظ�
protected:
	std::string preferencef, preferencep;
	//int experience;   //�������������о������
};
class Admin :public User{
public:
	void set();
	void changeinformation();    //�޸ľ�����ʳ��Ϣ
	void reply();                //�����û�����������,���Ķ�һ���ĵ���֮��Ѵ�����д����һ���ĵ�reply
};
#endif