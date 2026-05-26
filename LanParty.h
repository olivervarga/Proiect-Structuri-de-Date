#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Player {
    char* FirstName;
    char* SecondName;
    int points;
} Player;

typedef struct Teams {
    char* name;
    int number_of_players;
    float score;
    Player* players;
} Teams;

typedef struct Node {
    Teams team;
    struct Node* next;
} Node;

typedef struct Match {
    Teams team1;
    Teams team2;
} Match;

typedef struct QueueNode {
    Match match;
    struct QueueNode* next;
} QueueNode;

typedef struct Queue {
    QueueNode* front;
    QueueNode* rear;
} Queue;

typedef struct StackNode {
    Teams team;
    struct StackNode* next;
} StackNode;

typedef struct BSTNode {
    Teams team;
    struct BSTNode* left;
    struct BSTNode* right;
} BSTNode;

void addAtBeginning(Node** head, Teams t);
void removeLowest(Node** head);

Queue* createQueue();
void enqueue(Queue* q, Match m);
Match dequeue(Queue* q);
int isEmptyQueue(Queue* q);

void push(StackNode** top, Teams t);
Teams pop(StackNode** top);
int isEmptyStack(StackNode* top);

BSTNode* insertBST(BSTNode* root, Teams team);
void printBSTDesc(BSTNode* root, FILE* f);