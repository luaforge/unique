#pragma once
#include"platform.hxx"

//tolua_begin
namespace unbase{
  class CPU{
  public:
    static double freq;
    static string vendor;
    static string extens;
    static string info;
    operator string();
    CPU();
  };
  double rdtsc();
  //tolua_end
  void cpuid(int func,int&eax,int&ebx,int&ecx,int&edx);
};//tolua_export
