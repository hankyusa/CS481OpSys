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

## Question 4

>Use semaphore system calls to modify your code in Q3 in order to remove any potential race conditions. Show your modification of the code and explain the outcome with your modification.