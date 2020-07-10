#ifndef CSCORELOGIC_H
#define CSCORELOGIC_H
#include <Qt>
#include "global.h"
#include "CScoreDao.h"

class CScoreLogic
{
public:
    CScoreLogic();

    static bool SaveScore(SCORE &score);

    static QString getPath();
};

#endif // CSCORELOGIC_H
