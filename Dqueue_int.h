#include<stdlib.h>
#include<stdbool.h>
#include<stdio.h>
struct Dqueue{
    int *que;
    int size;
    int front;
    int rear;
};
void init(struct Dqueue *queue,int size){
    queue->que = malloc(size*sizeof(int));
    queue->size = size;
    queue->front = queue->rear = -1;
}
bool isEmpty(struct Dqueue queue){
    if(queue.rear == -1){
        return true;
    }else{
        return false;
    }
}
bool isFull(struct Dqueue queue){
    if(queue.front == (queue.rear + 1) % queue.size){
        return true;
    }
    else{
        return false;
    }
}
void insertFromFront(struct Dqueue *queue,int val){
    if(!isFull(*queue)){
        if(isEmpty(*queue)){
            queue->front = queue->rear = 0;
            queue->que[queue->front] = val;
        }
        else{
            queue->front = (queue->size + queue->front - 1) % queue->size;
            queue->que[queue->front] = val;
        }
    }
}
void insertFromRear(struct Dqueue *queue,int val){
    if(!isFull(*queue)){
        if(isEmpty(*queue)){
            queue->front = queue->rear = 0;
            queue->que[queue->rear] = val;
        }
        else{
            queue->rear = (queue->size + queue->rear + 1) % queue->size;
            queue->que[queue->rear] = val;
        }
    }
}
int deleteFromFront(struct Dqueue *queue){
    if(!isEmpty(*queue)){
        if(queue->rear == queue->front){
            int data = queue->que[queue->front];
            queue->front = queue->rear = -1;
            return data;
        }
        else{
            int data = queue->que[queue->front];
            queue->front = (queue->size + queue->front + 1)%queue->size;
            return data;
        }
    }
}
int deleteFromRear(struct Dqueue *queue){
    if(!isEmpty(*queue)){
        if(queue->rear == queue->front){
            int data = queue->que[queue->front];
            queue->front = queue->rear = -1;
            return data;
        }
        else{
            int data = queue->que[queue->rear];
            queue->rear = (queue->size + queue->rear - 1)%queue->size;
            return data;
        }
    }
}
int peekRear(struct Dqueue queue){
    return queue.que[queue.rear];
}
int peekFront(struct Dqueue queue){
    return queue.que[queue.front];
}
