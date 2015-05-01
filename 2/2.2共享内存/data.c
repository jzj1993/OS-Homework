#include "mem.h"

int main()
{
	char buffer[BUFSIZ]; char *p;
	char buffer2[BUFSIZ];
	int id;
	struct mem_st *data, *data2;
	data = init(1234, &id);
	data2 = init(2345, 0);
	
	printf("data: --------start--------\n");
	while(1) {
		// 接收消息
        rev(data, buffer);
		// test
        printf("data: %s\n", buffer);
		// quit
		if(strncmp(buffer, "quit", 3) == 0) { // 如果是quit指令,直接转发给显示进程
			send(data2, buffer);
			break;
		}
		// 分类
		p = buffer;
		while(*p) {
			if(*p >= '0' && *p <= '9') {
				sprintf(buffer2, "get num: %c\n", *p);
			} else if((*p >= 'a' && *p <= 'z') || (*p >= 'A' && *p <= 'Z')) {
				sprintf(buffer2, "get letter: %c\n", *p);
			} else {
				sprintf(buffer2, "throw char: %c\n", *p);
			}
			send(data2, buffer2);
			usleep(10000);
			++p;
		}
	}
	release(data);
	release(data2);
	del(id);
	printf("data: --------stop--------\n");
	return 0;
}
