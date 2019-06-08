/*

[2019-05-25]
Train.h 火车类 头文件
使用方法：将Train.h放入编译器中的头文件夹中
		在cpp源文件上加入 #include<Train.h> 即可

注：以下的功能都是尽可能的模仿12306移动端的功能

思路：TrainList 保存的是列车的所有信息，是一个由Train类构成的vector
我们另建一个Station 类，用来保存：经过某一站的所有列车信息，便于后续操作
12306基本的操作有：查询某车次信息，查询某车站（某地）信息
根据客户要求（从哪到哪）给出可供选择的列车信息，并可以根据用户需求进行优先级排序

在12306中，有2种优先级顺序：发时最早，耗时最少。但这个和  "到时最早"  是不同的
12306在给出可供选择的方案时，用户可选择换乘（仅一次）或不换乘两种方式。
如果考虑不限换乘次数下的  "到时最早"，将会非常麻烦，原因许多。
一是目前在网上查询的资料 大多是地铁或者公交的最佳换乘，或者就是最少站数换乘算法，这个仅需要简单的最短路算法求解即可
然而火车不同，火车的到站时间是有限制的。很可能一个满足上述算法的换乘方案实际上是不可行的（换乘只能换乘当前时间之后到达的车次）
从实际意义角度上来说，换乘次数越多，越不可能达到所谓的到时最早，但从算法的理论角度上来看，这样说是不对的
所以，一个比较好的方法就是搜索。考虑到如果按列车车次建边，车站为点建图，从现实意义角度上来看，这必将是一个稠密图
这样我们跑搜索的算法效率极差极差，甚至说是不可能得到最优的结果，只能得到一个比较接近的值，这就和我们的初衷违背
因此，在上述考虑之下，我没有写这个到时最早的算法。而是完整的复刻12306的最多换乘一次的可行方案查找算法

另一个要点是，12306并没有提供所谓的花钱最少查找，因为在12306移动端我们可以看到：选择座位等级是确定选择了某一趟车次
在提交订单时才可以的，而且仅提供了简单的总价计算功能，和Hotel的最少花钱方案又有很大区别，因此按下不表。


大体框架：
struct viaStation,用来构成Train类
Train类 包括列车的基本信息 以及输出方式
Station类 包括车站名以及一个timetable，保存所有经过该车站的列车

*/
#include "pch.h"
#include "CConsole.h"

using namespace std;
#undef Train


/*

这一段考虑自己重写Time类 后来想想还是不太重要
如果时间多的话再写

class MyTime{
	public:
		static int ThisYear,ThisMonth;//仅考虑在某个月内的车票信息
		int day,hour,minute;//时间
		MyTime(){
			day=hour=minute=0;
		}
		MyTime(int inDay,int inHour,int inMinute){
			day=inDay;hour=inHour;minute=inMinute;
		}
		bool operator<(MyTime &R){
			if(day!=R.day) return day<R.day;
			else if(hour!=R.hour) return hour<R.hour;
				else if(minute!=R.minute) return minute<R.minute;
		}
		bool isLeapYear(){
			if(ThisYear%4==0 && ThisYear%100 !=0) return true;
			if(ThisYear%400 == 0) return true;
			return false;
		}
		bool operator+(int inMinute){//分钟数 (用于火车晚点)
			minute+=inMinute;
			hour+=(minute/60);minute%=60;
			if(hour==24) hour=0,day++;//不考虑天数溢出的问题
		}
};
int MyTime::ThisYear = 2019;
int MyTime::ThisMonth = 6;

*/

struct viaStation {
	int hour, minute;//时间 
	string stationName;//车站名 
	void outStationInfo() {
		console << stationName << " ("; if (hour < 10) console << 0;
		console << hour << ":"; if (minute < 10) console << 0;
		console << minute << ")";
	}
};

//时间比较 返回 L<R 的 bool 值 
bool cmpTime(viaStation &L, viaStation &R) {
	if (L.hour != R.hour) return L.hour < R.hour;
	else return L.minute < R.minute;
}

//名称比较 返回L<R 的 bool 值 
bool cmpName(viaStation &L, viaStation &R) {
	return L.stationName < R.stationName;
}

class Train {
public:
	int seat[3][2];//seat[i][0] 表示i+1等座位 还剩几张票 seat[i][1] 表示i+1等座位 要多少钱 
	string TrainName;//车次
	vector<viaStation> route;//途径地 

	//更改信息 
	void changeInfo() {
		cin >> TrainName;
		TrainName = console.UTF82ANSI(TrainName);
		//console<<TrainName<<endl; 
		int len; cin >> len;//途径地个数，0,len-1 分别表示首发站和终点站
		while (len--) {
			viaStation temp;
			cin >> temp.stationName >> temp.hour >> temp.minute;
			temp.stationName = console.UTF82ANSI(temp.stationName);
			//console << temp.stationName << endl;
			route.push_back(temp);
		}
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 2; j++)
				cin >> seat[i][j];//输入车票信息  
	}

	//输出基本信息 
	void outputBasicInfo() {
		console << this->TrainName << " : ";
		route[0].outStationInfo();
		console << " => ";
		route[route.size() - 1].outStationInfo();
		console << endl;
	}
	void outputSeat() {
		console << TrainName << "余票信息:" << endl;
		console << " 一等(" << seat[0][1] << "￥)" << seat[0][0] << "张 ";
		console << " 二等(" << seat[1][1] << "￥)" << seat[1][0] << "张 ";
		console << " 三等(" << seat[2][1] << "￥)" << seat[2][0] << "张 " << endl;
	}
	void outputRoute() {
		for (size_t i = 0; i < route.size(); i++) {
			console << i + 1 << "   "; route[i].outStationInfo();
			console << endl;
		}
	}

	//查询是否经过某一站 返回下标 
	int findRoute(string InputS) {
		int i = route.size() - 1;
		while (i >= 0 && route[i].stationName != InputS) i--;
		return i;
	}
};
class Station {//车站 
public:
	string name;//车站名 
	vector<Train*> timetable;// 时刻表
	void outputInfo() {
		/*
		输出所有经过该站的车次
		有一点值得注意，这个输出功能12306并没有。
		12306并不提供这种经过某一站的所有车次的输出显示，
		必须提供准确的车次和日期才可以
		所以没有排序
		*/
		size_t i = 0;
		while (i < timetable.size()) {
			console << i + 1 << ":";
			//输出时，如果是首发、终点站，则正常输出，否则在中间输出到本站的时间
			if (timetable[i]->route[0].stationName == name //首发站 
				|| timetable[i]->route[timetable[i]->route.size() - 1].stationName == name)//终点站 
				timetable[i]->outputBasicInfo();
			else {//非首发 或 终点站 
				console << timetable[i]->TrainName << " : ";
				timetable[i]->route[0].outStationInfo();
				console << " => "; int j = 0;
				while (timetable[i]->route[j].stationName != name) j++;
				timetable[i]->route[j].outStationInfo();
				console << " => ";
				timetable[i]->route[timetable[i]->route.size() - 1].outStationInfo();
				console << endl;
			}
			i++;
		}
	}
};

vector<Station*> StationList;//车站总表 

/*

查找车站，返回InputName车站所在车站总表的下标(int)
如果找不到返回-1
*/

int findStation(string InputName) {
	int i = StationList.size() - 1;
	while (i >= 0 && StationList[i]->name != InputName) i--;
	return i;
}

/*

排序：对给定的Train* 的vector进行排序
关键字 首发站时间排序(对于车站的timetable排序

*/
void sortByTime(vector<Train*> &Array) {
	int len = Array.size();
	for (int i = 0; i < len; i++)
		for (int j = 1; j < len; j++)
			if (!cmpTime(Array[j]->route[0], Array[j - 1]->route[0]))
				swap(Array[j], Array[j - 1]);
}

/*

添加一辆列车
注意，我们将列车经过的站台进行更新，也就是说，我们不提供addStation这种操作
所以，addTrain 将新加入列车总表的列车的所经过的车站信息进行更新
因此没有写在类内，而是写在类外


addTrain 格式(Example)

T151  车次
3  经过站数
北京 0 0  站名 几点几分到
上海 1 1
广州 2 2
1 2 2 3 3 4 一等座余票量，价格，二等座余票量，价格，三等余票，价格

T332
3
湖南 2 2
上海 3 3
香港 4 4
2 3 4 5 6 7

G312
3
北京 1 1
广州 3 3
香港 6 6
4 3 2 1 3 4

*/

vector<Train*> TrainList;//列车总表

void addTrain() {
	Train *temp = new Train;
	temp->changeInfo();//读入车辆信息
	TrainList.push_back(temp);
	for (size_t i = 0; i < temp->route.size(); i++) {
		//枚举经过的车站
		int index = findStation(temp->route[i].stationName);//查询车站所在下标
		if (index == -1) {
			//未找到车站，新建此车站
			Station *tempStation = new Station;
			tempStation->name = temp->route[i].stationName;
			tempStation->timetable.push_back(temp);
			StationList.push_back(tempStation);
		}
		else {
			StationList[index]->timetable.push_back(temp);
		}
	}
}

//查找车次 返回下标 
int findTrain(string InputS) {
	int i = TrainList.size() - 1;
	while (i >= 0 && TrainList[i]->TrainName != InputS) i--;
	return i;
}

//方案结构 
struct way {
	Train* first;
	Train* second;//如果无需换乘，则此项为NULL
	int begTime, endTime;//发时，结束时 
};
vector<way> Result;

void findResult(const string & s, const string & e) {
	while (!Result.empty()) Result.pop_back();//置为空
	string Start, End;//起点终点
	Start = s, End = e;
	int StartIndex, EndIndex;
	//cin >> Start >> End;
	//Start = console.UTF82ANSI(Start);
	//End = console.UTF82ANSI(End);
	//不考虑换乘
	for (size_t i = 0; i < TrainList.size(); i++) {
		StartIndex = TrainList[i]->findRoute(Start);
		EndIndex = TrainList[i]->findRoute(End);
		if (StartIndex == -1 || EndIndex == -1) continue; //此车不经过起点或终点
		if (EndIndex <= StartIndex)  continue; //车是反向的
	//	console<<"Here"<<endl;
		way temp;
		temp.begTime = TrainList[i]->route[StartIndex].hour * 60 + TrainList[i]->route[StartIndex].minute;
		temp.endTime = TrainList[i]->route[EndIndex].hour * 60 + TrainList[i]->route[EndIndex].minute;
		temp.first = TrainList[i];
		temp.second = NULL;
		Result.push_back(temp);
	}
	//考虑换乘
	StartIndex = findStation(Start);
	EndIndex = findStation(End);
	for (size_t i = 0; i < StationList[StartIndex]->timetable.size(); i++) {
		//这里枚举的是经过起点的所有车
		Train *Index = StationList[StartIndex]->timetable[i];
		int q = Index->findRoute(End);
		if (q == -1) {//不能直达才考虑换乘
			for (size_t j = 0; j < StationList[EndIndex]->timetable.size(); j++) {
				//枚举换乘的车辆
				Train *NIndex = StationList[EndIndex]->timetable[j];
			//	console<<"Attempting:"<<Index->TrainName<<"->"<<NIndex->TrainName<<endl;
				int p = NIndex->findRoute(Start);
				if (p == -1)//不能直达
					for (size_t k = 1; k < Index->route.size(); k++) {
					//	console<<"Here"<<endl;
						//这里枚举在哪一站换乘
						int r = NIndex->findRoute(Index->route[k].stationName);
						if (r != -1 && cmpTime(Index->route[k], NIndex->route[r])) { //可换乘
							way temp;
							temp.first = Index; temp.second = NIndex;
							temp.begTime = Index->route[Index->findRoute(Start)].hour * 60 + Index->route[Index->findRoute(Start)].minute;
							temp.begTime = NIndex->route[NIndex->findRoute(End)].hour * 60 + NIndex->route[NIndex->findRoute(End)].minute;
							Result.push_back(temp);
							break;//to for-j  	 
						}
					}//for-k  
			}//for-j 
		}//if-q
	}//for-i
}

//按发时最早排序 
void sortResultEarly() {
	for (size_t i = 0; i < Result.size(); i++)
		for (size_t j = 1; j < Result.size(); j++)
			if (Result[j].begTime < Result[j - 1].begTime) swap(Result[j], Result[j - 1]);
}

//按耗时最少排序 
void sortResultFast() {
	for (size_t i = 0; i < Result.size(); i++)
		for (size_t j = 1; j < Result.size(); j++)
			if (Result[j].endTime - Result[j].begTime < Result[j - 1].endTime - Result[j - 1].begTime) swap(Result[j], Result[j - 1]);
}

//输出结果
void outputResult() {
	console << endl << "共为您查到" << Result.size() << "条信息" << endl;
	for (size_t i = 0; i < Result.size(); i++) {
		if (Result[i].second == NULL) {
			console << Result[i].first->TrainName << "(直达)" << endl;
			Result[i].first->outputSeat();
			console << endl;
		}
		else {
			//换乘
			console << Result[i].first->TrainName << "(换乘) => " << Result[i].second->TrainName << endl;
			Result[i].first->outputSeat();
			Result[i].second->outputSeat();
			console << endl;
		}
	}
}

//读取数据
void TrainDataLoad() {
	int n;//总列车数
	//openfile
	freopen(".\\TrainData.txt", "r", stdin);
	cin >> n;
	while (n--)
		addTrain();
	cin.clear();
}
