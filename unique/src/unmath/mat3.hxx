#pragma once

namespace unmath{//tolua_export
  /*
    for all the matrices...a<x><y> indicates the element at row x, col y

    For example:
    a01 <-> row 0, col 1 
  */
  static const scalar array9_id[]={
    1.0, 0.0, 0.0,
    0.0, 1.0, 0.0,
    0.0, 0.0, 1.0
  };
  static const scalar array9_null[]={
    0.0, 0.0, 0.0,
    0.0, 0.0, 0.0,
    0.0, 0.0, 0.0
  };
  //tolua_begin
  class mat3{  //   3x3 Matrix
  public:
    mat3(const scalar* arr){ memcpy(array, arr, sizeof(scalar)*9); }//tolua_noexport
    mat3(){ memcpy(array, array9_id, sizeof(scalar)*9); }
    mat3(const vec3 v1, const vec3 v2, const vec3 v3){
      memcpy(array,   v1, sizeof(scalar)*3);
      memcpy(array+3, v2, sizeof(scalar)*3);
      memcpy(array+6, v3, sizeof(scalar)*3);
    }
    mat3(const mat3& M){ memcpy(array, M.array, sizeof(scalar)*9); }
    mat3(const quat& q){ (*this)=array9_id; this->rotate(q); }
    mat3(const scalar& f0, const scalar& f1, const scalar& f2,  
	 const scalar& f3, const scalar& f4, const scalar& f5,  
	 const scalar& f6, const scalar& f7, const scalar& f8):
      a00(f0), a10(f1), a20(f2), 
      a01(f3), a11(f4), a21(f5),
      a02(f6), a12(f7), a22(f8) { }
    // Equals
    bool operator==(const mat3 &m) const{
      return bool(fabs(array[0]-m[0])<cnst::one_eps&&fabs(array[1]-m[1])<cnst::one_eps&&
		  fabs(array[2]-m[2])<cnst::one_eps&&fabs(array[3]-m[3])<cnst::one_eps&&
		  fabs(array[4]-m[4])<cnst::one_eps&&fabs(array[5]-m[5])<cnst::one_eps&&
		  fabs(array[6]-m[6])<cnst::one_eps&&fabs(array[7]-m[7])<cnst::one_eps&&
		  fabs(array[8]-m[8])<cnst::one_eps);
    }
    bool operator!=(const mat3 &m) const{ return !(*this==m); }//tolua_noexport
    // Typecasting
    //tolua_end
    operator scalar*(){return array;}
    operator const scalar*()const{return array;}
    //tolua_begin
    // Accessing
    scalar & operator[](int i){ return array[i]; }
    const scalar operator[](int i) const{ return array[i]; }

    /*const vec3 col(const int i)const{ return vec3(&array[i*3]); }
      const vec3 operator[](int i)const{ return vec3(array[i], array[i+3], array[i+6]); }*/

    const scalar & operator()(const int& i, const int& j)const{ return array[j*3+i]; }
    scalar & operator()(const int& i, const int& j){ return  array[j*3+i]; }

    const vec3 operator*(const vec3 &v) const{
      return vec3(array[0]*v.x+array[3]*v.y+array[6]*v.z,
		  array[1]*v.x+array[4]*v.y+array[7]*v.z,
		  array[2]*v.x+array[5]*v.y+array[8]*v.z);
    }
    const vec4 operator*(const vec4 &v) const{
      return vec4(array[0]*v.x+array[3]*v.y+array[6]*v.z,
		  array[1]*v.x+array[4]*v.y+array[7]*v.z,
		  array[2]*v.x+array[5]*v.y+array[8]*v.z, v.w);
    }
    mat3 operator*(const scalar f) const{
      return mat3(a00*f, a10*f, a20*f,
		  a01*f, a11*f, a21*f,
		  a02*f, a12*f, a22*f);
    }
    mat3 operator*(const mat3 &m) const{
      return mat3(array[0]*m[0]+array[3]*m[1]+array[6]*m[2],
		  array[1]*m[0]+array[4]*m[1]+array[7]*m[2],
		  array[2]*m[0]+array[5]*m[1]+array[8]*m[2],
		  array[0]*m[3]+array[3]*m[4]+array[6]*m[5],
		  array[1]*m[3]+array[4]*m[4]+array[7]*m[5],
		  array[2]*m[3]+array[5]*m[4]+array[8]*m[5],
		  array[0]*m[6]+array[3]*m[7]+array[6]*m[8],
		  array[1]*m[6]+array[4]*m[7]+array[7]*m[8],
		  array[2]*m[6]+array[5]*m[7]+array[8]*m[8]);
    }
    mat3 operator+(const mat3 &m) const{
      return mat3(array[0]+m[0], array[1]+m[1], array[2]+m[2],
		  array[3]+m[3], array[4]+m[4], array[5]+m[5],
		  array[6]+m[6], array[7]+m[7], array[8]+m[8]);
    }
    mat3 operator-(const mat3 &m) const {
      return mat3(array[0]-m[0], array[1]-m[1], array[2]-m[2],
		  array[3]-m[3], array[4]-m[4], array[5]-m[5],
		  array[6]-m[6], array[7]-m[7], array[8]-m[8]);
    }
    //tolua_end
    mat3 &operator*=(scalar f){ return *this=*this*f; }
    mat3 &operator*=(const mat3 &m){ return *this=*this*m; }
    mat3 &operator+=(const mat3 &m){ return *this=*this+m; }
    mat3 &operator-=(const mat3 &m){ return *this=*this-m; }
    //tolua_begin
    // Methods
    scalar det() const{ scalar d; // determinant
      d =array[0]*array[4]*array[8];
      d+=array[3]*array[7]*array[2];
      d+=array[6]*array[1]*array[5];
      d-=array[6]*array[4]*array[2];
      d-=array[3]*array[1]*array[8];
      d-=array[0]*array[7]*array[5];
      return d;
    }
    inline scalar operator~()const{ return det(); } //  determinant
    mat3 tran() const { // Transpose matrix
      return mat3(array[0],array[3],array[6],
		  array[1],array[4],array[7],
		  array[2],array[5],array[8]);
    }
    mat3 inv() const{ // Inverse matrix
      float idet=1.0f/det();
      return mat3( (array[4]*array[8]-array[7]*array[5])*idet,
		  -(array[1]*array[8]-array[7]*array[2])*idet,
		   (array[1]*array[5]-array[4]*array[2])*idet,
		  -(array[3]*array[8]-array[6]*array[5])*idet,
		   (array[0]*array[8]-array[6]*array[2])*idet,
		  -(array[0]*array[5]-array[3]*array[2])*idet,
		   (array[3]*array[7]-array[6]*array[4])*idet,
		  -(array[0]*array[7]-array[6]*array[1])*idet,
		   (array[0]*array[4]-array[3]*array[1])*idet );
    }
    bool isid() const{ // True if it identity matrix
      return (fabs(array[0]-1.0f)<cnst::one_eps&&fabs(array[3])<cnst::one_eps&&
	      fabs(array[6]     )<cnst::one_eps&&fabs(array[1])<cnst::one_eps&&
	      fabs(array[4]-1.0f)<cnst::one_eps&&fabs(array[7])<cnst::one_eps&&
	      fabs(array[2]     )<cnst::one_eps&&fabs(array[5])<cnst::one_eps&&
	      fabs(array[8]-1.0f)<cnst::one_eps);
    }
    void siden(){ // Load identity matrix
      array[0]=1.0; array[3]=0.0; array[6]=0.0;
      array[1]=0.0; array[4]=1.0; array[7]=0.0;
      array[2]=0.0; array[5]=0.0; array[8]=1.0;
    }
    void snull(){ // Load null matrix
      array[0]=0.0; array[3]=0.0; array[6]=0.0;
      array[1]=0.0; array[4]=0.0; array[7]=0.0;
      array[2]=0.0; array[5]=0.0; array[8]=0.0;
    }
    // Modelview matrix
    void rotate(const vec3& axis, scalar angle){ // Rotate matrix about axis
      scalar rad=angle*cnst::to_rad;
      scalar c=cos(rad),s=sin(rad);
      vec3 v=axis;
      v.norm();
      scalar xx=v.x*v.x, yy=v.y*v.y, zz=v.z*v.z, xy=v.x*v.y, yz=v.y*v.z, zx=v.z*v.x;
      scalar xs=v.x*s,   ys=v.y*s,   zs=v.z*s;
      array[0]=(1.0f-c)*xx+c;  array[3]=(1.0f-c)*xy-zs; array[6]=(1.0f-c)*zx+ys;
      array[1]=(1.0f-c)*xy+zs; array[4]=(1.0f-c)*yy+c;  array[7]=(1.0f-c)*yz-xs;
      array[2]=(1.0f-c)*zx-ys; array[5]=(1.0f-c)*yz+xs; array[8]=(1.0f-c)*zz+c;
    }
    void rotate(const quat& q); // Rotate matrix use quaternion
    void scale(const vec3 &v){
      array[0]=v.x; array[3]=0.0; array[6]=0.0;
      array[1]=0.0; array[4]=v.y; array[7]=0.0;
      array[2]=0.0; array[5]=0.0; array[8]=v.z;
    }
    // Projection matrix
    void orthonorm(){ // Orthonormalize matrix
      vec3 x(array[0],array[1],array[2]);
      vec3 y(array[3],array[4],array[5]);
      vec3 z;    x.norm();
      z=x^y;     z.norm();
      y=z^x;     y.norm();
      array[0]=x.x; array[3]= y.x; array[6]=z.x;
      array[1]=x.y; array[4]= y.y; array[7]=z.y;
      array[2]=x.z; array[5]= y.z; array[8]=z.z;
    }
    /*
      inline vec3 at();
      inline vec3 up();
      inline vec3 dir();
    */
    // Matrix norms...
    // Compute || M ||
    //      1
    //scalar norm_one();
    // Compute || M ||
    //      +inf
    //scalar norm_inf();
    // data cells
    //tolua_end
    union{
      struct{
	//tolua_begin
	scalar a00, a10, a20;
	scalar a01, a11, a21;
	scalar a02, a12, a22;
	//tolua_end
      };
      struct{
	//tolua_begin
	scalar _11, _12, _13;
	scalar _21, _22, _23;
	scalar _31, _32, _33;
	//tolua_end
      };
      struct{
	//tolua_begin
	scalar b00, b10, b20;
	scalar b01, b11, b21;
	scalar b02, b12, b22;
	//tolua_end
      };
      scalar array[9];     // array access //tolua_export
    };
    //tolua_begin
    void set_row(int i, const vec3& v){ array[i]=v.x; array[i+3]=v.y; array[i+6]=v.z; }
    void set_col(int i, const vec3& v){ array[i*3]=v.x; array[i*3+1]=v.y; array[i*3+2]=v.z; }
    // documented
    static string __info(string);
    // constants
    static tolua_readonly mat3 null;
    static tolua_readonly mat3 nul;
    static tolua_readonly mat3 id;
    static tolua_readonly mat3 one;
    //
    operator string()const;
  };
  //tolua_end

  const mat3 operator*(const scalar, const mat3&);

}//tolua_export

