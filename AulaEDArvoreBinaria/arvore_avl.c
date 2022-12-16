// PROJETO DE ESTUDO!

#include <stdio.h>
#include <stdbool.h> // true/false
#include <stdlib.h>  // free, malloc, sizeof
//------------------------------------
//------------------------------------

//NoAVL* PtrNoAVL
typedef struct NoAVL* PtrNoAVL;

typedef struct NoAVL{
  PtrNoAVL dir, esq;
  int chave;
  int altura; // novidade no nó de AVL
} NoAVL;

//------------------------------------
//------------------------------------

void iniciaArvoreAVL(PtrNoAVL *no){
  (*no) = NULL;
}

bool estaVaziaArvoreAVL(PtrNoAVL *no) {
  return((*no) == NULL);
}

void preOrdemAVL(PtrNoAVL *no) {
  if((*no) == NULL) return;
  // print
  printf("%d ", (*no)->chave);
  // esq (recursivamente)
  preOrdemAVL(&(*no)->esq);
  // dir (recursivamente)
  preOrdemAVL(&(*no)->dir);
}

void preOrdemPrincipal(PtrNoAVL *no){
  printf("Pre-ordem = {");
  preOrdemAVL(no);
  printf("}\n");
}
//------------------------------------
//------------------------------------

int alturaArvoreAVL(PtrNoAVL *no) {
  if ((*no) == NULL) return 0;
  else return (*no)->altura;
}

int atualizaAlturaNoAVL(PtrNoAVL *esq, PtrNoAVL *dir) {
  int ae, ad, ret;
  ae = alturaArvoreAVL(&(*esq));
  ad = alturaArvoreAVL(&(*dir));

  if(ae >= ad) {
    ret = ae + 1;
  } else { // ad > ae
    ret = ad + 1;
  }
  return (ret);
}

void rotacaoSimplesDireita(PtrNoAVL *p) {
  printf(" - Rotação Simples Direita ... \n");
  PtrNoAVL v = (*p)->esq;
  (*p)->esq  = v->dir;
  v->dir     = (*p);
  (*p)->altura = atualizaAlturaNoAVL(&(*p)->esq, &(*p)->dir);
  v->altura    = atualizaAlturaNoAVL(&(v->esq), &(v->dir));
  (*p) = v;
}

void rotacaoSimplesEsquerda(PtrNoAVL *p) {
  printf(" - Rotação Simples Esquerda ... \n");
  PtrNoAVL v = (*p)->dir;
  (*p)->dir  = v->esq;
  v->esq     = (*p);
  (*p)->altura = atualizaAlturaNoAVL(&(*p)->esq, &(*p)->dir);
  v->altura    = atualizaAlturaNoAVL(&(v->esq), &(v->dir));
  (*p) = v;
}

void rotacaoDuplaDireita(PtrNoAVL *p) {
  printf(" - Rotação Dupla Direita ... \n");

  PtrNoAVL u = (*p)->esq;
  PtrNoAVL v = u->dir;
  u->dir     = v->esq;
  (*p)->esq  = v->dir;
  v->esq     = u;
  v->dir     = (*p);
  (*p)->altura = atualizaAlturaNoAVL(&(*p)->esq, &(*p)->dir);
  v->altura    = atualizaAlturaNoAVL(&(v->esq), &(v->dir));
  u->altura    = atualizaAlturaNoAVL(&(u->esq), &(u->dir));
  (*p) = v;
}

void rotacaoDuplaEsquerda(PtrNoAVL *p){
  printf(" - Rotação Dupla Esquerda ... \n");
  PtrNoAVL u = (*p)->dir;
  PtrNoAVL v = u->esq;
  u->esq     = v->dir;
  (*p)->dir  = v->esq;
  v->esq     = (*p);
  v->dir     = u;
  (*p)->altura = atualizaAlturaNoAVL(&(*p)->esq, &(*p)->dir);
  v->altura    = atualizaAlturaNoAVL(&(v->esq), &(v->dir));
  u->altura    = atualizaAlturaNoAVL(&(u->esq), &(u->dir));
  (*p) = v;
}


void aplicarRotacoes(PtrNoAVL *no) {  // se entrou, o FB do *no é -2, ou 2
  int ae, ad, fatorBalanceamento;
  ae = alturaArvoreAVL(&(*no)->esq);
  ad = alturaArvoreAVL(&(*no)->dir);
  fatorBalanceamento = ad - ae;
  PtrNoAVL u;
  int aUdir, aUesq;
  if(fatorBalanceamento == -2) {
    u = (*no)->esq;
    aUdir = alturaArvoreAVL(&u->dir);
    aUesq = alturaArvoreAVL(&u->esq);
    //Rotacoes p Direita {Simples, Dupla}
    if(aUesq >= aUdir) {
      rotacaoSimplesDireita(&(*no));
    } else {
      rotacaoDuplaDireita(&(*no));
    }
  } else { // == +2
    u = (*no)->dir;
    aUdir = alturaArvoreAVL(&u->dir);
    aUesq = alturaArvoreAVL(&u->esq);
    //Rotacoes p Esquerda {Simples, Dupla}
    if(aUdir >= aUesq) {
      rotacaoSimplesEsquerda(&(*no));
    } else {
      rotacaoDuplaEsquerda(&(*no));
    }
  }
}

bool insereArvoreAVL(PtrNoAVL *no, int valor) {

  // verificacoes, clausulas de fim de recursao
  //  - ponto de insercao (true)
  if((*no) == NULL) {
    (*no) = malloc(sizeof(NoAVL));
    (*no)->esq = NULL;
    (*no)->dir = NULL;
    (*no)->chave = valor;
    (*no)->altura = 1;  // novidade na AVL
    printf("Inserindo valor = %d\n", valor);
    return true;
  }
  //  - não insere (valor duplicado) (false)
  if((*no)->chave == valor) {
    printf("Warning: elemento duplicado, não inserindo\n");
    return false;
  }

// clausulas recursivas
//  valor > no->chave: chamada recursiva direita
//  valor < no->chave: chamada recursiva esquerda
  bool ret;
  if(valor > (*no)->chave) {
    ret = insereArvoreAVL(&(*no)->dir, valor);
  } else {
    ret = insereArvoreAVL(&(*no)->esq, valor);
  }
  // --------------------------
  // Daqui p baixo é novidade da AVL
  // --------------------------

  // nao inseriu elemento, nao desbalanceou
  if(!ret) return false;
  // PODE ter desbalanceamento (*no)
  int ad, ae, fatorBalanceamento;
  ad = alturaArvoreAVL(&(*no)->dir);
  ae = alturaArvoreAVL(&(*no)->esq);
  fatorBalanceamento = ad - ae;
  //fb = {-2, -1, 0, 1, 2}
  // valores aceitaveis = {-1, 0, 1}
  // valor desbalanceamento = {-2, +2}
  if(fatorBalanceamento == 2 || fatorBalanceamento == -2) {
    aplicarRotacoes(&(*no));
  }
  //atualizar a altura do no atual (*no)
  (*no)->altura = atualizaAlturaNoAVL(&(*no)->esq, &(*no)->dir);
  return true;
}


//------------------------------------
//------------------------------------

int main(int argc, char* argv[]) {
  PtrNoAVL raiz;
  iniciaArvoreAVL(&raiz);
  if(estaVaziaArvoreAVL(&raiz)) {
    printf("Árvore é uma mudinha ainda. Esta vazia\n");
  }
  preOrdemPrincipal(&raiz);

  insereArvoreAVL(&raiz, 8);
  preOrdemPrincipal(&raiz);
  insereArvoreAVL(&raiz, 5);
  preOrdemPrincipal(&raiz);
  insereArvoreAVL(&raiz, -4);
  preOrdemPrincipal(&raiz);
  insereArvoreAVL(&raiz, 15);
  preOrdemPrincipal(&raiz);
  insereArvoreAVL(&raiz, 27);
  preOrdemPrincipal(&raiz);
  insereArvoreAVL(&raiz, 6);
  preOrdemPrincipal(&raiz);
  insereArvoreAVL(&raiz, 2);
  preOrdemPrincipal(&raiz);
  insereArvoreAVL(&raiz, -1);
  preOrdemPrincipal(&raiz);
  insereArvoreAVL(&raiz, 13);
  preOrdemPrincipal(&raiz);
  insereArvoreAVL(&raiz, 11);
  preOrdemPrincipal(&raiz);
  insereArvoreAVL(&raiz, 12);
  preOrdemPrincipal(&raiz);
  insereArvoreAVL(&raiz, 2);
  preOrdemPrincipal(&raiz);

  printf("\n\n\n\n");

  return 0;
}

//------------------------------------
//------------------------------------