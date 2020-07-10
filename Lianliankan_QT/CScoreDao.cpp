#include "CScoreDao.h"
#include "QDir"

CScoreDao::CScoreDao()
{

}

bool CScoreDao::Save(QString &strPath, SCORE &score)
{
    QFile file(strPath);
    QDir dir;
    dir.mkdir("Score");

    if(!file.open(QIODevice::ReadWrite |QIODevice::Append | QIODevice::Text))
    {
        return false;
    }

    file.write(QString("%1").arg(score.nMode,2,10,QChar('0')).toUtf8());
    file.write("-");
    file.write(score.strName.toUtf8());
    file.write("-");
    file.write(QString("%1").arg(score.nGrade,5,10,QChar('0')).toUtf8());
    file.write("-");
    file.write(QString::number(score.nLevel).toUtf8());

    file.write("\n");

    file.close();

    return true;
}
