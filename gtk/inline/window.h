#include <gtk/gtk.h>

static inline void kk_gtk_window_present(kk_gtk_window__gtk_window window, kk_context_t* ctx) {
    struct kk_gobject_gobject_Gobject base = window.base;
    kk_box_t box = kk_intptr_box(base.pointer, ctx);
    void *raw = kk_cptr_unbox_borrowed(box, ctx);
    gtk_window_present((GtkWindow*)raw);
}


static inline void kk_gtk_window_set_title(kk_gtk_window__gtk_window window, kk_string_t title, kk_context_t* ctx) {
    kk_ssize_t len;
    const char *buf = kk_string_buf_borrow(title, &len, ctx);
    char *str = kk_malloc(len + 1, ctx);
    memcpy(str, buf, len);
    str[len] = '\0';

    struct kk_gobject_gobject_Gobject base = window.base;
    kk_box_t box = kk_intptr_box(base.pointer, ctx);
    void *raw = kk_cptr_unbox_borrowed(box, ctx);

    gtk_window_set_title((GtkWindow*)raw, str);
    kk_free(str, ctx);
}

static inline void kk_gtk_window_set_child(kk_gtk_window__gtk_window window, kk_gtk_widget_core__gtk_widget child, kk_context_t* ctx) {
    struct kk_gobject_gobject_Gobject window_base = window.base;
    kk_box_t window_box = kk_intptr_box(window_base.pointer, ctx);
    void *window_raw = kk_cptr_unbox_borrowed(window_box, ctx);

    struct kk_gobject_gobject_Gobject child_base = child.base;
    kk_box_t child_box = kk_intptr_box(child_base.pointer, ctx);
    void *child_raw = kk_cptr_unbox_borrowed(child_box, ctx);
    gtk_window_set_child((GtkWindow*)window_raw, (GtkWidget*)child_raw);
}