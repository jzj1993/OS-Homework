#include "msg.h"

int main()
{
	struct msg_st data;
	char buffer[BUFSIZ]; char *p;
	int id = init(4567);
	
	printf("data: --------start--------\n");
	while(1) {
		// 接收消息
        rev(id, 1, (void*)&data);
        strcpy(buffer, data.text);
		// test
        printf("data: %s\n", buffer);
		// quit
		if(strncmp(buffer, "quit", 3) == 0) {
			data.msg_type = 2; // 如果是quit指令,直接转发给显示进程
			send(id, (void *)&data);
			break;
		}
		// 分类
		p = buffer;
		while(*p) {
			if(*p >= '0' && *p <= '9') {
				sprintf(data.text, "get num: %c\n", *p);
			} else if((*p >= 'a' && *p <= 'z') || (*p >= 'A' && *p <= 'Z')) {
				sprintf(data.text, "get letter: %c\n", *p);
			} else {
				sprintf(data.text, "throw char: %c\n", *p);
			}
			//printf("data _ sendmsg: %s", data.text);
			data.msg_type = 2;
			send(id, (void *)&data);
			usleep(10000);
			++p;
		}
	}
	printf("data: --------stop--------\n");
	return 0;
}
