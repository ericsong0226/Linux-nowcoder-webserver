/* ************************************************************************
> File Name:     write_shm.c
> Author:        程序员Eric
> 微信公众号:    源水本木
> Created Time:  Sun 08 Jan 2023 04:05:16 PM CST
> Description:   
 ************************************************************************/
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

int main() {

    int shmid = shmget(100, 4096, IPC_CREAT | 0664);
    printf("shmid : %d\n", shmid);

    void * ptr = shmat(shmid, NULL, 0);

    char * str = "helloworld";

    memcpy(ptr, str, strlen(str) + 1);

    printf("any key continue\n");
    getchar();

    shmdt(ptr);

    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}
