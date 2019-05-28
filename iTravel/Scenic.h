/*

[2019-05-16 20:26] [wyw]
Scenic.h: 景点类头文件
使用方法：将Scenic.h放入编译器中的头文件夹中
		在cpp源文件上加入 #include<Scenic.h> 即可

Scenic类 景点类，包含名称，热度，价格
Position类 地点类， 包含城市名，所含景点个数，Scenic类指针数组
RegionClass类 地点类+指针， 用于构建链表的节点封装类

注意：部分函数和头文件仅在windows下有效，中文部分在linux下会出现问题

Region （RegionClass类 指针），储存所有景点信息的链表头
RegionTail （RegionClass类 指针），储存所有景点信息的链表尾

读入的景点信息放入Data文件内，
/================
/	Data文件要求：
/	第一行数字表示地区个数 例如 34(表示34个省)
/	接下来用空格分开所有字符串
/	第一个字符串表示地区名 后一个数字表示景点个数
/	接下来每个景点 景点名 价格 热度 ， 后两者是数字
/	例如：
/
/	34
/	北京 10
/	故宫 60 9.9
/	天安门 0 9.8
/	...
/
/	四川 10
/	都江堰 78 9.5
/	锦里古街 0 9.4
/	...
/
/================

目前已有：
LoadData 读入数据
OutputRegion 输出完整信息
OutputSpecific 输出城市信息
findRegion 查找城市
sortBy Heat/Price,Down/Up 根据不同关键字升降序排序
Add/Delete Region/Scenic 增添/删除 景点/地区
RandomRecommand 随机推荐
TODO： 模糊搜索(?)
*/
#include "pch.h"
#include "CConsole.h"

using namespace std;
#undef Scenic
#undef Position
#undef Region

class Scenic {
public:
	string name;
	double price;//价格
	double heat;//景点热度
	Scenic() {
		cin >> name >> heat >> price;
	}
};

class Position {
public:
	string name;//地名
	int len;//著名景点个数
	Scenic *p[100];//上限100 这里没有使用链表是因为 可以但不必要 
};

class RegionClass :public Position {
public:
	static int tot_Region;//总地区数
	static RegionClass *Region;
	static RegionClass *RegionTail;
	RegionClass *next;
	RegionClass() {
		cin >> name >> len;
		next = nullptr;
	}
};

int RegionClass::tot_Region = 0;
RegionClass *RegionClass::Region = nullptr;
RegionClass *RegionClass::RegionTail = nullptr;


/*
OutLoad 用于产生读取数据的动画效果
延迟一秒显得更加真实
*/
void OutLoad() {
	console.ClearScreen();
	//system("cls");
	console << "Loading data..." << endl;
	Sleep(1000);//顿挫感
	console.ClearScreen();
}
void LoadData() {
	// Openfile;
	freopen(".\\Data.txt","r",stdin);
	OutLoad();
	cin >> RegionClass::Region->tot_Region;
	for (int i = 1; i <= RegionClass::Region->tot_Region; i++) {
		RegionClass *tempRegion = new RegionClass();
		if (i == 1) RegionClass::Region = tempRegion;
		else RegionClass::RegionTail->next = tempRegion;
		RegionClass::RegionTail = tempRegion;
		for (int j = 1; j <= tempRegion->len; j++) {
			tempRegion->p[j] = new Scenic();
		}
	}
	Sleep(1000);//顿挫感
	console << "Data load finished" << endl;
	Sleep(1000);
	console.ClearScreen();
	freopen("CON","r",stdin);
}

/*

完整地输出所有的信息
格式是
 -城市1
	- 景点1 热度：热度 价格：价格
	- 景点2 热度：热度 价格：价格
 - 城市2
	- 景点3 热度：热度 价格：价格
	- 景点4 热度：热度 价格：价格

*/
void OutputRegion() {

	RegionClass *index = RegionClass::Region;
	if (index == nullptr) {
		console << "Warning: No data found." << endl;
		return;
	}
	while (index != nullptr) {
		console << "|-" << index->name << endl;
		for (int i = 1; i <= index->len; i++) {
			console << "  |-";
			console << index->p[i]->name << "  热度:" << index->p[i]->heat << "  价格:" << index->p[i]->price << endl;
		}
		index = index->next;
	}

	console << endl;
	return;
}

/*

按城市输出景点

*/
void OutputSpecific(RegionClass *index) {
	if (index == nullptr) return;
	else {
		console << index->name << endl;
		for (int i = 1; i <= index->len; i++) {
			console << "|-";
			console << index->p[i]->name << "  热度:" << index->p[i]->heat << "  价格:" << index->p[i]->price << endl;
		}
	}
}

/*

根据输入的城市名寻找对应在Region链表中的位置

*/
RegionClass* FindRegion(string targetRegion) {
	RegionClass *ret = RegionClass::Region;
	while (ret != nullptr && ret->name != targetRegion) ret = ret->next;
	if (ret == nullptr) console << "Warning : No such region found." << endl;
	return ret;
}
/*

根据不同的关键字进行排序
注意这里的排序仅仅针对某个城市下的景点进行排序
使用sort函数即可

*/

bool cmp_Heat_Down(Scenic *a, Scenic *b) {
	return a->heat < b->heat;
}

bool cmp_Heat_Up(Scenic *a, Scenic *b) {
	return a->heat > b->heat;
}

bool cmp_Price_Down(Scenic *a, Scenic *b) {
	return a->price < b->price;
}

bool cmp_Price_Up(Scenic *a, Scenic *b) {
	return a->price > b->price;
}

/*

接口输入: 某个城市的RegionClass指针
可以是Region 链表中的某一项
这里的排序都是冒泡排序
分别是：

热度 升序 热度 降序 价格 升序 价格 降序

*/

void sortByHeatDown(RegionClass *index) {
	for (int i = 1; i <= index->len; i++)
		for (int j = 1; j < index->len; j++)
			if (cmp_Heat_Down(index->p[j], index->p[j + 1]))
				swap(index->p[j], index->p[j + 1]);

}

void sortByHeatUp(RegionClass *index) {
	for (int i = 1; i <= index->len; i++)
		for (int j = 1; j < index->len; j++)
			if (cmp_Heat_Up(index->p[j], index->p[j + 1]))
				swap(index->p[j], index->p[j + 1]);
}

void sortByPriceDown(RegionClass *index) {
	for (int i = 1; i <= index->len; i++)
		for (int j = 1; j < index->len; j++)
			if (cmp_Price_Down(index->p[j], index->p[j + 1]))
				swap(index->p[j], index->p[j + 1]);
}

void sortByPriceUp(RegionClass *index) {
	for (int i = 1; i <= index->len; i++)
		for (int j = 1; j < index->len; j++)
			if (cmp_Price_Up(index->p[j], index->p[j + 1]))
				swap(index->p[j], index->p[j + 1]);
}


/*

添加一个地区：按照最上方对Data文件的规范输入

*/
void AddRegion() {
	string InputS; cin >> InputS;
	RegionClass *temp = FindRegion(InputS);
	// 若地区已经存在 增加景点时直接添加。 
	if (temp != nullptr) {
		int lenDelta; cin >> lenDelta;
		for (int i = 1; i <= lenDelta; i++) {
			temp->p[temp->len + i] = new Scenic();
		}
		temp->len += lenDelta;
	}
	else {
	//添加地区不存在 新建链表节点放置链表尾 
		for (int i = 1; i <= temp->len; i++)
			temp->p[i] = new Scenic();
		if (RegionClass::Region == nullptr)
			RegionClass::Region = temp;
		else
			RegionClass::RegionTail->next = temp;
		RegionClass::RegionTail = temp;
		temp->tot_Region++;//总的地区数++ 
	}
}

/*

删除一个地区：这里是删除一个完整城市的信息
输入的是一个城市名

*/
void DeleteRegion(string InputS) {
	RegionClass *Index = RegionClass::Region;
	RegionClass *Target = RegionClass::Region->next;

	//如果Region 链表头就是我们所删除的节点 
	if (Index->name == InputS) {
		RegionClass::Region = RegionClass::Region->next;
		if (RegionClass::RegionTail->name == InputS)  //链表中只存在一个节点 且恰为想删除的节点 
			RegionClass::RegionTail = RegionClass::Region = nullptr;
		free(Index); //Index 此时就是一开始的链表头 
	}
	else {
		//目标节点不存在 或者 在非链表头节点
		while (Target->name != InputS && Target != nullptr) {
			Index = Target;
			Target = Target->next;
		}
		if (Target == nullptr) {
			//目标节点未找到
			console << "Warning : No such region found." << endl;
			return;
		}
		else {
			//目标节点找到，是Target，且Target的前驱是Index
			Index->next = Target->next;
			free(Target);
			Index->tot_Region--;//总的地区数减少 
		}
	}
}

/*

增加一个景点：输入的是一个城市名

*/
void AddScenic(string InputS) {
	RegionClass *Index = FindRegion(InputS);
	//如果该城市并不存在 等价于新增一个城市，该城市仅有一个景点 
	if (Index == nullptr) {
		Index = new RegionClass;
		Index->name = InputS;
		Index->len = 1;
		Index->p[1] = new Scenic();
		//以上：增加一个城市，一个景点 
		if (RegionClass::Region == nullptr)
			RegionClass::Region = Index;
		else
			RegionClass::RegionTail->next = Index;
		RegionClass::RegionTail = Index;
		RegionClass::RegionTail->tot_Region++;
	}
	else {
		Index->len++;
		Index->p[Index->len] = new Scenic();
	}
}

/*

删除一个景点：输入的是一个城市名
我们没有提供直接删除景点的操作，必须经过城市-景点进行精确定位
因为删除操作是谨慎的

*/

void DeleteScenic(string InputS) {
	RegionClass *Index = FindRegion(InputS);
	if (Index == nullptr) return;
	else {
		cin >> InputS;//这里的InputS是景点名 不是地区名
		bool isfound = false;//状态 是否找到  
		for (int i = 1; i <= Index->len; i++) {
			if (Index->p[i]->name == InputS)
				isfound = true;
			if (isfound == true)
				if (i < Index->len)// 非最后一个景点
					Index->p[i] = Index->p[i + 1];
			//上述操作在于：将目标景点的节点之后的所有节点向前平移 
		}
		if (isfound == false)//未找到景点
			console << "Warning : No such scenic found.";
	}
}

/*

随机推荐
随机推荐某一个城市的某一个景点
**这里不等于根据用户的喜好进行推荐

*/
void RandomRecommand() {
	srand(time(0));
	int MagicN = rand() % RegionClass::Region->tot_Region;
	RegionClass *Index = RegionClass::Region;
	while (MagicN--)
		Index = Index->next;
	MagicN = 1 + rand() % Index->len;
	console << "随机推荐：" << Index->name << " " << Index->p[MagicN]->name << endl;
}

/*

TODO：
模糊搜索

*/
