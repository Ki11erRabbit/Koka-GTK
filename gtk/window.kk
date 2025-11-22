/*----------------------------------------------------------------------------
   Copyright 2024, Koka-Community Authors

   Licensed under the MIT License ("The License"). You may not
   use this file except in compliance with the License. A copy of the License
   can be found in the LICENSE file at the root of this distribution.
----------------------------------------------------------------------------*/
module gtk/window

import gobject/gobject
import gtk/widget/core

extern import
  c file "inline/window.h"

pub struct gtk-window
  base : gobject

pub fun gtk-window/from(ptr : intptr_t) : gtk-window
  Gtk-window(gobject/from(ptr))

pub fun gtk-window/into(window : gtk-window) : gtk-widget
  Gtk-widget(window.base)

pub extern gtk-window/present(window : gtk-window) : ()
  c inline "kk_gtk_window_present(#1, kk_context())"

pub extern gtk-window/set-title(window : gtk-window, title : string) : ()
  c inline "kk_gtk_window_set_title(#1, #2, kk_context())"

pub extern gtk-window/set-child(window : gtk-window, widget : gtk-widget) : ()
  c inline "kk_gtk_window_set_child(#1, #2, kk_context())"