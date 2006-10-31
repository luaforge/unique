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
#include"platform.hxx"
#include"option.hxx"
#include<map>
#include<iostream>
#include<vector>

namespace unbase{//tolua_export
  class PATH{//tolua_export
  protected:
  public:
    //tolua_begin
    string path;
    PATH();
    PATH(string);
    ~PATH();
    string operator[](int); // extract component
    int operator~();        // num of components
    operator string();      // return full path
    PATH operator|(const PATH&);
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
    string& operator[](string type);
    operator string();
    bool pop(string type);
  };
  //tolua_end
  
  class REPOS{//tolua_export
  public:
    typedef map<iostream*,string> OPNSTMS;
    typedef OPNSTMS::iterator OPNSTMSITER;
  protected:
    OPNSTMS stm;
  public:
    //tolua_begin
    string location;
    unbase::STATE state;
    unbase::NAMES path;
    unbase::NAMES ext;
    //tolua_end
    
    virtual iostream& stream(string name, string type="", ios::openmode mode=ios::in);
    virtual bool stream(iostream& stm);
    virtual iostream* openstm(string name, ios::openmode mode=ios::in){}
    virtual bool closestm(iostream* stm){}

    //tolua_begin
    REPOS(){}
    virtual ~REPOS(){}

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
    REPOS *& operator[](string name);
    operator string();
    bool pop(string type);
  };
  //tolua_end
  
  class DATA{//tolua_export
  public:
    //tolua_begin
    static unbase::REPOSS repos; // repositories
    static unbase::NAMES path;
    static unbase::NAMES ext;
    
    static iostream& open(string name, string type, string repos, ios::openmode mode);
    static void close(iostream& s);
    
    static string __info(string);
  };
  //tolua_end

  //tolua_begin
  inline iostream& unstream(string name, ios::openmode mode, string type="", string repos=""){
    return DATA::open(name,type,repos,mode);
  }
  inline iostream& unstream(string name, string type="", string repos=""){
    return DATA::open(name,type,repos,ios::in);
  }
  inline void unstream(iostream& stm){
    DATA::close(stm);
  }
  //tolua_end
  
  class DIRECTORY: public unbase::REPOS{//tolua_export
  public:
    //tolua_begin
    DIRECTORY();
    virtual ~DIRECTORY();
    //tolua_end
    virtual bool open();
    virtual bool close();
    virtual iostream* openstm(string name, ios::openmode mode=ios::in);
    virtual bool closestm(iostream* stm);
  };//tolua_export
  
}//tolua_export

