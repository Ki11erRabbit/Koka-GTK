#include <gtk/gtk.h>

static inline struct kk_gtk_widget_button_Gtk_button kk_gtk_button_new_with_label(kk_string_t label, kk_context_t* ctx) {
    kk_ssize_t len;
    const char* buf = kk_string_buf_borrow(label, &len, ctx);
    char* str = (char*)kk_malloc(len + 1, ctx);
    memcpy(str, buf, len);
    str[len] = '\0';
    GtkWidget* raw = gtk_button_new_with_label(str);
    kk_free(str, ctx);
    struct kk_gobject_gobject_Gobject base = { .pointer = (intptr_t)(uintptr_t)raw };
    struct kk_gtk_widget_button_Gtk_button button = { .base = base };
    return button;
}

static void gtk_button_clicked_callback(GtkWidget* gbutton, gpointer user_data) {
    kk_context_t* ctx = kk_get_context();
    kk_function_t* fn_ptr = (kk_function_t*)user_data;
    kk_function_t callback = *fn_ptr;
    struct kk_gobject_gobject_Gobject base = { .pointer = (intptr_t)(uintptr_t)gbutton };
    struct kk_gtk_widget_button_Gtk_button button = { .base = base };
    kk_function_call(kk_box_t, (kk_function_t, struct kk_gtk_widget_button_Gtk_button, kk_context_t*), callback, (callback, button, ctx), ctx);
}

static inline void kk_gtk_button_connect_clicked(struct kk_gtk_widget_button_Gtk_button button, kk_function_t callback, kk_context_t* ctx) {
    GtkWidget* raw = (GtkWidget*)(uintptr_t)button.base.pointer;
    kk_function_dup(callback, ctx);
    kk_function_t* fn_box = (kk_function_t*)kk_malloc(sizeof(kk_function_t), ctx);
    *fn_box = callback;
    g_signal_connect(raw, "clicked", G_CALLBACK(gtk_button_clicked_callback), fn_box);
}