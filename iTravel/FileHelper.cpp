#include "pch.h"
#include "shlwapi.h"
#include "FileHelper.h"
#pragma comment(lib,"Shlwapi.lib")
//数据格式 --  userinfo.dat
/*
	权限代号*
		1 - 普通用户
		2 - 管理员
	权限代号 用户名 手机号 密码
*/
userDataFileHelper::userDataFileHelper() {
}
std::string userDataFileHelper::__format(const char* format, ...) {
	va_list args;
	va_start(args, format);
	char buffer[205]{ 0 };
	sprintf(buffer, format, args);
	va_end(args);
	return std::string(buffer);
}
void userDataFileHelper::__loadData() {
	ReopenFile(Filename);
	if (!fp) {
		OutputDebugStringA("[Error]Invaild File!\n");
		return;
	}
	rewind(fp);
	int type;
	char user[25]{ 0 }, phone[25]{ 0 }, password[25]{ 0 };
	while (~fscanf(fp, "%d %s %s %s", &type, user, phone, password)) {
		User us;
		us.name = user;
		us.password = password;
		us.phone = phone;
		us.type = type;
		mp.insert(std::make_pair(user, us));
	}
	fclose(fp);
}
SYSTEMTIME userDataFileHelper::__Localtimenow(){
	SYSTEMTIME lptime;
	GetLocalTime(&lptime);
	return lptime;
}
void userDataFileHelper::findUser(const std::string& username, std::string & password, std::string & phone, int& type) {
	__loadData(); 
	std::map<std::string, User>::iterator iter = mp.find(username);
	if (iter == mp.end()) {
		return;
	}
	password = iter->second.password;
	phone = iter->second.phone;
	type = iter->second.type;
	return;
}
void userDataFileHelper::revise(const std::string &username, const std::string & newPhone, const std::string &newPassword, int type) {
	ReopenFile(Filename);
	rewind(fp);
	char user[25]{ 0 }, phone[25]{ 0 }, password[25]{ 0 };
	int ttype;
	std::vector<User>users;
	//为清除原有的一行，首先把除那一行的所有信息读出来，然后清空原来的文件
	while (~fscanf(fp, "%d %s %s %s", &ttype, user, phone, password)) {
		User us;
		if (user != username) {
			us.name = user;
			us.phone = phone;
			us.password = password;
			users.push_back(us);
		}
	}
	//重新关闭并打开　
	fclose(fp);
	//清空
	fopen_s(&fp, Filename.c_str(), "w");
	fclose(fp);
	//以原来模式打开
	fopen_s(&fp, Filename.c_str(), "a+");
	for (int i = 0; i < users.size(); ++i) {
		fprintf(fp, "%d %s %s %s\n", type, users[i].name.c_str(), users[i].phone.c_str(), users[i].password.c_str());
	}
	users.clear();
	fprintf(fp, "%d %s %s %s\n", type, username.c_str(), newPhone.c_str(), newPassword.c_str());
	auto iter = mp.find(username);
	iter->second.phone = newPhone;
	iter->second.password = newPassword;
	fclose(fp);
}
void userDataFileHelper::closeFile() {
	fclose(fp);
	fp = nullptr;
	Filename.clear();
}
void userDataFileHelper::ReopenFile(const std::string& filename) {
	std::string Errorinfo;
	if (fp)
		fclose(fp);
	if (!PathFileExistsA(filename.c_str()))
		OutputDebugStringA(__format("[Warning]File %s not existed!\n", filename.c_str()).c_str());
	errno_t status =
		fopen_s(&fp, filename.c_str(), "a+");
	if (status) {
		Errorinfo = __format("[Error]Failed to open %s with %d", filename.c_str(), status);
		throw std::runtime_error(Errorinfo);
	}
	Filename = filename;
}
void userDataFileHelper::RegistUser(const std::string &username, const std::string &password, const std::string &phone, int& type) {
	ReopenFile(Filename);
	char buff[1024]{ 0 };
	sprintf(buff, "%d %s %s %s\n", type, username.data(), phone.data(), password.data());
	//fprintf(fp,"%s",buff);
	fprintf(fp, "%s", buff);
	fclose(fp);
	bool res = mp.insert(std::make_pair(username, User{ username, password,phone,type })).second;
	if (!res)
		OutputDebugStringA("Failed to insert a new User!");
}
std::string userDataFileHelper::getFilename()const {
	return Filename;
}
FILE* userDataFileHelper::getFile()const {
	return fp;
}