#include "CHelpDialog.h"
#include "ui_CHelpDialog.h"

CHelpDialog::CHelpDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CHelpDialog)
{
    ui->setupUi(this);
    show();
}

CHelpDialog::~CHelpDialog()
{
    delete ui;
}
