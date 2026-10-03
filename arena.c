#include "./arena.h"

void arena_init(Arena* a, void* backing_buffer, size_t backing_buffer_len)
{
    if (!a) return;
    a->buf     = backing_buffer;
    a->buf_len = backing_buffer_len;
    a->offset  = 0;
}

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

void* arena_alloc_align(Arena* a, size_t size, size_t align)
{
    if (!a) return NULL;
    uintptr_t curr_ptr = (uintptr_t)a->buf + (uintptr_t)a->offset;
    uintptr_t offset = align_forward(curr_ptr, align);
    offset -= (uintptr_t)a->buf; // Change to relative offset
    if (offset + size <= a->buf_len){

        void* ptr = &a->buf[offset];
        a->offset = offset + size;

        memset(ptr, 0, size);
        return ptr;
    }
    return NULL;
}

void* arena_alloc(Arena* a, size_t size)
{
    return arena_alloc_align(a, size, DEFAULT_ALIGNMENT);
}

void arena_reset(Arena* a)
{
    if (!a) return;
    a->offset = 0;
}
