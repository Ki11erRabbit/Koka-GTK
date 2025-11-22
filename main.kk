module main

import gobject/gobject
import gobject/gio
import gtk/gtk
import gtk/window

fun callback(app: gtk-application) : () 
  val window = match app.get-active-window
    Just(window) -> window
    Nothing -> app.create-window
  
  window.present


pub fun main()
   val app = gtk-application-new()
   app.connect-activate(callback)
   gtk-application/run(app, [])
   ()