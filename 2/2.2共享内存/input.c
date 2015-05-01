#include "mem.h"

int main()
{
	char buffer[BUFSIZ];
	struct mem_st *data = init(1234, 0);
	
	printf("input: --------start--------\n");
	while(1) {
		// 输入数据
		printf("Enter some text: ");
		fgets(buffer, BUFSIZ, stdin);
		// 发送消息
		send(data, buffer);
		if(strncmp(buffer, "quit", 4) == 0)
			break;
		sleep(1);
	}
	release(data);
	printf("receive: --------stop--------\n");
	return 0;
}
