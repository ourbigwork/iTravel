#include "pch.h"                         //反正每次写之前加上四个std，加上clearscreen，结尾加东西，cout写成console
#include "UserInfo.h"
#include "CConsole.h"
#include "constStr.h"
User::User(const std::string & Datafilename) {
	file.ReopenFile(Datafilename);
}
void User::Login() {
	using std::console;          //1、std::这种东西作用在于？
	using std::endl;
	using std::string;
	using std::cin;
	console.ClearScreen();       //清空屏幕当前内容（画的框框）
	console << "用户名：";      //定义好的字符串，点开就明白了    2、inline？L？
	string username, phone, password;
	string _password;
	cin >> username;
	console << username << endl;
	int ttype;      //判断是用户还是管理员
	
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
		console << "欢迎您，管理员:" << username << "." << endl;
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
		fprintf(ptimeFile, "%s from %s", time.c_str(), username.c_str());
		fclose(ptimeFile);
	}
	this->password = password;     //给成员变量赋值
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
	string phone1, phone2;        //phone用户输入的暂时的号码
	console << "请输入用户名：";
	while (cin >> name)
	{
		console << name << endl;     
		if (name.empty()) {
			console << "用户名不能为空！" << endl;
			cin.get();            //5、这个要来干啥？？get空的东西？
			continue;
		}
		file.findUser(name, password2, phone2, ttype);          
		if (!password2.empty()) {                      
			console << "该用户已被注册，请重新输入" << endl << "请输入用户名：";
			continue;
		}
		else {
			password2.clear();        //把password的字符删除
			break;
		}
	}
	console << "请输入电话号码：";
	while (cin >> phone1) {
		console << phone1 << endl;
		if (phone1.length() != 11) {
			console << "号码长度有误，请查证后重新输入" << endl << "请输入电话号码：";
			cin.get();       //问题同5
			continue;
		}
		else {
			bool f = false;
			for (auto x : phone1) {    //对于phone1的每个元素x，auto是自动存储变量的关键字，自动判断类型
				if (!isdigit(x)) {        //用来判断类型的
					console << "号码必须全部是数字！" << endl;
					f = true;
					break;        //跳出for循环但是跳不出while，继续输入号码
				}
			}
			if (!f)    
				break; //号码全是数字，跳出while
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
		console << "密码错误，请重新输入,剩余次数：" << --i << "次；" << endl << "请输入密码：";    //减了再用
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
	file.revise(Username, phone, password1, type);    //重要的函数
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
void Customer::Regist()
{
	User::Regist();
	fstream userlike,commentfile,replyfile;
	string like_file_name, comment_file_name, reply_file_name;
	like_file_name = Username + "的收藏夹";
	comment_file_name = Username + "的历史评论";
	reply_file_name = Username + "收到的回复";

	userlike.open("d:\\"+ like_file_name +".dat", ios::out | ios::binary | ios::app);

	userlike.open("d:\\"+ comment_file_name+".dat", ios::out | ios::binary | ios::app);

	userlike.open("d:\\"+ reply_file_name+".dat", ios::out | ios::binary | ios::app);

	//初始化文件们????
}
void Customer::ilike() {
	using namespace std;
	using std::console;
	using std::endl;
	using std::string;
	using std::cin;
	console.ClearScreen();
	fstream userlike;
	string file_like_name;
	file_like_name = Username + "的收藏夹";
	string getwhat, getwhere;
	                             //缺个获得景点信息的函数
	                             //想要查重

	userlike.open("d:\\" + file_like_name + ".txt", ios::out | ios::in | ios::binary | ios::app);
	like.What = getwhat;
	like.Where = getwhere;
	userlike << like;
	userlike.close();
}

void Customer::showlike() {
	using namespace std;
	using std::console;    
	using std::endl;
	using std::string;
	using std::cin;
	console.ClearScreen();
	console << "我的收藏夹:" << endl;
	fstream userlike;
	string file_like_name;
	file_like_name = Username + "的收藏夹";
	userlike.open("d:\\" + file_like_name + ".txt", ios::out | ios::in | ios::binary);
	userlike.seekg(0);
	while (userlike >> readd)
	{
		console << readd.Where << "  " << readd.What << endl;
	}
	userlike.close();
}

void Customer::comment() {
	using namespace std;
	using std::console;
	using std::endl;
	using std::string;
	using std::cin;
	console.ClearScreen();
	
}

void Customer::feedback() {
	using namespace std;
	using std::console;
	using std::endl;
	using std::string;
	using std::cin;
	console.ClearScreen();
	fstream feedbackfile; //用户们共用一份
	string word;
	console << "请写下您的反馈" << endl;
	cin >> word;
	console << word;        
							//缺一个展示在页面上的
	myfeedback.customername = Username;
	myfeedback.words = word;
	string file_feedback_name;
	file_feedback_name = "用户反馈";  //把评论从尾部写入文件
	feedbackfile.open("d:\\" + file_feedback_name + ".txt", ios::out | ios::in | ios::binary | ios::app);
	feedbackfile << myfeedback;
	feedbackfile.close();
}

void Customer::read() {
	using namespace std;
	fstream replyfile; 
	string word;
	string file_reply_name;
	file_reply_name = Username + "收到的回复";
	replyfile.open("d:\\" + file_reply_name + ".txt", ios::out | ios::in | ios::binary);
	replyfile.seekg(0);
	console << "尊敬的" << Username<< endl;
	while (replyfile >> myreply)
	{
		console << readd.What << endl;
	}
	replyfile.close();
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
	fstream feedbackfile;
	fstream replyfile; //feedbackfile打开来读，写入reply
	string file_feedback_name;string cname;//获得用户名
	file_feedback_name = "用户反馈";
	feedbackfile.open("d:\\" + file_feedback_name + ".txt", ios::out | ios::in | ios::binary );
	
	
	
	
	string file_reply_name;
	
	file_reply_name =     + "收到的回复";
}
