#ifndef _WORK_QUE_H_
#define _WORK_QUE_H_

typedef struct sfnode{
	int sockfd;
	struct sfnode *next;
}node_t,*pnode_t;


typedef struct work_que{
	pnode_t head,tail;
	int capacity;
	int size;
	pthread_mutex_t q_mutex;
}que_t,*pque_t;

void que_init(pque_t pque,int);
void que_set(pque_t pque,pnode_t pnew);
void que_get(pque_t pque,pnode_t* pnew);
#endif
