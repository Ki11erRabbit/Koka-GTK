#include <glib-object.h>
#include <stdint.h>

void gobject_free(void* p, kk_block_t* box, kk_context_t* ctx) {
    g_object_unref((gpointer)p);
}

static inline struct kk_gobject_gobject_Gobject kk_gobject_from(kk_box_t ptr, kk_context_t* ctx) {
    void* raw = kk_cptr_unbox_borrowed(ptr, ctx);
    kk_box_t box = kk_cptr_raw_box((kk_free_fun_t*)gobject_free, raw, ctx);
    struct kk_gobject_gobject_Gobject out = { .pointer = (intptr_t)box.box };
    return out;
}