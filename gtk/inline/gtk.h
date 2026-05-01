#include <gtk/gtk.h>
#include <stdint.h>



static inline kk_gtk_gtk__gtk_application kk_gtk_app_new(kk_context_t* ctx) {
    GtkApplication* raw = gtk_application_new(NULL, G_APPLICATION_DEFAULT_FLAGS);
    struct kk_gobject_gobject_Gobject base = { .pointer = (intptr_t)(uintptr_t)raw };
    kk_gtk_gtk__gtk_application app = { .base = base };
    return app;
}


/*static inline intptr_t kk_gtk_app_new(kk_gobject_gio__g_application app, kk_context_t* ctx) {
    GtkApplication *gtk_app = GTK_APPLICATION((GApplication *)app.base.pointer.ptr);
    return (intptr_t)gtk_app;
}*/

static inline int32_t kk_gtk_application_run(kk_gtk_gtk__gtk_application app, kk_std_core_types__list arg_list, kk_context_t* ctx) {
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
    g_object_unref((gpointer)raw);
    return out;
}

static void gtk_app_connect_callback(GtkApplication* gapp, gpointer user_data) {
    kk_context_t* ctx = kk_get_context();
    
    // Unpack the heap-allocated function we passed as user_data
    kk_function_t* fn_ptr = (kk_function_t*)user_data;
    kk_function_t callback = *fn_ptr;
    
    // Reconstruct the Koka app wrapper from the raw GtkApplication pointer
    struct kk_gobject_gobject_Gobject base = { (intptr_t)(uintptr_t)gapp };
    kk_gtk_gtk__gtk_application app = { base };
    
    // Call the Koka function
    kk_function_call(kk_box_t, (kk_function_t, kk_gtk_gtk__gtk_application, kk_context_t*), 
                     callback, (callback, app, ctx), ctx);
    
    // Free the heap allocation from connect_activate
    kk_free(fn_ptr, ctx);
}

static inline void kk_gtk_app_connect_activate(kk_gtk_gtk__gtk_application app, kk_function_t callback, kk_context_t* ctx) {
    struct kk_gobject_gobject_Gobject base = app.base;
    GtkApplication* raw = (GtkApplication*)(uintptr_t)base.pointer;
    
    kk_function_dup(callback, ctx);
    kk_function_t* fn_box = (kk_function_t*)kk_malloc(sizeof(kk_function_t), ctx);
    *fn_box = callback;
    
    g_signal_connect(raw, "activate", G_CALLBACK(gtk_app_connect_callback), fn_box);
}


static inline kk_std_core_types__maybe kk_gtk_get_active_window(kk_gtk_gtk__gtk_application app, kk_context_t* ctx) {
    struct kk_gobject_gobject_Gobject base = app.base;
    kk_box_t box = kk_intptr_box(base.pointer, ctx);
    void *raw = kk_cptr_unbox_borrowed(box, ctx);

    GtkWindow *window = gtk_application_get_active_window((GtkApplication*)raw);

    if (!window) {
        return kk_std_core_types__new_Nothing(ctx);
    }
    kk_std_core_types__maybe out = kk_std_core_types__new_Just(kk_int64_box((int64_t)window, ctx), ctx);
    return out;
}

static inline struct kk_gtk_window_Gtk_window kk_gtk_create_window(kk_gtk_gtk__gtk_application app, kk_context_t* ctx) {
    GtkApplication* raw = (GtkApplication*)(uintptr_t)app.base.pointer;
    GtkWidget* window_raw = gtk_application_window_new(raw);
    struct kk_gobject_gobject_Gobject window_base = { .pointer = (intptr_t)(uintptr_t)window_raw };
    struct kk_gtk_window_Gtk_window window = { .base = window_base };
    return window;
}