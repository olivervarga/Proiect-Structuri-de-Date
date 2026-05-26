#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LanParty.h"

int main(int argc, char *argv[]) {
    if (argc < 4) {
        printf("Not enough arguments!\n");
        return 1;
    }

    FILE *f_c_in = fopen(argv[1], "r");
    FILE *f_d_in = fopen(argv[2], "r");
    FILE *f_output = fopen(argv[3], "w");

    int tasks[5] = {0};
    for (int i = 0; i < 5; i++) {
        if (fscanf(f_c_in, "%d", &tasks[i]) != 1) {
            break;
        }
    }

    Node *head = NULL;
    int num_teams, i;
    fscanf(f_d_in, "%d", &num_teams);

    for (i = 0; i < num_teams; i++) {
        Teams newTeam;
        char buffer[150];

        fscanf(f_d_in, "%d", &newTeam.number_of_players);
        fgetc(f_d_in); 

        fgets(buffer, 150, f_d_in);

        int len = strlen(buffer);
        while (len > 0 && (buffer[len - 1] == '\n' || buffer[len - 1] == '\r' || buffer[len - 1] == ' ')) {
            buffer[len - 1] = '\0';
            len--;
        }

        newTeam.name = malloc(sizeof(char) * (strlen(buffer) + 1));
        strcpy(newTeam.name, buffer);

        newTeam.players = malloc(newTeam.number_of_players * sizeof(Player));
        float total_points = 0;

        for (int j = 0; j < newTeam.number_of_players; j++) {
            char fname[50], sname[50];
            int pts;
            
            fscanf(f_d_in, "%s %s %d", fname, sname, &pts);

            newTeam.players[j].FirstName = malloc(strlen(fname) + 1);
            strcpy(newTeam.players[j].FirstName, fname);

            newTeam.players[j].SecondName = malloc(strlen(sname) + 1);
            strcpy(newTeam.players[j].SecondName, sname);

            newTeam.players[j].points = pts;
            total_points += pts;
        }

        newTeam.score = total_points / newTeam.number_of_players;
        addAtBeginning(&head, newTeam);
    }

    int target = 1;
    while (target * 2 <= num_teams) {
        target *= 2;
    }

    int current_teams = num_teams;
    while (current_teams > target) {
        removeLowest(&head); 
        current_teams--;
    }

    if (tasks[0] == 1) {
        Node *printNode = head;
        while (printNode != NULL) {
            fprintf(f_output, "%s\n", printNode->team.name);
            printNode = printNode->next;
        }
        
    }

    if (tasks[1] == 1) {
        fprintf(f_output, "\n");
        Queue* matchQueue = createQueue();
        Node* current = head;

        while (current != NULL && current->next != NULL) {
            Match m;
            m.team1 = current->team;
            m.team2 = current->next->team;
            enqueue(matchQueue, m);
            current = current->next->next;
        }

        int tournamentTeamsCount = target;
        int roundNo = 1;
        StackNode* top8Stack = NULL;

        if (tournamentTeamsCount == 8) {
            Node* temp = head;
            while(temp != NULL) {
                push(&top8Stack, temp->team);
                temp = temp->next;
            }
        }

        while (tournamentTeamsCount > 1) {
            fprintf(f_output, "--- ROUND NO:%d\n", roundNo);

            QueueNode* tempQ = matchQueue->front;
            while (tempQ != NULL) {

                fprintf(f_output, "%-33s-%33s\n", tempQ->match.team1.name, tempQ->match.team2.name);
                tempQ = tempQ->next;
            }

            StackNode* winnerStack = NULL;
            StackNode* loserStack = NULL; 

            while (!isEmptyQueue(matchQueue)) {
                Match m = dequeue(matchQueue);
                Teams winner, loser;
                
                if (m.team1.score > m.team2.score) {
                    winner = m.team1; loser = m.team2;
                } else if (m.team2.score > m.team1.score) {
                    winner = m.team2; loser = m.team1;
                } else {

                    winner = m.team2; loser = m.team1;
                }

                for (int j = 0; j < winner.number_of_players; j++) {
                    winner.players[j].points += 1;
                }
                winner.score += 1.0f; // Media crește exact cu 1
                
                push(&winnerStack, winner);
                push(&loserStack, loser);
            }

            fprintf(f_output, "\nWINNERS OF ROUND NO:%d\n", roundNo);

            StackNode* tempS = winnerStack;
            while (tempS != NULL) {
                fprintf(f_output, "%-34s-  %.2f\n", tempS->team.name, tempS->team.score);
                tempS = tempS->next;
            }
            
            tournamentTeamsCount /= 2;

            if (tournamentTeamsCount == 8) {
                StackNode* t = winnerStack;
                while (t != NULL) {
                    push(&top8Stack, t->team);
                    t = t->next;
                }
            }

            while (!isEmptyStack(winnerStack)) {
                Match m;
                m.team1 = pop(&winnerStack);
                m.team2 = pop(&winnerStack);
                enqueue(matchQueue, m);
            }

            roundNo++;
            
            if (tournamentTeamsCount > 1) {
                fprintf(f_output, "\n");
            }
        }

        if (tasks[2] == 1 && top8Stack != NULL) {
            fprintf(f_output, "\nTOP 8 TEAMS:\n");
            BSTNode* root = NULL;

            while (!isEmptyStack(top8Stack)) {
                Teams t = pop(&top8Stack);
                root = insertBST(root, t);
            }
            
            printBSTDesc(root, f_output);
        }
    }

    fclose(f_c_in);
    fclose(f_d_in);
    fclose(f_output);
    
    return 0;
}