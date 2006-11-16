#pragma once

namespace unmath{//tolua_export
  class vec4{//tolua_export
  public:
    //tolua_begin
    inline vec4(): x(0.0f), y(0.0f), z(0.0f), w(1.0f) { }
    inline vec4(scalar x, scalar y, scalar z, scalar w):x(x), y(y), z(z), w(w) { }
    inline vec4(const scalar* xyzw): x(xyzw[0]), y(xyzw[1]), z(xyzw[2]), w(xyzw[3]) { }//tolua_noexport
    inline vec4(const vec2& u): x(u.x), y(u.y), z(0.0f),w(1.0f) { }
    inline vec4(const vec3& u): x(u.x), y(u.y), z(u.z), w(1.0f) { }
    inline vec4(const vec4& u): x(u.x), y(u.y), z(u.z), w(u.w) { }
    // Operations
    inline bool operator==(const vec4& v)const{ return (fabs(x-v.x)<cnst::one_eps&&fabs(y-v.y)<cnst::one_eps&&fabs(z-v.z)<cnst::one_eps&&fabs(w-v.w)<cnst::one_eps); }
    inline bool operator!=(const vec4& v)const{ return !(*this==v); }//tolua_noexport
    // Typecasting
    //tolua_end
    inline operator scalar*(){ return array; }
    inline operator const scalar*() const{ return array; }
    //tolua_begin
    // Computation
    const vec4 operator*(const mat4&)const;
    inline const vec4 operator*(scalar f) const{ return vec4(x*f, y*f, z*f, w*f); }
    inline const vec4 operator/(scalar f) const{ return vec4(x/f, y/f, z/f, w/f); }
    inline const vec4 operator+(const vec4& v) const{ return vec4(x+v.x, y+v.y, z+v.z, w+v.w); }
    inline const vec4 operator-() const{ return vec4(-x,-y,-z,-w); }
    //inline const vec4 operator-(const vec4 v) const{ return vec4(x-v.x, y-v.y, z-v.z, z-v.w); }
    inline const vec4 operator-(const vec4& v) const{ return vec4(x-v.x, y-v.y, z-v.z, z-v.w); }
    inline const vec4 operator^(const vec4& v){ return vec4(y*v.z-z*v.y, z*v.x-x*v.z, x*v.y-y*v.x, w); } // Cross product
    //tolua_end
    inline vec4 &operator*=(float f){ return *this=*this*f; }
    inline vec4 &operator/=(float f){ return *this=*this/f; }
    inline vec4 &operator+=(const vec4& v){ return *this=*this+v; }
    inline vec4 &operator-=(const vec4& v){ return *this=*this-v; }
    //tolua_begin
    inline scalar operator*(const vec3& v) const{ return x*v.x+y*v.y+z*v.z+w; }
    inline scalar operator*(const vec4& v) const{ return x*v.x+y*v.y+z*v.z+w*v.w; }
    // Indexing
    inline scalar& operator[](int i){ return array[i]; }
    inline const scalar operator[](int i)const{ return array[i]; }
    // Methods
    inline scalar sqlen() const{ return scalar(x*x+y*y+z*z+w*w); }
    inline scalar len()   const{ return len_vec4(*this)/*sqrtf(sqlen())*/; } // lenght
    inline scalar operator~()const{ return len(); } // lenght
    inline vec4& norm(){ norm_vec4(*this); /*(*this)*=oo_scalar(len());*/ return *this; }
    inline vec4 sat(){ // Saturate vector    
      vec4 r;
      saturation_macros(r,x);
      saturation_macros(r,y);
      saturation_macros(r,z);
      saturation_macros(r,w);
      return r;
    }
    //tolua_end
    // data cells
    union{
      struct { // space coordinates
        scalar x,y,z,w;//tolua_export
      };
      struct { // texture coordinates
	scalar s,t,r,q;//tolua_export
      };
      struct { // color components
	scalar R,G,B,A;//tolua_export
      };
      struct { // for clipping and widgets
	scalar left,right,top,bottom;//tolua_export
      };
      struct { // Plane params
	scalar a,b,c,d;//tolua_export
      };
      scalar array[4];//tolua_export
    };
    //tolua_begin
    // documented
    static string __info(string);
    // constants
    static tolua_readonly vec4 null;
    static tolua_readonly vec4 nul;
    static tolua_readonly vec4 one;
    static tolua_readonly vec4 px;
    static tolua_readonly vec4 nx;
    static tolua_readonly vec4 py;
    static tolua_readonly vec4 ny;
    static tolua_readonly vec4 pz;
    static tolua_readonly vec4 nz;
    static tolua_readonly vec4 pw;
    static tolua_readonly vec4 nw;
    
    operator string() const;
  };
  //tolua_end

  inline const vec4 operator*(const scalar f, const vec4& u){ return u*f; }

  // Addition for vec2 and vec3
  inline vec3::vec3(const vec4& u){ x=u.x; y=u.y; z=u.z; }
  inline vec2::vec2(const vec4& u){ x=u.x; y=u.y; }

  inline scalar vec3::operator*(const vec4 &v) const{ return x*v.x+y*v.y+z*v.z+v.w; }
  //inline vec2::vec2(const vec3& u){ scalar k=1/u.z; x=k*u.x; y=k*u.y; }// projection

}//tolua_export
