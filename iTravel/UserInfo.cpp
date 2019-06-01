#include "pch.h"
#include "UserInfo.h"
#include "CConsole.h"
#include "constStr.h"
User::User(const std::string & Datafilename) {
	file.ReopenFile(Datafilename);
}
void User::Login() {
	using std::console;
	using std::endl;
	using std::string;
	using std::cin;
	console.ClearScreen();
	console << tUser << endl;
	string username, phone, password;
	string _password;
	cin >> username;
	cin.get();
	console << username << endl;
	file.findUser(username, password, phone);
	if (password.empty()) {
		console << tInvaildUser << endl;
		return;
	}
	console << "密码:" << endl;
	while (true) {
		_password = console.InputPassword();
		if (password != _password) {
			console << "密码错误，请重新输入！" << endl;
		}
		else
			break;
	}
	console << "登陆成功！" << endl;
	this->password = password;
	this->Phone = phone;
	this->Username = username;
	return;
}
void User::Show() {
	std::console << "用户名: " << Username << std::endl << "手机号码: " << Phone << std::endl;
}
void User::Regist() {
	using std::console;
	using std::endl;
	using std::string;
	using std::cin;
	console.ClearScreen();
	console << "注册" << endl;
	string password1, password2, name;
	string phone1, phone2;
	console << "请输入用户名：" << endl;
	while (cin >> name) {
		if (name.empty()) {
			console << "用户名不能为空！" << endl;
			cin.get();
			continue;
		}
		file.findUser(name, password2, phone2);
		if (!password2.empty()) {
			console << "该用户已被注册，请重新输入" << endl;
			continue;
		}
		else {
			password2.clear();
			break;
		}
	}
	console << "请输入电话号码：" << endl;
	while (cin >> phone1) {
		if (phone1.length() != 11) {
			console << "号码长度有误，请查证后重新输入" << endl;
			cin.get();
			continue;
		}
		else break;
	}
	console << "请输入密码：" << endl;
	while (cin >> password1) {
		if (password1.empty()) {
			console << "密码不能为空！" << endl;
			cin.get();
		}else break;
	}
	console << "请再次输入密码：" << endl;
	cin >> password2;
	while (password2 != password1) {
		console << "两次输入的密码不相同,再次输入密码：" << endl;
		cin >> password2;
	}
	console << "注册成功！" << endl;
	file.RegistUser(name, password1, phone1);
}
void User::Change() {
	using std::console;
	using std::endl;
	using std::string;
	using std::cin;
	console.ClearScreen();
	console << "用户" << Username << "修改个人信息" << endl;
	string name = Username;
	string passwordcheck;
	string oldphone, oldpass;
	file.findUser(Username, oldpass, oldphone);
	int i = 3;
	console << "请输入密码" << endl;
	cin >> passwordcheck;
	while (passwordcheck != oldpass) {
		if (!i) {
			console << "密码尝试次数过多！" << endl;
			return;
		}
		console << "密码错误，请重新输入,剩余次数" << --i << endl << "请输入密码：";
		cin >> passwordcheck;
	}
	string password1, password2;
	string phone;
	console << "请输入电话号码:";
	cin >> phone;
	console << phone << endl;
	console << "请输入密码（忘记密码请留空）：";
	password1 = console.InputPassword();
	if (password1.empty()) {
		console << "无法验证身份！" << endl;
		return;
	}
	console << "请再次输入密码：";
	password2 = console.InputPassword();
	while (password1 != password2) {
		console << "两次输入的密码不相同,再次输入密码：";
		password2 = console.InputPassword();
	}
	file.revise(Username, phone, password1);
	password = password1;
	Phone = phone;
	console << "修改成功！" << endl;
	console << "修改后的信息：" << endl;
	console << "用户名" << Username << '\n' << "手机号：" << phone << '\n' << "密码：" << password1 << endl;
}