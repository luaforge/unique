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
  string PATH::cnstr() const{
    string r;
    for(int i=0;i<path.size();i++){
      r+=path[i]; if(i!=path.size()-1)r+="/";
    }
    return r;
  }
  void PATH::parse(string _p){
    path.clear();
    int t,i,j;
    for(i=0,t=0;i<_p.length();t=i){
      i=_p.find("/",i);
      path.push_back(_p.substr(t,i-t));
      for(i;_p[i]=='/'&&i<_p.length();i++);
    }
  }
  PATH::PATH(){}
  PATH::PATH(string _p){parse(_p);}
  PATH::~PATH(){}
  PATH::operator string()const{return string("PATH(\"")+cnstr()+"\")";}
  int PATH::operator~()const{return path.size();}
  string& PATH::operator[](int _n){return path[_n];}
  void PATH::operator()(int&k/**-1 asnil**/,string&v){
    if(k==-1){
      k=0; v=path[k];
    }else if(k+1>=path.size()){
      k=-1; v="";
    }else{
      k++; v=path[k];
    }
  }
  PATH PATH::operator|(PATH&_n) const{
    PATH r;
    r.path=path;
    for(int i=0;i<~_n;i++)if(_n[i].length()>0)r.path.push_back(_n[i]);
    return r;
  }
  PATH PATH::operator|(string _n)const{PATH _p(_n); return (*this)|_p;}
  string PATH::operator()()const{return cnstr();}
  void PATH::operator()(string _n){parse(_n);}
  
  /*
   *  PATHS
   */
  PATHS::PATHS(){}
  PATHS::~PATHS(){}
  void PATHS::operator()(string&k/**="" asnil**/, PATH*&v){
    ITER i=cont.begin();
    if(k!=""){
      i=cont.find(k);
      if(i!=cont.end())i++;
    }
    if(i==cont.end()){
      k="";
      v=NULL;
    }else{
      k=i->first;
      v=i->second;
    }
  }
  PATH& PATHS::operator[](string k){
    return *cont[k];
  }
  PATHS::operator string(){
    string r="PATHS{";
    int t=r.length();
    for(ITER i=cont.begin();i!=cont.end();i++){
      r+=i->first+"="+static_cast<string>(*(i->second))+",";
    }
    if(r.length()>t)r.erase(r.length()-1);
    r+="}";
    return r;
  }
  void PATHS::set(string k, PATH* _p){
    if(k=="")return;
    if(_p){
      cont[k]=_p;
    }else{
      cont.erase(k);
    }
  }
  PATH* PATHS::get(string k){
    if(k=="")return NULL;
    if(cont.find(k)!=cont.end()){
      return cont[k];
    }
    return NULL;
  }

  /*
   *  NAMES
   */
  NAMES::NAMES(){}
  NAMES::~NAMES(){}
  void NAMES::operator()(string&k, string&v){
    ITER i=cont.begin();
    if(k!=""){
      i=cont.find(k);
      if(i!=cont.end())i++;
    }
    if(i==cont.end()){
      k="";
      v="";
    }else{
      k=i->first;
      v=i->second;
    }
  }
  string& NAMES::operator[](string k){
    return cont[k];
  }
  NAMES::operator string(){
    string r="NAMES{";
    int t=r.length();
    for(ITER i=cont.begin();i!=cont.end();i++){
      r+=i->first+"=\""+i->second+"\",";
    }
    if(r.length()>t)r.erase(r.length()-1);
    r+="}";
    return r;
  }
  void NAMES::set(string k, string v){
    if(k=="")return;
    if(v!=""){
      cont[k]=v;
    }else{
      cont.erase(k);
    }
  }
  string NAMES::get(string k){
    if(k=="")return NULL;
    if(cont.find(k)!=cont.end()){
      return cont[k];
    }
    return "";
  }
  
  /*
   *  REPOS
   */
  REPOS::REPOS(){
    path.set("def",new PATH());
    ext["def"]="?";
  }
  REPOS::~REPOS(){
    delete path.get("def");
  }
  PATH REPOS::makepath(string n, string t){
    string e=ext.get(t)!=""?ext[t]:ext["def"];
    string r;
    int i,b=0;
    for(i=0;(i=e.find("?",b))<e.length();i++,b=i){
      r+=e.substr(b,i-b);
      r+=n;
    }
    r+=e.substr(b);
    PATH p=path.get(t)?path[t]:path["def"];
    return p|r;
  }
  iostream& REPOS::stream(string n, string t, ios::openmode m){
    PATH p(makepath(n,t));
    return stream(p,m);
  }
  iostream& REPOS::stream(PATH p, ios::openmode m){
    iostream* s=openstm(p,m);
    ostm[s]=p;
    return *s;
  }
  bool REPOS::stream(iostream& s){
    if(ostm.find(&s)!=ostm.end()){
      closestm(&s);
      ostm.erase(&s);
      return true;
    }else{
      return false;
    }
  }
  REPOS::operator string(){
    string r;
    r+=string("location=\"")+location+"\",";
    r+=string("stream={");
    for(OPNSTMSITER i=ostm.begin();i!=ostm.end();i++){
      r+=string("[")+i->first+"]=\""+static_cast<string>(i->second)+"\",";
    }
    r.erase(r.length()-1);
    r+="}";
    return r;
  }
  REPOS::RESTYPE REPOS::restype(string n, string t){
    PATH f=makepath(n,t);
    return restype(f);
  }
  REPOS::RESTYPE REPOS::restype(PATH p){
    return non;
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
  PATHS DATA::path;
  NAMES DATA::ext;

  REPOS::RESTYPE DATA::restype(string n, string t, string r){
    if(r==""){
      for(REPOSS::ITER i=repos.cont.begin();i!=repos.cont.end();i++){
	if(i->second){
	  REPOS::RESTYPE s=i->second->restype(n,t);
	  if(s!=REPOS::non)return s;
	}
      }
    }else{
      if(repos.cont.find(r)!=repos.cont.end())return repos[r]->restype(n,t);
    }
    return REPOS::non;
  }

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
}

#include<sys/types.h> 
#include<sys/stat.h> 
#include<unistd.h> 
namespace unbase{ 
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
  iostream* DIRECTORY::openstm(PATH p, ios::openmode m){
    PATH l(location);
    PATH f=l|p;
    return new fstream(f().data(),m);
  }
  bool DIRECTORY::closestm(iostream* s){
    delete s;
  }
  REPOS::RESTYPE DIRECTORY::restype(PATH p){
    PATH l(location);
    PATH f=l|p;
    struct stat s;
    if(stat(f().data(),&s))return non;
    if(S_ISREG(s.st_mode))return stm;
    if(S_ISDIR(s.st_mode))return dir;
    return non;
  }
  REPOS::RESTYPE DIRECTORY::restype(string n, string t){
    return REPOS::restype(n,t);
  }
}
