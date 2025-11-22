/*----------------------------------------------------------------------------
   Copyright 2025, Koka-Community Authors

   Licensed under the MIT License ("The License"). You may not
   use this file except in compliance with the License. A copy of the License
   can be found in the LICENSE file at the root of this distribution.
----------------------------------------------------------------------------*/
module gobject/gobject

import std/cextern

extern import
  c file "inline/gobject.h"

pub struct gobject
   pointer : c-pointer<int64>

pub fun gobject/from(ptr : intptr_t) : gobject
   Gobject(C-pointer(ptr))

pub extern gobject/unref(object : gobject) : ()
   c inline "kk_object_unref(#1, kk_context())"