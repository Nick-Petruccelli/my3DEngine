#include "../inc/linkedList.h"

int listPop(LinkedList *list, unsigned int target) {
  ListNode *curr = list->head;
  while (curr->next != NULL) {
    if (curr->next->data == target) {
      ListNode *temp = curr->next;
      curr->next = curr->next->next;
      free(temp);
      return 0;
    }
  }

  return -1;
}

void listPush(LinkedList *list, unsigned int n) {
  ListNode *node;
  node->next = NULL;
  node->data = n;
  if (list->len == 0) {
    list->head = node;
    list->tail = node;
    list->len++;
    return;
  }
  list->tail->next = node;
  list->tail = node;
  list->len++;
  return;
}

LinkedList *createList() {
  LinkedList *list;
  list->len = 0;
  list->head = NULL;
  list->tail = NULL;
  return list;
}
