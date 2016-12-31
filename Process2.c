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
    if ((shmem = shmget(key, size, 0666)) < 0){
        perror("getting shared failed");
        return 1;
    }

    //attach to memory segment
    if ((sharing = shmat(shmem, NULL, 0)) == (char *) -1) 
    {
        perror("failed");
        return 1;
    }

   //wait for proc1 to write to shared memory segment
    while(*sharing != 'a')
	sleep(1);
   //write to shared memory
    s = sharing;
    char text[6] = {'t', 'h', 'e','r','e'};
    int i = 0;
    for (i = 0; i < 6; i++)
        *s++ = (int)text[i];
    *s++ = '-';
    *sharing = 't';
   
    return 0;
}
