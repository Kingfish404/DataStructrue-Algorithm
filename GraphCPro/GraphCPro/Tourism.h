#pragma once
#ifndef TOURISM_H
#define TOURISM_H
#include "Graph.h"



class Tourism {
private:
	Graph graph;
	// 列出当前景点列表
	int tryTimes;
	void showEdge();
public:
	Tourism();
	// 读取文件，创建景区景点图。
	void CreateGraph();

	// 查询指定景点信息，显示到相邻景点的距离。
	void GetSpotInfo();

	// 实现旅游景点导航功能,将查询到的景点导航路线显示在界面上
	void TravelPath();

	// 搜索两个景点之间的所有路径，找到其中距离最短的路径。
	void FindShortPath();

	// 根据景区景点图，构造一棵最小生成树，设计出一套铺设线路最短，但能满足每个景点都能通电的方案。
	void DesignPath();
};


#endif // !TOURISM_H