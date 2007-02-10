#pragma once

//tolua_begin
namespace unmath{
  class vec3{
  public:
    inline vec3():x(0.0),y(0.0),z(0.0){}
    inline vec3(scalar x,scalar y,scalar z):x(x),y(y),z(z){}
    inline vec3(const scalar*xyz):x(xyz[0]),y(xyz[1]),z(xyz[2]){} //tolua_noexport
    inline vec3(const vec2& u):x(u.x),y(u.y),z(1.0f){}
    inline vec3(const vec3& u):x(u.x),y(u.y),z(u.z){}
    inline vec3(const vec4&);
    // Operations
    inline bool operator==(const vec3&v)const{return(fabs(x-v.x)<cnst::one_eps&&fabs(y-v.y)<cnst::one_eps&&fabs(z-v.z)<cnst::one_eps);}
    inline bool operator!=(const vec3&v)const{return(!(*this==v));}//tolua_noexport
    ////////inline bool operator~(const vec3&v)const{}
    //inline bool collin(const vec3&v)const{return(*this==v || *this==-v);} // Collinear
    inline bool collin(const vec3&v)const{return((*this^v).len()<cnst::one_eps);} // Collinear
    // Typecasting
    //tolua_end
    inline operator scalar*(){ return array; }
    inline operator const scalar*() const{ return array; }
    //tolua_begin
    // Computations
    vec3 operator*(const mat3& m)const;
    vec3 operator*(const mat4& m)const;
    inline vec3 operator*(scalar f)const{ return vec3(x*f,y*f,z*f); }
    inline vec3 operator/(scalar f)const{ return vec3(x/f,y/f,z/f); }
    inline vec3 operator+(const vec3& v)const{ return vec3(x+v.x,y+v.y,z+v.z); }
    inline vec3 operator+(const scalar f)const{ return vec3(x+f, y+f, z+f); }  // Add scalar
    inline vec3 operator-()const{return vec3(-x,-y,-z);}
    inline vec3 operator-(const vec3& v)const{ return vec3(x-v.x, y-v.y, z-v.z); }
    inline vec3 operator^(const vec3& v)const{ vec3 r; return cross_vec3_vec3(r,*this,v); } // Cross product
    inline scalar operator*(const vec3& v)const{ scalar r; return dot_vec3_vec3(r,*this,v); } // Dot product
    inline const vec3 operator%(const vec3& v)const{return vec3(x*v.x,y*v.y,z*v.z);}// Mult product
    inline scalar operator*(const vec4& v) const;
    //tolua_end
    inline vec3 &operator*=(scalar f){ return *this=*this*f; }
    inline vec3 &operator/=(scalar f){ return *this=*this/f; }
    inline vec3 &operator+=(const vec3& v){ return *this=*this+v; }
    inline vec3 &operator-=(const vec3& v){ return *this=*this-v; }
    inline vec3 &operator*=(const vec3& v){ x*=v.x; y*=v.y; z*=v.z; return *this; } // Mult product
    //tolua_begin
    // Accessing
    inline scalar& operator[](int i){ return array[i]; }
    inline const scalar operator[](int i) const { return array[i]; }
    // Methods
    inline scalar sqlen() const{ scalar l=len_vec3(*this); return l*l; }
    inline scalar len()   const{ return len_vec3(*this); } // lenght
    inline scalar operator~()const{ return len(); } // lenght
    inline vec3& norm(){ norm_vec3(*this); return *this; }//{ (*this)*=oo_scalar(len()); return *this; }
    //  inline void orthogon(const vec3& v); //  just orthogonalize
    //inline void orthonorm(const vec3& v){
    //  orthogon(v); //  just orthogonalize...
    //  norm();   //  ...and normalize it
    //}
    inline vec3 sat(){
      vec3 r=(*this); // Saturate vector    
      saturation_macros(r,x);
      saturation_macros(r,y);
      saturation_macros(r,z);
      return r;
    }
    //tolua_end
    union{ // data cells
      struct{ // standard names for coord components
	scalar x,y,z; //tolua_export
      };
      struct{ // standard names for texture components
	scalar s,t,r; //tolua_export
      };
      struct{ // standard names for uvw components
	scalar u,v,w; //tolua_export
      };
      struct{ // standard names for color components
	scalar R,G,B; //tolua_export
      };
      struct{
	scalar a,b,c; //tolua_export
      };
      struct{ // euler angle components
	scalar roll, pitch, yaw; //tolua_export
      };
      struct{ // sphere angle components
	scalar latitude, longitude, angle; //tolua_export
      };
      struct{ // For widgets and clipping
	scalar width, height, depth; //tolua_export
      };
      scalar array[3]; //tolua_export
    };
    //tolua_begin
    // documented
    static string __info(string);
    // constants
    static tolua_readonly vec3 null;
    static tolua_readonly vec3 nul;
    static tolua_readonly vec3 one;
    static tolua_readonly vec3 px;
    static tolua_readonly vec3 py;
    static tolua_readonly vec3 pz;
    static tolua_readonly vec3 nx;
    static tolua_readonly vec3 ny;
    static tolua_readonly vec3 nz;
    static tolua_readonly vec3 at;
    static tolua_readonly vec3 dir;
    static tolua_readonly vec3 up;
    //
    operator string() const;
  };
  //tolua_end

  inline vec2::vec2(const vec3& u){ x=u.x; y=u.y; }

  inline const vec3 operator*(const scalar f, const vec3& u){ return u*f; }
  //inline const vec3 operator^(const vec3& u, const vec3& v){ return vec3(u.y*v.z-u.z*v.y, u.z*v.x-u.x*v.z, u.x*v.y-u.y*v.x); }

}//tolua_export
