/***************************************************************************
 *            data.hpp
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
#include<map>
#include<iostream>
#include<vector>

namespace undata{//tolua_export
  /*
   *  separate path
   */
  class PATH{//tolua_export
  protected:
    vector<string> path; // path is an array of entires, each of it is a separate entire (stream or catalog)
    void parse(string);
    string cnstr()const;
  public:
    //tolua_begin
    PATH();
    PATH(string);
    ~PATH();
    string& operator[](int); // extract component
    int operator~()const;   // num of components
    operator string()const; // return full path
    string operator()()const; // return full path
    void operator()(string); // set new value
    PATH apply(string)const; // apply (if path=="path/to/res/?.ext" then path=path.gsub("?",res_name))
    void operator()(int&/**k=-1 asnil**/,string&); // iterator
    PATH operator|(PATH&)const; // concat paths
    PATH operator|(string)const; // concat with string
  };
  //tolua_end
  /*
   *  PATHS
   */
  class PATHS{//tolua_export
  protected:
    typedef map<string,vector<PATH> > CONT;
    typedef CONT::iterator ITER;
    CONT cont;
    void parse(vector<PATH>&,string);
    string cnstr(vector<PATH>&);
  public:
    static vector<PATH> empty;
    //tolua_begin
    
    PATHS();
    ~PATHS();
    
    void operator()(string&/** k="" asnil**/,string&); // iterator
    operator string();
    //tolua_end
    void operator()(string&/** k="" asnil**/,vector<PATH>&); // iterator
    vector<PATH>& operator[](string);
    //tolua_begin
    /**tolua_getindex {**/
    string get(string)/**="" asnil**/;
    /**}**/
    /**tolua_setindex {**/
    void set(string,string/** p="" asnil**/);
    /**}**/
  };
  //tolua_end
  class NAMES{//tolua_export
  public:
    typedef map<string,string> CONT;
    typedef map<string,string>::iterator ITER;
    CONT cont;
    //tolua_begin
    NAMES();
    ~NAMES();
    void operator()(string&type/**="" asnil**/, string&name);
    operator string();
    //tolua_end
    string& operator[](string type);
    //tolua_begin
    /**tolua_getindex {**/
    string get(string)/**="" asnil**/;
    /**}**/
    /**tolua_setindex {**/
    void set(string,string/** s="" asnil**/);
    /**}**/
  };
  //tolua_end
  class REPOS;
  //class STREAM;
  class RESOURCE;
  //class CATALOG;
  
  class CATALOG{//tolua_export
  protected:
    
  public:
    //tolua_begin
    enum MODE{
      no =0x0,
      in =0x1,
      out=0x2,
      io =0x3
    };
    
  };
  //tolua_end
  class STREAM{//tolua_export
  public:
    //tolua_begin
    typedef long pos_type;
    enum MODE{ // open mode   // bits implement
      no =0x0, // No access   //  00
      inp=0x1, // Read only   //  01
      out=0x2, // Write only  //  10
      io =0x3, // Read/Write  //  11
      ro =0x1,
      wo =0x2,
      rw =0x3
    };
    enum STATE{ // stream status
      good=0x0,
      eof=0x1,
      bad=0x2,
      fail=0x2
    };
    enum DIR{ // seek dir
      cur=0x0,
      beg=0x1,
      end=0x2
    };
    //tolua_end
  protected:
    pos_type __length;
    pos_type __rcount;
    pos_type __wcount;
    
    virtual string __content();
    virtual void __content(string chunk);
    
    virtual void __open(){}
    virtual void __close(){}
    virtual void __read(void* chunk, pos_type count){}
    virtual void __write(const void* chunk, pos_type count){}
    virtual pos_type __tellr()const{return 0;}
    virtual pos_type __tellw()const{return 0;}
    virtual void __seekr(pos_type count,DIR dir){}
    virtual void __seekw(pos_type count,DIR dir){}
  public:
    //tolua_begin
    string name;
    PATH   path;
    REPOS* repos;
    MODE   mode;
    STATE  state;
    
    STREAM();
    STREAM(REPOS* r);
    virtual ~STREAM();
    
    // Operate
    inline void open(PATH path, MODE mode){STREAM::path=path;STREAM::name=path();STREAM::mode=mode;__open();}
    inline void close(){__close();}
    
    // Reading
    inline void read(void* chunk,pos_type count){if(mode&inp)__read(chunk,count);}
    inline string read(){if(mode&inp)return __content();else return "";}
    inline void datar(void* chunk, pos_type count){if(mode&inp)__read(chunk,count);}
    
    // Writing
    inline void write(const void* chunk,pos_type count){if(mode&out)__write(chunk,count);}
    inline void write(string chunk){if(mode&out)__content(chunk);}
    inline void dataw(const void* chunk,pos_type count){if(mode&out)__write(chunk,count);}
    
    // Count
    inline pos_type gcount()const{return __rcount;}
    inline pos_type scount()const{return __wcount;}
    
    // Tell
    inline pos_type tellr()const{if(mode&inp)return __tellr();else return 0;}
    inline pos_type tellw()const{if(mode&out)return __tellw();else return 0;}
    inline pos_type tellg()const{if(mode&inp)return __tellr();else return 0;}
    inline pos_type tells()const{if(mode&out)return __tellw();else return 0;}

    // Seek
    inline void seekr(pos_type count,DIR dir=cur){if(mode&inp)__seekr(count,dir);}
    inline void seekw(pos_type count,DIR dir=cur){if(mode&out)__seekw(count,dir);}
    inline void seekg(pos_type count,DIR dir=cur){if(mode&inp)__seekr(count,dir);}
    inline void seekp(pos_type count,DIR dir=cur){if(mode&out)__seekw(count,dir);}
    
    // Length
    inline pos_type length(){return __length;}

    virtual operator string();
  };
  //tolua_end
  class RESOURCE{//tolua_export
  protected:
    
  public:
    //tolua_begin
    enum TYPE{                // bits implement
      non=0x0, // Not found   //  00
      dir=0x1, // Directory   //  01
      stm=0x2, // Data stream //  10
      lnk=0x3, // Link        //  11
    };
    
    string name;
    string spec;
    STREAM::MODE access;
    TYPE   type;
    REPOS* repos;
    PATH   path;
    
    RESOURCE():type(non),access(STREAM::no),repos(NULL){}
    RESOURCE(string n,string s="",REPOS* r=NULL,PATH p=PATH(),TYPE t=non,STREAM::MODE a=STREAM::no):name(n),spec(s),repos(r),type(t),access(a),path(p){}
    virtual ~RESOURCE(){}

    virtual STREAM& stream(STREAM::MODE mode=STREAM::inp); // open stream
    virtual void stream(STREAM& stm); // close stream
    //virtual CATALOG& catalog(CATALOG::MODE mode=CATALOG::in);
    virtual operator string();
  };
  RESOURCE resource(string name, string spec="def", string repos=""); // get resource info
  //tolua_end
  class REPOS{//tolua_export
  public:
    typedef map<STREAM*,PATH> OPNSTMS;
    typedef OPNSTMS::iterator OPNSTMSITER;
  protected:
    OPNSTMS ostm;
    virtual string makename(string name);
    // common redefineable
    virtual STREAM* stream(PATH path, STREAM::MODE mode=STREAM::inp){return NULL;}
    virtual void stream(STREAM* stm){}
    virtual RESOURCE::TYPE restype(PATH path);
    virtual STREAM::MODE resmode(PATH path);
  public:
    //tolua_begin
    static STREAM empty;
    string name; // Repository name
    string location; // Repository location
    unbase::STATE state; // State of repoaitory
    undata::PATHS path; // Repository pathes
    unsigned int prior; // Repository priority
    //tolua_end
  public:
    /* name automatic convert to path, as example:
       
       name=metal.steel.anisotropic, type="material"
                            |
			    V
       path[type]+"metal/steel/anisotropic"+ext[type]
                            |
			    V
       data/material/metal/steel/anisotropic.lua     */
    
    //tolua_begin
    virtual RESOURCE resource(string name, string spec=""); // get resource info
    virtual STREAM& stream(RESOURCE& res, STREAM::MODE mode=STREAM::inp); // open stream
    virtual void stream(STREAM& s); // close stream
    
    REPOS();
    virtual ~REPOS();
    
    virtual operator string();
  };
  //tolua_end
  class REPOSS{//tolua_export
  protected:
    typedef map<string,REPOS*> CONT;
    typedef CONT::iterator ITER;
    CONT cont;
  public:
    //tolua_begin
    REPOSS();
    ~REPOSS();
    void operator()(string&name/**="" asnil**/, REPOS*&repos/**=NULL asnil**/);
    //tolua_end
    REPOS *& operator[](string name);
    //tolua_begin
    /**tolua_getindex {**/
    REPOS* get(string name);
    /**}**/
    /**tolua_setindex {**/
    void set(string name,REPOS*repos);
    /**}**/
    operator string();
  };
  //tolua_end
   
  //tolua_begin
  extern REPOSS repos; // repositories
  extern PATHS  path;  // standard paths
  //tolua_end

  //tolua_begin
  //STREAM& stream(string name, STREAM::MODE mode, string type="def", string repos="");
  //STREAM& stream(string name, string type="def", string repos="");
  
}
//tolua_end

