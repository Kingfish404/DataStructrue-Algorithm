#pragma once
#ifndef GLOBAL_H
#define GLOBAL_H
#include <Qt>
#include <QDebug>
#define TRUE 1
#define FALSE 0

#define SUCCESS 1
#define ERROR 0

// 空白的值
#define BLANK -1

// 最大数据元素的个数
#define MAX_VERTEX_NUM 256

// 连连看默认地图大小
#define DEFAULT_MAP_COL 16

#define DEFAULT_MAP_ROW 10
// TODO 恢复至上述格式

// 连连看可用图片数目
#define ITEM_NUM 8

// 连连看方块的宽带
#define MAP_ITEM_WIDTH 40

// 游戏可以用的时间，单位：秒
#define GAME_TOTAL_TIME 300

// 每次随机刷新的次数
#define DEFAULT_RANDOM_TIMES 100

typedef struct tagVertex{
    qint16 row;
    qint16 col;
    qint16 info;
}Vertex;

typedef struct tagFlag
{
    bool bTimer;    // 计时进度条
    bool bProp;     // 道具
    bool bScore;    // 积分
    QString szTitle;    // 对话标题栏文字
}FLAG;

typedef struct tagScore
{
    qint16 nMode;   // 游戏模式，0基本模式，1休闲模式，2关卡模式
    qint16 nGrade;  // 积分分数
    qint16 nLevel;  // 积分等级
    QString strName;    // 玩家姓名
}SCORE;

#endif // GLOBAL_H
