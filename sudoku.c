#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){
    int i, j , k, p;
    int visto[10];
    
    //confirmo filas
    for (i = 0; i < 9; i++){
        for (k = 0; k < 10; k++) visto[k] = 0;
        for (j = 0; j < 9 ; j++) {
          int val = n -> sudo[i][j];
          if (val == 0) continue;
          if (visto[val]) return 0;
          visto[val] = 1;
        }
    }

    //misma logica pero para las columnas
    for (j = 0; j < 9; j++){
        for (k = 0; k < 10; k++) visto[k] = 0;
        for (i = 0; i < 9 ; i++) {
          int val = n -> sudo[i][j];
          if (val == 0) continue;
          if (visto[val]) return 0;
          visto[val] = 1;
        }
    }
    
    //ahora para los cuadros de 3x3
    for (k = 0; k < 9 ; k++) {
      for (p = 0 ; p < 10; p++) visto[p] = 0;	
      for (p = 0 ; p < 9; p++) {
        int i = 3*(k/3) + (p/3);
        int j = 3*(k%3) + (p%3);
        int val = n -> sudo[i][j];
        if (val == 0) continue;
        if (visto[val]) return 0;
        visto[val] = 1;
      }
    }
    return 1;
}


List* get_adj_nodes(Node* n){
    List* list=createList();
    int i,j,k; //para que sea mas simple :P
    int lopille = 0; // para saber si ya lo pille 0 = falso 1 = true

    for (i = 0 ; i < 9 && !lopille; i++){
        for (j = 0 ; j < 9 && !lopille; j++){
            if (n->sudo[i][j] == 0){
              lopille = 1;

              for (k = 1; k <= 9 , k++) {
                Node *Nuevo = copy(n);
                Nuevo -> sudo[i][j] = k;
                if (is_valid(Nuevo)){
                    pushBack(list, Nuevo);
                } else {
                  free(Nuevo);
                }
              }
            }
        }
    }

    return list;
}


int is_final(Node* n){
    return 0;
}

Node* DFS(Node* initial, int* cont){
  return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/