/***************************************************************************
 *            sndogg.hpp
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
#include"sndres.hxx"

#include<vorbis/codec.h>
#include<vorbis/vorbisfile.h>

namespace unsnd{
  class OGGRES: public SNDRES{
  protected:
    ov_callbacks    cb;
    OggVorbis_File* vfile;
    vorbis_comment* comment;
    vorbis_info*    info;
  public:
    static string type;
    static ALuint sign;
  
    OGGRES();
    virtual ~OGGRES();
  
    bool open();
    void close();
    unsigned int tell();
    void set(int);
    bool eof();
    unsigned int read(void*d,unsigned int s);
  };
}
