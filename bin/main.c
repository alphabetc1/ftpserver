#include "head.h"
#include "factory.h"
#include "work_que.h"

void* handle_request(void* arg);

int main(int argc,char* argv[])
{
	if(argc !=4)
	{
		printf("the args should be ./ELF IP PORT NPthread\n");
		exit(-1);
	}
	int npthread=atoi(argv[3]);
	factory_t fact;
	factory_init(&fact,handle_request,NULL,npthread,0,100);
	factory_start(&fact,npthread);
	int lisenfd;
	lisenfd=socket(AF_INET,SOCK_STREAM,0);
	if(-1==lisenfd)
	{
		perror("socket");
		exit(-1);
	}
	struct sockaddr_in ser_addr;
	bzero(&ser_addr,sizeof(struct sockaddr));
	ser_addr.sin_family=AF_INET;
	ser_addr.sin_addr.s_addr=inet_addr(argv[1]);
	ser_addr.sin_port=htons(atoi(argv[2]));
	int ret;
	ret=bind(lisenfd,(struct sockaddr*)&ser_addr,sizeof(struct sockaddr));
	if(-1==ret)
	{
		perror("bind");
		exit(-1);
	}
	listen(lisenfd,npthread);
	struct sockaddr_in client_addr;
	int len=sizeof(struct sockaddr);
	int new_sfd;
	pnode_t pnew;
	while(1)
	{
		bzero(&client_addr,sizeof(struct sockaddr));
		new_sfd=accept(lisenfd,(struct sockaddr *)&client_addr,&len);			
		pnew=(pnode_t)malloc(sizeof(node_t));
		bzero(pnew,sizeof(node_t));
		pnew->sockfd=new_sfd;
		pthread_mutex_lock(&(fact.s_que).q_mutex);
		que_set(&fact.s_que,pnew);
		pthread_mutex_unlock(&(fact.s_que).q_mutex);	
		pthread_cond_signal(&fact.cond);
	}		
}


void* handle_request(void* arg)
{
	pfactory_t pf=(pfactory_t)arg;
	pque_t pq=&pf->s_que;
	pnode_t pget;
	while(1)
	{
		pthread_mutex_lock(&pq->q_mutex);
		if(pq->size == 0)
		{
			pthread_cond_wait(&pf->cond,&pq->q_mutex);
		}
		que_get(pq,&pget);
		pthread_mutex_unlock(&pq->q_mutex);
		send_file(pget->sockfd);
		free(pget);		
	}
}
