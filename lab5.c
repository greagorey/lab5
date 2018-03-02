/*
 *  Add tail pointer to a Singly Linked List
 *
 *  Author:  Joseph Fall
 *  Date:    Feb. 2, 2018
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <limits.h>

//----- NODE -----
struct  Node {
    int data;
    struct Node* next;
};
typedef struct Node Node_t;

Node_t* nodeCreate(int value) {
    Node_t* node = malloc(sizeof(Node_t));
    node->data = value;
    node->next = NULL;
    return node;
}

void nodePrint(Node_t node) {
    printf("[%d]%s", node.data, node.next ? "-->" : "--|");
}


//----- LINKED LIST -----
struct LinkedList {
   Node_t* head;
   Node_t* tail;
};
typedef struct LinkedList LinkedList_t;

LinkedList_t llCreate() {
   LinkedList_t list = {NULL, NULL};
   Node_t* dummy = nodeCreate(INT_MIN);
   list.head = dummy;
   list.tail = dummy;
   return list;
   
}

void llPrint(const LinkedList_t list) {
   Node_t* cur = list.head->next;
   printf("\nList:  ");
   while (cur != NULL) {
       nodePrint(*cur);
       cur = cur->next;
   }
   printf("\n\n");
    
}

bool llIsEmpty(const LinkedList_t list) {
   return list.head->next == NULL;
}

void llPush(LinkedList_t* list, int value) {
   Node_t* newNode = nodeCreate(value);
   if (llIsEmpty(*list)) {
      list->head->next =  newNode;
	  list->tail = newNode;
   }
   else {
      newNode->next = list->head->next;
      list->head->next = newNode;
   }
}

int llPop(LinkedList_t* list) {
   assert(!llIsEmpty(*list));
   Node_t* node = list->head->next;
   if (list->tail->next == list->head->next) {
      list->head->next = list->tail->next = NULL;
   }
   else {
      list->head->next = list->head->next->next;
   }
   int value = node->data;
   free(node);
   return value;
}

void llAppend(LinkedList_t* list, int value) {
   Node_t* newNode = nodeCreate(value);
   if (llIsEmpty(*list)) {
      llPush(list, value);
   }
   else {
      list->tail->next = newNode;
      list->tail=newNode;
   }
}

void llDelete(LinkedList_t* list) {
   while (list->head->next != NULL) {
      Node_t* cur = list->head->next;
      list->head->next= list->head->next->next;
      free(cur);
   }
   list->tail = list->head;
}

int llLength(const LinkedList_t list) {
   Node_t* cur = list.head->next;
   int len = 0;
   while (cur != NULL) {
      len++;
      cur = cur->next;
   }
   return len;
}

Node_t* llFind(const LinkedList_t list, int value) {
   Node_t* cur = list.head->next;
   
   while (cur != NULL) {
       if (cur->data == value)
	   {
         return cur;
	   }
       cur = cur->next;
   }
   return NULL;
}

void llLinkAfter(LinkedList_t* list, Node_t *cur, Node_t *newnode)
{
	if(cur->next==NULL)
	{
		cur->next = newnode;
		newnode->next = NULL;
		list->tail = newnode;
	}
	else{
		newnode->next = cur->next;
		cur->next = newnode;
	}
}

Node_t* llUnlinkAfter(LinkedList_t* list, Node_t *cur)
{
	Node_t *unode = cur->next;
	
	if(cur->next == NULL)
	{
		return NULL;
	}
	else{
			
		cur->next=cur->next->next;
		return unode;
		}
	
}

void insertAfter(LinkedList_t* list, Node_t *cur,int value)
{
	Node_t *newnode = nodeCreate(value);
	llLinkAfter(list,cur,newnode);
}






//----- TEST DRIVER -----
int main( )
{
   int v;
   Node_t* tmp;
   
   LinkedList_t list = llCreate();
   assert(llIsEmpty(list));
   assert(llLength(list) == 0);
   assert(llFind(list, 1) == NULL);
   llAppend(&list, 1);
   llAppend(&list, 2);
   llAppend(&list, 3);
   llPrint(list);

   assert(!llIsEmpty(list));
   assert(llLength(list) == 3);
   assert(llFind(list, 2) != NULL);
   assert(llFind(list, 42) == NULL);
   llPush(&list, 99);
   llPush(&list, 98);
   llPush(&list, 97);
   llPrint(list);
   assert(llLength(list) == 6);
   assert(llFind(list, 2) != NULL);
   assert(llFind(list, 99) != NULL);
   v = llPop(&list);
   assert(v == 97);
   v = llPop(&list);
   assert(v == 98);
   llPrint(list);
   llDelete(&list);
   assert(llIsEmpty(list));
   
   printf("\nLink / Unlink tests... \n");
   llLinkAfter(&list, list.head, nodeCreate(100));
   llLinkAfter(&list, list.head->next, nodeCreate(102));
   llLinkAfter(&list, list.head->next, nodeCreate(101));
   llLinkAfter(&list, list.tail, nodeCreate(103));
   llPrint(list);
   assert(llLength(list) == 4);
   
   assert(llUnlinkAfter(&list, list.tail) == NULL);
   assert(llLength(list) == 4);
   tmp = llUnlinkAfter(&list, list.head->next);
   llPrint(list);
   assert(llLength(list) == 3);
   assert(tmp->data == 101);
   free(tmp);

   tmp = llUnlinkAfter(&list, list.head->next->next);
   llPrint(list);
   assert(llLength(list) == 2);
   assert(tmp->data == 103);
   free(tmp);
   tmp = llUnlinkAfter(&list, list.head);
   llPrint(list);
   assert(llLength(list) == 1);
   assert(tmp->data == 100);
   free(tmp);
   llDelete(&list);
   assert(llIsEmpty(list));
   
}

