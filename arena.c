#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

uint8_t*	arena_buffer;
size_t		arena_buffer_len;
size_t		arena_offset;

static bool is_power_of_2(uintptr_t x)
{
    return (x & (x - 1)) == 0;
}

static uintptr_t align_forward(uintptr_t ptr, size_t align)
{
    uintptr_t p, a, modulo;
    assert(is_power_of_2(align));

    p = ptr;
    a = (uintptr_t)align;
    modulo = p & (a - 1);

    if (modulo != 0) {
        p += a - modulo;
    }
    return p;
}

void* arena_alloc(size_t size)
{
    if (arena_offset + size <= arena_buffer_len) {
        void* ptr = &arena_buffer[arena_offset];
        arena_offset += size;
        memset(ptr, 0, size);
        return ptr;
    }
    return NULL;
}
