// Date: 06/09/2016
// CS 17L2 NETWORKS AND OPERATING SYSTEMS LABORATORY
// Cycle 2 : Exp 9 - INTERPROCESS COMMUNICATION USING POSIX SHARED MEMORY
/* Server Program. Creates a shared memory region. Increments the values of the two
variables at an interval of 3 seconds and writes them to the shared memory space. */
// ADARSH P.K. CSU13203

#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <signal.h>

struct shared_data {
    int var1;
    int var2;
};

int main() {
    int shmfd;
    int vol, cur;
    int shared_seg_size = sizeof(struct shared_data);
    struct shared_data *shared_msg;

    shmfd = shm_open("/shm", O_CREAT | O_RDWR, S_IRWXU);
    if (shmfd < 0)
    {
        perror("In shm_open()");
        exit(1);
    }
    fprintf(stderr, "Created shared memory object %s\n", "/shm");
    ftruncate(shmfd, shared_seg_size);
    shared_msg = (struct shared_data *)mmap(NULL, shared_seg_size, PROT_READ | PROT_WRITE, MAP_SHARED, shmfd, 0);
    if (shared_msg == NULL)
    {
        perror("In mmap()");
        exit(1);
    }
    fprintf(stderr, "Shared memory segment allocated correctly (%d bytes).\n", shared_seg_size);

    vol = 10;
    cur = 0;
    while(1)
    {
    shared_msg->var1 = vol;
    shared_msg->var2 = cur;
    sleep(3);
    vol++;
    cur++;
    }

    if (shm_unlink("/shm") != 0) {
        perror("In shm_unlink()");
        exit(1);
    }

    return 0;
}
