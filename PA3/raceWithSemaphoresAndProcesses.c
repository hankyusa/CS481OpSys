/*=========================================================*/
/* raceWithSemaphoresAndProcesses.c                        */
/*=========================================================*/
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

sem_t* shared_mutex;

struct {
  int balance[2];
} * Bank;  // global variable defined

void* MakeTransactions() {  // routine for thread execution
  int i, j, tmp1, tmp2, rint;
  double dummy;
  for (i = 0; i < 100; i++) {
    rint = (rand() % 30) - 15;
    sem_wait(shared_mutex);
    if (((tmp1 = Bank->balance[0]) + rint) >= 0 &&
        ((tmp2 = Bank->balance[1]) - rint) >= 0) {
      Bank->balance[0] = tmp1 + rint;
      for (j = 0; j < rint * 1000; j++) {
        dummy = 2.345 * 8.765 / 1.234;
      }  // spend time on purpose
      Bank->balance[1] = tmp2 - rint;
    }
    sem_post(shared_mutex);
  }
  return NULL;
}

int main(int argc, char** argv) {
  int i, shmid_bank, shmid_mutex;
  void* voidptr = NULL;
  pthread_t tid[2];
  srand(getpid());

  shmid_mutex = shmget(5678, sizeof(sem_t), IPC_CREAT | 0666);
  if (shmid_mutex == -1) {
    perror("Error in getting shared memory segment\n");
    return 1;
  }
  shared_mutex = shmat(shmid_mutex, NULL, 0);
  if (shared_mutex == (void*)-1) {
    perror("Error in shared memory attach");
    return 1;
  }
  sem_init(shared_mutex, 0, 1);

  if ((shmid_bank = shmget(1234, 4, IPC_CREAT | 0666)) == -1) {
    perror("Error in getting shared memory segment\n");
    return 1;
  }
  Bank = shmat(shmid_bank, NULL, 0);
  if (Bank == (void*)-1) {
    perror("Error in shared memory attach");
    return 1;
  }
  Bank->balance[0] = 100;
  Bank->balance[1] = 100;
  printf("Init balances A:%d + B:%d ==> %d!\n", Bank->balance[0],
         Bank->balance[1], Bank->balance[0] + Bank->balance[1]);
  if (fork() == -1) {
    // Error
    perror("Error in forking\n");
    return (1);
  } else {
    MakeTransactions();
  }
  printf("Let's check the balances A:%d + B:%d ==> %d ?= 200\n",
         Bank->balance[0], Bank->balance[1],
         Bank->balance[0] + Bank->balance[1]);
  if (shmdt(Bank) == -1) {
    perror("Error in shared memory detach");
    return 1;
  }
  sem_destroy(&shared_mutex);
  return 0;
}
