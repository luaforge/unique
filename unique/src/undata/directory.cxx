#include"directory.hxx"

#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>

namespace undata{
  FSTREAM::FSTREAM(REPOS* r):STREAM(r),__fd(0),__rpos(0),__wpos(0){}
  FSTREAM::FSTREAM():STREAM(),__fd(0),__rpos(0),__wpos(0){}
  FSTREAM::~FSTREAM(){close();}
  
  void FSTREAM::__open(){
    if(__fd)return;
    string n=path();
    int flags=0;
    flags|=mode==inp?O_RDONLY:0;
    flags|=mode==out?O_WRONLY|O_CREAT:0;
    flags|=mode==io?O_RDWR|O_CREAT:0;
    flags|=O_LARGEFILE;
    mode_t modes=S_IREAD|S_IWRITE|S_IRGRP|S_IROTH;
    __fd=::open(n.data(),flags,modes);
    if(__fd<0){
      state=bad;
      __fd=0;
    }
    {
      struct stat s;
      if(::stat(path().data(),&s))__length=0;
      else __length=s.st_size;
    }
  }
  void FSTREAM::__close(){
    if(!__fd)return;
    ::close(__fd);
    __fd=0;
  }

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
  RESOURCE::TYPE DIRECTORY::restype(PATH p){
    PATH l(location);
    PATH f=l|p;
    struct stat s;
    if(::stat(f().data(),&s))return RESOURCE::non;
    if(S_ISREG(s.st_mode))   return RESOURCE::stm;
    if(S_ISDIR(s.st_mode))   return RESOURCE::dir;
    return RESOURCE::non;
  }
  STREAM::MODE DIRECTORY::resmode(PATH p){
    PATH l(location);
    PATH f=l|p;
    struct stat s;
    if(::stat(f().data(),&s))return STREAM::no;
    int m=STREAM::no;
    m|=s.st_mode&S_IRUSR?STREAM::inp:STREAM::no;
    m|=s.st_mode&S_IWUSR?STREAM::out:STREAM::no;
    return STREAM::MODE(m);
  }
}
