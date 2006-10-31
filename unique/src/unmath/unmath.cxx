/***************************************************************************
 *            unmath.cpp
 *
 *  Wed Jun 29 17:12:37 2005
 *  Copyright  2005  Fenix
 *  tonder@trktvs.ru
 ***************************************************************************/

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

#include"unmath.hxx"

namespace unmath{

//vec2
const vec2 vec2::nul(0.0,0.0);
const vec2 vec2::null(0.0,0.0);
const vec2 vec2::one(1.0,1.0);
const vec2 vec2::px(1.0,0.0);
const vec2 vec2::py(0.0,1.0);
const vec2 vec2::nx(-1.0,0.0);
const vec2 vec2::ny(0.0,-1.0);
//vec3
const vec3 vec3::nul(0.0,0.0,0.0);
const vec3 vec3::null(0.0,0.0,0.0);
const vec3 vec3::one(1.0,1.0,1.0);
const vec3 vec3::px(1.0,0.0,0.0);
const vec3 vec3::py(0.0,1.0,0.0);
const vec3 vec3::pz(0.0,0.0,1.0);
const vec3 vec3::nx(-1.0,0.0,0.0);
const vec3 vec3::ny(0.0,-1.0,0.0);
const vec3 vec3::nz(0.0,0.0,-1.0);
const vec3 vec3::at(0.0,-1.0,0.0);
const vec3 vec3::dir(0.0,1.0,0.0);
const vec3 vec3::up(0.0,0.0,1.0);
//vec4
const vec4 vec4::null(0.0,0.0,0.0,0.0);
const vec4 vec4::nul(0.0,0.0,0.0,0.0);
const vec4 vec4::one(1.0,1.0,1.0,1.0);
const vec4 vec4::px(1.0,0.0,0.0,0.0);
const vec4 vec4::nx(-1.0,0.0,0.0,0.0);
const vec4 vec4::py(0.0,1.0,0.0,0.0);
const vec4 vec4::ny(0.0,-1.0,0.0,0.0);
const vec4 vec4::pz(0.0,0.0,1.0,0.0);
const vec4 vec4::nz(0.0,0.0,-1.0,0.0);
const vec4 vec4::pw(0.0,0.0,0.0,1.0);
const vec4 vec4::nw(0.0,0.0,0.0,-1.0);
//mat3
const mat3 mat3::null(array9_null);
const mat3 mat3::nul(array9_null);
const mat3 mat3::id(array9_id);
const mat3 mat3::one(array9_id);
//mat4
const mat4 mat4::one(array16_id);
const mat4 mat4::id(array16_id);
const mat4 mat4::null(array16_null);
const mat4 mat4::nul(array16_null);
const mat4 mat4::scale_bias(array16_scale_bias);
//quat
const quat quat::id(0.0,0.0,0.0,1.0);

#ifdef IOSTREAM_ENABLE
# ifndef TEXT_NL
#  define TEXT_NL "\n"
# endif
# ifndef TEXT_TB
#  define TEXT_TB "   "
# endif
# ifndef TEXT_COMA
#  define TEXT_COMA ", "
# endif
# ifndef TEXT_SQ_OPEN
#  define TEXT_SQ_OPEN "["
# endif
# ifndef TEXT_SQ_CLOSE
#  define TEXT_SQ_CLOSE "]"
# endif
std::ostream& operator<<(std::ostream& stm, vec2& v){
  return stm<<"vec2"<<TEXT_SQ_OPEN<<v.x<<TEXT_COMA<<v.y<<TEXT_SQ_CLOSE; }
std::ostream& operator<<(std::ostream& stm, vec3& v){
  return stm<<"vec3"<<TEXT_SQ_OPEN<<v.x<<TEXT_COMA<<v.y<<TEXT_COMA<<v.z<<TEXT_SQ_CLOSE; }
std::ostream& operator<<(std::ostream& stm, vec4& v){
  return stm<<"vec4"<<TEXT_SQ_OPEN<<v.x<<TEXT_COMA<<v.y<<TEXT_COMA<<v.z<<TEXT_COMA<<v.w<<TEXT_SQ_CLOSE; }
std::ostream& operator<<(std::ostream& stm, mat3& m){
  return stm<<"mat3"<<TEXT_SQ_OPEN<<m.a00<<TEXT_COMA<<m.a10<<TEXT_COMA<<m.a20<<TEXT_COMA<<TEXT_NL \
             <<TEXT_TB<<m.a01<<TEXT_COMA<<m.a11<<TEXT_COMA<<m.a21<<TEXT_COMA<<TEXT_NL \
             <<TEXT_TB<<m.a02<<TEXT_COMA<<m.a12<<TEXT_COMA<<m.a22<<TEXT_SQ_CLOSE; }
std::ostream& operator<<(std::ostream& stm, mat4& m){
  return stm<<"mat4"<<TEXT_SQ_OPEN<<m.a00<<TEXT_COMA<<m.a10<<TEXT_COMA<<m.a20<<TEXT_COMA<<m.a30<<TEXT_COMA<<TEXT_NL \
             <<TEXT_TB<<m.a01<<TEXT_COMA<<m.a11<<TEXT_COMA<<m.a21<<TEXT_COMA<<m.a31<<TEXT_COMA<<TEXT_NL \
             <<TEXT_TB<<m.a02<<TEXT_COMA<<m.a12<<TEXT_COMA<<m.a22<<TEXT_COMA<<m.a32<<TEXT_COMA<<TEXT_NL \
             <<TEXT_TB<<m.a03<<TEXT_COMA<<m.a13<<TEXT_COMA<<m.a23<<TEXT_COMA<<m.a33<<TEXT_SQ_CLOSE; }
std::ostream& operator<<(std::ostream& stm, quat& q){
  return stm<<"quat"<<TEXT_SQ_OPEN<<q.x<<TEXT_COMA<<q.y<<TEXT_COMA<<q.z<<TEXT_COMA<<q.w<<TEXT_SQ_CLOSE; }
#endif


vec2::operator string()const{ return string("vec2(")+x+","+y+")"; }
vec3::operator string()const{ return string("vec3(")+x+","+y+","+z+")"; }
vec4::operator string()const{ return string("vec4(")+x+","+y+","+z+","+w+")"; }
mat3::operator string()const{
  return string("mat3(")
    +a00+","+a10+","+a20+","+
    +a01+","+a11+","+a21+","+
    +a02+","+a12+","+a22+
    ")"; }
mat4::operator string()const{
  return string("mat4(")
    +a00+","+a10+","+a20+","+a30+","+
    +a01+","+a11+","+a21+","+a31+","+
    +a02+","+a12+","+a22+","+a32+","+
    +a03+","+a13+","+a23+","+a33+","+
    ")"; }
quat::operator string()const{ return string("quat(")+x+","+y+","+z+","+w+")"; }


const mat3 operator*(const scalar l, const mat3& M){ mat3 nM=M; nM*=l; return nM; }

void mat3::rotate(const quat &q){
  scalar x2=q.x* 2, y2=q.y* 2, z2=q.z* 2;
  scalar xx=q.x*x2, yy=q.y*y2, zz=q.z*z2;
  scalar xy=q.x*y2, yz=q.y*z2, xz=q.z*x2;
  scalar wx=q.w*x2, wy=q.w*y2, wz=q.w*z2;
  a00=1.0f-(yy+zz); a10=xy+wz;        a20=xz-wy;
  a01=xy-wz;        a11=1.0f-(xx+zz); a21=yz+wx;
  a02=xz+wy;        a12=yz-wx;        a22=1.0f-(xx+yy);
}

mat4::mat4(const quat& q){ this->rotate(q); }
mat4::mat4(const vec3& v){ this->translate(v); }

/*
vec3 mat3::at(){ return vec3(vec3_at)*(mat3&)(*this); }
vec3 mat3::up(){ return vec3(vec3_up)*(mat3&)(*this); }
vec3 mat3::dir(){ return vec3(vec3_dir)*(mat3&)(*this); }
*/
const vec3 vec3::operator*(const mat3& M)const{
  return vec3(M.a00*x+M.a10*y+M.a20*z,
	      M.a01*x+M.a11*y+M.a21*z,
	      M.a02*x+M.a12*y+M.a22*z);
}
const vec3 vec3::operator*(const mat4& M)const{
  return vec3(vec4(*this)*M);
}

const vec4 vec4::operator*(const mat4& M)const{
  return vec4(M.a00*x+M.a10*y+M.a20*z+M.a30*w,
	      M.a01*x+M.a11*y+M.a21*z+M.a31*w,
	      M.a02*x+M.a12*y+M.a22*z+M.a32*w,
	      M.a03*x+M.a13*y+M.a23*z+M.a33*w);
}

vec2 glfW2GL(vec2 p, vec2 wh){ // Convert window coords to opengl
  return vec2(2.0*p.x/wh.width-1.0, 1.0-2.0*p.y/wh.height);
}
vec2 glfGL2W(vec2 p, vec2 wh){ // Convert opengl coords to window
  return vec2(int((p.x+1.0)*0.5*wh.width),int((1.0-p.y)*0.5*wh.height));
}

// ‚’ƒ≈‘ ”ﬁ…‘¡‘ÿ FPU
mat4& fpu_look_at(mat4& M, const vec3& eye, const vec3& center, const vec3& up){
  vec3 x, y, z;
  // make rotation matrix
  // Z vector
  z.x=eye.x-center.x;
  z.y=eye.y-center.y;
  z.z=eye.z-center.z;
  z.norm();
  // Y vector
  y.x=up.x;
  y.y=up.y;
  y.z=up.z;
  // X vector=Y cross Z
  x=y^z;
  // Recompute Y=Z cross X
  y=z^x;
  // cross product gives area of parallelogram, which is < 1.0 for
  // non-perpendicular unit-length vectors; so normalize x, y here
  x.norm();
  y.norm();

  M.a00=x.x; M.a01=x.y; M.a02=x.z; M.a03=-x.x*eye.x-x.y*eye.y-x.z*eye.z;
  M.a10=y.x; M.a11=y.y; M.a12=y.z; M.a13=-y.x*eye.x-y.y*eye.y-y.z*eye.z;
  M.a20=z.x; M.a21=z.y; M.a22=z.z; M.a23=-z.x*eye.x-z.y*eye.y-z.z*eye.z;
  M.a30=0.0; M.a31=0.0; M.a32=0.0; M.a33=1.0;
  return M;
}

mat4& fpu_frustum(mat4& M, const scalar l, const scalar r, const scalar b, 
               const scalar t, const scalar n, const scalar f){
  M.a00=(2.0*n)/(r-l);
  M.a10=0.0;
  M.a20=0.0;
  M.a30=0.0;

  M.a01=0.0;
  M.a11=(2.0*n)/(t-b);
  M.a21=0.0;
  M.a31=0.0;

  M.a02=(r+l)/(r-l);
  M.a12=(t+b)/(t-b);
  M.a22=-(f+n)/(f-n);
  M.a32=-1.0;

  M.a03=0.0;
  M.a13=0.0;
  M.a23=-(2.0*f*n)/(f-n);
  M.a33=0.0;
  return M;
}

mat4& fpu_perspective(mat4& M, const scalar fovy, const scalar aspect, const scalar n, const scalar f){
  scalar xmin, xmax, ymin, ymax;

  ymax=n*tanf(fovy*cnst::to_rad*0.5);
  ymin=-ymax;

  xmin=ymin*aspect;
  xmax=ymax*aspect;

  return fpu_frustum(M, xmin, xmax, ymin, ymax, n, f);
}

mat4& fpu_ortho(mat4& M, const scalar l, const scalar r, // Û¡Õ ƒœ–…”¡Ã
             const scalar b, const scalar t, 
             const scalar n, const scalar f){
  scalar r_l=r-l;
  scalar t_b=t-b;
  scalar f_n=f-n;
  //˜ ‘¡ÀœÕ ◊…ƒ≈ ‹‘¡ ∆’ŒÀ√…— ‘œﬁŒœ ”œœ‘◊≈‘”‘◊’≈‘ GL-≈◊”Àœ 
  
  M.a00=2.0/r_l;
  M.a01=0.0;
  M.a02=0.0;
  M.a03 =-(r+l)/r_l; // ˙ƒ≈”ÿ, –œ …ƒ≈≈, Õ…Œ’” ƒœÃ÷≈Œ ¬Ÿ‘ÿ

  M.a10=0.0;
  M.a11=2.0/t_b;
  M.a12=0.0;
  M.a13 =-(t+b)/t_b; // ˙ƒ≈”ÿ, –œ …ƒ≈≈, Õ…Œ’” ƒœÃ÷≈Œ ¬Ÿ‘ÿ

  M.a20=0.0;
  M.a21=0.0;
  M.a22 =-2.0/f_n;
  M.a23 =-(f+n)/f_n; // ˙ƒ≈”ÿ, –œ …ƒ≈≈, Õ…Œ’” ƒœÃ÷≈Œ ¬Ÿ‘ÿ

  M.a30=0.0;
  M.a31=0.0;
  M.a32=0.0;
  M.a33=1.0; // Ìœ÷≈‘ ‘’‘ Õ…Œ’”, Œ≈ ⁄Œ¡¿, ◊ “¡⁄ŒŸ» Õ¡Œ’¡Ã¡» –œ“¡⁄ŒœÕ’.

  return M;
}

// ’”‘ÿ OpenGL ◊ GPU ”ﬁ…‘¡≈‘ … ◊œ⁄◊“¡›¡≈‘ “≈⁄’Ãÿ‘¡‘ Œ¡Õ!
#ifdef COMPILE_GLMATRIXOP
#include "../seogl.h"

mat4& gpu_look_at(mat4& M, const vec3& eye, const vec3& center, const vec3& up){
  GLint mode;
  glGetIntegerv(GL_MATRIX_MODE,&mode);
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();

  glLoadIdentity();
  gluLookAt(eye.x,eye.y,eye.z,center.x,center.y,center.z,up.x,up.y,up.z);
  glGetFloatv(GL_PROJECTION_MATRIX,M.array);
  
  glPopMatrix();
  glMatrixMode(mode);
  return M;
}

mat4& gpu_frustum(mat4& M, const scalar l, const scalar r, const scalar b, 
         const scalar t, const scalar n, const scalar f){
  GLint mode;
  glGetIntegerv(GL_MATRIX_MODE,&mode);
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();

  glLoadIdentity();
  glFrustum(l,r,b,t,n,f);
  glGetFloatv(GL_PROJECTION_MATRIX,M.array);
  
  glPopMatrix();
  glMatrixMode(mode);
  return M;
}
mat4& gpu_perspective(mat4& M, const scalar fovy, const scalar aspect, const scalar n, const scalar f){
  GLint mode;
  glGetIntegerv(GL_MATRIX_MODE,&mode);
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();

  glLoadIdentity();
  gluPerspective(fovy,aspect,n,f);
  glGetFloatv(GL_PROJECTION_MATRIX,M.array);
  
  glPopMatrix();
  glMatrixMode(mode);
  return M;
}
mat4& gpu_ortho(mat4& M, const scalar l, const scalar r, // Û¡Õ ƒœ–…”¡Ã
             const scalar b, const scalar t, 
             const scalar n, const scalar f){
  GLint mode;
  glGetIntegerv(GL_MATRIX_MODE,&mode);
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();

  glLoadIdentity();
  glOrtho(l,r,b,t,n,f);
  glGetFloatv(GL_PROJECTION_MATRIX,M.array);
  
  glPopMatrix();
  glMatrixMode(mode);
  return M;
}
#endif

#ifndef acosf
#define acosf acos
#endif

void mat4::rotate(const quat& q){rotate(mat3(q));}

// Project an x,y pair onto a sphere of radius r OR a hyperbolic sheet
// if we are away from the center of the sphere.
scalar tb_project_to_sphere(scalar r, scalar x, scalar y){
  scalar d,t,z;
  d=sqrtf(x*x+y*y);
  if(d<r*cnst::one_sqrt_half){ // Inside sphere
    z=sqrtf(r*r-d*d);
  }else{ // On hyperbola
    t=r/(scalar)cnst::two_sqrt_half;
    z=t*t/d;
  }
  return z;
}

quat euler_2_quat(vec3 e){
  e*=0.5; return quat(sin(e.a),0,0,cos(e.a))*quat(0,sin(e.b),0,cos(e.b))*quat(0,0,sin(e.c),cos(e.c));
}

quat sph_2_quat(vec3 s){
  return quat();
}

TRIANGLE::TRIANGLE(){}
TRIANGLE::TRIANGLE(const vec3& _a,const vec3& _b,const vec3& _c){v[0]=_a;v[1]=_b;v[2]=_c;}
TRIANGLE::~TRIANGLE(){}

char TRIANGLE::where(const vec3& p){
  scalar factor=(p-v[0])*((v[1]-v[0])^(v[2]-v[0]));
  if(factor<-cnst::one_eps)return FRONT;
  if(factor> cnst::one_eps)return BACK;
  return ON;
}
char TRIANGLE::where(const TRIANGLE& p){
  char r=ON,s;
  for(char vi=0;vi<3;vi++){
    s=where(p.v[vi]);
    if(s!=FRONT && s!=ON)r=r&~FRONT;
    if(s!=BACK  && s!=ON)r=r&~BACK;
  }
  return r;
}

void TRIANGLE::shadow(vec3* lg,const vec3& lp,scalar lf){
  //if(where(lpos)&POLYGON::FRONT){
  for(char i=0;i<3;i++){
    char j=i>1?3-i-1:i+1,a=i*4; //,k=i>0?3-i-2:i+2;
    lg[0+a]=v[i];
    lg[1+a]=v[j];
    lg[2+a]=(lg[0+a]-lp)*lf+lg[0+a];
    lg[3+a]=(lg[1+a]-lp)*lf+lg[1+a];
  }
    //}
}

bool TRIANGLE::intersect(const vec3& p){
  vec3 n=normal();
  if(((v[1]-v[0])^(p-v[0]))*n<=0)return false;
  if(((v[2]-v[1])^(p-v[1]))*n<=0)return false;
  if(((v[0]-v[2])^(p-v[2]))*n<=0)return false;
  return true;
}
bool TRIANGLE::collision(vec3& p,const LINE& l){
  vec3 n=normal();
  scalar a=(l[0]-v[0])*n,b=(l[1]-v[0])*n;
  p=(l[0]+((l[1]-l[0])*(-a/(b-a))));
  return intersect(p);
}

/*********

Â”Ã… œ¬ﬂ≈À‘ ”√≈ŒŸ ”œ”‘œ…‘ …⁄ ‘“≈’«œÃÿŒ…Àœ◊, ‘œ ƒÃ— –“œ◊≈“À… –≈“≈”≈ﬁ≈Œ…— ‘“≈’«œÃÿŒ…À¡ ” ÛÔ Õœ÷Œœ ◊œ”–œÃÿ⁄œ◊¡‘ÿ”  ∆’ŒÀ√…≈ : 


bool intersect_triangle_line(CVector3  v1, // ◊≈“€…ŒŸ ‘“≈’«œÃÿŒ…À¡.
                             CVector3  v2,
                             CVector3  v3,
                             CVector3  n,  // Œœ“Õ¡Ãÿ ‘“≈’«œÃÿŒ…À¡.
                             CVector3  p1, // –≈“◊Ÿ  ÀœŒ≈√ œ‘“≈⁄À¡.
                             CVector3  p2, // ◊‘œ“œ  ÀœŒ≈√ œ‘“≈⁄À¡.
                             CVector3& pc) // ◊œ⁄◊“¡›¡≈Õ¡— ‘œﬁÀ¡ –≈“≈”≈ﬁ≈Œ…—.
{
  // ◊Ÿﬁ…”Ã—≈Õ “¡””‘œ—Œ…— Õ≈÷ƒ’ ÀœŒ√¡Õ… œ‘“≈⁄À¡ … –Ãœ”Àœ”‘ÿ¿ ‘“≈’«œÃÿŒ…À¡.
  float r1 = n & (p1 - v1);
  float r2 = n & (p2 - v1);
  // ≈”Ã… œ¬¡ ÀœŒ√¡ œ‘“≈⁄À¡ Ã≈÷¡‘ –œ œƒŒ’ ”‘œ“œŒ’ œ‘ –Ãœ”Àœ”‘…, ‘œ œ‘“≈⁄œÀ
  // Œ≈ –≈“≈”≈À¡≈‘ ‘“≈’«œÃÿŒ…À.
  if( f1_sgn(r1) == f1_sgn(r2) ) return FALSE;
  // ◊Ÿﬁ…”Ã—≈Õ ‘œﬁÀ’ –≈“≈”≈ﬁ≈Œ…— œ‘“≈⁄À¡ ” –Ãœ”Àœ”‘ÿ¿ ‘“≈’«œÃÿŒ…À¡.
  CVector3 ip = (p1 + ((p2 - p1) * (-r1 / (r2 - r1))));
  // –“œ◊≈“—≈Õ, Œ¡»œƒ…‘”— Ã… ‘œﬁÀ¡ –≈“≈”≈ﬁ≈Œ…— ◊Œ’‘“… ‘“≈’«œÃÿŒ…À¡.
  if( (((v2 - v1) ^ (ip - v1)) & n) <= 0) return FALSE; 
  if( (((v3 - v2) ^ (ip - v2)) & n) <= 0) return FALSE;
  if( (((v1 - v3) ^ (ip - v3)) & n) <= 0) return FALSE;
  pc = ip; return TRUE; 
}

˙ƒ≈”ÿ: 

Ô–≈“¡√…… ” ◊≈À‘œ“¡Õ… " & " … " ^ " œ¬œ⁄Œ¡ﬁ¡¿‘ ”œœ‘◊≈‘”‘◊≈ŒŒœ Dot Product … Cross Product. 


int f1_sgn(const float& k) // - ∆’ŒÀ√…—, ◊Ÿﬁ…”Ã—¿›¡— ⁄Œ¡À ﬁ…”Ã¡.
{
  if( k > 0 ) return 1;
  if( k < 0 ) return -1;
  return 0;
}


*********/


/*
*Ok, ËÏËÚËÛÂÏ track-ball (ÚÂÍ-¯‡‡).  Project the points onto the virtual
*trackball, then figure out the axis of rotation, which is the cross
*product of P1 P2 and O P1 (O is the center of the ball, 0,0,0)
*Note:  This is a deformed trackball-- is a trackball in the center,
*but is deformed into a hyperbolic sheet of rotation away from the
*center.  This particular function was chosen after trying out
*several variations.
 *
*It is assumed that the arguments to this routine are in the range
*(-1.0 ... 1.0)
 */
/*
*Ok, simulate a track-ball.  Project the points onto the virtual
*trackball, then figure out the axis of rotation, which is the cross
*product of P1 P2 and O P1 (O is the center of the ball, 0,0,0)
*Note:  This is a deformed trackball-- is a trackball in the center,
*but is deformed into a hyperbolic sheet of rotation away from the
*center.  This particular function was chosen after trying out
*several variations.
 *
*It is assumed that the arguments to this routine are in the range
*(-1.0 ... 1.0)
 */
quat & trackball(quat& q, vec2& pt1, vec2& pt2, scalar trackballsize){
  vec3 a; // Axis of rotation
  scalar phi;  // how much to rotate about axis
  vec3 d;
  scalar t;

  if(pt1.x==pt2.x && pt1.y==pt2.y){ // Zero rotation
    q=quat::id;
    return q;
  }
  // First, figure out z-coordinates for projection of P1 and P2 to
  // deformed sphere
  vec3 p1(pt1.x,pt1.y,tb_project_to_sphere(trackballsize,pt1.x,pt1.y));
  vec3 p2(pt2.x,pt2.y,tb_project_to_sphere(trackballsize,pt2.x,pt2.y));

  //  Now, we want the cross product of P1 and P2
  a=p1^p2;

  //  Figure out how much to rotate around that axis.
  d.x=p1.x-p2.x;
  d.y=p1.y-p2.y;
  d.z=p1.z-p2.z;
  t=sqrtf(d.x*d.x+d.y*d.y+d.z*d.z) / (trackballsize);

  // Avoid problems with out-of-control values...
  if(t> 1.0)t= 1.0;
  if(t<-1.0)t=-1.0;
  phi=2.0*scalar(asin(t));
  //axis_to_quat(q,a,phi);
  q.axis(a,phi);
  return q;
}

vec3& cube_map_normal(int i, int x, int y, int cubesize, vec3& v){
  scalar s, t, sc, tc;
  s=(scalar(x)+0.5)/scalar(cubesize);
  t=(scalar(y)+0.5)/scalar(cubesize);
  sc=s*2.0-1.0;
  tc=t*2.0-1.0;

  switch(i){
    case 0: v.x= 1.0; v.y= -tc; v.z= -sc; break;
    case 1: v.x=-1.0; v.y= -tc; v.z=  sc; break;
    case 2: v.x=  sc; v.y= 1.0; v.z=  tc; break;
    case 3: v.x=  sc; v.y=-1.0; v.z= -tc; break;
    case 4: v.x=  sc; v.y= -tc; v.z= 1.0; break;
    case 5: v.x= -sc; v.y= -tc; v.z=-1.0; break;
  }
  v.norm();
  return v;
}

vec3& reflect(vec3& r, const vec3& n, const vec3& l){
// compute the reflected vector R of L w.r.t N-vectors need to be 
// normalized
//
//  R   N   L
//  _       _
// |\   ^   /|
//   \  |  /
//    \ | /
//     \|/
//      +
  scalar n_dot_l;
  n_dot_l=2.0*n*l;
  r=l*(-1.0);
  r+=n*n_dot_l;
  return r;
}
// computes normal to polygon
// —˜ËÚ‡ÂÚ ÌÓÏ‡Î¸ Í ÚÂÛ„ÓÎ¸ÌËÍÛ
vec3 tri_normal_fpu(const vec3& v1, const vec3& v2, const vec3& v3){
/*  vec3 e1=v1-v2,e2=v3-v2;
  e1=e1^e2;
  e1.norm();
  return e1;
*/
  return vec3((v1-v2)^(v3-v2)).norm();
}
// Ò˜ËÚ‡ÂÚ ÔÎÓ˘‡‰¸ ÚÂÛ„ÓÎ¸ÌËÍ‡
// computes the area of a triangle
scalar tri_area_fpu(const vec3& v1, const vec3& v2, const vec3& v3){
/*  vec3 cp_sum=vec3_null;
  cp_sum=v1^v2;
  cp_sum+=v2^v3;
  cp_sum+=v3^v1;
  return cp_sum.len()*0.5;
*/
  return vec3((v1^v2)+(v2^v3)+(v3^v1)).len()*0.5;
}

// Ò˜ËÚ‡ÂÚ ÔÂËÏÂÚ ÚÂÛ„ÓÎ¸ÌËÍ‡
// computes the perimeter of a triangle
scalar tri_perim_fpu(const vec3& v1, const vec3& v2, const vec3& v3){
/*  scalar perim;
  vec3 diff;
  diff=v1-v2;
  perim=diff.len();
  diff=v2-v3;
  perim+=diff.len();
  diff=v3-v1;
  perim+=diff.len();
  return perim;
*/
  return scalar( (v1-v2).len()+(v2-v3).len()+(v3-v1).len() );
}

scalar tri_sprain(const vec3& v1, const vec3& v2, const vec3& v3){
/*
  Find triangle sprain as area attitude to perimeter with tri_spr_good adjustment.
  I think it is good method.
  May be, may be...
*/
  scalar perimeter;
  if((perimeter=tri_perim(v1,v2,v3)*cnst::tri_spr_good/3)==0)return 1.0;
  return scalar(sqrtf_scal(tri_area(v1,v2,v3))/perimeter);
}

// ‚˚˜ËÒÎËÚÂ ˆÂÌÚ Ë ‡‰ËÛÒ ‚ÔËÒ‡ÌÌÓÈ ÒÙÂ˚, ÓÔÂ‰ÂÎÂÌÌÓÈ ÚÂÏˇ „‡ÌˇÏË
// compute the center and radius of the inscribed circle defined by the three vertices
scalar find_in_circle(vec3& center, const vec3& v1, const vec3& v2, const vec3& v3){
  scalar area=tri_area(v1, v2, v3);
  if(area<cnst::one_eps){ center=v1; return 0.0; }// if the area is null
  scalar oo_perim=1.0/tri_perim(v1, v2, v3);
  center=v1*(v2-v3).len();
  center+=v2*(v3-v1).len();
  center+=v3*(v1-v2).len();
  center*=oo_perim;
  return 2.0*area*oo_perim;
/*
  vec3 diff;
  sub(diff, v2, v3);
  mult(center, v1, norm(diff));
  sub(diff, v3, v1);
  madd(center, v2, norm(diff));
  sub(diff, v1, v2);
  madd(center, v3, norm(diff));
  center *= oo_perim;
  return 2.0*area*oo_perim;
*/
}

// ‚˚˜ËÒÎˇÂÚ ˆÂÌÚ Ë ‡‰ËÛÒ ÒÙÂ˚, Ó„‡ÌË˜ÂÌÌÓÈ ÚÂÏˇ „‡ÌˇÏË
// ÚÓ ÂÒÚ¸ ÓÔËÒ‡ÌÌÛ˛ ÓÍÓÎÓ ÚÂı „‡ÌÂÈ ÒÙÂÛ
// compute the center and radius of the circumscribed circle defined by the three vertices
// i.e. the osculating circle of the three vertices
scalar find_circ_circle(vec3& center, const vec3& v1, const vec3& v2, const vec3& v3){
  vec3 e0=v3-v1, e1=v2-v1;
  scalar d1=e0*e1;

  e0=v3-v2; e1=v1-v2;
  scalar d2=e0*e1;

  e0=v1-v3; e1=v2-v3;
  scalar d3=e0*e1;

  scalar c1=d2*d3, c2=d3*d1, c3=d1*d2;
  scalar oo_c=1.0/(c1+c2+c3);

  center=(v1*(c2+c3)+v2*(c3+c1)+v3*(c1+c2))*oo_c*0.5;
  return 0.5*sqrtf((d1+d2)*(d2+d3)*(d3+d1)*oo_c);
}

// “Ë„ÓÌÓÏÂÚËˇ
// ¡˚ÒÚ˚È ÔÓ‰Ò˜ÂÚ ÍÓÒËÌÛÒ‡
scalar fast_cos(const scalar x){
  // Û„ÓÎ:  0 <= fT <= PI/2
  // Ï‡ÍÒËÏ‡Î¸Ì‡ˇ ‡·ÒÓÎ˛ÚÌ‡ˇ ÔÓ„Â¯ÌÓÒÚ¸ 2.3082e-09
  // ÛÒÍÓÂÌËÂ 1.47
  scalar x_sqr=x*x;
  scalar res=scalar(-2.605e-07);
  res*=x_sqr;
  res+=scalar(2.47609e-05);
  res*=x_sqr;
  res-=scalar(1.3888397e-03);
  res*=x_sqr;
  res+=scalar(4.16666418e-02);
  res*=x_sqr;
  res-=scalar(4.999999963e-01);
  res*=x_sqr;
  res+=1.0;
  return res;
}
// —‚Âı ·˚ÒÚ˚È ÔÓ‰Ò˜ÂÚ ÍÓÒËÌÛÒ‡
scalar ffast_cos(const scalar x){
  // Û„ÓÎ:  0<=fT<=PI/2
  // Ï‡ÍÒËÏ‡Î¸Ì‡ˇ ‡·ÒÓÎ˛ÚÌ‡ˇ ÔÓ„Â¯ÌÓÒÚ¸ 1.1880e-03
  // ÛÒÍÓÂÌËÂ 2.14

  scalar x_sqr=x*x, res=scalar(3.705e-02);
  res*=x_sqr;
  res-=scalar(4.967e-01);
  res*=x_sqr;
  res+=1.0;
  return res;
}

scalar fcos(const scalar x){ // adduction argument (0<=x<=PI/2)
  //bool sign=(x<0)?false:true; // ÔÓÎÓÊËÚÂÎ¸Ì˚ÏË Ò˜ËÚ‡ÂÏ ˜ËÒÎ‡, ÍÓÚÓ˚Â >=0
  scalar i;
  for(i=fabs(x);i>=cnst::two_pi;i-=cnst::two_pi); // Û·Ë‡ÂÏ ˆÂÎ˚Â ÔÂËÓ‰˚
  bool sign=(i>cnst::one_pi)?false:true;
  i-=sign?0:cnst::one_pi;
  bool asign=(i>cnst::half_pi)?false:true;
  i-=asign?0:cnst::half_pi;
  sign=(sign==asign);
  return sign?unmath::fast_cos(i):-unmath::fast_cos(i);
}

#ifndef _WIN32
#define _isnan isnan
#define _finite finite
#endif

void v_is_valid(const vec3& v){// Ô‡‚ËÎ¸Ì˚È ‚ÂÍÚÓ
  assert(!_isnan(v.x) && !_isnan(v.y) && !_isnan(v.z) &&
    _finite(v.x) && _finite(v.y) && _finite(v.z));
}

void v_is_valid(scalar lambda){// Ô‡‚ËÎ¸Ì˚È ÒÍ‡Îˇ
  assert(!_isnan(lambda) && _finite(lambda));
}

}
