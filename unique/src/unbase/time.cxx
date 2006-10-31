#include"time.hxx"
using namespace unbase;

TIME::TIME(const TIME& t):time(t.time){}
TIME::TIME(const double t):time(t){}
TIME::TIME(){(*this)();}
TIME::operator string(){return string("TIME(")+time+string(" sec)");}
bool TIME::operator==(TIME& t){return bool(time-t.time<0.000000001);}
bool TIME::operator!=(TIME& t){return bool(*this!=t);}
TIME TIME::operator+(TIME& t) {return TIME(time+t.time);}
TIME TIME::operator-(TIME& t) {return TIME(time-t.time);}
void TIME::operator=(double t){
  double old=time;
  time=t;
  lambda=delta;
  delta=time-old;
  lambda=delta-lambda;
}
void TIME::operator()(double t){
  (*this)=t;
}
void TIME::operator()(){
  (*this)=utime();
}
double unbase::utime(){return (rdtsc()/CPU::freq);}
