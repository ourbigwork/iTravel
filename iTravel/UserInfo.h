#pragma once
#ifndef USER_INFO
#define USER_INFO
#include "pch.h"
#include "FileHelper.h"
struct User_like {
	std::string Where;
	std::string What;
	friend std::istream& operator>>(std::istream& in, User_like&p) {
		in >> p.Where >> p.What;             //��
		return in;
	}
	friend std::ostream& operator<<(std::ostream& out, const User_like& p) {
		out << p.Where << std::endl;
		out << p.What << std::endl;            //д,һ��Ҫ���з�������
		return out;
	}
};
extern User_like like;
extern User_like readd;
struct Key_Data {
	std::string nicknamee;//�û���
	std::string phonee;//�绰����
	std::string passwordd;//����

};
struct FeedbackWords {
	//�û�����
	std::string words;
	std::string customername;
	friend std::istream& operator>>(std::istream& in, FeedbackWords&p){
		in >> p.customername >> p.words;             
		return in;
	}
	friend std::ostream& operator<<(std::ostream& out, const FeedbackWords& p){
		out << p.customername << std::endl;
		out << p.words << std::endl;           
		return out;
	}
};
extern FeedbackWords myfeedback;

struct Replywords {
	//����Ա����
	std::string customername;
	std::string words;
	friend std::istream& operator>>(std::istream& in, Replywords&p)
	{
		in >> p.customername >> p.words;             
		return in;
	}
	friend std::ostream& operator<<(std::ostream& out, const Replywords& p)
	{
		out << p.customername << std::endl;
		out << p.words << std::endl;          
		return out;
	}
};
extern Replywords myreply;

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
class Customer :public User {
public:
	Customer() = default;//Ĭ�Ϲ��캯��
	void show();         //������Ϣ��ʾ
	void judgelikecin(User_like&p);//����
	void ilike();        //������Ը��,Ҫ���ĵ�����������ӵĶ���ת���ɴ���д���ĵ�
	void showlike();     //��ʾ��Ը����Ҫ���ĵ����������ĵ���Ĵ��Ŷ�ȡ����,��ɿ��ӵ�
	void comment();      //�������ۣ�ҲҪ���ĵ���������д�Ķ��������ĵ�
	void feedback();     //�����Ա��������
	void read();         //�鿴����Ա�Ļظ�
protected:
	std::string preferencef, preferencep;
};
class Admin :public User {
public:
	void set();
	void changeinformation();    //�޸ľ�����ʳ��Ϣ
	void reply();                //�����û�����������,���Ķ�һ���ĵ���֮��Ѵ�����д����һ���ĵ�reply
};
#endif