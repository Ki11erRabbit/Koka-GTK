module main

import gobject
import gio

fun callback(object: g-application) : () 
   trace("hello, world")

pub fun main()
   val app = g-application-new()
   app.connect-activate(callback)
   g-application/run(app, [])
   ()