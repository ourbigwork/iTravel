
/*

[2019-05-18]
Hotel.h �ù� �Ƶ��� ͷ�ļ�
ʹ�÷�������Hotel.h����������е�ͷ�ļ�����
		��cppԴ�ļ��ϼ��� #include<Hotel.h> ����

*/
#include "pch.h"
#include "CConsole.h"

using namespace std;
#undef Scenic
#undef Position
#undef Region


#undef GuestRoom

class GuestRoom {//�ͷ��� 
public:
	string name;//��������
	int capacity;//�������� ��ס������ 
	int price;//�۸� 
};

class GuestRoomClass : public GuestRoom {// GuestRoomClass�Ǽ̳�GuestRoom ������������Ľڵ��� 
public:
	GuestRoomClass *next;
	GuestRoomClass() {
		cin >> name >> capacity >> price;
		next = nullptr;
	}
};

class Hotel {//�Ƶ����� 
public:
	string name;//�Ƶ��� 
	string contact;//��ϵ��ʽ 
	string address;//��ַ
	GuestRoomClass *RoomList;//��������ͷ 
	GuestRoomClass *RoomListTail;//��������β 
};

class HotelClass :public Hotel {//HotelClass �Ǽ̳�Hotel ������������Ľڵ��� 
public:
	HotelClass *next;

	/*

	���һ������ ,ע�����������ĳһ���Ƶ����
	���ǵ� name ���������� �������ԣ��󴲷� ��׼��֮�ࣩ ����û�в���
	������������ָ��

	*/
	GuestRoomClass* addRoom() {
		GuestRoomClass *tempPoint = new GuestRoomClass();
		if (this->RoomList == nullptr) this->RoomList = tempPoint;
		else RoomListTail->next = tempPoint;
		RoomListTail = tempPoint;
		return tempPoint;
	}

	/*

	ɾ��һ�����䣬ע�����������ĳһ���Ƶ����
	�ӿ���һ��������ָ�� ��������ȷɾ��
	����һ��bool ��ʾ�Ƿ�ɹ�ɾ��

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

class City {//ע�������Scenic.h��Region���ǲ�ͬ�� ��City���� 
public:
	string name;//������
	HotelClass *HotelList;//�Ƶ�����ͷ
	HotelClass *HotelListTail;//�Ƶ�����β 
};

class CityClass :public City {//City Class �Ǽ̳�City ������������Ľڵ���
public:
	CityClass *next;

	/*

	���һ���Ƶ꣬ע�����������ĳ�����ж������
	���Ա�����CityClass���ʵ���ڷ���
	ע�⣬��ʹ��ͬһ������ͬ���Ƶ�Ҳ�����кܶ�
	��������û�в��� ֱ����Ӽ���
	��������Ƶ��ָ��

	*/
	HotelClass* addHotel() {
		HotelClass *tempPoint = new HotelClass();
		if (HotelList == nullptr)  HotelList = tempPoint;
		else HotelListTail->next = tempPoint;
		HotelListTail = tempPoint;
		return HotelListTail;
	}

	/*

	ɾ��һ���Ƶ꣬ע�����������ĳ�����ж���ɾ��
	���Ա�����Cityclass���ʵ���ڷ���
	������Ľӿڱ�����һ��HotelClass��ָ���Ծ�ȷɾ��
	����һ��bool�� ��ʾ�Ƿ�ɹ�ɾ��

	*/
	bool deleteHotel(HotelClass *Input) {
		HotelClass *Index = HotelList, *INext = HotelList->next;
		if (Index == Input) {
			//����ͷɾ��
			HotelList = HotelList->next;
			if (HotelListTail == Input) HotelListTail = nullptr;
			free(Index); return true;
		}
		while (Index != nullptr) {
			if (INext == Input) {
				Index->next = INext->next;
				if (INext == HotelListTail) HotelListTail = Index;//����βɾ�� 
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
CityClass* CityList = nullptr;//�ص�����ͷ
CityClass* CityListTail = nullptr;//�ص�����β

/*

����һ�����У��������Ӧ������ڵ�(CityList)ָ��
��������� ����nullptr
�ӿڣ�������string

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

����һ���Ƶ�
ע�� ���ؿ�����ͬ���ľƵ꣬����Ҫ��ͬ����ȫ���
�ӿڣ��Ƶ���string
�����һ��resultHotel������ɵ�����������ÿһ���ڵ㶼����һ��Hotel
��������Ϊ findHotelList ,Ҳ��ͷ�ڵ�ָ��

*/
struct resultHotel {
	HotelClass *HotelPointer;
	resultHotel *next;
	CityClass *Super;//����һ���������ʸ��׽ڵ��ָ��
}*findHotelList, *findHotelTail;

/*

��findHotelList������������һ��InsertPoint��ָ��Ľڵ�

*/
void resHotelInsert(HotelClass *InsertPoint, CityClass *Father) {//��resultHotel����ڵ� 
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
		HotelClass *HIndex = Index->HotelList;// HIndex ö������һ���Ƶ�
		while (HIndex != nullptr) {
			if (HIndex->name == targetS)
				resHotelInsert(HIndex, Index);
			HIndex = HIndex->next;
		}
	}
}

/*

���findHotelList�е���Ϣ

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

���һ�����У��ӿڣ�������
������в���������ӳ���
���ص���������е�ָ��

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

ɾ��һ�����У��ӿڣ�������
����һ��bool�ͱ�ʾ�Ƿ�ɹ�ɾ��

*/
bool deleteCity(string InputS) {
	return false;
}


/*

��ȡ����
�����ļ�Ҫ��
��һ�б�ʾ������ ����������һ��������Ϣ

	����ÿ������ ��һ�г����� ������ֱ�ʾ�Ƶ����
	�����������Ƶ���Ϣ

		����ÿ���Ƶ� ��һ������������Ϣ ������ֱ�ʾ������
		����������������Ϣ

			����ÿ������ ��һ����������Ļ�����Ϣ

*/
void HotelLoadData() {
	//openFile
	string InputS;
	int totCity = 0; cin >> totCity;//������ 
	while (totCity--) {
		cin >> InputS;
		CityClass *Index = addCity(InputS);
		int totHotel = 0; cin >> totHotel;//�Ƶ���
		while (totHotel--) {
			HotelClass *HIndex = Index->addHotel();
			int totRoom = 0; cin >> totRoom;//������
			while (totRoom--)
				HIndex->addRoom();
		}
	}
}

/*

�����û�����ɸѡ���ʵı���
�ӿڣ�������string ����int ����int
���һ�� optionHotel�� ���飬�����пɹ�ѡ��ľƵ��Լ�����۸�
����û��ѡ����������Ϊ���򲻷��㣬���Ҳ�������������
�ǿռ临�Ӷ� ��ȡʱ�临�ӶȺͱ�̸��Ӷȵ�����

����ǰ�����޺��ʵľƵ꣨�޾Ƶ� �� �����������ľƵ꣩ �����Ӧ��ʾ
�����ں��ʵľƵ꣬��ĳ��˳������ʺϵľƵ��Լ�����Ҫ�ļ�Ǯ
��ͬһ�Ƶ���ڲ�ͬ�Ľ������ʱ�����ȿ��Ǽ�Ǯ��͵�

������ĳ��˳��ָ���ǣ���Ĭ�ϣ����� ������Ĭ�ϣ��۸�������
����ָ���Ǽ۸�˳�����к���������м��λ�ȽϺ���
Ȼ��һǰһ�����������ľƵ�����

*/

struct optionHotel {
	HotelClass *HotelPointer;//ָ��Ƶ�
	int price;//��Ǯ (��������) 
}HotelOptions[30];

int totOption = 0;//���пɹ�ѡ��ľƵ��� 

/*

calcMinPrice ������ڸ����Ƶ��ڿͻ�ָ�������������ٴ��ۻ���
int �ͷ��أ��������ٴ��ۻ��ѣ�Ĭ�ϴ���0.�������ֵΪ-1
��˵���˾Ƶ�û�к��ʵĿͷ�����ס �ϲ�˵�������Ϊ���ݽ�����һ������

��̬�滮˼�룬��f(n)��ʾn������ס��Ҫ����С����
ö�ٷ��䣬�跿��i��סCi�ˣ��۸�Pi ��
for_all i:1->inf, f(n)=min { f(n-Ci) + Pi }
��˵��������ѭ�� һ��Ϊ����ѭ�� for( peopleNum: 1->n)
����Ϊ����ö��ѭ�� ���������� û���±� ��ԭ������ͬ��
��ʼ��: for_all i:1->inf, f(i)=inf , f(0) = 0
��� ans=mfor_all i:n->inf ,min{f(i)}

*/
int calcMinPrice(HotelClass *Index, int peopleNum, int dayNum) {
	int f[15], ret = 2147483647;
	//���ʮ����ͬʱ��ס������Я�̹�����
	//���ܴ���һ�ֹ�ס���������һ�Ǯ���ٵķ��� ���Ҫ��Ӽ�λ 
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
		while (HIndex != nullptr) {//�����Ƶ��б� 
			//��ʱHIndex ָ�����һ���Ƶ�
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

��struct optionHotel��HotelOptions��������
�ؼ��ֱַ�Ϊ �۸�ӵ͵��ߣ� �۸�Ӹߵ��� ����������
��ν�����Ѿ��������и������壬 ����ʹ��algorithm ��� qsort������������
��Ҫ���cmp�����������Ƚϣ���Ϊ�Ƿ񽻻�������

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
	//����������
	vector<optionHotel> tempArray;
	int i = totOption / 2, j = 1 + totOption / 2;
	//���м���������չ 
	while (i >= 1 || j <= totOption) {
		if (i >= 1) tempArray.push_back(HotelOptions[i--]);
		if (j <= totOption)tempArray.push_back(HotelOptions[j++]);
	}
	for (i = 1; i <= totOption; i++)
		HotelOptions[i] = tempArray[i - 1];
}


