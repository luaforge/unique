/***************************************************************************
 *            texture.hpp
 *
 *  Wed Jun 29 17:12:37 2005
 *  Copyright  2005  Fenix
 *  tonder@trktvs.ru
 ****************************************************************************/

/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Library General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#pragma once
#include "unbase.hxx"
#include "unmath.hxx"
#include "unogl.hxx"
#include "image.hxx"

namespace unvis{//tolua_export
  class TEXGROUP;
  
  // Abstract OpenGL texture class
  class TEXTURE{//tolua_export
  public:
    class COORD{//tolua_export
    public:
      //tolua_begin
      enum { // Coord
	s=GL_S,
	t=GL_T,
	r=GL_R,
	q=GL_Q,
      };
      enum { // Plane
	eye    =GL_EYE_LINEAR,
	object =GL_OBJECT_LINEAR,
	sphere =GL_SPHERE_MAP,
	reflect=GL_REFLECTION_MAP,
	normal =GL_NORMAL_MAP,
      };
      unsigned int coord; // Coordinate which generated
      bool   state;       // Enable/Disable
      unsigned int mode;  // Generation mode : GL_OBJECT_PLANE, GL_EYE_PLANE, GL_SPHERE_MAP
      vec4   scale;       // Scale     default vec4(1.0,1.0,1.0,0.0)
      //tolua_end
      
      COORD(unsigned int);
      COORD(unsigned int,unsigned int);
      COORD(unsigned int,unsigned int,vec4);
      void set();
    };//tolua_export
    
    class GENCRD{//tolua_export
    public:
      COORD s,t,r,q;//tolua_export
      GENCRD();
      void set();
    };//tolua_export
    
    class WRAP{//tolua_export
    public:
      //tolua_begin
      enum {
	repeat   =GL_REPEAT,       // Повторение текстуры (граница игнорируется)
	clamp    =GL_CLAMP,        // Клампинг используя границу
	clampedge=GL_CLAMP_TO_EDGE,// Клампинг игнорируя края
      };
      int s,t,r;
      //tolua_end
      WRAP(int _s=WRAP::repeat,int _t=WRAP::repeat,int _r=WRAP::repeat);
      void set(unsigned int);
    };//tolua_export
    
    class FUNCPAR{//tolua_export
    public:
      //tolua_begin
      unsigned int target_rgb;
      unsigned int target_alpha;
      unsigned int rgb;
      unsigned int alpha;
      //tolua_end
      FUNCPAR();
      FUNCPAR(unsigned int trgb, unsigned int ta);
      void set();
    };//tolua_export
    
    class FUNC{//tolua_export
    public:
      //tolua_begin
      enum {
	// Функция текстурирования
	replace =GL_REPLACE, // Замещение фрагмента текселем текстуры
	modulate=GL_MODULATE,// Цвет фрагмента модулируется содержимым текстурной карты
	decal   =GL_DECAL,   // Замещение, работает только для RGB и RGBA и обрабатывает альфа канал иначе
	blend   =GL_BLEND,   // Блендинг
	combine =GL_COMBINE, // Комбинирование
      };// type
      enum {
	dot3rgb    =GL_DOT3_RGB,
	dot3rgba   =GL_DOT3_RGBA,
	//replace =GL_REPLACE,
	//modulate=GL_MODULATE,
	add        =GL_ADD,     // Добавление
	addsign    =GL_ADD_SIGNED, //
	sub        =GL_SUBTRACT_ARB,
	interpol   =GL_INTERPOLATE_ARB,
      };// make
      enum {
	primary =GL_PRIMARY_COLOR_ARB, // Основной цвет фрагмента (Cf, Af)
	texture =GL_TEXTURE,      // Цвет текстуры (Ct, At)
	constant=GL_CONSTANT_ARB, // Цвет, заданный при помощи glTexEnfv
	previos =GL_PREVIOUS_ARB, //
      };// src
      enum {
	src_color          =GL_SRC_COLOR,          // color
	one_minus_src_color=GL_ONE_MINUS_SRC_COLOR,// 1 - color
	src_alpha          =GL_SRC_ALPHA,          // alpha
	one_munis_src_alpha=GL_ONE_MINUS_SRC_ALPHA,// 1 - alpha
      };// opr
      unsigned int type;   // Texturing function
      FUNCPAR src[3]; // Sources
      FUNCPAR opr[3]; // Operands
      unsigned int combine_rgb;   // Cmd
      unsigned int combine_alpha; //
      unmath::scalar scale_rgb;
      unmath::scalar scale_alpha;
      //tolua_end
      FUNC();
      void set();
    };//tolua_export
    
    //tolua_begin
    enum FLTBITS{ // Texture float bits
      float16,
      float32,
    };
    enum FORMAT{ // Texture format
      lum     =GL_LUMINANCE,
      luma    =GL_LUMINANCE_ALPHA,
      rgb     =GL_RGB,
      rgba    =GL_RGBA,
      depth   =GL_DEPTH_COMPONENT,
    };
    enum INTERNFORMAT{ // Texture internal format
      // Alpha
      alpha4  =GL_ALPHA4,
      alpha8  =GL_ALPHA8,
      alpha12 =GL_ALPHA12,
      alpha16 =GL_ALPHA16,
      // Luminance
      lum4    =GL_LUMINANCE4,
      lum8    =GL_LUMINANCE8,
      lum12   =GL_LUMINANCE12,
      lum16   =GL_LUMINANCE16,
      // Luminance Alpha
      lum4a4  =GL_LUMINANCE4_ALPHA4,
      lum6a2  =GL_LUMINANCE6_ALPHA2,
      lum8a8  =GL_LUMINANCE8_ALPHA8,
      lum12a4 =GL_LUMINANCE12_ALPHA4,
      lum12a12=GL_LUMINANCE12_ALPHA12,
      lum16a16=GL_LUMINANCE16_ALPHA16,
      // Intensity
      intens4 =GL_INTENSITY4,
      intens8 =GL_INTENSITY8,
      intens12=GL_INTENSITY12,
      intens16=GL_INTENSITY16,
      // RGB
      r3g3b2  =GL_R3_G3_B2,
      rgb4    =GL_RGB4,
      rgb5    =GL_RGB5,
      rgb8    =GL_RGB8,
      rgb10   =GL_RGB10,
      rgb12   =GL_RGB12,
      rgb16   =GL_RGB16,
      // RGBA
      rgba2   =GL_RGBA2,
      rgba4   =GL_RGBA4,
      rgb5a1  =GL_RGB5_A1,
      rgba8   =GL_RGBA8,
      rgb10a2 =GL_RGB10_A2,
      rgba12  =GL_RGBA12,
      rgba16  =GL_RGBA16,
      // Compressed format
      dxt1rgb =GL_COMPRESSED_RGB_S3TC_DXT1_EXT,
      dxt1rgba=GL_COMPRESSED_RGBA_S3TC_DXT1_EXT,
      dxt3rgba=GL_COMPRESSED_RGBA_S3TC_DXT3_EXT,
      dxt5rgba=GL_COMPRESSED_RGBA_S3TC_DXT5_EXT,
    };
    enum FILTER{
      // Константы режимов
      // Фильтрация
      linear    =0x1,
      bilinear  =0x2,
      trilinear =0x3,
      anisotropy=0x4,
      fullinear =0x5,
      // Направления генерации текстурных координат
    };
    //tolua_end
  protected:
    unsigned int Enabled[4];
    
    string osrc;
    unsigned int owidth;
    unsigned int oheight;
    
    unsigned int glid;   // OpenGL texture identifier
    
    unsigned int typetarget;
    
    bool inited;
    bool binded;
  public:
    //tolua_begin
    unbase::STATE state;
    // Texturing parameters
    FILTER filter;  // Filtration type
    FUNC func;      // Texturing function
    bool    mipmap; // Mipmapping
    WRAP wrap;      // Texture wraping
    GENCRD cgen;    // Texture coord automatic generation
    string  src;    // Texture source
    string  name;   // Texture name
    TEXGROUP* parent;
    unsigned int format;
    unsigned int storage;
    unsigned int chan;
    unsigned int width;
    unsigned int height;
    unsigned int length;
    bool screen;
    
    // Methods
    static unsigned int maxunits();
    
    TEXTURE();
    virtual ~TEXTURE();
    
    virtual operator string();

    // Binding
    virtual void bind();
    virtual void ubind();
    virtual bool update();
    virtual void copy();
    virtual void init();
    //tolua_end
    
  };//tolua_export

  class TEXGROUP: public TEXTURE{//tolua_export
  protected:
    typedef map<string,TEXTURE*> POOL;
    typedef map<string,TEXTURE*>::iterator ITER;
    POOL pool;
    bool autoload;
    string fullhiername(string n="");
  public:
    const TEXTURE* operator[](string);
    //tolua_begin
    TEXGROUP();
    TEXGROUP(bool al);
    ~TEXGROUP();
    void operator()(string&/**k="" asnil**/,TEXTURE*&);
    /**tolua_getindex {**/
    TEXTURE* get(string name);
    /**}**/
    /**tolua_setindex {**/
    void set(string name, TEXTURE* tex);
    /**}**/
    virtual operator string();
  };
  //tolua_end

  int glTextureCompatSize(int);
  
}//tolua_export
