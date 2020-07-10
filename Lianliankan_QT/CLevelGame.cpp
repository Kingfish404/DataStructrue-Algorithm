#include "CLevelGame.h"

CLevelGame::CLevelGame():CGameControl()
{
}


CLevelGame::CLevelGame(qint16 Col,qint16 Row):CGameControl(Col,Row)
{
}


void CLevelGame::StartGame()
{
    m_gameLogic.SetMapLen(mapCol,mapRow);
    m_gameLogic.InitMap(m_graph);

    CTest::Output(m_graph);
}

// 连接判断函数
bool CLevelGame::Link(Vertex m_svSelFst,Vertex m_svSelSec)
{
    if(CGameControl::Link(m_svSelFst,m_svSelSec))
    {
        m_nGrade+=10;

        return TRUE;
    }else
    {
        return FALSE;
    }
}

bool CLevelGame::SaveScore()
{
    SCORE CScore;
    QDateTime curDateTime=QDateTime::currentDateTime();
    CScore.nMode=2;
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
