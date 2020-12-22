#include <stdio.h>  
#include <string.h>  
#include <stdlib.h>  

struct node{  
    int data;  
    struct node *next;  
}*head,*tail;  
  

void pushHead(int data){   
    struct node *newNode = (struct node*)malloc(sizeof(struct node));  
    newNode->data = data;  
  
    if(head == NULL){          
        head = newNode;  
        tail = newNode;  
        newNode->next = head;  
    }else {  
		tail->next = newNode;  
		tail = newNode; 
		tail->next = head;  
	}  
}  
  
 
void removeDuplicate() {  
	struct node *curr = head, *index = NULL, *temp = NULL;  
	if(head == NULL) {  
		printf("List is empty");  
	}  
	else {  
		do{  
		temp = curr;  
		index = curr->next;  
		while(index != head) {  
			if(curr->data == index->data) {  
				temp->next = index->next;  
			}  
			else{  
	      
	 		    temp = index;  
			}  
			index= index->next;  
		}  
		curr =curr->next;  
		}while(curr->next != head);   
	}  
}  

void display(){  
    struct node *curr = head;  
    if(head == NULL){  
        printf("List is empty");  
    }  
    else{  
		do{     
			printf("%d ", curr->data);  
			curr = curr->next;  
		}while(curr != head);  
		printf("\n");  
	}  
}  
      
int main()  {  
	int a,b,c;
	printf("Banyak isi link list: ");
	scanf("%d",&a);
	printf("Masukan isi link list: ");
	  
  for(int i=0;i<a;i++){
		scanf("%d",&b);
		pushHead(b);
	}
   removeDuplicate();  
   printf("List tanpa duplicates: \n");  
   display();  
     
   return 0;  
}  

