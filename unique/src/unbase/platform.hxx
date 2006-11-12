/***************************************************************************
 *            platform.hpp
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

#ifndef NULL
#  define NULL 0x00000000
#endif

#include"config.hxx"
//#include "memory.hxx"

#define tolua_readonly const

#ifdef _WIN32
#  define UNAPI __declspec(dllexport)
#  define UNAPICLASS __declspec(dllexport)
#else
#  define UNAPI extern "C"
#  define UNAPICLASS 
#endif

#include <string>
/*
#  ifdef _WIN32
inline std::string operator+(const std::string& so, const std::string& st){
  std::string sr=so;
  sr+=st;
  return sr;
}
#  endif
*/
inline std::string operator+(const std::string& s, const float f){
  char t[32];
  sprintf(t,"%f",f);
  return s+t;
}
inline std::string operator+(const std::string& s, const double f){
  char t[32];
  sprintf(t,"%f",f);
  return s+t;
}
inline std::string operator+(const std::string& s, const int i){
  char t[32];
  sprintf(t,"%d",i);
  return s+t;
}
inline std::string operator+(const std::string& s, const unsigned int i){
  char t[32];
  sprintf(t,"%u",i);
  return s+t;
}
inline std::string operator+(const std::string& s, const long i){
  char t[64];
  sprintf(t,"%d",i);
  return s+t;
}
inline std::string operator+(const std::string& s, const unsigned long i){
  char t[64];
  sprintf(t,"%u",i);
  return s+t;
}
inline std::string operator+(const std::string& s, const void*p){
  char t[32];
  sprintf(t,"%x",p);
  return s+t;
}
inline std::string& operator+=(std::string& s, const float f){s=s+f;return s;}
inline std::string& operator+=(std::string& s, const int i){s=s+i;return s;}
inline std::string& operator+=(std::string& s, const unsigned int i){s=s+i;return s;}
inline std::string& operator+=(std::string& s, const long i){s=s+i;return s;}
inline std::string& operator+=(std::string& s, const unsigned long i){s=s+i;return s;}
inline std::string& operator+=(std::string& s, const void*p){s=s+p;return s;}
using namespace std;

