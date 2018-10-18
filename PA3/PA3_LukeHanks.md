# Programming Assignment 03

by Luke Hanks

## Question 1

>Compile then run the above code for 10-20 times. Write a paragraph to explain.

`void* MakeTransactions()` makes 100 random transactions under $15 between accounts A and B. Consider the following possible (and likely given that dummy for-loop) order of value assignments.

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