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

# define ENUMVALSTR(re,name,cs) {		\
    string&__ret=re;				\
    __ret+=#name; __ret+="=";			\
    switch(name){				\
      cs;					\
    default: __ret+="<incorrect value>";	\
    }						\
  }
# define ENUMCASESTR(cs) case cs: __ret+=#cs; break;

namespace undata{
  /*
   *  PATH
   */
  string PATH::cnstr()const{
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
  PATH PATH::operator|(PATH&_n)const{
    PATH r;
    r.path=path;
    for(int i=0;i<~_n;i++)if(_n[i].length()>0)r.path.push_back(_n[i]);
    return r;
  }
  PATH PATH::operator|(string _n)const{PATH _p(_n); return (*this)|_p;}
  string PATH::operator()()const{return cnstr();}
  void PATH::operator()(string _n){parse(_n);}
  PATH PATH::apply(string _n)const{
    string r=cnstr();
    int i=0;
    for(;(i=r.find("?"))<r.length();i++)r=r.substr(0,i)+_n+r.substr(i+1);
    return PATH(r);
  }
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
  vector<PATH> PATHS::empty;
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
  RESOURCE::TYPE REPOS::restype(PATH p){
    return RESOURCE::non;
  }
  STREAM::MODE REPOS::resmode(PATH path){
    return STREAM::no;
  }
  string REPOS::makename(string n){
    for(int i=0;n[i]=='.';n[i]='/',i++);
    return n;
  }
  // n=="path.to.stream"   - path to stream
  // n=="path.to.catalog." - path to catalog
  RESOURCE REPOS::resource(string n, string s){
    if(n.length()<=0)return RESOURCE();
    RESOURCE::TYPE g=n[n.length()-1]=='.'?RESOURCE::dir:RESOURCE::stm;
    n=makename(n);
    if(path.get(s)=="")s="def";
    vector<PATH>& ps=path[s];
    for(int i=0;i<ps.size();i++){
      PATH p=ps[i].apply(n);
      RESOURCE::TYPE t=restype(p);
      if(t==RESOURCE::non)continue;
      STREAM::MODE a=resmode(p);
      return RESOURCE(n,s,this,p,t,a);
    }
    return RESOURCE();
  }
  STREAM& REPOS::stream(RESOURCE& r, STREAM::MODE m){
    if(r.type==RESOURCE::non)return empty;
    STREAM* s=stream(r.path,m);
    if(!s)return empty;
    ostm[s]=r.name;
    return *s;
  }
  void REPOS::stream(STREAM& s){
    if(ostm.find(&s)==ostm.end())return;
    ostm.erase(&s);
    if(&s)delete &s;
  }
  REPOS::operator string(){
    string r="REPOS{";
    r+=string("location=\"")+location+"\",";
    r+=string("stream={");
    int b=r.length();
    for(OPNSTMSITER i=ostm.begin();i!=ostm.end();i++){
      r+=string("[")+i->first+"]=\""+static_cast<string>(i->second)+"\",";
    }
    if(r.length()>b)r.erase(r.length()-1);
    r+="}}";
    return r;
  }
  STREAM REPOS::empty;
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
      r+=i->first+"="+static_cast<string>(*(i->second))+",";
    }
    if(r.length()>1)r.erase(r.length()-1);
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
  /*
  CATALOG& RESOURCE::catalog(){
    return CATALOG();
    }*/
  /*
   *  STREAM
   */
  STREAM::STREAM():repos(NULL),__rcount(0),__wcount(0){}
  STREAM::STREAM(REPOS* r):repos(r){}
  STREAM::~STREAM(){}
  string STREAM::__content(){
    string r;
    {
      char*b=new char[__length+1];
      __read(b,__length);
      b[__length]='\0';
      r=b;
    }
    return r;
  }
  void STREAM::__content(string chunk){
    __write((void*)chunk.data(),chunk.length());
  }
  STREAM::operator string(){
    string r="STREAM{name=\""; r+=name; r+="\",path="; r+=static_cast<string>(path); r+=",";
    ENUMVALSTR(r,mode,
	       ENUMCASESTR(STREAM::no)
	       ENUMCASESTR(STREAM::inp)
	       ENUMCASESTR(STREAM::out)
	       ENUMCASESTR(STREAM::io)
	       ); r+=",";
    r+="length="; r+=length();
    r+="}";
    return r;
  }
  /*
   *  RESOURCE
   */
  STREAM& RESOURCE::stream(STREAM::MODE m){
    if(m&access&&repos)return repos->stream(*this,m);
    return REPOS::empty;
  }
  void RESOURCE::stream(STREAM& stm){
    if(repos&&repos==stm.repos)repos->stream(stm);
  }
  RESOURCE::operator string(){
      string r="RESOURCE{";
      r+="name=\""; r+=name; r+="\",";
      r+="spec=\""; r+=spec; r+="\",";
      r+="path=\""; r+=static_cast<string>(path); r+="\",";
      ENUMVALSTR(r,access,
		 ENUMCASESTR(STREAM::no)
		 ENUMCASESTR(STREAM::inp)
		 ENUMCASESTR(STREAM::out)
		 ENUMCASESTR(STREAM::io)
		 ); r+=",";
      ENUMVALSTR(r,type,
		 ENUMCASESTR(RESOURCE::non)
		 ENUMCASESTR(RESOURCE::stm)
		 ENUMCASESTR(RESOURCE::dir)
		 ENUMCASESTR(RESOURCE::lnk)
		 ); r+=",";
      r+="repos=";  if(repos)r+=static_cast<string>(*repos);else r+="nil";
      r+="}";
      return r;
    }
  RESOURCE resource(string name, string spec, string repos){
    if(repos==""){ // Examine all repositoryes
      string n;
      REPOS* r;
      for(undata::repos(n,r);n!="";undata::repos(n,r)){
	if(r){
	  //cout<<"::::::: name="<<name<<"  spec="<<spec<<"  repos="<<n<<endl;
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
