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

  class TEXTURES;

  class TEXCRD{
  public:
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
  
    GLenum coord; // Coordinate which generated
    bool   state; // Enable/Disable
    GLenum  mode; // Generation mode : GL_OBJECT_PLANE, GL_EYE_PLANE, GL_SPHERE_MAP
    vec4   scale; // Scale     default vec4(1.0,1.0,1.0,0.0)
  
    TEXCRD(GLenum);
    TEXCRD(GLenum,GLenum);
    TEXCRD(GLenum,GLenum,vec4);
    void set();
    CLASSINFODECL
  };
  
  class TEXCGEN{
  public:
    TEXCRD s,t,r,q;
    TEXCGEN();
    void set();
  };

  class TEXWRAP{
  public:
    enum{// Функции управления наложением
      repeat   =GL_REPEAT,       // Повторение текстуры (граница игнорируется)
      clamp    =GL_CLAMP,        // Клампинг используя границу
      clampedge=GL_CLAMP_TO_EDGE,// Клампинг игнорируя края
    };
    GLint s,t,r;
    TEXWRAP(GLint _s=TEXWRAP::repeat,GLint _t=TEXWRAP::repeat,GLint _r=TEXWRAP::repeat);
    void set(GLuint);
  };

  class TEXFUNCPAR{
  public:
    GLuint target_rgb;
    GLuint target_alpha;
    GLuint rgb;
    GLuint alpha;
    TEXFUNCPAR();
    TEXFUNCPAR(GLuint trgb, GLuint ta);
    void set();
    CLASSINFODECL
  };

  class TEXFUNC{
  public:
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
    GLuint type;   // Texturing function
    TEXFUNCPAR src[3]; // Sources
    TEXFUNCPAR opr[3]; // Operands
    GLuint combine_rgb;   // Cmd
    GLuint combine_alpha; //
    scalar scale_rgb;
    scalar scale_alpha;
    TEXFUNC();
    void set();
    CLASSINFODECL
  };
  // Abstract OpenGL texture class
  class TEXTURE{//tolua_export
  protected:
    GLenum Enabled[4];
    string  osrc;
    bool inited;
    unsigned int owidth;
    unsigned int oheight;
  public:
    static const GLuint textarget;
    GLuint typetarget;
    enum { // Texture float bits
      float16,
      float32,
    };
    enum { // Texture format
      lum     =GL_LUMINANCE,
      luma    =GL_LUMINANCE_ALPHA,
      rgb     =GL_RGB,
      rgba    =GL_RGBA,
      depth   =GL_DEPTH_COMPONENT,
    };
    enum { // Texture internal format
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
    enum {
      //textarget=0,
      // Константы режимов
      // Фильтрация
      linear    =0x1,
      bilinear  =0x2,
      trilinear =0x3,
      anisotropy=0x4,
      fullinear =0x5,
      // Направления генерации текстурных координат
    };
    bool binded;
    unbase::STATE state;
    // Texturing parameters
    GLuint glid;    // OpenGL texture identifier
    GLuint filter;  // Filtration type
    TEXFUNC func;   // Texturing function
    bool    mipmap; // Mipmapping
    TEXWRAP wrap;   // Texture wraping
    TEXCGEN cgen;   // Texture coord automatic generation
    string  src;    // Texture source
    string  name;   // Texture name
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

    // Binding
    virtual void bind();
    virtual void ubind();
    virtual bool update();
    virtual void copy();
    virtual void init();
  };//tolua_export

  class TEXTURES{//tolua_export
  public:
    typedef map<string,TEXTURE*> CONT;
    typedef map<string,TEXTURE*>::iterator ITER;
  public:
    CONT array;
    //tolua_begin
    TEXTURES();
    ~TEXTURES();
    void operator()(string&name/**="" asnil**/,TEXTURE*&tex);
    TEXTURE* get(string name)/**=NULL asnil**/;
    void set(string name, TEXTURE* tex);
    //const TEXTURE* operator[](string);
    operator string();
  };
  //tolua_end

  int glTextureCompatSize(int);
  
}//tolua_export
