#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

#define PHILOSOPHER_COUNT 5
#define THINKING 2
#define HUNGRY 1
#define EATING 0
#define LEFT (philosopherNumber + 4) % PHILOSOPHER_COUNT
#define RIGHT (philosopherNumber + 1) % PHILOSOPHER_COUNT

int state[PHILOSOPHER_COUNT];
int philosophers[PHILOSOPHER_COUNT] = {0, 1, 2, 3, 4};

sem_t mutex;
sem_t S[PHILOSOPHER_COUNT];

void test(int philosopherNumber) {
    if (state[philosopherNumber] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING) {
        state[philosopherNumber] = EATING;
        sleep(2);
        printf("Philosopher %d takes chopstick %d and %d\n", philosopherNumber + 1, LEFT + 1, philosopherNumber + 1);
        printf("Philosopher %d is Eating\n", philosopherNumber + 1);
        sem_post(&S[philosopherNumber]);
    }
}

void takeChopstick(int philosopherNumber) {
    sem_wait(&mutex);
    state[philosopherNumber] = HUNGRY;
    printf("Philosopher %d is Hungry\n", philosopherNumber + 1);
    // Try to eat if neighbours are not eating
    test(philosopherNumber);
    sem_post(&mutex);
    // Wait if unable to eat
    sem_wait(&S[philosopherNumber]);
    sleep(1);
}

void putChopstick(int philosopherNumber) {
    sem_wait(&mutex);
    state[philosopherNumber] = THINKING;
    printf("Philosopher %d putting chopstick %d and %d down\n", philosopherNumber + 1, LEFT + 1, philosopherNumber + 1);
    printf("Philosopher %d is thinking\n", philosopherNumber + 1);
    test(LEFT);
    test(RIGHT);
    sem_post(&mutex);
}

void* philosopher(void* num) {
    while (1) {
        int* i = num;
        sleep(1);
        takeChopstick(*i);
        sleep(0);
        putChopstick(*i);
    }
}

int main() {
    int i;
    pthread_t thread_id[PHILOSOPHER_COUNT];

    sem_init(&mutex, 0, 1);

    for (i = 0; i < PHILOSOPHER_COUNT; i++)
        sem_init(&S[i], 0, 0);

    for (i = 0; i < PHILOSOPHER_COUNT; i++) {
        pthread_create(&thread_id[i], NULL, philosopher, &philosophers[i]);
        printf("Philosopher %d is thinking\n", i + 1);
    }

    for (i = 0; i < PHILOSOPHER_COUNT; i++)
        pthread_join(thread_id[i], NULL);
}
