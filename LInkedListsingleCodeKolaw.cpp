#include <stdio.h>
#include <stdlib.h>

struct Node {
    int angka;
    struct Node *next;
} *head, *tail;

Node *createNode(int angka) {
    Node *newNode = (Node*)malloc(sizeof(Node)); // Perbaikan: Gunakan pointer
    newNode->angka = angka;
    newNode->next = NULL;
    
    return newNode;
}

void pushHead(int angka) {
    Node *temp = createNode(angka);
    if (!head) {
        head = tail = temp;
    } else {
        temp->next = head;
        head = temp;
    }
}

void pushTail(int angka) {
    Node *temp = createNode(angka);
    if (!head) {
        head = tail = temp;
    } else {
        tail->next = temp;
        tail = temp;
    }
}

void popHead(){
	if(!head){
		return;
	}
	else if(head == tail){
		free(head);
		head = tail = NULL;
	}
	else{
		Node *temp;
		temp = head -> next;
		head -> next = NULL;
		free(head);
		head = temp;
	}
}

void popTail(){
	if(!head){
		return;
	}
	else if(head == tail){
		free(head);
		head = tail = NULL;
	}
	else{
		Node *temp = head;
		
		while(temp -> next != tail){
			temp = temp -> next;
		}
		temp -> next = NULL;
		free(tail);
		tail = temp;
	}
}



void print(){
	Node *curr = head;
	
	while(curr != NULL){
		printf("%d -> ", curr -> angka);
		curr = curr -> next;
	}
}

int main() {
    pushTail(76);
    pushTail(90);
    pushTail(45);
	//pushTail(45);
     //popHead();
    popTail();
    print();

    return 0;
}

