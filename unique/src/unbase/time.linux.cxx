#include"time.hxx"
#ifdef _LINUX
#  include<unistd.h>
#  include<time.h>
#  include<sys/time.h>
#  include<cmath>

#  define ESTIMATE_TIME 0.1 // seconds

namespace unbase{

  double curtime(){
    timeval now;
    gettimeofday(&now,NULL);
    return double(now.tv_sec)+double(now.tv_usec)/double(1000000);
  }

  double estimate_cpu_frequency(){
    double start,stop;
    double before,after;
    timespec d;
    
    d.tv_sec=long(double(ESTIMATE_TIME));
    d.tv_nsec=long((double(ESTIMATE_TIME)-double(long(double(ESTIMATE_TIME))))*pow(double(10),double(9)));
    
    before=curtime();
    start=rdtsc();
    nanosleep(&d,NULL);
    after=curtime();
    stop=rdtsc();

    return double(stop-start)/double(after-before);
  }

}

#endif
