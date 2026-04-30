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
   pointer : intptr_t

pub extern gobject/from(ptr : i64) : gobject
   c inline "kk_gobject_from(#1, kk_context())"