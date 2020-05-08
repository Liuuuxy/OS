#include <Windows.h>
#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include <time.h>
#include <easyx.h>
/*
（1）奇数号的哲学家先拿起右边的筷子再拿起左边的筷子。

（2）偶数号哲学家先拿起左边的筷子，再拿起右边的筷子。

（3）如果哲学家抢到一只筷子，在抢占另一只筷子时失败，则要放弃已经抢占到的资源。

（4）左右两边都抢到筷子的哲学家，吃完放后释放资源。*/
using namespace std;

HANDLE chop[5];
HANDLE ph[5];
HANDLE mutex;
int nums = 0;

int random()
{
    return rand() % 100 + 20;
}
void eating(int id)
{
    int num = random();
    Sleep(num);
    printf("\t\t\t哲学家%d号吃了%d秒\n", id, num);
}

DWORD WINAPI phthread(LPVOID param) {
    nums++;
    int id = nums;
    int lc = id - 1;
    int rc = id % 5;
    int times = 0;
    int ret1, ret2;
    while (true)
    {
        Sleep(100);
        if (times >= 2)
            break;
        if (id % 2 == 0)
        {
            ret1 = WaitForSingleObject(chop[lc], 0);
            if (ret1 == WAIT_OBJECT_0)
            {
                ret2 = WaitForSingleObject(chop[rc], 0);
                if (ret2 == WAIT_OBJECT_0)
                {
                    WaitForSingleObject(mutex, INFINITE);
                    char s[100];
                    sprintf(s, "哲学家%d号拿到两只筷子开始吃第%d顿饭。\n", id, times + 1);
                    outtextxy(700,100,s);
                    ReleaseMutex(mutex);
                    times++;
                    WaitForSingleObject(mutex, INFINITE);
                    eating(id);
                    ReleaseMutex(mutex);
                    WaitForSingleObject(mutex, INFINITE);
                    sprintf(s,"\t\t\t哲学家%d号吃完两顿饭啦，放下筷子。\n", id);
                    outtextxy(700, 200, s);
                    ReleaseMutex(mutex);
                    ReleaseSemaphore(chop[rc], 1, NULL);
                }
                ReleaseSemaphore(chop[lc], 1, NULL);
            }
        }
        else
        {
            ret1 = WaitForSingleObject(chop[rc], 0);
            if (ret1 == WAIT_OBJECT_0)
            {
                ret2 = WaitForSingleObject(chop[lc], 0);
                if (ret2 == WAIT_OBJECT_0)
                {
                    WaitForSingleObject(mutex, INFINITE);
                    char s[100];
                    sprintf(s,"哲学家%d号拿到两只筷子开始吃%d顿饭。\n", id, times + 1);
                    outtextxy(700, 100, s);
                    ReleaseMutex(mutex);
                    times++;
                    WaitForSingleObject(mutex, INFINITE);
                    eating(id);
                    ReleaseMutex(mutex);
                    WaitForSingleObject(mutex, INFINITE);
                    printf("\t\t\t哲学家%d号吃完两顿饭啦，放下筷子。\n", id);
                    ReleaseMutex(mutex);
                    ReleaseSemaphore(chop[lc], 1, NULL);
                }
                ReleaseSemaphore(chop[rc], 1, NULL);
            }
        }
        WaitForSingleObject(mutex, INFINITE);
        ReleaseMutex(mutex);
    }
    printf("=======哲学家%d吃饱了然后离开了。=======\n", id);
    return 0;

}

int main()
{
    initgraph(1200, 600);
    fillcircle(400, 300, 200);//桌子
    fillcircle(400, 50, 30);//哲学家1
    fillcircle(150, 230, 30);//哲学家2
    fillcircle(650, 230, 30);//哲学家3
    fillcircle(230, 520, 30);//哲学家4
    fillcircle(570, 520, 30);//哲学家5
    //筷子    
    line(0, 0, 1, 1);
    setlinecolor(0x9D8487);
    line(450, 300, 550, 350);
    setlinecolor(0x9D8487);
    line(350, 300, 250, 350);
    setlinecolor(0x9D8487);
    line(400, 350, 400, 450);
    setlinecolor(0x9D8487);
    line(300, 150, 350, 250);
    setlinecolor(0x9D8487);
    line(500, 150, 450, 250);
    setlinecolor(0x9D8487);
    srand((unsigned)time(0));
    mutex = CreateMutex(NULL, false, NULL);
    for (int i = 0; i < 5; ++i)
    {
        chop[i] = CreateSemaphore(NULL, 1, 1, NULL);
    }
    for (int i = 0; i < 5; ++i)
    {
        int j = i + 1;
        ph[i] = CreateThread(NULL, 0, phthread, NULL, 0, NULL);
    }



    Sleep(10000);//释放句柄
    for (int i = 0; i < 5; ++i)
    {
        CloseHandle(ph[i]);
        CloseHandle(chop[i]);
    }
    CloseHandle(mutex);
    Sleep(500);
    system("pause");
    closegraph();
    return 0;
}