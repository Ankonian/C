# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include "ll.h"

listNode *newNode(const char *oldspeak, const char *newspeak)
{
        listNode *t = (listNode *) malloc(sizeof(listNode));
        if(oldspeak != NULL)
        {
          t->oldspeak = strdup(oldspeak);
        }
        else
        {
          t->oldspeak = NULL;
        }
        if(newspeak != NULL)
        {
          t->newspeak = strdup(newspeak);
        }
        else
        {
          t->newspeak = NULL;
        }
        t->next = NIL;
        return t;
}

void delNode(listNode *n)
{
   free(n->oldspeak);
   free(n);
   return;
}

void delLL(listNode *n)
{
        while (n != NIL)
        {
                listNode *t = n;
                n = n-> next;
                delNode(t);
        }
        return;
}

listNode *insertLL(listNode **n, const char *key, const char *value)
{
        listNode *t = newNode(key, value);
        t->next = *n;
	//printf("here");
//	printLL(t);

        return t;
}

listNode *findLL(listNode **n, const char *key)
{
	listNode *prev = NULL;
        for (listNode *t = *n; t != NIL; t = t->next)
        {
          if (strcmp(t->oldspeak, key) == 0)
          {	//move-to-front rule

			         if(moveToFront == true && t != NULL && t != *n)
			            {
				                prev->next = t->next;
				                t->next = *n;
				                *n = t;
			            }
                  return t;
          }
        }
        return NIL;
}

void printLL(listNode *n)
{
        for (listNode *t = n; t != NIL; t = t->next)
        {
                printf("%s ", t->oldspeak);
        }
        printf("\n");
        return;
}
