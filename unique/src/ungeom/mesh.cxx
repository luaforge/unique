/***************************************************************************
 *            meshgeom.cpp
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

#include"mesh.hxx"
namespace ungeom{
  using namespace unogl;
  /*
   *  Mesh object
   */
# ifndef DEFAULT_VBO_ENABLE
#   define DEFAULT_VBO_ENABLE false // VertexBufferObject GPU rendering
# endif
  bool MESH::VBO=DEFAULT_VBO_ENABLE;
  MESH::MESH():unobj::OBJECT(){
    //glGetIntegerv(GL_MAX_VERTEX_ATTRIBS,&maxvertexattribs);
  }
  MESH::~MESH(){}
  bool MESH::update(){
    OBJECT::update();
    if(osrc!=src){
      osrc=src;
      undata::RESOURCE r=undata::resource(name,"meshdata");
      if(r.type==undata::RESOURCE::stm && r.access&undata::STREAM::inp){
	undata::STREAM& s=r.stream();
	if(LOADER::load(*this,s)){// if loaded ok
	  r.stream(s);
	  state=unbase::STATE(true,string("Mesh \"")+src+"\" loaded...");
	  return true;
	}
	r.stream(s);
	state=unbase::STATE(false,string("Mesh \"")+src+"\" not loaded...");
	return false;
      }
    }
    return false;
  }
  void MESH::draw_geom(const unobj::MODE&m){
    for(unsigned int s=0;s<surface.size();s++){
      if(surface[s])surface[s]->draw();
    }
  }
  /*
  void MESH::casteshadow(const vec3& lp){
    BindLoc();
    mat4 model_view;
    glGetFloatv(GL_MODELVIEW_MATRIX,model_view);
    vec3 lpos=model_view.inv()*lp;
    if(shadow)if(data)for(unsigned int s=0;s<data->surface.size();s++)
			data->surface[s].casteshadow(lpos);
    uBindLoc();
  }
  */
  unsigned int MESH::operator~(){
    return surface.size();
  }
  void MESH::operator()(int&k,ungeom::SURFACE*&n){
    if(k>=0){ if(k<surface.size())k++; }else k=0;
    if(k==surface.size()){ k=-1; n=NULL; }else{ n=surface[k]; }
  }
  ungeom::SURFACE* MESH::get(int k){
    if(k>=0&&k<surface.size())return surface[k];else return NULL;
  }
  MESH::operator string(){return string("MESH(\"")+src+"\")";}
  
  /*
   *  Mesh chunk
   */
  CHUNK::CHUNK():id(0),lim(0),data(NULL){}
  CHUNK::~CHUNK(){}
  void CHUNK::init(){
    if(!lim){
      lim=format*compon*size;
      data=new char[lim];
      offset=data;
    }
  }
  void CHUNK::dest(){
    if(lim){
      delete[](char*)data;
      lim=0;
    }
  }
  /*
   *  Aux functions
   */
  unsigned int GLIndexType(unsigned char format){// ��������� ��� ����� ��������
    switch(format){
    case 1: return GL_UNSIGNED_BYTE;
    case 2: return GL_UNSIGNED_SHORT;
    case 4: return GL_UNSIGNED_INT;
    }
  }
  unsigned int GLDrawPrim(unsigned char compon){// ��������� ��� �������������� ����������
    switch(compon){
    case 1: return GL_POINTS;
    case 2: return GL_LINES;
    case 3: return GL_TRIANGLES;
    case 4: return GL_QUADS;
    }
  }
  unsigned int GLIndex2uint(void* data, unsigned char node){
    unsigned int res=0,i;
    for(i=0;i<node;i++)((char*)&res)[i]=((char*)data)[i];
    return res;
  }

  /*
   *  Mesh surface
   */
  /*
    vec3* verts=((vec3*)blok[b_verts].data);
    vec3 beg,end;
    for(GLuint i=0;i<blok[b_verts].size;i++){
    beg=verts[i].len()<beg.len()?verts[i]:beg;
    end=verts[i].len()>end.len()?verts[i]:end;
    }
    boundbox=end-beg;
    boundsphere=boundbox.len()*0.5;
  */
  
  void SURFACE::operator()(int&k,ungeom::CHUNK*&n){
    if(k>=0){ if(k<attrib.size())k++; }else k=0;
    if(k>=attrib.size()){ k=-1; n=NULL; }else{ n=attrib[k]; }
  }
  CHUNK* SURFACE::get(int k){
    if(k>=0&&k<attrib.size())return attrib[k];else return NULL;
  }
  unsigned int SURFACE::operator~(){return attrib.size();}
  
  SURFACE::SURFACE():mat(NULL){}
  SURFACE::~SURFACE(){dest();}
  void SURFACE::init(){
# ifdef MESH_TEST_MODE1
    for(vector<CHUNK*>::iterator i=attrib.begin();i!=attrib.end();i++)if(*i){
	CHUNK& chunk=*(*i);
	cout<<"chunk( type:"<<int(chunk.type)<<endl;
	if(chunk.compon==2){
	  vec2* data=(vec2*)chunk.data;
	  for(int k=0;k<chunk.size;k++)cout<<data[k]<<endl;
	}
	if(chunk.compon==3){
	  vec3* data=(vec3*)chunk.data;
	  for(int k=0;k<chunk.size;k++)cout<<data[k]<<endl;
	}
      }
# endif
    calc_normal();
    calc_tangent();
    calc_coincidedvertexes();
    calc_againsttriangles();
    calc_openedges();
    GLuint type;
    if(MESH::VBO){
      for(vector<CHUNK*>::iterator i=attrib.begin();i!=attrib.end();i++){
	if(*i){
	  CHUNK&chunk=*(*i);
	  if(chunk.type==CHUNK::element)type=GL_ELEMENT_ARRAY_BUFFER;
	  else type=GL_ARRAY_BUFFER;
	  glGenBuffers(1,&chunk.glid);
	  glBindBuffer(type,chunk.glid);
	  glBufferData(type,chunk.lim,chunk.data,GL_STATIC_DRAW);
	  glBindBuffer(type,0);
	  //delete[](char*)(chunk.data);
	  chunk.offset=NULL;
	  OGL_DEBUG();
	}
      }
    }
  }
  CHUNK* SURFACE::findattrib(char type){
    for(int i=0;i<attrib.size();i++)
      if(attrib[i])
	if(attrib[i]->type==type)
	  return attrib[i];
    return NULL;
  }
  void SURFACE::dest(){
    if(MESH::VBO)
      for(int i=0;i<attrib.size();i++)
	if(attrib[i])
	  glDeleteBuffers(1,&(attrib[i]->glid));
  }
  
  void SURFACE::calc_coincidedvertexes(){
    CHUNK*chunk=findattrib(CHUNK::vertex);
    if(!chunk)return;
    coincidedvertex.clear();
    CHUNK&cvertex=*chunk;
    vec3  *pvertex=(vec3*)cvertex.data;
    for(unsigned int i=0;i<cvertex.size;i++){
      bool f=true;
      for(unsigned int j=0;j<coincidedvertex.size();j++){
	if(pvertex[coincidedvertex[j][0]]==pvertex[i]){
	  coincidedvertex[j].push_back(i);
	  f=false;
	  break;
	}
      }
      if(f){
	coincidedvertex.push_back(vector<unsigned int>());
	coincidedvertex.back().push_back(i);
      }
    }
# ifdef MESH_TEST_MODE
    {
      for(unsigned int i=0;i<coincidedvertex.size();i++){
	cout<<"Coincided vertexes ["<<i<<"] = {";
	for(unsigned int j=0;j<coincidedvertex[i].size();j++){
	  cout<<coincidedvertex[i][j]<<", ";
	}
	cout<<"};"<<endl;
      }
    }
# endif
  }

  void SURFACE::calc_againsttriangles(){
    if(coincidedvertex.empty())calc_coincidedvertexes();
    if(coincidedvertex.empty())return;
    CHUNK*chunk=findattrib(CHUNK::vertex);
    if(!chunk)return;
    CHUNK&cvertex=*chunk;
    vec3  *pvertex=(vec3*)cvertex.data;
    againsttriangle.clear();
    for(unsigned int i=0;i<cvertex.size;i+=3){
      againsttriangle.push_back(AGAINSTTRIANGLE());
      unsigned int t0=trinum(i);
      unsigned int j[3],k;
      for(k=0;k<3;k++){
	for(j[k]=0;j[k]<coincidedvertex.size();j[k]++){
	  if(pvertex[coincidedvertex[j[k]][0]]==pvertex[i+k])break;
	}
      }
      for(k=0;k<3;k++){
	bool p=true;
	unsigned int n1=j[trinex(k,0)],n2=j[trinex(k,1)];
	for(unsigned int m1=0;m1<coincidedvertex[n1].size()&&p;m1++){
	  unsigned int t1=trinum(coincidedvertex[n1][m1]);
	  for(unsigned int m2=0;m2<coincidedvertex[n2].size()&&p;m2++){
	    unsigned int t2=trinum(coincidedvertex[n2][m2]);
	    if(t1==t2&&t1!=t0){
	      againsttriangle.back()[k]=t1;
	      p=false;
	    }
	  }
	}
	if(p){
	  againsttriangle.back()[k]=outindex;
	}
      }
    }
# ifdef MESH_TEST_MODE
    {
      for(unsigned int i=0;i<againsttriangle.size();i++){
	cout<<"Against triangle ["<<i<<"] = {";
	for(unsigned int k=0;k<3;k++){
	  cout<<againsttriangle[i][k]<<",";
	}
	cout<<"};"<<endl;
      }
    }
# endif
  }

  void SURFACE::calc_openedges(){
    if(againsttriangle.empty())calc_againsttriangles();
    if(againsttriangle.empty())return;
    openedge.clear();
    for(unsigned int i=0;i<againsttriangle.size();i++){
      for(char k=0;k<3;k++){
	if(againsttriangle[i][k]==outindex){
	  openedge.push_back(OPENEDGE(i,k));
	}
      }
    }
# ifdef MESH_TEST_MODE
    {
      if(openedge.empty()){
	cout<<"No open edges"<<endl;
      }else{
	for(unsigned int i=0;i<openedge.size();i++){
	  cout<<"Open edge ["<<i<<"] = {";
	  cout<<" triangle="<<openedge[i].t<<", edge="<<(unsigned int)openedge[i].e<<"";
	  cout<<"};"<<endl;
	}
      }
    }
# endif
  }

  void SURFACE::calc_normal(){
    // Detect normal chunk
    CHUNK*chunk=findattrib(CHUNK::normal);
    if(chunk)return;
    chunk=findattrib(CHUNK::vertex);
    if(!chunk)return;
    CHUNK&cvertex=*chunk;
    // Insert normal chunk
    attrib.push_back(new CHUNK());
    CHUNK&cnormal=*attrib.back();
    cnormal.id    =cvertex.id;
    cnormal.format=4;
    cnormal.compon=3;
    cnormal.size  =cvertex.size;
    cnormal.type  =CHUNK::normal;
    cnormal.init();
    // Calculate normals
    vec3*pvertex  =(vec3*)cvertex.data;
    vec3*pnormal  =(vec3*)cnormal.data;
    if(smooth){
      vector<vector<unsigned int> > vertmap; // Vertex map
      /*
       *         .::: VERTEX MAP \\ CONTENTS :::.
       *
       *          v e r t e x
       *          u n i q u e
       *          i n d e x e s
       *          _______________________________________\
       *  v u c  |              _0_1_2__3___4_______     /
       *  e n o  | vec3(1,2,3) | 1 4 7 19 201 ....
       *  r i o  |    .....    |
       *  t q r  |             |
       *  e u d  |             |
       *  x e s \ /
       *
       */
      // Generating vertex map
      for(unsigned int i=0;i<cvertex.size;i++){ // per vertex
	// If i exist in vertex unique indexes =>
	// Insert i into exist unique cortage and continue
	bool exist=false;
	unsigned int viuc=0;
	for(unsigned int iuc=0;iuc<vertmap.size() && !exist;iuc++){
	  vector<unsigned int>&uc=vertmap[iuc];
	  for(unsigned int iui=0;iui<uc.size() && !exist;iui++){
	    if(pvertex[i]==pvertex[uc[iui]]){
	      exist=true;
	      viuc=iuc;
	    }
	  }
	}
	if(exist){
	  vertmap[viuc].push_back(i);
	  continue;
	}
	// Else => Create new unique indices cortage and
	// Insert vertex unique indexes into it
	vertmap.push_back(vector<unsigned int>());
	vertmap.back().push_back(i);
      }
      // Calculate smooth normals
      /*         6     5_            1. Illiminate vertex (find it's index
       *         /\    /                in triangle) Formula: pi=vi%3
       *       1/  \ 2/
       *    __\/____\/____/8         2. Get face direct vectors (as example
       *      /\    /\    \             v5-v2, v8-v2, v6-v2, v3-v2, v4-v2)
       *        \  /  \
       *       __\/____\/___         3. Calculate triangle normals (as cross)
       *         /\    /\
       *        / 3     4            4. Calculate smooth normal    (as dot)
       */
      for(unsigned int iuc=0;iuc<vertmap.size();iuc++){
	vector<unsigned int>&uc=vertmap[iuc];
	vec3&normal=pnormal[uc[0]]; // get link for first vertex
	deque<vec3> fv;
	// Calculate triangle normals for all triangles
	for(unsigned int iui=0;iui<uc.size();iui++){
	  unsigned int ui=uc[iui];
	  char pi=ui%3; // illiminate
	  unsigned int si[3];
	  si[0]=ui/3;
	  si[1]=si[0]+(pi<2)?pi+1:0;
	  si[2]=si[0]+(pi<1)?pi+2:1;
	  fv.push_back((pvertex[si[1]]-pvertex[si[0]])^(pvertex[si[2]]-pvertex[si[0]]));
	}
	// Dot product for all triangle normals
	normal=fv[0];
	for(unsigned int vi=1;vi<fv.size();vi++){
	  normal*=fv[vi];
	}
	// Set normal for all other vertexes
	for(unsigned int iui=1;iui<uc.size();iui++){
	  pnormal[uc[iui]]=normal;
	}
      }
    }else{
      for(unsigned int i=0;i<cnormal.size;i+=3){ // per triangle
	vec3&normal=pnormal[i];
	normal=(pvertex[i+1]-pvertex[i+0])^(pvertex[i+2]-pvertex[i+1]);
	normal.norm();
	pnormal[i+1]=normal; pnormal[i+2]=normal;
      }
    }
  }

  void SURFACE::calc_tangent(){
    // Detect vertex chunk
    CHUNK*chunk=findattrib(CHUNK::vertex);
    if(!chunk)return;
    CHUNK&cvertex=*chunk;
    // Detect texture coord chunk
    chunk=findattrib(CHUNK::texcoord);
    if(!chunk)return;
    CHUNK&ctexture=*chunk;
    // Detect normal chunk
    chunk=findattrib(CHUNK::normal);
    if(!chunk)calc_normal();// If not exist, auto generate
    // Get normal chunk
    CHUNK&cnormal=*chunk;
    // Insert binormal chunk
    attrib.push_back(new CHUNK());
    CHUNK&cbinormal=*attrib.back();
    cbinormal.id    =cnormal.id;
    cbinormal.format=cnormal.format;
    cbinormal.compon=cnormal.compon;
    cbinormal.size  =cnormal.size;
    cbinormal.type  =CHUNK::binormal;
    cbinormal.init();
    // Insert tangent chunk
    attrib.push_back(new CHUNK());
    CHUNK&ctangent=*attrib.back();
    ctangent.id    =cnormal.id;
    ctangent.format=cnormal.format;
    ctangent.compon=cnormal.compon;
    ctangent.size  =cnormal.size;
    ctangent.type  =CHUNK::tangent;
    ctangent.init();
    // Typefied pointers to data
    vec3*pvertex  =(vec3*)cvertex.data;
    vec2*ptexture =(vec2*)ctexture.data;
    vec3*pnormal  =(vec3*)cnormal.data;
    vec3*pbinormal=(vec3*)cbinormal.data;
    vec3*ptangent =(vec3*)ctangent.data;
    // Calculate normals and binormals
    for(unsigned int i=0;i<cvertex.size;i++){
      // get link
      vec3&normal=pnormal[i];
      vec3&binormal=pbinormal[i];
      vec3&tangent=ptangent[i];
      // Find plane coord basis
      unsigned int vi[3]; // surface related vertex indexes, [0] - current
      unsigned int bi=(i/3)*3;
      char pi[3]; // polygon related vertex indexes
      pi[0]=i%3;
      pi[1]=tridex(pi[0],1);
      pi[2]=tridex(pi[0],0);
      vi[0]=bi+pi[0];
      vi[1]=bi+pi[1];
      vi[2]=bi+pi[2];
      vec3 vab=pvertex[vi[1]]-pvertex[vi[0]];
      vec3 vac=pvertex[vi[2]]-pvertex[vi[0]];
      // tu and tv texture coordinate differences
      vec3 dab=ptexture[vi[1]]-ptexture[vi[0]];
      vec3 dac=ptexture[vi[2]]-ptexture[vi[0]];
      if(dac.u*dab.v>dab.u*dac.v){dac.u=-dac.u; dab.u=-dab.u;}
      // Components of vectors to neghboring vertices that are orthogonal to the
      // vertex normal
      vec3 pab=vab-(normal*vab)*normal;
      vec3 pac=vac-(normal*vac)*normal;
      // Calculate tangent
      tangent=dac.u*pab-dab.u*pac;
      tangent.norm();
      binormal=tangent^normal;
      binormal.norm();
    }
  }

  vector<unsigned int>& SURFACE::coincidedvertexes(vec3 v){
    // Detect vertex chunk
    CHUNK*chunk=findattrib(CHUNK::vertex);
    if(!chunk)return nocoincidedvertex;
    vec3*pvertex=(vec3*)chunk->data;
    for(unsigned int i=0;i<coincidedvertex.size();i++)if(pvertex[coincidedvertex[i][0]]==v)return coincidedvertex[i];
    return nocoincidedvertex;
  }

  void SURFACE::draw(){
    glPushClientAttrib(GL_CLIENT_VERTEX_ARRAY_BIT);
    glEnable(GL_DEPTH_TEST);
    //glDisable(GL_BLEND);
    glDepthFunc(GL_LESS);
  
    glPolygonMode(GL_FRONT,GL_FILL);
    glPolygonMode(GL_BACK,GL_LINE);
    glEdgeFlag(GL_FALSE);

    CHUNK* face=NULL;
    CHUNK* vert=NULL;
    for(int i=0;i<attrib.size();i++)if(attrib[i]->lim){
	CHUNK& chunk=*attrib[i];
	switch(chunk.type){
	case CHUNK::vertex: // Vertex array
	  vert=&chunk;
	  glEnableClientState(GL_VERTEX_ARRAY);
	  if(MESH::VBO)glBindBuffer(GL_ARRAY_BUFFER,chunk.glid);
	  glVertexPointer(chunk.compon,GL_FLOAT,0,chunk.offset);
	  break;
	case CHUNK::normal: // Normal array
	  glEnableClientState(GL_NORMAL_ARRAY);
	  if(MESH::VBO)glBindBuffer(GL_ARRAY_BUFFER,chunk.glid);
	  glNormalPointer(GL_FLOAT,0,chunk.offset);
	  // As Attrib array
	  glEnableVertexAttribArray(14);
	  if(MESH::VBO)glBindBuffer(GL_ARRAY_BUFFER,chunk.glid);
	  glVertexAttribPointer(14,chunk.compon,GL_FLOAT,GL_FALSE,0,chunk.offset);
	  break;
	case CHUNK::texcoord: // Texture coords array
	  glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	  if(MESH::VBO)glBindBuffer(GL_ARRAY_BUFFER,chunk.glid);
	  glTexCoordPointer(chunk.compon,GL_FLOAT,0,chunk.offset);
	  break;
	case CHUNK::element: // Faces array
	  face=&chunk;
	  if(MESH::VBO){ // Assign element buffer
	    glEnableClientState(GL_INDEX_ARRAY);
	    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,chunk.glid);
	    glIndexPointer(GL_INT,0,chunk.offset);
	  }
	  break;
	case CHUNK::binormal: // Binormals array as vertex attrib
	  glEnableVertexAttribArray(13);
	  if(MESH::VBO)glBindBuffer(GL_ARRAY_BUFFER,chunk.glid);
	  glVertexAttribPointer(13,chunk.compon,GL_FLOAT,GL_FALSE,0,chunk.offset);
	  break;
	case CHUNK::tangent: // Tangents array as vertex attrib
	  glEnableVertexAttribArray(12);
	  if(MESH::VBO)glBindBuffer(GL_ARRAY_BUFFER,chunk.glid);
	  glVertexAttribPointer(12,chunk.compon,GL_FLOAT,GL_FALSE,0,chunk.offset);
	  break;
	}
	OGL_DEBUG();
      }
    if(vert){
      if(face)glDrawElements(GLDrawPrim(face->compon),face->compon*face->size,
			     GLIndexType(face->format),face->data);
      else glDrawArrays(GL_TRIANGLES,0,vert->size);
    }
    OGL_DEBUG();

    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    for(unsigned int vai=0;vai<2;vai++)glDisableVertexAttribArray(vai);
    if(MESH::VBO){ // Close element's buffer
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
      glDisableClientState(GL_INDEX_ARRAY);
    }
    OGL_DEBUG();
    glPopClientAttrib();
  }
  /*
  void SURFACE::casteshadow(const vec3& lp){
    CHUNK* v=findattrib(CHUNK::vertex);
    if(v){
      unmath::POLYGON* p=(unmath::POLYGON*)v->data;
      unsigned int s=v->size/3;
      bool f[s];
      for(unsigned int i=0;i<s;i++)
	f[i]=p[i].where(lp)==POLYGON::FRONT;
      // first pass
      glFrontFace(GL_CCW);
      glStencilOp(GL_KEEP,GL_KEEP,GL_INCR);
      vec3 g[12];
      glEnableClientState(GL_VERTEX_ARRAY);
      for(unsigned int i=0;i<s;i++)if(f[i]){
	  p[i].shadow(g,lp,100);
	  glVertexPointer(3,GL_FLOAT,0,g);
	  for(char j=0;j<3;j++)glDrawArrays(GL_TRIANGLE_STRIP,j*4,4);
	}
      // second pass
      glFrontFace(GL_CW);
      glStencilOp(GL_KEEP,GL_KEEP,GL_DECR);
      for(unsigned int i=0;i<s;i++)if(f[i]){
	  p[i].shadow(g,lp,100);
	  glVertexPointer(3,GL_FLOAT,0,g);
	  for(char j=0;j<3;j++)glDrawArrays(GL_TRIANGLE_STRIP,j*4,4);
	}
      glDisableClientState(GL_VERTEX_ARRAY);
    }
  }
  */
  
  /*
   *  Mesh loader
   */
  vector<LOADER::METHOD> LOADER::loader;
  LOADER::LOADER(){}
  LOADER::~LOADER(){}
  void LOADER::Register(LOADER::METHOD m){loader.push_back(m);}
  bool LOADER::load(MESH&m,undata::STREAM&s){
    init();
    LOADER l;
    for(ITER i=loader.begin();i!=loader.end();i++)if((*i)(l,s))break;
    if(l.state.state){
      l.gen(m);
      return true;
    }
    return false;
  }
    
  bool LOADER::gen(MESH&m){ // Gen Surfaces
    for(vector<CHUNK*>::iterator i=chunk.begin();i!=chunk.end();i++){// Find surface
      if((*i)->surf>=m.surface.size())m.surface.push_back(new SURFACE());// Make surface
      m.surface[(*i)->surf]->attrib.push_back(*i);
    }
    for(vector<SURFACE*>::iterator s=m.surface.begin();s!=m.surface.end();s++)(*s)->init();
    //cout<<"Surfaces: "<<surface.size()<<endl;
    //for(int k=0;k<surface.size();k++)cout<<"Surface: "<<k<<" attribs: "<<surface[k].attrib.size()<<" elements: "<<surface[k].attrib[0]->size<<" compon: "<<int(surface[k].attrib[0]->compon)<<endl;
    return true;
  }

#define MESH_LOADER(func) Register(func);
#include"mesh_loader_config.hxx"
  void LOADER::init(){
    if(loader.size()==0){MESH_LOADER_LIST}
  }
}
