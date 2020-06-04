
#include<iostream>
#include"Tourism.h"

using namespace std;

class Main {
private:
	int bRuning;
	char* cRuning;
	Tourism tourism;
	const static int MAX = 256;
public:
	Main();
	void run();
	void menu();
	~Main();
};

int main()
{
	Main main;
	main.run();
	return 0;
}

// ����ΪMain��ľ���ʵ��

Main::Main() {
	bRuning = 1;
	cRuning = new char[MAX];
}


void Main::run() 
{

	int bRuning = 1;
	char cRuning[MAX];
	Tourism tourism;
	while (bRuning)
	{
		menu();
		cin >> cRuning;
		bRuning = cRuning[0] - '0';
		switch (bRuning)
		{
		case 1:
			tourism.CreateGraph();
			break;
		case 2:
			tourism.GetSpotInfo();
			break;
		case 3:
			tourism.TravelPath();
			break;
		case 4:
			tourism.FindShortPath();
			break;
		case 5:
			tourism.DesignPath();
			break;
		case 0:
			cout << "�˳�ϵͳ�ɹ�" << endl;
			break;
		default:
			cout << "��������ȷ��ֵ" << endl;
			break;
		}
	}
}

void Main::menu() 
{
	cout << "======== ������Ϣ����ϵͳ ========" << endl;
	cout << " 1.������������ͼ" << endl;
	cout << " 2.��ѯ������Ϣ" << endl;
	cout << " 3.���ξ��㵼��" << endl;
	cout << " 4.�������·��" << endl;
	cout << " 5.�����·�滮" << endl;
	cout << " 0.�˳�" << endl;
	cout << "����������<0~5>:";
}

Main::~Main() 
{
	if (cRuning) {
		delete[] cRuning;
	}
}