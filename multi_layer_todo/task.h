#ifndef TASK_H
#define TASK_H

#define MAX_LENGTH 100
// Task structure
struct Task {
    char text[MAX_LENGTH];
    int done; // 0 = not done, 1 = done
};

// Function prototypes
void add_task(struct Task **tasks, int *task_count);
void view_tasks(struct Task *tasks, int task_count);
void mark_done(struct Task *tasks, int task_count);
void delete_task(struct Task **tasks, int *task_count);
void save_tasks(struct Task *tasks, int task_count);
void load_tasks(struct Task **tasks, int *task_count);

#endif // TASK_H