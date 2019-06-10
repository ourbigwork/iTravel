
/*

[2019-05-18]
Hotel.h 旅馆 酒店类 头文件
使用方法：将Hotel.h放入编译器中的头文件夹中
		在cpp源文件上加入 #include<Hotel.h> 即可

*/
#include "pch.h"
#include "CConsole.h"

using namespace std;
#undef Scenic
#undef Position
#undef Region


#undef GuestRoom

class GuestRoom {//客房类 
public:
	string name;//房间属性
	int capacity;//房间容量 能住多少人 
	int price;//价格 
};

class GuestRoomClass : public GuestRoom {// GuestRoomClass是继承GuestRoom 用于生成链表的节点类 
public:
	GuestRoomClass *next;
	GuestRoomClass() {
		cin >> name >> capacity >> price;
		name = console.UTF82ANSI(name);
		next = NULL;
	}

	void printInfo() {
		console << name << ' ' << capacity << ' ' << price << endl;
	}
};

class Hotel {//酒店类类 
public:
	string name;//酒店名 
	string address;//地址
	GuestRoomClass *RoomList;//房间链表头 
	GuestRoomClass *RoomListTail;//房间链表尾 
};

class HotelClass :public Hotel {//HotelClass 是继承Hotel 用于生成链表的节点类 
public:
	HotelClass *next;

	/*

	添加一个房间 ,注意这里是针对某一个酒店添加
	考虑到 name 并不是名字 而是属性（大床房 标准间之类） 所以没有查重
	返回这个房间的指针

	*/
	GuestRoomClass* addRoom() {
		GuestRoomClass *tempPoint = new GuestRoomClass();
		if (this->RoomList == NULL) this->RoomList = tempPoint;
		else RoomListTail->next = tempPoint;
		RoomListTail = tempPoint;
		return tempPoint;
	}

	/*

	删除一个房间，注意这里是针对某一个酒店添加
	接口是一个房间类指针 以做到精确删除
	返回一个bool 表示是否成功删除

	*/
	bool deleteRoom(GuestRoomClass *Input) {
		GuestRoomClass *Index = RoomList;
		GuestRoomClass *INext = Index->next;
		if (RoomList == Input) {
			RoomList = RoomList->next;
			if (RoomListTail == Input) RoomListTail = NULL;
			free(Input);
			return true;
		}
		while (Index != NULL) {
			if (INext == Input) {
				Index->next = INext->next;
				if (INext == RoomListTail) RoomListTail = Index;
				free(INext);
				return true;
			}
			else {
				Index = Index->next;
				if (INext != NULL) INext = INext->next;
			}
		}
		return false;
	}

	HotelClass() {
		cin >> name >> address;
		name = console.UTF82ANSI(name);
		address = console.UTF82ANSI(address);
		RoomList = RoomListTail = NULL;
		next = NULL;
	}
	void printInfo() {
		console << name << "  @" << address << endl;
	}
};

class City {//注意这里和Scenic.h的Region类是不同的 用City区分 
public:
	string name;//城市名
	HotelClass *HotelList;//酒店链表头
	HotelClass *HotelListTail;//酒店链表尾 
};

class CityClass :public City {//City Class 是继承City 用于生成链表的节点类
public:
	CityClass *next;

	/*

	添加一个酒店，注意这里是针对某个城市而言添加
	所以必须在CityClass类的实例内访问
	注意，即使是同一个城市同名酒店也可能有很多
	所以这里没有查重 直接添加即可
	返回这个酒店的指针

	*/
	HotelClass* addHotel() {
		HotelClass *tempPoint = new HotelClass();
		if (HotelList == NULL)  HotelList = tempPoint;
		else HotelListTail->next = tempPoint;
		HotelListTail = tempPoint;
		return tempPoint;
	}

	/*

	删除一个酒店，注意这里是针对某个城市而言删除
	所以必须在Cityclass类的实例内访问
	而这里的接口必须是一个HotelClass的指针以精确删除
	返回一个bool型 表示是否成功删除

	*/
	bool deleteHotel(HotelClass *Input) {
		HotelClass *Index = HotelList, *INext = HotelList->next;
		if (Index == Input) {
			//链表头删除
			HotelList = HotelList->next;
			if (HotelListTail == Input) HotelListTail = NULL;
			free(Index); return true;
		}
		while (Index != NULL) {
			if (INext == Input) {
				Index->next = INext->next;
				if (INext == HotelListTail) HotelListTail = Index;//链表尾删除 
				free(INext);
				return true;
			}
			else {
				Index = Index->next;
				if (INext != NULL) INext = INext->next;
			}
		}
		return false;
	}

	void printCityInfo() {
		console << name << endl;
		HotelClass *Index = HotelList;
		while (Index != NULL) {
			console << " -> ";
			Index->printInfo();
			Index = Index->next;
		}
		console << endl;
	}
};
CityClass* CityList = NULL;//地点链表头
CityClass* CityListTail = NULL;//地点链表尾

/*

查找一个城市，返回其对应的链表节点(CityList)指针
如果不存在 返回NULL
接口：城市名string

*/
CityClass* findCity(string targetS) {
	CityClass *Index = CityList;
	if (Index != NULL)
		while (Index != NULL && Index->name != targetS) {
			Index = Index->next;
		}
	return Index;
}

/*

查找一个酒店
注意 各地可能有同名的酒店，所以要把同名的全输出
接口：酒店名string
输出：一个resultHotel类型组成的链表，链表中每一个节点都代表一个Hotel
该链表名为 findHotelList ,也是头节点指针

*/
struct resultHotel {
	HotelClass *HotelPointer;
	resultHotel *next;
	CityClass *Super;//这是一个用来访问父亲节点的指针
}*findHotelList, *findHotelTail;

/*

向findHotelList链表最后面插入一个InsertPoint所指向的节点

*/
void resHotelInsert(HotelClass *InsertPoint, CityClass *Father) {//对resultHotel插入节点 
	resultHotel *tempPoint = new resultHotel;
	tempPoint->HotelPointer = InsertPoint;
	tempPoint->next = NULL;
	tempPoint->Super = Father;
	if (findHotelList == NULL)
		findHotelList = tempPoint;
	else
		findHotelTail->next = tempPoint;
	findHotelTail = tempPoint;
}

void findHotel(string targetS) {
	findHotelList = findHotelTail = NULL;
	CityClass *Index = CityList;
	while (Index != NULL) {
		HotelClass *HIndex = Index->HotelList;// HIndex 枚举是哪一个酒店
		while (HIndex != NULL) {
			if (HIndex->name == targetS)
				resHotelInsert(HIndex, Index);
			HIndex = HIndex->next;
		}
	}
}

/*

输出findHotelList中的信息

*/
void outputHotelFind() {
	resultHotel *Index = findHotelList;
	while (Index != NULL) {
		console << Index->Super->name << ":";
		Index->HotelPointer->printInfo();
		Index = Index->next;
	}
}

/*

添加一个城市，接口：城市名
如果城市不存在则添加城市
返回的是这个城市的指针

*/

CityClass* addCity(string InputS) {
	CityClass *tempPoint = findCity(InputS);
	if (tempPoint == NULL) {
		tempPoint = new CityClass;
		tempPoint->name = InputS;
		tempPoint->next = NULL;
		if (CityList == NULL) CityList = tempPoint;
		else CityListTail->next = tempPoint;
		CityListTail = tempPoint;

		tempPoint->HotelList = tempPoint->HotelListTail = NULL;
	}
	return tempPoint;
}

/*

删除一个城市，接口：城市名
返回一个bool型表示是否成功删除

*/
bool deleteCity(string InputS) {
	return false;
}


/*

读取数据
数据文件要求：
第一行表示地区数 接下来描述一个地区信息

	对于每个地区 第一行城市名 后接数字表示酒店个数
	接下来描述酒店信息

		对于每个酒店 第一行描述基本信息 后接数字表示房间数
		接下来描述房间信息

			对于每个房间 仅一行描述房间的基本信息

*/
void HotelLoadData() {
	freopen(".\\HotelData.dat", "r", stdin);
	string InputS;
	int totCity = 0; cin >> totCity;//地区数
	while (totCity--) {
		cin >> InputS;
		InputS = console.UTF82ANSI(InputS);
		CityClass *Index = addCity(InputS);
		int totHotel = 0; cin >> totHotel;//酒店数
		while (totHotel--) {
			HotelClass *HIndex = Index->addHotel();
			int totRoom = 0; cin >> totRoom;//房间数 
			while (totRoom--)
				HIndex->addRoom();
		}
	}
	freopen("CON", "r", stdin);
}

/*

根据用户输入筛选合适的宾馆
接口：城市名string 人数int 天数int
输出一个 optionHotel类 数组，是所有可供选择的酒店以及所需价格
这里没有选用链表是因为排序不方便，而且不易作后续处理，
是空间复杂度 换取时间复杂度和编程复杂度的作法

若当前地区无合适的酒店（无酒店 和 无满足条件的酒店） 输出相应提示
若存在合适的酒店，按某种顺序输出适合的酒店以及所需要的价钱
当同一酒店存在不同的解决方案时，优先考虑价钱最低的

上述的某种顺序指的是：（默认）中序 ，（非默认）价格升降序
中序指的是价格按顺序排列后优先输出中间价位比较合理
然后一前一后地输出完整的酒店序列

*/

struct optionHotel {
	HotelClass *HotelPointer;//指向酒店
	int price;//价钱 (乘天数后) 
}HotelOptions[30];

int totOption = 0;//所有可供选择的酒店数 

/*

calcMinPrice 计算对于给定酒店在客户指定的条件下最少代价花费
int 型返回，返回最少代价花费，默认大于0.如果返回值为-1
则说明此酒店没有合适的客房供入住 上层菜单将依次为依据进行下一步操作

动态规划思想，设f(n)表示n个人入住所要的最小花费
枚举房间，设房间i可住Ci人，价格Pi ,那么对于所有的i<=Ci,需要比较f(i)和Pi的值
实际意义表现为：i个人住容量为Ci，价格为Pi的房间的花费现在是否更小
对于所有i，如果f(i+Ci)<f(i)+Pi,更新f(i+Ci)的值
实际意义表现为：存在一个更优的方案使得住i+Ci个人的花钱数更少

**然而这里有一个很严重的问题 假设只有一个单人间 价格为108 其他都是双人间且价格贵的离谱（上千）
如果按上述方法进行操作发现入住3人 的最小价格为316,很明显是不对的 原因在于
更新f(i+Ci)时，很有可能f(i)是已经更新过了的值，等价于用了该房间以后再用一次 是不对的
因此我们使用滚动数组来替换。设cnt=0，每次与1异或，cnt表示当前处理的数组行
每次更新是cnt^1的值更新cnt的值 这样就不会出错

*/
int calcMinPrice(HotelClass *Index, int peopleNum, int dayNum) {
	int f[2][20], ret = 2147483647;
	//最多十个人同时入住（来自携程官网）
	//可能存在一种供住人数更多且花钱更少的方案 因此要多加几位 
	f[0][0] = f[1][0] = 0;
	for (int i = 1; i <= 19; i++) f[0][i] = f[1][i] = 200000000;
	GuestRoomClass *ite = Index->RoomList;
	int cnt = 0;
	while (ite != NULL) {
	//	ite->printInfo();
		for (int i = 1; i < 20 - ite->capacity; i++) {
			if (i <= ite->capacity) f[cnt][i] = min(f[cnt ^ 1][i], ite->price);
			if (f[cnt ^ 1][i] + ite->price < f[cnt ^ 1][i + ite->capacity])
				f[cnt][i + ite->capacity] = f[cnt ^ 1][i] + ite->price;
			if (i >= peopleNum) ret = min(ret, f[cnt][i]);
		}
		ite = ite->next;
//		for(int i=1;i<20;i++) console<<f[cnt][i]<<' ';console<<endl;
		cnt ^= 1;
	}
	/*for(int pNum=1;pNum<15;pNum++){
		GuestRoomClass *ite = Index->RoomList;
		while(ite != NULL){
			f[pNum] = min (f[pNum] , f[max (pNum-ite->capacity, 0)]+ite->price);
			ite=ite->next;
		}
		if(pNum>=peopleNum)
			ret = min(ret,f[pNum]);
	}*/
	if (ret > 100000000) ret = -1;

//	console<<"============================="<<endl;
	return ret;
}

void findOption(string cityString, int peopleNum, int dayNum) {
	totOption = 0;
	CityClass *Index = findCity(cityString);
	if (Index != NULL) {
		HotelClass *HIndex = Index->HotelList;
		while (HIndex != NULL) {//遍历酒店列表 
			//此时HIndex 指向的是一个酒店

			int retNum = calcMinPrice(HIndex, peopleNum, dayNum);
			if (retNum) {
				++totOption;
				HotelOptions[totOption].HotelPointer = HIndex;
				HotelOptions[totOption].price = retNum;
			}
			HIndex = HIndex->next;
		}
	}
}
/*

将struct optionHotel的HotelOptions数组排序
关键字分别为 价格从低到高， 价格从高到低 ，中序排序
所谓中序已经在上文中给出定义， 这里使用algorithm 库的 qsort函数进行排序
需要完成cmp函数，用来比较，作为是否交换的依据

*/

int cmpPriceUp(const void *a, const void *b) {
	optionHotel x = *(optionHotel *)a;
	optionHotel y = *(optionHotel *)b;
	return x.price > y.price;
}

int cmpPriceDown(const void *a, const void *b) {
	optionHotel x = *(optionHotel *)a;
	optionHotel y = *(optionHotel *)b;
	return x.price < y.price;
}

void sortByPriceUp() {
	qsort(HotelOptions + 1, totOption, sizeof(optionHotel), cmpPriceUp);
}

void sortByPriceDown() {
	qsort(HotelOptions + 1, totOption, sizeof(optionHotel), cmpPriceDown);
}

void sortDefault() {
	sortByPriceUp();
	//先升序排列
	vector<optionHotel> tempArray;
	int i = totOption / 2, j = 1 + totOption / 2;
	//从中间向两边扩展 
	while (i >= 1 || j <= totOption) {
		if (i >= 1) tempArray.push_back(HotelOptions[i--]);
		if (j <= totOption)tempArray.push_back(HotelOptions[j++]);
	}
	for (i = 1; i <= totOption; i++)
		HotelOptions[i] = tempArray[i - 1];
}

/*
酒店模糊搜索
考虑到是中文字符 占两个字节 所以两两一处理
例如 设string s="广州", 那么 s[0]s[1] 为 '广'，s[2]s[3]为'州'
现在考虑两个字符的相似度比较，设前一个字符编码是i1,i2 后一个为j1,j2
由于中文是区块码 (靠前区块)区内按拼音排序 /(靠后区块)区内按偏旁部首排序
靠前区主要是常用字，靠后区主要是生僻字。而出现在酒店名称上的字大多是常用字，也即在靠前的区块，
所以i1和j1的差距影响因子大，i2,j2的差距影响因子小。
我们设两个权重w1,w2, dif = w1*|i1-j1| + w2*|i2-j2| 来计算两个中文字符的差异度
dif 越大 说明差别越大，越小则说明越相似。且明显的有dif的取值是[0,+oo)
可以用指数函数映射成匹配度match,即match = k^dif,(0<k<1),
k确定match的下降速度 ，映射后match 取值是 (0~1],完全一样的两个字符match=1
我们计算输入字符串中的每一个字符和对应酒店的名称的匹配度的平均值作为该酒店对输入的匹配度
考虑到地名影响，看输入内是否有城市名。如果输入有城市名，则应优先考虑该城市的酒店
也就是说 城市 所占的比重非常大，设这里得出的CityMatch也是处于(0,1]
然而 CityMatch的取值(略去精度)只会出现三种情况：1 或 0.5 或 0
而如果是1或0.5则应该提高城市的比重（出现了完整或部分城市名）
将CityMatch开根号，作为权重于酒店匹配度相乘，作为最终的匹配度结果，按该结果排序即可

exp:

	string s="背景别墅";//北京？
	fuzzySearch(s);
	outputFuzzy();
*/
struct fuzzyNode {
	HotelClass *Node;
	double sMark;//相似度 
};
vector<fuzzyNode> fuzzyRes;

bool cmp_sMark(fuzzyNode L, fuzzyNode R) {
	return L.sMark > R.sMark;
}


double calcSimilarity(string L, string R) {
	//对中文处理
	int Ll = L.length(), Rl = R.length();
	//console<<Ll<<' '<<Rl<<endl;
	double w1 = 0.65, w2 = 0.35;
	double totM = 0.0;
	for (int i = 0; i * 2 < Ll; i++) {//L匹配串 R模式串 
		double maxMatch = 0;
		int i1 = (int)L[i * 2], i2 = (int)L[i * 2 + 1];
		for (int j = 0; j * 2 < Rl; j++) {
			int j1 = (int)R[j * 2], j2 = (int)R[j * 2 + 1];
			double dif = w1 * abs(i1 - j1) + w2 * abs(i2 - j2);
			//console<<i1<<' '<<i2<<' '<<j1<<' '<<j2<<endl;
			double mat = pow(0.6, dif);
			maxMatch = mat > maxMatch ? mat : maxMatch;
		}//console<<maxMatch<<endl;
		totM += maxMatch;
	}
	totM = totM * 2 / (double)Ll;//消除长度影响
	//console<<L<<' '<<R<<' '<<totM<<endl;console<<"======"<<endl;
	return totM;
}

void fuzzySearch(string InputS) {
	while(!fuzzyRes.empty()) fuzzyRes.pop_back(); 
	CityClass *CIndex = CityList;
	double Match = 0;
	while (CIndex != NULL) {//枚举城市
		double CityMatch = 0;
		HotelClass *HIndex = CIndex->HotelList;
		CityMatch = sqrt(calcSimilarity(CIndex->name, InputS));//城市匹配度 
		while (HIndex != NULL) {//枚举酒店 计算酒店匹配度 
			double HotelMatch = calcSimilarity(InputS, HIndex->name);
			Match = CityMatch * HotelMatch;
			fuzzyRes.push_back(fuzzyNode{ HIndex, Match });
			HIndex = HIndex->next;
		}
		CIndex = CIndex->next;
	}
	sort(fuzzyRes.begin(), fuzzyRes.end(), cmp_sMark);
}

void outputFuzzy() {
	console << "您是不是在查找：";
	fuzzyRes[0].Node->printInfo();
	console << endl << "搜索结果(相似度前10):" << endl;
	for (int i = 0; i < 10; i++) {
		console << fuzzyRes[i].Node->name << " 相似度: " << fuzzyRes[i].sMark << endl;
	}
}

