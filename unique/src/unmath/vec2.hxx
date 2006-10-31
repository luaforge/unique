#pragma once

//tolua_begin
namespace unmath{
  class vec2{
  public:
    inline vec2():x(0.0),y(0.0){}
    inline vec2(scalar x,scalar y):x(x),y(y){}
    inline vec2(const scalar* xy):x(xy[0]),y(xy[1]){}//tolua_noexport
    inline vec2(const vec2& u):x(u.x),y(u.y){}
    inline vec2(const vec3&);
    inline vec2(const vec4&);
    // Operations
    inline bool operator==(const vec2& v)const{ return ((fabs(x-v.x)<cnst::one_eps)&&(fabs(y-v.y)<cnst::one_eps)); }
    //tolua_end
    inline bool operator!=(const vec2& v)const{ return !(*this==v); }
    // Typecasting
    inline operator scalar*(){ return array; } // to scalar*
    inline operator const scalar*() const{ return array; }
    //tolua_begin
    // Calculations
    inline vec2 operator+(const vec2&v)const{ return vec2(x+v.x,y+v.y); } // add
    inline vec2 operator+(const scalar f) const{ return vec2(x+f, y+f); }  // add scalar
    inline vec2 operator-() const{ return vec2(-x,-y); } // inversion
    inline vec2 operator-(const vec2&v) const{ return vec2(x-v.x, y-v.y); } // sub
    inline vec2 operator*(scalar f) const{ return vec2(x*f, y*f); }// mult on scalar
    inline vec2 operator/(scalar f) const{ return vec2(x/f, y/f); }
    inline vec2 operator%(const vec2&v)const{return vec2(x*v.x,y*v.y);}// mult product
    inline scalar operator*(const vec2&v) const{ return scalar(x*v.x+y*v.y); } // dot product
    inline vec2 operator^(const vec2&v){ return vec2(x*v.y-y*v.x, y*v.x-x*v.y); }// cross product
    inline vec2 operator/(const vec2&v){ return vec2(x/v.x, y/v.y); }
    //tolua_end
    inline vec2 &operator*=(float f){ return *this=*this*f; }
    inline vec2 &operator/=(float f){ return *this=*this/f; }
    inline vec2 &operator^=(const vec2 &v){ return *this=*this^v; }
    inline vec2 &operator+=(const vec2 &v){ return *this=*this+v; }
    inline vec2 &operator-=(const vec2 &v){ return *this=*this-v; }
    inline vec2 &operator*=(const vec2 &v){ x*=v.x; y*=v.y; return *this; } // mult product
    // Accessing
    //tolua_begin
    inline scalar& operator[](int i){ return array[i]; }
    inline const scalar operator[](int i)const{ return array[i]; }
    // Methods
    inline scalar sqlen()const{ return scalar(x*x+y*y); } // square vector length
    inline scalar len()  const{ return sqrtf(sqlen()); }  // lenght
    inline scalar operator~()const{ return len(); } // lenght
    inline vec2&  norm(){ (*this)*=oo_scalar(len()); return *this; } // normalize vector
    inline vec2   sat(){ vec2 r=(*this); // saturate vector    
      saturation_macros(r,x);
      saturation_macros(r,y);
      return r;
    }
    inline vec2&  scale(vec2& v){ x*=v.x; y*=v.y; return *this; }
    inline vec2&  dec2pol(){ // convert vector from decart to polar coords
      scalar length=len(); angle=atan(x/y); radius=length; return *this;
    }
    inline vec2&  pol2dec(){ // convert vector from polar to decart coords
      scalar length=radius; x=length*cos(angle); y=length*sin(angle); return *this;
    }
    inline vec2&  rotate(scalar fov){
      dec2pol(); angle+=fov; pol2dec(); return *this; }
    // data cells
    //tolua_end
    union{ // standard names for components
      struct{ // Space components
	scalar x,y; //tolua_export
      };
      struct{ // Texture components
	scalar s,t; //tolua_export
      };
      struct{ // UV map components
	scalar u,v; //tolua_export
      };
      struct{ // Color   components
	scalar G,A; //tolua_export
      };
      struct{
	scalar a,b; //tolua_export
      };
      struct{ // For widgets and clipping
	scalar left,   right; //tolua_export
      };
      struct{ // For widgets and clipping
	scalar width,  height; //tolua_export
      };
      struct{ // For widgets and clipping
	scalar bottom, top; //tolua_export
      };
      struct{ // For widgets and clipping
	scalar pnear,  pfar; //tolua_export
      };
      struct{ // For polar coords
	scalar radius, angle; //tolua_export
      };
      struct{ // For cylinder params
	scalar _hook_, length; //tolua_export
      };
      // Sic! Angle in radians
      // Array access
      scalar array[2]; //tolua_export
    };
    //tolua_begin
    // documented
    static string __info(string);
    //constants
    static tolua_readonly vec2 null;
    static tolua_readonly vec2 nul;
    static tolua_readonly vec2 one;
    static tolua_readonly vec2 px;
    static tolua_readonly vec2 py;
    static tolua_readonly vec2 nx;
    static tolua_readonly vec2 ny;
  
    operator string()const;
  };
  //tolua_end

  inline const vec2 operator*(const scalar f, const vec2& u){ return u*f; }

}//tolua_export
