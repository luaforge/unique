#include"directory.hxx"

#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fstream>

namespace undata{ 
  /*
   *  DERECTORY
   */
  DIRECTORY::DIRECTORY():REPOS(){
    
  }
  DIRECTORY::~DIRECTORY(){
    
  }
  bool DIRECTORY::open(){
    
  }
  bool DIRECTORY::close(){
    
  }
  iostream* DIRECTORY::openstm(PATH p, ios::openmode m){
    PATH l(location);
    PATH f=l|p;
    return new fstream(f().data(),m);
  }
  bool DIRECTORY::closestm(iostream* s){
    delete s;
  }
  REPOS::RESTYPE DIRECTORY::restype(PATH p){
    PATH l(location);
    PATH f=l|p;
    struct stat s;
    if(stat(f().data(),&s))return non;
    if(S_ISREG(s.st_mode))return stm;
    if(S_ISDIR(s.st_mode))return dir;
    return non;
  }
  REPOS::RESTYPE DIRECTORY::restype(string n, string t){
    return REPOS::restype(n,t);
  }
}
