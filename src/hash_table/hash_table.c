/*
 * ccol/hash_table.c
 *
 * Hash table implementation
 *
 * Created by Jack Einbinder
 * Copyright (C) 2025 Jack Einbinder
 */

#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "dll.h"
#include "hash.h"
#include "hash_table.h"
#include "hash_table_internal.h"
#include "hash_table_iterator.h"
#include "comparator.h"
#include "ccol_status.h"
#include "ccol_constants.h"
#include "ccol_macros.h"

// Create / Initialize
ccol_status_t hash_table_init(
    hash_table_t *hash_table,
    hash_t hasher,
    copy_t copier,
    free_t freer,
    print_t printer,
    comparator_t comparator
) {
    if (!hash_table) return CCOL_STATUS_INVALID_ARG;

    hash_table->hasher = hasher;

    hash_table->copier = copier;
    hash_table->freer = freer;
    hash_table->printer = printer;
    hash_table->comparator = comparator;

    hash_table->is_initialized = true;

    return CCOL_STATUS_OK;
}

ccol_status_t hash_table_create(
    size_t num_buckets,
    size_t key_size,
    hash_policy_t policy,
    hash_t hasher,
    copy_t copier,
    free_t freer,
    print_t printer,
    comparator_t comparator,
    hash_table_t **hash_table_out
) {
    if (!hash_table_out || num_buckets < 1 || key_size < 1) return CCOL_STATUS_INVALID_ARG;
	if (!comparator.func) return CCOL_STATUS_COMPARATOR_FUNC;
    if (!hasher.func) return CCOL_STATUS_HASH_FUNC;

    return hash_table_create_internal(
    	num_buckets,
       	key_size,
        policy,
        hasher.func,
        hasher.ctx,
        copier,
        freer,
        printer,
        comparator,
        hash_table_out
   	);
}

// Insertion
ccol_status_t hash_table_insert(hash_table_t *hash_table, void *key, void *data) {
    CCOL_CHECK_INIT(hash_table);
    if (!key) return CCOL_STATUS_INVALID_ARG;

    size_t hash_key = hash_table->hasher.func(key, hash_table->hasher.ctx) % hash_table->num_buckets;
    ccol_status_t status;
    if (!(hash_table->buckets[hash_key])) {
        status = dll_create(
            &hash_table->buckets[hash_key],
            hash_table->copier,
            hash_table->freer,
            hash_table->printer,
            hash_table->comparator
        );

        if (status != CCOL_STATUS_OK) return status;
    }

    dll_node_t *duplicate = dll_search(hash_table->buckets[hash_key], key);
    if (duplicate) return CCOL_STATUS_ALREADY_EXISTS;

    hash_entry_t *entry = malloc(sizeof(hash_entry_t));
    if (!entry) return CCOL_STATUS_ALLOC;
    entry->key = key;
    entry->value = data;

    status = dll_push(hash_table->buckets[hash_key], entry);
    if (status != CCOL_STATUS_OK) {
        free(entry);
        return status;
    }

    hash_table->size++;
    return CCOL_STATUS_OK;
}

// Removal
ccol_status_t hash_table_remove(hash_table_t *hash_table, void *key) {
    CCOL_CHECK_INIT(hash_table);

    size_t hash_key = hash_table->hasher.func(key, hash_table->hasher.ctx) % hash_table->num_buckets;
    dll_t *bucket = hash_table->buckets[hash_key];
    if (!bucket) return CCOL_STATUS_NOT_FOUND;

    ccol_status_t status = dll_remove(bucket, key);
    if (status != CCOL_STATUS_OK) return status;

    hash_table->size--;
    return CCOL_STATUS_OK;
}

// Access
ccol_status_t hash_table_get_node(const hash_table_t *hash_table, const void *key, dll_node_t **node_out) {
    CCOL_CHECK_INIT(hash_table);

    size_t hash_key = hash_table->hasher.func(key, hash_table->hasher.ctx) % hash_table->num_buckets;
    dll_t *bucket = hash_table->buckets[hash_key];
    if (!bucket) return CCOL_STATUS_NOT_FOUND;

    dll_node_t *node = dll_search(bucket, key);
    if (!node) return CCOL_STATUS_NOT_FOUND;

    *node_out = node;

    return CCOL_STATUS_OK;
}

ccol_status_t hash_table_get(const hash_table_t *hash_table, const void *key, void **data_out) {
    CCOL_CHECK_INIT(hash_table);

    dll_node_t *node = NULL;
    ccol_status_t status = hash_table_get_node(hash_table, key, &node);
    if (status != CCOL_STATUS_OK) return status;
    hash_entry_t *entry = (hash_entry_t *)node->data;
    *data_out = entry->value;

    return CCOL_STATUS_OK;
}

ccol_status_t hash_table_get_entry(const hash_table_t *hash_table, const void *key, hash_entry_t **entry_out) {
    CCOL_CHECK_INIT(hash_table);

    dll_node_t *node = NULL;
    ccol_status_t status = hash_table_get_node(hash_table, key, &node);
    if (status != CCOL_STATUS_OK) return status;
    *entry_out = (hash_entry_t *)node->data;

    return CCOL_STATUS_OK;
}

ccol_status_t hash_table_get_all_keys(const hash_table_t *hash_table, void ***keys_out, size_t *key_count) {
	CCOL_CHECK_INIT(hash_table);
    if (!keys_out) return CCOL_STATUS_INVALID_ARG;
    if (hash_table->size == 0) {
    	*keys_out = NULL;
        *key_count = 0;
        return CCOL_STATUS_EMPTY;
    }

    void **keys = calloc(hash_table->size, sizeof(void *));
    if (!keys) return CCOL_STATUS_ALLOC;

    size_t keys_copied = 0;
    for (size_t i = 0; i < hash_table->num_buckets; i++) {
    	dll_t *bucket = hash_table->buckets[i];
    	if (!bucket) continue;

        dll_node_t *node = bucket->head;
        for (size_t j = 0; j < bucket->size; j++) {
        	hash_entry_t *entry = (hash_entry_t *)node->data;
        	keys[keys_copied++] = entry->key;
            node = node->next;
        }
    }

    *keys_out = keys;
    *key_count = keys_copied;

    return CCOL_STATUS_OK;
}

// Attributes
bool hash_table_is_empty(const hash_table_t *hash_table) {
    return (!hash_table || !hash_table->is_initialized || hash_table->size == 0);
}

size_t hash_table_size(const hash_table_t *hash_table) {
    if (!hash_table || !hash_table->is_initialized) return 0;
    return hash_table->size;
}

size_t hash_table_num_buckets(const hash_table_t *hash_table) {
    if (!hash_table || !hash_table->is_initialized) return 0;
    return hash_table->num_buckets;
}

bool hash_table_contains(const hash_table_t *hash_table, const void *key) {
    return hash_table_contains_key(hash_table, key);
}

bool hash_table_contains_key(const hash_table_t *hash_table, const void *key) {
    if (!hash_table || !hash_table->is_initialized) return 0;

    size_t hash_key = hash_table->hasher.func(key, hash_table->hasher.ctx) % hash_table->num_buckets;
    dll_t *bucket = hash_table->buckets[hash_key];
    if (!bucket) return false;

    return dll_contains(bucket, key);
}

bool hash_table_contains_value(const hash_table_t *hash_table, void *key, void *value) {
    if (!hash_table || !hash_table->is_initialized) return 0;

    size_t hash_key = hash_table->hasher.func(key, hash_table->hasher.ctx) % hash_table->num_buckets;
    dll_t *bucket = hash_table->buckets[hash_key];
    if (!bucket) return false;

    return dll_contains(bucket, value);
}

double hash_table_load_factor(const hash_table_t *hash_table) {
	if (!hash_table || !hash_table->is_initialized || hash_table->num_buckets == 0) return 0;
    return (double) hash_table->size / (double) hash_table->num_buckets;
}

// Utilities
ccol_status_t hash_table_swap(hash_table_t *hash_table, void *key1, void *key2) {
	CCOL_CHECK_INIT(hash_table);
    if (!key1 || !key2) return CCOL_STATUS_INVALID_ARG;

    hash_entry_t *entry1 = NULL, *entry2 = NULL;

    ccol_status_t status = hash_table_get_entry(hash_table, key1, &entry1);
    if (status != CCOL_STATUS_OK) return status;

    status = hash_table_get_entry(hash_table, key2, &entry2);
    if (status != CCOL_STATUS_OK) return status;

    if (entry1 == entry2) return CCOL_STATUS_OK;

    void *temp = entry1->value;
    entry1->value = entry2->value;
    entry2->value = temp;

    return CCOL_STATUS_OK;
}

ccol_status_t hash_table_resize(hash_table_t *hash_table, int new_num_buckets) {
	CCOL_CHECK_INIT(hash_table);
    if (new_num_buckets <= 0) return CCOL_STATUS_INVALID_ARG;

	dll_t **new_buckets = calloc(new_num_buckets, sizeof(dll_t *));
	if (!new_buckets) return CCOL_STATUS_ALLOC;

    hash_func_t hash_func = hash_table->hasher.func;
    void *ctx = hash_table->hasher.ctx;
	for (size_t i = 0; i < hash_table->num_buckets; i++) {
		dll_t *bucket = hash_table->buckets[i];
        if (!bucket) continue;

        ccol_status_t status;
        dll_node_t *node = bucket->head;
        for (size_t j = 0; j < bucket->size; j++) {
         	hash_entry_t *entry = (hash_entry_t *)node->data;
            size_t new_index = hash_func(entry->key, ctx) % new_num_buckets;
            if (!new_buckets[new_index]) {
            	status = dll_create(
                    &new_buckets[new_index],
                    hash_table->copier,
                    hash_table->freer,
                    hash_table->printer,
                    hash_table->comparator
                );
                if (status != CCOL_STATUS_OK) return status;
            }

            dll_push_back(new_buckets[new_index], entry);
            node = node->next;
        }
   }
   for (size_t i = 0; i < hash_table->num_buckets; i++) {
       if (hash_table->buckets[i]) {
           dll_destroy(hash_table->buckets[i]);
           free(hash_table->buckets[i]);
           hash_table->buckets[i] = NULL;
       }
   }
   free(hash_table->buckets);

   hash_table->buckets = new_buckets;
   hash_table->num_buckets = new_num_buckets;

   hash_table->size = 0;
   for (size_t i = 0; i < new_num_buckets; i++) {
       if (hash_table->buckets[i]) {
           hash_table->size += hash_table->buckets[i]->size;
       }
   }

   return CCOL_STATUS_OK;
}

// Copy / Clone
ccol_status_t hash_table_clone(const hash_table_t *src, hash_table_t **hash_table_out) {
    CCOL_CHECK_INIT(src);
    if (!hash_table_out) return CCOL_STATUS_INVALID_ARG;
    if (!src->copier.func) return CCOL_STATUS_COPY_FUNC;
    
    ccol_status_t status = hash_table_create(
        src->num_buckets,
        src->key_size,
        src->hasher.policy,
        src->hasher,
        src->copier,
        src->freer,
        src->printer,
        src->comparator,
        hash_table_out
    );
    if (status != CCOL_STATUS_OK) return status;

    if (!src->buckets) return CCOL_STATUS_OK;

    for (size_t i = 0; i < src->num_buckets; i++) {
        if (!src->buckets[i]) continue;

        status = dll_clone(src->buckets[i], &((*hash_table_out)->buckets[i]));
        if (status != CCOL_STATUS_OK) {
            hash_table_destroy(*hash_table_out);
            return status;

        }
    }

    return CCOL_STATUS_OK;
}

ccol_status_t hash_table_deep_clone(const hash_table_t *src, hash_table_t **hash_table_out) {
    CCOL_CHECK_INIT(src);
    if (!hash_table_out) return CCOL_STATUS_INVALID_ARG;

    return hash_table_clone(src, hash_table_out);
}

ccol_status_t hash_table_copy(hash_table_t *dest, hash_table_t *src) {
    CCOL_CHECK_INIT(dest);
    CCOL_CHECK_INIT(src);
    if (dest == src) return CCOL_STATUS_OK;
    
    if (!src->copier.func) return CCOL_STATUS_COPY_FUNC;

    ccol_status_t status;
    for (size_t i = 0; i < src->num_buckets; i++) {
        if (!src->buckets[i]) continue;

        if (!dest->buckets[i]) {
            dll_t* dest_bucket = NULL;
            status = dll_create(
            	&dest_bucket,
            	src->copier,
            	src->freer,
            	src->printer,
            	src->comparator
        	);

            if (status != CCOL_STATUS_OK) {
                hash_table_destroy(dest);
                return status;
            }

            status = dll_copy(dest_bucket, src->buckets[i]);
            if (status != CCOL_STATUS_OK) {
                dll_destroy(dest_bucket);
                hash_table_destroy(dest);
                return status;
            }

            dest->buckets[i] = dest_bucket;
        } else {
            status = dll_clear(dest->buckets[i]);
            if (status != CCOL_STATUS_OK) {
                hash_table_destroy(dest);
                return status;
            }

            status = dll_copy(dest->buckets[i], src->buckets[i]);
            if (status != CCOL_STATUS_OK) {
                hash_table_destroy(dest);
                return status;
            }
        }
    }

    // Clear remaining dest buckets
    for (size_t i = src->num_buckets; i < dest->num_buckets; i++) {
        if (dest->buckets[i]) {
            dll_destroy(dest->buckets[i]);
            dest->buckets[i] = NULL;
        }
    }

    // Recalculate dest size
    dest->size = 0;
    for (size_t i = 0; i < dest->num_buckets; i++) {
        if (dest->buckets[i]) dest->size += dest->buckets[i]->size;
    }

    return CCOL_STATUS_OK;
}

ccol_status_t hash_table_deep_copy(hash_table_t *dest, hash_table_t *src) {
	return hash_table_copy(dest, src);
}

// Cleanup
ccol_status_t hash_table_clear_bucket(hash_table_t *hash_table, int bucket_index) {
	CCOL_CHECK_INIT(hash_table);
    if (bucket_index < 0 || bucket_index > ((int)hash_table->num_buckets - 1)) return CCOL_STATUS_OUT_OF_BOUNDS;
    if (hash_table->size == 0) return CCOL_STATUS_OK;

    dll_t *bucket = hash_table->buckets[bucket_index];
    if (!bucket) return CCOL_STATUS_NOT_FOUND;

    hash_table->size -= dll_size(bucket);

    ccol_status_t status = dll_clear(bucket);
    return status;
}

ccol_status_t hash_table_clear(hash_table_t *hash_table) {
    CCOL_CHECK_INIT(hash_table);

    ccol_status_t final_status = CCOL_STATUS_OK;
    for (size_t i = 0; i < hash_table->num_buckets; i++) {
        ccol_status_t bucket_status = hash_table_clear_bucket(hash_table, i);
        if (bucket_status != CCOL_STATUS_OK && final_status == CCOL_STATUS_OK) final_status = bucket_status;
    }

    return final_status;
}

ccol_status_t hash_table_destroy(hash_table_t *hash_table) {
    CCOL_CHECK_INIT(hash_table);

    ccol_status_t status = hash_table_clear(hash_table);
    hash_table_uninit(hash_table);

    return status;
}

ccol_status_t hash_table_free(hash_table_t **hash_table_ptr) {
	if (!hash_table_ptr || !*hash_table_ptr || !(*hash_table_ptr)->is_initialized) return CCOL_STATUS_INVALID_ARG;

    ccol_status_t status = hash_table_destroy(*hash_table_ptr);
    free(*hash_table_ptr);
    *hash_table_ptr = NULL;

    return status;
}

// Print / Debug
ccol_status_t hash_table_print(hash_table_t *hash_table) {
	CCOL_CHECK_INIT(hash_table);
    if (!hash_table->printer.func) return CCOL_STATUS_INVALID_ARG;
    if (hash_table->size == 0) {
    	printf("[]\n");
        return CCOL_STATUS_OK;
    }

    ccol_status_t status = CCOL_STATUS_OK;
    for (size_t i = 0; i < hash_table->num_buckets; i++) {
    	dll_t *bucket = hash_table->buckets[i];
        if (!bucket) continue;

        printf("Bucket[%zu]: ", i);
        status = dll_print(bucket);
        if (status != CCOL_STATUS_OK) return status;
    }

    return CCOL_STATUS_OK;
}
