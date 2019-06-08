/*

[2019-05-25]
Train.h ���� ͷ�ļ�
ʹ�÷�������Train.h����������е�ͷ�ļ�����
		��cppԴ�ļ��ϼ��� #include<Train.h> ����

ע�����µĹ��ܶ��Ǿ����ܵ�ģ��12306�ƶ��˵Ĺ���

˼·��TrainList ��������г���������Ϣ����һ����Train�๹�ɵ�vector
������һ��Station �࣬�������棺����ĳһվ�������г���Ϣ�����ں�������
12306�����Ĳ����У���ѯĳ������Ϣ����ѯĳ��վ��ĳ�أ���Ϣ
���ݿͻ�Ҫ�󣨴��ĵ��ģ������ɹ�ѡ����г���Ϣ�������Ը����û�����������ȼ�����

��12306�У���2�����ȼ�˳�򣺷�ʱ���磬��ʱ���١��������  "��ʱ����"  �ǲ�ͬ��
12306�ڸ����ɹ�ѡ��ķ���ʱ���û���ѡ�񻻳ˣ���һ�Σ��򲻻������ַ�ʽ��
������ǲ��޻��˴����µ�  "��ʱ����"������ǳ��鷳��ԭ����ࡣ
һ��Ŀǰ�����ϲ�ѯ������ ����ǵ������߹�������ѻ��ˣ����߾�������վ�������㷨���������Ҫ�򵥵����·�㷨��⼴��
Ȼ���𳵲�ͬ���𳵵ĵ�վʱ���������Ƶġ��ܿ���һ�����������㷨�Ļ��˷���ʵ�����ǲ����еģ�����ֻ�ܻ��˵�ǰʱ��֮�󵽴�ĳ��Σ�
��ʵ������Ƕ�����˵�����˴���Խ�࣬Խ�����ܴﵽ��ν�ĵ�ʱ���磬�����㷨�����۽Ƕ�������������˵�ǲ��Ե�
���ԣ�һ���ȽϺõķ����������������ǵ�������г����ν��ߣ���վΪ�㽨ͼ������ʵ����Ƕ�����������ؽ���һ������ͼ
�����������������㷨Ч�ʼ�������˵�ǲ����ܵõ����ŵĽ����ֻ�ܵõ�һ���ȽϽӽ���ֵ����ͺ����ǵĳ���Υ��
��ˣ�����������֮�£���û��д�����ʱ������㷨�����������ĸ���12306����໻��һ�εĿ��з��������㷨

��һ��Ҫ���ǣ�12306��û���ṩ��ν�Ļ�Ǯ���ٲ��ң���Ϊ��12306�ƶ������ǿ��Կ�����ѡ����λ�ȼ���ȷ��ѡ����ĳһ�˳���
���ύ����ʱ�ſ��Եģ����ҽ��ṩ�˼򵥵��ܼۼ��㹦�ܣ���Hotel�����ٻ�Ǯ�������кܴ�������˰��²���


�����ܣ�
struct viaStation,��������Train��
Train�� �����г��Ļ�����Ϣ �Լ������ʽ
Station�� ������վ���Լ�һ��timetable���������о����ó�վ���г�

*/
#include "pch.h"
#include "CConsole.h"

using namespace std;
#undef Train


/*

��һ�ο����Լ���дTime�� �������뻹�ǲ�̫��Ҫ
���ʱ���Ļ���д

class MyTime{
	public:
		static int ThisYear,ThisMonth;//��������ĳ�����ڵĳ�Ʊ��Ϣ
		int day,hour,minute;//ʱ��
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
		bool operator+(int inMinute){//������ (���ڻ����)
			minute+=inMinute;
			hour+=(minute/60);minute%=60;
			if(hour==24) hour=0,day++;//�������������������
		}
};
int MyTime::ThisYear = 2019;
int MyTime::ThisMonth = 6;

*/

struct viaStation {
	int hour, minute;//ʱ�� 
	string stationName;//��վ�� 
	void outStationInfo() {
		console << stationName << " ("; if (hour < 10) console << 0;
		console << hour << ":"; if (minute < 10) console << 0;
		console << minute << ")";
	}
};

//ʱ��Ƚ� ���� L<R �� bool ֵ 
bool cmpTime(viaStation &L, viaStation &R) {
	if (L.hour != R.hour) return L.hour < R.hour;
	else return L.minute < R.minute;
}

//���ƱȽ� ����L<R �� bool ֵ 
bool cmpName(viaStation &L, viaStation &R) {
	return L.stationName < R.stationName;
}

class Train {
public:
	int seat[3][2];//seat[i][0] ��ʾi+1����λ ��ʣ����Ʊ seat[i][1] ��ʾi+1����λ Ҫ����Ǯ 
	string TrainName;//����
	vector<viaStation> route;//;���� 

	//������Ϣ 
	void changeInfo() {
		cin >> TrainName;
		TrainName = console.UTF82ANSI(TrainName);
		//console<<TrainName<<endl; 
		int len; cin >> len;//;���ظ�����0,len-1 �ֱ��ʾ�׷�վ���յ�վ
		while (len--) {
			viaStation temp;
			cin >> temp.stationName >> temp.hour >> temp.minute;
			temp.stationName = console.UTF82ANSI(temp.stationName);
			//console << temp.stationName << endl;
			route.push_back(temp);
		}
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 2; j++)
				cin >> seat[i][j];//���복Ʊ��Ϣ  
	}

	//���������Ϣ 
	void outputBasicInfo() {
		console << this->TrainName << " : ";
		route[0].outStationInfo();
		console << " => ";
		route[route.size() - 1].outStationInfo();
		console << endl;
	}
	void outputSeat() {
		console << TrainName << "��Ʊ��Ϣ:" << endl;
		console << " һ��(" << seat[0][1] << "��)" << seat[0][0] << "�� ";
		console << " ����(" << seat[1][1] << "��)" << seat[1][0] << "�� ";
		console << " ����(" << seat[2][1] << "��)" << seat[2][0] << "�� " << endl;
	}
	void outputRoute() {
		for (size_t i = 0; i < route.size(); i++) {
			console << i + 1 << "   "; route[i].outStationInfo();
			console << endl;
		}
	}

	//��ѯ�Ƿ񾭹�ĳһվ �����±� 
	int findRoute(string InputS) {
		int i = route.size() - 1;
		while (i >= 0 && route[i].stationName != InputS) i--;
		return i;
	}
};
class Station {//��վ 
public:
	string name;//��վ�� 
	vector<Train*> timetable;// ʱ�̱�
	void outputInfo() {
		/*
		������о�����վ�ĳ���
		��һ��ֵ��ע�⣬����������12306��û�С�
		12306�����ṩ���־���ĳһվ�����г��ε������ʾ��
		�����ṩ׼ȷ�ĳ��κ����ڲſ���
		����û������
		*/
		size_t i = 0;
		while (i < timetable.size()) {
			console << i + 1 << ":";
			//���ʱ��������׷����յ�վ��������������������м��������վ��ʱ��
			if (timetable[i]->route[0].stationName == name //�׷�վ 
				|| timetable[i]->route[timetable[i]->route.size() - 1].stationName == name)//�յ�վ 
				timetable[i]->outputBasicInfo();
			else {//���׷� �� �յ�վ 
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

vector<Station*> StationList;//��վ�ܱ� 

/*

���ҳ�վ������InputName��վ���ڳ�վ�ܱ���±�(int)
����Ҳ�������-1
*/

int findStation(string InputName) {
	int i = StationList.size() - 1;
	while (i >= 0 && StationList[i]->name != InputName) i--;
	return i;
}

/*

���򣺶Ը�����Train* ��vector��������
�ؼ��� �׷�վʱ������(���ڳ�վ��timetable����

*/
void sortByTime(vector<Train*> &Array) {
	int len = Array.size();
	for (int i = 0; i < len; i++)
		for (int j = 1; j < len; j++)
			if (!cmpTime(Array[j]->route[0], Array[j - 1]->route[0]))
				swap(Array[j], Array[j - 1]);
}

/*

���һ���г�
ע�⣬���ǽ��г�������վ̨���и��£�Ҳ����˵�����ǲ��ṩaddStation���ֲ���
���ԣ�addTrain ���¼����г��ܱ���г����������ĳ�վ��Ϣ���и���
���û��д�����ڣ�����д������


addTrain ��ʽ(Example)

T151  ����
3  ����վ��
���� 0 0  վ�� ���㼸�ֵ�
�Ϻ� 1 1
���� 2 2
1 2 2 3 3 4 һ������Ʊ�����۸񣬶�������Ʊ�����۸�������Ʊ���۸�

T332
3
���� 2 2
�Ϻ� 3 3
��� 4 4
2 3 4 5 6 7

G312
3
���� 1 1
���� 3 3
��� 6 6
4 3 2 1 3 4

*/

vector<Train*> TrainList;//�г��ܱ�

void addTrain() {
	Train *temp = new Train;
	temp->changeInfo();//���복����Ϣ
	TrainList.push_back(temp);
	for (size_t i = 0; i < temp->route.size(); i++) {
		//ö�پ����ĳ�վ
		int index = findStation(temp->route[i].stationName);//��ѯ��վ�����±�
		if (index == -1) {
			//δ�ҵ���վ���½��˳�վ
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

//���ҳ��� �����±� 
int findTrain(string InputS) {
	int i = TrainList.size() - 1;
	while (i >= 0 && TrainList[i]->TrainName != InputS) i--;
	return i;
}

//�����ṹ 
struct way {
	Train* first;
	Train* second;//������軻�ˣ������ΪNULL
	int begTime, endTime;//��ʱ������ʱ 
};
vector<way> Result;

void findResult(const string & s, const string & e) {
	while (!Result.empty()) Result.pop_back();//��Ϊ��
	string Start, End;//����յ�
	Start = s, End = e;
	int StartIndex, EndIndex;
	//cin >> Start >> End;
	//Start = console.UTF82ANSI(Start);
	//End = console.UTF82ANSI(End);
	//�����ǻ���
	for (size_t i = 0; i < TrainList.size(); i++) {
		StartIndex = TrainList[i]->findRoute(Start);
		EndIndex = TrainList[i]->findRoute(End);
		if (StartIndex == -1 || EndIndex == -1) continue; //�˳������������յ�
		if (EndIndex <= StartIndex)  continue; //���Ƿ����
	//	console<<"Here"<<endl;
		way temp;
		temp.begTime = TrainList[i]->route[StartIndex].hour * 60 + TrainList[i]->route[StartIndex].minute;
		temp.endTime = TrainList[i]->route[EndIndex].hour * 60 + TrainList[i]->route[EndIndex].minute;
		temp.first = TrainList[i];
		temp.second = NULL;
		Result.push_back(temp);
	}
	//���ǻ���
	StartIndex = findStation(Start);
	EndIndex = findStation(End);
	for (size_t i = 0; i < StationList[StartIndex]->timetable.size(); i++) {
		//����ö�ٵ��Ǿ����������г�
		Train *Index = StationList[StartIndex]->timetable[i];
		int q = Index->findRoute(End);
		if (q == -1) {//����ֱ��ſ��ǻ���
			for (size_t j = 0; j < StationList[EndIndex]->timetable.size(); j++) {
				//ö�ٻ��˵ĳ���
				Train *NIndex = StationList[EndIndex]->timetable[j];
			//	console<<"Attempting:"<<Index->TrainName<<"->"<<NIndex->TrainName<<endl;
				int p = NIndex->findRoute(Start);
				if (p == -1)//����ֱ��
					for (size_t k = 1; k < Index->route.size(); k++) {
					//	console<<"Here"<<endl;
						//����ö������һվ����
						int r = NIndex->findRoute(Index->route[k].stationName);
						if (r != -1 && cmpTime(Index->route[k], NIndex->route[r])) { //�ɻ���
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

//����ʱ�������� 
void sortResultEarly() {
	for (size_t i = 0; i < Result.size(); i++)
		for (size_t j = 1; j < Result.size(); j++)
			if (Result[j].begTime < Result[j - 1].begTime) swap(Result[j], Result[j - 1]);
}

//����ʱ�������� 
void sortResultFast() {
	for (size_t i = 0; i < Result.size(); i++)
		for (size_t j = 1; j < Result.size(); j++)
			if (Result[j].endTime - Result[j].begTime < Result[j - 1].endTime - Result[j - 1].begTime) swap(Result[j], Result[j - 1]);
}

//������
void outputResult() {
	console << endl << "��Ϊ���鵽" << Result.size() << "����Ϣ" << endl;
	for (size_t i = 0; i < Result.size(); i++) {
		if (Result[i].second == NULL) {
			console << Result[i].first->TrainName << "(ֱ��)" << endl;
			Result[i].first->outputSeat();
			console << endl;
		}
		else {
			//����
			console << Result[i].first->TrainName << "(����) => " << Result[i].second->TrainName << endl;
			Result[i].first->outputSeat();
			Result[i].second->outputSeat();
			console << endl;
		}
	}
}

//��ȡ����
void TrainDataLoad() {
	int n;//���г���
	//openfile
	freopen(".\\TrainData.txt", "r", stdin);
	cin >> n;
	while (n--)
		addTrain();
	cin.clear();
}
