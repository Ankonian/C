/*
 * This file is used to test the arrayLinkedList data structure
 * I have built.
 *
 * TODO: 1. Build
 *  make
 *
 * TODO: 2. Execute
 *  ./linkedListTest
 *
 * TODO: 3. Experiment
 *  Experiment with the values in this file and see
 *  how it affects the output
 *
 * TODO: 4. Understand
 *  This code is heavily commented for explanations.
 *  Try and understand it to see what is going on.
 *
 * TODO: 5. Extra Information
 *  Search for the term "NOTE" in all files and read
 *  what has been mentioned. There is some extra
 *  information available.
 *
 * TODO: 6. Improve
 *  This code is not optimized. It was written in a
 *  hurry and can be severely improved. Try to do it.
 *
 * Author: Yash Gupta <ygupta@ucsc.edu>
 */
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include "arrayLinkedList.h"

# define NUM_NAMES      (12)

/*
 * This is a simply main function which provides test
 * cases for the arrayLinkedList data structure.
 *
 * @return Zero or Error
 */
int main(void)
{
    int i, ret;
    struct arrayLinkedList *nameList;

    /* My list of names which I put in my list */
    char *testNames[NUM_NAMES] =
    {
        "Yash",
        "Matthew",
        "Arjun",
        "Boris",
        "Art",
        "Bharath",
        "Nehal",
        "Shubham",
        "Jurik",
        "Sneha",
        "Darrell",
        "Daniel"
    };

    /*
     * The first thing I need to do is call a function which allocates
     * enough memory for me so that I can begin storing information
     * in my list.
     *
     * Error checking is also present.
     */
    nameList = makeList();
    if (nameList == NULL)
    {
        printf("Error On Malloc {nameList} [%d: %s]\n", errno, strerror(errno));
        return errno;
    }

    /*
     * I begin adding names to my list using the interface functions
     * I have defined in arrayLinkedList.h and arrayLinkedList.c.
     *
     * I have again included error checking information.
     */
    for (i = 0; i < NUM_NAMES; i++)
    {
        ret = addElement(nameList, testNames[i]);
        if (ret == -1)
        {
            printf("Error On AddName (%s) {nameList} [%d: %s]\n", testNames[i], ret, "List Is Full");
            return ret;
        }
    }

    /*
     * In the following code snippets, I have NOT performed any error checking
     * and this is bad code from me. All the error checking is conventional
     * to how I have done it in addElement and makeElement from before.
     */

    /*
     * Now, I print the list to show how this list looks like
     * after I have inserted all those names
     */
    printf("INITIAL PRINT\n");
    printList(nameList);

    /*
     * Now, I delete the lement "Yash" from the list and I print
     * the list to show that the element list which was present
     * earlier has been removed.
     *
     * Notice that "Yash" is the first element in the list and
     * after removing it, "Matthew" becomes the first element in the list
     * even though its index value does not change.
     */
    printf("\nAFTER deleteElement(linkedList, \"Yash\")\n");
    ret = deleteElement(nameList, "Yash");
    printList(nameList);

    /*
     * Now, I delete an element in the middle of the list "Art".
     * Notice how after removing "Art", the next element after "Boris"
     * is "Bharath".
     */
    printf("\nAFTER deleteElement(linkedList, \"Art\")\n");
    ret = deleteElement(nameList, "Art");
    printList(nameList);

    /*
     * Now, over here, I replace the value of "Darrell" with
     * "Professor Long". All I do is replace the value and hence
     * the index of the element remains the same.
     */
    printf("\nAFTER replaceElement(linkedList, \"Darrell\", \"Professor Long\")\n");
    ret = replaceElement(nameList, "Darrell", "Professor Long");
    printList(nameList);

    /*
     * Now, I add another element to the list "Life". Notice how
     * this element gets the index 0 as this index became free after I
     * removed "Yash". However, notice that even though it is index 0,
     * it is the last element in the list.
     *
     * This is how this data structure differs from an array. I can
     * keep addinf and removing elements from the lsit without having to
     * care about their actual index in memory.
     */
    printf("\nAFTER addElement(linkedList, \"Life\")\n");
    ret = addElement(nameList, "Life");
    printList(nameList);

    /*
     * Finally, we free the memory associated with this list and
     * exit the program.
     */
    freeList(nameList);

    return 0;
}
