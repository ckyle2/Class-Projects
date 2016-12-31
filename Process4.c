
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
    char *sharing, *s1, *s2, *s3;

  
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

    for (s1 = sharing; *s1 != '-'; s1++)
        putchar(*s1);
    putchar(' ');
    *sharing = 'a';
    while (*sharing != 't')
	sleep(1);

    for (s2 = sharing; *s2 != '-'; s2++)
	putchar(*s2);
    putchar(' ');
    *sharing = 'r';
    
    while (*sharing != 'h')
	sleep(1);

    for (s3 = sharing; *s3 != '-'; s3++)
	putchar(*s3);
    putchar('\n');


   *sharing = '*';
   
    return 0;
}
