
#include"system.hxx"

using namespace unbase;

RESUSAGE::RESUSAGE(){
  
}

RESUSAGE::~RESUSAGE(){
  
}

RESUSAGE::operator string(){
  return string("system time: ")+static_cast<string>(sys)+" user time: "+static_cast<string>(user);
}
