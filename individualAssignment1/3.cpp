#include <stdio.h>
#include <stdlib.h>

struct Node{
    int number;
    Node *next;
}*head , *tail , *curr, *mid;

Node *createNode(int number){
    Node *newNode = (Node*) malloc(sizeof(Node));
    newNode->number = number;
    newNode->next  = NULL;
    return newNode;
}

void pushHead(int number){
  Node *temp = createNode(number);

  if(!head){
    head=tail=temp;
  } else{
    temp->next = head;
    head=temp;
  }
}

void printLinkedList(){
  int count=0;
  struct Node *mid=head;
  struct Node *prev=head;
  while(head!=NULL){
  	count++;
	if(count%2==0)
	mid=mid->next; 
  	head=head->next;
  }
  if(mid!=NULL)
  printf("The Middle Element is %d\n", mid->number);
}

int main(){
  int data , a , b;
  printf("Banyaknya isi Link List: "); 
  scanf("%d" , &data);
  printf("Masukan isi Link List: ");
  for(int i=0 ; i<data ; i++){
    scanf(" %d" , &a);
    pushHead(a);
  }
  printLinkedList();

printf("\n");
return 0;
}