#include <pthread.h>
#include <stdio.h>

int count = 0;
pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;

struct thread_arg {
    int vezes;
};

typedef struct thread_arg thread_arg_t;

int work(int n);

void *thread_func(void *arg) {
    thread_arg_t *ctx = (thread_arg_t *) arg;

    for (int i = 0; i < ctx->vezes; i++) {
        pthread_mutex_lock(&mut);
        int id = count++;
        pthread_mutex_unlock(&mut);

        work(id);
    }

    pthread_exit(NULL);
}
