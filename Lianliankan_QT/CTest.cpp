#include "CTest.h"

CTest::CTest()
{

}

void CTest::Output(CGraph &g)
{
    QFile file("log.txt");
    file.open(QIODevice::WriteOnly | QIODevice::Text);


    qint16 len=g.GetVexnum();
    for (qint16 i=0;i<len;i++)
    {
        file.write(QString::number(g.GetVertex(i)).toUtf8());
        file.write(" ");
    }
    file.write("\n\n");

    for (qint16 i=0;i<len;i++)
    {
        for (qint16 j=0;j<len;j++)
        {
            if(g.GetArc(i,j))
            {
                file.write(QString::number(1).toUtf8());
            }else
            {
                file.write(QString::number(0).toUtf8());
            }

            file.write(" ");
        }
        file.write("\n");
    }

    if(file.isOpen())
    {
        file.close();
    }
}
