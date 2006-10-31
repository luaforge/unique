/***************************************************************************
 *            data.cpp
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

#include"data.hxx"
#include<fstream>

namespace unbase{
  /*
   *  PATH
   */
  PATH::PATH(){}
  PATH::PATH(string p):path(p){}
  PATH::~PATH(){}
  PATH::operator string(){return path;}
  int PATH::operator~(){
    int c=1;
    for(int i=0;(i=path.find("/",i))<path.length()-1;i++,c++);
    return c;
  }
  string PATH::operator[](int n){
    if(n<1||n>~(*this))return "";
    int p,i,c;
    for(p=0,i=0,c=1;(i=path.find("/",p))<path.length();c++)
      if(c==n) return path.substr(p,i-p); else p=i+1;
    return path.substr(p);
  }
  PATH PATH::operator|(const PATH&_n){
    //string r=path+n.path;
    //r=r.replace(r.begin(),r.end(),"//","/");
    string r=path,n=_n.path;
    //if(n.find("/")==0)n.erase(0);
    //if(n.rfind("/")==n.length()-1)n.erase(n.length()-1);
    //if(r.rfind("/")==r.length()-1)r.erase(r.length()-1);
    return PATH(r+"/"+n);
  }
  /*
   *  NAMES
   */
  NAMES::NAMES(){}
  NAMES::~NAMES(){}
  void NAMES::operator()(string&type, string&name){
    ITER i=cont.begin();
    if(type!=""){
      i=cont.find(type);
      if(i!=cont.end())i++;
    }
    if(i==cont.end()){
      type="";
      name="";
    }else{
      type=i->first;
      name=i->second;
    }
  }
  string& NAMES::operator[](string type){
    return cont[type];
  }
  bool NAMES::pop(string type){
    ITER i=cont.find(type);
    if(i==cont.end())return false;
    cont.erase(type);
    return true;
  }
  NAMES::operator string(){
    string r="{";
    for(ITER i=cont.begin();i!=cont.end();i++){
      r+=i->first+"=\""+i->second+"\",";
    }
    r.erase(r.length()-1);
    r+="}";
    return r;
  }
  
  /*
   *  REPOS
   */
  iostream& REPOS::stream(string name, string type, ios::openmode mode){
    string full=path[type]+"/"+name+"."+ext[type];
    iostream* s=openstm(full,mode);
    stm[s]=full;
    return *s;
  }
  bool REPOS::stream(iostream& s){
    if(stm.find(&s)!=stm.end()){
      closestm(&s);
      stm.erase(&s);
      return true;
    }else{
      return false;
    }
  }
  REPOS::operator string(){
    string r;
    r+=string("location=\"")+location+"\",";
    r+=string("stream={");
    for(OPNSTMSITER i=stm.begin();i!=stm.end();i++){
      r+=string("[")+i->first+"]=\""+i->second+"\",";
    }
    r.erase(r.length()-1);
    r+="}";
    return r;
  }
  /*
   *  REPOSS
   */
  REPOSS::REPOSS(){}
  REPOSS::~REPOSS(){}
  void REPOSS::operator()(string&name, REPOS*&repos){
    ITER i=cont.begin();
    if(name!=""){
      i=cont.find(name);
      if(i!=cont.end())i++;
    }
    if(i==cont.end()){
      name="";
      repos=NULL;
    }else{
      name=i->first;
      repos=i->second;
    }
  }
  REPOS *& REPOSS::operator[](string name){
    return cont[name];
  }
  REPOSS::operator string(){
    string r="{";
    for(ITER i=cont.begin();i!=cont.end();i++){
      r+=i->first+"=\""+i->second+"\",";
    }
    r.erase(r.length()-1);
    r+="}";
    return r;
  }
  bool REPOSS::pop(string type){
    ITER i=cont.find(type);
    if(i==cont.end())return false;
    cont.erase(type);
    return true;
  }
  /*
   *  DATA
   */
  REPOSS DATA::repos; // repositories
  NAMES DATA::path;
  NAMES DATA::ext;

  iostream& DATA::open(string name, string type, string rep, ios::openmode mode){
    if(rep==""){
      for(REPOSS::ITER i=repos.cont.begin();i!=repos.cont.end();i++){
	if(i->second){
	  REPOS& r=*(i->second);
	  {
	    iostream&s=r.stream(name,type,mode);
	    if(s.good())return s;
	    r.stream(s);
	  }
	  {
	    iostream&s=r.stream(name,"",mode);
	    REPOSS::ITER n=i; n++;
	    if(s.good() || n==repos.cont.end())return s;
	    r.stream(s);
	  }
	}else{
	  repos.cont.erase(i);
	}
      }
    }else{
      REPOS& r=*repos[rep];
      iostream&s=r.stream(name,type,mode);
      return s;
    }
  }
  void DATA::close(iostream& s){
    for(REPOSS::ITER i=repos.cont.begin();i!=repos.cont.end();i++){
      REPOS& r=*(i->second);
      if(r.stream(s))return;
    }
  }
  /*
   *  DERECTORY
   */
  DIRECTORY::DIRECTORY():REPOS(){
    
  }
  DIRECTORY::~DIRECTORY(){
    
  }
  bool DIRECTORY::open(){
    
  }
  bool DIRECTORY::close(){
    
  }
  iostream* DIRECTORY::openstm(string name, ios::openmode mode){
    return new fstream((location+name).data(),mode);
  }
  bool DIRECTORY::closestm(iostream* s){
    delete s;
  }
}
