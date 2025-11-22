#!/bin/sh

GTK_INCLUDE=$(pkg-config gtk4 --cflags)
#GTK_INCLUDE=${GTK_INCLUDE// / --ccopts=}
GTK_LIBS=$(pkg-config gtk4 --libs)
#GTK_LIBS=${GTK_LIBS// / --ccopts=}

#echo "${GTK_INCLUDE} ${GTK_LIBS}"

#koka --include=../std --ccopts="${GTK_INCLUDE} ${GTK_LIBS}" main.kk -o test.out

koka --include=../std --include=../Koka-GTK/gobject "--ccincdir=/nix/store/0784w06097k9i46zipgjf05l87i19jj0-glib-2.84.3-dev/include/glib-2.0;/nix/store/8gfq9pn1shnhi6mha2a56aa3ny7g9r6f-glib-2.84.3/lib/glib-2.0/include;/nix/store/r6bfsfxlvc6xw2vqhszym2ibp9fms1zr-gtk4-4.18.6-dev/include/gtk-4.0;/nix/store/l4qp25bavh9yqpk4q0b3zminn9zsgl5p-cairo-1.18.2-dev/include/cairo;/nix/store/79b83lm0fwilxc816z4pcvd58j1j3cdd-freetype-2.13.3-dev/include/freetype2;/nix/store/79b83lm0fwilxc816z4pcvd58j1j3cdd-freetype-2.13.3-dev/include;/nix/store/53ahz0rv7prrcqk5snjd2dda2km8mk4l-gdk-pixbuf-2.42.12-dev/include/gdk-pixbuf-2.0;/nix/store/0rzrwwy1hacsv5yjqn02wh34gnn0l74b-graphene-1.10.8-dev/include/graphene-1.0;/nix/store/jr0ankf63ki8g46f3a2nprgqawnq27ym-graphene-1.10.8/lib/graphene-1.0/include;/nix/store/f1cxz5ch15xdg20lc8b83q7crbfqphlv-pango-1.56.3-dev/include/pango-1.0;/nix/store/61d844iw2isz4cc8dn1rdmzn89cp2qzx-harfbuzz-10.2.0-dev/include/harfbuzz;/nix/store/a3qs5lq9ls4n1nfv7lrq0mmi9yn6v16q-vulkan-headers-1.4.313.0/include" "--cclib=glib-2.0;gio-2.0;gobject-2.0;gtk-4" main.kk -o test.out