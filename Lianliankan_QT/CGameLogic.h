#ifndef CGAMELOGIC_H
#define CGAMELOGIC_H
#include <QRandomGenerator>
#include"global.h"
#include"CGraph.h"

class CGameLogic
{
private:
    qint16 mapCol;      // 地图的宽度
    qint16 mapRow;      // 地图的高度

protected:
    qint16 m_anPath[MAX_VERTEX_NUM];   // 保存连通图的顶点索引
    qint16 m_anNum;                    // m_anPath中的数
    qint16 m_nCorner;     // 连接路径数组m_anPath中的拐点数

    // 深度优先搜索Depth-First-Search，判断V1，V2是否联通,联通返回true
    bool SearchPath(CGraph &g,qint16 nV0,qint16 nV1);

    // 判断nVi点是否保存到联通数组m_anPath中
    bool IsExsit(qint16 nVi);

    // 判断数组m_anPath中，连续三个顶点是否构成一个顶点
    bool IsCornor(void);

    // 将索引号为nV的顶点压入m_anPath,并判断是否形成拐点，如果是，则拐点+1
    void PushVertex(qint16 nV);

    // 从栈m_anPath中，取出一个顶点并判断取出前
    // 是否构成一个拐点，如果构成，则拐点减一
    void PopVertex();

public:
    CGameLogic();

    // 设置地图大小
    void SetMapLen(qint16 Col,qint16 Row);

    // 地图初始化函数
    void InitMap(CGraph &graph);

    // 判断某个点是否和周围的点相邻，如果有边，则更新图结构
    void UpdateArc(CGraph &graph,qint16 nRow,qint16 nCol);

    // 连接判断函数
    bool IsLink(CGraph &graph,Vertex v1,Vertex v2);

    // 消子函数
    void Clear(CGraph &graph,Vertex v1,Vertex v2);

    // 图中顶点是否为空，为空则返回true
    bool IsBlank(CGraph &g);

    // 获得联通路径
    void GetWay(qint16* anPath,qint16 &anNum);

    // 寻找联通路径
    bool SearchValidPath(CGraph graph);

    // 重新排列剩余图片
    void ResetGraph(CGraph &g);
};

#endif // CGAMELOGIC_H
