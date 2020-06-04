#pragma once
#ifndef TOURISM_H
#define TOURISM_H
#include "Graph.h"



class Tourism {
private:
	Graph graph;
	// �г���ǰ�����б�
	int tryTimes;
	void showEdge();
public:
	Tourism();
	// ��ȡ�ļ���������������ͼ��
	void CreateGraph();

	// ��ѯָ��������Ϣ����ʾ�����ھ���ľ��롣
	void GetSpotInfo();

	// ʵ�����ξ��㵼������,����ѯ���ľ��㵼��·����ʾ�ڽ�����
	void TravelPath();

	// ������������֮�������·�����ҵ����о�����̵�·����
	void FindShortPath();

	// ���ݾ�������ͼ������һ����С����������Ƴ�һ��������·��̣���������ÿ�����㶼��ͨ��ķ�����
	void DesignPath();
};


#endif // !TOURISM_H