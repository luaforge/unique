#pragma once
#include"mesh.hxx"

namespace ungeom{
  class SECTOR;
  class PORTAL{
  protected:
    SECTOR* sector[2];
  public:
    PORTAL();
    ~PORTAL();
  };

  class SECTOR{
  protected:
    vector<PORTAL*> portal;
    vector<unsigned int> triangle;
  public:
    SECTOR();
    ~SECTOR();
  
    void draw();
  };

  class SECTORER: public MPROC{
  protected:
  public:
    void compile(MDATA&);
  };
}
