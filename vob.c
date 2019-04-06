#include <stdio.h>
#include <stdlib.h>

struct node {
  char letter;
  struct node* left; //arvore a esquerda
  struct node* right; //arvore a direita
};

struct node* tree(char (*s1)[], char (*s2)[], int start, int finish);
void print_post_order(struct node* node);
int i;

int main() {
  int c; //numero de testes
  scanf("%d",&c);
  int length;
  char s1[53], s2[53]; //array com o maximo de nos possiveis (pode ser otimizado)
  for (; c; c--) {
    i=0;
    char (*s1_ptr)[] = &s1; 
    char (*s2_ptr)[] = &s2; //ponteiros para arrays de caracteres
    scanf("%d %s %s",&length,s1,s2);
    struct node* root = (struct node*)malloc(length*sizeof(struct node)); //aloca numero de digitos x tamanho da struct node
    root = tree(s1_ptr,s2_ptr, 0, length-1); //chama a funcao recursiva que constroi a arvore e retorna um ponteiro que aponta para raiz
    print_post_order(root); //chama a funcao recursiva que printa a arvore em pos-ordem
    printf("\n");
    free(root); //libera ponteiro root
  }
  return 0;
}

struct node* tree(char (*s1)[], char (*s2)[], int start, int finish) {
  if (start > finish) return NULL; //se param start > param finish, significa que estamos numa folha
  struct node *node = (struct node*)malloc(sizeof(struct node)); //aloca um espaco para um no que nao sera perdido ao termino da execucao da funcao
  node->letter = (*s1)[i]; //cria no para letra s1[i] da preordem. ex: s1[0] = raiz da arvore
  int stop = start;
  while (stop <= finish) {
    if ((*s2)[stop] == node->letter) { //se encontrarmos a posicao de s1[i] na arvore lida em em-ordem, paramos e guardamos esse valor
      break;
    }
    stop++;
  }
  i++; //incrementa-se o i para iniciar um novo node na proxima iteracao
  node->left = tree(s1,s2,start,stop-1); //a esquerda do node, procuramos de start do no atual ate ele mesmo - 1
  node->right = tree(s1,s2,stop+1,finish); // a direita do node, procuramos dele mesmo + 1 ate o final
  return node; //retorna o node criado
}

void print_post_order(struct node* node) {
  if (node) {
    print_post_order(node->left); //enquanto houver node na esquerda, precisamos printa-los
    print_post_order(node->right); //enquanto houver node na direita, precisamos printa-los
    printf("%c",node->letter); //so entao printamos o node
  }
}