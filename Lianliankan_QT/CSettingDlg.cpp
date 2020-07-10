#include "CSettingDlg.h"
#include "ui_CSettingDlg.h"

CSettingDlg::CSettingDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CSettingDlg)
{
    ui->setupUi(this);

    QDir dir;
    dir.mkdir("theme");

    show();
}

CSettingDlg::~CSettingDlg()
{
    delete ui;
}


void CSettingDlg::on_rbtnDefautl_clicked(bool checked)
{
    if(checked)
    {
        QFile file("theme\\config.ini");
        if(file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            file.write("style=1");
            file.close();
        }

        emit changeStyle();
    }
}

void CSettingDlg::on_rbtnThin_clicked(bool checked)
{
    if(checked)
    {
        QFile file("theme\\config.ini");
        if(file.open(QIODevice::WriteOnly| QIODevice::Text))
        {
            file.write("style=2");
            file.close();
        }
        emit changeStyle();
    }
}
