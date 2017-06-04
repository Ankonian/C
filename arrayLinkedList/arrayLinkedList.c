/*
 * This file defines the functions decalred in arrayLinkedList.h
 * and makes a functionally complete linked list which works
 * through links stored in another array.
 *
 * This linked list is meant only for a tutorial and in this
 * case is not very useful as all it does is sotre some strings.
 *
 * Author: Yash Gupta <ygupta@ucsc.edu>
 */
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <errno.h>
# include "arrayLinkedList.h"

/*
 * NOTE
 * A bunch of the functions present in this file are not declared
 * anywhere in the header file. All these functions, you will notice,
 * have been defined as static functions.
 *
 * The keyword static (in this case) essentially means that these functions
 * are local to THIS file. The test file which I have created "linkedListTest.c"
 * will NOT be able to all these static functions.
 *
 * A static function has local scope to the file is it defined in and cannot
 * be called by other files.
 *
 * You will also notice that all static functions I have begin with an
 * underscore "_". This is NOT required, however, I prefer to name these
 * functions with an "_" because these functions are helper funcstions to
 * the other functions and should NOT be called directly by a user.
 */

/**
 * This function scans the link array to find an index
 * location which is unallocated and we can use to
 * store a node in the list.
 *
 * @param linkedList The linked list to look into
 * @return Index or Error
 */
static int _findNextFreeIndex(struct arrayLinkedList *linkedList)
{
    int index;

    /*
     * NOTE
     * There is a potential optimization one can do over here.
     * You can have a variable somewhere which saves which
     * index we last looked at and then begin searching for an
     * unallocated spot from that index rather than zero
     * everytime.
     */

    /*
     * The functioning of this program is simple. All it does is
     * loop through every single entry in the link array trying to
     * look for an index which has been set to UNALLOCATED {-2}. As
     * soon as it finds one, it returns that index.
     *
     * If it cannot find one, then it returns an error indicating we
     * do not have any free spots left in the list.
     */
    index = 0;
    while (linkedList->link[index] != UNALLOCATED && index < LIST_MAX)
    {
        index += 1;
    }

    if (index == LIST_MAX)
    {
        return -1;
    }
    else
    {
        return index;
    }
}

/**
 * This function builds a node for the linked list
 * at the specified index.
 *
 * @param linkedList The linked list to build into.
 * @param index The index to build at.
 * @param string The string to build from.
 */
static void _buildElement(struct arrayLinkedList *linkedList, int index, char *string)
{
    /*
     * We need to copy over the string into our linked list structure.
     * We will use the function 'strncpy' (found in string.h) to do so.
     * At max, we will copy over NAME_LENGTH - 1 bytes to reserve space
     * for the NULL.
     */
    strncpy(linkedList->strings[index], string, STRING_LENGTH - 1);

    /*
     * Now, we set this as the last element in the list. We will be inserting
     * this element into the last spot of the list and hence, the
     * link for this element gets set to -1 to indicate the end
     * of the list.
     */
    linkedList->link[index] = LIST_END;

    /*
     * Now, we need to increase the count of elements added to our list
     * because well, we just added one.
     */
    linkedList->count += 1;
}

/**
 * This function is used to acquire the index of an
 * element in a linked list.
 *
 * @param linkedList The linked list to search in
 * @param string The string to look for
 * @return Index of String or -1
 */
 static int _getIndexOfElement(struct arrayLinkedList *linkedList, char *string)
 {
     int index;

     /*
      * If the list is empty, then obviously the element
      * the user is looking for does not exist.
      */
     if (linkedList->count == 0)
     {
         return -1;
     }

     /*
      * In case the list is not empty, we traverse through the list
      * and search until we find the first occurence of the string.
      *
      * This search function only searches for the first time the
      * element occurs in the list.
      */
     index = linkedList->firstIndex;
     while (linkedList->link[index] >= 0)
     {
         if (strcmp(linkedList->strings[index], string) == 0)
         {
             return index;
         }
         index = linkedList->link[index];
     }

     /*
      * Our loop keeps checking until link[index] is not negative.
      * This means we still need to look at the last element separately
      * because the last element won't be considered in the loop.
      */
     if (strcmp(linkedList->strings[index], string) == 0)
     {
         return index;
     }
     else
     {
         return -1;
     }
 }

 /**
  * This function is used to get the "parent" link for
  * an index. It traverses until it find an index whose
  * link is the index we pass in.
  *
  * @param linkedList The Linked List we need to search.
  * @param index The index whose parent index we need to find.
  * @return The Parent Index of index
  */
 static int _getParentIndex(struct arrayLinkedList *linkedList, int index)
 {
     int parentIndex;

     /*
      * We traverse through the list until link[x] == index
      * and at that point we return x.
      *
      * We assume this function is only going to be called for a valid
      * index. Hence, there needs to be some x such that link[x] == index.
      */
     parentIndex = linkedList->firstIndex;
     while (linkedList->link[parentIndex] != index)
     {
         parentIndex = linkedList->link[parentIndex];
     }

     return parentIndex;
 }

/**
 * This function is used to make a new list. We allocate
 * enough space for a new list which can hold a structure
 * of type arrayLinkedList.
 *
 * @return A structure or NULL
 */
struct arrayLinkedList* makeList(void)
{
    struct arrayLinkedList *newList;

    newList = malloc(sizeof(struct arrayLinkedList));
    if (newList == NULL)
    {
        return NULL;
    }

    for (int i = 0; i < LIST_MAX; i++)
    {
        newList->link[i] = UNALLOCATED;
    }
    newList->firstIndex = -1;
    newList->endIndex = -1;
    newList->count = 0;

    return newList;
}

/**
 * This function is used to free a list. We deallocate
 * all the memory we stored for a list.
 *
 * @param linkedList The list we need to free.
 */
void freeList(struct arrayLinkedList *linkedList)
{
    /*
     * Out two arrays strings and link were NOT
     * allocated dynamically and hence, they do not
     * need to be free'd separately.
     */

    free(linkedList);
}

/**
 * This function is used to insert an element into the
 * list.
 *
 * @param linkedList The linked list to insert into
 * @param string The string to insert
 * @return Success or Error
 */
int addElement(struct arrayLinkedList *linkedList, char *string)
{
    int index;

    /*
     * If this is the first element in the list, then we insert at
     * the index 0 of the list.
     */
    if (linkedList->count == 0)
    {
        _buildElement(linkedList, 0, string);
        linkedList->firstIndex = 0;
        linkedList->endIndex = 0;

        return 0;
    }

    /*
     * Since this is not the first element in the list,
     * we need to find an index which is unallocated.
     *
     * After that, we build the node by calling our _buildElement
     * function. Once we have successfuly built the node, we
     * can insert the node properly into the list.
     */
    index = _findNextFreeIndex(linkedList);
    if (index == -1)
    {
        return -1;
    }
    _buildElement(linkedList, index, string);

    /*
     * Inser this node at the end of the list. This is done by utilizing
     * the variable endIndex inside linkedList.
     */
    linkedList->link[linkedList->endIndex] = index;
    linkedList->endIndex = index;

    return 0;
}

/**
 * This function is used to search the linked list
 * for an element. It traverses through the list
 * and tries to find a specific element.
 *
 * @param linkedList The Linked List to search in.
 * @param string The string to search for.
 * @return True or False
 */
int searchElement(struct arrayLinkedList *linkedList, char *string)
{
    if (_getIndexOfElement(linkedList, string) >= 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * This function is used to remove an element
 * from the linked list. It traverses through the list
 * and tries to remove a specified element.
 *
 * NOTE: This function is unoptimized. It needs to traverse
 * the list twice. Once to find the index, and another time
 * to find the "parent" of index. I urge anyone reading this
 * to try and optimize this.
 *
 * @param linkedList The Linked List to remove element from.
 * @param string The string to remove.
 * @return Success or Error
 */
int deleteElement(struct arrayLinkedList *linkedList, char *string)
{
    int index;
    int temp;
    int parentIndex;

    /*
     * Acquire the index of the element to be removed.
     * We can then use this index to work on this elements
     * removal.
     */
    index = _getIndexOfElement(linkedList, string);
    if (index == -1)
    {
        return -1;
    }

    /*
     * We save the value of link[index] as we will need it later on.
     * Afterwards, we need to reset the value of link[index] to be UNALLOCATED
     * and reduce the count of our list.
     */
    temp = linkedList->link[index];
    linkedList->link[index] = UNALLOCATED;
    linkedList->count -= 1;

    /*
     * There is an edge case over here. We need to have special
     * instructions in case this is the first element in the list
     * as then there is no parentIndex.
     */
    if (index == linkedList->firstIndex)
    {
        linkedList->firstIndex = temp;
        return 0;
    }

    /*
     * Acquire the parent index of the recently acquired index.
     * The reason we need to acquire this is because we need to change
     * the value of link[parentIndex] to be link[index] as the element
     * at location index is no longer a valid element and we need to fill
     * up the hole which is left by removing index.
     */
    parentIndex = _getParentIndex(linkedList, index);
    linkedList->link[parentIndex] = temp;

    return 0;
}

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
int replaceElement(struct arrayLinkedList *linkedList, char *oldString, char *newString)
{
    int index;

    /*
     * We need to find the index of the element which
     * holds oldString.
     */
    index = _getIndexOfElement(linkedList, oldString);
    if (index == -1)
    {
        return -1;
    }

    /*
     * We simply need to replace the oldString with the new string and all
     * we do in this case is overwrite what is stored in our array
     * with newString.
     */
    strncpy(linkedList->strings[index], newString, STRING_LENGTH - 1);

    return 0;
}

/**
 * This function is used to print the entire linked
 * list and display its contents onto the standard
 * output.
 *
 * @param linkedList The Linked List to print
 */
void printList(struct arrayLinkedList *linkedList)
{
    int index;

    /*
     * In case the list is emtpy, we simply retutn as there is
     * nothing to print.
     */
    if (linkedList->count == 0)
    {
        return;
    }

    /*
     * If the list is not empty, we traverse the list, printing
     * all the lements until the link[index] value is -1 as that
     * specifies the end of the list.
     *
     * Notice that this loop exits as soon as link[index] becomes
     * negative. However, there is still a valid element at this point
     * as index now represents the last element in the list. So, we
     * need to print that separately.
     *
     * In an actual implementation we would not usually print the index
     * since we do not directly ever care about the index of something
     * in this list.
     */
    index = linkedList->firstIndex;
    while (linkedList->link[index] >= 0)
    {
        printf("[Index: %d] %s\n", index, linkedList->strings[index]);
        index = linkedList->link[index];
    }
    printf("[Index: %d] %s\n", index, linkedList->strings[index]);
}
