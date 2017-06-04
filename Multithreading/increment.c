# include <pthreads.h>

// Below skeleton code is generously provided by Darrell Long
int someSharedVariable;
pthread_mutex_t mutex;

struct threadArgs
{
  int data;
}

void *threadFunc(void *myArgs)
{
  struct threadArgs *args = (struct threadArgs *) myArgs;
  int data = args->data;

  someWork();
}

void someWork()
{
  pthread_mutex_lock(&mutex);

  // Perform stuff on someSharedVariable

  pthread_mutex_unlock(&mutex);
}
int main(void)
{
  pthread_t thisThread;
  struct threadArgs args;

  // Init mutex
  pthread_mutex_init(&mutex);

  // Set Arguments and create thread
  args.data = 10;
  pthread_create(&thisThread, NULL, threadFunc, &args);

  // Wait for thread to finish executing
  pthread_join(thisThread, NULL);

  // Destroy mutex
  pthread_mutex_destroy(&mutex);

  return 0;
}
