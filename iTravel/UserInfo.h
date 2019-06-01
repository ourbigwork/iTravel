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
	std::string getUser()const { return Username; }
	//void VerifyPassword();
	//std::string lookupPassword();
protected:
	std::string Phone, Username, password;
	userDataFileHelper file;
};

#endif