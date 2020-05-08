#include<iostream>
#include<cstdlib>
#include<ctime>
#include<windows.h>
using namespace std;

//��������С��Ϊ10
const int BUFFER_SIZE = 10;
int buffer[BUFFER_SIZE];
int front, rear;
bool full;
HANDLE Mutex;
HANDLE Full;
HANDLE Empty;

void showBuffer() {
    cout << "������: ";
    if (front != rear || full) {
        int i = front;
        do {
            cout << buffer[i] << " ";
            i = (i + 1) % BUFFER_SIZE;
        } while (i != rear);
    }
    else
        cout << "����";
    cout << "\n==============================" << endl;
}

int insert_item(int item) {
    int condition = -1;
    WaitForSingleObject(Empty, INFINITE);
    WaitForSingleObject(Mutex, INFINITE);//����
    //���������û��
    if (!full) {
        buffer[rear] = item;
        rear = (rear + 1) % BUFFER_SIZE;
        //�ղŲ嵽���һλ�Ŀ�λ��˵���������Ѿ�����
        if (rear == front)full = true;
        condition = 0;
        cout << "������������ " << item << endl;
        showBuffer();
    }

    ReleaseMutex(Mutex);//����
    ReleaseSemaphore(Full, 1, NULL);
    return condition;
}

int remove_item(int item) {
    int condition = -1;
    WaitForSingleObject(Full, INFINITE); //����ź�����һ��ռ��Ȩ 
    WaitForSingleObject(Mutex, INFINITE);//���� 
    //�������ﲻ�ǿյģ���Ϊ������˵Ļ�front�����rear�����Զ�һ���ж��ǲ������ģ�
    if (front != rear || full) {
        item = buffer[front];
        front = (front + 1) % BUFFER_SIZE;
        full = false;
        condition = 0;

        cout << "������������" << item << endl;
        showBuffer();
    }
    ReleaseMutex(Mutex); //���� 
    ReleaseSemaphore(Empty, 1, NULL); // �ͷ��ź�����һ��ռ��Ȩ 
    return condition;
}
//������
DWORD WINAPI producer(void* param) {
    srand((unsigned)time(0));

    for (int i = 0;; ++i) {
        Sleep((rand() % 50) + 2000);
        insert_item(rand() % BUFFER_SIZE);
    }
};
//������
DWORD WINAPI consumer(void* param) {
    srand((unsigned)time(0));
    for (int j = 0;; j++) {
        Sleep((rand() % 100) + 2500);
        remove_item(rand() % BUFFER_SIZE);
    }
};
/*
int main(int argc, char* argv[]) {
    front = 0;
    rear = 0;
    full = false;

    Mutex = CreateMutex(NULL, FALSE, NULL);
    Full = CreateSemaphore(NULL, 0, 5, NULL); //����һ���ź��� 
    Empty = CreateSemaphore(NULL, 5, 5, NULL);
    CreateThread(NULL, 0, producer, NULL, 0, NULL);
    CreateThread(NULL, 0, consumer, NULL, 0, NULL);

    Sleep(400000);
    return 0;
}*/