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

pub struct g-application
   base : gobject

extern g-application/new-internal() : intptr_t
   c inline "kk_g_application_new(kk_context())"

pub fun g-application/g-application-new() : g-application
   G-application(Gobject(C-pointer(g-application/new-internal())))

pub extern g-application/run(app : g-application, args : list<string>) : int32
   c inline "kk_gio_application_run(#1, #2, kk_context())"



