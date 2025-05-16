# CCOL Iterators

This directory contains iterator implementations for traversing CCOL containers.

## Iterators

- `ccol_cdll_iterator.c`
- `ccol_deque_iterator.c`
- `ccol_dll_iterator.c`
- `ccol_hash_table_iterator.c`
- `ccol_queue_iterator.c`
- `ccol_stack_iterator.c`
- `ccol_vector_iterator.c`

Each iterator exposes the `ccol_iterator_t` interface and supports:

- Sequential, safe traversal (`next`, `has_next`)