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
	console << "����:" << endl;
	while (true) {
		_password = console.InputPassword();
		if (password != _password) {
			console << "����������������룡" << endl;
		}
		else
			break;
	}
	console << "��½�ɹ���" << endl;
	this->password = password;
	this->Phone = phone;
	this->Username = username;
	return;
}
void User::Show() {
	std::console << "�û���: " << Username << std::endl << "�ֻ�����: " << Phone << std::endl;
}
void User::Regist() {
	using std::console;
	using std::endl;
	using std::string;
	using std::cin;
	console.ClearScreen();
	console << "ע��" << endl;
	string password1, password2, name;
	string phone1, phone2;
	console << "�������û�����" << endl;
	while (cin >> name) {
		if (name.empty()) {
			console << "�û�������Ϊ�գ�" << endl;
			cin.get();
			continue;
		}
		file.findUser(name, password2, phone2);
		if (!password2.empty()) {
			console << "���û��ѱ�ע�ᣬ����������" << endl;
			continue;
		}
		else {
			password2.clear();
			break;
		}
	}
	console << "������绰���룺" << endl;
	while (cin >> phone1) {
		if (phone1.length() != 11) {
			console << "���볤���������֤����������" << endl;
			cin.get();
			continue;
		}
		else break;
	}
	console << "���������룺" << endl;
	while (cin >> password1) {
		if (password1.empty()) {
			console << "���벻��Ϊ�գ�" << endl;
			cin.get();
		}else break;
	}
	console << "���ٴ��������룺" << endl;
	cin >> password2;
	while (password2 != password1) {
		console << "������������벻��ͬ,�ٴ��������룺" << endl;
		cin >> password2;
	}
	console << "ע��ɹ���" << endl;
	file.RegistUser(name, password1, phone1);
}
void User::Change() {
	using std::console;
	using std::endl;
	using std::string;
	using std::cin;
	console.ClearScreen();
	console << "�û�" << Username << "�޸ĸ�����Ϣ" << endl;
	string name = Username;
	string passwordcheck;
	string oldphone, oldpass;
	file.findUser(Username, oldpass, oldphone);
	int i = 3;
	console << "����������" << endl;
	cin >> passwordcheck;
	while (passwordcheck != oldpass) {
		if (!i) {
			console << "���볢�Դ������࣡" << endl;
			return;
		}
		console << "�����������������,ʣ�����" << --i << endl << "���������룺";
		cin >> passwordcheck;
	}
	string password1, password2;
	string phone;
	console << "������绰����:";
	cin >> phone;
	console << phone << endl;
	console << "���������루�������������գ���";
	password1 = console.InputPassword();
	if (password1.empty()) {
		console << "�޷���֤��ݣ�" << endl;
		return;
	}
	console << "���ٴ��������룺";
	password2 = console.InputPassword();
	while (password1 != password2) {
		console << "������������벻��ͬ,�ٴ��������룺";
		password2 = console.InputPassword();
	}
	file.revise(Username, phone, password1);
	password = password1;
	Phone = phone;
	console << "�޸ĳɹ���" << endl;
	console << "�޸ĺ����Ϣ��" << endl;
	console << "�û���" << Username << '\n' << "�ֻ��ţ�" << phone << '\n' << "���룺" << password1 << endl;
}