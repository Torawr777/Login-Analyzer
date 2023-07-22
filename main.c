#include <stdio.h>
#include <utmp.h>
#include <string.h>
#include <arpa/inet.h>
#include "linkedList.h"


int main() {
	struct linkedList *node = NULL;
	node = readFile(node);
	node = sortedInsert(node);

	char name[50];
	int cmd;


	do {
		printf("\nUser to look up ('exit' to exit): ");
		scanf("%s", name);
		cmd = strcmp(name, "exit"); //cmd = 0 if exit

		if(cmd == 0) { break; } //exit the loop
		else { printLog(node, 0, name); }
	} while(1);

	deleteList(node);
	return 0;
}
