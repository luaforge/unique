#include"bsp.hxx"

namespace ungeom{
  BSPNODE::BSPNODE():front(NULL),back(NULL){}
  BSPNODE::~BSPNODE(){
    if(front)delete front;
    if(back )delete back;
  }
  /*
    bool BSPNODE::exist(unsigned int i){
    if(i==index)return true;
    if(front)if(front->exist(i))return true;
    if( back)if( back->exist(i))return true;
    return false;
    }
  */

  class BSPPROC{
  public:
    POLYGON* polygon;
    unsigned int count;
    bool* free;
    BSPPROC():polygon(NULL),count(0),free(NULL){}
    BSPPROC(const BSPPROC& p,bool* f=NULL){
      polygon=p.polygon;
      count=p.count;
      if(f)free=f;else{
	free=new bool[count];
	for(unsigned int i=0;i<count;i++)free[i]=true;
      }
    }
    BSPPROC(const CHUNK& m){
      polygon=(POLYGON*)m.data;
      count=(unsigned int)(m.size/3);
      free=new bool[count];
      for(unsigned int i=0;i<count;i++)free[i]=true;
    }
    ~BSPPROC(){
      count=0;
      if(free)delete[] free;
      free=NULL;
    }
    // Exts functionality
    unsigned int first(){ // First free polygon
      for(unsigned int i=0;i<count;i++)if(free[i])return i;
      return count;
    }
    BSPPROC side(char s,unsigned int idx){ // Polygones per side
      bool* f=new bool[count];
      for(unsigned int i=0;i<count;i++){
	if(free[i]){
	  if(polygon[idx].where(polygon[i])==s)f[i]=true;
	  else f[i]=false;
	}else f[i]=false;
      }
      return BSPPROC(*this,f);
    }
    BSPPROC side(char s){ // Polygones per side
      return side(s,first());
    }
  };

  BSPTREE::BSPTREE():root(NULL){}
  BSPTREE::~BSPTREE(){clean();}
  void BSPTREE::clean(){ if(root){delete root; root=NULL;} }
  BSPNODE* BSPTREE::procnode(BSPPROC proc){
    unsigned int p=proc.first();
    if(p==proc.count)return NULL;
    BSPNODE* n=new BSPNODE();
    BSPPROC on=proc.side(POLYGON::ON);
    for(unsigned int i=0;i<proc.count;i++)if(proc.free[i])n->index.push_back(i);
    n->front=procnode(proc.side(POLYGON::FRONT));
    n->back =procnode(proc.side(POLYGON::BACK ));
    return n;
  }
  //if(side==POLYGON::FRONT && !node.front)node.front=new BSPNODE(i);
  //if(side==POLYGON::FRONT && !node.back )node.back =new BSPNODE(i);
  //proc.free[i]=false;
  //return true;

  void BSPTREE::build(const CHUNK& data){
    BSPPROC proc=BSPPROC(data);
    clean();
    root=procnode(proc);
  }
}
