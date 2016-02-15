#ifndef _MSG_H_
#define _MSG_H_

#define MAX_DATA 1000
#define FILE_NAME "main.c"
typedef struct file_buf{
    int len;
    char buf[MAX_DATA];
}file_t,*pfile_t;

#endif
