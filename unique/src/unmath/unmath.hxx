/***************************************************************************
 *            unmath.hpp
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
#include"decl.hxx"
#include"simd.hxx"
#include"vec2.hxx"
#include"vec3.hxx"
#include"vec4.hxx"
#include"mat3.hxx"
#include"mat4.hxx"
#include"quat.hxx"
#include"util.hxx" 
#include"geom.hxx"


#ifdef IOSTREAM_ENABLE
#  include<iostream>
extern std::ostream& operator<<(std::ostream& stm, vec2& v);
extern std::ostream& operator<<(std::ostream& stm, vec3& v);
extern std::ostream& operator<<(std::ostream& stm, vec4& v);
extern std::ostream& operator<<(std::ostream& stm, quat& q);
extern std::ostream& operator<<(std::ostream& stm, mat3& m);
extern std::ostream& operator<<(std::ostream& stm, mat4& m);
#  endif
