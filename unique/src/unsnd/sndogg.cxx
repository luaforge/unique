/***************************************************************************
 *            sndogg.cpp
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

#include"sndogg.hxx"

namespace unsnd{
  string OGGRES::type="ogg vorbis stream";
  ALuint OGGRES::sign=0x0067674F;
  
  // vorbisfile specific vars
  
  size_t ReadOgg(void *ptr, size_t size, size_t nmemb, void *datasource){
    undata::STREAM& s=*reinterpret_cast<undata::STREAM*>(datasource);
    //printf("ReadOGG()\n");
    s.read(ptr,size*nmemb);
    return s.gcount();
  }
  int SeekOgg(void *datasource, ogg_int64_t offset, int whence){
    undata::STREAM& s=*reinterpret_cast<undata::STREAM*>(datasource);
    //printf("SeekOGG(): offset:%d", offset);
    switch(whence){
    case SEEK_SET: s.seekg(offset,undata::STREAM::beg); break;
    case SEEK_CUR: s.seekg(offset,undata::STREAM::cur); break;
    case SEEK_END: s.seekg(offset,undata::STREAM::end); break;
    default: return -1;
    }
    return (s.eof()?0:-1);
  }
  long TellOgg(void *datasource){
    undata::STREAM& s=*reinterpret_cast<undata::STREAM*>(datasource);
    //printf("TellOGG()\n");
    return s.tellg();
  }
  int CloseOgg(void *datasource){
    return 0;
  }

  OGGRES::OGGRES():vfile(NULL){}
  OGGRES::~OGGRES(){close();}
  bool OGGRES::open(){
    // OggVorbis specific structures
    cb.close_func=CloseOgg;
    cb.read_func=ReadOgg;
    cb.seek_func=SeekOgg;
    cb.tell_func=TellOgg;
    // Create OggVorbis_File struct
    res->seekg(0,undata::STREAM::beg);
    vfile=new OggVorbis_File;
    switch(ov_open_callbacks(res,vfile,NULL,-1,cb)){
    case OV_EREAD:      state=unbase::STATE(false,"A read from media returned an error"); return false;
    case OV_ENOTVORBIS: state=unbase::STATE(false,"Bitstream is not Vorbis data"); return false;
    case OV_EVERSION:   state=unbase::STATE(false,"Vorbis version mismatch"); return false;
    case OV_EBADHEADER: state=unbase::STATE(false,"Invalid Vorbis bitstream header"); return false;
    case OV_EFAULT:     state=unbase::STATE(false,"Internal logic fault; indicates a bug or heap/stack corruption"); return false;
    }
    comment=ov_comment(vfile,-1); // Return vorbis_comment and vorbis_info structures
    info=ov_info(vfile,-1);       // Fill buffer infos
    ogg_int64_t total=ov_pcm_total(vfile,-1);
    rate=info->rate;
    bits=16;
    chan=info->channels;
    return true;
  }
  void OGGRES::set(int p){
    if(eof())return;
    //cout<<"Begin seek:"<<tell()<<" Seek:"<<p<<endl;
    if(vfile){ov_pcm_seek(vfile,p);}
    //cout<<"End seek:"<<tell()<<endl;
  }
  unsigned int OGGRES::tell(){
    if(vfile){
      ogg_int64_t t=ov_pcm_tell(vfile);
      if(t==OV_EINVAL){
	state=unbase::STATE(false,"The requested bitstream did not exist.");
	return 0;
      }
      return t*2;
    }else return 0;
  }
  bool OGGRES::eof(){
    return (tell()>=size);
  }
  void OGGRES::close(){
    if(vfile){ov_clear(vfile); delete vfile;}
  }
  unsigned int OGGRES::read(void*d,unsigned int s){
    //BlockSize=ov_pcm_total(vfile,-1)*4;
    int current_section;
    // Read loop
    int tot=0,ret=0;
    for(;(tot=ov_read(vfile,(char*)d+ret,s-ret,0,2,1,&current_section))>0 && ret<s;ret+=tot);
    switch(ret){
    case OV_HOLE: state=unbase::STATE(false,"Interruption in the data stream"); return 0;
    case OV_EBADLINK: state=unbase::STATE(false,"Invalid stream section was supplied to libvorbisfile, or the requested link is corrupt"); return 0;
    }
    //cout<<"OGGRES::read(tell()="<<tell()<<";s="<<s<<";ret="<<ret<<") "; if(!state.state)cout<<state; cout<<endl;
    return ret;
  }
}
