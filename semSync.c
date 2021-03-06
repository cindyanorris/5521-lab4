#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include "wrappers.h"

void *text(void *arg);

int code[] = { 4, 6, 3, 1, 5, 0, 2 };

int main()
{

  //initialize semaphores

  //create seven threads
  //the argument to thread i is code[i], which indicates
  //the section of the switch statement that the thread should
  //execute

  //join with the threads and destroy the semaphores
  
  return 0;
}

/* text
 * Outputs the text indicated by the argument
 */
void *text(void *arg)
{
  int n = *(int*)arg;

  //use the semaphores to force the output to
  //appear in the proper order
  switch (n)
  {
    case 0:
      printf("A semaphore S is an integer-valued variable which can take only non-negative\n");
      printf("values. Exactly two operations are defined on a semaphore:\n\n");
      break;

    case 1:
      printf("Signal(S): If there are processes that have been suspended on this semaphore,\n");
      printf(" wake one of them, else S := S+1.\n\n");
      break;

    case 2:
      printf("Wait(S): If S>0 then S:=S-1, else suspend the execution of this process.\n");
      printf(" The process is said to be suspended on the semaphore S.\n\n");
      break;

    case 3:
      printf("The semaphore has the following properties:\n\n");
      break;

    case 4:
      printf("1. Signal(S) and Wait(S) are atomic instructions. In particular, no\n");
      printf(" instructions can be interleaved between the test that S>0 and the\n");
      printf(" decrement of S or the suspension of the calling process.\n\n");
      break;

    case 5:
      printf("2. A semaphore must be given an non-negative initial value.\n\n");
      break;

    case 6:
      printf("3. The Signal(S) operation must waken one of the suspended processes. The\n");
      printf(" definition does not specify which process will be awakened.\n\n");
      break;
  }

  pthread_exit(0);
}
