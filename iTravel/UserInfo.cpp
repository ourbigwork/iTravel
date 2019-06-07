#include "pch.h"                         //����ÿ��д֮ǰ�����ĸ�std������clearscreen����β�Ӷ�����coutд��console
#include "UserInfo.h"
#include "CConsole.h"
#include "constStr.h"
User::User(const std::string & Datafilename) {
	file.ReopenFile(Datafilename);
}
void User::Login() {
	using std::console;          //1��std::���ֶ����������ڣ�
	using std::endl;
	using std::string;
	using std::cin;
	console.ClearScreen();       //�����Ļ��ǰ���ݣ����Ŀ��
	console << "�û�����";      //����õ��ַ������㿪��������    2��inline��L��
	string username, phone, password;
	string _password;
	cin >> username;
	console << username << endl;
	int ttype;      //�ж����û����ǹ���Ա
	
	file.findUser(username, password, phone, ttype);
	while (password.empty()) {
		console << tInvaildUser;
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
		console << "��ӭ��������Ա:" << username << "." << endl;
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
	this->password = password;     //����Ա������ֵ
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
	int ttype;
	console.ClearScreen();
	console << "ע��" << endl;
	string password1, password2, name;
	string phone1, phone2;        //phone�û��������ʱ�ĺ���
	console << "�������û�����";
	while (cin >> name)
	{
		console << name << endl;     
		if (name.empty()) {
			console << "�û�������Ϊ�գ�" << endl;
			cin.get();            //5�����Ҫ����ɶ����get�յĶ�����
			continue;
		}
		file.findUser(name, password2, phone2, ttype);          
		if (!password2.empty()) {                      
			console << "���û��ѱ�ע�ᣬ����������" << endl << "�������û�����";
			continue;
		}
		else {
			password2.clear();        //��password���ַ�ɾ��
			break;
		}
	}
	console << "������绰���룺";
	while (cin >> phone1) {
		console << phone1 << endl;
		if (phone1.length() != 11) {
			console << "���볤���������֤����������" << endl << "������绰���룺";
			cin.get();       //����ͬ5
			continue;
		}
		else {
			bool f = false;
			for (auto x : phone1) {    //����phone1��ÿ��Ԫ��x��auto���Զ��洢�����Ĺؼ��֣��Զ��ж�����
				if (!isdigit(x)) {        //�����ж����͵�
					console << "�������ȫ�������֣�" << endl;
					f = true;
					break;        //����forѭ������������while�������������
				}
			}
			if (!f)    
				break; //����ȫ�����֣�����while
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
		console << "�����������������,ʣ�������" << --i << "�Σ�" << endl << "���������룺";    //��������
		passwordcheck = console.InputPassword();
		console << "*********" << endl;
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
	file.revise(Username, phone, password1, type);    //��Ҫ�ĺ���
	password = password1;
	Phone = phone;
	console << "�޸ĳɹ���" << endl;
	console << "�޸ĺ����Ϣ��" << endl;
	console << "�û���" << Username << '\n' << "�ֻ��ţ�" << phone << '\n' << "���룺" << password1 << endl;
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
	like_file_name = Username + "���ղؼ�";
	comment_file_name = Username + "����ʷ����";
	reply_file_name = Username + "�յ��Ļظ�";

	userlike.open("d:\\"+ like_file_name +".dat", ios::out | ios::binary | ios::app);

	userlike.open("d:\\"+ comment_file_name+".dat", ios::out | ios::binary | ios::app);

	userlike.open("d:\\"+ reply_file_name+".dat", ios::out | ios::binary | ios::app);

	//��ʼ���ļ���????
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
	file_like_name = Username + "���ղؼ�";
	string getwhat, getwhere;
	                             //ȱ����þ�����Ϣ�ĺ���
	                             //��Ҫ����

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
	console << "�ҵ��ղؼ�:" << endl;
	fstream userlike;
	string file_like_name;
	file_like_name = Username + "���ղؼ�";
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
	fstream feedbackfile; //�û��ǹ���һ��
	string word;
	console << "��д�����ķ���" << endl;
	cin >> word;
	console << word;        
							//ȱһ��չʾ��ҳ���ϵ�
	myfeedback.customername = Username;
	myfeedback.words = word;
	string file_feedback_name;
	file_feedback_name = "�û�����";  //�����۴�β��д���ļ�
	feedbackfile.open("d:\\" + file_feedback_name + ".txt", ios::out | ios::in | ios::binary | ios::app);
	feedbackfile << myfeedback;
	feedbackfile.close();
}

void Customer::read() {
	using namespace std;
	fstream replyfile; 
	string word;
	string file_reply_name;
	file_reply_name = Username + "�յ��Ļظ�";
	replyfile.open("d:\\" + file_reply_name + ".txt", ios::out | ios::in | ios::binary);
	replyfile.seekg(0);
	console << "�𾴵�" << Username<< endl;
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
	fstream replyfile; //feedbackfile��������д��reply
	string file_feedback_name;string cname;//����û���
	file_feedback_name = "�û�����";
	feedbackfile.open("d:\\" + file_feedback_name + ".txt", ios::out | ios::in | ios::binary );
	
	
	
	
	string file_reply_name;
	
	file_reply_name =     + "�յ��Ļظ�";
}
