# Programming Assignment 03

by Luke Hanks

## Question 1

>Compile then run the above code for 10-20 times. Write a paragraph to explain.

`void* MakeTransactions()` makes 100 random transactions under $15 between accounts A and B. The sum of the account balances should not change. But they do change. To understand why consider the following possible (and likely given that dummy for-loop) order of value assignments.

```c
//          Thread 0                       Thread 1
Bank.balance[0] = tmp1 + rint
                                        tmp1 = Bank.balance[0]
                                        tmp2 = Bank.balance[1]
                                        Bank.balance[0] = tmp1 + rint
Bank.balance[1] = tmp2 - rint
                                        Bank.balance[1] = tmp2 - rint
```

Thread 1's `temp1` value would reflect Thread 0's partially completed transaction, but Thread 1's `temp2` value would would not. This will result in Thread 0's effect on `Bank.balance[1]` being undone, but not Thread 0's  effect on `Bank.balance[0]`. Money will appear to vanish and materialize at random.

## Question 2

>Use thread library calls (mutex lock and unlock) to modify the code in Q1) to remove any potential race conditions. Show your modification of the code and explain the outcome with your modification.

```c
/*=========================================================*/
/* raceWithMutex.c                                         */
/*=========================================================*/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t shared_mutex; //                              <-- MODIFICATION

struct {int balance[2];} Bank = {{100, 100}};

void* MakeTransactions() {  // routine for thread execution
  int i, j, tmp1, tmp2, rint;
  double dummy;
  for (i = 0; i < 100; i++) {
    rint = (rand() % 30) - 15;
    pthread_mutex_lock(&shared_mutex); //                     <-- MODIFICATION
    if (((tmp1 = Bank.balance[0]) + rint) >= 0 &&
        ((tmp2 = Bank.balance[1]) - rint) >= 0) {
      Bank.balance[0] = tmp1 + rint;
      for (j = 0; j < rint * 1000; j++) {
        dummy = 2.345 * 8.765 / 1.234;
      }  // spend time on purpose
      Bank.balance[1] = tmp2 - rint;
    }
    pthread_mutex_unlock(&shared_mutex); //                   <-- MODIFICATION
  }
  return NULL;
}

int main(int argc, char** argv) {
  int i;
  void* voidptr = NULL;
  pthread_t tid[2];
  srand(getpid());
  pthread_mutex_init(&shared_mutex, NULL); //                 <-- MODIFICATION
  printf("Init balances A:%d + B:%d ==> %d!\n", Bank.balance[0],
         Bank.balance[1], Bank.balance[0] + Bank.balance[1]);
  for (i = 0; i < 2; i++) {
    if (pthread_create(&tid[i], NULL, MakeTransactions, NULL)) {
      perror("Error in thread creating\n");
      return (1);
    }
  }
  for (i = 0; i < 2; i++) {
    if (pthread_join(tid[i], (void*)&voidptr)) {
      perror("Error in thread joining\n");
      return (1);
    }
  }
  printf("Let's check the balances A:%d + B:%d ==> %d ?= 200\n",
         Bank.balance[0], Bank.balance[1], Bank.balance[0] + Bank.balance[1]);
  return 0;
}
```

The above code always maintains a consistent sum of account balances.

`shared_mutex` is a static variable so all the threads share it. The first thread to call `pthread_mutex_lock(&shared_mutex)` locks `shared_mutex` and executes its transaction. While that transaction is happening, the second thread to call `pthread_mutex_lock(&shared_mutex)` waits for `shared_mutex` to be unlocked. After the first thread finishes its transaction, it calls `pthread_mutex_unlock(&shared_mutex)` which unlocks `shared_mutex`. The second thread which has been waiting immediately locks `shared_mutex` and does its transaction.

## Question 3

>Rewrite your code in Q1) replacing threads by processes.
>
>- Instead of creating two threads to call “MakeTransactions”, you will use fork() to create a child process. Both parent and child processes will call procedure “MakeTransactions”.
>- Since two processes will not share a common address space, you will need to rewrite code to allocate “Bank” as a shared variable (by applying shared memory IPC, see Slide M02c).
>- Other parts (i.e., set up initial values, print the initial values and balance, and print the ending values and balance) stay the same.
>
>Show your implementation code in the written report, compile then run your new process-based code for 10-20 times. Write a paragraph to explain if the race condition still exists.

### Code

```c
/*=========================================================*/
/* raceWithMutexAndProcesses.c                             */
/*=========================================================*/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

pthread_mutex_t shared_mutex;

struct {
  int balance[2];
} * Bank;  // global variable defined

void* MakeTransactions() {  // routine for thread execution
  int i, j, tmp1, tmp2, rint;
  double dummy;
  for (i = 0; i < 100; i++) {
    rint = (rand() % 30) - 15;
    pthread_mutex_lock(&shared_mutex);
    if (((tmp1 = Bank->balance[0]) + rint) >= 0 &&
        ((tmp2 = Bank->balance[1]) - rint) >= 0) {
      Bank->balance[0] = tmp1 + rint;
      for (j = 0; j < rint * 1000; j++) {
        dummy = 2.345 * 8.765 / 1.234;
      }  // spend time on purpose
      Bank->balance[1] = tmp2 - rint;
    }
    pthread_mutex_unlock(&shared_mutex);
  }
  return NULL;
}

int main(int argc, char** argv) {
  int i, shmid;
  void* voidptr = NULL;
  pthread_t tid[2];
  srand(getpid());
  pthread_mutex_init(&shared_mutex, NULL);

  if ((shmid = shmget(1234, 4, IPC_CREAT | 0666)) == -1) {
    perror("Error in getting shared memory segment\n");
    return 1;
  }
  Bank = shmat(shmid, NULL, 0);
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
  return 0;
}
```

### Output

```text
Init balances A:100 + B:100 ==> 200!
Let's check the balances A:17 + B:141 ==> 158 ?= 200
Let's check the balances A:17 + B:180 ==> 197 ?= 200

Init balances A:100 + B:100 ==> 200!
Let's check the balances A:143 + B:83 ==> 226 ?= 200
Let's check the balances A:128 + B:56 ==> 184 ?= 200

Init balances A:100 + B:100 ==> 200!
Let's check the balances A:31 + B:151 ==> 182 ?= 200
Let's check the balances A:28 + B:125 ==> 153 ?= 200

Init balances A:100 + B:100 ==> 200!
Let's check the balances A:144 + B:118 ==> 262 ?= 200
Let's check the balances A:154 + B:113 ==> 267 ?= 200

Init balances A:100 + B:100 ==> 200!
Let's check the balances A:191 + B:77 ==> 268 ?= 200
Let's check the balances A:146 + B:98 ==> 244 ?= 200

Init balances A:100 + B:100 ==> 200!
Let's check the balances A:30 + B:164 ==> 194 ?= 200
Let's check the balances A:18 + B:151 ==> 169 ?= 200

Init balances A:100 + B:100 ==> 200!
Let's check the balances A:16 + B:215 ==> 231 ?= 200
Let's check the balances A:8 + B:179 ==> 187 ?= 200

Init balances A:100 + B:100 ==> 200!
Let's check the balances A:23 + B:170 ==> 193 ?= 200
Let's check the balances A:11 + B:150 ==> 161 ?= 200

Init balances A:100 + B:100 ==> 200!
Let's check the balances A:96 + B:114 ==> 210 ?= 200
Let's check the balances A:49 + B:120 ==> 169 ?= 200

Init balances A:100 + B:100 ==> 200!
Let's check the balances A:0 + B:169 ==> 169 ?= 200
Let's check the balances A:1 + B:109 ==> 110 ?= 200

Init balances A:100 + B:100 ==> 200!
Let's check the balances A:49 + B:128 ==> 177 ?= 200
Let's check the balances A:41 + B:174 ==> 215 ?= 200

Init balances A:100 + B:100 ==> 200!
Let's check the balances A:16 + B:170 ==> 186 ?= 200
Let's check the balances A:9 + B:134 ==> 143 ?= 200

Init balances A:100 + B:100 ==> 200!
Let's check the balances A:256 + B:0 ==> 256 ?= 200
Let's check the balances A:287 + B:6 ==> 293 ?= 200

Init balances A:100 + B:100 ==> 200!
Let's check the balances A:3 + B:142 ==> 145 ?= 200
Let's check the balances A:7 + B:130 ==> 137 ?= 200

Init balances A:100 + B:100 ==> 200!
Let's check the balances A:107 + B:82 ==> 189 ?= 200
Let's check the balances A:131 + B:74 ==> 205 ?= 200
```

The race condition exists because the static `pthread_mutex_t shared_mutex` is not shared across processes, just threads.

## Question 4

>Use semaphore system calls to modify your code in Q3 in order to remove any potential race conditions. Show your modification of the code and explain the outcome with your modification.

### Code

```c
/*=========================================================*/
/* raceWithSemaphoresAndProcesses.c                        */
/*=========================================================*/
#include <fcntl.h>
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
    if (sem_wait(shared_mutex) < 0) {
      perror("Error in sem_wait()");
      continue;
    }
    if (((tmp1 = Bank->balance[0]) + rint) >= 0 &&
        ((tmp2 = Bank->balance[1]) - rint) >= 0) {
      Bank->balance[0] = tmp1 + rint;
      for (j = 0; j < rint * 1000; j++) {
        dummy = 2.345 * 8.765 / 1.234;
      }  // spend time on purpose
      Bank->balance[1] = tmp2 - rint;
    }
    while (sem_post(shared_mutex) < 0) {
      perror("Error in sem_post()");
    }
  }
  return NULL;
}

int main(int argc, char** argv) {
  int i, shmid_bank, shmid_mutex;
  void* voidptr = NULL;
  pthread_t tid[2];
  srand(getpid());

  shared_mutex = sem_open("/mutex_sem", O_CREAT, 0666, 1);

  if ((shmid_bank = shmget(1234, 4, IPC_CREAT | 0666)) < 0) {
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
  pid_t pid = fork();
  if (pid < 0) {
    perror("Error in forking\n");
    return (1);
  } else if (pid == 0) {
    shared_mutex = sem_open("/mutex_sem", O_RDWR);
    MakeTransactions();
  } else {
    shared_mutex = sem_open("/mutex_sem", O_RDWR);
    MakeTransactions();
  }
  printf("Let's check the balances A:%d + B:%d ==> %d ?= 200\n",
         Bank->balance[0], Bank->balance[1],
         Bank->balance[0] + Bank->balance[1]);
  if (shmdt(Bank) < 0) {
    perror("Error in shared memory detach");
    return 1;
  }
  sem_unlink(shared_mutex);
  sem_destroy(shared_mutex);
  return 0;
}
```

### Output

```text
Init balances A:100 + B:100 ==> 200!
Let's check the balances A:185 + B:15 ==> 200 ?= 200
Let's check the balances A:196 + B:4 ==> 200 ?= 200

Init balances A:100 + B:100 ==> 200!
Let's check the balances A:17 + B:183 ==> 200 ?= 200
Let's check the balances A:14 + B:186 ==> 200 ?= 200

Init balances A:100 + B:100 ==> 200!
Let's check the balances A:117 + B:83 ==> 200 ?= 200
Let's check the balances A:94 + B:106 ==> 200 ?= 200

Init balances A:100 + B:100 ==> 200!
Let's check the balances A:10 + B:190 ==> 200 ?= 200
Let's check the balances A:12 + B:188 ==> 200 ?= 200

Init balances A:100 + B:100 ==> 200!
Let's check the balances A:3 + B:197 ==> 200 ?= 200
Let's check the balances A:2 + B:198 ==> 200 ?= 200

Init balances A:100 + B:100 ==> 200!
Let's check the balances A:144 + B:56 ==> 200 ?= 200
Let's check the balances A:128 + B:72 ==> 200 ?= 200

Init balances A:100 + B:100 ==> 200!
Let's check the balances A:190 + B:10 ==> 200 ?= 200
Let's check the balances A:197 + B:3 ==> 200 ?= 200

Init balances A:100 + B:100 ==> 200!
Let's check the balances A:13 + B:187 ==> 200 ?= 200
Let's check the balances A:5 + B:195 ==> 200 ?= 200

Init balances A:100 + B:100 ==> 200!
Let's check the balances A:57 + B:143 ==> 200 ?= 200
Let's check the balances A:83 + B:117 ==> 200 ?= 200

Init balances A:100 + B:100 ==> 200!
Let's check the balances A:36 + B:164 ==> 200 ?= 200
Let's check the balances A:65 + B:135 ==> 200 ?= 200

Init balances A:100 + B:100 ==> 200!
Let's check the balances A:1 + B:199 ==> 200 ?= 200
Let's check the balances A:8 + B:192 ==> 200 ?= 200

Init balances A:100 + B:100 ==> 200!
Let's check the balances A:74 + B:126 ==> 200 ?= 200
Let's check the balances A:54 + B:146 ==> 200 ?= 200

Init balances A:100 + B:100 ==> 200!
Let's check the balances A:125 + B:75 ==> 200 ?= 200
Let's check the balances A:173 + B:27 ==> 200 ?= 200

Init balances A:100 + B:100 ==> 200!
Let's check the balances A:93 + B:107 ==> 200 ?= 200
Let's check the balances A:104 + B:96 ==> 200 ?= 200

Init balances A:100 + B:100 ==> 200!
Let's check the balances A:91 + B:109 ==> 200 ?= 200
Let's check the balances A:15 + B:185 ==> 200 ?= 200
```