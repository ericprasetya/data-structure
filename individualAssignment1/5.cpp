#include <stdio.h>
#include <stdlib.h>

struct Node {
  int angka;
  Node *next; 
} *head, *tail; 

Node *createNode(int angka) {
  Node *newNode = (Node*)malloc(sizeof(Node)); 
  newNode->angka = angka;
  newNode->next = NULL; 
  return newNode;
}

void pushHead(int angka) {
  Node *temp = createNode(angka); 

  if(!head) { 
    head = tail = temp; 
  } else { 
    temp->next = head; 
    head = temp; 
  }
}

void pushTail(int angka) {
  Node *temp = createNode(angka); 

  if(!head) { 
    head = tail = temp; 
  } else { 
    tail->next = temp; 
    tail = temp; 
  }
}

void printLinkedList() {
  Node *curr = head; 
  while(curr) { 
    printf("%d ", curr->angka); 
    curr = curr->next;
	if(curr) printf("-> ");
  }
  
//  printf("NULL\n");
}

int count=0;
void searchLinkedList(int b){
  Node *curr = head;
  while(curr){
    count++;
    if(count == b)
    printf("Node ke-%d : %d\n" , b , curr->angka);
    curr= curr-> next;
  }
}

int main(){
  int m , a , b;

  printf("Banyaknya isi Link List : "); scanf("%d" , &m);
  printf("Masukan isi link list :\n");
  for(int i=0 ; i<m ; i++){
    scanf(" %d" , &a);
    pushHead(a);
  }
  printf("Cari node ke (dari belakang): "); scanf("%d" , &b);
  searchLinkedList(b);

  printf("\n");
  return 0;
}
