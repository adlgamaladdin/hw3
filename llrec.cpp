#include "llrec.h"

//*********************************************
// Provide your implementation of llpivot below
//*********************************************
void llpivot(Node *&head, Node *&smaller, Node *&larger, int pivot){
    if(head == nullptr){ // base case
        smaller = nullptr;
        larger = nullptr;
        return;
    }
    Node* nextNode = head->next;
    head->next = NULL;
    llpivot(nextNode, smaller, larger, pivot);

    if(head->val > pivot){ // current is larger than pivot
        head->next = larger;  
        larger = head;  
    }

    if(head->val <= pivot){ // current is smaller thgan pivot
        head->next = smaller;
        smaller = head;
    }
    head = nullptr; //ensures that head list does not exist after function terminates
}


