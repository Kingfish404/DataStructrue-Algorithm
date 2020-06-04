#include<iostream>
#include<fstream>
#include"Tourism.h"
#include"Graph.h"

using namespace std;

Tourism::Tourism() 
{
	tryTimes = 1;
}

void Tourism::showEdge() 
{
	int v = graph.GetVexnum();
	Edge* aEdge = new Edge[graph.Maxsize];
	Vex vex;
	for (int i = 0; i < v; i++)
	{
		vex = graph.GetVex(i);
		cout << vex.num << "-" << vex.name << endl;
	}
	delete[] aEdge;
}

//读取文件，创建景区景点图。
void Tourism::CreateGraph()
{
	Vex vex;
	Edge edge;
	ifstream in;
	int num;
	in.open("Vex.txt");
	if (!in.is_open()) {
		cout << "点信息文件打开出错" << endl;
		return;
	}
	// 1 初始化图
	graph.Init();

	cout << "==== 创建景区景点图 ====" << endl;

	//2 设置图的顶点
	in >> num;
	cout << "Vex num: " << num << endl;
	for (int i = 0; i < num; i++)
	{
		in >> vex.num;
		in >> vex.name;
		in >> vex.desc;
		graph.InsertVex(vex);
	}
	in.close();

	cout << "---- Vex ---- " << endl;
	showEdge();

	//3 设置图的边
	in.open("Edge.txt");
	if (!in.is_open()) {
		cout << "边信息文件打开出错" << endl;
		return;
	}
	cout << "---- Edge ---- " << endl;
	while (!in.eof()) {
		in >> edge.vex1;
		in >> edge.vex2;
		in >> edge.weight;
		cout << "<v" << edge.vex1 << ",v" << edge.vex2 << ">" << " " << edge.weight << endl;
		graph.InsertEdge(edge);
	}
	in.close();
}

//查询指定景点信息，显示到相邻景点的距离。
void  Tourism::GetSpotInfo()
{
	int v = graph.GetVexnum(), n;
	Vex vex, vexNaibor;
	Edge* aEdge = new Edge[graph.Maxsize];
	cout << "==== 创建景区景点图 ====" << endl;
	showEdge();
	int count = 0;
	do
	{
		cout << "请输入想要查询的景点编号:";
		cin >> n;
		if (n >= v || n < 0) {
			cout << "编号输入错误,无此景点" << endl;
			if (count >= tryTimes) {
				return;
			}
		}
		count++;
	} while (n >= v || n < 0);

	//取得指定顶点信息
	vex = graph.GetVex(n);
	cout << vex.name << endl;
	cout << vex.desc << endl;

	//查询所有与指定顶点相连的边的信息
	cout << "---- 周边景区 ---- " << endl;
	n = graph.FindEdge(n, aEdge);
	for (int i = 0; i < n; i++)
	{
		vex = graph.GetVex(aEdge[i].vex1);
		vexNaibor = graph.GetVex(aEdge[i].vex2);
		cout << vex.name << "->" << vexNaibor.name << " "
			<< aEdge[i].weight << "m" << endl;
	}
	delete[] aEdge;
}

void Tourism::TravelPath() 
{
	int v = graph.GetVexnum(), n;
	Vex vex;
	PathList pathList = new Path;
	pathList->next = NULL;
	cout << "==== 旅游景点导航 ====" << endl;
	showEdge();

	//输入景点编号
	int count = 0;
	do
	{
		cout << "请输入起始点编号:";
		cin >> n;
		if (n >= v || n < 0) {
			cout << "编号输入错误,无此景点" << endl;
			if (count >= tryTimes) {
				return;
			}
		}
		count++;
	} while (n >= v || n < 0);

	//遍历景区景点图
	graph.DFSTraverse(n, pathList);

	//输出遍历结果
	PathList q = pathList;
	int num = 0;
	while (q->next != NULL)
	{
		cout << "路线" << ++num << ": ";
		for (int i = 0; i < v; i++)
		{
			vex = graph.GetVex(q->vexs[i]);
			cout << vex.name << " ";
			if (i != v - 1) {
				cout << "-> ";
			}
		}
		cout << endl;
		q = q->next;
	}

	PathList p = pathList;
	while (p != NULL) {
		pathList = p->next;
		delete p;
		p = pathList;
	}
}

void Tourism::FindShortPath() 
{
	int v = graph.GetVexnum(), start, end, cost = 0,n;
	Vex vex;
	Edge aPath[MAX_VERTEX_NUM];
	cout << "==== 搜索最短路径 ====" << endl;

	showEdge();

	//输入景点编号
	int count = 0;
	do
	{
		cout << "请输入起始点编号:";
		cin >> start;
		if (start >= v || start < 0) {
			cout << "编号输入错误,无此景点" << endl;
			if (count >= tryTimes) {
				return;
			}
		}
		count++;
	} while (start >= v || start < 0);

	//输入景点编号
	count = 0;
	do
	{
		cout << "请输入终点编号:";
		cin >> end;
		if (end >= v || end < 0) {
			cout << "编号输入错误,无此景点" << endl;
			if (count >= tryTimes) {
				return;
			}
		}
		count++;
	} while (end >= v || end < 0);

	if (start == end) {
		cout << "起点终点相同，无需规划路线" << endl;
		return;
	}

	// aPath为从终点到起点的路径
	n = graph.FindShortPath(start, end, aPath);

	cout << "最短路线为：";
	for (int i = n-1; i >=0 ; i--)
	{
		vex = graph.GetVex(aPath[i].vex2);
		cout << vex.name << " ";
		cout << "-> ";
		cost += aPath[i].weight;
	}
	vex = graph.GetVex(aPath[0].vex1);
	cout << vex.name <<endl;

	cout << "最短距离为：" << cost << endl;
}


void Tourism::DesignPath()
{
	int v = graph.GetVexnum(), cost = 0, n;
	Vex vex;
	Edge aPath[MAX_VERTEX_NUM];
	cout << "==== 铺设电路规划 ====" << endl;

	n = graph.FindMinTree(aPath);

	cout << "在以下两个景点之间铺设电路:" << endl;

	for (int i = 0; i < n; i++)
	{
		vex = graph.GetVex(aPath[i].vex1);
		cout << vex.name << " - ";
		vex = graph.GetVex(aPath[i].vex2);
		cout << vex.name << "  " << aPath[i].weight <<"m"<< endl;
		cost += aPath[i].weight;
	}
	cout << "铺设电路的总长度为: " << cost << endl;
}
