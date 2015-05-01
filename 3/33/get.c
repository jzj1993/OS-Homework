/* 
 * get.c 
 * 
 *  Created on: May 14, 2012 
 *      Author: dell 
 */  
#include "signalmove.h"  
  
void get() {  
    int fd = open(filename_in, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);  
    if (fd == -1) {  
        printf("open file wrong!\n");  
        exit(0);  
    }  
    file_in(fd, data_s, len);  
}  