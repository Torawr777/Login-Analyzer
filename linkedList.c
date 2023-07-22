#include <stdio.h>
#include <stdlib.h>
#include <utmp.h>
#include <string.h>
#include <arpa/inet.h>
#include "linkedList.h"


struct linkedList *readFile(struct linkedList *root) {
	FILE *file;
	struct utmp log;

	if((file = fopen("wtmp", "rb")) != NULL) { //Check if file isn't empty
		while(fread(&log, sizeof(struct utmp), 1, file) != 0) { //Read entire file
			if(log.ut_type == 7) { //Only insert succesful logins (7)
				root = insert(root, &log);
			}
		}
	}
	else { return root; }

	fclose(file);
	return root;
}


struct linkedList *createNode(struct linkedList *root, struct utmp *log) {

	//Create a node
	struct linkedList *node = malloc(sizeof(struct linkedList));
	node->logCount = 1;
	node->child = NULL;

	//Store username
	node->username = malloc(UT_NAMESIZE*sizeof(char));
	char *temp = log->ut_user;
	strncpy(node->username, temp, UT_NAMESIZE);

	//Store IP address
	node->addr = malloc(16*sizeof(char));
	char *IP_addr = inet_ntoa(*(struct in_addr *)&log->ut_addr);
	strcpy(node->addr, IP_addr);

	return node;
}


struct linkedList *insert(struct linkedList *root, struct utmp *log) {
	char *target_addr = inet_ntoa(*(struct in_addr *)&log->ut_addr);
	 
	//If current node is null
	if(root == NULL) { return createNode(root, log); }

	//If IP address matches
	if(strncmp(root->addr, target_addr, strlen(root->addr)) == 0) {

		//If username matches
		if(strncmp(log->ut_user, root->username, strlen(root->username)) == 0) {
			root->logCount += 1; //Increment log count
			return root;
		}
	}

	root->child = insert(root->child, log);
	return root;
}


//Mostly thanks to https://www.geeksforgeeks.org/insertion-sort-for-singly-linked-list/
struct linkedList *insertionSort(struct linkedList *node, struct linkedList *sort) {
	if(sort == NULL || sort->logCount <= node->logCount) { //Edge case
		node->child = sort;
		sort = node;
	}

	else {  //Find node before insertion point
		struct linkedList *current = sort;
		while(current->child != NULL && current->child->logCount > node->logCount) {
			current = current->child;
		}

		node->child = current->child;
		current->child = node;
	}
	return sort;
}


//Also mostly thanks to https://www.geeksforgeeks.org/insertion-sort-for-singly-linked-list/
struct linkedList *sortedInsert(struct linkedList *node) {
	struct linkedList *sorted = NULL;
	struct linkedList *current = node;

	while(current != NULL) { //While current spot isn't empty

		//Sort the current node after saving it to a variable
		struct linkedList *nextSort = current->child;
		sorted = insertionSort(current, sorted);
		current = nextSort;
	}
	return sorted;
}


void printLog(struct linkedList *root, int present, char *name) {
	while(root->child != NULL) { //If node isn't empty

		//If target name finds a match
		if(strncmp(root->username, name, strlen(root->username)) == 0) {
			if(present == 0) {
				present = 1; //Set to avoid "can't find user" statement
				printf("\nPreferred IP Addresses for %s \n\n", name);
				printf("  IP Address\tCount\n");
				printf("--------------------\n");
			}

			//Print in aligned columns
			printf("%-15s %d\n", root->addr, root->logCount); 
		}
		root = root->child;
	}
	if (present == 0) { //No match found
		printf("Cannot find user %s\n", name);
	}
}


void deleteList(struct linkedList *root) {
	if(root != NULL) {
		deleteList(root->child); //Delete the children first
		free(root->username);
		free(root->addr);
		free(root);
	}
}
