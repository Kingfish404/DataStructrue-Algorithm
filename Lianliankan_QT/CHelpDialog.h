#ifndef CHELPDIALOG_H
#define CHELPDIALOG_H

#include <QDialog>

namespace Ui {
class CHelpDialog;
}

class CHelpDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CHelpDialog(QWidget *parent = nullptr);
    ~CHelpDialog();

private:
    Ui::CHelpDialog *ui;
};

#endif // CHELPDIALOG_H
