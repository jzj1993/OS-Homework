#include "mem.h"

int main()
{
	char buffer2[BUFSIZ];
	int id;
	struct mem_st *data2 = init(2345, &id);
	
	printf("disp: --------start--------\n");
	while(1) {
		// 接收消息
		rev(data2, buffer2);
        strcpy(buffer2, data2->text);
		// 显示
		printf("disp: %s", buffer2);
		// quit
		if(strncmp(buffer2, "quit", 3) == 0)
			break;
	}
	release(data2);
	del(id);
	printf("disp: --------stop--------\n");
	return 0;
}


