module main

import gobject/gobject
import gobject/gio
import gtk/gtk
import gtk/window
import gtk/widget/box
import gtk/widget/button

fun callback(app: gtk-application) : () 
  val window : gtk-window = match app.get-active-window
    Just(window) -> window
    Nothing -> app.create-window
  
  window.set-title("Hello")
  val button = gtk-button-new-with-label("Hello World")
  button.connect-clicked fn (b)
    trace("hello world!")
  
  val box = gtk-box-new(OrientationVertical, 0)
  box.append(button.into)

  window.set-child(box.into)

  window.present


pub fun main()
   val app = gtk-application-new()
   app.connect-activate(callback)
   gtk-application/run(app, [])
   ()