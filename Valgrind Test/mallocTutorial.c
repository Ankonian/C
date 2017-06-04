/*
 * This is the Lab demonstration for dynamic memory allocation in C.
 *
 * Dynamic memory is simply memory which exists on the heap rather
 * than the stack. It has global scope, meaning, the memory can be accessed
 * from any part of the program. It is an extremely useful tool, as it
 * allows us to allocate memory for a program as and when needed.
 *
 * It is crucial for almost every other data strcuture like Linked Lists,
 * Trees and Graphs.
 *
 * To get the most out of this tutorial, we recommended that you read the code
 * demonstrations in order as follows:-
 *	1. main
 *	2. demonstrateMalloc
 *	3. demonstrateCalloc
 *	4. demonstrateRealloc
 *
 * TODO: COMPILE USING
 *	cc -Wall -Wextra -Wpedantic -Werror -std=c99 mallocLab.c -o mallocTest
 *
 * TODO: 1. EXECUTE USING
 *	./mallocTest
 *
 * TODO: 2. EXECUTE USING
 *	valgrind --leak-check=full mallocTest
 */
# include <stdio.h>	// Required for printf
# include <stdlib.h>	// Required for malloc, calloc, realloc, free, and NULL
# include <errno.h>	// Required for errno
# include <string.h>	// Required for strdup, strcpy, and strlen

/*----- STUFF WHICH SHOULD BE IN HEADER FILE -----*/

/*
 * This is a macro in C. It is a preprocessor, and it gets inserted
 * into your code before compile time.
 *
 * In case you are perplexed by this statement, we recommended
 * you Google about C macros.
 */
# define BUFFER_SIZE			(101)	// Size of our buffer

/*
 * This is a very basic structure in C. A structure is a data
 * type used to hold other data types. It is extremely useful
 * in collecting different data types pertaining to a single
 * object.
 *
 * Read about C structs on Google for more information.
 */
typedef struct testStruct {
	int myData;
	char myString[BUFFER_SIZE];
} testStruct;

/* Prototypes */
int demonstrateMalloc(void);
int demonstrateCalloc(void);
int demonstrateRealloc(void);

/*----- END OF STUFF WHICH SHOULD BE IN HEADER FILE -----*/

/**
 * This function is used to demonstrate the malloc system
 * call for dynmaic memory allocation.
 *
 * @return Zero Or Error
 */
int
demonstrateMalloc(void)
{
	int *myInt;
	int *myArray;
	char *myString;
	testStruct *myStruct;

	/*
	 * The malloc system call allocates a specified number of bytes
	 * from the heap and returns the beginning address of that memory.
	 * In this example, we allocate space for a single integer and
	 * store the address for that integer in myInt.
	 *
	 * The 'sizeof' operator is a built-in call which returns the size of the
	 * data type in bytes. Note, sizeof is not a function, it is a language
	 * keyword. The parentheses in this case are actually a cast operation.
	 *
	 * For example this code allocates a piece of memory of the same size as
	 * the variable v. There are no parentheses here because sizeof is not a
	 * function:
	 *
	 * int v;
	 * malloc(sizeof v);
	 */
	myInt = malloc(sizeof(int));

	/*
	 * It is possible that the call we just made might have failed due
	 * to the system not having enough memory, or some other reason.
	 *
	 * The error code is stored in the global variable 'errno' (found in errno.h)
	 * and this error code allows us to debug what the problem was.
	 *
	 * In case an error did occur, malloc returns NULL.
	 */
	if (myInt == NULL)
	{
		/*
		 * The 'strerror' function (found in string.h) takes in an error code
		 * and returns a string telling us what the error code meant.
		 *
		 * Note, it is critical that you do not make any other library calls
		 * before you check the value of errno, because they could change its
		 * value. This is why global variables are bad, but this is a deeply
		 * traditional method of error handling in C, so you have no choice.
		 */
		printf("Error on malloc {myInt} [%d: %s]\n", errno, strerror(errno));
		return errno;
	}

	/*
	 * To allocate an array of integers, we need to calculate how many
	 * bytes an array of N number of integers require. This can be done
	 * using sizeof(int) * N. Note, the variable myArray is just a pointer,
	 * and unlike in Java, it does not contain any information about its length.
	 */
	myArray = malloc(sizeof(int) * 3);
	if (myArray == NULL)
	{
		printf("Error on malloc {myArray} [%d: %s]\n", errno, strerror(errno));
		return errno;
	}

	/*
	 * A very important thing to remember is that malloc returns the address of
	 * the space we have requested. Hence, myInt now POINTS to the single
	 * integer we requested and myArray POINTS to the address of the first
	 * of the three integers.
	 *
	 * To access the value stored at these addresses, there are multiple syntactical
	 * ways.
	 */
	printf("MALLOC OPERATIONS\n");

	/*
	 * To change the value associated with myInt, we need to use the
	 * dereference operator.
	 *
	 * The dereference operator is simply a '*' before the name of a pointer
	 * variable. It is important to note some things
	 *	int *ptr;	This is the declaration of a pointer. NOT a dereference
	 *	*ptr = 5;	This is the dereference of a pointer. NOT a declaration
	 */
	*myInt = 5;

	printf("{malloc} myInt	    [VALUE]: %d\n", *myInt);
	printf("{malloc} myInt   [ADDRESS]: %p\n\n", (void *)myInt);

	/*
	 * We can access the array using the general notation for working
	 * with arrays. This is because the usual way for accessing arrays
	 * deferences the array pointer.
	 *
	 * An alternate, more "pointeristic" approach is shown in the comments.
	 * It is receommended to use the usual notation for clarity.
	 *
	 * However, it is important to note, that the addition of value to a
	 * pointer really does not add the value to the pointer, it adds the
	 * value times the size of the type of the pointer. For example if we
	 * add one to an integer pointer, on most machines you will see that
	 * the actual address is incremented by 4 (what sizeof(int) is).
	 * Similarly, if we add 1 to a character pointer, you will notice
	 * that it will add 1 to the address.
	 *
	 * This is because on most machines, integers are 4 bytes and characters
	 * are single byte.
	 */
	myArray[0] = 10;	// OR *(myArray + 0) = 10
	myArray[1] = 11;	// OR *(myArray + 1) = 11
	myArray[2] = 12;	// OR *(myArray + 2) = 12

	printf("{malloc} myArray[0]    [VALUE]: %d\n", myArray[0]);
	printf("{malloc} myArray     [ADDRESS]: %p\n\n", (void *)myArray);

	/*
	 * Since array access notation is exactly equivalent to the addition
	 * and for reasons beyond comprehension of reasonable people, pointer
	 * addition is commutative, another exactly equivalent notation is
	 * -- DO NOT DO THIS --
	 * 0[myArray] = 10;
	 * 1[myArray] = 11;
	 * 2[myArray] = 12;
	 * -- DO NOT DO THIS --
	 */

	/*
	 * We can work with strings in multiple ways as well. We can use
	 * the traditional malloc method and a function called strcpy to
	 * create a duplicate of a string.
	 */
	const char *original = "Hello, World!";
	myString = malloc(strlen(original) + 1); // +1 for the null termination character
	if (myString == NULL)
	{
		printf("Error on malloc {myString} [%d: %s]\n", errno, strerror(errno));
		return errno;
	}
	strcpy(myString, original);

	printf("{strcpy} myString     [VALUE]: %s\n", myString);
	printf("{strcpy} myString   [ADDRESS]: %p\n\n", (void *)myString);

	/*
	 * Working with structures is similar. We call malloc and
	 * like before we get the size of the allocation using the sizeof
	 * call.
	 * Accessing the structure fields can be done in two ways,
	 * and they are shown below.
	 *
	 * It is recommended to use the '->' (arrow notation) for clarity.
	 */
	myStruct = malloc(sizeof(testStruct));
	if (myStruct == NULL)
	{
		printf("Error on malloc {myStruct} [%d: %s]\n", errno, strerror(errno));
		return errno;
	}

	myStruct->myData = 5;						// OR (*myStruct).myData = 5
	strcpy(myStruct->myString, myString);	// OR strcpy((*myStruct).myString, myString)

	printf("{malloc} myStruct->myData     [VALUE]: %d\n", myStruct->myData);
	printf("{malloc} myStruct->myString   [VALUE]: %s\n", myStruct->myString);
	printf("{malloc} myStruct            [ADDRESS]: %p\n\n", (void *)myStruct);

	/*
	 * Everything we malloc needs to be free'd once we no longer have a use
	 * for that space. Freeing is crucial as it opens up the space which might
	 * be needed by other programs.
	 *
	 * Not freeing up the space leaves it allocated in the system and this
	 * is what we call a memory leak.
	 *
	 * To free previously allocated space, we use the system call 'free'.
	 * It simply takes in a variable which holds an address for the heap.
	 * The size does not need to be specified.
	 *
	 * It is good practice to also set your pointers to NULL after you free
	 * them to avoid potential use-after-free bugs, which are responsible for
	 * a large fraction of real-world security exploits.
	 *
	 * NOTE: It is recommended, but NOT necessary to free variables in the
	 * opposite order of allocation.
	 */
	free(myStruct);
	free(myString);
	free(myArray);
	free(myInt);

	myStruct = NULL;
	myString = NULL;
	myArray = NULL;
	myInt = NULL;

	return 0;
}

/**
 * This function is used to demonstrate the calloc system
 * call for dynmaic memory allocation.
 *
 * @return Zero Or Error
 */
int
demonstrateCalloc(void)
{
	int *myInt;
	int *myArray;
	char *myString;
	testStruct *myStruct;

	/*
	 * The 'calloc' (found in stdlib.h) system call is very similar to
	 * the 'malloc' (found in stdlib.h) system call. They both allocate
	 * memory on the heap, however, there is a slight difference.
	 *
	 * Allocating memory using the calloc call zeroes out the memory,
	 * or in other words, it overwrites the newly allocated memory with
	 * zero. Hence, calls to calloc might be slower than calls to malloc.
	 *
	 * The first parameter for calloc is the count of a variable we need to
	 * allocate, and the second parameter is the size of each thing.
	 *
	 * NOTE: Both calloc and malloc return the address to the memory allocated.
	 */
	printf("CALLOC OPERATIONS\n");

	/* To allocate a single integer, we would do as follows */
	myInt = calloc(1, sizeof(int));
	if (myInt == NULL)
	{
		printf("Error on calloc {myInt} [%d: %s]\n", errno, strerror(errno));
		return errno;
	}

	/*
	 * Like with malloc, we now have the address of the memory we just allocated
	 * and to access the value at this memory, we will use the dereference
	 * operator.
	 */
	*myInt = 5;
	printf("{calloc} myInt     [VALUE]: %d\n", *myInt);
	printf("{calloc} myInt   [ADDRESS]: %p\n\n", (void *)myInt);

	/*
	 * Working with arrays is again similar. This time, we will specify
	 * the count as the number of integers our array can hold.
	 */
	myArray = calloc(3, sizeof(int));
	if (myArray == NULL)
	{
		printf("Error on calloc {myArray} [%d: %s]\n", errno, strerror(errno));
		return errno;
	}

	myArray[0] = 10;
	myArray[1] = 11;
	myArray[2] = 12;

	printf("{calloc} myArray[0]    [VALUE]: %d\n", myArray[0]);
	printf("{calloc} myArray     [ADDRESS]: %p\n\n", (void *)myArray);

	/*
	 * Calloc can be used for strings as well. A simple demonstration is shown
	 * below.
	 *
	 * The 'strlen' (found in string.h) is a library call that returns the
	 * length of the string passed to it.
	 */
	char *testString = "Hello, World!";
	int stringSize = strlen(testString);

	myString = calloc(stringSize, sizeof(char));
	if (myString == NULL)
	{
		printf("Error on calloc {myString} [%d: %s]\n", errno, strerror(errno));
		return errno;
	}

	strcpy(myString, testString);

	printf("{calloc} myString     [VALUE]: %s\n", myString);
	printf("{calloc} myString   [ADDRESS]: %p\n\n", (void *)myString);

	/* Syntax for structure is the same and should be obvious to you now */
	myStruct = calloc(1, sizeof(testStruct));
	if (myStruct == NULL)
	{
		printf("Error on calloc {myStruct} [%d: %s]\n", errno, strerror(errno));
		return errno;
	}

	myStruct->myData = 5;						// OR (*myStruct).myData = 5
	strcpy(myStruct->myString, myString);	// OR strcpy((*myStruct).myString, myString)

	printf("{calloc} myStruct->myData     [VALUE]: %d\n", myStruct->myData);
	printf("{calloc} myStruct->myString   [VALUE]: %s\n", myStruct->myString);
	printf("{calloc} myStruct            [ADDRESS]: %p\n\n", (void *)myStruct);

	/* Like before, we need to free everything allocated */
	free(myStruct);
	free(myString);
	free(myArray);
	free(myInt);

	myStruct = NULL;
	myString = NULL;
	myArray = NULL;
	myInt = NULL;

	return 0;
}

/**
 * This function is used to demonstrate the realloc system
 * call for dynmaic memory allocation.
 *
 * @return Zero Or Error
 */
int
demonstrateRealloc(void)
{
	int *myVar;
	const int firstSize = 5;
	const int secondSize = 10;

	printf("REALLOC OPERATIONS\n");
	printf("There are none :)\n");

	/*
	 * The 'realloc' (found in stdlib.h) is a bit different from the malloc
	 * and calloc calls. From the top, it performs the same task of allocating
	 * memory on the heap, and then returning the address of the beginning of the
	 * memory, however, it has a different use case.
	 *
	 * Essentially, this call is utilized when we want to change the size of our
	 * allocation without making a new allocation.
	 *
	 * The call takes two parameters, the start address of the memory to be changed
	 * and the size it needs to be changed to in bytes. As before, this call returns
	 * the beginning address in success, and a NULL on failure, setting the errno
	 * global variable with the required code.
	 */
	myVar = malloc(sizeof(int) * firstSize);
	if (myVar == NULL)
	{
		printf("Error on malloc {myVar} [%d: %s]\n", errno, strerror(errno));
		return errno;
	}

	/*
	 * At this point myVar is an array which can hold firstSize (5)
	 * integers. But what if we decided that because of workload, we now need
	 * myVar to be able to hold secondSize (10) integers.
	 *
	 * We could, of course, allocate ompletely new memory of 10 integers, copy
	 * the first 5 integers from myVar and then free the memory in myVar. But
	 * as you might have guessed, that will be a cumbersome and annoying proces
	 * and we don't want C to be an annoying language, do we?
	 *
	 * This is where realloc steps in. By passing in a size greater than the
	 * previous allocation, we can extend the allocation size. Conversely, by passing
	 * in something smaller, we can shrink the allocation size.
	 *
	 * Hence, after this call, myVar is an array which can hold upto 10 integers.
	 *
	 * NOTE: In almost all cases, realloc actually extends or shrinks the memory
	 * allocation. What this means is that, the starting address literally remains the
	 * the same after the call. It is only when the system cannot find enough mmemory in
	 * the allocation 'spot' that it changes the starting address of where myVar would
	 * point. In that case, it automatically copies the contents of the previous memory
	 * over to the new memory, and free's the old memory for you.
	 */
	myVar = realloc(myVar, sizeof(int) * secondSize);
	if (myVar == NULL)
	{
		/*
		 * There is a very subtle, yet a very dangerous way to screw up
		 * over here. Basically, if the realloc call failed in this
		 * case, it will return a NULL. However, the original memory which
		 * was stored in myVar is still valid memory.
		 *
		 * But as you can see, during the call to realloc, we set the new memory
		 * to again be returned in myVar. Hence, if the return call fails, we lose
		 * the address of the originally allocated memory and essentially cause
		 * a memory leak as there is no way we can get back to that memory now in
		 * order to use or free it as myVar (which holds the address of the valid
	 	 * memory) gets set to NULL.
		 *
		 * Hence, it is recommended that before you make a realloc call, you should
		 * save the memory address pointed to by myVar, and then call realloc
		 * on myVar. This way, you still have access to the old memory.
		 *
		 * int *tempPtr;
		 * tempPtr = myVar;
		 * myVar = realloc...
		 *
		 * NOTE: There is another call 'reallocf' (found in stdlib.h) which frees up
		 * the original memory incase a call to extend or shrink the memory fails.
		 */
		printf("Error on realloc {myVar} [%d: %s]\n", errno, strerror(errno));
		return errno;
	}

	/*
	 * The asutute and perhaps curious reader at this point might be wondering
	 * what would happen if the address parameter for realloc was set at NULL.
	 * Would we get allocated memory beginning at address 0 (NULL is essentially 0)?
	 *
	 * The answer is no. If the argument parameter is NULL, realloc simply behaves
	 * as malloc, and allocates the assigned size memory somewhere in the heap.
	 */
	myVar = realloc(NULL, sizeof(int) * firstSize);
	if (myVar == NULL)
	{
		printf("Error on realloc {myVar} [%d: %s]\n", errno, strerror(errno));
		return errno;
	}

	/*
	 * The even more astute reader at this point might have noticed a grave
	 * error which has been made in this code.
	 *
	 * We did not free the memory pointed to by myVar before the "disguised" malloc
	 * call (again, realloc with argument parameter set to NULL is essentially
	 * malloc). Hence, there is no way we can access the previous memory. This is again
	 * a memory leak as that memory can now not be free'd and will remain utilized in the
	 * system for the duration of the length of program execution.
	 *
	 * Code like this HAS made its way into production machines over the world
	 * and is one of the leading causes for memory leaks and poor memory performance.
	 */
	free(myVar);
	myVar = NULL;

	return 0;
}

/**
 * Always comment your code well. In this particular case,
 * the main function performs no other task other than
 * demonstrating some basic uses cases for dynamic
 * memory allocation.
 *
 * @return Error code or zero
 */
int
main(void)
{
	int ret;

	/* Look at code for demonstrateMalloc for a tutorial on malloc */
	ret = demonstrateMalloc();
	if (ret)
	{
		return errno;
	}

	/* Look at code for demonstrateCalloc for a tutorial on calloc */
	ret = demonstrateCalloc();
	if (ret)
	{
		return errno;
	}

	/* Look at code for demonstrateRealloc for a tutorial on realloc */
	ret = demonstrateRealloc();
	if (ret)
	{
		return errno;
	}

	return 0;
}
