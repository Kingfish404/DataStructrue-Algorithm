#include "CGraph.h"

CGraph::CGraph()
{

}


void CGraph::InitGraph(void)
{
    m_nVexnum=0;
    m_nArcnum=0;
    for(qint16 i=0;i<MAX_VERTEX_NUM;i++)
    {
        for (qint16 j=0;j<MAX_VERTEX_NUM;j++) {
            m_AdjMatrix[i][j]=false;
        }
        m_Vertices[i]=BLANK;
    }
}

void CGraph::setMapLen(qint16 len)
{
    m_mapLen=len;
}

qint16 CGraph::getMapLen()
{
    return  m_mapLen;
}

qint16 CGraph::AddVertex(qint16 info)
{
    m_Vertices[m_nVexnum]=info;
    m_nVexnum++;

    return info;
}

void CGraph::UpdateVertex(qint16 nIndex,qint16 info)
{
    m_Vertices[nIndex]=info;
}

qint16 CGraph::GetVertex(qint16 nIndex)
{
    if(nIndex<0||nIndex>=m_nVexnum)
    {
        return -1;
    }
    return m_Vertices[nIndex];
}

bool CGraph::GetArc(qint16 nV1Index, qint16 nV2Index)
{
    return m_AdjMatrix[nV1Index][nV2Index];
}

// 添加关系矩阵中,nV1Index与nV2Index的关系
void CGraph::AddArc(qint16 nV1Index,qint16 nV2Index)
{
    if(m_AdjMatrix[nV1Index][nV2Index]==true)
    {
        return;
    }
    m_AdjMatrix[nV1Index][nV2Index]=true;
    m_AdjMatrix[nV2Index][nV1Index]=true;

    m_nArcnum++;
}

// 交换两个点的值，并且刷新关系
void CGraph::Exchange(qint16 v1, qint16 v2)
{
    qint16 temp=m_Vertices[v1];
    m_Vertices[v1]=m_Vertices[v2];
    m_Vertices[v2]=temp;
}

void CGraph::ClearGraph()
{
    InitGraph();
}

qint16 CGraph::GetVexnum(void)
{
    return m_nVexnum;
}

CGraph::~CGraph()
{

}
