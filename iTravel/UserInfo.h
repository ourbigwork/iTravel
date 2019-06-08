#pragma once
#ifndef USER_INFO
#define USER_INFO
#include "pch.h"
#include "FileHelper.h"
struct User_like {
	std::string Where;
	std::string What;
	friend std::istream& operator>>(std::istream& in, User_like&p) {
		in >> p.Where >> p.What;             //读
		return in;
	}
	friend std::ostream& operator<<(std::ostream& out, const User_like& p) {
		out << p.Where << std::endl;
		out << p.What << std::endl;            //写,一定要换行符！！！
		return out;
	}
};
extern User_like like;
extern User_like readd;
struct Key_Data {
	std::string nicknamee;//用户名
	std::string phonee;//电话号码
	std::string passwordd;//密码

};
struct FeedbackWords {
	//用户反馈
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
	//管理员回信
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

//用户类
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
	int type;//	1 - 普通用户；2  - 管理员
	userDataFileHelper file;
};
class Customer :public User {
public:
	Customer() = default;//默认构造函数
	void show();         //个人信息显示
	void judgelikecin(User_like&p);//查重
	void ilike();        //加入心愿单,要对文档操作，把添加的东西转换成代号写入文档
	void showlike();     //显示心愿单，要对文档操作，把文档里的代号读取出来,变成可视的
	void comment();      //发表评论，也要对文档操作。把写的东西存入文档
	void feedback();     //向管理员反馈问题
	void read();         //查看管理员的回复
protected:
	std::string preferencef, preferencep;
};
class Admin :public User {
public:
	void set();
	void changeinformation();    //修改景点美食信息
	void reply();                //处理用户反馈的问题,先阅读一个文档，之后把处理结果写入另一个文档reply
};
#endif