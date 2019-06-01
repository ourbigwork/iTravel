#include "pch.h"
#include "constStr.h"
#include "CConsole.h"
using namespace std;
struct like {
	string where;    //什么地方的
	string what;    //什么东西
}likee;
struct keydata {
	string nicknamee;//用户名
	string phonee;//电话号码
	string passwordd;//密码
	string preferenceff;//保留
	string preferencepp;//保留
	friend istream& operator>>(istream& in, keydata &p) {
		in >> p.nicknamee >> p.phonee >> p.passwordd >> p.preferenceff >> p.preferencepp;
		return in;
	}
	friend ostream& operator<<(ostream& out, const keydata& p) {
		out << p.nicknamee << "\t" << p.phonee << "\t" << p.passwordd << "\t" << p.preferenceff;
		return out;
	}
}onepiece;
//const keydata mark{ "0","00000000000","0","0","0" };
/*int endmark(keydata)
{
	if (onepiece.phonee.compare("00000000000") == 0)
		return 1;
	else return 0;
}*/
struct feedbackwords    //用户的反馈
{
	string words;
	string customername;
}myfeedback;
struct replywords        //管理员的回应
{
	string customername;
	string words;
}myreply;
class user {
public:
	void login();  //登陆
	void show();      //显示个人信息
	void set();      //注册用户     
	void change();     //修改个人信息
	void reset_password(); //重置密码，要先输入一次原密码，符合才可以改
protected:
	string phone, nickname, password;
};
void user::login() {
	//输入用户名之后在那个文件查找到对应那个人的信息，然后看一下这边输入的密码和那边存的符合不符合
	string name, passwordtemp;
	ifstream userdata;
	userdata.open(userDataFileName, ios_base::in | ios_base::binary);
	userdata.seekg(0, ios_base::beg);
	cout << tUser << endl;
	while (cin >> name)
	{
		userdata.seekg(0, ios_base::beg);   //这个没办法再次移动
		int mark = 0;
		while (!userdata.eof())           //判断还没到文件尾
		{

			userdata.read((char*)&onepiece, sizeof(keydata));
			if (name.compare(onepiece.nicknamee) == 0)      //找到该用户的信息
			{
				nickname = name;                     //读到了文件里的东西以后，要把这个东西赋给成员变量
				mark = 1;
				break;
			}
		}
		if (!mark) {
			cout << tInvaildUser << endl;
			continue;
		}
		while (mark == 1)
		{
			cout << "密码:" << endl;
			cin >> passwordtemp;
			while (passwordtemp != onepiece.passwordd)
			{
				cout << "密码错误，请重新输入" << endl;
				cin >> passwordtemp;
			}
			if (passwordtemp == onepiece.passwordd)
			{
				phone = onepiece.phonee;          //赋给成员变量
				password = onepiece.passwordd;
				cout << "登陆成功！" << endl;
			}
			break;
		}
		break;
	}
	userdata.close();
}
void user::show()
{
	cout << "用户名:" << nickname << '\n' << "手机号码:" << phone << endl;
}
void user::set()              //这个只先给三个主要的成员变量赋值，不写入文档先
{
	cout << "注册" << endl;
	string password1, password2, name;
	ifstream userdata;
	userdata.open(userDataFileName, ios_base::in | ios_base::binary);
	userdata.seekg(0, ios_base::beg);
	cout << "请输入用户名：" << endl;
	while (cin >> name)
	{
		userdata.seekg(0, ios_base::beg);
		while (!userdata.eof())
		{
			userdata >> onepiece;
			if ((name.compare(onepiece.nicknamee) == 0) || name.compare("0") == 0)
			{
				cout << "该用户名已被注册，请重新输入" << endl;
				cin >> name;
			}
		}
		break;
	}
	nickname = name;
	cout << "请输入电话号码:" << endl;
	cin >> phone;
	while (phone.length() != 11)
	{
		cout << "号码长度有误，请查证后重新输入" << endl;
		cin >> phone;
	}
	cout << "请输入密码：" << endl;
	cin >> password1;
	cout << "请再次输入密码：" << endl;
	cin >> password2;
	while (password1.compare(password2) != 0)
	{
		cout << "两次输入的密码不相同,再次输入密码：" << endl;
		cin >> password2;
	}
	if (password1.compare(password2) == 0)
	{
		password = password1;
	}
	cout << "注册成功！" << endl;
	userdata.close();
}
void user::change()      //不可以改名字
{
	cout << "用户" << nickname << "修改个人信息" << endl;
	string name = nickname;
	fstream userdata;
	userdata.open(userDataFileName, ios_base::out | ios_base::in | ios_base::binary);        //要把指针移动到原来nickname在的地方，覆盖原来的phone，password
	userdata.seekg(0);
	string passwordcheck;
	cout << "请输入密码" << endl;
	cin >> passwordcheck;
	int i = 2;
	while (passwordcheck.compare(password) != 0)
	{
		cout << "密码错误，请重新输入,剩余次数" << i << '\n' << "请输入密码：";
		cin >> passwordcheck;
		if (i == 0)
			exit(0);
		i--;
	}
	if (passwordcheck.compare(password) == 0)         //开始修改
	{
		string password1, password2;
		cout << "请输入电话号码:" << endl;
		cin >> phone;
		cout << "请输入密码：" << endl;         //缺一个东西，转为不可见的！！！！
		cin >> password1;
		cout << "请再次输入密码：" << endl;
		cin >> password2;
		while (password1.compare(password2) != 0)    //书155页
		{
			cout << "两次输入的密码不相同,再次输入密码：" << endl;         //假如忘记了第一次的密码要直接退出咋整??
			cin >> password2;
		}
		if (password1.compare(password2) == 0)
			password = password1;
		while (!userdata.eof() && onepiece.nicknamee != nickname)
		{
			userdata.read((char*)&onepiece, sizeof(keydata));
		}
		if (onepiece.nicknamee == nickname)
		{
			onepiece.phonee = phone;
			onepiece.passwordd = password;
			userdata.seekp(-long(sizeof(keydata)), ios_base::cur);
			userdata.write((char*)&onepiece, sizeof(keydata));
		}
		userdata.close();
		cout << "修改成功！" << endl;
		cout << "修改后的信息：" << endl;
		cout << "用户名" << nickname << '\n' << "手机号：" << phone << '\n' << "密码：" << password << endl;
	}
	else cout << "密码多次输入错误，验证失败！" << endl;

}
void user::reset_password()
{
	fstream userdata;
	string password1, password2, passwordtemp;
	cout << "修改密码" << '\n' << "请输入原密码:" << endl;
	cin >> passwordtemp;
	int i = 2;
	while (passwordtemp.compare(password) != 0)
	{
		cout << "密码错误，请重新输入,剩余次数" << i << '\n' << "请输入密码：";
		cin >> passwordtemp;
		if (i == 0)
		{
			cout << "认证失败！" << endl;
			exit(0);
		}
		i--;
	}
	if (passwordtemp.compare(password) == 0)
	{
		cout << "请输入修改后的密码:" << endl;
		cin >> password1;
		cout << "请再次输入密码:" << endl;
		cin >> password2;
		while (password1.compare(password2) != 0)
		{
			cout << "两次输入的密码不相同,再次输入密码：" << endl;         //假如忘记了第一次的密码要直接退出咋整??
			cin >> password2;
		}
		if (password1.compare(password2) == 0)
			password = password1;
		userdata.open(userDataFileName, ios_base::out | ios_base::in | ios_base::binary);     //写入文件
		userdata.seekg(0);
		do
		{
			userdata.read((char*)&onepiece, sizeof(keydata));
		} while (!userdata.eof() && onepiece.nicknamee != nickname);
		if (onepiece.nicknamee == nickname)
		{
			onepiece.passwordd = password;
			userdata.seekp(-long(sizeof(keydata)), ios_base::cur);
			userdata.write((char*)&onepiece, sizeof(keydata));
		}
		userdata.close();
		cout << "修改密码成功！" << endl;
	}
}
//-----------------------------------------------------------------------------------------------------
class customer :public user
{
public:
	customer();
	void set();
	void login();
	void show();  //个人信息显示
	void ilike();      //加入心愿单,要对文档操作，把添加的东西转换成代号写入文档
	void showlike();     //显示心愿单，要对文档操作，把文档里的代号读取出来,b变成可视的
	void comment(); //发表评论，也要对文档操作。把写的东西存入文档
	void feedback();   //向管理员反馈问题
	void read();             //查看管理员的回复
protected:
	string preferencef, preferencep;
	int experience;   //升级……？还有经验点数
};
customer::customer()
{
}
void customer::login()
{
	ifstream userdata;
	user::login();
	userdata.open(userDataFileName, ios_base::in | ios_base::binary);
	userdata.seekg(0);
	while (!userdata.eof())
	{
		userdata.read((char*)&onepiece, sizeof(keydata));
		if (nickname == onepiece.nicknamee)
		{
			preferencef = onepiece.preferenceff;
			preferencep = onepiece.preferencepp;
		}
	}
	userdata.close();
}
void customer::set()
{
	user::set();
	fstream userdata;
	userdata.open(userDataFileName, ios_base::out | ios_base::in | ios_base::binary);
	userdata.seekg(0, ios_base::beg);
	while (!userdata.eof())
	{
		userdata >> onepiece;
	}                  //指针指到最末尾
	cout << "您对食物的喜好是？" << '\n' << "清淡的" << " " << "口味重的" << endl;
	cin >> preferencef;
	cout << "您更喜欢哪种类型的旅行地？(可多选)" << "幽静古城" << " " << "现代都市" << " " << "自然山水" << " " << "趣味乐园" << endl;
	cin.ignore();           //要有这个玩意！不然下面一句话就用不了了
	getline(cin, preferencep);
	onepiece.nicknamee = nickname;
	onepiece.passwordd = password;
	onepiece.phonee = phone;
	onepiece.preferenceff = preferencef;
	onepiece.preferencepp = preferencep;
	/*cout << nickname << phone << preferencep;    *///到这里，给成员变量赋值成功的
	userdata.seekp(-long(sizeof(keydata)), ios_base::cur);      //指针前移一个
	userdata << onepiece;
	userdata << onepiece;
	userdata.close();
}
void customer::show()
{
	cout << "用户信息查询" << endl;
	user::show();
	cout << "您的喜好是：" << '\n' << "食物：" << preferencef << '\n' << "旅行地:" << preferencep << endl;
}
void customer::ilike()
{
	ofstream userlike;
	userlike.open(favFilename, ios_base::out | ios_base::binary | ios_base::app);
	likee.what = "? ? ? ? ? ";
	likee.where = " ? ? ? ? ? ";
	userlike.write((char*)&likee, sizeof(like));
	userlike.close();
}
void customer::showlike()
{
	cout << "我的收藏夹" << endl;
	ifstream userlike;
	userlike.open(favFilename, ios_base::in | ios_base::binary);
	userlike.seekg(0);
	while (userlike.eof())
	{
		userlike.read((char*)&likee, sizeof(like));
		cout << likee.where << " " << likee.what << endl;
	}
	userlike.close();
}
void customer::comment()
{
	string words;
	cout << "发表评论" << endl;
	cin >> words;                //把words存入文档
}
void customer::feedback()
{
	string say;
	ofstream feedbackk;
	feedbackk.open(feedFilename, ios_base::out | ios_base::binary | ios_base::app);  //追加到尾
	cout << "请写下您要反馈的内容：" << endl;
	cin.ignore();
	getline(cin, say);
	myfeedback.words = say;
	myfeedback.customername = nickname;
	feedbackk.write((char*)&myfeedback, sizeof(feedbackwords));
	feedbackk.close();
}
void customer::read()
{
	ifstream reply;
	reply.open(feedFilename, ios_base::in | ios_base::binary);
	reply.seekg(0);
	int a = 0;
	while (reply.eof())
	{
		reply.read((char*)&myreply, sizeof(replywords));
		if (myreply.customername == nickname)
		{
			cout << "尊敬的用户" << nickname << ":" << endl;
			cout << myreply.words << endl;
			a = 1;
			break;
		}
	}
	if (a == 0)
		cout << "暂未相关回复，请稍作等待" << endl;
	reply.close();
}
//-----------------------------------------------------------------------------------------------------
class charge :public user
{
public:
	void set();
	void changeinformation();        //修改景点美食信息
	void reply();                //处理用户反馈的问题,先阅读一个文档，之后把处理结果写入另一个文档reply
};
void charge::set()
{
	user::set();
	fstream userdatac;
	userdatac.open(userDataFileName, ios_base::out | ios_base::binary | ios_base::app);       //管理员和用户不放在一个文件
	onepiece.nicknamee = nickname;
	onepiece.passwordd = password;
	onepiece.phonee = phone;
	onepiece.preferenceff = "";
	onepiece.preferencepp = "";

	userdatac.write((char*)&onepiece, sizeof(keydata));
	userdatac.close();
}
void charge::changeinformation()
{

}
void charge::reply()
{
	ifstream feedbackk;
	feedbackk.open(feedFilename, ios_base::in | ios_base::binary);
	feedbackk.seekg(0);
	feedbackk.read((char*)&myfeedback, sizeof(feedbackwords));     //从头读一条
	cout << myfeedback.customername << ":" << '\n' << myfeedback.words << endl;
	//删掉!

	cout << "请写下您的回复" << '\n' << "尊敬的:";
	ofstream reply;
	reply.open(BackFilename, ios_base::in | ios_base::binary | ios_base::app);
	cin >> myreply.customername;
	cin >> myreply.words;
	reply.write((char*)&myreply, sizeof(replywords));
	feedbackk.close();
	reply.close();
}
	//初始化文件，写入空标志

	//fstream userdata;
	//userdata.open(userDataFileName, ios_base::out| ios_base::binary);
	//userdata.seekp(0,ios_base::beg);
	//userdata << onepiece;
	//userdata.close();

	//customer one;
	//one.set();

	/*customer one;
	one.login();
	one.show();
	one.change();*/

	//查看所有用户的数据
	//ifstream userdata;
	//userdata.open(userDataFileName, ios_base::in | ios_base::binary );
	//userdata.seekg(0);
	//while (!endmark(onepiece))
	//{
	//	userdata >> onepiece;
	//	/*userdata.read((char*)&onepiece, sizeof(keydata));*/
	//	cout << onepiece.nicknamee << " " << onepiece.phonee << " " << onepiece.passwordd << " " << onepiece.preferencepp << endl;
	//}
	//userdata.close();
