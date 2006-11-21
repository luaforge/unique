#include"directory.hxx"

#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>

namespace undata{
  FSTREAM::FSTREAM(REPOS* r):STREAM(r),__fd(0),__rpos(0),__wpos(0){}
  FSTREAM::FSTREAM():STREAM(),__fd(0),__rpos(0),__wpos(0){}
  FSTREAM::~FSTREAM(){close();}
  
  void FSTREAM::__read (void* chunk, pos_type count){
    ::lseek(__fd,__rpos,SEEK_SET);
    __rcount=::read(__fd,chunk,count);
    __rpos+=__rcount;
  }
  void FSTREAM::__write(const void* chunk, pos_type count){
    ::lseek(__fd,__wpos,SEEK_SET);
    __wcount=::write(__fd,chunk,count);
    __wpos+=__wcount;
  }
  STREAM::pos_type FSTREAM::__tellr()const{
    return __rpos;
  }
  STREAM::pos_type FSTREAM::__tellw()const{
    return __wpos;
  }
  void FSTREAM::__seekr(pos_type count,DIR dir){
    if(dir==cur)__rpos+=count;
    if(dir==beg)__rpos=count;
    if(dir==end)__rpos=__length-count;
  }
  void FSTREAM::__seekw(pos_type count,DIR dir){
    if(dir==cur)__wpos+=count;
    if(dir==beg)__wpos=count;
    if(dir==end)__wpos=__length-count;
  }
  /*
   *  DERECTORY
   */
  DIRECTORY::DIRECTORY():REPOS(){}
  DIRECTORY::~DIRECTORY(){}
  STREAM* DIRECTORY::stream(PATH p, STREAM::MODE m){
    PATH l(location);
    PATH f=l|p;
    FSTREAM* s=new FSTREAM();
    s->open(f,m);
    return s;
  }
  void DIRECTORY::stream(STREAM* s){
    s->close();
    delete s;
  }
}
