#pragma once
#ifndef FILE_HELPER
#define FILE_HELPER
#include "pch.h"
//文件助手类
class userDataFileHelper {
public:
	userDataFileHelper();
	~userDataFileHelper() = default;
	void findUser(const std::string&username, std::string& password, std::string& phone, int&);
	void revise(const std::string& username, const std::string&newPhone, const std::string& password, int type);
	void closeFile();
	void ReopenFile(const std::string&);
	void RegistUser(const std::string&, const std::string&, const std::string&, int&);
	std::string getFilename()const;
	FILE* getFile()const;
	std::string TimeUTCNow(){
		SYSTEMTIME sys = __Localtimenow();

	}
private:
	FILE* fp;
	struct User {
		std::string name;
		std::string password;
		std::string phone;
		int type = 1;
	};
	std::map<std::string, User> mp;
	std::string Filename;
	std::string __format(const char*, ...);
	void __loadData();
	SYSTEMTIME __Localtimenow();
};
#endif