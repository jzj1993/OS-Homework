#include "msg.h"

int main()
{
	struct msg_st data;
	char buffer[BUFSIZ];
	int id = init(4567);
	
	printf("input: --------start--------\n");
	while(1) {
		// 输入数据
		printf("Enter some text: ");
		fgets(buffer, BUFSIZ, stdin);
		// 创建消息
		data.msg_type = 1;
		strcpy(data.text, buffer);
		// 发送消息
		send(id, (void*)&data);
		if(strncmp(buffer, "quit", 4) == 0)
			break;
		sleep(1);
	}
	printf("receive: --------stop--------\n");
	return 0;
}
