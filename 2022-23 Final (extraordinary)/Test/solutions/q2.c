#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
	char country_code[3];
	int population;
	struct node* next;
};

int main(){
	int size = 5;
	struct node** hash_table = (struct node **) calloc(sizeof(struct node*),size);
	struct node* spain = (struct node *) malloc(sizeof(struct node));
	strcpy(spain->country_code,"ESP");
	spain->population = 47;
	//spain->next = NULL;
	struct node* france = (struct node *) malloc(sizeof(struct node));
	strcpy(france->country_code,"FRA");
	france->population = 67;
	//france->next = NULL;
	hash_table[0] = spain;
	hash_table[0]->next = france;
	printf("%s | %s \n", hash_table[0]->country_code, hash_table[0]->next->country_code);
	free(france);
	free(spain);
	free(hash_table);
}
