/* 
 * put.c 
 * 
 *  Created on: May 14, 2012 
 *      Author: dell 
 */  
#include "signalmove.h"  
  
void put() {  
    int fd = open(filename_out, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);  
    if (fd == -1) {  
        printf("open file wrong!\n");  
        exit(0);  
    }  
    file_out(fd, data_t, len);  
}  