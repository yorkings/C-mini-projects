#include <stdio.h>
#include <stdlib.h>

int main() {
    int size = 7;

    // --- MALLOC VERSION ---
    // Takes 1 argument. Memory contains "garbage" from whatever was there before.
    int *m_arr = (int*)malloc(size * sizeof(int));

    // --- CALLOC VERSION ---
    // Takes 2 arguments. Memory is "zeroed out" (cleaned) automatically.
    int *c_arr = (int *)calloc(size, sizeof(int));

    // 2. CHECK: Always check both
    if (m_arr == NULL || c_arr == NULL) {
        printf("Memory allocation failed!\n");
        return 1; 
    }

    // 3. USE: Let's see the difference BEFORE we assign any values
    printf("--- BEFORE ASSIGNING VALUES ---\n");
    for (int i = 0; i < size; i++) {
        printf("Index %d | Malloc:%10d | Calloc: %d\n", i, m_arr[i], c_arr[i]);
    }

    // 4. ASSIGN & USE: (Same as your original example)
    printf("\n--- AFTER ASSIGNING VALUES ---\n");
    for (int i = 0; i < size; i++) {
        m_arr[i] = i * 10;
        c_arr[i] = i * 10;
        printf("Index %d | Malloc: %10d | Calloc: %d\n", i, m_arr[i], c_arr[i]);
    }

    // 5. FREE: You must free both separately!
    free(m_arr);
    free(c_arr);
    
    // 6. CLEANUP
    m_arr = NULL;
    c_arr = NULL;

    return 0;
}
