#include <stdio.h>
#include <string.h>

#define MAX_TASKS 100
#define MAX_LENGTH 50

void add_task(char tasks[][MAX_LENGTH], int *task_count) {
    if (*task_count < MAX_TASKS) {
        printf("Enter task: ");
        fgets(tasks[*task_count], MAX_LENGTH, stdin);
        tasks[*task_count][strcspn(tasks[*task_count], "\n")] = 0; // remove newline
        (*task_count)++;
        printf("Task added!\n");
    } else {
        printf("Task list full!\n");
    }
}

void view_tasks(char tasks[][MAX_LENGTH], int task_count) {
    if (task_count == 0) {
        printf("No tasks yet.\n");
    } else {
        printf("\n--- Your Tasks ---\n");
        for (int i = 0; i < task_count; i++) {
            printf("%d. %s\n", i + 1, tasks[i]);
        }
    }
}

void delete_task(char tasks[][MAX_LENGTH], int *task_count) {
    if (*task_count == 0) {
        printf("No tasks to delete.\n");
        return;
    }

    int del;
    printf("Enter task number to delete: ");
    scanf("%d", &del);
    while (getchar() != '\n'); // clear buffer

    if (del < 1 || del > *task_count) {
        printf("Invalid task number.\n");
    } else {
        for (int i = del - 1; i < *task_count - 1; i++) {
            strcpy(tasks[i], tasks[i + 1]);
        }
        (*task_count)--;
        printf("Task deleted.\n");
    }
}

void save_tasks(char tasks[][MAX_LENGTH], int task_count) {
    FILE *file = fopen("tasks.txt", "w");
    if (file == NULL) return; // Error checking

    for (int i = 0; i < task_count; i++) {
        fprintf(file, "%s\n", tasks[i]); // Write each task to a new line
    }
    fclose(file);
    printf("Saved to disk!\n");
}

void load_tasks(char tasks[][MAX_LENGTH], int *task_count) {
    FILE *file = fopen("tasks.txt", "r");
    if (file == NULL) return; // No file yet, which is fine for first run

    while (fgets(tasks[*task_count], MAX_LENGTH, file)) {
        tasks[*task_count][strcspn(tasks[*task_count], "\n")] = 0; // Clean newline
        (*task_count)++;
    }
    fclose(file);
}


int main() {
    char tasks[MAX_TASKS][MAX_LENGTH];
    int task_count = 0;
    int choice;
    // Load existing data at startup
    load_tasks(tasks, &task_count);


    do {
        printf("\n--- To-Do List Menu ---\n");
        printf("1. Add Task\n2. View Tasks\n3. Delete Task\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        while (getchar() != '\n'); // clear buffer

        switch(choice) {
            case 1:
                add_task(tasks, &task_count);
                break;
            case 2:
                view_tasks(tasks, task_count);
                break;
            case 3:
                delete_task(tasks, &task_count);
                break;
            case 4:
                save_tasks(tasks, task_count);
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 4);

    return 0;
}
