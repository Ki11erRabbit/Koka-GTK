#include <gtk/gtk.h>
#include <stdint.h>

static inline intptr_t kk_gtk_box_new(int32_t orientation, int32_t spacing, kk_context_t* ctx) {
    return (intptr_t)gtk_box_new(orientation, spacing);
}

static inline void kk_gtk_box_append(kk_gtk_widget_box__gtk_box box, kk_gtk_widget_core__gtk_widget widget, kk_context_t* ctx) {
    gtk_box_append((GtkBox*)box.base.pointer.ptr, (GtkWidget*)widget.base.pointer.ptr);
}