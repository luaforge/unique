/***************************************************************************
 *            alapp.hpp
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
#include"unmath.hxx"

#include<al.h>
#include<alc.h>

namespace unoal{//tolua_export
  ALCdevice *alGetCurrentDevice();
  
# define GET_AL_STR(name) string((char*)alGetString(name))
# define GET_ALC_STR(dev,name) string((char*)alcGetString(dev,name))

  class ALAPP: public unbase::CONTEXT{//tolua_export
  protected:
    ALCdevice  *alDevice;  // AL устройство
    ALCcontext *alContext; // AL контекст рендеринга звука
  public:
    //tolua_begin
    ALAPP();
    virtual ~ALAPP();
    // Methods
    virtual bool open();
    virtual void close();
    virtual void bind();
    virtual void ubind();
    //tolua_end
    // Errors detecting
    static bool CheckError();
    // AL/ALC context info
    virtual void RendererInfo();
    //tolua_begin
    string default_device;
    string device;
    string alc_extensions;
    //tolua_end
  };//tolua_export
}//tolua_export
