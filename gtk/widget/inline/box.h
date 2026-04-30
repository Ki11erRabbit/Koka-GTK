#include <gtk/gtk.h>
#include <stdint.h>

extern void gobject_free(void*, kk_block_t*, kk_context_t*);

static inline struct kk_gtk_widget_box_Gtk_box kk_gtk_box_new(int32_t orientation, int32_t spacing, kk_context_t* ctx) {
    void* raw = (void*)gtk_box_new(orientation, spacing);
    kk_box_t box = kk_cptr_raw_box((kk_free_fun_t*)gobject_free, raw, ctx);
    struct kk_gobject_gobject_Gobject base = { .pointer = (intptr_t)box.box };
    struct kk_gtk_widget_box_Gtk_box out = { .base = base };
    return out;
}

static inline void kk_gtk_box_append(struct kk_gtk_widget_box_Gtk_box box, kk_gtk_widget_core__gtk_widget widget, kk_context_t* ctx) {
    struct kk_gobject_gobject_Gobject box_base = box.base;
    kk_box_t box_box = kk_intptr_box(box_base.pointer, ctx);
    void *box_raw = kk_cptr_unbox_borrowed(box_box, ctx);
    struct kk_gobject_gobject_Gobject widget_base = box.base;
    kk_box_t widget_box = kk_intptr_box(widget_base.pointer, ctx);
    void *widget_raw = kk_cptr_unbox_borrowed(widget_box, ctx);
    gtk_box_append((GtkBox*)box_raw, (GtkWidget*)widget_raw);
}