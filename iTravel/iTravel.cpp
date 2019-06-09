#include "CConsole.h"
#include "pch.h"
#include "Train.h"
#include "Scenic.h"
#include "Hotel.h"
#include "UserInfo.h"
#include "constStr.h"
#include "ReflectFactory.h"

using namespace Gdiplus;
using namespace std;
Reflect::Worker ReflectWorker;
std::CConsole std::console(cTitle);
User user(".\\userinfo.dat");
bool isLogin = false, sdataload = false, tdata = false, hdata = false;
namespace Reflect {
	using std::console;
	class scenic :public ReflectBase, DynamicCreator<scenic> {
	private:
		void printSubMenu() {
			if (!sdataload)
				LoadData();
			sdataload = true;
			console.ClearScreen();
			console << "好康的……是新景点噢？" << endl <<
				"1 - 输出全部景点\t2 - 查询目的地\t3 - 随机推荐\n" << "请输入命令代号：";
			int k;
			cin >> k;
			while (k < 1 || k > 3) {
				console << k << endl;
				console << "这↑里↓还没有被开发，再来一次吧：";
				cin >> k;
			}
			console << k << endl;
			string s;
			RegionClass * Index;
			switch (k) {
			case 1:
				OutputRegion();
				break;
			case 2:
				console << "您要去哪呢？";
				cin >> s;
				if (s == ".")return;
				console << s << endl;
				while (s != "北京" && s != "成都" && s != "三亚" && s != "广州") {
					console << "兄啊您输入的城市去不了呢……再来一次罢：";
					cin >> s;
					if (s == ".")return;
					console << s << endl;
				}
				Index = FindRegion(s);
				OutputSpecific(Index);
				sortByPriceDown(Index);
				OutputSpecific(Index);
				break;
			case 3:
				srand(time(NULL));
				RandomRecommand();
				RandomRecommand();
				RandomRecommand();
				break;
			}
		}

	public:
		virtual void Work() {
			if (isLogin) {
				printSubMenu();
				cin.get();
			}
			else
				console << "请登录后使用此功能！" << endl;
		}
	};
	class train :public ReflectBase, DynamicCreator<train> {
	private:
		void printMenu() {
			if (!tdata)
				TrainDataLoad();
			tdata = true;
			console.ClearScreen();
			console << "欢迎使用车票查询" << endl;
			console << "1 - 查询站点\t2 - 查询列车\t3 - 查询车次" << endl << "请输入代号：";
			freopen("CON", "r", stdin);
			int ss = 0;
			cin.clear();
			cin >> ss;
			while (ss < 1 || ss > 3) {
				console << ss << endl;
				console << "这↑里↓还没有被开发，再来一次吧：";
				cin >> ss;
			}
			console << ss << endl;
			string s, e;
			int Index;
			switch (ss) {
			case 1:
				console << "输入城市名：";
				cin >> s;
				console << s << endl;
				Index = findStation(s);
				StationList[Index]->outputInfo();
				break;
			case 2:
				console << "输入车次号：";
				cin >> s;
				console << s << endl;
				Index = findTrain(s);
				if (Index == -1) {
					console << "找不到您要查询的车次： " << s << " ,返回.";
					return;
				}
				TrainList[Index]->outputBasicInfo();
				TrainList[Index]->outputSeat();
				TrainList[Index]->outputRoute();
				break;
			case 3:
				console << "起点: ";
				cin >> s;
				console << s << " 终点： ";
				cin >> e;
				console << e << endl;
				findResult(s, e);
				cout << "按耗时最少排序" << endl;
				sortResultFast();
				outputResult();
			}
		}
	public:
		virtual void Work() {
			if (isLogin) {
				printMenu();
				cin.get();
			}
			else
				console << "请登录后使用此功能！" << endl;
		}

	};
	class hotel :public ReflectBase, DynamicCreator<hotel> {
	private:
		void printSubMenu() {
			console.ClearScreen();
			if (!hdata)
				HotelLoadData();
			hdata = true;
			console.ClearScreen();
			console << "请输入您的目的地：";
			string s;
			cin >> s;
			if (s == ".")return;
			console << s << endl;
			while (s != "北京" && s != "上海" && s != "广州") {
				fuzzySearch(s);
				outputFuzzy();
				console << "兄啊……再来一次罢：";
				cin >> s;
				if (s == ".")return;
				console << s << endl;
			}
			console << "欢迎来到" << s << "，那么首先能告诉我你们有多少人吗？";
			int n;
			cin >> n;
			console << n << endl;
			while (n >= 50 || n <= 0) {
				console << "你们是一个一个，一个一个一个……房客！（获取数据失败）";
				cin >> n;
				console << n << endl;
			}
			console << "嗯.." << n << "个人，那么要住几天呢：";
			int k;
			cin >> k;
			console << k << endl;
			while (k >= 20 || k <= 0) {
				console << "你们是一个一个，一个一个一个……（获取数据失败）" << endl;
				cin >> k;
			}
			findOption(s, n, k);
			console << "入驻" << n << "人可供选择的有 " << totOption << " 家酒店：" << endl;
			sortDefault();
			for (int i = 1; i <= totOption; i++) {
				console << endl;
				HotelOptions[i].HotelPointer->printInfo();
				console << "最低价格: " << HotelOptions[i].price << " ,详情请前往酒店前台问询" << endl;
			}
			return;
		}
	public:
		virtual void Work() {
			if (isLogin) {
				printSubMenu();
				cin.get();
			}
			else
				console << "请登录后使用此功能！" << endl;
		}
	};
	//class 命令名:public ReflectBase,DynamicCreator<命令名>

	class exit :public ReflectBase, DynamicCreator<exit> {
	public:
		exit() {}
		virtual void Work() {
			::exit(0);
		}//必须有的
	};
	class addfav :public ReflectBase, DynamicCreator<addfav> {
	public:
		addfav() {}
		virtual void Work() {
			if (isLogin) {
				Customer* p = reinterpret_cast<Customer*>(&user);
				p->ilike();
				cin.get();
			}
			else
				console << "请登录后使用此功能！" << endl;
		}
	};
	class showfav :public ReflectBase, DynamicCreator<showfav> {
	public:
		showfav() {}
		virtual void Work() {
			if (isLogin) {
				Customer* p = reinterpret_cast<Customer*>(&user);
				p->showlike();
				cin.get();
			}
			else
				console << "请登录后使用此功能！" << endl;
		}
	};
	class reply :public ReflectBase, DynamicCreator<reply> {
	public:
		reply() {}
		virtual void Work() {
			if (isLogin) {
				if (user.isAdmin()) {
					Admin* p = reinterpret_cast<Admin*>(&user);
					p->reply();
				}
				else {
					console << "只有管理员才可以回复！" << endl;
				}
			}
			else {
				console << "请登录后使用此功能！" << endl;
			}
			cin.get();
		}
	};
	class feedback :public ReflectBase, DynamicCreator<feedback> {
	public:
		feedback() {}
		virtual void Work() {
			if (isLogin) {
				if (!user.isAdmin()) {
					Customer* p = reinterpret_cast<Customer*>(&user);
					p->feedback();
				}
				else {
					console << "我 反 馈 我 自 己（失败）" << endl;
				}
			}
			else {
				console << "请登录后使用此功能！" << endl;
			}
			cin.get();
		}
	};
	class readback :public ReflectBase, DynamicCreator<readback> {
	public:
		readback() {}
		virtual void Work() {
			if (isLogin) {
				if (!user.isAdmin()) {
					Customer* p = reinterpret_cast<Customer*>(&user);
					p->read();
				}
				else {
					console << "管理员读个毛啊！" << endl;
				}
			}
			else {
				console << "请登录后使用此功能！" << endl;
			}
			cin.get();
		}
	};
	class showme :public ReflectBase, DynamicCreator<showme> {
	public:
		showme() {}
		virtual void Work() {
			if (isLogin) {
				console.stopDrawingThread();
				const string filenames[]{ ".\\buxingjie.dat",".\\changlong.dat",
					".\\guangzhouta.dat",".\\kuiyuan.dat",".\\shamian.dat" };
				int i = rand() % 4;
				console.displayImage(console.string2wstring(filenames[i]), COORD{ 0,0 });
			}
			else
				console << "请登录后使用此功能！" << endl;
		}
	};
	class whoami :public ReflectBase, DynamicCreator<whoami> {
	public:
		virtual void Work() {
			if (isLogin) {
				user.Show();
				cin.get();
			}
			else
				console << "我也不知道您是谁，因为您没登录>.<" << endl;
		}

	};
	class regist :public ReflectBase, DynamicCreator<regist> {
	public:
		virtual void Work() {
			if (!isLogin) {
				user.Regist();
				cin.get();
			}
			else
				console << "您已经登录，" << user.getUser() << endl;
		}

	};
	class change :public ReflectBase, DynamicCreator<change> {
	public:
		virtual void Work() {
			if (isLogin) {
				user.Change();
				cin.get();
			}
			else
				console << "要改谁的信息我也不知道呀>.<" << endl;
		}
	};
	class login :public ReflectBase, DynamicCreator<login> {
	public:
		virtual void Work() {
			if (!isLogin) {
				user.Login();
				cin.get();
				if (!user.getUser().empty())
					isLogin = true;
			}
			else
				console << "您已经登录，" << user.getUser() << endl;
			//cin.get();//清理最后的换行符
		}

	};
	class logout :public ReflectBase, DynamicCreator<logout> {
	public:
		virtual void Work() {
			if (isLogin) {
				isLogin = false;
				user.Logout();
				console.ClearScreen();
				console << Welcome;
			}
			else
				console << "兄啊你还没登录注销个毛啊（" << endl;
		}
	};
	class help :public ReflectBase, DynamicCreator<help> {
	public:
		virtual void Work() {
			console.ClearScreen();
			console << cHelp;
		}
	};
	class about :public ReflectBase, DynamicCreator<about> {
	public:
		about() {}
		virtual void Work() {
			console.ClearScreen();
			console << Welcome << about_info;
			//console.Dialog(about_info, COORD{ 5,3 }, COORD{ 80,20 });
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
	return false;
}

int main(void) {
	isLogin = false;
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