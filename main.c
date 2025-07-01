/* 
   FocusPal - Study Focus & Break Tracker
   ---------------------------------------
   📘 Created by: Kisu
   Language: C
   Description: Tracks focused study sessions, logs breaks, and generates performance reports.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

struct Session {
    int breaks;
    float duration; // in minutes
    char date[20];
    char score[30];
};

void getCurrentDate(char *buffer) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(buffer, "%02d-%02d-%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
}

void evaluateScore(float duration, int breaks, char *score) {
    if (duration < 15)
        strcpy(score, "Try Harder");
    else if (duration < 30)
        strcpy(score, "Not Bad!");
    else
        strcpy(score, "🔥 You’re a beast!");
}

int startSession() {
    struct Session s;
    time_t start, end;
    char ch;
    s.breaks = 0;

    getCurrentDate(s.date);

    printf("\nSession Started. Press 'b' + Enter for break. Press 'e' + Enter to end session.\n");
    time(&start);

    while (1) {
        scanf(" %c", &ch);
        if (ch == 'b' || ch == 'B') {
            s.breaks++;
            printf("Break logged.\n");
        } else if (ch == 'e' || ch == 'E') {
            time(&end);
            break;
        } else {
            printf("Invalid input. Press 'b' for break or 'e' to end.\n");
        }
    }

    s.duration = difftime(end, start) / 60.0;
    evaluateScore(s.duration, s.breaks, s.score);

    FILE *fp = fopen("focus_log.txt", "a");
    fprintf(fp, "%s | %.2f mins | Breaks: %d | %s\n", s.date, s.duration, s.breaks, s.score);
    fclose(fp);

    printf("\nSession Ended.\n");
    printf("Total Time: %.2f mins\n", s.duration);
    printf("Breaks: %d\n", s.breaks);
    printf("Score: %s\n", s.score);

    return 0;
}

int viewReport() {
    char line[200];
    FILE *fp = fopen("focus_log.txt", "r");
    if (!fp) {
        printf("No report found yet.\n");
        return 0;
    }
    printf("\n--- Focus Report ---\n");
    while (fgets(line, sizeof(line), fp)) {
        printf("%s", line);
    }
    fclose(fp);
    return 0;
}

int main() {
    int choice;
    do {
        printf("\n--- FocusPal: Study Session Tracker ---\n");
        printf("1. Start Focus Session\n");
        printf("2. View Report\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: startSession(); break;
            case 2: viewReport(); break;
            case 3: printf("Exiting... Stay focused!\n"); break;
            default: printf("Invalid choice. Try again.\n");
        }
    } while (choice != 3);
    return 0;
}
