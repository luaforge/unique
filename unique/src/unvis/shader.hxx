/***************************************************************************
 *            shader.hpp
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
#include"unbase.hxx"
#include"unmath.hxx"
#include"undata.hxx"
#include"unogl.hxx"

#define SHADER_TEST_MODE 

#ifdef SHADER_TEST_MODE
#   define TESTMSG(str){ cout<<str; }
#else
#   define TESTMSG(str){ ; }
#endif

#define SEHADER_FAST_UNIFORM

namespace unvis{//tolua_export
  /*
   *  COMMON
   */
  class SHDGROUP;
  class SHADER{//tolua_export
  public:
    //tolua_begin
    SHDGROUP* parent;
    string name;

    SHADER():parent(NULL){}
    virtual ~SHADER(){}
    
    virtual bool update(){}
    virtual void bind(){}
    virtual void ubind(){}
    
    virtual operator string();
    //tolua_end
  };//tolua_export
  
  class SHDCHUNK{//tolua_export
  public:
    //tolua_begin
    SHDCHUNK(){}
    virtual ~SHDCHUNK(){}
    //tolua_end
  };//tolua_export
  
  class SHDGROUP: public SHADER{//tolua_export
  protected:
    typedef map<string,SHADER*> POOL;
    typedef map<string,SHADER*>::iterator ITER;
    POOL pool;
    bool autoload;
  public:
    string fullhiername(string n="");
    ITER begin();
    ITER end();
    //tolua_begin
    SHDGROUP();
    SHDGROUP(bool autoload);
    ~SHDGROUP();
    void operator()(string&/**k="" asnil**/,SHADER*&);
    /**tolua_getindex {**/
    SHADER* get(string);
    /**}**/
    /**tolua_setindex {**/
    void set(string,SHADER*);
    /**}**/
    virtual operator string();
    //tolua_end
    SHADER* operator[](string);
  };//tolua_export
  
  /*
   *  GLSL
   */
  class sint{//tolua_export
  protected:
    int value;
  public:
    //tolua_begin
    sint(int v):value(v){}
    operator int* (){return &value;}
    int& operator()(){return value;}
    void operator()(int v){value=v;}
    //tolua_end
  };//tolua_export
  class GLSLPROG;
  class GLSLUNIFORM{//tolua_export
  protected:
    GLSLPROG* prog;
    enum TYPE{
      BOOL=0x1,
      SCAL=0x2,
      SINT=0x3,
      VEC2=0x4,
      VEC3=0x5,
      VEC4=0x6,
      MAT3=0x7,
      MAT4=0x8,
    };
    map<string,int> type;
  public:
    bool nobool;
    float noscal;
    
    GLSLUNIFORM(GLSLPROG*);
    ~GLSLUNIFORM();
    //tolua_begin
    /**tolua_getindex {**/
    void getbool(string name, bool* ret/**=self->nobool asnil**/);
    void getscal(string name,float* ret/**=self->noscal asnil**/);
    /*
    sint* getsint(string name);
    vec2* getvec2(string name);
    vec3* getvec3(string name);
    vec4* getvec4(string name);
    mat3* getmat3(string name);
    mat4* getmat4(string name);
    */
    /**}**/
    /**tolua_setindex {**/
    void setbool(string,bool);
    void setscal(string,float);
    void setsint(string,sint&);
    void setvec2(string,unmath::vec2&);
    void setvec3(string,unmath::vec3&);
    void setvec4(string,unmath::vec4&);
    void setmat3(string,unmath::mat3&);
    void setmat4(string,unmath::mat4&);
    void setnull(string,void*);
    /**}**/
    operator string();
    //tolua_end
  };//tolua_export
  
  class GLSLSHADER: public SHDCHUNK{//tolua_export
  protected:
    string osrc,otext;
  public:
    typedef map<string,GLint> UNIFORM;
    
    UNIFORM uniform;
    GLuint obj;      // ARB Shader object handle
    //tolua_begin
    string src;      // Source name
    string text;     // Shared source text
    unbase::STATE state;

    GLSLSHADER();
    GLSLSHADER(string);
    GLSLSHADER(string,string);
    virtual ~GLSLSHADER();
    //tolua_end
    
    virtual bool load();
    virtual bool compile();
    virtual bool param();
    
    //tolua_begin
    virtual bool update(); // If return true then update GLSLPROG too
    virtual operator string();
  };
  //tolua_end
  
  /* Vertex shader */
  class GLSLVERT: public GLSLSHADER{//tolua_export
  public:
    //tolua_begin
    GLSLVERT();
    GLSLVERT(string);
    GLSLVERT(string,string);
    virtual ~GLSLVERT();

    virtual operator string();
  };
  //tolua_end
  
  /* Fragment shader */
  class GLSLFRAG: public GLSLSHADER{//tolua_export
  public:
    //tolua_begin
    GLSLFRAG();
    GLSLFRAG(string);
    GLSLFRAG(string,string);
    virtual ~GLSLFRAG();

    virtual operator string();
  };
  //tolua_end
  
  class GLSLPROG: public SHADER{//tolua_export
  public:
    typedef vector<GLSLSHADER*> CONT;
    typedef vector<GLSLSHADER*>::iterator ITER;
  protected:
    GLSLSHADER::UNIFORM vars;
    bool upd;     // Update link
    GLuint osize; // Count Shaders
  public:
    GLuint obj;   // Program Object ARB
    CONT array;
    
    //tolua_begin
    GLSLUNIFORM uniform;
    unbase::STATE state;

    GLSLPROG();
    virtual ~GLSLPROG();
  
    bool update();
    void bind();
    void ubind();

    /**tolua_getindex {**/
    GLSLSHADER* get(int);
    /**}**/
    /**tolua_setindex {**/
    void set(int, GLSLSHADER*);
    /**}**/
    
    virtual operator string();
    //tolua_end
    
    GLint uniformlocation(string name);
  protected:
    bool link();
    
    bool detach(GLuint);
    bool attach(GLuint,GLSLSHADER*);
    GLSLSHADER* attached(GLuint);

    void defaultattribs();
    void defaultparameters();
    void binddefaultparameters();
    
  };//tolua_export
  
}//tolua_export

