#include "../inc/sceneManager.h"
#include <stdbool.h>
#include <stdio.h>

// Tests of scenemanagers nextID Queue
void testNextIDQueue() {
  IDQueue *q = createQueue(5);
  unsigned int actual;
  unsigned int expected;
  bool passed = true;
  expected = 0;
  actual = q->len;
  if (expected != actual) {
    printf("createQueue failed expected len = %u was %u\n", expected, actual);
    passed = false;
  }
  queuePush(q, 1);
  expected = 1;
  actual = q->len;
  if (expected != actual) {
    printf("pushQueue failed expected len = %u was %u\n", expected, actual);
    passed = false;
  }
  expected = 1;
  actual = q->queue[0];
  if (expected != actual) {
    printf("pushQueue failed expected %u was %u\n", expected, actual);
    passed = false;
  }
  expected = 1;
  actual = queuePop(q);
  if (expected != actual) {
    printf("popQueue failed expected %u was %u\n", expected, actual);
    passed = false;
  }
  expected = 0;
  actual = q->len;
  if (expected != actual) {
    printf("popQueue failed expected len = %u was %u\n", expected, actual);
    passed = false;
  }

  for (int i = 0; i < 10; i++) {
    queuePush(q, i);
  }
  for (int i = 0; i < 10; i++) {
    if (q->queue[i] != i) {
      printf("queuePush failed on realocat test\n");
      passed = false;
      break;
    }
  }
  for (int i = 0; i < 10; i++) {
    expected = i;
    actual = queuePop(q);
    if (expected != actual) {
      printf("popQueue1 failed expected %d was %d\n", expected, actual);
      passed = false;
    }
  }
  for (int i = 0; i < 10; i++) {
    queuePush(q, i);
  }
  for (int i = 0; i < 5; i++) {
    expected = i;
    actual = queuePop(q);
    if (expected != actual) {
      printf("popQueue2 failed expected %d was %d\n", expected, actual);
      passed = false;
    }
  }
  for (int i = 0; i < 5; i++) {
    queuePush(q, i);
  }
  for (int i = 0; i < 10; i++) {
    expected = i;
    actual = q->queue[i];
    if (expected != actual) {
      printf("pushQueue failed on wrap test\n");
      passed = false;
    }
  }

  if (passed) {
    printf("Test IDQueue: PASSED\n");
  } else {
    printf("Test IDQueue: FAILED\n");
  }
}
