/***************************************************************************
 *            time.win32.cpp
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

#include"time.hxx"
#if _WIN32 || _MINGW
#  include<windows.h>
#  include<sys/timeb.h>

#  define ESTIMATE_TIME 0.1 // seconds

namespace unbase{
  
  double curtime(){
    timeb now;
    ftime(&now);
    return double(now.time)+double(now.millitm)/double(1000);
  }
  
  double estimate_cpu_frequency(){
    double start,stop;
    double before,after;
    
    before=curtime();
    start=rdtsc();
    Sleep((unsigned long)(double(1000)*double(ESTIMATE_TIME)));
    after=curtime();
    stop=rdtsc();
    
    return double(stop-start)/double(after-before);
  }
}

#endif
