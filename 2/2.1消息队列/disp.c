#include "msg.h"

int main()
{
	struct msg_st data;
	char buffer[BUFSIZ];
	int id = init(4567);
	
	printf("disp: --------start--------\n");
	while(1) {
		// 接收消息
		rev(id, 2, (void*)&data);
        strcpy(buffer, data.text);
		// 显示
		printf("disp: %s", buffer);
		// quit
		if(strncmp(buffer, "quit", 3) == 0)
			break;
	}
	del(id);
	printf("disp: --------stop--------\n");
	return 0;
}


