#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <semaphore.h>

#define SEMAPHORE_NAME "/bhavith"

void printsem(sem_t* sem)
{
    int value;
    if (sem_getvalue(sem, &value) < 0) {
        printf("Failed to get value from semaphore \n");
    }
    printf("value: %d\n", value);
}

void increment(sem_t* sem) 
{
    if (sem_post(sem) == 0) {
        printf("Incremented semaphore \n");
    } else {
        printf("Failed to increment semaphore: %s\n", strerror(errno));
    }
}

void decrement(sem_t* sem)
{
    if (sem_wait(sem) == 0) {
        printf("Decrement semaphore \n");
    } else {
        printf("Failed to decrement semaphore: %s\n", strerror(errno));
    }
}


int main()
{
    // open semaphore
    sem_t* sem = sem_open(SEMAPHORE_NAME, O_RDWR | O_CREAT, 0666, 2);
    if (sem == SEM_FAILED) {
        printf("Failed to open semaphore: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    int iter = 0;

    for (iter = 0; iter < 5; iter++) {
        increment(sem);
        printsem(sem);
    }

    printf("-------------------\n");

    for (iter = 0; iter < 6; iter++) {
        decrement(sem);
        printsem(sem);
    }

    // close semaphore
    if (sem_close(sem) < 0) {
        printf("Failed to close semaphore\n");
        exit(EXIT_FAILURE);
    }

    if (sem_unlink(SEMAPHORE_NAME) < 0) {
        printf("Failed to unlink semaphore: %s\n", SEMAPHORE_NAME);
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}