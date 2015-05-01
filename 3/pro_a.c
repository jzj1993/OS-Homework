#include "mem.h"
#include "msg.h"
#include <pthread.h>
#include <semaphore.h>

sem_t sem;

void *thread(void *tid)
{
	while(1) {
		sem_wait(&sem);
		size_t fread ( void *buffer, size_t size, size_t count, FILE *stream);
		sem_post(&sem);
        usleep(10000);
	}
}

int main()
{
	char buffer[BUFSIZ];
	FILE *fin = NULL;
	FILE *fout = NULL;
	struct msg_st msg;
	int msgid;
	int buf_size_s, buf_size_t;
	struct mem_st *buf_s = init(1234, 0);
	
	msgid = msg_init(1234);
	
	printf("a: --------start--------\n");
	
	// input file
	while(fin == NULL) {
		printf("Enter input file: ");
		scanf("%s", &buffer);
		// fgets(buffer, BUFSIZ, stdin); //
		fin = fopen(buffer, "r");
	}
	
	// output file
	while(fout == NULL) {
		printf("Enter output file: ");
		scanf("%s", &buffer);
		// fgets(buffer, BUFSIZ, stdin); //
		fout = fopen(buffer, "w");
		if(fout != NULL) {
			fclose(fout);
			strcpy(msg.s, buffer);
			break;
		}
	}
	
	// buf size of S and T
	printf("Enter buf size of S and T: ");
	scanf("%d%d", &buf_size_s, &buf_size_t);
	
	msg.d1 = buf_size_s;
	msg.d2 = buf_size_t;
	
	msg.msg_type = 1;
	msg_send(id, (void*)&msg); // 用消息发送信息
	msg.msg_type = 2;
	msg_send(id, (void*)&msg); // 用消息发送信息
	
	
	sem_init(&s1, 0, 1);
	pthread_create(&t1, NULL, thread1, (void *)t);
	pthread_create(&t2, NULL, thread2, (void *)t);

	
	while(1) {
		printf("Enter input file: ");
		fgets(buffer, BUFSIZ, stdin);
		// 发送消息
		send(buf_s, buffer);
		if(strncmp(buffer, "quit", 4) == 0)
			break;
		sleep(1);
	}
	release(buf_s);
	fclose(fin);
	printf("a: --------stop--------\n");
	return 0;
}
