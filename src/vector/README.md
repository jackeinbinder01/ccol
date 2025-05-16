## Dynamic Array (`vector`)

Public headers:
- `ccol_vector.h` – Core API
- `ccol_vector_iterator.h` – `vector` iterator

Provides:
- `ccol_vector_t` container
- Dynamic array with automatic resizing
- Index-based access (`get`, `set`)
- Common operations: `push_back`, `pop_back`, `insert`, `remove`, `clone`, etc.
- Optional comparator, copier, printer, and free function pointers
- Iterator support for linear traversal

Usage:

```c
#include <ccol/ccol_vector.h>

ccol_vector_t vec;
ccol_vector_init(&vec, (ccol_copy_t){0}, (ccol_free_t){0}, (ccol_print_t){0}, (ccol_comparator_t){0});
ccol_vector_push_back(&vec, some_data_ptr);
```