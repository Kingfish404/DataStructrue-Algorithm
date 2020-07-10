#ifndef CRANKDLG_H
#define CRANKDLG_H

#include <QDialog>
#include <CScoreLogic.h>
#include <QFile>
#include "global.h"

namespace Ui {
class CRankDlg;
}

class CRankDlg : public QDialog
{
    Q_OBJECT

public:
    explicit CRankDlg(QWidget *parent = nullptr);
    ~CRankDlg();

private slots:
    void on_rbtnEasy_clicked(bool checked);

    void on_rbtnGrade_clicked(bool checked);

private:
    Ui::CRankDlg *ui;
};

#endif // CRANKDLG_H
