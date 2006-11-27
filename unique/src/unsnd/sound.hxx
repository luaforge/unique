/***************************************************************************
 *            sound.hpp
 *
 *  Wed Jun 29 17:12:37 2005
 *  Copyright  2005  FeniX11
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
#include"unobj.hxx"
#include"sndres.hxx"

#ifndef SOUND_STREAM_BUFFERS
#  define SOUND_STREAM_BUFFERS 4     // num buffers in AL queue
#endif
/*

  Небольшие, но необходимые рекомендации об установке значений вышеобъявленных директив:
  
  Первая - размер буффера по умолчанию. Не стоит делать его меньше 512 байт, так как
  ввиду недостаточно частого обновления буфферов могут происходить сбои в проигрывании.
  
  Вторая - число максимальное буфферов проигрывания - тоже влияет на выше описанный
  эффект, это число должно быть больше 2 по понятным причинам.
  
  Оптимальное соотношение этих параметров на современном железе, исходя из эмперических
  данных, может быть выявленно следующим образом:
  
  SOUND_STREAM_BUFFER_SIZE * SOUND_STREAM_BUFFERS = 1048576

  что будет соответствовать одному мегабайту буффера.

*/

/*
                  -------  Updating Buffers  -------

  UnQueue Old Buffer       Processed Buffer          Queue New Buffer
            ___________       _____v_____         ___________
   ________| AL_BUFFER |_____| AL_BUFFER |__...__| AL_BUFFER |______
  |        |_____1_____|  >  |_____2_____|   >   |_____n_____|      |
  ^                                                                 |
  |                                                                 v
  |_________________________________________________________________|
                               If Looped
*/

#include <deque>

namespace unsnd{//tolua_export
  /*                  *
   *  class SOUND;    *
   *                  */
  class SOUND: public unobj::OBJECT{//tolua_export
  protected:
    deque<SNDBUFFER*> seq;
    //SNDRES* data;   // Resource for reading data stream
    ALuint  alid;   // AL Source Id
    // Shadowing parameters
    string osrc;
    bool oplay,oloop;
    float oseek,opitch,ogain,omingain,omaxgain,orolloff,
      ooutgain,orefdist,omaxdist,oinangle,ooutangle;
  public:
    //tolua_begin
    static unsigned int seqcount;
    unsigned short chan; // Stream channels
    unsigned short bits; // Stream bits per channel
    unsigned short rate; // Stream frequency
    string  src;
    // Sound source state
    bool play;  // true - Play,  false - Pause
    bool loop;  // Looped playing
    scalar seek;// Seek (in seconds) if >0 then relate begin of stream else relate end of stream
    // Sound source parameters
    float pitch,rolloff;
    float gain,mingain,maxgain,outgain;
    float refdist,maxdist;
    float inangle,outangle;

    //  typedef bool(SOUND::*FUNC_LOAD)(DRES*   res);
    //  typedef bool(SOUND::*FUNC_READ)(SNDRES::BUFFER& buf);

    SOUND();
    virtual ~SOUND();
    //tolua_end
    /* Binding Drawing */
    void drawmodel(GLenum mode);
    bool update();
  };//tolua_export
}//tolua_export
