#ifndef CTEST_H
#define CTEST_H
#include <Qt>
#include <QFile>
#include "global.h"
#include "CGraph.h"

class CTest
{
public:
    CTest();

    static void Output(CGraph &g);
};

#endif // CTEST_H
