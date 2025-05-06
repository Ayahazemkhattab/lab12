#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define THREAD_NUM 4

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* routine(void* args) {
    pthread_mutex_lock(&mutex);
    sleep(1);
    printf("Hello from thread %d\n", *(int*)args);
    pthread_mutex_unlock(&mutex);
    free(args);
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t th[THREAD_NUM];
    int i;

    for (i = 0; i < THREAD_NUM; i++) {
        int* a = malloc(sizeof(int));
        *a = i;
        if (pthread_create(&th[i], NULL, &routine, a) != 0) {
            perror("Failed to create thread");
        }
    }

    for (i = 0; i < THREAD_NUM; i++) {
        if (pthread_join(th[i], NULL) != 0) {
            perror("Failed to join thread");
        }
    }

    pthread_mutex_destroy(&mutex);
    return 0;
}

