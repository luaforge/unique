/***************************************************************************
 *            sndres.hpp
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
#include"unbase.hxx"
#include"unoal.hxx"
#include"undata.hxx"

#ifndef SOUND_STREAM_BUFFER_SIZE
# define SOUND_STREAM_BUFFER_SIZE 1*512*1024;
#endif

namespace unsnd{
  /* 
   *  Interface sound resource
   */
  class SNDRES{
  public:
    unbase::STATE state;
    static string type;
    string src;
    ALsizei chan;  // Num of channels
    ALsizei bits;  // Num of bits per channel
    ALsizei rate;  // Frequency
  protected:
    unsigned int size;
    undata::STREAM* res;
  public:
    static ALuint sign;
    static bool check(undata::STREAM& res, ALuint sign); // Проверка принадлежности формату
    static SNDRES* get(string name);
    static void put(SNDRES* r);
    
    SNDRES(){}
    virtual ~SNDRES(){close();}
    
    virtual bool open(){}
    virtual bool open(undata::STREAM& r){res=&r;open();}
    virtual void close(){}
    virtual unsigned int tell(){}
    virtual bool eof(){}
    virtual void set(int){}
    virtual unsigned int read(void*d,unsigned int s);
  };

  class SNDSTREAM;
  class SNDBUFFER{
  public:
    //        source name  |  buffer
    typedef map<string,SNDSTREAM*> CONT;
    typedef map<string,SNDSTREAM*>::iterator ITER;
    static unsigned int meansize;  // Buffer size in bytes
    static CONT pool;
    static SNDBUFFER* get(string name,unsigned int from);
    static void put(string name,SNDBUFFER*b);
  protected:
    ALenum CalcFormat();
  public:
    bool filled;
    bool ended;
    unsigned int used; // Used this buffer
    ALuint  id;    // AL buffer identifier
    scalar  start; // Start  in seconds
    scalar  length;// Length in seconds
    ALsizei size;  // Buffer size in bytes
    ALuint  from;  // Buffer offset in bytes
    ALsizei chan;  // Num of channels
    ALsizei bits;  // Num of bits per channel
    ALsizei rate;  // Frequency

    SNDBUFFER();
    SNDBUFFER(SNDRES*res);
    ~SNDBUFFER();

    bool fill(SNDRES*res);
    bool fill(ALsizei c,ALsizei b,ALsizei f,ALvoid* d,ALsizei l,ALuint s);
    void queuesource(ALuint sid);
    void unquesource(ALuint sid);
    // channels | bits per channel | frequency | data | length in bytes | start in bytes
  };

  class SNDSTREAM{
  public:
    typedef vector<SNDBUFFER*>::iterator ITER;
  public:
    SNDRES* res;
    vector<SNDBUFFER*> buf;
  
    SNDSTREAM();
    SNDSTREAM(SNDRES*r);
    ~SNDSTREAM();
  
    SNDBUFFER* get(unsigned int from);
    void put(SNDBUFFER*);
  };

  //   Buffering         stream1
  // > ---------------||-----------------------------------||
  // > resource_name1 || buffer1 | buffer2 | ... | bufferN ||
  // > ---------------||-----------------------------------||
  //                     stream2
  // > ---------------||-----------------------------------||
  // > resource_name2 || buffer1 | buffer2 | ... | bufferN ||
  // > ---------------||-----------------------------------||
  //
  //         .......................................
  //                     streamN
  // > ---------------||--------------------
  // > resource_nameN || buffer1 | buffer2
  // > ----------
  //

  //# include"sndwav.hxx"
  //# include"sndmp3.hxx"
}

# include"sndogg.hxx"
