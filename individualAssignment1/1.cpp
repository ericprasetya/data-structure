#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Node{
    int angka;
    Node *next;
}*head , *tail , *curr;

Node *createNode(int angka){
    Node *newNode = (Node*) malloc(sizeof(Node));
    newNode->angka = angka;
    newNode->next  = NULL;
    return newNode;
}

void pushTail(int angka){
    Node *temp = createNode(angka);
    if(!head){
        head = tail = temp;
    }
    else{
        tail->next = temp;
        tail = temp;
    }
}

void printLinkedList(){
  Node *curr = head;
  while(curr !=NULL){
  printf("%d ", curr-> angka);
    curr= curr-> next;
    if(curr) printf("-> ");
  }
}

void sortLinkedList(){
  int temp;
  Node *curr;
  Node *ptr = head;
  while(ptr!= NULL){
    curr = ptr-> next;
    while(curr!= NULL){
      if(ptr->angka > curr->angka){
        temp = ptr->angka;
        ptr->angka = curr->angka;
        curr->angka = temp;
      }
      curr = curr->next;
    }
    ptr = ptr->next;
  }
}

int main(){
  int a ,b, c, d;
  printf("Banyaknya List ke-1 : "); scanf("%d" , &a);
  printf("Masukan list ke 1 :\n");
  for(int i=0 ; i<a ; i++){
    scanf(" %d" , &b);
    pushTail(b);
  }

  printf("Banyaknya List ke-2 : "); scanf("%d" , &c);
  printf("Masukan list ke 2 :\n");
  for(int i=0 ; i<c ; i++){
    scanf(" %d" , &d);
    pushTail(d);
  }
  sortLinkedList();
  printf("List Akhir :\n");
  printLinkedList();
printf("\n");
return 0;
}
