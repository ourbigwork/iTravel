/*

[2019-05-16 20:26] [wyw]
Scenic.h: ������ͷ�ļ�
ʹ�÷�������Scenic.h����������е�ͷ�ļ�����
		��cppԴ�ļ��ϼ��� #include<Scenic.h> ����

Scenic�� �����࣬�������ƣ��ȶȣ��۸�
Position�� �ص��࣬ �������������������������Scenic��ָ������
RegionClass�� �ص���+ָ�룬 ���ڹ�������Ľڵ��װ��

ע�⣺���ֺ�����ͷ�ļ�����windows����Ч�����Ĳ�����linux�»��������

Region ��RegionClass�� ָ�룩���������о�����Ϣ������ͷ
RegionTail ��RegionClass�� ָ�룩���������о�����Ϣ������β

����ľ�����Ϣ����Data�ļ��ڣ�
/================
/	Data�ļ�Ҫ��
/	��һ�����ֱ�ʾ�������� ���� 34(��ʾ34��ʡ)
/	�������ÿո�ֿ������ַ���
/	��һ���ַ�����ʾ������ ��һ�����ֱ�ʾ�������
/	������ÿ������ ������ �۸� �ȶ� �� ������������
/	���磺
/
/	34
/	���� 10
/	�ʹ� 60 9.9
/	�찲�� 0 9.8
/	...
/
/	�Ĵ� 10
/	������ 78 9.5
/	����Ž� 0 9.4
/	...
/
/================

Ŀǰ���У�
LoadData ��������
OutputRegion ���������Ϣ
OutputSpecific ���������Ϣ
findRegion ���ҳ���
sortBy Heat/Price,Down/Up ���ݲ�ͬ�ؼ�������������
Add/Delete Region/Scenic ����/ɾ�� ����/����
RandomRecommand ����Ƽ�
TODO�� ģ������(?)
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
	double price;//�۸�
	double heat;//�����ȶ�
	Scenic() {
		cin >> name >> heat >> price;
	}
};

class Position {
public:
	string name;//����
	int len;//�����������
	Scenic *p[100];//����100 ����û��ʹ����������Ϊ ���Ե�����Ҫ 
};

class RegionClass :public Position {
public:
	static int tot_Region;//�ܵ�����
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
OutLoad ���ڲ�����ȡ���ݵĶ���Ч��
�ӳ�һ���Եø�����ʵ
*/
void OutLoad() {
	console.ClearScreen();
	//system("cls");
	console << "Loading data..." << endl;
	Sleep(1000);//�ٴ��
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
	Sleep(1000);//�ٴ��
	console << "Data load finished" << endl;
	Sleep(1000);
	console.ClearScreen();
	freopen("CON","r",stdin);
}

/*

������������е���Ϣ
��ʽ��
 -����1
	- ����1 �ȶȣ��ȶ� �۸񣺼۸�
	- ����2 �ȶȣ��ȶ� �۸񣺼۸�
 - ����2
	- ����3 �ȶȣ��ȶ� �۸񣺼۸�
	- ����4 �ȶȣ��ȶ� �۸񣺼۸�

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
			console << index->p[i]->name << "  �ȶ�:" << index->p[i]->heat << "  �۸�:" << index->p[i]->price << endl;
		}
		index = index->next;
	}

	console << endl;
	return;
}

/*

�������������

*/
void OutputSpecific(RegionClass *index) {
	if (index == nullptr) return;
	else {
		console << index->name << endl;
		for (int i = 1; i <= index->len; i++) {
			console << "|-";
			console << index->p[i]->name << "  �ȶ�:" << index->p[i]->heat << "  �۸�:" << index->p[i]->price << endl;
		}
	}
}

/*

��������ĳ�����Ѱ�Ҷ�Ӧ��Region�����е�λ��

*/
RegionClass* FindRegion(string targetRegion) {
	RegionClass *ret = RegionClass::Region;
	while (ret != nullptr && ret->name != targetRegion) ret = ret->next;
	if (ret == nullptr) console << "Warning : No such region found." << endl;
	return ret;
}
/*

���ݲ�ͬ�Ĺؼ��ֽ�������
ע�����������������ĳ�������µľ����������
ʹ��sort��������

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

�ӿ�����: ĳ�����е�RegionClassָ��
������Region �����е�ĳһ��
�����������ð������
�ֱ��ǣ�

�ȶ� ���� �ȶ� ���� �۸� ���� �۸� ����

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

���һ���������������Ϸ���Data�ļ��Ĺ淶����

*/
void AddRegion() {
	string InputS; cin >> InputS;
	RegionClass *temp = FindRegion(InputS);
	// �������Ѿ����� ���Ӿ���ʱֱ����ӡ� 
	if (temp != nullptr) {
		int lenDelta; cin >> lenDelta;
		for (int i = 1; i <= lenDelta; i++) {
			temp->p[temp->len + i] = new Scenic();
		}
		temp->len += lenDelta;
	}
	else {
	//��ӵ��������� �½�����ڵ��������β 
		for (int i = 1; i <= temp->len; i++)
			temp->p[i] = new Scenic();
		if (RegionClass::Region == nullptr)
			RegionClass::Region = temp;
		else
			RegionClass::RegionTail->next = temp;
		RegionClass::RegionTail = temp;
		temp->tot_Region++;//�ܵĵ�����++ 
	}
}

/*

ɾ��һ��������������ɾ��һ���������е���Ϣ
�������һ��������

*/
void DeleteRegion(string InputS) {
	RegionClass *Index = RegionClass::Region;
	RegionClass *Target = RegionClass::Region->next;

	//���Region ����ͷ����������ɾ���Ľڵ� 
	if (Index->name == InputS) {
		RegionClass::Region = RegionClass::Region->next;
		if (RegionClass::RegionTail->name == InputS)  //������ֻ����һ���ڵ� ��ǡΪ��ɾ���Ľڵ� 
			RegionClass::RegionTail = RegionClass::Region = nullptr;
		free(Index); //Index ��ʱ����һ��ʼ������ͷ 
	}
	else {
		//Ŀ��ڵ㲻���� ���� �ڷ�����ͷ�ڵ�
		while (Target->name != InputS && Target != nullptr) {
			Index = Target;
			Target = Target->next;
		}
		if (Target == nullptr) {
			//Ŀ��ڵ�δ�ҵ�
			console << "Warning : No such region found." << endl;
			return;
		}
		else {
			//Ŀ��ڵ��ҵ�����Target����Target��ǰ����Index
			Index->next = Target->next;
			free(Target);
			Index->tot_Region--;//�ܵĵ��������� 
		}
	}
}

/*

����һ�����㣺�������һ��������

*/
void AddScenic(string InputS) {
	RegionClass *Index = FindRegion(InputS);
	//����ó��в������� �ȼ�������һ�����У��ó��н���һ������ 
	if (Index == nullptr) {
		Index = new RegionClass;
		Index->name = InputS;
		Index->len = 1;
		Index->p[1] = new Scenic();
		//���ϣ�����һ�����У�һ������ 
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

ɾ��һ�����㣺�������һ��������
����û���ṩֱ��ɾ������Ĳ��������뾭������-������о�ȷ��λ
��Ϊɾ�������ǽ�����

*/

void DeleteScenic(string InputS) {
	RegionClass *Index = FindRegion(InputS);
	if (Index == nullptr) return;
	else {
		cin >> InputS;//�����InputS�Ǿ����� ���ǵ�����
		bool isfound = false;//״̬ �Ƿ��ҵ�  
		for (int i = 1; i <= Index->len; i++) {
			if (Index->p[i]->name == InputS)
				isfound = true;
			if (isfound == true)
				if (i < Index->len)// �����һ������
					Index->p[i] = Index->p[i + 1];
			//�����������ڣ���Ŀ�꾰��Ľڵ�֮������нڵ���ǰƽ�� 
		}
		if (isfound == false)//δ�ҵ�����
			console << "Warning : No such scenic found.";
	}
}

/*

����Ƽ�
����Ƽ�ĳһ�����е�ĳһ������
**���ﲻ���ڸ����û���ϲ�ý����Ƽ�

*/
void RandomRecommand() {
	srand(time(0));
	int MagicN = rand() % RegionClass::Region->tot_Region;
	RegionClass *Index = RegionClass::Region;
	while (MagicN--)
		Index = Index->next;
	MagicN = 1 + rand() % Index->len;
	console << "����Ƽ���" << Index->name << " " << Index->p[MagicN]->name << endl;
}

/*

TODO��
ģ������

*/
