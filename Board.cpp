// Please copy and paste your Board.cpp file content to here.
// Please do not copy Board.h file content, but of course you will #include it at the beginning of Board.cpp


#include "Board.h"
#include <iostream>
using namespace std;

Board::Board() {
    head = nullptr; //initialize the head pointer to null
    tail = nullptr; //initialize the tail pointer to null
    xCnt = 0; //initialize the x count to 0
    oCnt = 0; //initialize the o count to 0
}

void Board::movePiece(int start, int end){
    Slot * curr = head; //initialize a pointer to the head of the linked list
    char c;
    int step_size;
    int index;
    for (int i = 0; i < start; i++){ //traverse the linked list until reaching the starting point
        curr = curr->next;
        index = i;
    }
    curr->mystack.pop(c); //pop the top character from the stack at the starting point
    if (end > start){ //if moving to the right
        step_size = end - start;
        for (int i = 0; i < step_size; i++){ //traverse the linked list to the right by step_size
            curr = curr->next;
        }
        curr->mystack.push(c); //push the character onto the stack at the ending point
    }
    else if (start > end){ //if moving to the left
        step_size = start - end;
        for (int i = 0; i < step_size; i++){ //traverse the linked list to the left by step_size
            curr = curr->prev;
        }
        curr->mystack.push(c); //push the character onto the stack at the ending point
    }
    if (curr->mystack.isFull() == true){ //if the stack at the ending point is full
        destroySlot(index); //remove the slot at the starting point
    }
}

bool Board::validMove(char c, int start, int step, int direction) {
    Slot * curr = head; //initialize a pointer to the head of the linked list
    Slot * temp;
    for (int i= 0 ; i < start; i++){ //traverse the linked list until reaching the starting point
        curr = curr->next;
    }
    if (direction == 0){ //if moving to the left
        int distance = start - step;
        for (int i = 0; i < distance; i++){ //traverse the linked list to the left by distance
            if (curr == nullptr){ //if the end of the linked list is reached
                return true; //return true
            }
            curr = curr->prev;
        }
        return false; //otherwise return false
    }
    else if (direction == 1){ //if moving to the right
        int distance = step - start;
        for (int i = 0; i < distance; i++){ //traverse the linked list to the right by distance
            if (curr == nullptr){ //if the end of the linked list is reached
                return true; //return true
            }
            curr = curr->next;
        }
        return false; //otherwise return false
    }
    return true;
}

// This function creates a new slot at the beginning of the linked list and fills it with a given character for a given number of times.
void Board::createSlotBegin(char c, int num) {

    Slot * ptr;

// If the linked list is empty, create a new slot and make it both head and tail.
    if (head == nullptr){
        head = new Slot();
        tail = head;
        head->prev = nullptr;
        head->next = nullptr;
        tail->prev = nullptr;
        tail->next = nullptr;
    }
// If the linked list is not empty, create a new slot and make it the new head.
    else {
        ptr = new Slot();
        ptr->prev = nullptr;
        ptr->next = head;
        head = ptr;
        head->prev = nullptr;
        head->next = ptr->next;
        ptr = head;
    }

// Fill the new slot with the given character for a given number of times.
    for (int i = 0 ; i < num; i++){
        ptr->mystack.push(c);
    }

// Move to the tail of the linked list.
    while (ptr->next != nullptr){
        ptr = ptr->next;
    }
// Update the tail of the linked list.
    tail = ptr;
    tail->next = nullptr;
}



// This function creates a new slot at the end of the linked list and fills it with a given character for a given number of times.
void Board::createSlotEnd(char c, int num) {
// If the linked list is empty, create a new slot and make it both head and tail.
    if (head == nullptr){
        head = new Slot();
        tail = head;
    }
// If the linked list is not empty, move to the tail and create a new slot after it.
    else{
        Slot * curr = head;
        while (curr->next != nullptr){
            curr = curr->next;
        }

        curr->next = new Slot();
        tail = curr->next;
    }

// Fill the new slot with the given character for a given number of times.
    for (int i = 0; i < num; i++){
        tail->mystack.push(c);
    }
}

// This function creates a new empty slot at the end of the linked list.
void Board::createEmptySlotEnd() {
    Slot * curr = head;
    // If the linked list is empty, create a new slot and make it both head and tail.
    if (head == nullptr){
        head = new Slot();
        tail = head;
        curr->next = nullptr;
        curr->prev = nullptr;
        curr= head;
    }

// Move to the tail of the linked list and create a new empty slot after it.
    while (curr->next != nullptr){
        curr = curr->next;
    }
    curr->next = new Slot();
    tail = curr->next;

}

bool Board::targetSlotFull(int index) const {
    Slot* curr = head;
    int i =0;
// Move to the target slot.
    while (curr->next != nullptr && i < index) {
        curr = curr->next;
        i++;
    }
// Check if the target slot is full or not and return the result.
    if(curr->mystack.isFull()){
        return true;
    }
    else if(!curr->mystack.isFull()){
        return false;
    }
}

void Board::destroySlot(int index) {
    Slot * ptr = head;
    Slot * yildiz = head;

    // traverse to the slot to be destroyed
    for(int i = 0; i < index; i++){
        ptr = ptr->next;
    }

    // traverse to the tail slot
    while (yildiz->next != NULL){
        yildiz = yildiz->next;
    }

    // update tail slot
    tail = yildiz;

    // if the slot to be destroyed is the head slot
    if (ptr == head){
        head = ptr->next;
        delete ptr;
    }

    // if the slot to be destroyed is the tail slot
    if (ptr == tail){
        tail = ptr->prev;
        delete ptr;
    }

    // update the pointers to remove the slot from the linked list
    ptr->prev->next = ptr->next;
    ptr->next->prev = ptr->prev;
    delete ptr; // delete the slot from memory
}

void Board::printBoard() {
    Slot *ptr = nullptr;
    string arr[3];

    char c;

    // traverse through the slots from top to bottom
    for (int i = 2; i >= 0; i--){
        ptr = head;

        // traverse through the stacks in the slot
        while (ptr->next != nullptr) {
            CharStack stack_example = (ptr->mystack);
            CharStack stack_example2 = (ptr->mystack);
            int counter = 0;

            // traverse through the characters in the stack
            while (stack_example.isEmpty() == false) {
                stack_example.pop(c);
                counter++;
            }

            // add the character to the row array if its position matches the current row being printed
            if (i+1 <= counter){
                stack_example2.pop(c);
                arr[i] += c;
            }
            else{
                arr[i] += " ";
            }

            ptr = ptr->next;
        }

        // if the last slot is being printed
        if (ptr->next == NULL){
            CharStack stack_example = (ptr->mystack);
            CharStack stack_example2 = (ptr->mystack);
            int counter = 0;

            // traverse through the characters in the stack
            while (stack_example.isEmpty() == false) {
                stack_example.pop(c);
                counter++;
            }

            // add the character to the row array if its position matches the current row being printed
            if (i+1 <= counter){
                stack_example2.pop(c);
                arr[i] += c;
            }
            else{
                arr[i] += " ";
            }
        }
        // print the row array
        cout << arr[i] << endl;
    }
}

void Board::clearBoard() {
    Slot * ptr = head;

    // traverse through the linked list and delete each slot
    while (ptr->next != nullptr){
        ptr = ptr->next;
        delete head;
        head = ptr;
    }

    // delete the last slot
    delete head;
}


// Function to check if there is a valid move for a given player and step
bool Board::noMove(char c, int step){
// Initialize a pointer to the first slot of the board
    Slot * ptr = head;
// Initialize another pointer to traverse the board to find the last slot
    Slot * temp = head;
    int say = 0;
// Find the last slot and count the number of slots in the board
    while (temp->next != NULL){
        temp = temp->next;
        say++;
    }
// Check if there is a valid move for the player in the right direction
    if(validMove(c, say, step, 1)){
        return false;
    }
// Check if there is a valid move for the player in the left direction
    else if (validMove(c, say, step, 0)){
        return false;
    }
// If there is no valid move for the player in either direction, return true
    return true;
}

bool Board::evaluateGame() {
    char c;

    // Start from the first slot of the board
    Slot * curr = head;
// Traverse the board and count the number of 'x' and 'o' symbols
    while (curr->next != nullptr){
        CharStack copy_stack(curr->mystack);
        while (copy_stack.isEmpty() == false){
            copy_stack.pop(c);
            if (c == 'x'){
                xCnt += 1;
            }
            else if (c == 'o'){
                oCnt += 1;
            }
        }
    }
// If the number of 'o' symbols is greater than the number of 'x' symbols, return 1
    if (oCnt > xCnt){
        return 1;
    }
// If the number of 'x' symbols is greater than the number of 'o' symbols, return 2
    else if (xCnt > oCnt){
        return 2;
    }
// If there are equal number of 'x' and 'o' symbols, return 3
    else{
        return 3;
    }
}

