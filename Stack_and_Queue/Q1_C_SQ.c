//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section C - Stack and Queue Questions
Purpose: Implementing the required functions for Question 1 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode
{
	int item;
	struct _listnode *next;
} ListNode;	// You should not change the definition of ListNode

typedef struct _linkedlist
{
	int size;
	ListNode *head;
} LinkedList;	// You should not change the definition of LinkedList


typedef struct _queue
{
	LinkedList ll;
} Queue;  // You should not change the definition of Queue

///////////////////////// function prototypes ////////////////////////////////////

// You should not change the prototypes of these functions
void createQueueFromLinkedList(LinkedList *ll, Queue *q);
void removeOddValues(Queue *q);

void enqueue(Queue *q, int item);
int dequeue(Queue *q);
int isEmptyQueue(Queue *q);
void removeAllItemsFromQueue(Queue *q);

void printList(LinkedList *ll);
ListNode * findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);
void removeAllItems(LinkedList *ll);

//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	int c, i;
	LinkedList ll;
	Queue q;

	c = 1;

	// Initialize the linked list as an empty linked list
	ll.head = NULL;
	ll.size = 0;

	// Initialize the Queue as an empty queue
	q.ll.head = NULL;
	q.ll.size = 0;


	printf("1: Insert an integer into the linked list:\n");
	printf("2: Create the queue from the linked list:\n");
	printf("3: Remove odd numbers from the queue:\n");
	printf("0: Quit:\n");


	while (c != 0)
	{
		printf("Please input your choice(1/2/3/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to insert into the List: ");
			scanf("%d", &i);
			insertNode(&ll, ll.size, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			createQueueFromLinkedList(&ll, &q); // You need to code this function
			printf("The resulting queue is: ");
			printList(&(q.ll));
			break;
		case 3:
			removeOddValues(&q); // You need to code this function
			printf("The resulting queue after removing odd integers is: ");
			printList(&(q.ll));
			removeAllItemsFromQueue(&q);
			removeAllItems(&ll);
			break;
		case 0:
			removeAllItemsFromQueue(&q);
			removeAllItems(&ll);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}

	}

	return 0;
}


//////////////////////////////////////////////////////////////////////////////////

void createQueueFromLinkedList(LinkedList *ll, Queue *q)
{
	if (ll == NULL || q == NULL || ll->head == NULL) {
		return;
	}
	ListNode* curr = ll->head;
	while (curr != NULL) {
		enqueue(q, curr->item);
		curr = curr->next;
	}
}

void removeOddValues(Queue *q)
{
	if (q == NULL) {
		return;
	}

	int originalSize = q->ll.size;
	for (int i = 0; i < originalSize; i++) {
		int curr = dequeue(q);
		if (curr % 2 == 0) {
			enqueue(q, curr);
		}
	}
}

//////////////////////////////test case////////////////////////////////////////////
/*
Case 1 – 혼합된 값
입력: {1, 2, 3, 4, 5}

기대 출력: 2 4

Case 2 – 전부 홀수
입력: {7, 9, 11}

기대 출력: Empty

Case 3 – 전부 짝수
입력: {2, 4, 6, 8}

기대 출력: 2 4 6 8
*/
//////////////////////////////////////////////////////////////////////////////////

void enqueue(Queue *q, int item) {
	insertNode(&(q->ll), q->ll.size, item);
}

int dequeue(Queue *q) {
	int item;

	if (!isEmptyQueue(q)) {
		item = ((q->ll).head)->item;
		removeNode(&(q->ll), 0);
		return item;
	}
	return -1;
}

int isEmptyQueue(Queue *q) {
	if ((q->ll).size == 0)
		return 1;
	return 0;
}

void removeAllItemsFromQueue(Queue *q)
{
	int count, i;
	if (q == NULL)
		return;
	count = q->ll.size;

	for (i = 0; i < count; i++)
		dequeue(q);
}


void printList(LinkedList *ll){

	ListNode *cur;
	if (ll == NULL)
		return;
	cur = ll->head;
	if (cur == NULL)
		printf("Empty");
	while (cur != NULL)
	{
		printf("%d ", cur->item);
		cur = cur->next;
	}
	printf("\n");
}


void removeAllItems(LinkedList *ll)
{
	ListNode *cur = ll->head;
	ListNode *tmp;

	while (cur != NULL){
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	ll->head = NULL;
	ll->size = 0;
}


ListNode * findNode(LinkedList *ll, int index){

	ListNode *temp;

	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	temp = ll->head;

	if (temp == NULL || index < 0)
		return NULL;

	while (index > 0){
		temp = temp->next;
		if (temp == NULL)
			return NULL;
		index--;
	}

	return temp;
}

int insertNode(LinkedList *ll, int index, int value){

	ListNode *pre, *cur;

	if (ll == NULL || index < 0 || index > ll->size + 1)
		return -1;

	// If empty list or inserting first node, need to update head pointer
	if (ll->head == NULL || index == 0){
		cur = ll->head;
		ll->head = malloc(sizeof(ListNode));
		if (ll->head == NULL)
		{
			exit(0);
		}
		ll->head->item = value;
		ll->head->next = cur;
		ll->size++;
		return 0;
	}


	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));
		if (pre->next == NULL)
		{
			exit(0);
		}
		pre->next->item = value;
		pre->next->next = cur;
		ll->size++;
		return 0;
	}

	return -1;
}


int removeNode(LinkedList *ll, int index){

	ListNode *pre, *cur;

	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// If removing first node, need to update head pointer
	if (index == 0){
		cur = ll->head->next;
		free(ll->head);
		ll->head = cur;
		ll->size--;
		return 0;
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){

		if (pre->next == NULL)
			return -1;

		cur = pre->next;
		pre->next = cur->next;
		free(cur);
		ll->size--;
		return 0;
	}

	return -1;
}

/////////////////////test case////////////////////////////////
void runTestCases();
void resetList(LinkedList *ll, int arr[], int size);

void runTestCases()
{
	printf("\n===== TEST CASES =====\n");

	LinkedList ll;
	Queue q;
	int arr1[] = {1, 2, 3, 4, 5};
	int arr2[] = {7, 9, 11};
	int arr3[] = {2, 4, 6, 8};

	// Test Case 1
	resetList(&ll, arr1, 5);
	q.ll.head = NULL; q.ll.size = 0;
	printf("\n[Case 1] Original list: ");
	printList(&ll);
	createQueueFromLinkedList(&ll, &q);
	printf("Queue after creation: ");
	printList(&q.ll);
	removeOddValues(&q);
	printf("Queue after removing odd values: ");
	printList(&q.ll);
	removeAllItems(&ll);
	removeAllItemsFromQueue(&q);

	// Test Case 2
	resetList(&ll, arr2, 3);
	q.ll.head = NULL; q.ll.size = 0;
	printf("\n[Case 2] Original list (only odds): ");
	printList(&ll);
	createQueueFromLinkedList(&ll, &q);
	printf("Queue after creation: ");
	printList(&q.ll);
	removeOddValues(&q);
	printf("Queue after removing odd values (should be empty): ");
	printList(&q.ll);
	removeAllItems(&ll);
	removeAllItemsFromQueue(&q);

	// Test Case 3
	resetList(&ll, arr3, 4);
	q.ll.head = NULL; q.ll.size = 0;
	printf("\n[Case 3] Original list (only evens): ");
	printList(&ll);
	createQueueFromLinkedList(&ll, &q);
	printf("Queue after creation: ");
	printList(&q.ll);
	removeOddValues(&q);
	printf("Queue after removing odd values (should be unchanged): ");
	printList(&q.ll);
	removeAllItems(&ll);
	removeAllItemsFromQueue(&q);

	printf("======================\n");
}

void resetList(LinkedList *ll, int arr[], int size)
{
	ll->head = NULL;
	ll->size = 0;
	for (int i = 0; i < size; i++) {
		insertNode(ll, ll->size, arr[i]);
	}
}

