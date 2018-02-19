#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "wrappers.h"

/*
 * Add comments here to indicate the number of threads that should be used so
 * that your threaded program has the best performance on array with this number
 * of elements:
 * 10G
 * 1G
 * 100M
 */

void getArgs(int argc, char * argv[], int * size, int * threads);
void printUsage();
void printArray(int * array, int size);
void initArray(int ** array, int size);
int sequentialSum(int * array, int size);

int DEBUG = 0;

/*
 * printUsage
 * This function is called if the user provides bad command
 * line arguments.  It outputs usage information and
 * exits.
 */
void printUsage()
{
   printf("usage: sumArray -s <size> -t <threads> [-D]\n");
   printf("-s <size> - size of array\n");
   printf("-t <threads> - number of threads used for sum\n");
   printf("-D - optional debug flag\n");
   exit(1);
}

/*
 * getArgs
 * This function parses the command line arguments and
 * initializes the ints pointed to by size and threads
 * @params: argc - count of command line arguments
 * @params: argv - array of command line arguments
 * @params: size - pointer to an int variable to be set to
 *          the atoi of the command line arg that follows the
 *          "-s" in the array.
 * @params: threads - pointer to an int variable to be set to
 *          the atoi of the command line arg that follows the
 *          "-t" in the array.
*/
void getArgs(int argc, char * argv[], int * size, int * threads)
{
   int i;
   if (argc != 5 && argc != 6) printUsage();
   for (i = 1; i < argc; i++)
   {
      if (strcmp("-s", argv[i]) == 0)
      {
         (*size) = atoi(argv[i + 1]);
         i++;
      } else if (strcmp("-t", argv[i]) == 0)
      {
         (*threads) = atoi(argv[i + 1]);
         i++;
      } else if (strcmp("-D", argv[i]) == 0)
          DEBUG = 1;
      else
         printUsage(); 
   }
   if ((*size) <= 0 || (*threads) <= 0) printUsage();
}

/* initArray
 * Calls malloc to dynamically allocate space for an int array
 * of with ``size" elements
 * Uses rand() to randomly generate initial values for the
 * array elements. Elements are set to a value in the range 
 * 0 to 9
 * @param: array - pointer to the array pointer
 * @param: size - number of elements to be created
 */
void initArray(int ** array, int size)
{
   int i;
   int * ptr; 
   srand(time(0));
   (*array) = malloc(sizeof(int) * size);
   ptr = (*array);
   for (i = 0; i < size; i++)
      ptr[i] = rand() % 10;
}

/* sequentialSum
 * Sums up all elements of the array
 * @param: array - point to first element in array
 * @param: size - number of elements in the array
 * @returns: sum of all elements
 */
int sequentialSum(int * array, int size)
{
   int i = 0, sum = 0;
   for (i = 0; i < size; i++)
      sum += array[i];
   return sum;
}

/* printArray
 * prints the elements of the array, 20 per line.
 * @param: array - point to first element in array
 * @param: size - number of elements in the array
 */
void printArray(int * array, int size)
{
   int i;
   for (i = 0; i < size; i++)
   {
      if ((i % 20) == 0) printf("\n");
      printf("%3d", array[i]);
   }
}

/* main
 * Driver for the program. Creates an array, initializes
 * the elements of the array, and calls the sequentialSum
 * to add up all elements of the array.  Command line arguments
 * are given to provided to indicate the size of the array and
 * the number of threads to use to calculate the sum
 * using threads.
 */
int main(int argc, char *argv[])
{
   double cpuTimeUsed;
   clock_t startTm, endTm;
   int size, threads, sum;
   int * array;
   getArgs(argc, argv, &size, &threads);   
   initArray(&array, size);
   if (DEBUG) printArray(array, size);
   //clock returns number of clock cycles since
   //program was launched
   startTm = clock();  
   sum = sequentialSum(array, size);
   endTm = clock();
   //calculate number of clock cycles to perform sum
   //convert from cycles to seconds
   cpuTimeUsed = ((double) (endTm - startTm)) / CLOCKS_PER_SEC;
   printf("\nSequential sum is: %d\n", sum);
   printf("Cpu time: %lf seconds\n", cpuTimeUsed);

   startTm = clock();  
   //need to write a threadedSum function and helpers
   //sum = threadedSum(array, size);
   endTm = clock();
   //calculate number of clock cycles to perform sum
   //convert from cycles to seconds
   cpuTimeUsed = ((double) (endTm - startTm)) / CLOCKS_PER_SEC;
   printf("\nThreaded sum is: %d\n", sum);
   printf("Cpu time: %lf seconds\n", cpuTimeUsed);

   return 0;
}
