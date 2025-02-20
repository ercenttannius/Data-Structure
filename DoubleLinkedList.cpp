#include<stdio.h>
#include<stdlib.h>

struct Node{
	int angka;
	Node *next;
	Node *prev;
}*head, *tail;

Node *createNode(int angka){
	Node *newNode = (Node*)malloc(sizeof(Node));
	
	newNode -> angka = angka;
	newNode -> next = NULL;
	newNode -> prev = NULL;
	
	return newNode;
}

void pushHead(int angka){
	Node *temp = createNode(angka);
	
	if(!head){
		head = tail = temp;
	}
	
	else{
		temp -> next = head;
		head -> prev = temp;
		head = temp;
	}
}

void pushTail(int angka){
	Node *temp = createNode(angka);
	
	if(!head){
		head = tail = temp;
	}
	
	else{
		tail -> next = temp;
		temp -> prev = tail;
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
		Node *temp = head -> next;
		head -> next = NULL;
		temp -> prev = NULL;
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
		Node *temp = tail -> prev;
		tail -> prev = NULL;
		temp -> next = NULL;
		free(tail);
		tail = temp;
	}
}

void popMid(int angka){
	if(!head){
		return;
	}
	
	else if(angka == head -> angka){
		popHead();
	}
	
	else if(angka == tail -> angka){
		popTail();
	}
	
	else{
		Node *curr = head -> next;
		while(curr -> angka != angka){
			curr = curr -> next;
		}
		
		Node *depan = curr -> prev;
		Node *belakang = curr -> next;
		curr -> prev = NULL;
		curr -> next = NULL;
		free(curr);
		depan -> next = belakang;
		belakang -> prev = depan;
		
	}
}

void print(){
	Node *curr = head;
	while(curr != NULL){
		printf("%d -> ", curr -> angka);
		curr = curr -> next;
	}
}

void pushMid(int angka){
    Node *temp = createNode(angka);

    if(!head){
        head = tail = temp;
    }

    else if(angka < head -> angka){
        pushHead(angka);
    }
    else if(angka > tail -> angka){
        pushTail(angka);
    }
    
    else{
        Node *curr = head -> next;
        while(angka > curr -> angka){
            curr = curr -> next;
        }
        Node *data = curr -> prev;
        curr -> prev = temp;
        data -> next = temp;
        temp -> next = curr;
        temp -> prev = data;
    }
}

int main(){
	pushMid(5);
	pushMid(7);
	pushMid(12);
	popMid(12);
	print();
	
}

