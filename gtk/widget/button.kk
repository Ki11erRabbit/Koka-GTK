/*----------------------------------------------------------------------------
   Copyright 2025, Koka-Community Authors

   Licensed under the MIT License ("The License"). You may not
   use this file except in compliance with the License. A copy of the License
   can be found in the LICENSE file at the root of this distribution.
----------------------------------------------------------------------------*/
module gtk/widget/button

import gobject/gobject
import gtk/widget/core


extern import
  c file "inline/button.h"


pub struct gtk-button
  base : gobject

pub fun gtk-button/from(ptr : int64) : gtk-button
  Gtk-button(gobject/from(ptr))

pub fun gtk-button/into(button : gtk-button) : gtk-widget
  Gtk-widget(button.base)

pub extern gtk-button/gtk-button-new-with-label(label : string) : gtk-button
  c inline "kk_gtk_button_new_with_label(#1, kk_context())"

pub extern gtk-button/connect-clicked(object : gtk-button, callback : (gtk-button) -> ()) : ()
  c inline "kk_gtk_button_connect_clicked(#1, #2, kk_context())"