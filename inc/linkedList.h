#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <stdlib.h>

typedef struct ListNode {
  unsigned int data;
  struct ListNode *next;
} ListNode;

typedef struct LinkedList {
  ListNode *head;
  ListNode *tail;
  int len;
} LinkedList;

int listPop(LinkedList *list, unsigned int target);
void listPush(LinkedList *list, unsigned int target);
LinkedList *createList();
#endif
