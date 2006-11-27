/***************************************************************************
 *            sndres.cpp
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

#include"sndres.hxx"

namespace unsnd{
  unsigned int SNDBUFFER::meansize=SOUND_STREAM_BUFFER_SIZE;
  SNDBUFFER::CONT SNDBUFFER::pool=SNDBUFFER::CONT();

  SNDBUFFER::SNDBUFFER():rate(0),bits(0),chan(0),size(0),used(0),filled(false){
    alGenBuffers(1,&id);
    OAL_DEBUG();
    //cout<<"crt buffer"<<endl;
    if(!alIsBuffer(id))cout<<"Error create al buffer"<<endl;
  }
  SNDBUFFER::SNDBUFFER(SNDRES*res):rate(0),bits(0),chan(0),size(0),used(0),filled(false){
    alGenBuffers(1,&id);
    OAL_DEBUG();
    //cout<<"crt buffer"<<endl;
    if(!alIsBuffer(id))cout<<"Error create al buffer"<<endl;
    fill(res);
  }
  SNDBUFFER::~SNDBUFFER(){
    alDeleteBuffers(1,&id);
    OAL_DEBUG();
  }
  ALenum SNDBUFFER::CalcFormat(){
    if(chan==1){
      if(bits==8)return AL_FORMAT_MONO8;
      else if(bits==16)return AL_FORMAT_MONO16;
    }else if(chan==2){
      if(bits==8)return AL_FORMAT_STEREO8;
      else if(bits==16)return AL_FORMAT_STEREO16;
    }
    return 0; // is unknown format
  }
  bool SNDBUFFER::fill(ALsizei c,ALsizei b,ALsizei f,ALvoid* d,ALsizei l,ALuint s){
    chan=c; bits=b; size=l; rate=f; from=s;
    if(chan && bits && size && rate){
      alBufferData(id,CalcFormat(),d,size,rate);
      scalar speed=scalar(chan*bits/8)/rate;
      length=size/speed;
      start =from/speed;
      filled=true;
      OAL_DEBUG();
      return true;
    }
    return false;
  }
  bool SNDBUFFER::fill(SNDRES*res){
    if(res){
      char* d=new char[meansize]();
      unsigned int t=res->tell();
      unsigned int s=res->read(d,meansize);
      if(s)fill(res->chan,res->bits,res->rate,d,s,t);
      delete[]d;
    }
  }
  void SNDBUFFER::queuesource(ALuint alid){
    if(alIsSource(alid) && alIsBuffer(id))alSourceQueueBuffers(alid,1,&id);
    OAL_DEBUG();
    //else cout<<"alIsSource(sid)=AL_FALSE"<<endl;
  }
  void SNDBUFFER::unquesource(ALuint alid){
    if(alIsSource(alid) && alIsBuffer(id))alSourceUnqueueBuffers(alid,1,&id);
    OAL_DEBUG();
    //else cout<<"alIsSource(sid)=AL_FALSE"<<endl;
  }
  SNDBUFFER* SNDBUFFER::get(string name,unsigned int from){
    ITER c=pool.find(name);
    if(c==pool.end()){ // If not exist
      SNDRES*res=SNDRES::get(name);
      if(res){
	//cout<<res->state<<endl;
	pool[name]=new SNDSTREAM();
	c=pool.find(name);
	c->second->res=res;
      }else return NULL;
    }
    return c->second->get(from);
  }
  void SNDBUFFER::put(string name,SNDBUFFER*b){
    ITER c=pool.find(name);
    c->second->put(b);
  }

  SNDSTREAM::SNDSTREAM(){}
  SNDSTREAM::SNDSTREAM(SNDRES*r):res(r){}
  SNDSTREAM::~SNDSTREAM(){
    SNDRES::put(res);
  }
  SNDBUFFER* SNDSTREAM::get(unsigned int from){
    if(buf.size())for(ITER i=buf.begin();i<buf.end();i++){ // Find buffer in existents
	if((*i)->from==from){
	  (*i)->used++;
	  return *i;
	}
      }
    //cout<<"SNDSTREAM::get"<<from<<endl;
    if(res){
      if(res->tell()!=from){
	res->close();
	res->open();
	res->set(from);
      }
      SNDBUFFER*b=new SNDBUFFER(res);
      if(b->filled){
	buf.push_back(b);
      }else{
	delete b;
	return NULL;
      }
      //cout<<res->state<<endl;
      return get(from);
    }
    return NULL;
  }
  void SNDSTREAM::put(SNDBUFFER*b){
    if(!b)return;
    if(buf.size())for(ITER i=buf.begin();i<buf.end();i++){ // Find buffer in existents
	if((*i)==b){
	  (*i)->used--;
	  if((*i)->used==0){
	    delete (*i);
	    buf.erase(i);
	  }
	  return;
	}
      }
  }

  ALuint SNDRES::sign=0x00000000;
  string SNDRES::type="none";

  bool SNDRES::check(undata::STREAM& s, ALuint sig){ //  Проверка принадлежности формату
    ALuint sg;
    s.seekg(0,undata::STREAM::beg); s.read(&sg,4); s.seekg(0,undata::STREAM::beg);
    //printf("SNDRES::Check(): %x ~ %x\n", sg, sig);
    return(memcmp(&sg,&sig,3)==0);
  }

#define SNDRES_ASSIGN(s,format)	{					\
    if(format::check(s,format::sign)){					\
      SNDRES* reader=new format();					\
      reader->open(s);							\
      return reader;							\
    }									\
  }

  SNDRES* SNDRES::get(string name){
    undata::RESOURCE r=undata::resource(name,"sounddata");
    if(r.type==undata::RESOURCE::stm&&r.access&undata::STREAM::inp){
      undata::STREAM& s=r.stream();
      SNDRES_ASSIGN(s,OGGRES);
      //SNDRES_ASSIGN(r,WAVRES);
      r.stream(s);
    }
  }
  void SNDRES::put(SNDRES* r){
    r->close();
    delete r;
  }
  
  unsigned int SNDRES::read(void*d,unsigned int s){
  
  }
}
