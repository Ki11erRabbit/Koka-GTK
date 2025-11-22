#include <glib-object.h>


static inline void kk_object_unref(kk_gobject_gobject__gobject object, kk_context_t* ctx) {
    g_object_unref((gpointer)object.pointer.ptr);
}

