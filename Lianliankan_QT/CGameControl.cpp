#include "CGameControl.h"

CGameControl::CGameControl()
{
    mapCol=DEFAULT_MAP_COL;
    mapRow=DEFAULT_MAP_ROW;
    m_nGrade=0;
}

CGameControl::CGameControl(qint16 Col,qint16 Row)
{
    mapCol=Col;
    mapRow=Row;
    m_graph.InitGraph();
    m_nGrade=0;
}

qint16 CGameControl::GetGrade()
{
    return m_nGrade;
}

qint16 CGameControl::GetElement(qint16 nRow, qint16 nCol)
{
    return m_graph.GetVertex(nRow*mapCol+nCol);
}

void CGameControl::SetFirstPoint(qint16 nRow, qint16 nCol)
{
    m_svSelFst.row=nRow;
    m_svSelFst.col=nCol;
}

void CGameControl::SetSecPoint(qint16 nRow, qint16 nCol)
{
    m_svSelSec.row=nRow;
    m_svSelSec.col=nCol;
}

bool CGameControl::Link(Vertex svSelFst,Vertex svSelSec)
{
    m_svSelFst=svSelFst;
    m_svSelSec=svSelSec;

    qint16 v1Index=m_svSelFst.row*mapCol+m_svSelFst.col;

    qint16 v2Index=m_svSelSec.row*mapCol+m_svSelSec.col;

    // 判断两点的图像是否相同，如果不相同则判断无法消除
    if(m_graph.GetVertex(v1Index)!=m_graph.GetVertex(v2Index)|| v1Index==v2Index)
    {
        return false;
    }

    // 判断两点是否相连
    if(m_gameLogic.IsLink(m_graph,m_svSelFst,m_svSelSec))
    {
        m_gameLogic.Clear(m_graph,m_svSelFst,m_svSelSec);
        return true;
    }

    return false;
}

bool CGameControl::Help(qint16 *avPath, qint16 &nVexnum)
{
    if(m_gameLogic.IsBlank(m_graph))
    {
        return false;
    }else if(m_gameLogic.SearchValidPath(m_graph))
    {
        m_gameLogic.GetWay(avPath,nVexnum);
        return true;
    }
    return false;
}

void CGameControl::Reset()
{
    m_gameLogic.ResetGraph(m_graph);
}

void CGameControl::Way(qint16 *anPath, qint16 &anNum)
{
    m_gameLogic.GetWay(anPath,anNum);
}

bool CGameControl::IsWin()
{
    if(m_gameLogic.IsBlank(m_graph))
    {
        m_graph.ClearGraph();
        return true;
    }
    return false;
}

FLAG CGameControl::GetGameFlag()
{
    return m_flag;
}

void CGameControl::SetGameFlag(FLAG tFlag)
{
    m_flag=tFlag;
}

CGameControl::~CGameControl()
{
    // 释放动态数组空间
}



