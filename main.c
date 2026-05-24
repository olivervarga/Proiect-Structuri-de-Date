#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LanParty.h"

int main(int argc, char *argv[]) {
    if (argc < 4) {
        printf("Usage: %s c.in d.in o.out\n", argv[0]);
        return 1;
    }

    FILE *f_c_in = fopen(argv[1], "r");
    FILE *f_d_in = fopen(argv[2], "r");
    FILE *f_output = fopen(argv[3], "w");

    if (!f_c_in || !f_d_in || !f_output) {
        if (f_c_in) fclose(f_c_in);
        if (f_d_in) fclose(f_d_in);
        if (f_output) fclose(f_output);
        return 1;
    }

    int tasks[5] = {0};
    for (int t = 0; t < 5; t++) {
        fscanf(f_c_in, "%d", &tasks[t]);
    }

    Node *head = NULL;
    int num_teams = 0;

    // --- TASK 1 ---
    fscanf(f_d_in, "%d", &num_teams);

    for (int i = 0; i < num_teams; i++) {
        Teams newTeam;
        char buffer[100];

        fscanf(f_d_in, "%d", &newTeam.number_of_players);
        fgetc(f_d_in);

        fgets(buffer, 100, f_d_in);
        buffer[strcspn(buffer, "\r\n")] = 0;

        int len = strlen(buffer);
        while (len > 0 && buffer[len - 1] == ' ') {
            buffer[len - 1] = '\0';
            len = strlen(buffer);
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
        newTeam.next = NULL;
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

    // --- TASK 2 (English translation applied) ---
    if (tasks[1] == 1) {
        Queue *matches = createQueue();
        Stack *winnerStack = createStack();
        Stack *loserStack = createStack();

        Node *currNode = head;
        while (currNode != NULL) {
            Teams *tAllocation = (Teams*) malloc (sizeof(Teams));
            *tAllocation = currNode->team;
            tAllocation->next = NULL;
            enQueue(matches, tAllocation);
            currNode = currNode->next;
        }

        int remainingTeams = target;
        int round = 1;

        while (matches->front != NULL && matches->front->next != NULL) {
            printQueueTeams (f_output, matches, round);
            runRound (matches, winnerStack, loserStack);
            printStackTeams (f_output, winnerStack, round);

            remainingTeams /= 2;
            freeLoserStack (loserStack);
            moveWinners (winnerStack, matches);
            round++;
        }

        free (winnerStack);
        free (loserStack);
        while (!isEmpty (matches)) {
            Teams *lastTeam = deQueue (matches);
            free(lastTeam);
        }
        free (matches);
    }

    fclose(f_c_in);
    fclose(f_d_in);
    fclose(f_output);
    
    return 0;
}