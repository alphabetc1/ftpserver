#include "head.h"
#include "msg.h"

void send_file(int sfd)
{
	file_t dbuf;
	int ret;
	bzero(&dbuf,sizeof(dbuf));
	strcpy(dbuf.buf,FILE_NAME);
	dbuf.len=strlen(dbuf.buf);
	ret=send(sfd,(void*)&dbuf,4+dbuf.len,MSG_CONFIRM);
	if(-1==ret)
	{
		perror("send_file_name");
		exit(-1);
	}
	int fd;
	fd=open(FILE_NAME,O_RDONLY);
	if(-1==fd)
	{
		perror("open");
		exit(-1);
	}
	while(bzero(&dbuf,sizeof(dbuf)),(dbuf.len=read(fd,dbuf.buf,sizeof(dbuf.buf)))>0)
	{
		printf("the dbuf.len is %d\n",dbuf.len);
		ret=send_n(sfd,(char*)&dbuf,4+dbuf.len);
		if(-1==ret)
		{
			perror("send_file_data");
			exit(-1);
		}
	}
	int flag=0;//发送结束标志给客户端
	ret=send(sfd,(void*)&flag,sizeof(int),MSG_CONFIRM);
	close(sfd);
}
