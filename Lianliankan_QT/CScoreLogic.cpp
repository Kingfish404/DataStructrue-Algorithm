#include "CScoreLogic.h"

CScoreLogic::CScoreLogic()
{
}

bool CScoreLogic::SaveScore(SCORE &score)
{

    QString strPath=QString("Score\\score.llk");
    // 根据积分，计算积分等级
    if(score.nGrade<500)
    {
        score.nLevel=1;
    }else if(score.nGrade<1000)
    {
        score.nLevel=2;
    }else{
        score.nLevel=3;
    }


    // 调用CScoreDao.Save保存积分
    if(CScoreDao::Save(strPath,score))
    {
        return true;
    }
    return false;
}

QString CScoreLogic::getPath()
{
    return QString("Score\\score.llk");
}
