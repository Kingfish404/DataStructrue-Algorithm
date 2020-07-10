#include "CBasicGame.h"

CBasicGame::CBasicGame():CGameControl()
{

}

CBasicGame::CBasicGame(qint16 Col,qint16 Row):CGameControl(Col,Row)
{

}

void CBasicGame::StartGame()
{
    m_gameLogic.SetMapLen(mapCol,mapRow);
    m_gameLogic.InitMap(m_graph);

    CTest::Output(m_graph);
}
