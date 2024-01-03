//
// Created by Berkan on 4/3/2023.
//
#define MAX 4
#ifndef UNTITLED3_BOARD_H
#define UNTITLED3_BOARD_H

struct node{
    int info;
    node * next;
    node * prev;
};

class Stack{
private:
    node * top;
public:
    char mystack[MAX];
    Stack();
    void push(int x);
    void pop(int &);
    bool isEmpty(void);
};



class Board{
private:
    Stack * head;
    Stack * tail;
    int xCnt;
    int oCnt;
public:
    bool noMove(char c, int step);
};
#endif //UNTITLED3_BOARD_H
