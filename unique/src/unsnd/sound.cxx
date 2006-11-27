/***************************************************************************
 *            sound.cpp
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

#include"sound.hxx"

namespace unsnd{
  /*                  *
   *  class SOUND;    *
   *                  */

  unsigned int SOUND::seqcount=SOUND_STREAM_BUFFERS;

# define SNDSRCPAR_INIT(p,op,alp) {alGetSourcef(alid,alp,&p);op=p;}

  SOUND::SOUND():OBJECT(),src(""),osrc(""),play(false),oplay(false),alid(0),
		 loop(false),oloop(false),seek(0.0f),oseek(0.0f),
		 rate(0),chan(0),bits(0){
    alGenSources(1,&alid); // Создаем источник
    OAL_DEBUG();
    // Init parameters
    alSourcei(alid,AL_LOOPING,loop?1:0);
    // Pitch
    SNDSRCPAR_INIT(   pitch,   opitch,AL_PITCH);
    // Gain
    SNDSRCPAR_INIT(    gain,    ogain,AL_GAIN);
    SNDSRCPAR_INIT( mingain, omingain,AL_MIN_GAIN);
    SNDSRCPAR_INIT( maxgain, omaxgain,AL_MAX_GAIN);
    SNDSRCPAR_INIT( outgain, ooutgain,AL_CONE_OUTER_GAIN);
    // Distance
    SNDSRCPAR_INIT( refdist, orefdist,AL_REFERENCE_DISTANCE);
    SNDSRCPAR_INIT( maxdist, omaxdist,AL_MAX_DISTANCE);
    // Angle
    SNDSRCPAR_INIT( inangle, oinangle,AL_CONE_INNER_ANGLE);
    SNDSRCPAR_INIT(outangle,ooutangle,AL_CONE_OUTER_ANGLE);
    // RollOff factor
    SNDSRCPAR_INIT( rolloff, orolloff,AL_ROLLOFF_FACTOR);
    OAL_DEBUG();
    alSourceRewind(alid);
  }

  SOUND::~SOUND(){
    alSourceStop(alid);
    alDeleteSources(1,&alid); // Delete source
    OAL_DEBUG();
  }

  void SOUND::drawmodel(GLenum mode){

  }

  /*

    Добавление буффера в очередь. Логика работы такова:
    Если буффер можно добавить в очередь, добавляет, возвращая
    истину, если число буфферов в очереди достаточное,
    не добавляет, возвращая ложь.

  */

  /*

    Удаление буфферов из очереди. Логика работы слеующая:
    Если буфферов не ноль, происходит удаление, возвращается
    истина, если буфферов ноль, возвращается ложь.

  */

#define SNDSRCPAR_UPDATE(p,op,alp) {if(p!=op){alSourcef(alid,alp,p);}}

  bool SOUND::update(){ // Updating buffers if _streamed;
    // Location
    mat4 mtx=locatematrix(),lmt=matrix();
    mat4 tmt=(mtx-lmt)*unmath::vec3::pz;
    vec3 gpos=mtx*unmath::vec3::null;  // Global position
    vec3 dir=tmt*unmath::vec3::pz;// Direction vector
    alSourcefv(alid,AL_POSITION,gpos);
    alSourcefv(alid,AL_VELOCITY, vel);
    alSourcefv(alid,AL_DIRECTION,dir);
    // Parameters
    // Pitch
    SNDSRCPAR_UPDATE(   pitch,   opitch,AL_PITCH);
    // Gain
    SNDSRCPAR_UPDATE(    gain,    ogain,AL_GAIN);
    SNDSRCPAR_UPDATE( mingain, omingain,AL_MIN_GAIN);
    SNDSRCPAR_UPDATE( maxgain, omaxgain,AL_MAX_GAIN);
    SNDSRCPAR_UPDATE( outgain, ooutgain,AL_CONE_OUTER_GAIN);
    // Distance
    SNDSRCPAR_UPDATE( refdist, orefdist,AL_REFERENCE_DISTANCE);
    SNDSRCPAR_UPDATE( maxdist, omaxdist,AL_MAX_DISTANCE);
    // Angle
    SNDSRCPAR_UPDATE( inangle, oinangle,AL_CONE_INNER_ANGLE);
    SNDSRCPAR_UPDATE(outangle,ooutangle,AL_CONE_OUTER_ANGLE);
    // RollOff factor
    SNDSRCPAR_UPDATE( rolloff, orolloff,AL_ROLLOFF_FACTOR);
    // Source sound resource
    OAL_DEBUG();
    if(osrc!=src){
      osrc=src;
      //if(data)SNDRES::put(data);
      //data=SNDRES::get(src);
      //if(data){ // Resource opened really
      //  state=STATE(true,"Resource opened normally");
      //}
    }
    // Streaming play update
    if(play){
      SNDBUFFER* b;
      bool filled=true;
      ALint processed;
      alGetSourceiv(alid,AL_BUFFERS_PROCESSED,&processed);
      OAL_DEBUG();
      unsigned int offset=0;
      bool k=false; //if(seq.size()<seqcount+processed){k=true;cout<<"queue[";}
      // Queue
      for(;seq.size()<seqcount+processed;){
	b=SNDBUFFER::get(src,offset);
	if(b){
	  seq.push_back(b);
	  b->queuesource(alid);
	  OAL_DEBUG();
	  chan=b->chan;
	  bits=b->bits;
	  rate=b->rate;
	  //cout<<"#";
	  offset=b->from+b->size;
	}else{
	  if(loop){
	    offset=0;
	  }else break;
	}
      }
      //if(k)cout<<"]"<<endl;
      OAL_DEBUG();
      if(seq.size()==0){
	alSourceStop(alid);
	OAL_DEBUG();
	play=false;
      }
      k=false; //if(processed>0){k=true;cout<<"unque[";}
      // UnQueue
      for(;processed>0;processed--){
	b=seq.front();
	b->unquesource(alid);
	OAL_DEBUG();
	SNDBUFFER::put(src,b);
	seq.pop_front();
	//cout<<"x";
      }
      //if(k)cout<<"]"<<endl;
      OAL_DEBUG();
    }
    // State
    if(play!=oplay){
      if(oplay==false){
	alSourceRewind(alid);
      }
      oplay=play;
      if(play)alSourcePlay(alid);
      else   alSourcePause(alid);
    }
    if(loop!=oloop){oloop=loop; /*alSourcei(alid,AL_LOOPING,loop?1:0);*/}
    if(seek!=oseek){oseek=seek;}
    return true;
  }
}
