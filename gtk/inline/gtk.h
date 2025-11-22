#include <gtk/gtk.h>



static inline intptr_t kk_gtk_app_new(kk_context_t* ctx) {
    return (intptr_t)gtk_application_new(NULL, 0);
}


/*static inline intptr_t kk_gtk_app_new(kk_gobject_gio__g_application app, kk_context_t* ctx) {
    GtkApplication *gtk_app = GTK_APPLICATION((GApplication *)app.base.pointer.ptr);
    return (intptr_t)gtk_app;
}*/

static inline int32_t kk_gtk_application_run(kk_gtk_gtk__gtk_application app, kk_std_core_types__list arg_list, kk_context_t* ctx) {
    kk_gobject_gobject__gobject raw = app.base;
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

    GApplication *application = (GApplication *)raw.pointer.ptr;
    int out = g_application_run(application, length, (char**)args);

    for (int i = 0; i < length; i++) {
        kk_free(args[i], ctx);
    }

    kk_free(args, ctx);
    return out;
}

static void gtk_app_connect_callback(kk_gtk_gtk__gtk_application app, kk_function_t callback) {
    kk_context_t* ctx = kk_get_context();
    kk_function_call(kk_box_t, (kk_function_t, kk_gtk_gtk__gtk_application, kk_context_t*), callback, (callback, app, ctx), ctx);
    kk_free_context();
}

static inline void kk_gtk_app_connect_activate(kk_gtk_gtk__gtk_application app, kk_function_t callback, kk_context_t* ctx) {
    kk_gobject_gobject__gobject base = app.base;
    kk_block_t* box = kk_block_dup((kk_block_t*)callback.dbox);
    g_signal_connect((GtkApplication*)(base.pointer.ptr), "activate", G_CALLBACK(gtk_app_connect_callback), box);
}


static inline kk_std_core_types__maybe kk_gtk_get_active_window(kk_gtk_gtk__gtk_application app, kk_context_t* ctx) {
    GtkWindow *window = gtk_application_get_active_window((GtkApplication*)app.base.pointer.ptr);

    if (!window) {
        return kk_std_core_types__new_Nothing(ctx);
    }
    kk_std_core_types__maybe out = kk_std_core_types__new_Just(kk_intptr_box((intptr_t)window, ctx), ctx);
    return out;
}

static inline intptr_t kk_gtk_create_window(kk_gtk_gtk__gtk_application app, kk_context_t* ctx) {
    GtkWidget* window = gtk_application_window_new((GtkApplication*)app.base.pointer.ptr);

    return (intptr_t)window;
}