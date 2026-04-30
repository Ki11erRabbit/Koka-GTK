#include <stdint.h>
#include <gio/gio.h>
#include <glib-object.h>
#include "gobject_gobject.h"

extern void gobject_free(void*, kk_block_t*, kk_context_t*);


static inline struct kk_gobject_gio_G_application kk_g_application_new(kk_context_t* ctx) {
    void* raw = (void*)g_application_new(NULL, 0);
    kk_box_t box = kk_cptr_raw_box((kk_free_fun_t*)gobject_free, raw, ctx);
    struct kk_gobject_gobject_Gobject base = { .pointer = (intptr_t)box.box };
    struct kk_gobject_gio_G_application app = { .base = base };
    return app;
}

static inline int32_t kk_gio_application_run(struct kk_gobject_gio_G_application app, kk_std_core_types__list arg_list, kk_context_t* ctx) {
    struct kk_gobject_gobject_Gobject base = app.base;
    kk_box_t box = kk_intptr_box(base.pointer, ctx);
    void *raw = kk_cptr_unbox_borrowed(box, ctx);
    kk_integer_t integer = kk_std_core_list_length(arg_list, ctx);
    kk_ssize_t length = kk_integer_clamp_ssize_t(integer, ctx);
    uint8_t **args = kk_malloc(length * sizeof(uint8_t*), ctx);

    kk_std_core_types__maybe item;
    int current_index = 0;
    while (!kk_box_is_Nothing(kk_std_core_types__maybe_box((item = kk_std_core_list_maybe_fs_head(arg_list, ctx)), ctx))) {
        kk_box_t box = kk_std_core_maybe_default(item, kk_bool_box(false), ctx);
        kk_string_t string = kk_string_unbox(box);
        kk_ssize_t len;
        const char *buf = kk_string_buf_borrow(string, &len, ctx);
        char *str = kk_malloc(len + 1, ctx);
        memcpy(str, buf, len);
        str[len] = '\0';
        args[current_index] = str;
        current_index++;
        arg_list = kk_std_core_list_tail(arg_list, ctx);
    }

    GApplication *application = (GApplication *)raw;
    int out = g_application_run(application, length, (char**)args);

    for (int i = 0; i < length; i++) {
        kk_free(args[i], ctx);
    }

    kk_free(args, ctx);
    return out;
}

static void g_app_connect_callback(struct kk_gobject_gio_G_application app, kk_function_t callback) {
    kk_context_t* ctx = kk_get_context();
    kk_function_call(kk_box_t, (kk_function_t, struct kk_gobject_gio_G_application, kk_context_t*), callback, (callback, app, ctx), ctx);
    kk_free_context();
}

static inline void kk_g_app_connect_activate(struct kk_gobject_gio_G_application app, kk_function_t callback, kk_context_t* ctx) {
    struct kk_gobject_gobject_Gobject base = app.base;
    kk_box_t box = kk_intptr_box(base.pointer, ctx);
    void *raw = kk_cptr_unbox_borrowed(box, ctx);
    kk_block_t* fn_box = kk_block_dup((kk_block_t*)callback.dbox);
    g_signal_connect((GApplication*)raw, "activate", G_CALLBACK(g_app_connect_callback), fn_box);
}