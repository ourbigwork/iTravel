
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
		next = nullptr;
	}
};

class Hotel {//酒店类类 
public:
	string name;//酒店名 
	string contact;//联系方式 
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
		if (this->RoomList == nullptr) this->RoomList = tempPoint;
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
			if (RoomListTail == Input) RoomListTail = nullptr;
			free(Input);
			return true;
		}
		while (Index != nullptr) {
			if (INext == Input) {
				Index->next = INext->next;
				if (INext == RoomListTail) RoomListTail = Index;
				free(INext);
				return true;
			}
			else {
				Index = Index->next;
				if (INext != nullptr) INext = INext->next;
			}
		}
		return false;
	}

	HotelClass() {
		cin >> name >> contact >> address;
		next = nullptr;
	}
	void printInfo() {
		console << name << " " << address << " " << contact << endl;
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
		if (HotelList == nullptr)  HotelList = tempPoint;
		else HotelListTail->next = tempPoint;
		HotelListTail = tempPoint;
		return HotelListTail;
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
			if (HotelListTail == Input) HotelListTail = nullptr;
			free(Index); return true;
		}
		while (Index != nullptr) {
			if (INext == Input) {
				Index->next = INext->next;
				if (INext == HotelListTail) HotelListTail = Index;//链表尾删除 
				free(INext);
				return true;
			}
			else {
				Index = Index->next;
				if (INext != nullptr) INext = INext->next;
			}
		}
		return false;
	}
};
CityClass* CityList = nullptr;//地点链表头
CityClass* CityListTail = nullptr;//地点链表尾

/*

查找一个城市，返回其对应的链表节点(CityList)指针
如果不存在 返回nullptr
接口：城市名string

*/
CityClass* findCity(string targetS) {
	CityClass *Index = CityList;
	if (Index == nullptr)
		console << "Warning:No such city found." << endl;
	else {
		while (Index != nullptr && Index->name != targetS) {
			Index = Index->next;
		}
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
	tempPoint->next = nullptr;
	tempPoint->Super = Father;
	if (findHotelList == nullptr)
		findHotelList = tempPoint;
	else
		findHotelTail->next = tempPoint;
	findHotelTail = tempPoint;
}

void findHotel(string targetS) {
	findHotelList = findHotelTail = nullptr;
	CityClass *Index = CityList;
	while (Index != nullptr) {
		HotelClass *HIndex = Index->HotelList;// HIndex 枚举是哪一个酒店
		while (HIndex != nullptr) {
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
	while (Index != nullptr) {
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
	if (tempPoint == nullptr) {
		tempPoint = new CityClass;
		tempPoint->name = InputS;
		tempPoint->next = nullptr;
		if (CityList == nullptr) CityList = tempPoint;
		else CityListTail->next = tempPoint;
		CityListTail = tempPoint;
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
	//openFile
	string InputS;
	int totCity = 0; cin >> totCity;//地区数 
	while (totCity--) {
		cin >> InputS;
		CityClass *Index = addCity(InputS);
		int totHotel = 0; cin >> totHotel;//酒店数
		while (totHotel--) {
			HotelClass *HIndex = Index->addHotel();
			int totRoom = 0; cin >> totRoom;//房间数
			while (totRoom--)
				HIndex->addRoom();
		}
	}
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
枚举房间，设房间i可住Ci人，价格Pi 有
for_all i:1->inf, f(n)=min { f(n-Ci) + Pi }
则说明有两层循环 一层为人数循环 for( peopleNum: 1->n)
二层为房间枚举循环 由于是链表 没有下标 但原理是相同的
初始化: for_all i:1->inf, f(i)=inf , f(0) = 0
最后 ans=mfor_all i:n->inf ,min{f(i)}

*/
int calcMinPrice(HotelClass *Index, int peopleNum, int dayNum) {
	int f[15], ret = 2147483647;
	//最多十个人同时入住（来自携程官网）
	//可能存在一种供住人数更多且花钱更少的方案 因此要多加几位 
	f[0] = 0;
	for (int i = 1; i <= 15; i++) f[i] = 2147483647;
	for (int pNum = 1; pNum < 15; pNum++) {
		GuestRoomClass *ite = Index->RoomList;
		while (ite != nullptr)
			f[pNum] = min(f[pNum], f[max(pNum - ite->capacity, 0)] + ite->price);
		if (pNum >= peopleNum)
			ret = min(ret, f[pNum]);
	}
	if (ret > 100000000) ret = -1;
	else return ret;
}

void findOption(string cityString, int peopleNum, int dayNum) {
	totOption = 0;
	CityClass *Index = findCity(cityString);
	if (Index != nullptr) {
		HotelClass *HIndex = Index->HotelList;
		while (HIndex != nullptr) {//遍历酒店列表 
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

void sortDefalut() {
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


