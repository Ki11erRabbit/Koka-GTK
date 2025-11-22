#include <gtk/gtk.h>

static inline void kk_gtk_window_present(kk_gtk_window__gtk_window window, kk_context_t* ctx) {
    gtk_window_present((GtkWindow*)window.base.pointer.ptr);
}