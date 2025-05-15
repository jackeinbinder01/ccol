# ✅ C Collections 1.0 MVP Checklist

A modular, context aware C collections library.

---

## 🔹 Core Data Structures

- [x] `vector_t` — dynamic array with capacity management
- [x] `dll_t` — doubly linked list (with context-aware function pointers)
- [x] `cdll_t` — circular doubly linked list (backbone for deque)
- [x] `hash_table_t` — generic key-value store with policy-based hashing
- [x] `deque_t` — double-ended queue using `cdll_t`
- [x] `queue_t` — FIFO queue adapter
- [x] `stack_t` — LIFO stack adapter

---

## 🔹 Test Suite

- [ ] `vector_t` tests
- [ ] `dll_t` / `cdll_t` tests
- [ ] `hash_table_t` tests
- [ ] `deque_t`, `queue_t`, `stack_t` tests
- [ ] `make test` or `ctest` integration (Makefile/CMake)

---

## 🔹 Documentation & Usability

- [ ] README with:
    - [ ] Project description
    - [ ] Build instructions
    - [ ] Usage examples
    - [ ] API overview
- [ ] Example usage for each data structure (`examples/`)
- [ ] Versioned release tag: `v1.0.0`

---

## 🔹 (Optional) Polishing for Bonus Points

- [ ] Minimal benchmark runner
- [ ] GitHub Actions / CI
- [ ] API doc generation (Doxygen or Markdown)
- [ ] CMakeLists.txt for full multi-platform builds

---

## 🎯 Goal

> Publish `ccol` v1.0.0 MVP as a complete, extensible C collections library.

