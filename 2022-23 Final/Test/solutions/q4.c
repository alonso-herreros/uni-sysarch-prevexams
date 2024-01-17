#include <stdio.h>
#include <stdlib.h>

struct node{
	int value;
	struct node *next;
};


struct node *add(struct node *mylist){
	int value = 1;
	struct node *new_node = (struct node *) malloc(sizeof(struct node));
	new_node -> value = value;
	new_node->next = mylist;
	mylist = new_node;
	return mylist;
}

struct node *delete(struct node *mylist){
	mylist = mylist->next;
	return mylist;
}

void print(struct node *mylist){
	struct node *aux = mylist;
	while(aux!=NULL){
		printf("%d ", aux->value);
		aux = aux->next;
	}
	printf("\n");
}

void free_list(struct node *mylist){
	struct node *aux = mylist;
	while(aux!=NULL){
		aux = aux->next;
		free(mylist);
		mylist = aux;
	}
}

int main(){
	struct node *mylist = NULL;
	struct node *(*operation)(struct node*);
	operation = add;
	mylist = operation(mylist);
	mylist = operation(mylist);
	operation = delete;
	mylist = operation(mylist);
	print(mylist);
	free(mylist);
}