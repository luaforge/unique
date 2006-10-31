/***************************************************************************
 *            simd.hpp
 *
 *  Wed Jun 29 17:12:37 2005
 *  Copyright  2005  Fenix
 *  tonder@trktvs.ru
 ****************************************************************************/

/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Library General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */
#pragma once
#include"decl.hxx"
using namespace unmath;

#ifndef UNMATH_PFUNC
#  define UNMATH_PFUNC(rets,name,args) extern rets (*name)args
#  include"simd.func.hxx"
#  undef UNMATH_PFUNC
#endif

class SIMD{ // SIMD Optimizer
 protected:
  static int mode;
 public:
  enum{ // SIMD extension mode
    _FPU=0,   // Default
    _GPU,     // New! test only
    _SSE,     // SSE
    _SSE3,    // SSE3
    _3DNOW,   // 3DNOW
    _3DNOWEXT,// 3DNOW EXT
  }OPT;
  // Methods
  SIMD(){ Switch(mode); }
  ~SIMD(){}
  // Switcher modes
  static bool Check(int swt);  // Check support SIMD extension
  static bool Switch(int swt); // Switcher SIMD optimization mode
  static int  Current(){ return mode; } // Return current SIMD mode
};
