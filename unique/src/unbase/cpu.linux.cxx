#include"cpu.hxx"
#ifdef _LINUX

void unbase::cpuid(int func,int&eax,int&ebx,int&ecx,int&edx){
  __asm__ __volatile__("cpuid":"=a"(eax),"=b"(ebx),"=c"(ecx),"=d"(edx):"a"(func));
}

double unbase::rdtsc(){
  unsigned int a,b;
  __asm__("rdtsc":"=a"(a),"=d"(b));
  return (double)b*(double)0x10000*(double)0x10000+a;
}

#endif
