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

struct rainCircle       //���������ɵ�ˮȦ
{
    int x;
    int y;
    int r;
    int curR;
    int rainCircleStep;    //ˮȦ��˳��
};

class raining
{
    int startX;   //��㿪ʼ��Xֵ
    int startY;   //��㿪ʼ��Yֵ
    int endY;     //��������Yֵ
    int curX;     //��㽵���е�Xֵ
    int curY;     //��㽵���е�Yֵ
    int rainLineStep;   //���ߵ�˳��
    int rainLineLength;   //���ߵĳ���
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

    void updateRainLineData()  //������ʼ����Yֵ
    {
        curX+=rainLineStep;
        curY+=rainLineStep;
        startY=curY-rainLineLength;
        startX=curX-5;
    }
    void drawRainLine()   //������
    {
        setcolor(WHITE);
        line(startX,startY,curX,curY);
    }
    void clearRainLine()    //�Ժ�ɫ��ʾ������ʧ
    {
        setcolor(BLACK);
        line(startX,startY,curX,curY);
    }
    void updateRainCircleData()   //����ˮȦ�Ĵ�С
    {
        water.curR+=water.rainCircleStep;
    }

    void drawRainCircle()   //���꽵����ˮȦ
    {
        setcolor(WHITE);
       ellipse(water.x,water.y,0,360,water.curR,water.curR/2);
    }

    void clearRainCircle()   //�Ժ�ɫ��ʾˮȦ��ʧ
    {

        setcolor(BLACK);
        ellipse(water.x,water.y,0,360,water.curR,water.curR/2);
    }
    void rainDropDown()   //�������·��
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
    void fallToWater()   //������Ȧ�����ν�
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
    void updatecloudData()   //�����Ʋʵ�λ��
    {
        erx+=cloudStep;
    }
     void drawcloud() //���Ʋ�
    {
        setfillcolor(WHITE);
        setcolor(WHITE);
        fillellipse(erx,y,a,b);
    }
    void clearcloud()    //�Ժ�ɫ��ʾ�Ʋ���ʧ
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
void creatRain(raining yu[])    //������
{
    int i;
    for(i = 0;i<100;i++)
        yu[i].creatDrop();
}
void creatcloud(cloud yu[])    //������
{
    int i;
    for(i = 0;i<5;i++)
      {
          yu[i].creatcloud();

      }
}
void rain(raining yu[],cloud w[])    //����ȫ����Ŀ�ʼ������
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
    //PIMAGE img = newimage(); // ����ͼ�����
    //getimage(img,"1.jpg"); // ����ͼƬ�ļ�
   // initgraph(getwidth(img), getheight(img));
    //putimage(0,0,img); // ����ͼƬ
    creatcloud(q);
    creatRain(p);
    rain(p,q);
    closegraph();
    return 0;
}
