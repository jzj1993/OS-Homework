/* 
 * file.c 
 * 
 *  Created on: May 14, 2012 
 *      Author:dell 
 *  file works 
 */  
#include "signalmove.h"  
  
void file_in(int fd, char *data, int len) {  
    while (1) {  
        sem_wait(&read_sem);  
        pthread_mutex_lock(&read_mutex);  
        printf("data_in..........\n");  
        if (lseek(fd, 0, SEEK_CUR) == -1) {  
            printf("lseek failed!\n");  
        }  
        if ((result = read(fd, data, len)) == -1) {  
            printf("read error! \n");  
        }  
        int i=0,j=0;  
        printf("data_in..........complete\n");  
        pthread_mutex_unlock(&read_mutex);  
        sem_post(?_sem);  
        if(result<len){  
            len=result;  
            result=0;  
            break;  
        }  
    }  
}  
void file_out(int fd, char *data, int len) {  
    while (1) {  
        sem_wait(&write_sem);  
        pthread_mutex_lock(&write_mutex);  
        printf("data_out..........\n");  
        if (write(fd, data, len) == -1) {  
            printf("write error! \n");  
        }  
        printf("data_out..........complete\n");  
        pthread_mutex_unlock(&write_mutex);  
        if(result_copy==1){  
            break;  
        }  
    }  
}  