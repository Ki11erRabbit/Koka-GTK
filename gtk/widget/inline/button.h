#include <gtk/gtk.h>

extern void gobject_free(void*, kk_block_t*, kk_context_t*);

static inline struct kk_gtk_widget_button_Gtk_button kk_gtk_button_new_with_label(kk_string_t label, kk_context_t* ctx) {
    kk_ssize_t len;
    const char *buf = kk_string_buf_borrow(label, &len, ctx);
    char *str = kk_malloc(len + 1, ctx);
    memcpy(str, buf, len);
    str[len] = '\0';

    void* raw = (void*)gtk_button_new_with_label(str);
    kk_box_t box = kk_cptr_raw_box((kk_free_fun_t*)gobject_free, raw, ctx);
    struct kk_gobject_gobject_Gobject base = { .pointer = (intptr_t)box.box };
    struct kk_gtk_widget_button_Gtk_button button = { .base = base };
    kk_free(str, ctx);

    return button;
}

static void gtk_button_clicked_callback(struct kk_gtk_widget_button_Gtk_button button, kk_function_t callback) {
    kk_context_t* ctx = kk_get_context();
    kk_function_call(kk_box_t, (kk_function_t, kk_gtk_widget_button__gtk_button, kk_context_t*), callback, (callback, button, ctx), ctx);
    kk_free_context();
}

static inline void kk_gtk_button_connect_clicked(struct kk_gtk_widget_button_Gtk_button button, kk_function_t callback, kk_context_t* ctx) {
    struct kk_gobject_gobject_Gobject base = button.base;
    kk_box_t box = kk_intptr_box(base.pointer, ctx);
    void *raw = kk_cptr_unbox_borrowed(box, ctx);
    kk_block_t* fn_box = kk_block_dup((kk_block_t*)callback.dbox);
    g_signal_connect((GtkWidget*)raw, "clicked", G_CALLBACK(gtk_button_clicked_callback), fn_box);
}