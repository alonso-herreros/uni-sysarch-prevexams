#include <stdio.h>
#include <stdlib.h>

struct node {
	int info;
	struct node* next;
};

void add(struct node *list, int info){
	struct node* newnode = (struct node*) malloc (sizeof(struct node));
	newnode->info = info;
	newnode->next = NULL;
	if(list == NULL){
		list = newnode;
	}
	else {
		newnode->next = list;
		list = newnode;
	}
}

void print_list(struct node* list){
	struct node* aux = list;
	while(aux!=NULL){
		printf("%d ",aux->info);
		aux = aux->next;
	}
	printf("\n");
}

int main(int argc, char **argv){
	struct node* list = NULL;
	add(list, 2);
	add(list, 3);
	print_list(list);
	return 0;
}