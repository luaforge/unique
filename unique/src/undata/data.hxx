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
  class PATH{//tolua_export
  protected:
    vector<string> path;
    void parse(string);
    string cnstr() const;
  public:
    //tolua_begin
    PATH();
    PATH(string);
    ~PATH();
    string& operator[](int); // extract component
    int operator~() const;   // num of components
    operator string() const; // return full path
    string operator()() const; // return full path
    void operator()(string); // set new value
    void operator()(int&/**k=-1 asnil**/,string&); // iterator
    PATH operator|(PATH&) const; // concat paths
    PATH operator|(string) const; // concat with string
  };
  //tolua_end
  class PATHS{//tolua_export
  protected:
    typedef map<string,PATH*> CONT;
    typedef map<string,PATH*>::iterator ITER;
    CONT cont;
  public:
    //tolua_begin
    PATHS();
    ~PATHS();
    void operator()(string&k/**="" asnil**/,PATH*&); // iterator
    operator string();
    //tolua_end
    PATH& operator[](string k);
    void set(string,PATH*);
    PATH* get(string);
    //tolua_begin
    /**PATH* tolua_index(string,get,set);**/
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
    void set(string,string);
    string get(string);
    //tolua_begin
    /**string tolua_index(string,get,set);**/
  };
  //tolua_end
  class RESOURCE;
  class CATALOG;
  class STREAM;
  class REPOS{//tolua_export
  public:
    typedef map<STREAM*,PATH> OPNSTMS;
    typedef OPNSTMS::iterator OPNSTMSITER;
  protected:
    OPNSTMS ostm;
    PATH makepath(string name, string type);
  public:
    //tolua_begin
    typedef enum RESTYPE{ // Resource type
      non=0x1, // None (resource not existing or not accessible)
      dir=0x2, // Directory (resource is directory)
      stm=0x3  // Stream (resource is stream)
    } RESTYPE;
    
    string name;
    string location;
    unbase::STATE state;
    undata::PATHS path;
    //tolua_end
    
    virtual iostream& stream(PATH path, ios::openmode mode=ios::in);
    virtual iostream& stream(string name, string type="def", ios::openmode mode=ios::in);
    virtual bool stream(iostream&);
  protected:
    virtual iostream* openstm(PATH path, ios::openmode mode=ios::in){}
    virtual bool closestm(iostream*){}
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
    virtual RESTYPE restype(string name, string type="def");
    virtual RESTYPE restype(PATH path);
    
    REPOS();
    virtual ~REPOS();
    
    operator string();
  };
  //tolua_end
  class REPOSS{//tolua_export
  public:
    typedef map<string,REPOS*> CONT;
    typedef CONT::iterator ITER;
    CONT cont;
    //tolua_begin
    REPOSS();
    ~REPOSS();
    void operator()(string&name/**="" asnil**/, REPOS*&repos/**=NULL asnil**/);
    //tolua_end
    REPOS *& operator[](string name);
    REPOS* get(string name);
    void set(string name, REPOS* repos);
    //tolua_begin
    /**REPOS* tolua_index(string,get,set);**/
    operator string();
  };
  //tolua_end
  class RESOURCE{//tolua_export
  protected:
    
  public:
    //tolua_begin
    enum RCLASS{
      dir=0x1,
      stm=0x2
    };
    enum ACCESS{
      in=0x1,
      out=0x2,
      io=0x3,
    };
    
    string name;
    string type;
    bool   exist;
    ACCESS access;
    RCLASS rclass;
    REPOS* repos;
    
    RESOURCE(const RESOURCE&);
    RESOURCE(string name, string type="def", string repos=""); // get resource info
    ~RESOURCE();
  };
  //tolua_end
  class CATALOG{//tolua_export
  protected:
    
  public:
    //tolua_begin
    enum MODE{
      in =0x1,
      out=0x2,
    };
    
  };
  //tolua_end
  class STREAM{//tolua_export
  protected:
    
  public:
    //tolua_begin
    enum MODE{
      in =0x1,
      out=0x2,
      io =0x3
    };
    enum STATE{
      good=0x0,
      bad=0x1,
      fail=0x2
    };
    unbase::STATE state;
    
  };
  //tolua_end

  //tolua_begin
  extern REPOSS repos; // repositories
  extern PATHS  path;  // standard paths
  //tolua_end

  //tolua_begin
  STREAM& stream(string name, STREAM::MODE mode, string type="def", string repos="");
  STREAM& stream(string name, string type="def", string repos="");
  
}
//tolua_end

