#include "CGameLogic.h"
#include "iostream"
CGameLogic::CGameLogic()
{
    mapRow=DEFAULT_MAP_COL;
}

void CGameLogic::SetMapLen(qint16 Col,qint16 Row)
{
    mapCol=Col;
    mapRow=Row;
}

void CGameLogic::InitMap(CGraph &graph)
{
    graph.InitGraph();

    QRandomGenerator random;
    random.seed(quint32(time(nullptr)));
//    qint16 anTemp[16]={2,0,1,3,2,2,1,3,2,1,0,0,1,3,0,3};
    qint16 anTemp[16]={2,0,1,3,5,5,6,3,2,1,0,0,6,4,0,4};

    qint16 r1,r2,temp;

    random.bounded(16);

    graph.setMapLen(mapCol);
    for (qint16 i=0;i<DEFAULT_MAP_ROW;i++)
    {
        for(qint16 j=0;j<DEFAULT_RANDOM_TIMES;j++)
        {
            r1 = random.bounded(mapCol);
            r2 = random.bounded(mapCol);
            temp=anTemp[r1];
            anTemp[r1]=anTemp[r2];
            anTemp[r2]=temp;
        }

        for (qint16 j=0;j<DEFAULT_MAP_COL;j++)
        {
            graph.AddVertex(anTemp[j]);
            UpdateArc(graph,i,j);
        }
    }
}

void CGameLogic::UpdateArc(CGraph &graph,qint16 nRow,qint16 nCol)
{
    qint16 nIndex=nRow*mapCol+nCol;
    qint16 selfType=graph.GetVertex(nIndex);

    if(nRow>0)
    {
        // 判断上方
        if(selfType==graph.GetVertex(nIndex-mapCol)||selfType==-1)
        {
            graph.AddArc(nIndex,nIndex-mapCol);
        }
    }

    if(nRow<mapCol-1)
    {
        // 判断下方
        if(selfType==graph.GetVertex(nIndex+mapCol)||selfType==-1)
        {
            graph.AddArc(nIndex,nIndex+mapCol);
        }
    }

    if(nCol>0)
    {
        // 判断左边
        if(selfType==graph.GetVertex(nIndex-1)||selfType==-1)
        {
            graph.AddArc(nIndex,nIndex-1);
        }
    }

    if(nCol<mapCol-1)
    {
        // 判断右边
        if(selfType==graph.GetVertex(nIndex+1)||selfType==-1)
        {
            graph.AddArc(nIndex,nIndex+1);
        }
    }
}

bool CGameLogic::IsLink(CGraph &graph,Vertex v1,Vertex v2)
{
    m_anNum=0;
    m_nCorner=0;

    qint16 v1Index=v1.row*mapCol+v1.col;
    qint16 v2Index=v2.row*mapCol+v2.col;

    if(SearchPath(graph,v1Index,v2Index))
    {
        return true;
    }

    return false;
}

bool CGameLogic::SearchPath(CGraph &g, qint16 nV0, qint16 nV1)
{

    PushVertex(nV0);

    // 深度优先搜索Depth-First-Search，判断V1，V2是否联通,联通返回true
    if(m_nCorner>2)
    {
        return false;
    }
    if(nV0==nV1)
    {

        if(m_nCorner<3)
        {
            return true;
        }
    }else
    {
        qint16 VexNum=g.GetVexnum();
        for (qint16 i=0;i<VexNum;i++)
        {
            if(IsExsit(i))
            {
                continue;
            }else if(g.GetArc(nV0,i))   // 判断是否联通,如果联通才进入下一层
            {
                // 判断联通方式是否为同色联通
                if(i!=nV1&&g.GetVertex(i)!=-1)
                {
                    continue;
                }

                if(SearchPath(g,i,nV1))
                {
                    return true;
                }
                PopVertex();
            }
        }
    }
    return false;
}

void CGameLogic::ResetGraph(CGraph &g)
{
    QRandomGenerator random;
    random.seed(quint32(time(nullptr)));
    qint16 r1,r2;

    for (qint16 i=0;i<DEFAULT_RANDOM_TIMES;i++)
    {
        r1 = random.bounded(mapCol*mapRow);
        r2 = random.bounded(mapCol*mapRow);
        if(g.GetVertex(r1)==BLANK||g.GetVertex(r2)==BLANK)
        {
            continue;
        }
        g.Exchange(r1,r2);
        UpdateArc(g,r1/mapCol,r1%mapCol);
        UpdateArc(g,r2/mapCol,r2%mapCol);
    }

}

bool CGameLogic::IsExsit(qint16 nVi)
{
    // 判断nVi点是否保存到联通数组m_anPath中
    for (qint16 i=0;i<m_anNum;i++)
    {
        if(m_anPath[i]==nVi)
        {
            return true;
        }
    }
    return false;
}

bool CGameLogic::IsCornor()
{
    // 判断数组m_anPath中，连续三个顶点是否构成一个顶点

    if(m_anNum < 3)
    {
        return false;
    }else
    {
        qint16 anNum=m_anNum-1;
        qint16 item[3][2]={{0}};

        for (qint16 i=0;i<3;i++)
        {
            item[i][0]=m_anPath[anNum-i]%mapCol;
            item[i][1]=m_anPath[anNum-i]/mapCol;
        }
        // 如果1,2列相等;2，3行相等
        if(item[0][1]==item[1][1]&&item[1][0]==item[2][0])
        {
            return true;
        }
        // 如果1,2行相等;2,3列相等
        if(item[0][0]==item[1][0]&&item[1][1]==item[2][1])
        {
            return true;
        }
        return false;
    }

}

void CGameLogic::PushVertex(qint16 nV)
{
    // 将索引号为nV的顶点压入m_anPath,并判断是否形成拐点，如果是，则拐点+1
    m_anPath[m_anNum++]=nV;
    if(IsCornor())
    {
        m_nCorner++;
    }
}

bool CGameLogic::IsBlank(CGraph &g)
{
    for (qint16 i=0;i<g.GetVexnum();i++)
    {
        if(g.GetVertex(i)!=BLANK)
        {
            return false;
        }
    }
    return true;
}

void CGameLogic::GetWay(qint16 *anPath,qint16 &anNum)
{
    anNum=m_anNum;
    for (qint16 i=0;i<m_anNum;i++)
    {
        anPath[i]=m_anPath[i];
    }
}

bool CGameLogic::SearchValidPath(CGraph graph)
{
    qint16 vexNum = graph.GetVexnum();

    for(qint16 i=0;i<vexNum;i++)
    {
        if(graph.GetVertex(i)==BLANK)
        {
            continue;
        }
        for (qint16 j=i+1;j<vexNum;j++)
        {
            if(i==j||graph.GetVertex(j)!=graph.GetVertex(i))
            {
                continue;
            }
            m_anNum=0;
            m_nCorner=0;
            if(SearchPath(graph,i,j))
            {
                return true;
            }
        }
    }
    return false;
}

void CGameLogic::PopVertex()
{
    // 从栈m_anPath中，取出一个顶点并判断取出前
    // 是否构成一个拐点，如果构成，则拐点减一
    if(IsCornor())
    {
        m_nCorner--;
    }
    m_anNum--;
}

void CGameLogic::Clear(CGraph &graph,Vertex v1,Vertex v2)
{
    qint16 v1Index=v1.row*mapCol+v1.col;
    qint16 v2Index=v2.row*mapCol+v2.col;
    graph.UpdateVertex(v1Index,-1);
    graph.UpdateVertex(v2Index,-1);

    UpdateArc(graph,v1.row,v1.col);
    UpdateArc(graph,v2.row,v2.col);
}


