#include"Graph.h"
#include<fstream>

Graph::Graph() 
{
	m_aAdjMatrix = new int* [Maxsize];
	for (int i = 0; i < Maxsize; i++)
	{
		m_aAdjMatrix[i] = new int[Maxsize];
	}
	m_aVexs = new Vex[Maxsize];
	m_nVexNum = 0;
}

void Graph::Init(void)//初始化图结构。
{
	m_nVexNum = 0;
	for (int i = 0; i < Maxsize; i++)
	{
		for (int j = 0; j < Maxsize; j++)
		{
			m_aAdjMatrix[i][j] = 0;
		}
	}
}

int Graph::InsertVex(Vex sVex)//将顶点添加到顶点数组中。
{
	m_aVexs[m_nVexNum] = sVex;
	m_nVexNum++;
	return TRUE;
}

int Graph::InsertEdge(Edge sEdge)//将边保存到邻接矩阵中。
{

	m_aAdjMatrix[sEdge.vex1][sEdge.vex2] = sEdge.weight;
	m_aAdjMatrix[sEdge.vex2][sEdge.vex1] = sEdge.weight;
	return TRUE;
}

Vex Graph::GetVex(int nVex)//查询指定顶点信息。
{
	return m_aVexs[nVex];
}

int Graph::FindEdge(int nVex, Edge aEdge[])//查询与指定顶点相连的边。
{
	int num = 0;
	for (int i = 0; i < m_nVexNum; i++)
	{
		if (m_aAdjMatrix[nVex][i]) {
			aEdge[num].vex1 = nVex;
			aEdge[num].vex2 = i;
			aEdge[num].weight = m_aAdjMatrix[nVex][i];
			num++;
		}
	}
	return num;
}

void Graph::DFSTraverse(int nVex, PathList pList)
{
	int nIndex = 0;
	bool aVisited[MAX_VERTEX_NUM] = { false };
	int aPath[MAX_VERTEX_NUM];
	DFS(nVex, aVisited, nIndex, pList, aPath);
}

void Graph::DFS(int nVex, bool bVisited[], int& nIndex, PathList pList, int* aPath)
{
	bVisited[nVex] = true; ;		// 改为已访问
	aPath[(nIndex)++] = nVex; ;		// 记录访问顶点
	if (nIndex >= GetVexnum()) {
		PathList p = pList;
		while (p->next != NULL) {
			p = p->next;
		}
		for (int i = 0; i < GetVexnum(); i++)
		{
			p->vexs[i] = aPath[i];
		}
		p->next = new Path;
		p->next->next = NULL;
	}
	else
	{
		for (int i = 0; i < GetVexnum(); i++)	// 搜素所有邻接点
		{
			if (m_aAdjMatrix[nVex][i] != 0 && !bVisited[i])
			{
				DFS(i, bVisited, nIndex, pList, aPath);	// 递归调用DFS
				bVisited[i] = false;	// 回溯，恢复状态
				(nIndex)--;				// 回溯
			}
		}
	}
}

int Graph::FindShortPath(int nVexStart, int nVexEnd, Edge aPath[])
{
	int n = 0;
	int mark[MAX_VERTEX_NUM] = { 0 };
	int dist[MAX_VERTEX_NUM];
	int path[MAX_VERTEX_NUM] = { 0 };

	mark[nVexStart] = 1;
	for (int i = 0; i < m_nVexNum; i++)
	{
		dist[i] = m_aAdjMatrix[nVexStart][i];
	}
	for (int i = 0; i < m_nVexNum; i++)
	{
		path[i] = nVexStart;
	}
	int here;

	// Dijkstra算法求最短路径
	while (!mark[nVexEnd])
	{
		int min = 0xFFFFFFF;
		for (int i = 0; i < m_nVexNum; i++)
		{
			if (mark[i] == 0 && dist[i] != 0) {
				if (dist[i] < min) {
					here = i;
					min = dist[i];
				}
			}
		}
		mark[here] = 1;
		for (int i = 0; i < m_nVexNum; i++)
		{
			if (mark[i] == 0 && m_aAdjMatrix[here][i] != 0) {
				if ((dist[i] > dist[here] + m_aAdjMatrix[here][i]) || (dist[i] == 0 && dist[here] != 0))
				{
					path[i] = here;
					dist[i] = dist[here] + m_aAdjMatrix[here][i];
				}
			}
		}
	}
	here = nVexEnd;

	while (here != nVexStart)
	{
		aPath[n].vex1 = here;
		aPath[n].vex2 = path[here];
		aPath[n].weight = m_aAdjMatrix[aPath[n].vex1][aPath[n].vex2];
		here = path[here];
		n++;
	}
	return n;
}

int Graph::FindMinTree(Edge aPath[])
{
	int n = 0;
	int mark[MAX_VERTEX_NUM] = { 0 };
	int from = 0, to = 0;
	mark[from] = 1;

	// Prim算法求最短生成树
	while (n < m_nVexNum-1)
	{
		int min = 0xFFFFFFF;
		for (int i = 0; i < m_nVexNum; i++)
		{
			// 遍历已经连接的点
			if (mark[i])
			{
				for (int j = 0; j < m_nVexNum; j++)
				{
					// 遍历未连接的点，从已连接的点到未连接的点中找一条最短的边
					if (!mark[j] && m_aAdjMatrix[i][j] != 0 && m_aAdjMatrix[i][j] < min) {
						min = m_aAdjMatrix[i][j];
						from = i;
						to = j;
					}
				}
			}
		}
		// 将新的点标记为已经找到
		mark[to] = 1;
		aPath[n].vex1 = from;
		aPath[n].vex2 = to;
		aPath[n].weight = m_aAdjMatrix[aPath[n].vex1][aPath[n].vex2];
		n++;
	}

	return n;
}



int Graph::GetVexnum(void)//获取当前顶点数。
{
	return m_nVexNum;
}


Graph::~Graph() {
	if (m_aVexs) {
		delete[] m_aVexs;
	}
	for (int i = 0; i < Maxsize; i++)
	{
		delete[] m_aAdjMatrix[i];
	}
	if (m_aAdjMatrix) {
		delete[] m_aAdjMatrix;
	}
}
