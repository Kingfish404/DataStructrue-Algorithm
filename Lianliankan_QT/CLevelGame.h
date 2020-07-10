#ifndef CLEVELGAME_H
#define CLEVELGAME_H
#include "CGameControl.h"

class CLevelGame:public CGameControl
{
public:
    CLevelGame();

    CLevelGame(qint16 Col,qint16 Row);

    virtual void StartGame() override;

    virtual bool Link(Vertex m_svSelFst, Vertex m_svSelSec) override;

    virtual bool SaveScore() override;
};

#endif // CLEVELGAME_H
