#pragma once
#include"data.hxx"

namespace undata{//tolua_export
  
  class DIRECTORY: public REPOS{//tolua_export
  public:
    //tolua_begin
    DIRECTORY();
    virtual ~DIRECTORY();
    virtual RESTYPE restype(PATH path);
    virtual RESTYPE restype(string name, string type="def");
    //tolua_end
  protected:
    virtual bool open();
    virtual bool close();
    virtual iostream* openstm(PATH path, ios::openmode mode=ios::in);
    virtual bool closestm(iostream* stm);
  };//tolua_export
  
}//tolua_export

