/***************************************************************************
 *            time.hpp
 *
 *  Thu Jun 30 20:29:45 2005
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
#include<iostream>
#include<string>
#include"platform.hxx"
#include"cpu.hxx"
#include"option.hxx"

//tolua_begin
namespace unbase{
  class TIME{ // Time object
  public:
    double time;  // Time
    double delta; // Delta time (time-old_time)
    double lambda;// Lambda (delta-old_delta)
  public:
    TIME(const TIME&);
    TIME(const double);
    TIME();
    /* Operations */
    bool operator==(TIME&);
    //tolua_end
    void operator=(double);
    bool operator!=(TIME&);
    //tolua_begin
    TIME operator+(TIME&);
    TIME operator-(TIME&);
    /* Methods */
    void operator()();
    void operator()(double);
    operator string();
    static string __info(string);
  };
  //tolua_end

  double estimate_cpu_frequency();
  double curtime();
  double utime();

}//tolua_export
