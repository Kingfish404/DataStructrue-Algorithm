#ifndef CGRAPH_H
#define CGRAPH_H
#include <Qt>
#include "global.h"

class CGraph
{
protected:
    // 顶点的数据类型
    typedef qint16 Vertices[MAX_VERTEX_NUM];

    // 边的数据类型
    typedef bool AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

    Vertices m_Vertices;    // 顶点数组
    AdjMatrix m_AdjMatrix;  // 关系矩阵

    qint16 m_nVexnum;  // 顶点数量
    qint16 m_nArcnum;  // 边的数量
    qint16 m_mapLen;   // 地图宽度

public:
    CGraph();

    ~CGraph();

    // 初始化图的顶点和关系
    void InitGraph(void);

    // 获取地图宽度
    qint16 getMapLen();

    // 设置地图宽度
    void setMapLen(qint16 len);

    // 将顶点info添加到数组中
    qint16 AddVertex(qint16 info);

    // 将图数组中索引号为nIndex的顶点更新为info
    void UpdateVertex(qint16 nIndex,qint16 info);

    // 获取顶点数组中索引为nIndex的顶点
    qint16 GetVertex(qint16 nIndex);

    // 获取两个点是否相邻
    bool GetArc(qint16 nV1Index,qint16 nV2Index);

    // 添加关系矩阵中,nV1Index与nV2Index的关系
    void AddArc(qint16 nV1Index,qint16 nV2Index);

    // 交换两个点的值，并且刷新关系
    void Exchange(qint16 v1,qint16 v2);

    // 还原顶点和边
    void ClearGraph();

    // 获取顶点数组中的顶点数
    qint16 GetVexnum(void);
};

#endif // CGRAPH_H
