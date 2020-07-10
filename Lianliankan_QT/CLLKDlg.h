#ifndef CLLKDLG_H
#define CLLKDLG_H

#include <QMainWindow>
#include <QMessageBox>
#include <QPainter>
#include "CGameDlg.h"
#include "CHelpDialog.h"
#include "CRankDlg.h"
#include "CSettingDlg.h"

QT_BEGIN_NAMESPACE
namespace Ui { class CLLKDlg; }
QT_END_NAMESPACE

class CLLKDlg : public QMainWindow
{
    Q_OBJECT
private:
    qint16 mapCol;      // 地图的宽度
    qint16 mapRow;      // 地图的高度
    QString gameName;   // 游戏名称

public:
    CLLKDlg(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *event);



    ~CLLKDlg();

private slots:
    // 按钮点击的信号槽函数
    void on_startBaseBtn_clicked();

    void on_startEasyBtn_clicked();

    void on_startGKBtn_clicked();

    void on_btnHelp_clicked();

    void on_btnQuit_clicked();

    void on_btnRank_clicked();

    void on_btnSetting_clicked();

    void changeStyle();

private:
    Ui::CLLKDlg *ui;
};
#endif // CLLKDLG_H
