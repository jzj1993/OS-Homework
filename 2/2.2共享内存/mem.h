#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/shm.h>
#include <errno.h>

// 共享内存结构体
#define TEXT_SZ 128

#define MEM_W  0
#define MEM_R  1

struct mem_st
{
	int flag; // 标志，1：表示可读取，0表示可写入
	char text[TEXT_SZ]; // 保存写入和读取的文本
};

// 创建内存共享
int init(int id)
{
	int shmid; // 共享内存标识符
	// 创建共享内存
	shmid = shmget((key_t) id, sizeof(struct mem_st), 0666|IPC_CREAT);
	if(shmid == -1) {
		fprintf(stderr, "shmget failed\n");
		exit(EXIT_FAILURE);
	}
	return shmid;
}

// 连接到当前进程的地址空间
void* mat(int id)
{
	void *shm = NULL; // 分配的共享内存的原始首地址
	// 将共享内存连接到当前进程的地址空间
	shm = shmat(id, (void*)0, 0);
	if(shm == (void*) -1) {
		fprintf(stderr, "shmat failed\n");
		exit(EXIT_FAILURE);
	}
	return shm;
}

// 阻塞式写入
int send(struct mem_st* shared, void *buf)
{
	// 数据还没有被读取，则等待数据被读取,不能向共享内存中写入文本
	while(shared->flag == MEM_R) {
		usleep(10000);
		// printf("Waiting read finish...\n");
	}
	// 向共享内存中写入数据
	strncpy(shared->text, buf, TEXT_SZ);
	// 写完数据，设置flag使共享内存段可读
	shared->flag = MEM_R;
	return 0;
}

// 阻塞式读取
int rev(struct mem_st* shared, void *buf)
{
	// 有其他进程在写数据，不能读取数据
	while(shared->flag == MEM_W) {
		usleep(10000);
		// printf("Waiting read finish...\n");
	}
	// 没有进程向共享内存定数据有数据可读取
	strcpy(buf, shared->text);
	// sleep(rand() % 3);
	// 读取完数据，设置flag使共享内存段可写
	shared->flag = MEM_W;
	return 0;
}

// 分离
int release(struct mem_st* shared)
{
	//把共享内存从当前进程中分离
	int r = shmdt((void *) shared);
	if(r == -1) {
		fprintf(stderr, "shmdt failed\n");
		exit(EXIT_FAILURE);
	}
	return r;
}

// 删除
int del(int id)
{
	//删除共享内存
	int r = shmctl(id, IPC_RMID, 0);
	if(r == -1) {
		fprintf(stderr, "shmctl(IPC_RMID) failed\n");
		exit(EXIT_FAILURE);
	}
	return r;
}
