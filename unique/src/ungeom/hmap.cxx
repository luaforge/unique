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
      undata::RESOURCE r=undata::resource(name,"heightmapdata");
      if(r.type==undata::RESOURCE::stm && r.access&undata::STREAM::inp){
	undata::STREAM& s=r.stream();
	if(LOADER::load(*this,s)){// if loaded ok
	  r.stream(s);
	  state=unbase::STATE(true,string("Height map \"")+src+"\" loaded...");
	  return true;
	}
	r.stream(s);
	state=unbase::STATE(false,string("Height map \"")+src+"\" not loaded...");
	return false;
      }
    }
  }
  HMAP::operator string(){
    return "HMAP()";
  }
}
