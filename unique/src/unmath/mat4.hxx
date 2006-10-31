#pragma once

namespace unmath{//tolua_export
  /*
    for all the matrices...a<x><y> indicates the element at row x, col y

    For example:
    a01 <-> row 0, col 1 
  */

  // constant algebraic values
  static const scalar array16_id[]={
    1.0, 0.0, 0.0, 0.0,
    0.0, 1.0, 0.0, 0.0,
    0.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 1.0
  };
  static const scalar array16_null[]={
    0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0
  };
  static const scalar array16_scale_bias[]={
    0.5, 0.0, 0.0, 0.0,
    0.0, 0.5, 0.0, 0.0,
    0.0, 0.0, 0.5, 0.0,
    0.5, 0.5, 0.5, 1.0
  };
  //tolua_begin
  class mat4{  //   4x4 Matrix
  public:
    mat4(const scalar* arr){ memcpy(array, arr, sizeof(scalar)*16); }//tolua_noexport
    mat4(){ memcpy(array, array16_id, sizeof(scalar)*16); }
    mat4(const vec4 v1,const vec4 v2,const vec4 v3,const vec4 v4){
      memcpy(array   ,v1.array,sizeof(scalar)*4);
      memcpy(array+4 ,v2.array,sizeof(scalar)*4);
      memcpy(array+8 ,v3.array,sizeof(scalar)*4);
      memcpy(array+12,v4.array,sizeof(scalar)*4);
    }
    mat4(const quat&);
    mat4(const vec3&);
    mat4(const mat4& M){ memcpy(array, M.array, sizeof(scalar)*16); }
    mat4(const scalar& f0,  const scalar& f1,  const scalar& f2,  const scalar& f3,
	 const scalar& f4,  const scalar& f5,  const scalar& f6,  const scalar& f7,
	 const scalar& f8,  const scalar& f9,  const scalar& f10, const scalar& f11,
	 const scalar& f12, const scalar& f13, const scalar& f14, const scalar& f15):
      a00(f0 ), a10(f1 ), a20(f2 ), a30(f3 ),
      a01(f4 ), a11(f5 ), a21(f6 ), a31(f7 ),
      a02(f8 ), a12(f9 ), a22(f10), a32(f11),
      a03(f12), a13(f13), a23(f14), a33(f15) { }
    // Equals
    inline bool operator==(const mat4& m) const{
      return bool(fabs(array[0] -m[0] )<cnst::one_eps&&fabs(array[1] -m[1] )<cnst::one_eps&&
		  fabs(array[2] -m[2] )<cnst::one_eps&&fabs(array[3] -m[3] )<cnst::one_eps&& 
		  fabs(array[4] -m[4] )<cnst::one_eps&&fabs(array[5] -m[5] )<cnst::one_eps&&
		  fabs(array[6] -m[6] )<cnst::one_eps&&fabs(array[7] -m[7] )<cnst::one_eps&& 
		  fabs(array[8] -m[8] )<cnst::one_eps&&fabs(array[9] -m[9] )<cnst::one_eps&&
		  fabs(array[10]-m[10])<cnst::one_eps&&fabs(array[11]-m[11])<cnst::one_eps&&
		  fabs(array[12]-m[12])<cnst::one_eps&&fabs(array[13]-m[13])<cnst::one_eps&&
		  fabs(array[14]-m[14])<cnst::one_eps&&fabs(array[15]-m[15])<cnst::one_eps);
    }
    //tolua_end
    inline bool operator!=(const mat4& m) const{ return !(*this==m); }
    // Typecasting
    inline operator scalar*() { return array; }
    inline operator const scalar*() const { return array; }
    //tolua_begin
    // Operations
    inline vec3 operator*(const vec3& v) const{
      vec3 r;
      mul_mat4_vec3(*this,&v,0,&r,0,1);
      return r;
    }
    inline vec4 operator*(const vec4& v) const{
      vec4 r;
      mul_mat4_vec4(*this,&v,0,&r,0,1);
      return r;
    }
    inline mat4 operator*(const scalar f) const{
      mat4 r;
      mul_mat4_scal(*this,f,r);
      return r;
    }
    inline mat4 operator*(const mat4& m) const{
      mat4 r;
      mul_mat4_mat4(*this,m,r);
      return r;
    }
    inline mat4 operator+(const mat4& m) const{
      mat4 r;
      add_mat4_mat4(*this,m,r);
      return r;
    }
    inline mat4 operator-(const mat4& m) const{
      mat4 r;
      sub_mat4_mat4(*this,m,r);
      return r;
    }
    //tolua_end
    inline mat4 &operator*=(const scalar f){ return *this=*this*f; }
    inline mat4 &operator*=(const mat4& m){ return *this=*this*m; }
    inline mat4 &operator+=(const mat4& m){ return *this=*this+m; }
    inline mat4 &operator-=(const mat4& m){ return *this=*this-m; }
    //tolua_begin
    // Accessing
    const vec4 col(const int i)const{ return vec4(&array[i*4]); }
    inline scalar & operator[](int i){ return array[i]; }
    inline const scalar operator[](int i) const{ return array[i]; }
    inline scalar & operator()(const int& i, const int& j){ return array[j*4+i]; }
    inline const scalar & operator()(const int& i, const int& j)const{ return array[j*4+i]; }
    void set_col(int i, const vec4& v){
      array[i*4]=v.x;
      array[i*4+1]=v.y;
      array[i*4+2]=v.z;
      array[i*4+3]=v.w;
    }
    void set_row(int i, const vec4& v){
      array[i]=v.x;
      array[i+4]=v.y;
      array[i+8]=v.z;
      array[i+12]=v.w;
    }
  
    mat4 tran() const{
      return mat4(array[0], array[4], array[8],  array[12],
		  array[1], array[5], array[9],  array[13],
		  array[2], array[6], array[10], array[14],
		  array[3], array[7], array[11], array[15]);
    }
    scalar det() const{ //  determinant
      return det_mat4(*this);
    }
    inline scalar operator~()const{ return det(); } //  determinant
    mat4 inv() const{
      mat4 r;
      inv_mat4(*this,r);
      return r;
    }
    bool isid() const{
      return (fabs(a00-1.0f)<cnst::one_eps&&fabs(a10     )<cnst::one_eps&&fabs(a20     )<cnst::one_eps&&
	      fabs(a30     )<cnst::one_eps&&fabs(a01     )<cnst::one_eps&&fabs(a11-1.0f)<cnst::one_eps&&
	      fabs(a21     )<cnst::one_eps&&fabs(a31     )<cnst::one_eps&&fabs(a02     )<cnst::one_eps&&
	      fabs(a12     )<cnst::one_eps&&fabs(a22-1.0f)<cnst::one_eps&&fabs(a32     )<cnst::one_eps&&
	      fabs(a03     )<cnst::one_eps&&fabs(a13     )<cnst::one_eps&&fabs(a23     )<cnst::one_eps&&
	      fabs(a33-1.0f)<cnst::one_eps);
    }
    void snull(){
      array[0]=0.0; array[4]=0.0; array[8]=0.0;  array[12]=0.0;
      array[1]=0.0; array[5]=0.0; array[9]=0.0;  array[13]=0.0;
      array[2]=0.0; array[6]=0.0; array[10]=0.0; array[14]=0.0;
      array[3]=0.0; array[7]=0.0; array[11]=0.0; array[15]=0.0;
    }
    void siden(){
      array[0]=1.0; array[4]=0.0; array[8]=0.0;  array[12]=0.0;
      array[1]=0.0; array[5]=1.0; array[9]=0.0;  array[13]=0.0;
      array[2]=0.0; array[6]=0.0; array[10]=1.0; array[14]=0.0;
      array[3]=0.0; array[7]=0.0; array[11]=0.0; array[15]=1.0;
    }
    // Modelview matrix
    void rotate(const vec3& axis, scalar angle){
      scalar rad=angle*cnst::to_rad;
      scalar c=cosf(rad), s=sinf(rad);
      vec3 v=axis; v.norm();
      scalar xy=v.x*v.y, yz=v.y*v.z, zx=v.z*v.x, xs=v.x*s, ys=v.y*s, zs=v.z*s;
      array[0]=(1.0f-c)*v.x*v.x+c; array[4]=(1.0f-c)*xy-zs;     array[8]=(1.0f-c)*zx+ys;      array[12]=0.0;
      array[1]=(1.0f-c)*xy+zs;     array[5]=(1.0f-c)*v.y*v.y+c; array[9]=(1.0f-c)*yz-xs;      array[13]=0.0;
      array[2]=(1.0f-c)*zx-ys;     array[6]=(1.0f-c)*yz+xs;     array[10]=(1.0f-c)*v.z*v.z+c; array[14]=0.0;
      array[3]=0.0;                array[7]=0.0;                array[11]=0.0;                array[15]=1.0;
    }
    void rotate(const mat3& M){ // copy the 3x3 rotation block
      a00=M.a00; a10=M.a10; a20=M.a20; a30=0.0;
      a01=M.a01; a11=M.a11; a21=M.a21; a31=0.0;
      a02=M.a02; a12=M.a12; a22=M.a22; a32=0.0;
      a03=0.0;   a13=0.0;   a23=0.0;   a33=1.0;
    }
    void rotate(const quat& q);
    void scale(const vec3 &v){
      array[0]=v.x; array[4]=0.0; array[8]=0.0;  array[12]=0.0;
      array[1]=0.0; array[5]=v.y; array[9]=0.0;  array[13]=0.0;
      array[2]=0.0; array[6]=0.0; array[10]=v.z; array[14]=0.0;
      array[3]=0.0; array[7]=0.0; array[11]=0.0; array[15]=1.0;
    }
    void translate(const vec3 &v){
      array[0]=1.0; array[4]=0.0; array[8]=0.0;  array[12]=v.x;
      array[1]=0.0; array[5]=1.0; array[9]=0.0;  array[13]=v.y;
      array[2]=0.0; array[6]=0.0; array[10]=1.0; array[14]=v.z;
      array[3]=0.0; array[7]=0.0; array[11]=0.0; array[15]=1.0;
    }
    void reflect(const vec4 &plane){
      scalar x2=plane.x*2.0f, y2=plane.y*2.0f, z2=plane.z*2.0f;
      array[0]=1.0f- plane.x*x2; array[4]=-plane.y*x2;     array[8]=-plane.z*x2;      array[12]=-plane.w*x2;
      array[1]=-plane.x*y2;      array[5]=1.0f-plane.y*y2; array[9]=-plane.z*y2;      array[13]=-plane.w*y2;
      array[2]=-plane.x*z2;      array[6]=-plane.y*z2;     array[10]=1.0f-plane.z*z2; array[14]=-plane.w*z2;
      array[3]=0.0;              array[7]=0.0;             array[11]=0.0;             array[15]=1.0;
    }
    void tangent_basis(const vec3& v0, const vec3& v1, const vec3& v2, const vec2& t0, const vec2& t1, const vec2& t2, const vec3& n){
      vec3 cp, e0(v1.x-v0.x, t1.s-t0.s, t1.t-t0.t), e1(v2.x-v0.x, t2.s-t0.s, t2.t-t0.t);
	
      cp=e0^e1;
      if(fabs(cp.x)>cnst::one_eps){ a00=-cp.y/cp.x; a10=-cp.z/cp.x; }

      e0.x=v1.y-v0.y;    e1.x=v2.y-v0.y;    cp=e0^e1;
      if(fabs(cp.x)>cnst::one_eps){ a01=-cp.y/cp.x; a11=-cp.z/cp.x; }

      e0.x=v1.z-v0.z;    e1.x=v2.z-v0.z;    cp=e0^e1;
      if(fabs(cp.x)>cnst::one_eps){ a02=-cp.y/cp.x; a12=-cp.z/cp.x; }

      scalar oonorm=1.0/sqrtf(a00*a00+a01*a01+a02*a02); // tangent...
      a00*=oonorm; a01*=oonorm; a02*=oonorm;

      oonorm=1.0/sqrtf(a10*a10+a11*a11+a12*a12); // binormal...
      a10*=oonorm; a11*=oonorm; a12*=oonorm;

      // normal...
      // compute the cross product TxB
      a20=a01*a12-a02*a11; a21=a02*a10-a00*a12; a22=a00*a11-a01*a10;

      oonorm=1.0/sqrtf(a20*a20+a21*a21+a22*a22);
      a20*=oonorm; a21*=oonorm; a22*=oonorm;

      // Gram-Schmidt orthogonalization process for B
      // compute the cross product B=NxT to obtain 
      // an orthogonal basis
      a10=a21*a02-a22*a01; a11=a22*a00-a20*a02; a12=a20*a01-a21*a00;

      if(a20*n.x+a21*n.y+a22*n.z<0.0){ a20=-a20; a21=-a21; a22=-a22; }
    }
    // Projection matrix
    void ortho(vec2 w, vec2 h, vec2 d){
      scalar r_l=w.right-w.left;
      scalar t_b=h.top-h.bottom;
      scalar f_n=d.pfar-d.pnear;
      //В таком виде эта функция точно соответствует GL-евской
  
      a00=2.0/r_l; a01=0.0;     a02=0.0;      a03=-(w.right+w.left)/r_l; // Здесь, по идее, минус должен быть
      a10=0.0;     a11=2.0/t_b; a12=0.0;      a13=-(h.top+h.bottom)/t_b; // Здесь, по идее, минус должен быть
      a20=0.0;     a21=0.0;     a22=-2.0/f_n; a23=-(d.pfar+d.pnear)/f_n; // Здесь, по идее, минус должен быть
      a30=0.0;     a31=0.0;     a32=0.0;      a33=1.0; // Может тут минус, не знаю, в разных мануалах поразному.
    }
    void frustum(vec2& w, vec2& h, vec2& d){
      scalar r_l=w.right-w.left, t_b=h.top-h.bottom, f_n=d.pfar-d.pnear, n2=d.pnear*2.0;
      a00=(n2)/(r_l);               a10=0.0;                    a20=0.0;                     a30=0.0;
      a01=0.0;                      a11=(n2)/(t_b);             a21=0.0;                     a31=0.0;
      a02=(w.right+w.left)/(r_l);   a12=(h.top+h.bottom)/(t_b); a22=-(d.pfar+d.pnear)/(f_n); a32=-1.0;
      a03=0.0;                      a13=0.0;                    a23=-(n2*d.pfar)/(f_n);      a33=0.0;
    }
    void persp(scalar fov, scalar aspect, vec2& d){
      scalar pfov;
      if(fabs(fov-90.0f)<cnst::one_eps)pfov=89.9f; else pfov=fov;
      scalar y=tan(pfov*cnst::one_pi/360.0f);
      scalar x=y*aspect;
      scalar f_n=d.pfar-d.pnear;
      array[0]=1.0f/x; array[4]=0.0;    array[8]=0.0;                      array[12]=0.0;
      array[1]=0.0;    array[5]=1.0f/y; array[9]=0.0;                      array[13]=0.0;
      array[2]=0.0;    array[6]=0.0;    array[10]=-(d.pfar+d.pnear)/(f_n); array[14]=-(2.0f*d.pfar*d.pnear)/(f_n);
      array[3]=0.0;    array[7]=0.0;    array[11]=-1.0;                    array[15]=0.0;
    }
    void lookat(vec3 &eye, vec3 &dir, vec3 &up){
      vec3 x,y,z;
      mat4 m0,m1;
      z=eye-dir; z.norm();
      x=up^z;    x.norm();
      y=z^x;     y.norm();
      m0[0]=x.x; m0[4]=x.y; m0[8] =x.z; m0[12]=0.0;
      m0[1]=y.x; m0[5]=y.y; m0[9] =y.z; m0[13]=0.0;
      m0[2]=z.x; m0[6]=z.y; m0[10]=z.z; m0[14]=0.0;
      m0[3]=0.0; m0[7]=0.0; m0[11]=0.0; m0[15]=1.0;
      m1.translate(-eye);
      *this=m0*m1;
    }
    //tolua_end
    union{ // data cells
      struct{ // standard names for components
	//tolua_begin
	scalar a00, a10, a20, a30;
	scalar a01, a11, a21, a31;
	scalar a02, a12, a22, a32;
	scalar a03, a13, a23, a33;
	//tolua_end
      };
      struct{
	//tolua_begin
	scalar _11, _12, _13, _14;
	scalar _21, _22, _23, _24;
	scalar _31, _32, _33, _34;
	scalar _41, _42, _43, _44;
	//tolua_end
      };
      struct{
	//tolua_begin
	scalar b00, b10, b20, p; // texture matrix
	scalar b01, b11, b21, q;
	scalar b02, b12, b22, r;
	scalar x,   y,   z,   w;
	//tolua_end
      };
      scalar array[16]; // array access //tolua_export
    };
    //tolua_begin
    // documented
    static string __info(string);
    // constants
    static tolua_readonly mat4 one;
    static tolua_readonly mat4 id;
    static tolua_readonly mat4 null;
    static tolua_readonly mat4 nul;
    static tolua_readonly mat4 scale_bias;
    //
    operator string()const;
  };

  //tolua_end

  inline mat4 operator*(const scalar& s, const mat4& m){ return m*s; }

}//tolua_export

