
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

// 以下为Main类的具体实现

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
			cout << "退出系统成功" << endl;
			break;
		default:
			cout << "请输入正确的值" << endl;
			break;
		}
	}
}

void Main::menu() 
{
	cout << "======== 景区信息管理系统 ========" << endl;
	cout << " 1.创建景区景点图" << endl;
	cout << " 2.查询景点信息" << endl;
	cout << " 3.旅游景点导航" << endl;
	cout << " 4.搜索最短路径" << endl;
	cout << " 5.铺设电路规划" << endl;
	cout << " 0.退出" << endl;
	cout << "请输操作编号<0~5>:";
}

Main::~Main() 
{
	if (cRuning) {
		delete[] cRuning;
	}
}