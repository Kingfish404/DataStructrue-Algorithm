#ifndef CSETTINGDLG_H
#define CSETTINGDLG_H

#include <Qt>
#include <QDialog>
#include <QDir>
#include "global.h"

namespace Ui {
class CSettingDlg;
}

class CSettingDlg : public QDialog
{
    Q_OBJECT

public:
    explicit CSettingDlg(QWidget *parent = nullptr);
    ~CSettingDlg();

private slots:
    void on_rbtnDefautl_clicked(bool checked);

    void on_rbtnThin_clicked(bool checked);

signals:
    void changeStyle();

private:
    Ui::CSettingDlg *ui;


};

#endif // CSETTINGDLG_H
