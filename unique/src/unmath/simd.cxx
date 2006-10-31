/***************************************************************************
 *            simd.cpp
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

#include "simd.hxx"
#include "unmath.hxx"

/*            FPU (non optimized)           */
namespace _FPU{
  static scalar oo_scal(const scalar f){return 1.0/f;}
  static scalar sqrtf_scal(const scalar f){return sqrtf(f);}
  static scalar len_vec3(const vec3& v){return sqrtf(v.x*v.x+v.y*v.y+v.z*v.z);}
  static scalar len_vec4(const vec4& v){return sqrtf(v.x*v.x+v.y*v.y+v.z*v.z+v.w*v.w);}
  static void norm_vec3(vec3& v){
    scalar length=sqrtf(v.x*v.x+v.y*v.y+v.z*v.z);
    if(fabs(length)<cnst::one_eps)return;
    scalar ilength=1.0f/length;
    v.x*=ilength;
    v.y*=ilength;
    v.z*=ilength;
  }
  static void norm_vec4(vec4& v){
    scalar length=sqrtf(v.x*v.x+v.y*v.y+v.z*v.z+v.w*v.w);
    if(fabs(length)<cnst::one_eps) return;
    scalar ilength=1.0f/length;
    v.x*=ilength;
    v.y*=ilength;
    v.z*=ilength;
    v.w*=ilength;
  }
  // Arithmetic
  // 3D Vector
  static scalar& dot_vec3_vec3(scalar& r,const vec3& a,const vec3& b){
    return r=a.x*b.x+a.y*b.y+a.z*b.z;
  }
  static vec3& cross_vec3_vec3(vec3& r,const vec3& a,const vec3& b){
    r.x=a.y*b.z-a.z*b.y; r.y=a.z*b.x-a.x*b.z; r.z=a.x*b.y-a.y*b.x;
    return r;
  }
  static vec3& sub_vec3_vec3(vec3& r, const vec3& v1, const vec3& v2){
    r.x=v1.x-v2.x; r.y=v1.y-v2.y; r.z=v1.z-v2.z;
    return r;
  }
  // 4D Vector
  static void dot_vec4_vec4(const vec4& v0, const void *v1, int v1_stride, void *result, int result_stride, int count){
    for(int i=0; i<count; i++){
      *(scalar*)result=v0**(const vec4*)v1;
      v1=(char*)v1+v1_stride;
      result=(char*)result+result_stride;
    }
  }
  /* mat4 */
  static void mul_mat4_vec3(const mat4& m, const void *v, int v_stride, void *r, int r_stride, int count){
    for(int i=0;i<count;i++){
      vec3&b=*(vec3*)r;
      const vec3&a=*(const vec3*)v;
      b.x=m[0]*a[0]+m[4]*a[1]+m[ 8]*a[2]+m[12];
      b.y=m[1]*a[0]+m[5]*a[1]+m[ 9]*a[2]+m[13];
      b.z=m[2]*a[0]+m[6]*a[1]+m[10]*a[2]+m[14];
      v=(char*)v+v_stride;
      r=(char*)r+r_stride;
    }
  }
  static void mul_mat4_vec4(const mat4& m, const void *v, int v_stride, void *r, int r_stride, int count){
    for(int i=0;i<count;i++){
      vec4&b=*(vec4*)r;
      const vec4&a=*(const vec4*)v;
      b.x=m[ 0]*a[0]+m[ 4]*a[1]+m[ 8]*a[2]+m[12]*a[3];
      b.y=m[ 1]*a[0]+m[ 5]*a[1]+m[ 9]*a[2]+m[13]*a[3];
      b.z=m[ 2]*a[0]+m[ 6]*a[1]+m[10]*a[2]+m[14]*a[3];
      b.w=m[ 3]*a[0]+m[ 7]*a[1]+m[11]*a[2]+m[15]*a[3];
      v=(char*)v+v_stride;
      r=(char*)r+r_stride;
    }
  }
  static void mul_mat4_scal(const mat4& m, const scalar& f, mat4& r){
    r[ 0]=m[ 0]*f; r[ 1]=m[ 1]*f; r[ 2]=m[ 2]*f; r[ 3]=m[ 3]*f;
    r[ 4]=m[ 4]*f; r[ 5]=m[ 5]*f; r[ 6]=m[ 6]*f; r[ 7]=m[ 7]*f;
    r[ 8]=m[ 8]*f; r[ 9]=m[ 9]*f; r[10]=m[10]*f; r[11]=m[11]*f;
    r[12]=m[12]*f; r[13]=m[13]*f; r[14]=m[14]*f; r[15]=m[15]*f;
  }
  static void add_mat4_mat4(const mat4& m0, const mat4& m1, mat4& r0){
    r0[ 0]=m0[ 0]+m1[ 0]; r0[ 1]=m0[ 1]+m1[ 1]; r0[ 2]=m0[ 2]+m1[ 2]; r0[ 3]=m0[ 3]+m1[ 3];
    r0[ 4]=m0[ 4]+m1[ 4]; r0[ 5]=m0[ 5]+m1[ 5]; r0[ 0]=m0[ 6]+m1[ 6]; r0[ 0]=m0[ 7]+m1[ 7];
    r0[ 8]=m0[ 8]+m1[ 8]; r0[ 9]=m0[ 9]+m1[ 9]; r0[10]=m0[10]+m1[10]; r0[11]=m0[11]+m1[11];
    r0[12]=m0[12]+m1[12]; r0[13]=m0[13]+m1[13]; r0[14]=m0[14]+m1[14]; r0[15]=m0[15]+m1[15];
  }
  static void sub_mat4_mat4(const mat4& m0, const mat4& m1, mat4& r0){
    r0[ 0]=m0[ 0]-m1[ 0]; r0[ 1]=m0[ 1]-m1[ 1]; r0[ 2]=m0[ 2]-m1[ 2]; r0[ 3]=m0[ 3]-m1[ 3];
    r0[ 4]=m0[ 4]-m1[ 4]; r0[ 5]=m0[ 5]-m1[ 5]; r0[ 0]=m0[ 6]-m1[ 6]; r0[ 0]=m0[ 7]-m1[ 7];
    r0[ 8]=m0[ 8]-m1[ 8]; r0[ 9]=m0[ 9]-m1[ 9]; r0[10]=m0[10]-m1[10]; r0[11]=m0[11]-m1[11];
    r0[12]=m0[12]-m1[12]; r0[13]=m0[13]-m1[13]; r0[14]=m0[14]-m1[14]; r0[15]=m0[15]-m1[15];
  }
  static void mul_mat4_mat4(const mat4& m0, const mat4& m1, mat4& r0){
    r0[ 0]=m0[ 0]*m1[ 0]+m0[ 4]*m1[ 1]+m0[ 8]*m1[ 2]+m0[12]*m1[ 3];
    r0[ 1]=m0[ 1]*m1[ 0]+m0[ 5]*m1[ 1]+m0[ 9]*m1[ 2]+m0[13]*m1[ 3];
    r0[ 2]=m0[ 2]*m1[ 0]+m0[ 6]*m1[ 1]+m0[10]*m1[ 2]+m0[14]*m1[ 3];
    r0[ 3]=m0[ 3]*m1[ 0]+m0[ 7]*m1[ 1]+m0[11]*m1[ 2]+m0[15]*m1[ 3];
    r0[ 4]=m0[ 0]*m1[ 4]+m0[ 4]*m1[ 5]+m0[ 8]*m1[ 6]+m0[12]*m1[ 7];
    r0[ 5]=m0[ 1]*m1[ 4]+m0[ 5]*m1[ 5]+m0[ 9]*m1[ 6]+m0[13]*m1[ 7];
    r0[ 6]=m0[ 2]*m1[ 4]+m0[ 6]*m1[ 5]+m0[10]*m1[ 6]+m0[14]*m1[ 7];
    r0[ 7]=m0[ 3]*m1[ 4]+m0[ 7]*m1[ 5]+m0[11]*m1[ 6]+m0[15]*m1[ 7];
    r0[ 8]=m0[ 0]*m1[ 8]+m0[ 4]*m1[ 9]+m0[ 8]*m1[10]+m0[12]*m1[11];
    r0[ 9]=m0[ 1]*m1[ 8]+m0[ 5]*m1[ 9]+m0[ 9]*m1[10]+m0[13]*m1[11];
    r0[10]=m0[ 2]*m1[ 8]+m0[ 6]*m1[ 9]+m0[10]*m1[10]+m0[14]*m1[11];
    r0[11]=m0[ 3]*m1[ 8]+m0[ 7]*m1[ 9]+m0[11]*m1[10]+m0[15]*m1[11];
    r0[12]=m0[ 0]*m1[12]+m0[ 4]*m1[13]+m0[ 8]*m1[14]+m0[12]*m1[15];
    r0[13]=m0[ 1]*m1[12]+m0[ 5]*m1[13]+m0[ 9]*m1[14]+m0[13]*m1[15];
    r0[14]=m0[ 2]*m1[12]+m0[ 6]*m1[13]+m0[10]*m1[14]+m0[14]*m1[15];
    r0[15]=m0[ 3]*m1[12]+m0[ 7]*m1[13]+m0[11]*m1[14]+m0[15]*m1[15];
    /*mat4(
    a00*B.a00+a01*B.a10+a02*B.a20+a03*B.a30,
    a10*B.a00+a11*B.a10+a12*B.a20+a13*B.a30,
    a20*B.a00+a21*B.a10+a22*B.a20+a23*B.a30,
    a30*B.a00+a31*B.a10+a32*B.a20+a33*B.a30,
    a00*B.a01+a01*B.a11+a02*B.a21+a03*B.a31,
    a10*B.a01+a11*B.a11+a12*B.a21+a13*B.a31,
    a20*B.a01+a21*B.a11+a22*B.a21+a23*B.a31,
    a30*B.a01+a31*B.a11+a32*B.a21+a33*B.a31,
    a00*B.a02+a01*B.a12+a02*B.a22+a03*B.a32,
    a10*B.a02+a11*B.a12+a12*B.a22+a13*B.a32,
    a20*B.a02+a21*B.a12+a22*B.a22+a23*B.a32,
    a30*B.a02+a31*B.a12+a32*B.a22+a33*B.a32,
    a00*B.a03+a01*B.a13+a02*B.a23+a03*B.a33,
    a10*B.a03+a11*B.a13+a12*B.a23+a13*B.a33,
    a20*B.a03+a21*B.a13+a22*B.a23+a23*B.a33,
    a30*B.a03+a31*B.a13+a32*B.a23+a33*B.a33
    )*/
  }
  static scalar det_mat4(const mat4& m){
    scalar d;
    d =m[ 0]*(m[ 5]*(m[10]*m[15]-m[14]*m[11])-m[ 9]*(m[ 6]*m[15]-m[14]*m[ 7])+
	      m[13]*(m[ 6]*m[11]-m[10]*m[ 7]));
    d-=m[ 4]*(m[ 1]*(m[10]*m[15]-m[14]*m[11])-m[ 9]*(m[ 2]*m[15]-m[14]*m[ 3])+
	      m[13]*(m[ 2]*m[11]-m[10]*m[ 3]));
    d+=m[ 8]*(m[ 1]*(m[ 6]*m[15]-m[14]*m[ 7])-m[ 5]*(m[ 2]*m[15]-m[14]*m[ 3])+
	      m[13]*(m[ 2]*m[ 7]-m[ 6]*m[ 3]));
    d-=m[12]*(m[ 1]*(m[ 6]*m[11]-m[10]*m[ 7])-m[ 5]*(m[ 2]*m[11]-m[10]*m[ 3])+
	      m[ 9]*(m[ 2]*m[ 7]-m[ 6]*m[ 3]));
    return d;
  }
  void inv_mat4(const mat4& m, mat4& r){
    scalar d=m.det();
    if(d<cnst::one_eps)r=array16_id;
    scalar i=1.0f/d;
    r[ 0]= (m[ 5]*(m[10]*m[15]-m[14]*m[11])-m[ 9]*(m[ 6]*m[15]-m[14]*m[ 7])+
	    m[13]*(m[ 6]*m[11]-m[10]*m[ 7]))*i;
    r[ 1]=-(m[ 1]*(m[10]*m[15]-m[14]*m[11])-m[ 9]*(m[ 2]*m[15]-m[14]*m[ 3])+
	    m[13]*(m[ 2]*m[11]-m[10]*m[ 3]))*i;
    r[ 2]= (m[ 1]*(m[ 6]*m[15]-m[14]*m[ 7])-m[ 5]*(m[ 2]*m[15]-m[14]*m[ 3])+
	    m[13]*(m[ 2]*m[ 7]-m[ 6]*m[ 3]))*i;
    r[ 3]=-(m[ 1]*(m[ 6]*m[11]-m[10]*m[ 7])-m[ 5]*(m[ 2]*m[11]-m[10]*m[ 3])+
	    m[ 9]*(m[ 2]*m[ 7]-m[ 6]*m[ 3]))*i;
    r[ 4]=-(m[ 4]*(m[10]*m[15]-m[14]*m[11])-m[ 8]*(m[ 6]*m[15]-m[14]*m[ 7])+
	    m[12]*(m[ 6]*m[11]-m[10]*m[ 7]))*i;
    r[ 5]= (m[ 0]*(m[10]*m[15]-m[14]*m[11])-m[ 8]*(m[ 2]*m[15]-m[14]*m[ 3])+
	    m[12]*(m[ 2]*m[11]-m[10]*m[ 3]))*i;
    r[ 6]=-(m[ 0]*(m[ 6]*m[15]-m[14]*m[ 7])-m[ 4]*(m[ 2]*m[15]-m[14]*m[ 3])+
	    m[12]*(m[ 2]*m[ 7]-m[ 6]*m[ 3]))*i;
    r[ 7]= (m[ 0]*(m[ 6]*m[11]-m[10]*m[ 7])-m[ 4]*(m[ 2]*m[11]-m[10]*m[ 3])+
	    m[ 8]*(m[ 2]*m[ 7]-m[ 6]*m[ 3]))*i;
    r[ 8]= (m[ 4]*(m[ 9]*m[15]-m[13]*m[11])-m[ 8]*(m[ 5]*m[15]-m[13]*m[ 7])+
	    m[12]*(m[ 5]*m[11]-m[ 9]*m[ 7]))*i;
    r[ 9]=-(m[ 0]*(m[ 9]*m[15]-m[13]*m[11])-m[ 8]*(m[ 1]*m[15]-m[13]*m[ 3])+
	    m[12]*(m[ 1]*m[11]-m[ 9]*m[ 3]))*i;
    r[10]= (m[ 0]*(m[ 5]*m[15]-m[13]*m[ 7])-m[ 4]*(m[ 1]*m[15]-m[13]*m[ 3])+
	    m[12]*(m[ 1]*m[ 7]-m[ 5]*m[ 3]))*i;
    r[11]=-(m[ 0]*(m[ 5]*m[11]-m[ 9]*m[ 7])-m[ 4]*(m[ 1]*m[11]-m[ 9]*m[ 3])+
	    m[ 8]*(m[ 1]*m[ 7]-m[ 5]*m[ 3]))*i;
    r[12]=-(m[ 4]*(m[ 9]*m[14]-m[13]*m[10])-m[ 8]*(m[ 5]*m[14]-m[13]*m[ 6])+
	    m[12]*(m[ 5]*m[10]-m[ 9]*m[ 6]))*i;
    r[13]= (m[ 0]*(m[ 9]*m[14]-m[13]*m[10])-m[ 8]*(m[ 1]*m[14]-m[13]*m[ 2])+
	    m[12]*(m[ 1]*m[10]-m[ 9]*m[ 2]))*i;
    r[14]=-(m[ 0]*(m[ 5]*m[14]-m[13]*m[ 6])-m[ 4]*(m[ 1]*m[14]-m[13]*m[ 2])+
	    m[12]*(m[ 1]*m[ 6]-m[ 5]*m[ 2]))*i;
    r[15]= (m[ 0]*(m[ 5]*m[10]-m[ 9]*m[ 6])-m[ 4]*(m[ 1]*m[10]-m[ 9]*m[ 2])+
	    m[ 8]*(m[ 1]*m[ 6]-m[ 5]*m[ 2]))*i;
  }
  // computes normal to polygon
  static vec3 tri_normal(const vec3& v1, const vec3& v2, const vec3& v3){
    return vec3((v1-v2)^(v3-v2)).norm();
  }
  // computes the area of a triangle
  static scalar tri_area(const vec3& v1, const vec3& v2, const vec3& v3){
    /*  vec3 cp_sum=vec3_null;
	cp_sum=v1^v2;
	cp_sum+=v2^v3;
	cp_sum+=v3^v1;
	return cp_sum.len()*0.5;
    */
    return vec3((v1^v2)+(v2^v3)+(v3^v1)).len()*0.5;
  }
  // computes the perimeter of a triangle
  static scalar tri_perim(const vec3& v1, const vec3& v2, const vec3& v3){
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
  static scalar tri_sprain(const vec3& v1, const vec3& v2, const vec3& v3){
    /*
      Find triangle sprain as area attitude to perimeter with tri_spr_good adjustment.
      I think it is good method.
      May be, may be...
    */
    scalar perimeter;
    if((perimeter=::tri_perim(v1,v2,v3)*cnst::tri_spr_good/3)==0)return 1.0;
    return scalar(::sqrtf_scal(::tri_area(v1,v2,v3))/perimeter);
  }
  
  bool toggle(){
    ::sqrtf_scal=(scalar (*)(const scalar))sqrtf;
    
    ::len_vec3=len_vec3;
    ::len_vec4=len_vec4;
    ::norm_vec3=norm_vec3;
    ::norm_vec4=norm_vec4;
    
    ::sub_vec3_vec3=sub_vec3_vec3;
    ::dot_vec3_vec3=dot_vec3_vec3;
    ::cross_vec3_vec3=cross_vec3_vec3;
    
    ::dot_vec4_vec4=dot_vec4_vec4;
    ::mul_mat4_vec3=mul_mat4_vec3;
    ::mul_mat4_mat4=mul_mat4_mat4;
    
    return true;
  }
}
  
/*    Pointers prototypes    */
// Scalar
//scalar (*sqrtf_scal)(const scalar f)=_FPU::sqrtf_scal;

#define UNMATH_PFUNC(rets,name,args) rets (*name)args=_FPU::name
#include"simd.func.hxx"
#undef UNMATH_PFUNC

#include "3dnow.hxx"
#include "sse.hxx"
#include "sse3.hxx"

/*      SIMD Optimizer       */
int SIMD::mode=SIMD::_FPU;
bool SIMD::Check(int swt){
  // Comming soon
  return true;
}

#define OPT_TOGGLE(swt,mode) if(swt==SIMD::mode) return mode::toggle();
bool SIMD::Switch(int swt){
  OPT_TOGGLE(swt,_FPU);
  //_3DNOW::toggle();
  //OPT_TOGGLE(swt,_SSE);
  OPT_TOGGLE(swt,_3DNOW);
}
