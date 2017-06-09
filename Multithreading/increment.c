# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <getopt.h>

// Below skeleton code is generously provided by Yash or Darrell or whoever created the pdf
int incrementor;
pthread_mutex_t mutex;

struct threadArgs
{
	int data;
}threadArgs;

void safeIncrement()
{
 	 pthread_mutex_lock(&mutex);

  	// Perform stuff on someSharedVariable
  	incrementor += 1;

  	pthread_mutex_unlock(&mutex);

	return;
}

void *threadFunc(void *myArgs)
{
	struct threadArgs *args = (struct threadArgs *) myArgs;
  	int numberOfCalls = args->data;
	// Jurik helped me on this part
	for(int i = 0; i < numberOfCalls; i++)
	{
  		safeIncrement();
	}
	return NULL;
}


int main(int argc, char **argv)
{
	// use getopt to get how many threads should be spawned
  	int numThreads;
	pthread_t *thisThread;
	int input;
	while((input = getopt(argc, argv, "n:")) != -1)
	{
		switch(input)
		{
			case 'n':
			{
				// get the number that runs runs the threading
				numThreads = atoi(optarg);
				break;
			}
			default:
			{
				printf("Invalid flag");
				break;
			}
		}
	}
	
	// Ishani and Boris helped me on explaining this concept
	thisThread = calloc(numThreads, sizeof(pthread_t));
	struct threadArgs *args = calloc(numThreads, sizeof(threadArgs));

  	// Init mutex
	// Ishani and Jurik helped me on this part of code
  	pthread_mutex_init(&mutex, NULL);

  	// Set Arguments and create thread
	for(int i = 0; i < numThreads; i++)
	{
		// Jurik and Ishani helped me to complete this code
		args[i].data = 1000;
  		pthread_create(&thisThread[i], NULL, threadFunc, &args[i]);
	}

  	// Wait for thread to finish executing
	for(int i = 0; i < numThreads; i++)
	{
  		pthread_join(thisThread[i], NULL);
	}

  	// Destroy mutex
  	pthread_mutex_destroy(&mutex);

	// Free allocated memory
	free(thisThread);
	free(args);

	// Print out the final result of the thread addition
	printf("%d\n", incrementor);
  	return 0;
}
