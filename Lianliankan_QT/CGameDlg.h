#ifndef CGAMEDLG_H
#define CGAMEDLG_H
#define DEAFULT_MAP_SIZE 4
#include <QMainWindow>
#include <QPushButton>
#include <QMessageBox>
#include <QPainter>
#include <QTimer>
#include <QRandomGenerator>
#include <QtWidgets/QHBoxLayout>

#include "CLevelGame.h"
#include "CBasicGame.h"
#include "CEasyGame.h"

#include "CHelpDialog.h"
#include "CSettingDlg.h"
#include "global.h"

namespace Ui {
class CGameDlg;
}

class CGameDlg : public QMainWindow
{
    Q_OBJECT

private:

    Ui::CGameDlg *ui;     // 指针指向真实的UI


protected:
    CGameControl* m_pGameC;

    QTimer* qtimer;        // Qt倒计时
    QPushButton*** btnMap;   // 游戏地图
    QWidget *GameMap;

    qint16 m_anPath[MAX_VERTEX_NUM];   // 保存连通图的顶点索引
    qint16 m_anNum;                    // m_anPath中的数

    bool m_bFirstPoint;     // 是否为第一次选中
    Vertex m_svSelFst;  // 选中的第一个点
    Vertex m_svSelSec;  // 选中的第二个点

    qint16 margin_left; // 地图离左边的距离
    qint16 margin_top;  // 地图离右边的距离

    bool  m_bPlaying;          // 游戏是否开始

    bool m_bPause;             // 游戏是否暂停

    bool isTips;                // 是否是提示

    qint16 gameMode;             //设置游戏模式
    // 0-基本模式,1-休闲模式，2-关卡模式

    qint16 lastTime;            // 剩余时间

    qint16 mapCol;       // 地图的大小
    qint16 mapRow;      // 地图的高度

    FLAG m_flag;    // Flag

    bool shouldPainer;  // 是否应该画图

    bool eventFilter(QObject *watched, QEvent *event);

    void painterLine();

public:
    explicit CGameDlg(QWidget *parent = nullptr,qint16 mapCol=DEFAULT_MAP_COL,qint16 mapRow=DEFAULT_MAP_ROW);

    void setGameMode(qint16 i=0);    // 设置游戏模式

    void initMap();             // 初始化地图界面

    void initGameMap(void);    // 更新游戏窗口大小

    void DrawGameGrade();   //绘制游戏积分

    void CalculateGameGrade();  // 根据游戏积分控制按钮状态

    void JudgeWin();    // 判断游戏是否胜利并执行相关函数

    ~CGameDlg();

    qint16 getMapLen() const;
    void setMapLen(const qint16 &value);

private slots:

    void changeStyle();         // 修改主题

    void on_btnStart_clicked();    // 点击开始游戏

    void OnLButtonUp();       // 按下图片后的响应函数,更新游戏地图

    void on_btnReset_clicked();     // 重新排列游戏地图

    void on_btnPause_clicked();     // 暂停游戏

    void on_btnTips_clicked();      // 获取提示

    void time_out();                // 时间变化反应函数

    void closeEvent(QCloseEvent *);



    void on_btnHelp_clicked();

    void on_btnTool_clicked();

    void on_btnSetting_clicked();

signals:
    void ExitWin(); //新建一个关闭信号槽


};

#endif // CGAMEDLG_H
