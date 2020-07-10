#include "CGameDlg.h"
#include "ui_CGameDlg.h"

CGameDlg::CGameDlg(QWidget *parent,qint16 tmapCol,qint16 tmapRow) :
    QMainWindow(parent),
    ui(new Ui::CGameDlg)
{
    // 初始化游戏的UI
    ui->setupUi(this);

    // 添加动画监控
    ui->widgetDraw->installEventFilter(this);

    // 修改样式
    ui->barLeftTime->setRange(0,100);

    shouldPainer=false;
    m_bPause=false;

    // 初始化时间监控
    qtimer = new QTimer(this);

    // 初始化窗口
    QIcon icon;
    icon.addFile(QString::fromUtf8(":/source/images/res/LLK.ico"), QSize(), QIcon::Normal, QIcon::Off);
    this->setWindowIcon(icon);
    this->setFixedSize(800,600);
    this->setStyleSheet("#centralwidget{background-color:white;}");

    m_bPlaying=false;

    // 设置地图大小并分配按钮内存
    mapCol=tmapCol;
    mapRow=tmapRow;
    btnMap = new QPushButton**[mapRow];
    for (qint16 i=0;i<mapRow;i++) {
        btnMap[i]=new QPushButton*[mapCol];
    }

    changeStyle();
}

void CGameDlg::changeStyle()
{
    QFile file("theme\\config.ini");
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        while (!file.atEnd()) {
            QString str = file.readLine();
            QStringList strList = str.split("=");
            if(strList[0]=="style")
            {
                if(strList[1]=="1")
                {
                    ui->frameSet->setStyleSheet(QString::fromUtf8(".QFrame{\n"
                                                                  "	background-image:url(:/source/images/res/llk_game_bg.jpg);\n"
                                                                  "	background-repeat:no-repeat;\n"
                                                                  "}\n"
                                                                  ".QPushButton\n"
                                                                  "{\n"
                                                                  "	border-radius:5px;\n"
                                                                  "	height:25px;\n"
                                                                  "	background-color:white;\n"
                                                                  "	border:1px solid blac\n"
                                                                  "}\n"
                                                                  ".QPushButton{\n"
                                                                  "	color:black;\n"
                                                                  "	background-color:rgb(202,174,126);\n"
                                                                  "}\n"
                                                                  "\n"
                                                                  ".QPushButton:pressed{\n"
                                                                  "	color:white;\n"
                                                                  "}\n"
                                                                  ".QPushButton:hover{\n"
                                                                  "	background-color:white;\n"
                                                                  "}"));
                }else
                {
                    ui->frameSet->setStyleSheet(QString::fromUtf8(".QFrame{\n"
                                                              "}\n"
                                                              ".QPushButton\n"
                                                              "{\n"
                                                              "	height:25px;\n"
                                                              "	background-color:white;\n"
                                                              "	border:1px solid blac\n"
                                                              "}\n"
                                                              ".QPushButton{\n"
                                                              "	color:black;\n"
                                                              "	background-color:white;\n"
                                                              "}\n"
                                                              "\n"
                                                              ".QPushButton:pressed{\n"
                                                              "	color:white;\n"
                                                              "}\n"
                                                              ".QPushButton:hover{\n"
                                                              "	background-color:white;\n"
                                                              "}"));
                }
            }
        }

        file.close();
    }
}

void CGameDlg::setGameMode(qint16 i)
{
    // 设置游戏模式
    QString title= "王国连连看";
    FLAG flag;
    gameMode=i;
    switch (i)
    {
    case 0:
        m_pGameC=new CBasicGame(mapCol,mapRow);

        flag.bTimer=true;
        flag.bProp=false;
        flag.bScore=false;
        flag.szTitle=QString("基本模式");

        // 添加时间监控信号反馈
        connect(qtimer,SIGNAL(timeout()),this,SLOT(time_out()));
        break;
    case 1:
        m_pGameC=new CEasyGame(mapCol,mapRow);

        flag.bTimer=false;
        flag.bProp=true;
        flag.bScore=true;
        flag.szTitle=QString("休闲模式");
        CalculateGameGrade();

        // 隐藏剩余时间显示
        ui->barLeftTime->hide();
        ui->labLeftTime->hide();
        ui->LabTime->hide();
        break;
    case 2:
        m_pGameC=new CLevelGame(mapCol,mapRow);

        flag.bTimer=false;
        flag.bProp=false;
        flag.bScore=true;
        flag.szTitle=QString("关卡模式");

        // 隐藏剩余时间显示
        ui->barLeftTime->hide();
        ui->labLeftTime->hide();
        ui->LabTime->hide();
        break;
    default:
        break;
    }

    m_pGameC->SetGameFlag(flag);

    // 初始化默认信息
    m_bFirstPoint=true;

    // 初始化地图界面
    initMap();
    m_flag = m_pGameC->GetGameFlag();

    // 通过FLAG设置界面
    ui->barLeftTime->setVisible(m_flag.bTimer);
    ui->LabTime->setVisible(m_flag.bTimer);
    ui->labLeftTime->setVisible(m_flag.bTimer);

    this->setWindowTitle(title+"-"+m_flag.szTitle);

    ui->labelGradeInfo->setVisible(m_flag.bScore);
    ui->labelGrade->setVisible(m_flag.bScore);

    ui->btnTool->setVisible(m_flag.bProp);
}

void CGameDlg::DrawGameGrade()
{
    // 绘制游戏分数
    ui->labelGrade->setText(QString::number(m_pGameC->GetGrade()));
    if(gameMode==1)
    {
        CalculateGameGrade();
    }
}

void CGameDlg::CalculateGameGrade()
{
    qint16 grade = m_pGameC->GetGrade();

    if(grade<=20)
    {
        ui->btnTips->setEnabled(false);
        ui->btnReset->setEnabled(false);
    }else if(grade<=50)
    {
        ui->btnTips->setEnabled(true);
        ui->btnReset->setEnabled(false);
    }else
    {
        ui->btnTips->setEnabled(true);
        ui->btnReset->setEnabled(true);
    }
}


bool CGameDlg::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->widgetDraw && event->type() == QEvent::Paint)
    {
        painterLine();
    }
    return QWidget::eventFilter(watched,event);
}

void CGameDlg::painterLine()
{
    // 判断是否应当刷新
    if(shouldPainer)
    {
        qint16 fx,fy,sx,sy;
        if(isTips)
        {
            fx=m_anPath[0]%mapCol;
            fy=m_anPath[0]/mapCol;
        }else
        {
            fx=m_svSelFst.col;
            fy=m_svSelFst.row;
        }
        QPainter painter(ui->widgetDraw);
        painter.setRenderHint(QPainter::Antialiasing, true);
        QPen pen;
        pen.setColor(Qt::green);
        pen.setWidth(3);
        painter.setPen(pen);

        // 开始绘制路径
        for (qint16 i=0;i<m_anNum;i++)
        {
            sx=m_anPath[i]%mapCol;
            sy=m_anPath[i]/mapCol;
            painter.drawLine(margin_left+(fx+0.5)*MAP_ITEM_WIDTH,
                             margin_top+(fy+0.5)*MAP_ITEM_WIDTH
                             ,margin_left+(sx+0.5)*MAP_ITEM_WIDTH,
                             margin_top+(sy+0.5)*MAP_ITEM_WIDTH);
            fx=sx;
            fy=sy;
        }
        painter.end();

        shouldPainer=false;
    }
}

void CGameDlg::time_out()
{
    // 和时间相关的触发函数
    lastTime--;
    ui->barLeftTime->setValue(lastTime*100/GAME_TOTAL_TIME);
    ui->LabTime->setText(QString::number(lastTime)+"S");

    if(lastTime==0)
    {
        qtimer->stop();
        QMessageBox::about(this,"You Failed!","时间用完，下次请加快速度哦");
        this->ui->btnStart->setEnabled(true);
        m_bPlaying=false;
    }
}

void CGameDlg::on_btnStart_clicked()
{
    // 初始化计时表
    qtimer->start(1000);
    ui->barLeftTime->setValue(100);
    lastTime=GAME_TOTAL_TIME;

    m_pGameC->StartGame();
    initGameMap();
    m_bPlaying=true;
    this->ui->btnStart->setDisabled(true);
}

void CGameDlg::on_btnPause_clicked()
{
    if(m_bPlaying)
    {
        if(!m_bPause)
        {
            ui->btnPause->setText("继续游戏");
            m_bPause=true;
            qtimer->stop();
        }else
        {
            ui->btnPause->setText("暂停游戏");
            m_bPause=false;
            qtimer->start();
        }
    }
}


void CGameDlg::on_btnTips_clicked()
{
    if(m_bPlaying==false||m_bPause)
    {
        return ;
    }

    // 清除上一次绘制的路径
    shouldPainer=false;
    update();

    if(m_pGameC->Help(m_anPath,m_anNum))
    {
        // 绘制路径
        isTips=true;
        shouldPainer=true;
        repaint();
        isTips=false;
    }else
    {

    }
    DrawGameGrade();
}

void CGameDlg::on_btnReset_clicked()
{
    // 重新排列现有图片
    m_pGameC->Reset();

    // 刷新界面
    initGameMap();
    DrawGameGrade();
}

void CGameDlg::initGameMap(void)
{
    // 更新游戏地图
    shouldPainer=false;
    update();
    for (qint16 i=0;i<mapRow;i++)
    {
        for (qint16 j=0;j<mapCol;j++)
        {
            QString bgImg= QString::number(m_pGameC->GetElement(i,j),10);
            if(bgImg=="-1")
            {
                btnMap[i][j]->hide();
                continue;
            }
            btnMap[i][j]->setStyleSheet(
                        ".QPushButton{"
                        "background-image:url("
                        ":/source/images/res/"+bgImg+".png);"
                                                     "}");
            btnMap[i][j]->show();
        }
    }
}


void CGameDlg::on_btnTool_clicked()
{
    if(m_pGameC->ProLink())
    {
        // 绘制路径

        shouldPainer=true;
        update();

        // 更新积分
        DrawGameGrade();

        initGameMap();
    }
}

void  CGameDlg::OnLButtonUp()
{
    if(m_bPlaying==false||m_bPause)
    {
        return ;
    }

    // 清除上一次绘制的路径
    shouldPainer=false;
    update();

    QObject* o = sender();
    qint8 i,j;
    i=o->property("i").toInt();
    j=o->property("j").toInt();

    if(m_bFirstPoint)
    {
        m_svSelFst.row=i;
        m_svSelFst.col=j;
        m_bFirstPoint=false;
    }else
    {
        m_svSelSec.row=i;
        m_svSelSec.col=j;

        if(m_pGameC->Link(m_svSelFst,m_svSelSec))
        {
            m_pGameC->Way(m_anPath,m_anNum);

            // 如果可以消去，则对地图进行更新
            btnMap[m_svSelFst.row][m_svSelFst.col]->hide();
            btnMap[m_svSelSec.row][m_svSelSec.col]->hide();

            // 更新积分
            DrawGameGrade();

            // 绘制路径
            if(!shouldPainer)
            {
                shouldPainer=true;
                update();
            }

            // 判断游戏是否胜利并执行相应函数
            JudgeWin();

        }else
        {
            // 无法消去，则将当前点设为第一点
            m_svSelFst.row=m_svSelSec.row;
            m_svSelFst.col=m_svSelSec.col;
        }
        m_bFirstPoint=false;
    }
}

void CGameDlg::JudgeWin()
{
    if(m_pGameC->IsWin())
    {
        shouldPainer=false;
        update();
        if(gameMode==0)
        {
            // 基本模式-无积分
            qtimer->stop();

            QMessageBox::about(this,"You Win!","恭喜你胜利了");
            this->ui->btnStart->setEnabled(true);

        }else{
            // 休闲和关卡模式-有积分
            QMessageBox::StandardButton result;
            result=QMessageBox::question(this,"You Win!","恭喜你胜利了\n是否保存记录?",
                                         QMessageBox::Yes|QMessageBox::No);
            if(result==QMessageBox::Yes)
            {
                // 如果选择保存记录
                if(m_pGameC->SaveScore())
                {
                    QMessageBox::about(this,"消息","记录保存成功");
                }
            }else
            {
                // 不保存记录
            }
        }

        this->ui->btnStart->setEnabled(true);
        m_bPlaying=false;
    }
}

void CGameDlg::initMap()
{
    switch (mapCol)
    {
    case 4:
        margin_left=250;
        margin_top = 200;
        break;
    case 10:
        margin_left=qAbs(500-mapCol*MAP_ITEM_WIDTH);
        margin_top =qAbs(470-mapCol*MAP_ITEM_WIDTH);
        break;
    case 16:
        margin_left=30;
        margin_top=70;
        break;
    default:
        margin_left=250;
        margin_top=200;
        break;

    }

    // 生成游戏按钮
    for (qint16 i=0;i<mapRow;i++)
    {
        for (qint16 j=0;j<mapCol;j++)
        {
            QString bgImg= QString::number(m_pGameC->GetElement(i,j),10);

            // 为游戏按钮添加样式
            btnMap[i][j] =new QPushButton(this);
            btnMap[i][j]->move(j*MAP_ITEM_WIDTH+margin_left,i*MAP_ITEM_WIDTH+margin_top);
            btnMap[i][j]->resize(MAP_ITEM_WIDTH,MAP_ITEM_WIDTH);
            btnMap[i][j]->setFlat(true);
            btnMap[i][j]->setCheckable(true);
            btnMap[i][j]->setAutoExclusive(true);
            btnMap[i][j]->setProperty("i",i);
            btnMap[i][j]->setProperty("j",j);
            btnMap[i][j]->connect(btnMap[i][j],SIGNAL(clicked()),this,SLOT(OnLButtonUp()));
        }
    }

}

void CGameDlg::closeEvent(QCloseEvent *)
{
    emit ExitWin();
}

qint16 CGameDlg::getMapLen() const
{
    return mapCol;
}

void CGameDlg::setMapLen(const qint16 &value)
{
    mapCol = value;
}

void CGameDlg::on_btnHelp_clicked()
{
    new CHelpDialog(this);
}


void CGameDlg::on_btnSetting_clicked()
{
    CSettingDlg* settingDlg=new CSettingDlg;
    connect(settingDlg,SIGNAL(changeStyle()),this,SLOT(changeStyle()));
}


CGameDlg::~CGameDlg()
{
    // 释放动态数组空间
    for (qint16 i=0;i<mapRow;i++)
    {
        for (qint16 j=0;j<mapCol;j++)
        {
            if(btnMap[i][j]!=nullptr)
            {
                delete btnMap[i][j];
            }
        }
    }
    if (btnMap!=nullptr)
    {
        delete [] btnMap;
    }
    if(qtimer!=nullptr)
    {
        delete qtimer;
    }
    if(m_pGameC!=nullptr)
    {
        delete m_pGameC;
    }
    delete ui;
}

