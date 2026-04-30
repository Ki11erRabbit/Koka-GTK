#!/bin/sh
set -e

# Get flags from pkg-config
GTK_CFLAGS=$(pkg-config --cflags gtk4 glib-2.0 gio-2.0 gobject-2.0)
GTK_LIBS=$(pkg-config --libs gtk4 glib-2.0 gio-2.0 gobject-2.0)

# Extract include dirs (-I/path) and convert to semicolon-separated list for --ccincdir
CCINCDIR=$(echo "$GTK_CFLAGS" | tr ' ' '\n' | grep '^-I' | sed 's/^-I//' | tr '\n' ';' | sed 's/;$//')

# Extract lib dirs (-L/path) for --cclibdir
CCLIBDIR=$(echo "$GTK_LIBS" | tr ' ' '\n' | grep '^-L' | sed 's/^-L//' | tr '\n' ';' | sed 's/;$//')

# Extract lib names (-lfoo) for --cclib
CCLIB=$(echo "$GTK_LIBS" | tr ' ' '\n' | grep '^-l' | sed 's/^-l//' | tr '\n' ';' | sed 's/;$//')

echo "Include dirs: $CCINCDIR"
echo "Lib dirs:     $CCLIBDIR"
echo "Libs:         $CCLIB"

koka \
  --include=../std \
  --include=../Koka-GTK/gobject \
  "--ccincdir=${CCINCDIR}" \
  "--cclibdir=${CCLIBDIR}" \
  "--cclib=${CCLIB}" \
  main.kk \
  "$@"