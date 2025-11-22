#include <gtk/gtk.h>

static inline void kk_gtk_window_present(kk_gtk_window__gtk_window window, kk_context_t* ctx) {
    gtk_window_present((GtkWindow*)window.base.pointer.ptr);
}


static inline void kk_gtk_window_set_title(kk_gtk_window__gtk_window window, kk_string_t title, kk_context_t* ctx) {
    kk_ssize_t len;
    const char *buf = kk_string_buf_borrow(title, &len, ctx);
    char *str = kk_malloc(len + 1, ctx);
    memcpy(str, buf, len);
    str[len] = '\0';

    gtk_window_set_title((GtkWindow*)window.base.pointer.ptr, str);
    kk_free(str, ctx);
}

static inline void kk_gtk_window_set_child(kk_gtk_window__gtk_window window, kk_gtk_widget_core__gtk_widget child, kk_context_t* ctx) {
    gtk_window_set_child((GtkWindow*)window.base.pointer.ptr, (GtkWidget*)child.base.pointer.ptr);
}