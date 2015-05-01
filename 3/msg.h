#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/msg.h>
#include <errno.h>

// 消息结构体
struct msg_st
{
	long int msg_type;
	int d1;
	int d2;
	char s[BUFSIZ];
};
#define MSG_SIZE (sizeof(msg_st)-sizeof(long int))

// 创建消息
int msg_init(int id)
{
    int r = msgget((key_t) id, 0666 | IPC_CREAT);
	if(r == -1) {
		fprintf(stderr, "msgget failed: %d\n", errno);
		exit(EXIT_FAILURE);
	}
	return r;
}

// 发送消息
int msg_send(int id, void *buf)
{
	int r = msgsnd(id, buf, MSG_SIZE, 0);
	if(r == -1) {
		fprintf(stderr, "msgsnd failed\n");
		exit(EXIT_FAILURE);
	}
	return r;
}

// 读取消息
int msg_rev(int id, long int msgtype, void *buf)
{
	int r = msgrcv(id, buf, BUFSIZ, msgtype, 0);
	if(r == -1) {
		fprintf(stderr, "msgrcv failed: %d\n", errno);
		exit(EXIT_FAILURE);
	}
	return r;
}

// 删除消息
int msg_del(int id)
{
	int r = msgctl(id, IPC_RMID, 0);
	if(r == -1) {
		fprintf(stderr, "msgctl(IPC_RMID) failed\n");
		exit(EXIT_FAILURE);
	}
	return r;
}
