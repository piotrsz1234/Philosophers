#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdbool.h>

typedef struct JobParams_m {
    pthread_mutex_t* mutexes;
    int index;
    bool asymmetric;
} JobParams;

void Job(JobParams* params) {
    int leftFork = params->index;
    int rightFork = (params->index == 4) ? 0: params->index + 1;
    printf("\n\nTest\n\n");
    while(true) {
        printf("Philosopher nr: %d tries to pick %s fork\n", params->index, (params->asymmetric) ? "right" : "left");
        pthread_mutex_lock(&params->mutexes[(params->asymmetric) ? rightFork : leftFork]);
        printf("Philosopher nr: %d picked %s fork\n", params->index, (params->asymmetric) ? "right" : "left");
        usleep(100);
        printf("Philosopher nr: %d tries to pick %s fork\n", params->index, (!params->asymmetric) ? "right" : "left");
        pthread_mutex_lock(&params->mutexes[(!params->asymmetric) ? rightFork : leftFork]);
        printf("Philosopher nr: %d picked %s fork\n", params->index, (!params->asymmetric) ? "right" : "left");
        usleep(100);
        printf("Philosopher nr: %d returns %s fork\n", params->index, (params->asymmetric) ? "right" : "left");
        pthread_mutex_unlock(&params->mutexes[(params->asymmetric) ? rightFork : leftFork]);
        usleep(100);
        printf("Philosopher nr: %d returns %s fork\n", params->index, (!params->asymmetric) ? "right" : "left");
        pthread_mutex_unlock(&params->mutexes[(!params->asymmetric) ? rightFork : leftFork]);
        printf("Philosopher nr: %d thinks...\n", params->index);
        usleep(100);
    }
}

int main(int argc, char** argv) {
    pthread_mutex_t mutexes[5];
    for(int i=0;i<5;i++) {
        pthread_mutex_init(mutexes + i, NULL);
    }
    JobParams params[5];
    pthread_t threads[5];
    for(int i=0;i<5;i++) {
        params[i].asymmetric = (i==0 && argc > 1);
        params[i].index = i;
        params[i].mutexes = mutexes;
        pthread_create(threads + i, NULL, Job, params + i);
    }

    for(int i=0;i<5;i++) pthread_join(threads[i], NULL);
    return 0;
}