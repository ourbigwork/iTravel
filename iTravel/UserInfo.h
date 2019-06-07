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
		in >> p.Where>>p.What;             //读
		return in;
	}
ostream& operator<<(ostream& out, const User_like& p)
	{
	out << p.Where << std::endl;
	out << p.What << std::endl;            //写,一定要换行符！！！
	return out;
	}
User_like like;
User_like readd;
struct Key_Data {
	std::string nicknamee;//用户名
	std::string phonee;//电话号码
	std::string passwordd;//密码
};
struct FeedbackWords {
	//用户反馈
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
	//管理员回信
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
//使用者类
class User {
public:
	User(const User&) = delete;         //这几个是啥玩意
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
	int type;//	1 - 普通用户；2  - 管理员
	userDataFileHelper file;
};
//用户类
class Customer :public User{
public:
	void Regist();  //用来初始化文件
	void show();         //个人信息显示
	void ilike();        //加入心愿单,要对文档操作，把添加的东西转换成代号写入文档
	void showlike();     //显示心愿单，要对文档操作，把文档里的代号读取出来,变成可视的
	void comment();      //发表评论，也要对文档操作。把写的东西存入文档
	void feedback();     //向管理员反馈问题
	void read();         //查看管理员的回复
protected:
	std::string preferencef, preferencep;
};
//管理员类
class Admin :public User{
public:
	void set();
	void changeinformation();    //修改景点美食信息
	void reply();                //处理用户反馈的问题,先阅读一个文档，之后把处理结果写入另一个文档reply
};
#endif