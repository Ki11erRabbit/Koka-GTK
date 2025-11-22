/*----------------------------------------------------------------------------
   Copyright 2024, Koka-Community Authors

   Licensed under the MIT License ("The License"). You may not
   use this file except in compliance with the License. A copy of the License
   can be found in the LICENSE file at the root of this distribution.
----------------------------------------------------------------------------*/
module gtk/gtk

import gobject/gobject
import gobject/gio
import gtk/window

extern import
  c file "inline/gtk.h"


pub struct gtk-application
  base : gobject

extern gtk-application/new-internal() : intptr_t
  c inline "kk_gtk_app_new(kk_context())"

pub fun gtk-application/gtk-application-new() : gtk-application
  Gtk-application(gobject/from(gtk-application/new-internal()))

pub extern gtk-application/run(app : gtk-application, args : list<string>) : int32
  c inline "kk_gtk_application_run(#1, #2, kk_context())"

pub extern g-application/connect-activate(object : gtk-application, callback : (gtk-application) -> ()) : ()
  c inline "kk_gtk_app_connect_activate(#1, #2, kk_context())"

extern gtk-application/get-active-window-internal(app : gtk-application) : maybe<intptr_t>
  c inline "kk_gtk_get_active_window(#1, kk_context())"

pub fun gtk-application/get-active-window(app : gtk-application) : maybe<gtk-window>
  match gtk-application/get-active-window-internal(app)
    Just(window) -> Just(gtk-window/from(window))
    Nothing -> Nothing

extern gtk-application/create-window-internal(app : gtk-application) : intptr_t
  c inline "kk_gtk_create_window(#1, kk_context())"

pub fun gtk-application/create-window(app : gtk-application) : gtk-window
  gtk-window/from(gtk-application/create-window-internal(app))