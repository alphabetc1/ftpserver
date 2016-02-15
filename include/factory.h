#ifndef _FACTORY_H_
#define _FACTORY_H_
#include "work_que.h"

typedef void* (*pfunc)(void *);

typedef struct factory{
	que_t s_que;
	pfunc pfunc_con;
	pfunc pfunc_pro;
	pthread_cond_t cond;
	pthread_t *pth_con;
	pthread_t *pth_pro;
	int flag; 
}factory_t,*pfactory_t;

void factory_init(pfactory_t parr,pfunc pfunc_con,pfunc pfunc_pro,int con_num,int pro_num,int capacity);

void factory_start(pfactory_t parr,int nthread);
#endif
