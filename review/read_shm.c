/* ************************************************************************
> File Name:     read_shm.c
> Author:        程序员Eric
> 微信公众号:    源水本木
> Created Time:  Sun 08 Jan 2023 04:00:40 PM CST
> Description:   
 ************************************************************************/
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

int main() {

    int shmid = shmget(100, 0, IPC_CREAT);
    printf("shmid : %d\n", shmid);

    void * ptr = shmat(shmid, NULL, 0);

    printf("%s\n", (char *)ptr);

    printf("any key continue\n");
    getchar();

    shmdt(ptr);

    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}
