#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
    int date;
    char *description;
} Day;

void read_line(char *buffer, size_t size) {
    if (fgets(buffer, (int)size, stdin) != NULL) {
        size_t i = 0;
        while (buffer[i] != '\0' && buffer[i] != '\n') i++;
        if (buffer[i] == '\n') buffer[i] = '\0';
    }
}

Day *create(void) {
    Day *calendar = calloc(7, sizeof(Day));
    if (calendar == NULL) return NULL;
    for (int i = 0; i < 7; i++) {
        calendar[i].name = malloc(50);
        calendar[i].description = malloc(200);
        if (calendar[i].name == NULL || calendar[i].description == NULL) {
            for (int j = 0; j <= i; j++) {
                free(calendar[j].name);
                free(calendar[j].description);
            }
            free(calendar);
            return NULL;
        }
    }
    return calendar;
}

void read_days(Day calendar[7]) {
    for (int i = 0; i < 7; i++) {
        printf("Enter name for Day %d: ", i + 1);
        read_line(calendar[i].name, 50);
        printf("Enter date for Day %d: ", i + 1);
        scanf("%d", &calendar[i].date);
        while (getchar() != '\n') {}
        printf("Enter description for Day %d: ", i + 1);
        read_line(calendar[i].description, 200);
    }
}

void display(const Day calendar[7]) {
    for (int i = 0; i < 7; i++) {
        printf("Day Name: %s\n", calendar[i].name);
        printf("Date: %d\n", calendar[i].date);
        printf("Description: %s\n\n", calendar[i].description);
    }
}

int main(void) {
    Day *calendar = create();
    if (calendar == NULL) return 1;
    read_days(calendar);
    printf("\nWeekly Activity Details:\n");
    display(calendar);
    for (int i = 0; i < 7; i++) {
        free(calendar[i].name);
        free(calendar[i].description);
    }
    free(calendar);
    return 0;
}
