#pragma once
#include"data.hxx"

namespace undata{//tolua_export
  
  class DIRECTORY: public REPOS{//tolua_export
  public:
    //tolua_begin
    DIRECTORY();
    virtual ~DIRECTORY();
    //tolua_end
  protected:
    virtual bool open();
    virtual bool close();
    virtual iostream* openstm(PATH path, ios::openmode mode=ios::in);
    virtual bool closestm(iostream* stm);
  };//tolua_export
  
}//tolua_export
