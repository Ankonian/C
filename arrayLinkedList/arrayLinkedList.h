/**
 * This the header file for an array based link list as explained
 * in lecture.
 *
 * This is meant for as a tutorial. This data structure as it is
 * currently is not a very useful structure as all it does is
 * hold some strings.
 *
 * Auhtor: Yash Gupta <ygupta@ucsc.edu>
 */
# include <stdint.h>

# ifndef ARRAYLINKEDLIST_H
# define ARRAYLINKEDLIST_H

/*
 * For simplicity, I limited the list to be able to hold only 100
 * strings. If you feel adventurous, you can go ahead and let the user
 * decide how many members they would like to hold (malloc is your friend).
 *
 * You can go one step ahead and support a dynamic size whereby you
 * keep changing the size of your allocation to suport more strings
 * as and when they are added (realloc is your friend).
 */
# define LIST_MAX           (100)   /* Our list can hold at max 100 entries */
# define STRING_LENGTH      (101)   /* Max string size we store */

/*
 * These are value which are special to out array table
 * as they represent the status of an index in the link array
 * inside the structure defined below.
 */
# define LIST_END           (-1)    /* This entry in link[k] means end of list */
# define UNALLOCATED        (-2)    /* This entry in link[X] means spot available */

/**
 * This is the structure for our linked list. It holds all
 * the variables which are necessary for a single instance of the
 * list to be able to function.
 */
struct arrayLinkedList
{
    /*
     * This is the array which holds the data of strings
     * in our list.
     */
    char strings[LIST_MAX][STRING_LENGTH];

    /*
     * This is the array which holds the links for our list.
     * link[x] holds the value for the next name in the list
     * after strings[x].
     */
    int32_t link[LIST_MAX];

    /*
     * This variable holds the value for the first index
     * of the linked list. This is important, because if
     * someone removes the index at 0, then 0 is no longer
     * the first index and needs to be tracked.
     */
    int32_t firstIndex;

    /*
     * This variable holds the value for the last index of
     * the linked list. It allows us to find the end index
     * very quickly.
     */
    int32_t endIndex;

    /*
     * This variable holds how many elements have been added
     * to out list.
     */
    uint32_t count;
};

/**
 * This function is used to make a new list. We allocate
 * enough space for a new list which can hold a structure
 * of type arrayLinkedList.
 *
 * @return A structure or NULL
 */
struct arrayLinkedList* makeList(void);

/**
 * This function is used to free a list. We deallocate
 * all the memory we stored for a list.
 *
 * @param linkedList The list we need to free.
 */
void freeList(struct arrayLinkedList*);

/**
 * This function is used to insert an element into the
 * list.
 *
 * @param linkedList Which linkedList to insert into.
 * @param name The name to insert
 * @return Success or Error
 */
int addElement(struct arrayLinkedList*, char*);

/**
 * This function is used to search the linked list
 * for an element. It traverses through the list
 * and tries to find a specific element.
 *
 * @param linkedList The Linked List to search in.
 * @param string The string to search for.
 * @return True or False
 */
int searchElement(struct arrayLinkedList*, char*);

/**
 * This function is used to remove an element
 * from the linked list. It traverses through the list
 * and tries to remove a specified element.
 *
 * @param linkedList The Linked List to remove element from.
 * @param string The string to remove.
 * @return Sucess or Error
 */
int deleteElement(struct arrayLinkedList*, char*);

/**
 * This function is used to replace an element
 * from the linked list with something else.
 * It traverses through the list and tries to
 * find the specified element and replace it what the
 * new thing.
 *
 * @param linkedList The Linked List to replace element from.
 * @param oldString The string to replace
 * @param newString The new string to replace to
 * @return Success or Error
 */
int replaceElement(struct arrayLinkedList*, char*, char*);

/**
 * This function is used to print the entire linked
 * list and display its contents onto the standard
 * output.
 *
 * @param linkedList The Linked List to print
 */
void printList(struct arrayLinkedList*);

# endif
