#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "task.h"


void add_task(struct Task **tasks, int *task_count) {
    struct Task *temp=realloc(*tasks, (*task_count + 1) * sizeof(struct Task));
    if(temp==NULL){
        printf("Memory allocation failed!\n");
        return;
    }
    *tasks=temp;
    printf("Enter task: ");
    fgets((*tasks)[*task_count].text, MAX_LENGTH, stdin);
    (*tasks)[*task_count].text[strcspn((*tasks)[*task_count].text, "\n")] = 0; // remove newline
    (*tasks)[*task_count].done=0;
    (*task_count)++;
    printf("Task added!\n");
}

void view_tasks(struct Task *tasks, int task_count) {
    if (task_count == 0) {
        printf("No tasks yet.\n");
    } else {
        printf("\n--- Your Tasks ---\n");
        for (int i = 0; i < task_count; i++) {
            printf("%d. [%c] %s\n", i + 1, tasks[i].done ? 'x' : ' ', tasks[i].text);
        }
    }
}

void mark_done(struct Task *tasks, int task_count) {
    int num;
    printf("Enter task number to mark done: ");
    scanf("%d", &num);  
    while (getchar() != '\n'); // clear buffer
    if(num<1 || num>task_count){
        printf("Invalid task number.\n");
        return;
    }
    tasks[num-1].done=1;
    printf("Task marked as done.\n");
}

void delete_task(struct Task **tasks, int *task_count) {
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
        return;
    }
    for (int i = del - 1; i < *task_count - 1; i++) {
        (*tasks)[i] = (*tasks)[i + 1];
    }
    (*task_count)--;
    struct Task *temp=realloc(*tasks, (*task_count) * sizeof(struct Task));
    if(temp==NULL && *task_count > 0){
        printf("Memory reallocation failed!\n");
        return;
    }
    *tasks=temp;
    printf("Task deleted.\n");
}

void save_tasks(struct Task *tasks, int task_count) {
    FILE *file = fopen("tasks.dat", "wb");
    if (file == NULL) {
        printf("Could not open file for writing!\n");
        return;
    }
    fwrite(&task_count, sizeof(int), 1, file);
    fwrite(tasks, sizeof(struct Task), task_count, file);   
    fclose(file);
}   

void load_tasks(struct Task **tasks, int *task_count) {
    FILE *file = fopen("tasks.dat", "rb");
    if (file == NULL) {
        printf("No saved tasks found.\n");
        return;
    }
    fread(task_count, sizeof(int), 1, file);
    struct Task *temp=realloc(*tasks, (*task_count) * sizeof(struct Task));
    if(temp==NULL && *task_count > 0){
        printf("Memory allocation failed!\n");
        fclose(file);
        return;
    }
    *tasks=temp;
    fread(*tasks, sizeof(struct Task), *task_count, file);
    fclose(file);
}
