#ifndef CGAMECONTROL_H
#define CGAMECONTROL_H
#include "QDateTime"
#include"global.h"
#include"CGameLogic.h"
#include"CGraph.h"
#include"CScoreLogic.h"
#include"CTest.h"

class CGameControl
{
protected:
    CGameLogic m_gameLogic;
    qint16 mapCol;      // 地图的宽度
    qint16 mapRow;      // 地图的高度
    CGraph m_graph;     // 游戏地图

    Vertex m_svSelFst;  // 选中的第一个点
    Vertex m_svSelSec;  // 选中的第二个点

    FLAG m_flag;  // 展示类型

    qint16 m_nGrade;    // 当前积分

public:
    CGameControl();

    CGameControl(qint16 Col,qint16 Row);

    // 开始游戏函数,初始化了地图数据
    virtual void StartGame(void)=0;

    // 获取当前积分
    virtual qint16 GetGrade();

    // 使用道具
    virtual bool ProLink(){return true;};

    // 获取某行列的图片编号
    qint16 GetElement(qint16 nRow,qint16 nCol);

    // 设置第一个点
    void SetFirstPoint(qint16 nRow,qint16 nCol);

    // 设置第二个点
    void SetSecPoint(qint16 nRow,qint16 nCol);

    // 连接判断函数
    virtual bool Link(Vertex m_svSelFst,Vertex m_svSelSec);

    // 获得路径
    void Way(qint16* anPath,qint16 &anNum);

    virtual bool SaveScore(){return false;};

    // 提示，查找是否有可以联通的路线
    virtual bool Help(qint16* avPath,qint16 &nVexnum);

    // 重新排列未消除棋子
    virtual void Reset();

    // 是否获胜，如果所有的顶点为空则获胜
    bool IsWin();

    // 获取Flag类型变量
    FLAG GetGameFlag();

    // 设置Flag类型变量
    void SetGameFlag(FLAG tFlag);

    virtual ~CGameControl();
};

#endif // CGAMECONTROL_H
