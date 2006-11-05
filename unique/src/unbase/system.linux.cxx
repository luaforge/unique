#if _LINUX
#include"system.hxx"
#include<sys/time.h> 
#include<sys/resource.h> 

using namespace unbase;

void RESUSAGE::operator()(){
  rusage usg;
  if(getrusage(RUSAGE_SELF,&usg)){
    
  }

  user=double(usg.ru_utime.tv_sec)+double(usg.ru_utime.tv_usec)/double(1000000);
  sys =double(usg.ru_stime.tv_sec)+double(usg.ru_stime.tv_usec)/double(1000000);

  inblock=usg.ru_inblock;
  oublock=usg.ru_oublock;
  
  mxrss=usg.ru_maxrss;
  ixrss=usg.ru_ixrss;
  idrss=usg.ru_idrss;
  isrss=usg.ru_isrss;
}

#endif
