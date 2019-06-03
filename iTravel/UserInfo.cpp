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
	console << "用户名：";
	string username, phone, password;
	string _password;
	cin >> username;
	console << username << endl;
	int ttype;
	file.findUser(username, password, phone, ttype);
	while (password.empty()) {
		console << tInvaildUser;
		cin >> username;
		console << username << endl;
		file.findUser(username, password, phone, ttype);
	}
	console << "密码:";
	int i = 3;
	while (i) {
		_password = console.InputPassword();
		console << "*********" << endl;
		if (password != _password) {
			i--;
			if (!i) {
				console << "尝试次数过多！" << endl;
				return;
			}
			console << "密码错误，请重新输入：";
		}
		else {
			break;
		}
	}
	if (ttype == 2) {
		console << "欢迎您，管理员：" << username << "." << endl;
	}
	else
		console << "登陆成功！" << endl;
	//获得当前时间
	string time = file.TimeUTCNow();
	FILE* ptimeFile = fopen(".\\login", "a+");
	//读入之前的文件；
	char bLastTime[255]{ 0 };
	if (ptimeFile) {
		fscanf(ptimeFile, "%[^\n]%*c", bLastTime);//读取一行
		if (strlen(bLastTime)) {
			console << "上次登录：" << bLastTime << "." << endl;
		}
		else
			OutputDebugStringA("[Warning]Last login time file not found!");
		fclose(ptimeFile);
	}
	//清空之前的内容
	ptimeFile = fopen(".\\login", "w");
	if (ptimeFile) {
		fprintf(ptimeFile, "%s from %s", time.c_str(),username.c_str());
		fclose(ptimeFile);
	}
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
	int ttype;
	console.ClearScreen();
	console << "注册" << endl;
	string password1, password2, name;
	string phone1, phone2;
	console << "请输入用户名：";
	while (cin >> name) {
		console << name << endl;
		if (name.empty()) {
			console << "用户名不能为空！" << endl;
			cin.get();
			continue;
		}
		file.findUser(name, password2, phone2, ttype);
		if (!password2.empty()) {
			console << "该用户已被注册，请重新输入" << endl << "请输入用户名：";
			continue;
		}
		else {
			password2.clear();
			break;
		}
	}
	console << "请输入电话号码：";
	while (cin >> phone1) {
		console << phone1 << endl;
		if (phone1.length() != 11) {
			console << "号码长度有误，请查证后重新输入" << endl << "请输入电话号码：";
			cin.get();
			continue;
		}
		else {
			bool f = false;
			for (auto x : phone1) {
				if (!isdigit(x)) {
					console << "号码必须全部是数字！" << endl;
					f = true;
					break;
				}
			}
			if (!f)
				break;
		}
	}
	console << "请输入密码（最多16位）：";
	while (true) {
		password1 = console.InputPassword();
		console << "*********" << endl;
		if (password1.empty()) {
			console << "密码不能为空！" << endl;
			cin.get();
		}
		else break;
	}
	console << "请再次输入密码：";
	password2 = console.InputPassword();
	console << "*********" << endl;
	while (password2 != password1) {
		console << "两次输入的密码不相同" << endl << "请再次输入密码：";
		password2 = console.InputPassword();
		console << "*********" << endl;
	}
	console << "注册成功！" << endl;
	int type = 1;
	//不提供注册管理员的接口
	file.RegistUser(name, password1, phone1, type);
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
	int type;
	file.findUser(Username, oldpass, oldphone, type);
	int i = 3;
	console << "请输入密码：";
	passwordcheck = console.InputPassword();
	console << "*********" << endl;
	while (passwordcheck != oldpass) {
		if (!i) {
			console << "密码尝试次数过多！" << endl;
			return;
		}
		console << "密码错误，请重新输入,剩余次数：" << --i << "次；" << endl << "请输入密码：";
		passwordcheck = console.InputPassword();
		console << "*********" << endl;
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
	file.revise(Username, phone, password1, type);
	password = password1;
	Phone = phone;
	console << "修改成功！" << endl;
	console << "修改后的信息：" << endl;
	console << "用户名" << Username << '\n' << "手机号：" << phone << '\n' << "密码：" << password1 << endl;
}

void User::Logout() {
	Phone.clear(), Username.clear(), password.clear();
	return;
}
//------------------------------------------------------------------------------------------------

void Customer::show() {
	using namespace std;
}

void Customer::ilike() {
	using namespace std;
}

void Customer::showlike() {
	using namespace std;
}

void Customer::comment() {
	using namespace std;
}

void Customer::feedback() {
	using namespace std;
}

void Customer::read() {
	using namespace std;
}
//------------------------------------------------------------------------------------------------
void Admin::set() {
	using namespace std;
}

void Admin::changeinformation() {
	using namespace std;
}

void Admin::reply() {
	using namespace std;
}
