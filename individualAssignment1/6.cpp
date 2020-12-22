#include <stdio.h>
#include <stdlib.h>

struct Node {
  int score;
  Node *next; 
} *head, *tail; 

Node *createNode(int score) {
  Node *newNode = (Node*)malloc(sizeof(Node)); 
  newNode->score = score;
  newNode->next = NULL; 
  return newNode;
}

void pushHead(int score) {
  Node *temp = createNode(score); 

  if(!head) { 
    head = tail = temp; 
  } else { 
    temp->next = head; 
    head = temp; 
  }
}

void pushTail(int score) {
  Node *temp = createNode(score); 

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
    printf("%d ", curr->score); 
    curr = curr->next;
	if(curr) printf("-> ");
  }
  printf("\n");
}



int main(){
  int a,b,c;
  printf("Banyak isi link list: ");
  scanf("%d",&a);
  printf("Masukan isi link list(secara ascending): ");
  
  for(int i=0;i<a;i++){
  	scanf("%d",&b);
  	pushHead(b);
  }
	printLinkedList();
	
	return 0;

}
