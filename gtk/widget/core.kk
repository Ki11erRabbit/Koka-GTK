/*----------------------------------------------------------------------------
   Copyright 2025, Koka-Community Authors

   Licensed under the MIT License ("The License"). You may not
   use this file except in compliance with the License. A copy of the License
   can be found in the LICENSE file at the root of this distribution.
----------------------------------------------------------------------------*/
module gtk/widget/core

import gobject/gobject

pub struct gtk-widget
  base : gobject


pub fun gtk-widget/from(ptr : intptr_t) : gtk-widget
  Gtk-widget(gobject/from(ptr))