#include "CLLKDlg.h"
#include "CGameDlg.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CLLKDlg w;
    w.show();
    return a.exec();
}
