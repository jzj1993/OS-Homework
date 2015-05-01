/* 
 * signalmove.h 
 * 
 *  Created on: May 14, 2012 
 *      Author: dell 
 */  
  
#ifndef SIGNALMOVE_H_  
#define SIGNALMOVE_H_  
  
#include <stdio.h>  
#include <stdlib.h>  
#include <unistd.h>  
#include <pthread.h>  
#include <semaphore.h>  
#include <signal.h>  
#include <fcntl.h>  
#include <string.h>  
#include <ctype.h>  
  
//file works  
void file_in();  
void file_out();  
//copy from s to t  
void copy();  
//put and get  
void put();  
void get();  
  
sem_t read_sem; // read  
sem_t write_sem; // write  
sem_t copy_sem; // copy  
  
pthread_mutex_t read_mutex; // pthread mutex for read  
pthread_mutex_t write_mutex; // pthread mutex for write  
  
char *data_s; //read buffer  
char *data_t; //write buffer  
int len; //buffer length  
  
char *filename_out; //name_out  
char *filename_in; //name_in  
  
int result;  
int result_copy;  
  
#endif /* SIGNALMOVE_H_ */  