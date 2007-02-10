#pragma once
#include"unbase.hxx"

namespace unobj{//tolua_export
  /*
    enum MODE{// Rendering mode
    geom=0x01,// Rendering geometry only
    matl=0x02,// Rendering with material
    name=0x04,// Generating names
    axis=0x08,// Rendering Axis
    imag=0x10,// Rendering imagined geometry
    link=0x20,// Rendering Links
    quer=0x40,// Quering rendered fragments
    shad=0x80,// Rendering shadows
    };
  */
  class MODE{//tolua_export
    // Rendering mode
  public:
    union {
      struct {
	bool __begin_[0];
	//tolua_begin
	bool geom;// Rendering geometry only
	bool matl;// Rendering with material
	bool name;// Generating names
	bool axis;// Rendering Axis
	bool modl;// Rendering imagined geometry
	bool link;// Rendering Links
	bool quer;// Quering rendered fragments
	bool shad;// Rendering shadows
	//tolua_end
	bool __end_[0];
      };
      bool array[];
    };
    //tolua_begin
    MODE();
    MODE(bool);
    int operator~();
    bool& operator[](int i);
    MODE operator()(const MODE&, const MODE&)const;
    operator string();
    //tolua_end
  };//tolua_export
  class RENDER{
  public:
    
  };
}//tolua_export
