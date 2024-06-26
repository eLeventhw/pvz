#include "wallnut.h"  // 包含头文件
#include <QDebug>  // 包含调试头文件

WallNut::WallNut()
{
    hp = 4000;  // 设置初始生命值
    setMovie(":/images/WallNut.gif");  // 设置初始动画
}

void WallNut::advance(int phase)
{
    if (!phase)  // 如果不是更新阶段，直接返回
        return;
    update();  // 更新图形状态

    if (hp <= 0)  // 如果生命值小于等于0，销毁当前对象
        delete this;
    else if (hp <= 1333 && state != 2)  // 如果生命值小于等于1333且状态不是2，改变状态为2并设置新的动画
    {
        state = 2;
        setMovie(":/images/WallNut2.gif");  // 设置受损较严重的动画
    }
    else if (1333 < hp && hp <= 2667 && state != 1)  // 如果生命值在1333到2667之间且状态不是1，改变状态为1并设置新的动画
    {
        state = 1;
        setMovie(":/images/WallNut1.gif");  // 设置受损较轻的动画
    }
}
