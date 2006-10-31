/***************************************************************************
 *            mathdecl.hpp
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

#include"unbase.hxx"
#include<cassert>
#include<cmath>
#include<limits>
#include<memory>

//tolua_begin
namespace unmath{
  typedef float scalar;
  class cnst{
  public:
    static tolua_readonly scalar one_pi;
    static tolua_readonly scalar half_pi;
    static tolua_readonly scalar quarter_pi;
    static tolua_readonly scalar two_pi;
    static tolua_readonly scalar oo_pi;
    static tolua_readonly scalar oo_two_pi;
    static tolua_readonly scalar sqrt_pi;
    static tolua_readonly scalar to_rad;
    static tolua_readonly scalar to_deg;

    static tolua_readonly scalar oo_255;
    static tolua_readonly scalar oo_256;
    static tolua_readonly scalar oo_127;
    static tolua_readonly scalar oo_128;

    static tolua_readonly scalar one_e;
    static tolua_readonly scalar half_e;
    static tolua_readonly scalar quarter_e;
    static tolua_readonly scalar two_e;

    static tolua_readonly scalar one_eps;
    static tolua_readonly scalar two_eps;
    static tolua_readonly scalar big_eps;
    static tolua_readonly scalar small_eps;
    //   _____
    // \/ 0.5
    static tolua_readonly scalar one_sqrt_half;
    static tolua_readonly scalar two_sqrt_half;
    static tolua_readonly scalar tri_spr_good;
  };
  //tolua_end

  class vec2;
  class vec3;
  class vec4;
  class quat;
  class mat3;
  class mat4;

  inline scalar oo_scalar(scalar n){ if(n>cnst::one_eps)return 1.0/n; else return 0.0; } // Обратное значение
#define saturation_macros(v,c){ v.c=(c<0.0f)?0.0:c; v.c=(c>1.0f)?1.0:c; }

}//tolua_export
