## Circular Doubly-linked List (`cdll`)

Public headers:
- `ccol_cdll.h` – Core API
- `ccol_cdll_iterator.h` – `cdll` iterator

Provides:
- `ccol_cdll_t` container
- Core operations: `push`, `pop`, `insert`, `remove`, `clone`, `reverse`, etc.
- Positional access: `peek_front`, `peek_middle`, `peek_back`
- Stable node handles via `ccol_dll_node_t`
- Optional comparator, copier, printer, and free function pointers
- Iterator support for linear traversal

Usage:

```c
#include <ccol/ccol_cdll.h>

ccol_cdll_t list;
ccol_cdll_init(&list, (ccol_copy_t){0}, (ccol_free_t){0}, (ccol_print_t){0}, (ccol_comparator_t){0});
ccol_cdll_push_back(&list, some_data_ptr);
```