#include <gtk/gtk.h>
#include <stdint.h>

static inline struct kk_gtk_widget_box_Gtk_box kk_gtk_box_new(int32_t orientation, int32_t spacing, kk_context_t* ctx) {
    GtkWidget* raw = gtk_box_new(orientation, spacing);
    struct kk_gobject_gobject_Gobject base = { .pointer = (intptr_t)(uintptr_t)raw };
    struct kk_gtk_widget_box_Gtk_box out = { .base = base };
    return out;
}

static inline void kk_gtk_box_append(struct kk_gtk_widget_box_Gtk_box box, kk_gtk_widget_core__gtk_widget widget, kk_context_t* ctx) {
    GtkBox* box_raw = (GtkBox*)(uintptr_t)box.base.pointer;
    GtkWidget* widget_raw = (GtkWidget*)(uintptr_t)widget.base.pointer;
    gtk_box_append(box_raw, widget_raw);
}