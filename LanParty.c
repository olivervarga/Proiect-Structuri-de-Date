#include "LanParty.h"

// --- Task 1 Functions ---
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

// --- Task 2 Functions ---
Queue* createQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}

void enqueue(Queue* q, Match m) {
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    newNode->match = m;
    newNode->next = NULL;
    if (q->rear == NULL) {
        q->front = q->rear = newNode;
        return;
    }
    q->rear->next = newNode;
    q->rear = newNode;
}

Match dequeue(Queue* q) {
    if (q->front == NULL) {
        Match emptyMatch = {0};
        return emptyMatch;
    }
    QueueNode* temp = q->front;
    Match m = temp->match;
    q->front = q->front->next;
    
    if (q->front == NULL) {
        q->rear = NULL;
    }
    free(temp);
    return m;
}

int isEmptyQueue(Queue* q) {
    return (q->front == NULL);
}

void push(StackNode** top, Teams t) {
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    newNode->team = t;
    newNode->next = *top;
    *top = newNode;
}

Teams pop(StackNode** top) {
    if (*top == NULL) {
        Teams emptyTeam = {0};
        return emptyTeam;
    }
    StackNode* temp = *top;
    Teams t = temp->team;
    *top = (*top)->next;
    free(temp);
    return t;
}

int isEmptyStack(StackNode* top) {
    return (top == NULL);
}

// --- Task 3 Functions ---
BSTNode* insertBST(BSTNode* root, Teams team) {
    if (root == NULL) {
        BSTNode* newNode = (BSTNode*)malloc(sizeof(BSTNode));
        newNode->team = team;
        newNode->left = newNode->right = NULL;
        return newNode;
    }

    if (team.score < root->team.score) {
        root->left = insertBST(root->left, team);
    } else if (team.score > root->team.score) {
        root->right = insertBST(root->right, team);
    } else {
        // Dacă scorurile sunt egale, ordonăm descrescător după nume
        if (strcmp(team.name, root->team.name) < 0) {
            root->left = insertBST(root->left, team);
        } else {
            root->right = insertBST(root->right, team);
        }
    }
    return root;
}

void printBSTDesc(BSTNode* root, FILE* f) {
    if (root == NULL) return;
    
    // Parcurgere Dreapta-Rădăcină-Stânga pentru afișare descrescătoare
    printBSTDesc(root->right, f);
    fprintf(f, "%-34s-  %.2f\n", root->team.name, root->team.score);
    printBSTDesc(root->left, f);
}