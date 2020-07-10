#ifndef CSCOREDAO_H
#define CSCOREDAO_H
#include <Qt>
#include "global.h"

class CScoreDao
{
public:
    CScoreDao();

    static bool Save(QString& strPath,SCORE& score);
};

#endif // CSCOREDAO_H
