#include"cpu.hxx"
#if _WIN32 && !_MINGW

void unbase::cpuid(int func,int&a,int&b,int&c,int&d){
  asm {
    mov eax, func
    cpuid
    mov a, eax
    mov b, ebx
    mov c, ecx
    mov d, edx
  }
}

/*
#include <windows.h>
double rdtsc(){
  LARGE_INTEGER t;
  QueryPerformanceCounter(&t);
  return double(t.QuadPart);
}
*/
double unbase::rdtsc(){
  unsigned int a,b;
  asm {
    rdtsc
    mov a, eax
    mov b, edx
  }
  return (double)b*(double)0x10000*(double)0x10000+a;
}

#endif
