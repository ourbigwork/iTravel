#include "pch.h"
#include "constStr.h"
#include "ReflectFactory.h"
#include "CConsole.h"
using namespace Gdiplus;
using namespace std;
CConsole console(cTitle);
Reflect::Worker ReflectWorker;

namespace Reflect {
	class exit :public ReflectBase, DynamicCreator<exit> {
	public:
		exit() {}
		virtual void Work() {
			::exit(0);
		}
	};
	class login :public ReflectBase, DynamicCreator<login> {
	public:
		login() {}
		virtual void Work() {
			console.ClearScreen();
			console << "UserName:";
			string username;
			cin >> username;
			console << username;
			console << endl << "password:";
			string password = console.InputPassword();
			//在这里判断
			console << password << endl << "Welcome," << username << ". Your password is:" << password << endl;
			cin.get();//清理最后的换行符
		}
	};
	class about :public ReflectBase, DynamicCreator<about> {
	public:
		about() {}
		virtual void Work() {
			console.ClearScreen();
			console.WriteText(about_info);
		}
	};
	class cls :public ReflectBase, DynamicCreator<cls> {
	public:
		cls() {}
		virtual void Work() {
			console.ClearScreen();
		}
	};
	class rect :public ReflectBase, DynamicCreator<rect> {
	public:
		rect() {}
		virtual void Work() {
			console.Dialog("Hello,Dialog!");
		}
	};
};
//解析命令部分
bool parseCommandline(const string & content) {
	string b = content;
	size_t x = 0;
	//删除空格
	b.erase(remove_if(b.begin(), b.end(), ::isblank), b.end());
	//转换为小写
	transform(b.begin(), b.end(), b.begin(), ::tolower);
	b.insert(0,"Reflect::");
	//反射到命令对应的类上
	Reflect::ReflectBase *p = ReflectWorker.Create(b);
	if(p){
		p->Work();
		return true;
	}else{
		if (size_t pos = b.find("loadimg") != string::npos) {
			console.stopDrawingThread();
			console.displayImage(console.string2wstring(b.substr(pos + 6)), COORD{ 233,233 });
			return true;
		}
	}
	//TODO:more commands here...
	return false;
}

int main(void) {
	//getCurrentConsoleHandle();
	console.init(BACKGROUND_BLUE, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
	console << Welcome;
	string content;
	while (getline(cin, content)) {
		if (!parseCommandline(content))
			console << "'" << content << "'" 
			<< " is not recognized as an internal or external command,\noperable program or batch file. " << endl;
	}
	return 0;
}