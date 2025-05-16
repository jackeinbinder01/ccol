## Hash Table (`hash_table`)

Public headers:
- `ccol_hash_table.h` – Core API
- `ccol_hash_table_iterator.h` – Iterators for keys, values, and items

Provides:
- `ccol_hash_table_t` container
- Key-value storage
- Support for automatic resizing and collision resolution
- Optional comparator, copier, printer, and free function pointers
- Iteration over keys, values, or key-value pairs
- Policy-based hashing (`simple`, `robust`, `secure`, or `custom`)

Usage:

```c
#include <ccol/ccol_hash_table.h>

ccol_hash_table_t hash_table;
ccol_hash_table_init(
    &hash_table,
    ccol_hash_create(NULL, NULL, CCOL_HASH_SIMPLE),  // built-in or custom hasher
    (ccol_copy_t){0},
    (ccol_free_t){0},
    (ccol_print_t){0},
    (ccol_comparator_t){0}
);

ccol_hash_table_put(&hash_table, key_ptr, value_ptr);
```