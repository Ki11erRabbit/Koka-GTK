#include <gtk/gtk.h>


static inline intptr_t kk_gtk_button_new_with_label(kk_string_t label, kk_context_t* ctx) {
    kk_ssize_t len;
    const char *buf = kk_string_buf_borrow(label, &len, ctx);
    char *str = kk_malloc(len + 1, ctx);
    memcpy(str, buf, len);
    str[len] = '\0';

    GtkWidget* button = gtk_button_new_with_label(str);
    kk_free(str, ctx);

    return (intptr_t)button;
}

static void gtk_button_clicked_callback(kk_gtk_widget_button__gtk_button button, kk_function_t callback) {
    kk_context_t* ctx = kk_get_context();
    kk_function_call(kk_box_t, (kk_function_t, kk_gtk_widget_button__gtk_button, kk_context_t*), callback, (callback, button, ctx), ctx);
    kk_free_context();
}

static inline void kk_gtk_button_connect_clicked(kk_gtk_widget_button__gtk_button button, kk_function_t callback, kk_context_t* ctx) {
    kk_block_t* box = kk_block_dup((kk_block_t*)callback.dbox);
    g_signal_connect((GtkWidget*)(button.base.pointer.ptr), "clicked", G_CALLBACK(gtk_button_clicked_callback), box);
}