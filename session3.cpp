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


void pushHead(const char *name) {
  Node *temp = createNode(name);

  if(!head) { // linked list kosong
    head = tail = temp;
  } else { // >= 1 node
    // Initial: NULL <-4 (head)-> <-8-> <-12-> <-14 (tail)-> NULL
    temp->next = head;
    head->prev = temp; // NULL <-10-> <-4 (head)-> <-8-> <-12-> <-14 (tail)-> NULL 
    head = temp; // NULL <-10 (head)-> <-4-> <-8-> <-12-> <-14 (tail)-> NULL
  }
}
void pushTail(const char *name) {
  Node *temp = createNode(name);

  if(!head) { // linked list kosong
    head = tail = temp;
  } else { // >= 1 node
    // Initial: NULL <-18(head)-> <-24-> <-32-> <-28(tail)-> NULL
    temp->prev = tail;
    tail->next = temp; // NULL <-18(head)-> <-24-> <-32-> <-28(tail)-> <-10-> NULL
    tail = temp; // NULL <-18(head)-> <-24-> <-32-> <-28-> <-10(tail)-> NULL
  }
}
void popHead() {
  if(!head) { // tidak ada node
    return; 
  } else if(head == tail) { // kasus 1 node
    head = tail = NULL;
    free(head);
  } else { // kasus > 1 node
    // Initial: NULL <-18(head)-> <-15-> <-28(tail)-> NULL
    Node *temp = head->next; // NULL <-18(head)-> <-15(temp)-> <-28(tail)-> NULL
    head->next = temp->prev = NULL; // N <-18(head)-> N || N <-15(temp)-> <-28(tail)-> N
    head = NULL; // N <-N-> N || N <-15(temp)-> <-28(tail)-> N
    free(head); // N <-15(temp)-> <-28(tail)-> N
    head = temp; // N <-15(head)-> <-28(tail)-> N
  }
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
void pushMid(const char *name) {
  Node *temp = createNode(name);

  if(!head) { // no data
    head = tail = temp;
  } else if (strcmp(name, head->name) < 0) { // kasus insert di depan
    pushHead(name);
  } else if(strcmp(name, tail->name) > 0) { // kasus insert di belakang
    pushTail(name);
  } else { // kasus di tengah
    // N <- Arif(head) -><- Cecep -> <- Fajar(tail) -> N
    Node *curr = head; // N <- Arif(head, curr) -><- Cecep -> <- Fajar(tail) -> N

    while(strcmp(name, curr->name) > 0) {
      curr = curr->next;
    }
 
    // Initial: N <- Arif(head) -><- Cecep -><- Fajar(curr, tail) -> N
    // Result: N <- Arif(head) -><- Cecep -><- Dodi(temp) -><- Fajar(curr, tail) -> N
    
    // Initial: Dodi -><- Elvan -><- Garry(curr) -><- NULL
    temp->prev = curr->prev;   
    //                Fajar(temp)
    //                /     
    // Dodi -><- Elvan -><- Garry(curr) -><- NULL

    temp->next = curr;
    //                Fajar(temp)
    //                /      
    // Dodi -><- Elvan -><- Garry(curr) -><- NULL    

    temp->prev->next = temp; // Elvan->next -> Fajar
    //                Fajar(temp)
    //                //      
    // Dodi -><- Elvan    <- Garry(curr) -><- NULL    

    curr->prev = temp; // Garry->prev = Fajar 
    //                Fajar(temp)
    //                //      
    // Dodi -><- Elvan       Garry(curr) -><- NULL  
  }
}
void popMid(const char *name) {
  if(!head) { // no data
    return;
  } else if (strcmp(name, head->name) == 0) { // kasus nama di depan
    popHead();
  } else if(strcmp(name, tail->name) == 0) { // kasus nama di belakang
    popTail();
  } else { // kasus di tengah
    // N <- Arif(head) -><- Cecep -> <- Fajar(tail) -> N
    Node *curr = head; // N <- Arif(head, curr) -><- Cecep -> <- Fajar(tail) -> N

    // Initial: N <- Arif(head) -><- Cecep(curr) -><- Fajar(tail) -> N
    // Result: N <- Arif(head) -><- Fajar(tail) -> N

    // curr->next != NULL (artinya kita sudah di tail)
    // curr != NULL (artinya kita satu node setelah tail)
    // NOTE: Biasakan sebelum cek nilai node, cek dulu apakah nodenya ada
    while(curr && strcmp(name, curr->name) != 0) {
      curr = curr->next; // traverse terus selama kondisi while terpenuhi
    }

    if(!curr) { // kita sudah ada di node setelah tail
      puts("Can't find the person!"); // artinya kita engga nemu nama yang dicari
      return; // langsung return aja (engga jalanin code di bawah)
    }
 
    curr->prev->next = curr->next; // Arif->next = Fajar
    curr->next->prev = curr->prev; // Fajar->prev = Arif
    curr->next = curr->prev = NULL; // cecep jadi jomblo
    curr = NULL; // remove value
    free(curr);
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