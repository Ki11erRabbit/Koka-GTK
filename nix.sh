#!/bin/sh

koka --include=../std --include=../Koka-GTK/gobject "--ccincdir=/nix/store/0784w06097k9i46zipgjf05l87i19jj0-glib-2.84.3-dev/include/glib-2.0;/nix/store/8gfq9pn1shnhi6mha2a56aa3ny7g9r6f-glib-2.84.3/lib/glib-2.0/include" "--cclib=glib-2.0;gio-2.0;gobject-2.0" main.kk -o test.out