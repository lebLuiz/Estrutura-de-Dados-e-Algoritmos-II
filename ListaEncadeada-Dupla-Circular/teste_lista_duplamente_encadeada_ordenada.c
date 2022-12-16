// PROJETO DE ESTUDO!

#include <stdlib.h>
#include <stdio.h>

typedef struct paciente {
    int codigo;
    char nome[75];
    char sexo;
    int idade;
    double peso;
    double altura;
    char telefone[15];
} Paciente;

typedef struct Item {
   int height;
   struct Item* prev;
   struct Item* next;
} Item;

typedef struct {
   int size;
   Item* first;
   Item* last;
} List;

static void insert(List *list, int height) {
   printf("* ===\n");

   Item *newItem = (Item*)malloc(sizeof(Item));
   newItem->height = height;

   if (list->size == 0)
   {
      printf("* inserindo elemento %d em lista vazia\n\n", height);
      list->first = newItem;
      list->last = newItem;
      newItem->prev = newItem;
      newItem->next = newItem;
      list->size = 1;
      return;
   }

   if (height > list->first->height)
   {
      printf("* inserindo elemento %d antes do primeiro\n\n", height);
      list->first->prev = newItem;
      list->last->next = newItem;
      newItem->prev = list->last;
      newItem->next = list->first;
      list->first = newItem;
      list->size++;
      return;
   }

   if (height < list->last->height)
   {
      printf("* inserindo elemento %d depois do ultimo\n\n", height);
      list->last->next = newItem;
      list->first->prev = newItem;
      newItem->prev = list->last;
      newItem->next = list->first;
      list->last = newItem;
      list->size++;
      return;
   }

   printf("* inserindo elemento %d intermediario\n\n", height);
   Item* item = list->first;
   for (int i = 0; i < list->size; i++)
   {
      if (item->height < height)
         break;
      item = item->next;
   }

   item->prev->next = newItem;

   newItem->prev = item->prev;
   newItem->next = item;

   item->prev = newItem;

   list->size++;
}

static void print(List* list)
{
   printf("* ---\n");
   printf("* tamanho da lista: %d\n", list->size);
   Item* item = list->first;
   for (int i = 0; i < list->size; i++)
   {
      printf("* list[%d] = %d\n", i, item->height);
      item = item->next;
   }
}


int main(void) {
   List list = { 0 };
   print(&list);

   insert(&list, 7);  // primeiro elemento
   print(&list);

   insert(&list, 2); // antes do primeiro elemento
   print(&list);

   insert(&list, 13); // depois do ultimo elemento
   print(&list);

   insert(&list, 9);  // elemento intermediario
   print(&list);
}