## Double-ended Queue (`deque`)

Public headers:
- `ccol_deque.h` – Core API
- `ccol_deque_iterator.h` – `deque` iterator

Provides:
- `ccol_deque_t` container
- Insertion and removal at both ends
- Support for positional access (`peek_front`, `peek_back`, `peek_middle`)
- Uses a circular doubly-linked list (`cdll`) internally
- Optional comparator, copier, printer, and free function pointers
- Iterator support for linear traversal

Usage:

```c
#include <ccol/ccol_deque.h>

ccol_deque_t deque;
ccol_deque_init(&deque, (ccol_copy_t){0}, (ccol_free_t){0}, (ccol_print_t){0}, (ccol_comparator_t){0});
ccol_deque_push_back(&deque, some_data_ptr);
```