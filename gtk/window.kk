/*----------------------------------------------------------------------------
   Copyright 2024, Koka-Community Authors

   Licensed under the MIT License ("The License"). You may not
   use this file except in compliance with the License. A copy of the License
   can be found in the LICENSE file at the root of this distribution.
----------------------------------------------------------------------------*/
module gtk/window

import gobject/gobject

extern import
  c file "inline/window.h"

pub struct gtk-window
  base : gobject

pub fun gtk-window/from(ptr : intptr_t) : gtk-window
  Gtk-window(gobject/from(ptr))

pub extern gtk-window/present(window : gtk-window) : ()
  c inline "kk_gtk_window_present(#1, kk_context())"