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
    struct Teams* next;
} Teams;

typedef struct Node {
    Teams team;
    struct Node* next;
} Node;

struct Q {
    Teams *front, *rear;
};
typedef struct Q Queue;

struct s {
    Teams *top;
};
typedef struct s Stack;

void addAtBeginning(Node** head, Teams t);
void removeLowest(Node** head);

Queue *createQueue ();
int isEmpty (Queue *q);
void enQueue (Queue *q, Teams *t);
Teams* deQueue (Queue *q);
void printQueueTeams (FILE *f, Queue *q, int round);

Stack *createStack ();
int isEmptyStack (Stack *s);
void push (Stack *s, Teams *t);
Teams *pop (Stack *s);

void runRound (Queue *q, Stack *winnerStack, Stack *loserStack);
void freeLoserStack (Stack *loserStack);
void moveWinners (Stack *winnerStack, Queue *q);
void printStackTeams (FILE *f, Stack *s, int round);
Teams *copyTeam (Teams *original);