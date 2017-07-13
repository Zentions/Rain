#include <iostream>
#include "graphics.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <math.h>
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

using namespace std;

struct rainCircle       //雨点落下造成的水圈
{
    int x;
    int y;
    int r;
    int curR;
    int rainCircleStep;    //水圈的顺序
};

class raining
{
    int startX;   //雨点开始的X值
    int startY;   //雨点开始的Y值
    int endY;     //雨点结束的Y值
    int curX;     //雨点降落中的X值
    int curY;     //雨点降落中的Y值
    int rainLineStep;   //雨线的顺序
    int rainLineLength;   //雨线的长度
    struct rainCircle water;
public:
    int status;
    void creatDrop()
    {

        startX=rand()%640;
        startY=rand()%430+140;
        endY=430+rand()%50;
        curX=startX;
        curY=startY;
        rainLineStep=8;
        rainLineLength=10;
        status=0;
        water.x=startX;
        water.y=endY;
        water.r=rand()%40;
        water.curR=rand()%2;
        water.rainCircleStep=rand()%2+1;

    }

    void updateRainLineData()  //控制起始雨点的Y值
    {
        curX+=rainLineStep;
        curY+=rainLineStep;
        startY=curY-rainLineLength;
        startX=curX-5;
    }
    void drawRainLine()   //画雨线
    {
        setcolor(WHITE);
        line(startX,startY,curX,curY);
    }
    void clearRainLine()    //以黑色表示雨线消失
    {
        setcolor(BLACK);
        line(startX,startY,curX,curY);
    }
    void updateRainCircleData()   //控制水圈的大小
    {
        water.curR+=water.rainCircleStep;
    }

    void drawRainCircle()   //画雨降落后的水圈
    {
        setcolor(WHITE);
       ellipse(water.x,water.y,0,360,water.curR,water.curR/2);
    }

    void clearRainCircle()   //以黑色表示水圈消失
    {

        setcolor(BLACK);
        ellipse(water.x,water.y,0,360,water.curR,water.curR/2);
    }
    void rainDropDown()   //控制雨的路径
    {
        if(curY>=endY)
        {
            clearRainLine();
            status=1;
        }
        else
        {
            clearRainLine();
            updateRainLineData();
            drawRainLine();
        }
    }
    void fallToWater()   //控制雨圈雨点的衔接
    {
        if(water.curR>=water.r)
        {
            clearRainCircle();
            creatDrop();
        }
        else
        {
            clearRainCircle();
            updateRainCircleData();
            drawRainCircle();
        }
    }
};
class cloud
{
    int x;
    int y;
    double erx;
    int a;
    int b;
    double cloudStep;
    int endx;
public:
    void creatcloud()
    {
       y = rand()%80;
       a = rand()%150 +70;
       b = a/4;
       x = -a;
       erx = x;srand(time(NULL));
       cloudStep = (rand()%10+10)/50.0;
       endx = 640+a;
    }
    void updatecloudData()   //控制云彩的位置
    {
        erx+=cloudStep;
    }
     void drawcloud() //画云彩
    {
        setfillcolor(WHITE);
        setcolor(WHITE);
        fillellipse(erx,y,a,b);
    }
    void clearcloud()    //以黑色表示云彩消失
    {

        setfillcolor(BLACK);
        setcolor(BLACK);
        fillellipse(erx,y,a,b);
    }
    void flow()
    {
        if(erx<endx)
        {
           clearcloud();
           updatecloudData();
           drawcloud();
        }
        else creatcloud();
    }
};
void creatRain(raining yu[])    //创建雨
{
    int i;
    for(i = 0;i<100;i++)
        yu[i].creatDrop();
}
void creatcloud(cloud yu[])    //创建云
{
    int i;
    for(i = 0;i<5;i++)
      {
          yu[i].creatcloud();

      }
}
void rain(raining yu[],cloud w[])    //控制全程雨的开始到结束
{

    while(!kbhit())
    {
        int i;
        for(i=0;i<100;i++)
       {
           w[i%5].flow();
           if(yu[i].status==0)
               yu[i].rainDropDown();
            else
                yu[i].fallToWater();
            Sleep((rand()%2+1)/10.0);
            if(i==99) i = -1;
        }
    }
}



int  main()
{
    initgraph(640,500);
    raining p[100];
    cloud q[5];
    sndPlaySound("1.wav",SND_ASYNC|SND_LOOP);
    //PIMAGE img = newimage(); // 创建图像对象
    //getimage(img,"1.jpg"); // 加载图片文件
   // initgraph(getwidth(img), getheight(img));
    //putimage(0,0,img); // 绘制图片
    creatcloud(q);
    creatRain(p);
    rain(p,q);
    closegraph();
    return 0;
}
