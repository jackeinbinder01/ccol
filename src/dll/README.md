## Doubly-linked List (`dll`)

Public headers:
- `ccol_dll.h` – Core API
- `ccol_dll_iterator.h` – `dll` iterator

Provides:
- `ccol_dll_t` container
- Core operations: `push`, `pop`, `insert`, `remove`, `clone`, `reverse`, etc.
- Positional access: `peek_front`, `peek_middle`, `peek_back`
- Stable node handles via `ccol_dll_node_t`
- Optional comparator, copier, printer, and free function pointers
- Iterator support for linear traversal

Usage:

```c
#include <ccol/ccol_dll.h>

ccol_dll_t list;
ccol_dll_init(&list, (ccol_copy_t){0}, (ccol_free_t){0}, (ccol_print_t){0}, (ccol_comparator_t){0});
ccol_dll_push_back(&list, some_data_ptr);
```