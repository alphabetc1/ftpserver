#include "head.h"
#include "factory.h"
#include "work_que.h"

void factory_init(pfactory_t parr,pfunc pfunc_con,pfunc pfunc_pro,int con_num,int pro_num,int capacity)
{
	que_init(&parr->s_que,capacity);
	parr->pfunc_con=pfunc_con;
	parr->pfunc_pro=NULL;
	pthread_cond_init(&parr->cond,NULL);
	parr->pth_con=(pthread_t *)calloc(con_num,sizeof(pthread_t));
	parr->pth_pro=NULL;
	parr->flag=0;
}

void factory_start(pfactory_t parr,int nthread)
{
	if(parr->flag==1)
	{
		return;
	}
	parr->flag=1;
	int i;
	int ret;
	for(i=0;i<nthread;i++)
	{
		ret=pthread_create(&parr->pth_con[i],NULL,parr->pfunc_con,(void*)parr);
		if(ret!=0)
		{
			printf("the pthread_create error is %d\n",ret);
			exit(-1);
		}
	}
}
