#include "stack.h"

int main(void) {
    int arr[] = { 2, 12, 123, 1234, 12345, 123456, 1234567, 123456789 };
    int nelems = sizeof(arr) / sizeof(arr[0]);

    stack *s = new_stack(sizeof(int));
    for (int i = 0; i < nelems; ++i) {
        stack_push(s, arr + i);
    }
    int popped;
    while (stack_pop(s, &popped)) printf("%d \n", popped);
    free(s);
    return 0;
}