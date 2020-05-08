#include<graphics.h>
#include<easyx.h>
#include<stdio.h>
#include<Windows.h>
#include<math.h>
#define pi  3.1415926535897932

//���廭�����߳�
DWORD WINAPI drawSquare(LPVOID)
{
	//��Ϊ720����
	for (int i = 0; i < 180; i++)
	{
		putpixel(50 + i, 50, RED);
		Sleep(50);
	}
	for (int i = 0; i < 180; i++)
	{
		putpixel(50 + 180, 50 + i, RED);
		Sleep(50);
	}
	for (int i = 0; i < 180; i++)
	{
		putpixel(50 + 180 - i, 50 + 180, RED);
		Sleep(50);
	}
	for (int i = 0; i < 180; i++)
	{
		putpixel(50, 50 + 180 - i, RED);
		Sleep(50);
	}
	return 0;
}

//���廭Բ�ĺ���
DWORD WINAPI drawCircle(LPVOID)
{
	//ͬ����Ϊ720����
	for (int i = 0; i < 720; i++)
	{
		putpixel(350 + 100 * cos(-pi / 2 + (double)((i * pi) / 360)), 140 + 100 * sin(-pi / 2 + (double)((i * pi) / 360)), YELLOW);
		Sleep(50);
	}
	return 0;
}
int main()
{
	// ��ʼ��ͼ��ģʽ
	initgraph(640, 480);

	HANDLE hThread[2];//��¼���߳̾��
	DWORD threadID;//��¼�߳�ID
	if ((hThread[0] = CreateThread(NULL, 0, drawSquare, 0, 0, &threadID)) == NULL)
	{
		printf("�̴߳���ʧ��!");
	}
	if ((hThread[1] = CreateThread(NULL, 0, drawCircle, 0, 0, &threadID)) == NULL)
	{
		printf("�̴߳���ʧ��!");
	}

	//�ȴ������߳̽���
	WaitForMultipleObjects(2, hThread, TRUE, INFINITE);

	CloseHandle(hThread[0]);
	CloseHandle(hThread[1]);

	getchar();
	// �ر�ͼ��ģʽ
	closegraph();
	return 0;
}
