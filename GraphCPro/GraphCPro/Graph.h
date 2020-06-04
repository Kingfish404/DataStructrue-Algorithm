#pragma once
#ifndef GRAPH_H
#define GRAPH_H
#define MAX_VERTEX_NUM 256
#define TRUE 1
#define FALSE 0

//定义Vex结构体，存储图的顶点信息。
struct Vex
{
	int num;	      // 景点编号
	char name[20];	// 景点名字
	char desc[1024];	// 景点介绍
};

//定义Edge结构体，存储图的边的信息。
struct Edge
{
	int vex1, vex2;   //边的两个个顶点
	int weight;  	    //权值
};

typedef struct Path
{
	int vexs[MAX_VERTEX_NUM];
	//保存一条路径
	Path* next; //下一条路径
}*PathList;

class Graph {
private:

	int** m_aAdjMatrix; // 邻接矩阵
	Vex* m_aVexs; // 顶点数组
	int m_nVexNum; // 顶点个数
	// 回溯法深度优先搜索算法遍历图
	void DFS(int nVex, bool bVisited[], int& nIndex, PathList pList, int* aPath);
public:

	const static auto Maxsize = MAX_VERTEX_NUM;    // 默认数组最大值参考

	Graph();

	// 初始化图结构。
	void Init(void);

	// 将顶点添加到顶点数组中。
	int InsertVex(Vex sVex);

	//	将边保存到邻接矩阵中。
	int InsertEdge(Edge sEdge);

	// 查询指定顶点信息。
	Vex GetVex(int nVex);

	// 查询与指定顶点相连的边。
	int FindEdge(int nVex, Edge aEdge[]);

	// 查询某个顶点到其他顶点的路径
	void DFSTraverse(int nVex, PathList pList);

	// 获取当前顶点数。
	int GetVexnum(void);

	// 通过Dijkstra算法求得v1到v2的最短路径。
	int FindShortPath(int nVexStart, int nVexEnd, Edge aPath[]);

	// 通过Prim算法构建最小生成树。 
	int FindMinTree(Edge aPath[]);

	~Graph();
};


#endif // !GRAPH_H