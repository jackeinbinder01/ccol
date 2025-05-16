## Stack (`stack`)

Public headers:
- `ccol_queue.h` – Core API
- `ccol_stack_iterator.h` – `stack` iterator

Provides:
- `ccol_stack_t` container
- FIFO (first-in, first-out) semantics
- `push` and `pop` operations
- Built on top of a double-ended queue (`deque`)
- Optional comparator, copier, printer, and free function pointers
- Iterator support for linear traversal

Usage:

```c
#include <ccol/ccol_stack.h>

ccol_stack_t stack;
ccol_stack_init(&stack, (ccol_copy_t){0}, (ccol_free_t){0}, (ccol_print_t){0}, (ccol_comparator_t){0});
ccol_stack_push(&stack, some_data_ptr);
```
