#include <assert.h>
#include <malloc/_malloc_type.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "C_Cpp.h"

typedef struct LinkedList {
  int data;
  struct LinkedList *next;
} LL;

void printLL(LL *head) {
  if (head != NULL) {
    printf("%d", head->data);
    head = head->next;
  }
  while (head != NULL) {
    printf("->%d", head->data);
    head = head->next;
  }
  printf("\n");
}

void pushLastLL(LL *head, int value) {
  assert(head != NULL);
  printLL(head);

  LL *tail = head;
  while (tail->next != NULL)
    tail = tail->next;
  LL *insert = (LL *)malloc(sizeof(LL));
  insert->next = NULL;
  insert->data = value;
  tail->next = insert;
  printLL(head);
}

void pushStartLL(LL **head, int value) {
  LL *newStart = (LL *)malloc(sizeof(LL));
  newStart->data = value;
  newStart->next = *head;
  *head = newStart;
  printLL(*head);
}

void insertStartLL(LL **head, int *values, int count) {
  LL *newStart = (LL *)malloc(sizeof(LL));
  newStart->data = values[0];
  newStart->next = NULL;

  LL *itr = newStart;
  for (int i = 1; i < count; i++) {
    LL *next = (LL *)malloc(sizeof(LL));
    next->data = values[i];
    next->next = NULL;
    itr->next = next;
    itr = next;
  }

  itr->next = *head;
  *head = newStart;
  printLL(*head);
}

void insertLastLL(LL *head, int *values, int count) {
  assert(head != NULL);
  LL *tail = head;
  while (tail->next != NULL)
    tail = tail->next;
  for (int i = 0; i < count; i++) {
    LL *insert = (LL *)malloc(sizeof(LL));
    insert->next = NULL;
    insert->data = values[i];
    tail->next = insert;
    tail = tail->next;
  }
  printLL(head);
}

int popFirstLL(LL **head) {
  LL *nextNode = (*head)->next;
  int retVal = (*head)->data;
  free(*head);
  *head = nextNode;
  printLL(*head);
  return retVal;
}

int popLastLL(LL *head) {
  int retVal = -1;
  LL *lastNode;
  if (head->next != NULL) {
    while (head->next->next != NULL) {
      head = head->next;
    }
    lastNode = head->next;
    retVal = lastNode->data;
    head->next = NULL;
  } else {
    retVal = head->data;
    lastNode = head;
    head = NULL;
  }
  free(lastNode);
  printLL(head);
  return retVal;
}

int removeAtIndexLL(LL **head, int index) {
  if (index == 0) {
    return popFirstLL(head);
  }
  LL *current = *head;
  LL *remove = NULL;
  for (int i = 0; i < index - 1; i++) {
    if (current->next == NULL) {
      return -1;
    }
    current = current->next;
  }
  if (current->next == NULL) {
    return -1;
  }
  remove = current->next;
  current->next = remove->next;
  int retVal = remove->data;
  free(remove);
  return retVal;
}

void removeByValueLL(LL **head, int value) {
  if ((*head)->data == value) {
    LL *newHead = (*head);
    free(*head);
    *head = newHead;
  }
  LL *current = (*head);

  while (current->next != NULL) {
    if (current->next->data == value) {
      current->next = current->next->next;
      free(current->next);
    }
    current = current->next;
  }
}

void testC() {
  printf("C Test\n");
  LL *head = NULL;
  head = (LL *)malloc(sizeof(LL));
  head->data = 1;
  head->next = NULL;
  LL *one = (LL *)malloc(sizeof(LL));
  one->data = 0;
  one->next = NULL;
  head->next = one;
  pushLastLL(head, 400);
  int array10[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 110};
  insertLastLL(head, (int *)&array10, 10);
  pushStartLL(&head, 1000);
  insertStartLL(&head, (int *)&array10, 5);
}