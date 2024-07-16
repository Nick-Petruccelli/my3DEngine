#include "../inc/glMath.h"
#include <stdbool.h>
#include <stdlib.h>

float *staticAssetArr;

typedef struct ListNode {
  unsigned int val;
  struct ListNode *next;
} ListNode;

typedef struct {
  ListNode *head;
  ListNode *tail;
  int count;
} LinkedList;

LinkedList createListF() {
  LinkedList list;
  list.head = NULL;
  list.tail = NULL;
  list.count = 0;

  return list;
}

void listPush(LinkedList list, unsigned int n) {
  if (list.count == 0) {
    list.head->val = n;
    list.head->next = NULL;
    list.tail->val = n;
    list.tail->next = NULL;
    list.count++;
    return;
  }
  if (list.count == 1) {
    list.head->next = list.tail;
    list.tail->val = n;
    return;
  }
  ListNode *node;
  node->val = n;
  node->next = NULL;
  list.tail = node;
}

unsigned int listPop(LinkedList list, unsigned int n) {
  if (list.count == 0) {
    return NULL;
  }
  ListNode *cur = list.head;
  while (cur->next != NULL) {
    if (cur->next->val == n) {
      cur->next = cur->next->next;
      list.count--;
      return n;
    }
  }

  return NULL;
}

typedef struct {
  unsigned int arrOffset;
  unsigned int vertCount;
  LinkedList entities;
} MeshInfo;
float *loadPlaneDataa() {
  static float data[] = {-0.500000, -0.500000, 0.000000, 0.000000, 0.000000,
                         0.500000,  -0.500000, 0.000000, 1.000000, 0.000000,
                         0.500000,  0.500000,  0.000000, 1.000000, 1.000000,
                         0.500000,  0.500000,  0.000000, 1.000000, 1.000000,
                         -0.500000, 0.500000,  0.000000, 0.000000, 1.000000,
                         -0.500000, -0.500000, 0.000000, 0.000000, 0.000000};

  return data;
}

float *loadCubeData(vec3 color) {
  static float data[] = {
      -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.5f,  -0.5f, -0.5f, 1.0f, 0.0f,
      0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,
      -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

      -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, 0.5f,  -0.5f, 0.5f,  1.0f, 0.0f,
      0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
      -0.5f, 0.5f,  0.5f,  0.0f, 1.0f, -0.5f, -0.5f, 0.5f,  0.0f, 0.0f,

      -0.5f, 0.5f,  0.5f,  1.0f, 0.0f, -0.5f, 0.5f,  -0.5f, 1.0f, 1.0f,
      -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
      -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, -0.5f, 0.5f,  0.5f,  1.0f, 0.0f,

      0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,
      0.5f,  -0.5f, -0.5f, 0.0f, 1.0f, 0.5f,  -0.5f, -0.5f, 0.0f, 1.0f,
      0.5f,  -0.5f, 0.5f,  0.0f, 0.0f, 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

      -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.5f,  -0.5f, -0.5f, 1.0f, 1.0f,
      0.5f,  -0.5f, 0.5f,  1.0f, 0.0f, 0.5f,  -0.5f, 0.5f,  1.0f, 0.0f,
      -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

      -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,
      0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
      -0.5f, 0.5f,  0.5f,  0.0f, 0.0f, -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f};

  return data;
}
