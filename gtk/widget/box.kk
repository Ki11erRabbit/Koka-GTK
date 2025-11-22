/*----------------------------------------------------------------------------
   Copyright 2025, Koka-Community Authors

   Licensed under the MIT License ("The License"). You may not
   use this file except in compliance with the License. A copy of the License
   can be found in the LICENSE file at the root of this distribution.
----------------------------------------------------------------------------*/
module gtk/widget/box

import gobject/gobject
import gtk/widget/core
import gtk/gtk
import std/num/int32


extern import
  c file "inline/box.h"


pub struct gtk-box
  base : gobject

pub fun gtk-box/from(ptr : intptr_t) : gtk-box
  Gtk-box(gobject/from(ptr))

pub fun gtk-box/into(box : gtk-box) : gtk-widget
  Gtk-widget(box.base)

extern gtk-box/gtk-box-new-internal(orientation : int32, spacing : int32) : intptr_t
  c inline "kk_gtk_box_new(#1, #2, kk_context())"

pub fun gtk-box/gtk-box-new(orientation : gtk-orientation, spacing : int) : gtk-box
  gtk-box/from(gtk-box/gtk-box-new-internal(orientation.int32, spacing.int32))

pub extern gtk-box/append(box : gtk-box, widget : gtk-widget) : ()
  c inline "kk_gtk_box_append(#1, #2, kk_context())"

