#include "pch.h"
#include "UserInfo.h"
#include "CConsole.h"
User_like like;
User_like readd;
FeedbackWords myfeedback;
Replywords myreply;
Commentwords mycomment;
int static hadReadFeedback = 0;  //相当于文件的指针
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
		console << "用户名无效，请重新输入：";
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
		fprintf(ptimeFile, "%s from %s", time.c_str(), username.c_str());
		fclose(ptimeFile);
	}
	this->password = password;
	this->Phone = phone;
	this->Username = username;
	this->type = ttype;
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
	console << "请输入新密码：";
	password1 = console.InputPassword();
	if (password1.empty()) {
		console << "新密码不能为空！" << endl;
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
	console << "用户名：" << Username << endl << "手机号：" << phone << endl << "密码：" << password1 << endl;
}

void User::Logout() {
	Phone.clear();
	Username.clear();
	password.clear();
	return;
}
//------------------------------------------------------------------------------------------------

void Customer::show() {
	using namespace std;
}
void Customer::judgelikecin(User_like&p)
{
	using namespace std;
	fstream userlike;
	string file_like_name;
	file_like_name = ".\\" + Username + ".fav";
	userlike.open(file_like_name, ios_base::in | ios_base::binary);
	User_like tmp;
	int flag = 0;
	while (userlike >> tmp) {
		if ((tmp.What == p.What) && (tmp.Where == p.Where))
			flag = 1;
	}
	userlike.close();
	if (flag)
		console << "已添加！" << endl;
	else {
		userlike.open(file_like_name, ios_base::out | ios_base::binary | ios_base::app);
		userlike << p;
		console << "添加成功！" << endl;
		userlike.close();
	}
}
void Customer::ilike() {
	using namespace std;
	console.ClearScreen();
	fstream userlike;
	string file_like_name;
	file_like_name = ".\\" + Username + ".fav";
	string getwhat, getwhere;
								 //缺个获得景点信息的函数，把地点什么的给上面那行的两个变量
	console << "您喜欢这里吗？麻烦您输入下您喜欢什么吧：";
	cin >> getwhat;
	console << getwhat << endl;
	console << "好的，您喜欢" << getwhat << ", 那么它在哪呢？" << endl;
	cin >> getwhere;
	console << "我明白了！" << endl;
	userlike.open(file_like_name, ios_base::out | ios_base::in | ios_base::binary | ios_base::app);
	like.What = getwhat;
	like.Where = getwhere;
	judgelikecin(like);//查重判断是否加入
						  //close在函数里了
}
void Customer::showlike() {
	using namespace std;
	console.ClearScreen();
	console << "我的收藏夹:" << endl;
	fstream userlike;
	string file_like_name;
	file_like_name = ".\\" + Username + ".fav";
	userlike.open(file_like_name, ios_base::out | ios_base::in | ios_base::binary);
	userlike.seekg(0);
	while (userlike >> readd)
	{
		console << readd.Where << "  " << readd.What << endl;
	}
	userlike.close();
}
void Customer::comment() {
	using namespace std;
	console.ClearScreen();
	string words;
	cin >> words;
	console << words << endl;
	fstream commentfile;
	commentfile.open(".\\comment.dat", ios_base::out | ios_base::in | ios_base::binary | ios_base::app);
	commentfile.seekg(0);
	mycomment.customername = this->Username;
	mycomment.words = words;
	commentfile << mycomment;
	commentfile.close();
	console << "感谢您的评论！" << endl;
}
void Customer::readcomment() {
	using namespace std;
	console.ClearScreen();
	console << "评论区（展示评论）：" << endl;
	fstream commentfile;
	commentfile.open(".\\comment.dat", ios_base::out | ios_base::in | ios_base::binary | ios_base::app);
	commentfile.seekg(0);
	while (commentfile >> mycomment)
	{
		console << mycomment.customername << endl;
		console << mycomment.words << endl;
		console << endl;
	}
	commentfile.close();
}
void Customer::feedback() {
	using namespace std;
	console.ClearScreen();
	fstream feedbackfile; //用户们共用一份
	string word;
	console << "请写下您的反馈" << endl;
	cin >> word;
	console << word;
	myfeedback.customername = Username;
	myfeedback.words = word;
	string file_feedback_name;
	file_feedback_name = ".\\FEEDBACK";  //把评论从尾部写入文件
	feedbackfile.open(file_feedback_name, ios_base::out | ios_base::binary | ios_base::app);
	feedbackfile << myfeedback;
	feedbackfile.close();
}
void Customer::read()
{
	using namespace std;
	fstream replyfile;
	string word;
	string file_reply_name;
	Replywords outTmp;
	file_reply_name = ".\\" + Username + ".reply";
	replyfile.open(file_reply_name, ios_base::in | ios_base::binary);
	console << "尊敬的" << Username << endl;
	while (replyfile >> outTmp)
	{
		console << outTmp.words << endl;
	}
	replyfile.close();
}
//------------------------------------------------------------------------------------------------
void Admin::changeinformation() {
	using namespace std;
}
void readAndWrite(int &hadReadFeedbackk) //管理员的读写操作
{
	using namespace std;
	int readFlag = 0;
	fstream feedbackfile;
	FeedbackWords inTmp;
	int countt = 0;
	string file_feedback_name = ".\\FEEDBACK";
	feedbackfile.open(file_feedback_name, ios_base::in | ios_base::binary);
	while ((feedbackfile >> inTmp) && (!readFlag))    //reflag用来每次只操作一次
	{
		if (countt == hadReadFeedbackk)
		{
			fstream replyfile;
			Replywords outTmp;
			FeedbackWords outTmpp;
			outTmpp.customername = inTmp.customername;
			outTmpp.words = inTmp.words;
			console << "用户反馈：" << endl;
			console << outTmpp.customername << endl;
			console << outTmpp.words << endl;

			string file_reply_name = ".\\" + outTmpp.customername + ".reply";
			replyfile.open(file_reply_name, ios_base::in | ios_base::binary | ios_base::app);
			console << "输入您的回复:" << endl;
			outTmp.customername = outTmpp.customername;
			cin >> outTmp.words;
			console << outTmp.words;
			replyfile << outTmp;
			replyfile.close();
			readFlag = 1;
			++hadReadFeedback;
		}
		++countt;
	}
}
void Admin::reply()
{
	using namespace std;
	fstream feedbackfile;
	fstream replyfile; //feedbackfile打开来读，写入reply
	string file_feedback_name; string cname; //获得用户名
	file_feedback_name = ".\\FEEDBACK";
	feedbackfile.open(file_feedback_name, ios_base::out | ios_base::in | ios_base::binary);
	FeedbackWords input;
	int count = 0;
	while (feedbackfile >> input)
		++count;
	feedbackfile.close();
	int totalFeedback = count;
	while (hadReadFeedback < totalFeedback)
	{
		readAndWrite(hadReadFeedback);
		console << endl;
	}
	feedbackfile.close();
}


