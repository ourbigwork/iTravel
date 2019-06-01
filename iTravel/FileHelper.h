#pragma once
#ifndef FILE_HELPER
#define FILE_HELPER
#include "pch.h"
//文件助手类
class userDataFileHelper {
public:
	userDataFileHelper();
	~userDataFileHelper() = default;
	void findUser(const std::string&, std::string& password,std::string& phone);
	void revise(const std::string&,const std::string&,const std::string&);
	void closeFile();
	void ReopenFile(const std::string&);
	void RegistUser(const std::string&,const std::string&,const std::string&);
	std::string getFilename()const;
	FILE* getFile()const;
private:
	FILE* fp;
	struct User {
		std::string name;
		std::string password;
		std::string phone;
	};
	std::map<std::string, User> mp;
	std::string Filename;
	std::string __format(const char*, ...);
	void __loadData();
};
#endif