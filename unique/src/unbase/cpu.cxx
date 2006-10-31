#include"cpu.hxx"
#include"time.hxx"
using namespace unbase;

//extern double estimate_cpu_frequency();

double CPU::freq=unbase::estimate_cpu_frequency();
string cpu_vendor(){
  char s[16];
  cpuid(0x00000000,(int&)s[12],(int&)s[0],(int&)s[8],(int&)s[4]);
  s[12]=0;
  return s;
}
string CPU::vendor=cpu_vendor();
string cpu_extensions(){
  string e;
  int r[4];
  cpuid(0x00000001,r[0],r[1],r[2],r[3]);
  e+=r[3]&0x00800000?"MMX ":"";
  e+=r[3]&0x02000000?"SSE ":"";
  e+=r[3]&0x04000000?"SSE2 ":"";
  e+=r[2]&0x00000001?"SSE3 ":"";
  cpuid(0x80000001,r[0],r[1],r[2],r[3]);
  e+=r[3]&0x00400000?"AMD-MMX ":"";
  e+=r[3]&0x80000000?"3dnow! ":"";
  e+=r[3]&0x40000000?"3dnow!2 ":"";
  return e;
}
string CPU::extens=cpu_extensions();
string cpu_otherinfo(){
  string e;
  char s[16];
  cpuid(0x00000001,(int&)s[0],(int&)s[4],(int&)s[8],(int&)s[12]);
  e+=string("Stepping number: ")+(void*)(s[0]&0x0F)+string("  ");
  e+=string("Model number:    ")+(unsigned int)(s[0]>>0x4)+string("  ");
  e+=string("Family number:   ")+(unsigned int)(s[1]&0x0F)+string("  ");
  e+=string("Processor Type:  ")+(unsigned int)(s[1]>>0x4)+string("  ");
  e+=string("Extended Model  Number: ")+(unsigned int)(s[2]&0x0F)+string("  ");
  e+=string("Extended Family Number: ")+(unsigned int)(s[2]>>0x4)+string("  ");
  return e;
}
string CPU::info=cpu_otherinfo();

CPU::CPU(){}
CPU::operator string(){
  return string("CPU Frequency: ")+freq+"\nCPU Vendor: "+vendor+"\nCPU Extensions: "+extens+"\n"+info;
}
