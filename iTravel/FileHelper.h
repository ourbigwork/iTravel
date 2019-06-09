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
	std::string TimeUTCNow() {
		SYSTEMTIME sys = __Localtimenow();
		const char* _week[]{ "Sun" ,"Mon","Tue","Wed","Thu","Fri","Sat",}, 
			*_month[]{ "Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec" };
		char buffer[255]{0};
		//Last login: Mon May 20 21:38:44 2019 from ...
		sprintf(buffer,"%s %s %d %d:%d:%d %d", _week[sys.wDayOfWeek], _month[sys.wMonth - 1],
			sys.wDay,sys.wHour,sys.wMinute,sys.wSecond,sys.wYear);
		return buffer;
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