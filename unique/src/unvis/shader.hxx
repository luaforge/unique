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
  class SHADERPROG{//tolua_export
  public:
    //tolua_begin
    SHADERPROG(){}
    virtual ~SHADERPROG(){}
  
    virtual bool update(){}
    virtual void bind(){}
    virtual void ubind(){}
    //tolua_end
  };//tolua_export
  class SHADERCHUNK{//tolua_export
  public:
    //tolua_begin
    SHADERCHUNK(){}
    virtual ~SHADERCHUNK(){}
    //tolua_end
  };//tolua_export
  
  class SHADERGROUP{//tolua_export
  protected:
    typedef map<string,SHADERPROG*> CONT;
    typedef map<string,SHADERPROG*>::iterator ITER;
    CONT array;
  public:
    //tolua_begin
    SHADERGROUP();
    ~SHADERGROUP();
    void operator()(string&/**k="" asnil**/,SHADERPROG*&);
    /**tolua_getindex {**/
    SHADERPROG* get(string);
    /**}**/
    /**tolua_setindex {**/
    void set(string,SHADERPROG*);
    /**}**/
    operator string();
    //tolua_end
    SHADERPROG* operator[](string);
  };//tolua_export
  
  /*
   *  GLSL
   */
  class SLINT{//tolua_export
  protected:
    int value;
  public:
    //tolua_begin
    SLINT(int v):value(v){}
    int operator()(){return value;}
    void operator()(int v){value=v;}
    //tolua_end
  };//tolua_export
  class SLSAMP{//tolua_export
  protected:
    int value;
  public:
    //tolua_begin
    SLSAMP(int v):value(v){}
    int operator()(){return value;}
    void operator()(int v){value=v;}
    //tolua_end
  };//tolua_export
  //tolua_begin
  extern const SLSAMP sampler[8];
  //tolua_end
  class GLSLPROG;
  class GLSLUNIFORM{//tolua_export
  protected:
    GLSLPROG* prog;
  public:
    GLSLUNIFORM(GLSLPROG*);
    ~GLSLUNIFORM();
    //tolua_begin
    /**tolua_getindex {**/
    bool get(string name);
    /**}**/
    /**tolua_setindex {**/
    void setbool(string,bool);
    void setscal(string,scalar);
    void setvec2(string,SLINT&);
    void setvec2(string,vec2&);
    void setvec3(string,vec3&);
    void setvec4(string,vec4&);
    void setmat3(string,mat3&);
    void setmat4(string,mat4&);
    void setsamp(string,SLSAMP&);
    /**}**/
    operator string();
    //tolua_end
  };//tolua_export
  
  class GLSLSHADER: public SHADERCHUNK{//tolua_export
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
  
  class GLSLPROG: public SHADERPROG{//tolua_export
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
    //tolua_end

    bool link();

    bool detach(GLuint);
    bool attach(GLuint,GLSLSHADER*);
    GLSLSHADER* attached(GLuint);

    void defaultattribs();
    void defaultparameters();
    void binddefaultparameters();
    GLint uniformlocation(string name);
    
    //tolua_begin
    operator string();
  };
  //tolua_end
  
}//tolua_export

