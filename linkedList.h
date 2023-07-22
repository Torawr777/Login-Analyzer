#ifndef LINKEDLIST_H
#define LINKEDLIST_H


struct linkedList {
	struct linkedList *child;
	char *username, *addr;
	int logCount;
};

struct linkedList *readFile(struct linkedList *root);
struct linkedList *createNode(struct linkedList *root, struct utmp *log);
struct linkedList *insert(struct linkedList *root, struct utmp *log);
struct linkedList *insertionSort(struct linkedList *node, struct linkedList *sort);
struct linkedList *sortedInsert(struct linkedList *node);
void printLog(struct linkedList *root, int present, char *name);
void deleteList(struct linkedList *root);

#endif 