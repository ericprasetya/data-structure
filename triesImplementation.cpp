#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//kita tentukan dulu apa yang mau kita isi kedalam Tries
//bila huruf kecil saja maka size = 26, bila dengan huruf besar maka size = 52, bila ditambah dengan angka maka size = 62

//sebagai contoh pakai huruf kecil saja
const int SIZE = 26;

//buat node Triesnya dengan struct
struct Tries{
  struct Tries *children[SIZE]; //ini merupakan penunjuk untuk tiap huruf kecil dari a-z
  bool isEndOfWord; // penanda bila string/ kata sudah berakhir di node/huruf tersebut
  char key; // ini hanya untuk contoh saja agar lebih mudah buat print nya, sebenarnya tidak perlu menggunakan ini
};

//buat fungsi untuk createNode dulu
struct Tries *createNode(char key){
  struct Tries *newNode = (Tries *) malloc(sizeof(Tries));
  newNode->isEndOfWord = false;
  newNode->key = key; // kita tandai dengan ini dulu nanti akan diganti saat insert
  for(int i = 0; i < SIZE; i++){
    newNode->children[i] = NULL;
  }
  return newNode;
}

//misal insert 'there'
//'a' -> 97
void insert(Tries *root, const char word[]){
  struct Tries *curr = root; // kita pakai curr untuk looping Tries kita
  int index = 0; // untuk index children
  for (int i = 0; i < strlen(word); i++)
  {
    index = word[i] - 'a'; // agar huruf alfabet bisa kita jadikan index dalam children kita
    if(curr->children[index] == NULL){
      //jika null kita bentuk nodenya
      curr->children[index] = createNode(word[i]);
    }
    curr= curr->children[index]; // lanjut ke anaknya
  }
  curr->isEndOfWord = true; //kita tandai sebagai akhir string bila sudah mencapai node yang terakhir
}

//misal ada 'there' di Tries kita
//search 'tos'
//search 'the'

bool search(Tries *root, const char word[]){
  //konsep sama dengan insert hanya saja kita return true/false
  if(!root) return false; // kalau kosong kita langsung return false
  struct Tries *curr = root; // kita pakai curr untuk looping
  int index = 0; // untuk index children
  for (int i = 0; i < strlen(word); i++)
  {
    index = word[i] - 'a'; // agar huruf alfabet bisa kita jadikan index dalam children kita
    if(curr->children[index] == NULL){
      //jika null maka pasti kata tersebut sudah tidak ada dalam Tries
      return false;
    }
    curr= curr->children[index]; // lanjut ke anaknya
  }
  //lalu kita return jika curr!= NULL && curr->isEndOfWordnya juga true yang menandakan word memiliki endOfWord yang sama dengan Tries
  return (curr!= NULL && curr->isEndOfWord == true);
}

void printTries(struct Tries *root){
  if(!root){ //bila nodenya kosong kita langsung return
    return; 
  }
  Tries *curr = root;
  printf("%c -> ", curr->key); //print keynya dulu
  for(int i = 0; i< SIZE ; i++){
    printTries(curr->children[i]); //lanjut print anak anaknya
  }
}

// Returns true jika root tidak memiliki children
bool isEmpty(Tries* root){
  for (int i = 0; i < SIZE; i++)
    if (root->children[i])
      return false;
  return true;
}

// untuk remove kita pakai recursive;
Tries *remove(struct Tries *root, const char word[], int depth){
  //jika node nya kosong kita return NULL;
  if(!root){
    return NULL;
  }
  //jika sampai di karakter terakhir
  if(depth == strlen(word)){
    //jika di huruf terakhir ubah end of word nya menjadi false
    if(root->isEndOfWord){
      root->isEndOfWord = false;
    }
    //jika di huruf terakhir ini node kita tidak memiliki anak, remove nodenya
    if(isEmpty(root)){
      free(root);
      root = NULL;
    }
    return root;
  }
  // jika belum sampai karakter terakhir, kita recursive sampai karakter terakhir
  int index = word[depth] - 'a';
  root->children[index] = remove(root->children[index], word, depth + 1);
  if (isEmpty(root) && root->isEndOfWord == false) {
    free (root);
    root = NULL;
  }
  return root;
}

int main(){
  struct Tries *root = createNode('*');
  insert(root, "the");
  insert(root, "there");
  insert(root, "these");
  printTries(root);
  puts("");
  root = remove(root, "there", 0);
  root = remove(root, "these", 0);
  root = remove(root, "the", 0);
  printTries(root);
  puts("");
  if(search(root, "the")){
      printf("found\n");
  }else{
      printf("not found\n");
  }
  return 0;
}
