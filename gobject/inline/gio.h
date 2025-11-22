#include <stdint.h>
#include <gio/gio.h>
#include <glib-object.h>


static inline intptr_t kk_g_application_new(kk_context_t* ctx) {
    return (intptr_t)g_application_new(NULL, 0);
}

static inline int32_t kk_gio_application_run(kk_gio__g_application app, kk_std_core_types__list arg_list, kk_context_t* ctx) {
    kk_gobject__gobject raw = app.base;
    kk_integer_t integer = kk_std_core_list_length(arg_list, ctx);
    kk_ssize_t length = kk_integer_clamp_ssize_t(integer, ctx);
    uint8_t **args = kk_malloc(length * sizeof(uint8_t*), ctx);

    kk_std_core_types__maybe item;
    int current_index = 0;
    while (!kk_box_is_Nothing(kk_std_core_types__maybe_box((item = kk_std_core_list_maybe_fs_head(arg_list, ctx)), ctx))) {
        kk_box_t box = kk_std_core_maybe_default(item, kk_bool_box(false), ctx);
        kk_string_t string = kk_string_unbox(box);
        kk_ssize_t len;
        const char *buf = kk_string_buf_borrow(string, &len, ctx);
        char *str = kk_malloc(len + 1, ctx);
        memcpy(str, buf, len);
        str[len] = '\0';
        args[current_index] = str;
        current_index++;
        arg_list = kk_std_core_list_tail(arg_list, ctx);
    }

    GApplication *application = (GApplication *)raw.pointer.ptr;
    int out = g_application_run(application, length, (char**)args);


    kk_free(args, ctx);
    return out;
}

static void g_app_connect_callback(kk_gio__g_application app, kk_function_t callback) {
    printf("getting context\n");
    kk_context_t* ctx = kk_get_context();
    printf("calling callback\n");
    //kk_function_call(kk_box_t, (kk_gio__g_application, kk_context_t*), callback, (app, ctx), ctx);
    kk_box_t(*fn_ptr)(kk_gio__g_application, kk_context_t*) = (kk_box_t(*)(kk_gio__g_application, kk_context_t*))kk_kkfun_ptr_unbox(kk_datatype_as_assert(struct kk_function_s*,callback,KK_TAG_FUNCTION, ctx)->fun, ctx);
    fn_ptr(app, ctx);
    printf("called callback\n");
    kk_free_context();
}

static inline void kk_g_app_connect_activate(kk_gio__g_application app, kk_function_t callback, kk_context_t* ctx) {
    kk_gobject__gobject base = app.base;
    kk_block_t* box = kk_block_dup((kk_block_t*)callback.dbox);
    g_signal_connect((GApplication*)(base.pointer.ptr), "activate", G_CALLBACK(g_app_connect_callback), box);
}