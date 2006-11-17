/***************************************************************************
 *            alapp.cpp
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

#include"oalapp.hxx"

namespace unoal{
  using namespace unbase;

  ALCdevice *alDevice;  // AL текущее устройство
  ALCdevice *alGetCurrentDevice(){return alDevice;}
  
  ALAPP::ALAPP(){}
  ALAPP::~ALAPP(){close();}

  bool ALAPP::open(){
    alDevice=alcOpenDevice(NULL);// Пусть устройство по умолчанию
    if(!alDevice){
      state=STATE(false,"Error Init AL Device");
      return false;
    }
    alContext=alcCreateContext(alDevice,NULL);// Creating rendering context
    CheckError();
    bind();
    RendererInfo();
    state=STATE(true,"AL Init Normally");
    return true;
  }
  void ALAPP::close(){
    ubind();
    if(alContext)alcDestroyContext(alContext); // Уничтожаем контекст
    if(alDevice) alcCloseDevice(alDevice);     // Закрываем звуковой девайс
  }
  void ALAPP::RendererInfo(){
    /* AL info */
    version=(const char*)alGetString(AL_VERSION);
    renderer=(const char*)alGetString(AL_RENDERER);
    vendor=(const char*)alGetString(AL_VENDOR);
    extensions=(char*)alGetString(AL_EXTENSIONS);
    /* ALC info */
    default_device=(const char*)alcGetString(alDevice,ALC_DEFAULT_DEVICE_SPECIFIER);
    device=(const char*)alcGetString(alDevice,ALC_DEVICE_SPECIFIER);
    alc_extensions=(const char*)alcGetString(alDevice,ALC_EXTENSIONS);
  }
  void ALAPP::bind(){
    unoal::alDevice=alDevice;
    alcMakeContextCurrent(alContext);
    if(!alContext)state=STATE(false,"Error Context Make Current");
  }
  void ALAPP::ubind(){
    unoal::alDevice=NULL;
    alcMakeContextCurrent(NULL);
  }
  
  bool ALAPP::CheckError(){
    ALenum errc;
    if((errc=alcGetError(unoal::alDevice))!=ALC_NO_ERROR){
      //state=STATE(false,(char*)alcGetString(unoal::alDevice,errc));
      cout<<"OpenAL error: "<<(char*)alcGetString(unoal::alDevice,errc)<<endl;
      return false;
    }
    return true;
  }
}
