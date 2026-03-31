#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "task.h"

int main()
{
    struct Task *tasks=NULL;
    int task_count = 0;
    int choice;
    load_tasks(&tasks, &task_count);
    do {
        printf("\n1. Add Task\n");
        printf("2. View Tasks\n");
        printf("3. Mark Done\n");
        printf("4. Delete Task\n");
        printf("5. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);
        while (getchar() != '\n');
        switch (choice) {
            case 1:
                add_task(&tasks, &task_count);
                break;
            case 2:
                view_tasks(tasks, task_count);
                break;
            case 3:
                mark_done(tasks, task_count);
                break;
            case 4:
                delete_task(&tasks, &task_count);
                break;
            case 5:
                save_tasks(tasks, task_count);
                free(tasks);
                printf("Goodbye!\n");
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 5);
    return 0;
}   
