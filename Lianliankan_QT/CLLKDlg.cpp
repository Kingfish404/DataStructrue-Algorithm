#include "CLLKDlg.h"
#include "ui_CLLKDlg.h"


CLLKDlg::CLLKDlg(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CLLKDlg)
{
    ui->setupUi(this);

    gameName=QString::fromUtf8("王国连连看");

    this->setWindowTitle(gameName);
    this->ui->labelTitle->setText(gameName);
    // 设置icon图标
    QIcon icon;
    icon.addFile(QString::fromUtf8(":/source/images/res/LLK.ico"), QSize(), QIcon::Normal, QIcon::On);
    this->setWindowIcon(icon);

    // 固定页面大小
    this->setFixedSize(800,600);

    // 初始化默认地图大小
    mapCol=DEFAULT_MAP_COL;
    mapRow=DEFAULT_MAP_ROW;

    changeStyle();
}

void CLLKDlg::paintEvent(QPaintEvent *event)
{
    //绘制窗口背景图片
    Q_UNUSED(event);
    QPainter painter(this);
    painter.drawPixmap(0,0,800,600,QPixmap(":/source/images/res/llk_main.jpg"));
}

void CLLKDlg::changeStyle()
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
                    this->setStyleSheet(QString::fromUtf8("#labelTitle{\n"
                                                          "	width:100%;\n"
                                                          "	text-align:center;\n"
                                                          "	font-size:80px;\n"
                                                          "	font-family: \"Microsoft Yahei\",Arial,Helvetica,sans-serif,\"\345\256\213\344\275\223\"!important;\n"
                                                          "}\n"
                                                          "\n"
                                                          ".QPushButton\n"
                                                          "{\n"
                                                          "	border-radius:10px;\n"
                                                          "	min-height:10px;\n"
                                                          "	min-width:20px;\n"
                                                          "	font-size:18px;\n"
                                                          "	color:black;\n"
                                                          "	background-color:rgb(202,174,126);\n"
                                                          "	border:1px solid black;\n"
                                                          "}\n"
                                                          ".QPushButton:hover\n"
                                                          "{\n"
                                                          "	font-size:20px;\n"
                                                          "	background-color:white;\n"
                                                          "}"));
                }else
                {
                    this->setStyleSheet(QString::fromUtf8("*{"
                                                          "background-color:white;"
                                                          "}"
                                                          "#labelTitle{\n"
                                                             "	width:100%;\n"
                                                             "	text-align:center;\n"
                                                             "	font-size:80px;\n"
                                                             "	font-family: \"Microsoft Yahei\",Arial,Helvetica,sans-serif,\"\345\256\213\344\275\223\"!important;\n"
                                                             "}\n"
                                                             "\n"
                                                             ".QPushButton\n"
                                                             "{\n"
                                                             "	min-height:10px;\n"
                                                             "	min-width:20px;\n"
                                                             "	font-size:18px;\n"
                                                             "	color:black;\n"
                                                             "	background-color:white;\n"
                                                             "	border:1px solid black;\n"
                                                             "}\n"
                                                             ".QPushButton:hover\n"
                                                             "{\n"
                                                             "	font-size:20px;\n"
                                                             "	background-color:white;\n"
                                                             "}"));
                }
            }
        }

        file.close();
    }
}


void CLLKDlg::on_startBaseBtn_clicked()
{
    CGameDlg* LLKGame = new CGameDlg(nullptr,mapCol,mapRow);

    LLKGame->setAttribute(Qt::WA_DeleteOnClose);
    this->setHidden(true);
    LLKGame->setGameMode(0);
    LLKGame->show();

    // 通过信号槽实现子窗口关闭时，父窗口显示
    connect(LLKGame,SIGNAL(ExitWin()),this,SLOT(show()));
}

void CLLKDlg::on_startEasyBtn_clicked()
{
    CGameDlg* LLKGame = new CGameDlg(nullptr,mapCol,mapRow);

    LLKGame->setAttribute(Qt::WA_DeleteOnClose);

    this->setHidden(true);
    LLKGame->setGameMode(1);
    LLKGame->show();

    // 通过信号槽实现子窗口关闭时，父窗口显示
    connect(LLKGame,SIGNAL(ExitWin()),this,SLOT(show()));
}

void CLLKDlg::on_startGKBtn_clicked()
{
    CGameDlg* LLKGame = new CGameDlg(nullptr,mapCol,mapRow);

    LLKGame->setAttribute(Qt::WA_DeleteOnClose);

    this->setHidden(true);
    LLKGame->setGameMode(2);
    LLKGame->show();

    // 通过信号槽实现子窗口关闭时，父窗口显示
    connect(LLKGame,SIGNAL(ExitWin()),this,SLOT(show()));
}


void CLLKDlg::on_btnHelp_clicked()
{
    new CHelpDialog(this);
}

void CLLKDlg::on_btnRank_clicked()
{
    new CRankDlg(this);
}

void CLLKDlg::on_btnSetting_clicked()
{
    CSettingDlg* settingDlg=new CSettingDlg;
    connect(settingDlg,SIGNAL(changeStyle()),this,SLOT(changeStyle()));
}

void CLLKDlg::on_btnQuit_clicked()
{
    this->close();
}

CLLKDlg::~CLLKDlg()
{
    delete ui;
}




