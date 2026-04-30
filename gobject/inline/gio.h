#include <stdint.h>
#include <gio/gio.h>
#include <glib-object.h>
#include "gobject_gobject.h"


static inline struct kk_gobject_gio_G_application kk_g_application_new(kk_context_t* ctx) {
    void* raw = (void*)g_application_new(NULL, 0);
    struct kk_gobject_gobject_Gobject base = { .pointer = (intptr_t)(uintptr_t)raw };
    struct kk_gobject_gio_G_application app = { .base = base };
    return app;
}

static inline int32_t kk_gio_application_run(struct kk_gobject_gio_G_application app, kk_std_core_types__list arg_list, kk_context_t* ctx) {
    GApplication* raw = (GApplication*)(uintptr_t)app.base.pointer;

    kk_integer_t integer = kk_std_core_list_length(arg_list, ctx);
    kk_ssize_t length = kk_integer_clamp_ssize_t(integer, ctx);
    char** args = (char**)kk_malloc(length * sizeof(char*), ctx);

    int current_index = 0;
    kk_std_core_types__list current = arg_list;
    while (kk_std_core_types__is_Cons(current, ctx)) {
        struct kk_std_core_types_Cons* cons = kk_std_core_types__as_Cons(current, ctx);
        kk_string_t string = kk_string_unbox(cons->head);
        kk_ssize_t len;
        const char* buf = kk_string_buf_borrow(string, &len, ctx);
        char* str = (char*)kk_malloc(len + 1, ctx);
        memcpy(str, buf, len);
        str[len] = '\0';
        args[current_index++] = str;
        current = cons->tail;
    }

    int out = g_application_run(raw, (int)length, args);

    for (int i = 0; i < current_index; i++) {
        kk_free(args[i], ctx);
    }
    kk_free(args, ctx);
    return out;
}

static void g_app_connect_callback(GApplication* gapp, gpointer user_data) {
    kk_context_t* ctx = kk_get_context();
    
    // Unpack the heap-allocated function we passed as user_data
    kk_function_t* fn_ptr = (kk_function_t*)user_data;
    kk_function_t callback = *fn_ptr;
    
    // Reconstruct the Koka app wrapper from the raw GtkApplication pointer
    struct kk_gobject_gobject_Gobject base = { (intptr_t)(uintptr_t)gapp };
    struct kk_gobject_gio_G_application app = { base };
    
    // Call the Koka function
    kk_function_call(kk_box_t, (kk_function_t, struct kk_gobject_gio_G_application, kk_context_t*), 
                     callback, (callback, app, ctx), ctx);
    
    // Free the heap allocation from connect_activate
    kk_free(fn_ptr, ctx);
}

static inline void kk_g_app_connect_activate(struct kk_gobject_gio_G_application app, kk_function_t callback, kk_context_t* ctx) {
    struct kk_gobject_gobject_Gobject base = app.base;
    kk_box_t box = kk_intptr_box(base.pointer, ctx);
    void *raw = kk_cptr_unbox_borrowed(box, ctx);
    kk_block_t* fn_box = kk_block_dup((kk_block_t*)callback.dbox);
    g_signal_connect((GApplication*)raw, "activate", G_CALLBACK(g_app_connect_callback), fn_box);
}