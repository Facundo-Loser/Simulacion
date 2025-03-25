#include <stdlib.h>
#include <stdio.h>

typedef struct Cliente{
  int timeArrived;
}Cliente;

typedef struct Queue{
  Cliente arr[100];
  int begin;
  int end;
}Queue;

Queue initialization() {
  Queue q;
  q.begin = 0;
  q.end = 0;
  return q;
}


void push(Cliente c, Queue* q) {
  q->arr[q->begin] = c;
  q->begin++;
  if(q->begin >= 100) {
    q->begin = 0;
  }
}

Cliente pop(Queue* q) {
  Cliente c = q->arr[q->end];
  q->end++;
  if (q->end >= 100) {
    q->end = 0;
  }
  return c;
}