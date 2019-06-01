#include "pch.h"
#include "constStr.h"
#include "CConsole.h"
using namespace std;
struct like {
	string where;    //ʲô�ط���
	string what;    //ʲô����
}likee;
struct keydata {
	string nicknamee;//�û���
	string phonee;//�绰����
	string passwordd;//����
	string preferenceff;//����
	string preferencepp;//����
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
struct feedbackwords    //�û��ķ���
{
	string words;
	string customername;
}myfeedback;
struct replywords        //����Ա�Ļ�Ӧ
{
	string customername;
	string words;
}myreply;
class user {
public:
	void login();  //��½
	void show();      //��ʾ������Ϣ
	void set();      //ע���û�     
	void change();     //�޸ĸ�����Ϣ
	void reset_password(); //�������룬Ҫ������һ��ԭ���룬���ϲſ��Ը�
protected:
	string phone, nickname, password;
};
void user::login() {
	//�����û���֮�����Ǹ��ļ����ҵ���Ӧ�Ǹ��˵���Ϣ��Ȼ��һ����������������Ǳߴ�ķ��ϲ�����
	string name, passwordtemp;
	ifstream userdata;
	userdata.open(userDataFileName, ios_base::in | ios_base::binary);
	userdata.seekg(0, ios_base::beg);
	cout << tUser << endl;
	while (cin >> name)
	{
		userdata.seekg(0, ios_base::beg);   //���û�취�ٴ��ƶ�
		int mark = 0;
		while (!userdata.eof())           //�жϻ�û���ļ�β
		{

			userdata.read((char*)&onepiece, sizeof(keydata));
			if (name.compare(onepiece.nicknamee) == 0)      //�ҵ����û�����Ϣ
			{
				nickname = name;                     //�������ļ���Ķ����Ժ�Ҫ���������������Ա����
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
			cout << "����:" << endl;
			cin >> passwordtemp;
			while (passwordtemp != onepiece.passwordd)
			{
				cout << "�����������������" << endl;
				cin >> passwordtemp;
			}
			if (passwordtemp == onepiece.passwordd)
			{
				phone = onepiece.phonee;          //������Ա����
				password = onepiece.passwordd;
				cout << "��½�ɹ���" << endl;
			}
			break;
		}
		break;
	}
	userdata.close();
}
void user::show()
{
	cout << "�û���:" << nickname << '\n' << "�ֻ�����:" << phone << endl;
}
void user::set()              //���ֻ�ȸ�������Ҫ�ĳ�Ա������ֵ����д���ĵ���
{
	cout << "ע��" << endl;
	string password1, password2, name;
	ifstream userdata;
	userdata.open(userDataFileName, ios_base::in | ios_base::binary);
	userdata.seekg(0, ios_base::beg);
	cout << "�������û�����" << endl;
	while (cin >> name)
	{
		userdata.seekg(0, ios_base::beg);
		while (!userdata.eof())
		{
			userdata >> onepiece;
			if ((name.compare(onepiece.nicknamee) == 0) || name.compare("0") == 0)
			{
				cout << "���û����ѱ�ע�ᣬ����������" << endl;
				cin >> name;
			}
		}
		break;
	}
	nickname = name;
	cout << "������绰����:" << endl;
	cin >> phone;
	while (phone.length() != 11)
	{
		cout << "���볤���������֤����������" << endl;
		cin >> phone;
	}
	cout << "���������룺" << endl;
	cin >> password1;
	cout << "���ٴ��������룺" << endl;
	cin >> password2;
	while (password1.compare(password2) != 0)
	{
		cout << "������������벻��ͬ,�ٴ��������룺" << endl;
		cin >> password2;
	}
	if (password1.compare(password2) == 0)
	{
		password = password1;
	}
	cout << "ע��ɹ���" << endl;
	userdata.close();
}
void user::change()      //�����Ը�����
{
	cout << "�û�" << nickname << "�޸ĸ�����Ϣ" << endl;
	string name = nickname;
	fstream userdata;
	userdata.open(userDataFileName, ios_base::out | ios_base::in | ios_base::binary);        //Ҫ��ָ���ƶ���ԭ��nickname�ڵĵط�������ԭ����phone��password
	userdata.seekg(0);
	string passwordcheck;
	cout << "����������" << endl;
	cin >> passwordcheck;
	int i = 2;
	while (passwordcheck.compare(password) != 0)
	{
		cout << "�����������������,ʣ�����" << i << '\n' << "���������룺";
		cin >> passwordcheck;
		if (i == 0)
			exit(0);
		i--;
	}
	if (passwordcheck.compare(password) == 0)         //��ʼ�޸�
	{
		string password1, password2;
		cout << "������绰����:" << endl;
		cin >> phone;
		cout << "���������룺" << endl;         //ȱһ��������תΪ���ɼ��ģ�������
		cin >> password1;
		cout << "���ٴ��������룺" << endl;
		cin >> password2;
		while (password1.compare(password2) != 0)    //��155ҳ
		{
			cout << "������������벻��ͬ,�ٴ��������룺" << endl;         //���������˵�һ�ε�����Ҫֱ���˳�զ��??
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
		cout << "�޸ĳɹ���" << endl;
		cout << "�޸ĺ����Ϣ��" << endl;
		cout << "�û���" << nickname << '\n' << "�ֻ��ţ�" << phone << '\n' << "���룺" << password << endl;
	}
	else cout << "���������������֤ʧ�ܣ�" << endl;

}
void user::reset_password()
{
	fstream userdata;
	string password1, password2, passwordtemp;
	cout << "�޸�����" << '\n' << "������ԭ����:" << endl;
	cin >> passwordtemp;
	int i = 2;
	while (passwordtemp.compare(password) != 0)
	{
		cout << "�����������������,ʣ�����" << i << '\n' << "���������룺";
		cin >> passwordtemp;
		if (i == 0)
		{
			cout << "��֤ʧ�ܣ�" << endl;
			exit(0);
		}
		i--;
	}
	if (passwordtemp.compare(password) == 0)
	{
		cout << "�������޸ĺ������:" << endl;
		cin >> password1;
		cout << "���ٴ���������:" << endl;
		cin >> password2;
		while (password1.compare(password2) != 0)
		{
			cout << "������������벻��ͬ,�ٴ��������룺" << endl;         //���������˵�һ�ε�����Ҫֱ���˳�զ��??
			cin >> password2;
		}
		if (password1.compare(password2) == 0)
			password = password1;
		userdata.open(userDataFileName, ios_base::out | ios_base::in | ios_base::binary);     //д���ļ�
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
		cout << "�޸�����ɹ���" << endl;
	}
}
//-----------------------------------------------------------------------------------------------------
class customer :public user
{
public:
	customer();
	void set();
	void login();
	void show();  //������Ϣ��ʾ
	void ilike();      //������Ը��,Ҫ���ĵ�����������ӵĶ���ת���ɴ���д���ĵ�
	void showlike();     //��ʾ��Ը����Ҫ���ĵ����������ĵ���Ĵ��Ŷ�ȡ����,b��ɿ��ӵ�
	void comment(); //�������ۣ�ҲҪ���ĵ���������д�Ķ��������ĵ�
	void feedback();   //�����Ա��������
	void read();             //�鿴����Ա�Ļظ�
protected:
	string preferencef, preferencep;
	int experience;   //�������������о������
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
	}                  //ָ��ָ����ĩβ
	cout << "����ʳ���ϲ���ǣ�" << '\n' << "�嵭��" << " " << "��ζ�ص�" << endl;
	cin >> preferencef;
	cout << "����ϲ���������͵����еأ�(�ɶ�ѡ)" << "�ľ��ų�" << " " << "�ִ�����" << " " << "��Ȼɽˮ" << " " << "Ȥζ��԰" << endl;
	cin.ignore();           //Ҫ��������⣡��Ȼ����һ�仰���ò�����
	getline(cin, preferencep);
	onepiece.nicknamee = nickname;
	onepiece.passwordd = password;
	onepiece.phonee = phone;
	onepiece.preferenceff = preferencef;
	onepiece.preferencepp = preferencep;
	/*cout << nickname << phone << preferencep;    *///���������Ա������ֵ�ɹ���
	userdata.seekp(-long(sizeof(keydata)), ios_base::cur);      //ָ��ǰ��һ��
	userdata << onepiece;
	userdata << onepiece;
	userdata.close();
}
void customer::show()
{
	cout << "�û���Ϣ��ѯ" << endl;
	user::show();
	cout << "����ϲ���ǣ�" << '\n' << "ʳ�" << preferencef << '\n' << "���е�:" << preferencep << endl;
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
	cout << "�ҵ��ղؼ�" << endl;
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
	cout << "��������" << endl;
	cin >> words;                //��words�����ĵ�
}
void customer::feedback()
{
	string say;
	ofstream feedbackk;
	feedbackk.open(feedFilename, ios_base::out | ios_base::binary | ios_base::app);  //׷�ӵ�β
	cout << "��д����Ҫ���������ݣ�" << endl;
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
			cout << "�𾴵��û�" << nickname << ":" << endl;
			cout << myreply.words << endl;
			a = 1;
			break;
		}
	}
	if (a == 0)
		cout << "��δ��ػظ����������ȴ�" << endl;
	reply.close();
}
//-----------------------------------------------------------------------------------------------------
class charge :public user
{
public:
	void set();
	void changeinformation();        //�޸ľ�����ʳ��Ϣ
	void reply();                //�����û�����������,���Ķ�һ���ĵ���֮��Ѵ�����д����һ���ĵ�reply
};
void charge::set()
{
	user::set();
	fstream userdatac;
	userdatac.open(userDataFileName, ios_base::out | ios_base::binary | ios_base::app);       //����Ա���û�������һ���ļ�
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
	feedbackk.read((char*)&myfeedback, sizeof(feedbackwords));     //��ͷ��һ��
	cout << myfeedback.customername << ":" << '\n' << myfeedback.words << endl;
	//ɾ��!

	cout << "��д�����Ļظ�" << '\n' << "�𾴵�:";
	ofstream reply;
	reply.open(BackFilename, ios_base::in | ios_base::binary | ios_base::app);
	cin >> myreply.customername;
	cin >> myreply.words;
	reply.write((char*)&myreply, sizeof(replywords));
	feedbackk.close();
	reply.close();
}
	//��ʼ���ļ���д��ձ�־

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

	//�鿴�����û�������
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
