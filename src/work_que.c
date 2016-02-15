#include "head.h"
#include "work_que.h"

void que_init(pque_t pque,int cap)
{
	pque->head=NULL;
	pque->tail=NULL;
	pque->capacity=cap;
	pque->size=0;
	pthread_mutex_init(&pque->q_mutex,NULL);
}

void que_set(pque_t pque,pnode_t pnew)
{
	if(pque->head == NULL)
	{
		pque->head=pnew;
	}else{
		(pque->tail)->next=pnew;
	}
	pque->tail=pnew;
	pque->size++;
}	

void que_get(pque_t pque,pnode_t* pnew)
{
	*pnew=pque->head;
	pque->head = (pque->head)->next;
	if(pque->head ==NULL)
	{
		pque->tail=NULL;
	}
	pque->size--;
}		
