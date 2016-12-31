#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>

#define size     15

int main()
{
    char c;
    int shmem;
    key_t key;
    char *sharing, *s;

  
    key = 5678;
	//create shared memory segment
    if ((shmem = shmget(key, size, IPC_CREAT | 0666)) < 0)
    {
        perror("getting shared failed");
        return 1;
    }

    //attach to memory segment
    if ((sharing = shmat(shmem, NULL, 0)) == (char *) -1) 
    {
        perror("failed");
        return 1;
    }

   //write to shared memory
    s = sharing;
    char text[6] = {'H', 'e', 'l','l','o'};
    int i = 0;
    for (i = 0; i < 5; i++)
        *s++ = (int)text[i];
    *s++ = '-';
   //wait for proc4 to read
    while (*sharing != '*') 
       		 sleep(1);
   
    return 0;
}
