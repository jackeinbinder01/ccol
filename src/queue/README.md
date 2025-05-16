## Queue (`queue`)

Public headers:
- `ccol_queue.h` – Core API
- `ccol_queue_iterator.h` – `queue` iterator

Provides:
- `ccol_queue_t` container
- FIFO (first-in, first-out) semantics
- `enqueue` and `dequeue` operations
- Built on top of a double-ended queue (`deque`)
- Optional comparator, copier, printer, and free function pointers
- Iterator support for linear traversal

Usage:

```c
#include <ccol/ccol_queue.h>

ccol_queue_t queue;
ccol_queue_init(&queue, (ccol_copy_t){0}, (ccol_free_t){0}, (ccol_print_t){0}, (ccol_comparator_t){0});
ccol_queue_enqueue(&queue, some_data_ptr);
```
