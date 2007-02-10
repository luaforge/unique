#pragma once
#include"mesh.hxx"

namespace ungeom{
  
  class BSPNODE{
  public:
    vector<unsigned int> index; // Polygon numbers
    BSPNODE* front;
    BSPNODE* back;
    
    BSPNODE();
    BSPNODE(unsigned int);
    ~BSPNODE();

    //void build(POLYGON* polygon,unsigned int count,unsigned int cur);
    bool exist(unsigned int index); // Exist polygon in tree
  };

  class BSPPROC;
  class BSPTREE{
  protected:
    BSPNODE* root;
  public:
    BSPTREE();
    ~BSPTREE();
    void clean();
    void draw();
    void build(const CHUNK&);
    BSPNODE* procnode(BSPPROC);
  };

  class BSPRENDER{
    
  };
}
