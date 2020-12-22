#include <stdio.h> // i/o
#include <string.h> // strcpy
#include <stdlib.h> // dynamic memory allocation

struct Node {
  char name[255];
  int score;
  Node *next; // pointer ke node selanjutnya
} *head, *tail; // head: node pertama, tail: node terakhir

Node *createNode(const char *name, int score) {
  Node *newNode = (Node*)malloc(sizeof(Node)); // alokasi memory
  strcpy(newNode->name, name);
  newNode->score = score;
  newNode->next = NULL; // awalnya tidak memiliki node selanjutnya
  return newNode;
}
// head = 5 // 5 adalah head
// tail = 5 // 5 adalah tail
// head = tail = temp // temp adalah head dan tail

void pushHead(const char *name, int score) {
  // Kita mau pushHead A1 di linked list berikut:
  // A2 (head) -> B3 -> C4 (tail) -> NULL 

  // A1 (temp) -> NULL || Node *temp = createNode(name, score)
  // A1 (temp) -> A2 (head) -> B3 -> C4 (tail) -> NULL || temp->next = head
  // A1 (head) -> A2 -> B3 -> C4 (tail) -> NULL || head = temp

  Node *temp = createNode(name, score); // buat node baru

  if(!head) { // linked list kosong (0 node)
    head = tail = temp; // temp akan menjadi head dan tail
  } else { // >= 1 node
    temp->next = head; // node setelah temp adalah head
    head = temp; // head baru adalah temp
  }
}
void pushTail(const char *name, int score) {
  // Kita mau pushTail D10 di linked list berikut:
  // A2 (head) -> B3 -> C4 (tail) 

  // D10 (temp) -> NULL || Node *temp = createNode(name, score)
  // A2 (head) -> B3 -> C4 (tail) -> D10 (temp) -> NULL || tail->next = temp
  // A2 (head) -> B3 -> C4 -> D10 (tail) -> NULL || tail = temp

  Node *temp = createNode(name, score); // buat nodenya

  if(!head) { // linked list kosong (0 node)
    head = tail = temp; // temp akan menjadi head dan tail
  } else { // >= 1 node
    tail->next = temp; // tail lama -> next adalah node baru
    tail = temp; // temp akan menjadi tail (node terakhir)
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

void popHead() {
  if(!head) { // jika tidak ada node
    return; // return (tidak ngapa2in)
  } else if(head == tail) { // untuk kasus 1 node di pophead bsa diabaikan
    head = tail = NULL; // cuman biar sesuai dengan poptail, bsa dimasukin
    free(head); // intinya kalau cuma ada 1 node, set nilainya jadi null dan free memorynya
  } else {
    // INITIAL: 98 (head) -> 100 -> 95 -> 97 (tail) -> NULL
    Node *temp = head; // 98 (head, temp) -> 100 -> 95 -> 97 (tail) -> NULL
    head = temp->next; // 98 (temp) -> 100 (head) -> 95 -> 97 (tail) -> NULL
    temp->next = NULL; // 98 (temp) -> NULL || 100 (head) -> 95 -> 97 (tail) -> NULL
    free(temp); // 100 (head) -> 95 -> 97 (tail) -> NULL
  }

  // INITIAL (kasus 1 node, tanpa if kedua): 150 (head, tail) -> NULL
  // Node *temp = head; // 150 (temp, head, tail) -> NULL
  // head = temp->next; // 150 (temp, tail) -> NULL (head)
  // temp->next = NULL; // 150 (temp, tail) -> NULL (head)
  // free(temp); // NULL (head)
}

void popTail() {
  if(!head) { // jika tidak ada node
    return; // return (tidak ngapa2in)
  } else if(head == tail) { // 50 (head, tail) -> NULL
    head = tail = NULL; // kosongkan nilainya
    free(head); // free memory yang sudah dialokasikan
  } else {
    // INITIAL: 50 (head) -> 54 -> 73 -> 36 (tail) -> NULL
    Node *temp = head; // 50 (head, temp) -> 54 -> 73 -> 36 (tail) -> NULL

    while(temp->next != tail) { // selama node selanjutnya bukan tail
      temp = temp->next; // loop terus
    }

    // 50 (head) -> 54 -> 73 (temp) -> 36 (tail) -> NULL
    temp->next = NULL; // 50 (head) -> 54 -> 73 (temp) -> NULL || 36 (tail) -> NULL
    free(tail); // 50 (head) -> 54 -> 73 (temp) -> NULL
    tail = temp; // 50 (head) -> 54 -> 73 (tail, temp) -> NULL
  }

  // INITIAL (kasus 1 node, kalau engga ada if kedua): 150 (head, tail) -> NULL
  // Node *temp = head; // 150 (temp, head, tail) -> NULL

  // while(temp->next != tail) {
  //   temp = temp->next; // loop terus
  // }

  // 150 (head, tail) -> NULL -> temp
  // head = temp->next; // 150 (tail) -> NULL -> .... -> temp -> head
  // temp->next = NULL; // 150 (tail) -> NULL -> .... -> temp -> NULL
  // free(temp); // 150 (tail) -> NULL -> .... -> NULL -> NULL
}

int main() {
  pushHead("Darnell", 95); // 95 (head, tail) -> NULL
  pushTail("whisper0", 97); // 95 (head) -> 97 (tail) -> NULL
  pushHead("pai", 100); // 100 (head) -> 95 -> 97 (tail) -> NULL
  pushHead("romario", 98); // 98 (head) -> 100 -> 95 -> 97 (tail) -> NULL
  popHead(); // 100 (head) -> 95 -> 97 (tail) -> NULL
  popTail(); // 100 (head) -> 95 (tail) -> NULL
  popTail(); // 100 (head, tail) -> NULL
  popHead(); // NULL
  printLinkedList();

  return 0;
}