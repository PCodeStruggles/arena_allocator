#ifndef ARENA_H
#define ARENA_H

#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

#ifndef DEFAULT_ALIGNMENT
#define DEFAULT_ALIGNMENT (2 * sizeof(void*))
#endif

typedef struct Arena Arena;
typedef struct Temp_Arena Temp_Arena;

void  arena_init(Arena* a, void* backing_buffer, size_t backing_buffer_len);
void* arena_alloc_align(Arena* a, size_t size, size_t align);
void* arena_alloc(Arena* a, size_t size);
Temp_Arena temp_arena_begin(Arena* a);
void temp_arena_end(Temp_Arena tmp);
void  arena_reset(Arena* a);

#endif // ARENA_H
