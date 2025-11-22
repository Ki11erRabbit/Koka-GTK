/*----------------------------------------------------------------------------
   Copyright 2024, Koka-Community Authors

   Licensed under the MIT License ("The License"). You may not
   use this file except in compliance with the License. A copy of the License
   can be found in the LICENSE file at the root of this distribution.
----------------------------------------------------------------------------*/
module gobject

import std/cextern

extern import
  c file "inline/gobject.h"

pub struct gobject
   pointer : c-pointer<int64>
