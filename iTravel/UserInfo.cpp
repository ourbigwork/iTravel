#include "pch.h"
#include "UserInfo.h"
#include "CConsole.h"
User_like like;
User_like readd;
FeedbackWords myfeedback;
Replywords myreply;
Commentwords mycomment;
int static hadReadFeedback = 0;  //�൱���ļ���ָ��
User::User(const std::string & Datafilename) {
	file.ReopenFile(Datafilename);
}
void User::Login() {
	using std::console;
	using std::endl;
	using std::string;
	using std::cin;
	console.ClearScreen();
	console << "�û�����";
	string username, phone, password;
	string _password;
	cin >> username;
	console << username << endl;
	int ttype;
	file.findUser(username, password, phone, ttype);
	while (password.empty()) {
		console << "�û�����Ч�����������룺";
		cin >> username;
		console << username << endl;
		file.findUser(username, password, phone, ttype);
	}
	console << "����:";
	int i = 3;
	while (i) {
		_password = console.InputPassword();
		console << "*********" << endl;
		if (password != _password) {
			i--;
			if (!i) {
				console << "���Դ������࣡" << endl;
				return;
			}
			console << "����������������룺";
		}
		else {
			break;
		}
	}
	if (ttype == 2) {
		console << "��ӭ��������Ա��" << username << "." << endl;
	}
	else
		console << "��½�ɹ���" << endl;
	//��õ�ǰʱ��
	string time = file.TimeUTCNow();
	FILE* ptimeFile = fopen(".\\login", "a+");
	//����֮ǰ���ļ���
	char bLastTime[255]{ 0 };
	if (ptimeFile) {
		fscanf(ptimeFile, "%[^\n]%*c", bLastTime);//��ȡһ��
		if (strlen(bLastTime)) {
			console << "�ϴε�¼��" << bLastTime << "." << endl;
		}
		else
			OutputDebugStringA("[Warning]Last login time file not found!");
		fclose(ptimeFile);
	}
	//���֮ǰ������
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
	std::console << "�û���: " << Username << std::endl << "�ֻ�����: " << Phone << std::endl;
}
void User::Regist() {
	using std::console;
	using std::endl;
	using std::string;
	using std::cin;
	int ttype;
	console.ClearScreen();
	console << "ע��" << endl;
	string password1, password2, name;
	string phone1, phone2;
	console << "�������û�����";
	while (cin >> name) {
		console << name << endl;
		if (name.empty()) {
			console << "�û�������Ϊ�գ�" << endl;
			cin.get();
			continue;
		}
		file.findUser(name, password2, phone2, ttype);
		if (!password2.empty()) {
			console << "���û��ѱ�ע�ᣬ����������" << endl << "�������û�����";
			continue;
		}
		else {
			password2.clear();
			break;
		}
	}
	console << "������绰���룺";
	while (cin >> phone1) {
		console << phone1 << endl;
		if (phone1.length() != 11) {
			console << "���볤���������֤����������" << endl << "������绰���룺";
			cin.get();
			continue;
		}
		else {
			bool f = false;
			for (auto x : phone1) {
				if (!isdigit(x)) {
					console << "�������ȫ�������֣�" << endl;
					f = true;
					break;
				}
			}
			if (!f)
				break;
		}
	}
	console << "���������루���16λ����";
	while (true) {
		password1 = console.InputPassword();
		console << "*********" << endl;
		if (password1.empty()) {
			console << "���벻��Ϊ�գ�" << endl;
			cin.get();
		}
		else break;
	}
	console << "���ٴ��������룺";
	password2 = console.InputPassword();
	console << "*********" << endl;
	while (password2 != password1) {
		console << "������������벻��ͬ" << endl << "���ٴ��������룺";
		password2 = console.InputPassword();
		console << "*********" << endl;
	}
	console << "ע��ɹ���" << endl;
	int type = 1;
	//���ṩע�����Ա�Ľӿ�
	file.RegistUser(name, password1, phone1, type);
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
	int type;
	file.findUser(Username, oldpass, oldphone, type);
	int i = 3;
	console << "���������룺";
	passwordcheck = console.InputPassword();
	console << "*********" << endl;
	while (passwordcheck != oldpass) {
		if (!i) {
			console << "���볢�Դ������࣡" << endl;
			return;
		}
		console << "�����������������,ʣ�������" << --i << "�Σ�" << endl << "���������룺";
		passwordcheck = console.InputPassword();
		console << "*********" << endl;
	}
	string password1, password2;
	string phone;
	console << "������绰����:";
	cin >> phone;
	console << phone << endl;
	console << "�����������룺";
	password1 = console.InputPassword();
	if (password1.empty()) {
		console << "�����벻��Ϊ�գ�" << endl;
		return;
	}
	console << "���ٴ��������룺";
	password2 = console.InputPassword();
	while (password1 != password2) {
		console << "������������벻��ͬ,�ٴ��������룺";
		password2 = console.InputPassword();
	}
	file.revise(Username, phone, password1, type);
	password = password1;
	Phone = phone;
	console << "�޸ĳɹ���" << endl;
	console << "�޸ĺ����Ϣ��" << endl;
	console << "�û�����" << Username << endl << "�ֻ��ţ�" << phone << endl << "���룺" << password1 << endl;
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
		console << "����ӣ�" << endl;
	else {
		userlike.open(file_like_name, ios_base::out | ios_base::binary | ios_base::app);
		userlike << p;
		console << "��ӳɹ���" << endl;
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
								 //ȱ����þ�����Ϣ�ĺ������ѵص�ʲô�ĸ��������е���������
	console << "��ϲ���������鷳����������ϲ��ʲô�ɣ�";
	cin >> getwhat;
	console << getwhat << endl;
	console << "�õģ���ϲ��" << getwhat << ", ��ô�������أ�" << endl;
	cin >> getwhere;
	console << "�������ˣ�" << endl;
	userlike.open(file_like_name, ios_base::out | ios_base::in | ios_base::binary | ios_base::app);
	like.What = getwhat;
	like.Where = getwhere;
	judgelikecin(like);//�����ж��Ƿ����
						  //close�ں�������
}
void Customer::showlike() {
	using namespace std;
	console.ClearScreen();
	console << "�ҵ��ղؼ�:" << endl;
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
	console << "��л�������ۣ�" << endl;
}
void Customer::readcomment() {
	using namespace std;
	console.ClearScreen();
	console << "��������չʾ���ۣ���" << endl;
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
	fstream feedbackfile; //�û��ǹ���һ��
	string word;
	console << "��д�����ķ���" << endl;
	cin >> word;
	console << word;
	myfeedback.customername = Username;
	myfeedback.words = word;
	string file_feedback_name;
	file_feedback_name = ".\\FEEDBACK";  //�����۴�β��д���ļ�
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
	console << "�𾴵�" << Username << endl;
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
void readAndWrite(int &hadReadFeedbackk) //����Ա�Ķ�д����
{
	using namespace std;
	int readFlag = 0;
	fstream feedbackfile;
	FeedbackWords inTmp;
	int countt = 0;
	string file_feedback_name = ".\\FEEDBACK";
	feedbackfile.open(file_feedback_name, ios_base::in | ios_base::binary);
	while ((feedbackfile >> inTmp) && (!readFlag))    //reflag����ÿ��ֻ����һ��
	{
		if (countt == hadReadFeedbackk)
		{
			fstream replyfile;
			Replywords outTmp;
			FeedbackWords outTmpp;
			outTmpp.customername = inTmp.customername;
			outTmpp.words = inTmp.words;
			console << "�û�������" << endl;
			console << outTmpp.customername << endl;
			console << outTmpp.words << endl;

			string file_reply_name = ".\\" + outTmpp.customername + ".reply";
			replyfile.open(file_reply_name, ios_base::in | ios_base::binary | ios_base::app);
			console << "�������Ļظ�:" << endl;
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
	fstream replyfile; //feedbackfile��������д��reply
	string file_feedback_name; string cname; //����û���
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


