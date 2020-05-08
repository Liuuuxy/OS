// ConsoleApplication1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include<stdio.h>
#include<Windows.h>
#include<math.h>

//定义画方的线程
DWORD WINAPI print1(LPVOID n)
{
	int m = (int)n;
	for (int i = m; i <= 1000; i++)
	{
		printf("A:%d\n", i);
		Sleep(500);
	}
	return 0;
}

//定义画圆的函数
DWORD WINAPI print2(LPVOID n)
{
	int m = (int)n;
	for (int i = m; i > 0; i--)
	{
		printf("B:%d\n", i);
		Sleep(500);
	}
	return 0;
}
/*
int main()
{
	HANDLE hThread[2];//记录新线程句柄
	DWORD threadID;//记录线程ID
	if ((hThread[0] = CreateThread(NULL, 0, print1, (LPVOID)1, 0, &threadID)) == NULL)
	{
		printf("线程创建失败!");
	}
	if ((hThread[1] = CreateThread(NULL, 0, print2, (LPVOID)1000, 0, &threadID)) == NULL)
	{
		printf("线程创建失败!");
	}

	//等待所有线程结束
	WaitForMultipleObjects(2, hThread, TRUE, INFINITE);

	CloseHandle(hThread[0]);
	CloseHandle(hThread[1]);

	return 0;
}
*/

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
