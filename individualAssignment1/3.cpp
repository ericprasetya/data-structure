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

void printLinkedList(int n){
  int count=0;
  struct Node *mid=head;
  struct Node *prev;
  int stop=0;
  if(n%2==0){
  	stop =n/2-1;
  }else if(n%2!=0){
  stop = n/2;
  	}
  while(count<stop){
	mid=mid->next; 
  	head=head->next;
  	count++;
  }
  if(mid!=NULL){
  	if(n%2!=0){
  	printf("The Middle Element is %d\n", mid->number);
	  }else{
	  	prev=mid->next;
	  	printf("The Middle Element(s) are %d & %d\n", prev->number, mid->number);
	  	printf("The Middle Element is %.2lf\n", (double)(prev->number+mid->number)/2.00);
	  }
  }
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
  printLinkedList(data);

//printf("\n");
return 0;
}