#if _LINUX
#  include"directory.hxx"

#  include<sys/types.h>
#  include<sys/stat.h>
#  include<unistd.h>
#  include<fcntl.h>

namespace undata{
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
      state=badbit;
      __fd=0;
    }
    {
      struct stat s;
      if(::stat(path().data(),&s))__length=0;
      else __length=s.st_size;
    }
    state=STATE(goodbit|openbit);
  }
  void FSTREAM::__close(){
    if(!__fd)return;
    ::close(__fd);
    __fd=0;
  }
  /*
   *  DERECTORY
   */
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
#endif
