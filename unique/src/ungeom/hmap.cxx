#include"hmap.hxx"

namespace ungeom{
  

  extern vec3 unhmap_density;
  extern vec2 unhmap_texcrd;

  HMAP::HMAP():density(0.001,0.001,0.001){}
  HMAP::~HMAP(){}
  
  bool HMAP::update(){
    if(osrc!=src || density!=odensity || texcrd!=otexcrd){
      unhmap_density=density;
      odensity=density;
      unhmap_texcrd=texcrd;
      otexcrd=texcrd;
      osrc=src;
      MDATA::put(data);
      data=MDATA::get(src);
      if(data)state=unbase::STATE(true,string("Height map \"")+src+"\" loaded...");
      else state=unbase::STATE(false,string("Height map \"")+src+"\" not loaded...");
    }
  }
  HMAP::operator string(){
    return "HMAP()";
  }
}
