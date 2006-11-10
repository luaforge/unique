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

namespace undata{
  /*
   *  PATH
   */
  string PATH::cnstr() const{
    string r;
    for(int i=0;i<path.size();i++){
      r+=path[i]; if(i+1<path.size())r+="/";
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
  PATH::operator string()const{return cnstr();}
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
  void PATHS::parse(vector<PATH>& e, string s){
    e.clear();
    int i=0,t=0;
    for(;i<s.length();t=i+1){
      i=min(s.find(":",t),s.find(";",t));
      if(i!=t)e.push_back(PATH(s.substr(t,i-t)));
    }
  }
  string PATHS::cnstr(vector<PATH>& e){
    string r;
    for(int i=0;i<e.size();i++){
      r+=e[i]();
      if(i+1<e.size())r+=";";
    }
    return r;
  }
  PATHS::PATHS(){}
  PATHS::~PATHS(){}
  void PATHS::operator()(string&k/**="" asnil**/, string&v){
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
      v=cnstr(i->second);
    }
  }
  void PATHS::operator()(string&k/**="" asnil**/, vector<PATH>&v){
    ITER i=cont.begin();
    if(k!=""){
      i=cont.find(k);
      if(i!=cont.end())i++;
    }
    if(i==cont.end()){
      k="";
      v=empty;
    }else{
      k=i->first;
      v=i->second;
    }
  }
  vector<PATH>& PATHS::operator[](string k){
    if(cont.find(k)!=cont.end())return cont[k];
    return empty;
  }
  PATHS::operator string(){
    string r="PATHS{";
    int t=r.length();
    for(ITER i=cont.begin();i!=cont.end();i++){
      r+=i->first+"=";
      //for(int j=0;j<i->second.size();j++)r+=static_cast<string>(i->second[j])+";";
      r+=cnstr(i->second);
      r+=",";
    }
    if(r.length()>t)r.erase(r.length()-1);
    r+="}";
    return r;
  }
  void PATHS::set(string k, string p){
    if(k=="")return;
    if(p.length()){
      parse(cont[k],p);
    }else{
      cont.erase(k);
    }
  }
  string PATHS::get(string k){
    if(k=="")return "";
    if(cont.find(k)!=cont.end()){
      return cnstr(cont[k]);
    }
    return "";
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
    path.set("def","?");
  }
  REPOS::~REPOS(){
  }
  PATH REPOS::makepath(string n, string t){
    /*
    string e=ext.get(t)!=""?ext[t]:ext["def"];
    string r;
    int i,b=0;
    for(i=0;(i=e.find("?",b))<e.length();i++,b=i){
      r+=e.substr(b,i-b);
      r+=n;
    }
    r+=e.substr(b);
    PATH p=path.get(t)?path[t]:path["def"];
    */
    //return p|r;
  }
  RESOURCE REPOS::resource(string name, string spec){
    
  }
  void REPOS::stream(STREAM& s){
    
  }
  STREAM& REPOS::stream(RESOURCE& r){
    
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
    cont[name]->name=name;
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
  REPOS* REPOSS::get(string name){
    if(cont.find(name)!=cont.end())return cont[name];
    return NULL;
  }
  void REPOSS::set(string name, REPOS* repos){
    if(repos){
      repos->name=name;
      cont[name]=repos;
    }else{
      if(cont.find(name)!=cont.end())cont.erase(name);
    }
  }
  /*
   *  DATA
   */
  REPOSS repos; // repositories
  PATHS  path;  // pathes
  
  STREAM& RESOURCE::stream(STREAM::MODE mode){
    if(repos)return repos->stream(*this);
  }
  /*
  CATALOG& RESOURCE::catalog(){
    return CATALOG();
    }*/

  RESOURCE resource(string name, string spec, string repos){
    if(repos==""){ // Examine all repositoryes
      string n;
      REPOS* r;
      for(undata::repos(n,r);n!="";undata::repos(n,r)){
	if(r){
	  RESOURCE s=r->resource(name,spec);
	  if(s.type!=RESOURCE::non)return s;
	}
      }
    }else{ // Geting from `repos` repository
      REPOS* r=undata::repos.get(repos);
      if(r)return r->resource(name,spec);
    }
    return RESOURCE(name,spec,NULL);
  }
}
