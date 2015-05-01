/* 
 * main.c 
 * 
 *  Created on: May 14, 2012 
 *      Author: dell 
 */  
#include "signalmove.h"  
  
int isdigit_all(char *str)  
{  
    while (*str != '\0')  
    {  
        if (!isdigit(*str++))  
            return 0;  
    }  
    return 1;  
}  
  
//signal out  
void Handlesignal(int signo) {  
    printf("end program!\n", signo);  
    exit(0);  
}  
  
void main(int argc, char* argv[]) {  
    if(argc!=4){  
        printf("error input! 1.filename_in,2.filename_out,3,length of buffer\n");  
        exit(0);  
    }  
    if(isdigit_all(argv[3])==0){  
        printf("error input! 1.filename_in,2.filename_out,3,length of buffer\n");  
        printf("error length of buffer must be digit!\n");  
        exit(0);  
    }  
    result_copy = 0;  
    filename_in=argv[1];  
    filename_out=argv[2];  
    len=atoi(argv[3]);  
    int thread_i = 0;  
    data_s = (char *) malloc(len * sizeof(char));  
    data_t = (char *) malloc(len * sizeof(char));  
  
    if (signal(SIGINT, Handlesignal) == SIG_ERR) {   
        printf("error signal out\n");  
    }  
    pthread_t read_pthread;  
    pthread_t copy_pthread;  
    pthread_t write_pthread;  
  
    //sem lock  
    int ini1 = sem_init(&read_sem, 0, 1);  
    int ini2 = sem_init(&write_sem, 0, 0);  
    int ini5 = sem_init(?_sem, 0, 0);  
    if (ini1 && ini2 && ini5 != 0) {  
        printf("sem error\n");  
        exit(1);  
    }  
    //mutex lock  
    int ini3 = pthread_mutex_init(&read_mutex, NULL);  
    int ini4 = pthread_mutex_init(&write_mutex, NULL);  
    if (ini3 && ini4 != 0) {  
        printf("mutex error\ n");  
        exit(1);  
    }  
    int thread_1 = pthread_create(&read_pthread, NULL, (void *)&get,  
            (void *) (&thread_i));  
    if (thread_1 != 0) {  
        printf("read thread create error!\n");  
        exit(1);  
    }  
    thread_i++;  
    int thread_2 = pthread_create(?_pthread, NULL, (void *)?,  
            (void *) (&thread_i));  
    if (thread_2 != 0) {  
        printf("copy thread create error!\n");  
        exit(1);  
    }  
    thread_i++;  
    int thread_3 = pthread_create(&write_pthread, NULL, (void *)&put,  
            (void *) (&thread_i));  
    if (thread_3 != 0) {  
        printf("write thread create error!\n");  
        exit(1);  
    }  
    pthread_join(read_pthread, NULL);  
    pthread_join(copy_pthread, NULL);  
    pthread_join(write_pthread, NULL);  
    free(data_s);  
    free(data_t);  
    exit(0);  
}  