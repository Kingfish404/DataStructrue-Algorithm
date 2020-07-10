#ifndef CEASYGAME_H
#define CEASYGAME_H
#include "CGameControl.h"

class CEasyGame:public CGameControl
{
protected:
    qint16 m_toolNum;
public:
    CEasyGame();

    CEasyGame(qint16 Col,qint16 Row);

    virtual void StartGame() override;

    // 连接判断函数
    virtual bool Link(Vertex m_svSelFst,Vertex m_svSelSec) override;

    // 提示，查找是否有可以联通的路线
    virtual bool Help(qint16* avPath,qint16 &nVexnum) override;

    // 重新排列未消除棋子
    virtual void Reset() override;

    // 使用道具
    virtual bool ProLink() override;

    // 保存记录
    virtual bool SaveScore() override;
};

#endif // CEASYGAME_H
