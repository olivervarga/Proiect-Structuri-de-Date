#include "LanParty.h"

void addAtBeginning(Node** head, Teams t) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->team = t;
    newNode->next = *head;
    *head = newNode;
}

void removeLowest(Node** head) {
    if (*head == NULL) return;

    Node *temp = *head;
    float min_score = temp->team.score;

    while (temp != NULL) {
        if (temp->team.score < min_score) {
            min_score = temp->team.score;
        }
        temp = temp->next;
    }

    temp = *head;
    Node *prev = NULL;

    while (temp != NULL) {
        if (temp->team.score == min_score) {
            if (prev == NULL) {
                *head = temp->next;
            } else {
                prev->next = temp->next;
            }
            free(temp);
            return; 
        }
        prev = temp;
        temp = temp->next;
    }
}

Queue *createQueue () {
    Queue *q = (Queue*) malloc (sizeof (Queue));
    if (q == NULL) return NULL;
    q->front = q->rear = NULL;
    return q;
}

int isEmpty (Queue *q) {
    return (q == NULL || q->front == NULL);
}

void enQueue (Queue *q, Teams *t) {
    if (q == NULL || t == NULL) return;
    t->next = NULL;
    if (q->rear == NULL) {
        q->rear = t;
    } else {
        (q->rear)->next = t;
        (q->rear) = t;
    }
    if (q->front == NULL) 
        q->front = q->rear;
}

Teams* deQueue (Queue *q) {
    if (isEmpty (q)) return NULL;
    Teams *aux = q->front;
    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }
    aux->next = NULL; 
    return aux;
}

void printQueueTeams (FILE *f, Queue *q, int round) {
    if (q == NULL || q->front == NULL) return;
    Teams *temp = q->front;
    fprintf (f, "\n--- ROUND NO:%d\n", round);
    while (temp != NULL && temp->next != NULL) {
        fprintf (f, "%-33s-%33s\n", temp->name, temp->next->name);
        temp = temp->next->next;
    }
}

Stack *createStack () {
    Stack *s = (Stack*) malloc (sizeof (Stack));
    if (s == NULL) return NULL;
    s->top = NULL;
    return s;
}

int isEmptyStack (Stack *s) {
    return (s == NULL || s->top == NULL);
}

void push (Stack *s, Teams *t) {
    if (s == NULL || t == NULL) return;
    t->next = s->top;
    s->top = t;
}

Teams *pop (Stack *s) {
    if (isEmptyStack (s)) return NULL;
    Teams *temp = s->top;
    s->top = s->top->next;
    temp->next = NULL;
    return temp;
}

void runRound (Queue *q, Stack *winnerStack, Stack *loserStack) {
    if (isEmpty (q)) return;
    while (!isEmpty (q)) {
        Teams *t1 = deQueue (q);
        Teams *t2 = deQueue (q);
        if (t1 == NULL || t2 == NULL) return;

        if (t1->score > t2->score) {
            t1->score += 1.0f;
            for (int i=0; i < t1->number_of_players; i++) {
                t1->players[i].points++;
            }
            push (winnerStack, t1);
            push (loserStack, t2);
        } else {
            t2->score += 1.0f;
            for (int i=0; i < t2->number_of_players; i++) {
                t2->players[i].points++;
            }
            push (winnerStack, t2);
            push (loserStack, t1);
        }
    }
}

void freeLoserStack (Stack *loserStack) {
    if (loserStack == NULL) return;
    while (!isEmptyStack (loserStack)) {
        Teams *t = pop (loserStack);
        if (t != NULL) {
            free (t->name);
            for (int i=0; i < t->number_of_players; i++) {
                free (t->players[i].FirstName);
                free (t->players[i].SecondName);
            }
            free (t->players);
            free (t);
        }
    }
}

void moveWinners (Stack *winnerStack, Queue *q) {
    while (!isEmptyStack (winnerStack)) {
        Teams *winner = pop (winnerStack);
        enQueue (q, winner);
    }
}

void printStackTeams (FILE *f, Stack *s, int round) {
    if (s == NULL || s->top == NULL) return;
    fprintf(f, "\nWINNERS OF ROUND NO:%d\n", round);
    Teams *temp = s->top;
    while (temp != NULL) {
        fprintf(f, "%-34s-  %.2f\n", temp->name, temp->score);
        temp = temp->next;
    }
}

Teams *copyTeam (Teams *original) {
    if (original == NULL) return NULL;
    Teams *clona = (Teams*) malloc (sizeof (Teams));
    clona->name = (char*) malloc ((strlen (original->name) + 1) * sizeof (char));
    strcpy (clona->name, original->name);
    clona->score = original->score;
    clona->number_of_players = original->number_of_players;
    
    clona->players = (Player*) malloc (original->number_of_players * sizeof (Player));
    
    for (int i=0; i < original->number_of_players; i++) {
        clona->players[i].FirstName = (char*) malloc ((strlen (original->players[i].FirstName) + 1) * sizeof (char));
        strcpy(clona->players[i].FirstName, original->players[i].FirstName);
        clona->players[i].SecondName = (char*) malloc ((strlen (original->players[i].SecondName) + 1) * sizeof (char));
        strcpy(clona->players[i].SecondName, original->players[i].SecondName);
        clona->players[i].points = original->players[i].points;
    }
    clona->next = NULL;
    return clona;
}