﻿#include "CConsole.h"
#include "Train.h"
#include "Scenic.h"
#include "Hotel.h"
#include "pch.h"

#include "constStr.h"
#include "ReflectFactory.h"

using namespace Gdiplus;
using namespace std;

Reflect::Worker ReflectWorker;
std::CConsole std::console("iTravel v0.11");

namespace Reflect {
	using std::console;
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
			console.Dialog(about_info,COORD{5,3},COORD{80,20});
			//console.WriteText(about_info);
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
			//console.Dialog(about_info);
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
	b.insert(0, "Reflect::");
	//反射到命令对应的类上
	Reflect::ReflectBase *p = ReflectWorker.Create(b);
	if (p) {
		p->Work();
		return true;
	}
	else {
		if (size_t pos = b.find("loadimg") != string::npos) {
			console.stopDrawingThread();
			console.displayImage(console.string2wstring(b.substr(pos + 6)), COORD{ 233,233 });
			return true;
		}else if( b == "Reflect::test"){
			LoadData();
			OutputRegion();
			
			return true;
		}
	}
	//TODO:more commands here...
	return false;
}

int main(void) {
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