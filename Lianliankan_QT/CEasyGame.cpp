#include "CEasyGame.h"

CEasyGame::CEasyGame():CGameControl()
{

}


CEasyGame::CEasyGame(qint16 Col,qint16 Row):CGameControl(Col,Row)
{

}

void CEasyGame::StartGame()
{
    m_gameLogic.SetMapLen(mapCol,mapRow);
    m_gameLogic.InitMap(m_graph);

    m_toolNum=0;

    CTest::Output(m_graph);
}

// 连接判断函数
bool CEasyGame::Link(Vertex m_svSelFst,Vertex m_svSelSec)
{
    if(CGameControl::Link(m_svSelFst,m_svSelSec))
    {
        m_nGrade+=10;
        if(m_nGrade%100==0)
        {
            m_toolNum++;
        }
        return TRUE;
    }else
    {
        return FALSE;
    }
}

bool CEasyGame::Help(qint16 *avPath, qint16 &nVexnum)
{
    if(m_nGrade>20)
    {
        m_nGrade-=20;
        return CGameControl::Help(avPath,nVexnum);
    }
    return false;
}

void CEasyGame::Reset()
{
    if(m_nGrade>50)
    {
        m_nGrade-=50;
        CGameControl::Reset();
    }
}

bool CEasyGame::ProLink()
{
    if(m_toolNum<1)
    {
        m_toolNum=0;
        return false;
    }
    qint16 nInfo1=0,nInfo2=0,vexNum = m_graph.GetVexnum();

    for (qint16 i=0;i<vexNum;i++)
    {
        if(m_graph.GetVertex(i)!=BLANK)
        {
            nInfo1=i;
        }
    }
    for (qint16 i=0;i<vexNum;i++)
    {
        if(m_graph.GetVertex(i)==m_graph.GetVertex(nInfo1)&&i!=nInfo1)
        {
            nInfo2=i;
        }
    }

    if(m_graph.GetVertex(nInfo1)==m_graph.GetVertex(nInfo2)&&m_graph.GetVertex(nInfo1)!=BLANK)
    {
        m_graph.UpdateVertex(nInfo1,BLANK);
        m_graph.UpdateVertex(nInfo2,BLANK);

        m_gameLogic.UpdateArc(m_graph,nInfo1/mapCol,nInfo1%mapCol);
        m_gameLogic.UpdateArc(m_graph,nInfo2/mapCol,nInfo2%mapCol);
        m_nGrade+=10;
        m_toolNum--;
        return true;
    }

    return false;
}

bool CEasyGame::SaveScore()
{
    SCORE CScore;
    QDateTime curDateTime=QDateTime::currentDateTime();
    CScore.nMode=1;
    CScore.strName = curDateTime.toString("yyyymmddhhmmss");
    CScore.nGrade = m_nGrade;

    // 调用CScoreLogic保存积分
    if(CScoreLogic::SaveScore(CScore))
    {
        // 保存积分成功
        return true;
    }

    return false;
}


