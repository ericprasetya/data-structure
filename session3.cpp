#include <stdio.h> // i/o
#include <string.h> // strcpy
#include <stdlib.h> // dynamic memory allocation

struct Node {
  char name[255];
  Node *next; // pointer ke node selanjutnya
  Node *prev;
} *head, *tail; // head: node pertama, tail: node terakhir

Node *createNode(const char *name) {
  Node *newNode = (Node*)malloc(sizeof(Node)); // alokasi memory
  strcpy(newNode->name, name);
  newNode->next = NULL; // awalnya tidak memiliki node selanjutnya
  newNode->prev = NULL;
  return newNode;
}


void popTail() {
  if(!head) { // tidak ada node
    return; 
  } else if(head == tail) { // kasus 1 node
    head = tail = NULL;
    free(head);
  } else { // kasus > 1 node
    // Initial: N <-18(head)-> <-15-> <-28(tail)-> N
    Node *temp = tail->prev; // N <-18(head)-> <-15(temp)-> <-28(tail)-> N
    tail->prev = temp->next = NULL; // N <-18(head)-> <-15(temp)-> N || N <-28(tail)-> N (avoid dangling ptr)
    tail = NULL; // N <-18(head)-> <-15(temp)-> N || N <-N-> N
    free(tail); // N <-18(head)-> <-15(temp)-> N 
    tail = temp; // N <-18(head)-> <-15(tail)-> N 
  }
}
void pushHead(const char *name) {
  Node *temp = createNode(name);

  if(!head) { // linked list kosong
    head = tail = temp;
  } else { // NULL <-4 (head)-> <-12-> <-14 (tail)-> NULL
    temp->next = head; // Buat link antara head dan temp
    head->prev = temp; // NULL <-10-> <-4 (head)-> <-12-> <-14 (tail)-> NULL 
    head = temp; // NULL <-10 (head)-> <-4-> <-12-> <-14 (tail)-> NULL
  }
}
void pushTail(const char *name) {
  Node *temp = createNode(name);

  if(!head) { // linked list kosong
    head = tail = temp;
  } else { // NULL <-18(head)-> <-28(tail)-> NULL
    temp->prev = tail; // Buat link antara tail dan temp
    tail->next = temp; // NULL <-18(head)-> <-28(tail)-> <-10-> NULL
    tail = temp; // NULL <-18(head)-> <-28-> <-10(tail)-> NULL
  }
}
void popHead() {
  if(!head) { // tidak ada node
    return; 
  } else if(head == tail) { // kasus 1 node
    free(head);
    head = tail = NULL;
  } else { // NULL <-18(head)-> <-15-> <-28(tail)-> NULL
    Node *temp = head->next; // NULL <-18(head)-> <-15(temp)-> <-28(tail)-> NULL
    head->next = temp->prev = NULL; // Putuskan hubungan head dan temp
    free(head); // Buang memory lama dari head
    head = temp; // Assign label head ke temp
  }
}

void pushMid(const char *name) {
  Node *temp = createNode(name);

  if(!head) { // no data
    head = tail = temp;
  } else if (strcmp(name, head->name) < 0) {
    pushHead(name); // kasus insert depan
  } else if(strcmp(name, tail->name) > 0) { 
    pushTail(name); // kasus insert belakang
  } else {
    Node *curr = head; // N <- Arif(head, curr) -><- Cecep -> <- Fajar(tail) -> N

    while(strcmp(name, curr->name) > 0) {
      curr = curr->next; // curr maju sampai kondisi while tidak terpenuhi
    }
    
    // Initial: Dodi -><- Elvan -><- Garry(curr)
    temp->prev = curr->prev; // Fajar->prev = Garry->prev, Fajar->prev = Elvan
    //                Fajar(temp)
    //                /     
    // Dodi -><- Elvan -><- Garry(curr)

    temp->next = curr; // Fajar->next = Garry
    //                Fajar(temp)
    //                /      \
    // Dodi -><- Elvan -><- Garry(curr)  

    temp->prev->next = temp; // Elvan->next = Fajar
    //                Fajar(temp)
    //                //      \
    // Dodi -><- Elvan    <- Garry(curr)  

    curr->prev = temp; // Garry->prev = Fajar 
    //                Fajar(temp)
    //                //      \\
    // Dodi -><- Elvan       Garry(curr)
  }
}
void popMid(const char *name) {
  if(!head) {
    return;
  } else if (strcmp(name, head->name) == 0) { 
    popHead(); // kasus nama di depan
  } else if(strcmp(name, tail->name) == 0) { 
    popTail(); // kasus nama di belakang
  } else {
    Node *curr = head; // N <- Arif(head, curr) -><- Cecep -> <- Fajar(tail) -> N

    while(strcmp(name, curr->name) != 0) {
      if(!curr->next) { // kita sudah di tail dan node selanjutnya NULL
        puts("Can't find the person!"); 
        return;
      }
      curr = curr->next; // traverse terus selama kondisi while terpenuhi
    }
 
    // Initial: N <- Arif(head) -><- Cecep(curr) -><- Fajar(tail) -> N
    // Result: N <- Arif(head) -><- Fajar(tail) -> N
    curr->prev->next = curr->next; // Arif->next = Fajar
    curr->next->prev = curr->prev; // Fajar->prev = Arif
    curr->next = curr->prev = NULL; // cecep jadi jomblo
    free(curr); // bebaskan memory yang sudah diassign untuk node curr
    curr = NULL; // remove value
  }
}
void printLinkedList() {
  Node *curr = head; // curr adalah index yang akan berjalan
  // 30 (head) -> 20 -> 15 -> 40 (tail) -> NULL
  //  curr
                                          
  while(curr) { // selama curr bukan NULL
    printf("%s -> ", curr->name); // print data
    curr = curr->next; // curr akan berjalan ke node selanjutnya
  }
  printf("NULL\n");
}

int main (){
  pushMid("cecep");
  pushMid("arif");
  pushMid("budi");
  pushMid("joko");
  pushMid("fahri");
  pushMid("dono");
  printLinkedList();

  return 0;
}