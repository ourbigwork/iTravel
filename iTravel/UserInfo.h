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
	std::string nicknamee;//用户名
	std::string phonee;//电话号码
	std::string passwordd;//密码

};
struct FeedbackWords {
	//用户反馈
	std::string words;
	std::string customername;
};
struct Replywords {
	//管理员回信
	std::string customername;
	std::string words;
};
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
	std::string getUser()const { return Username; }
	//void VerifyPassword();
	//std::string lookupPassword();
protected:
	std::string Phone, Username, password;
	userDataFileHelper file;
};

#endif