#pragma once

namespace unmath{//tolua_export
  //operations
  extern quat& add_quats(quat& p, const quat& q1, const quat& q2);
  extern scalar dot(const quat& p, const quat& q);
  extern quat& dot(scalar s, const quat& p, const quat& q);
  extern quat& slerp_quats(quat& p, scalar s, const quat& q1, const quat& q2);
  extern quat& axis_to_quat(quat& q, const vec3& a, const scalar phi);
  extern mat3& quat_2_mat(mat3& M, const quat& q);
  extern quat& mat_2_quat(quat& q, const mat3& M);
  extern quat sph_2_quat(vec3 spherical);
  extern quat sph_2_quat(scalar latitude, scalar longitude, scalar angle);
  extern quat euler_2_quat(vec3 euler);
  extern quat euler_2_quat(scalar roll, scalar pitch, scalar yaw);
  //tolua_begin
  class quat{ //     Quaternion
  public:
    quat():x(0.0),y(0.0),z(0.0),w(1.0){}
    //tolua_end
    quat(const double* xyzw):x(xyzw[0]),y(xyzw[1]),z(xyzw[2]),w(xyzw[3]){}
    quat(const scalar* xyzw):x(xyzw[0]),y(xyzw[1]),z(xyzw[2]),w(xyzw[3]){}
    //tolua_begin
    quat(scalar x,scalar y,scalar z,scalar w):x(x),y(y),z(z),w(w){}
    quat(const quat& q):x(q.x),y(q.y),z(q.z),w(q.w){}
    quat(const vec3& dir, scalar angle){axis(dir,angle);}
    quat(const mat3& r){rmat3(r);}
    // Operations
    inline bool operator==(const quat& q)const{ return (fabs(x-q.x)<cnst::one_eps&&fabs(y-q.y)<cnst::one_eps&&fabs(z-q.z)<cnst::one_eps&&fabs(w-q.w)<cnst::one_eps); }
    //tolua_end
    inline bool operator!=(const quat& q)const{ return !(*this==q); }
    // Operations
    quat& operator*=(const scalar a){ x*=a; y*=a; z*=a; w*=a; return *this; }
    quat& operator=(const quat& q){ x=q.x; y=q.y; z=q.z; w=q.w; return *this; }
    //tolua_begin
    quat operator-(){ return quat(-x, -y, -z, -w); }
    quat conj(){ return quat(-x, -y, -z, w); }
    quat operator+(const quat& q){
      quat t1=*this, t2=q;
      t1.x*=q.w; t1.y*=q.w; t1.z*=q.w;
      t2.x*=w;   t2.y*=w;   t2.z*=w;
      return quat((q.y*z)-(q.z*y)+t1.x+t2.x,
		  (q.z*x)-(q.x*z)+t1.y+t2.y,
		  (q.x*y)-(q.y*x)+t1.z+t2.z,
		  w*q.w-(x*q.x+y*q.y+z*q.z));
    }
    // Typecasting
    //tolua_end
    inline operator scalar*(){return array;}
    inline operator const scalar*()const{return array;}
    //tolua_begin
    // Math
    void slerp(const quat &q0, const quat &q1, scalar t){
      scalar k0,k1,cosomega=q0.x*q1.x+q0.y*q1.y+q0.z*q1.z+q0.w*q1.w;
      quat q;
      if(cosomega<0.0){
	cosomega=-cosomega;
	q.x=-q1.x;
	q.y=-q1.y;
	q.z=-q1.z;
	q.w=-q1.w;
      }else{
	q.x=q1.x;
	q.y=q1.y;
	q.z=q1.z;
	q.w=q1.w;
      }
      if(1.0-cosomega>1e-6){
	scalar omega=acos(cosomega);
	scalar sinomega=sin(omega);
	k0=sin((1.0f-t)*omega)/sinomega;
	k1=sin(t*omega)/sinomega;
      }else{
	k0=1.0f-t;
	k1=t;
      }
      x=q0.x*k0+q.x*k1;
      y=q0.y*k0+q.y*k1;
      z=q0.z*k0+q.z*k1;
      w=q0.w*k0+q.w*k1;
    }
    quat operator*(const quat &q) const{ // Multiply quaternions
      return quat(w*q.x+x*q.w+y*q.z-z*q.y,
		  w*q.y+y*q.w+z*q.x-x*q.z,
		  w*q.z+z*q.w+x*q.y-y*q.x,
		  w*q.w-x*q.x-y*q.y-z*q.z); }
    quat& operator*=(const quat& q){ return *this=*this*q; }//tolua_noexport
    quat inv(){ return quat(-x, -y, -z, w); }
    //vec4 axis();
    void axis(const vec3 &dir, scalar angle){
      scalar len=dir.len();
      if(len!=0.0){
	scalar half_angle=0.5f*angle*cnst::to_rad;
	len=1.0f/len;
	scalar sinangle=sinf(half_angle);
	x=dir[0]*len*sinangle;
	y=dir[1]*len*sinangle;
	z=dir[2]*len*sinangle;
	w=cosf(half_angle);
      }else{
	x=y=z=0.0;
	w=1.0;
      }
      //scalar half_angle=0.5*angle*to_rad;
      //scalar s=cosf(half_angle);
      //vec3 v=dir*sinf(half_angle)/dir.len();
    }
    inline void axis(vec4 a){axis(vec3(a),a.w);}
    inline void sphere(vec3 s){*this=sph_2_quat(s);}
    inline void euler(vec3 e){*this=euler_2_quat(e);}
    scalar sqlen() const{ return x*x+y*y+z*z+w*w; }
    scalar len()   const{ return sqrtf(sqlen()); }
    inline scalar operator~()const{ return len(); }
    quat& norm(){ (*this)*=oo_scalar(len()); return *this; }

    // Convert matrix
    void rmat3(const mat3& m){
      scalar trace=m[0]+m[4]+m[8];
      if(trace>0.0){
	scalar s=sqrt(trace+1.0f);
	array[3]=0.5f*s;
	s=0.5f/s;
	array[0]=(m[5]-m[7])*s;
	array[1]=(m[6]-m[2])*s;
	array[2]=(m[1]-m[3])*s;
      }else{
	static int next[3]={1,2,0};
	int i=0;
	if(m[4]>m[0])i=1;
	if(m[8]>m[3*i+i])i=2;
	int j=next[i];
	int k=next[j];
	scalar s=sqrt(m[3*i+i]-m[3*j+j]-m[3*k+k]+1.0f);
	array[i]=0.5f*s;
	if(s!=0)s=0.5f/s;
	array[3]=(m[3*j+k]-m[3*k+j])*s;
	array[j]=(m[3*i+j]+m[3*j+i])*s;
	array[k]=(m[3*i+k]+m[3*k+i])*s;
      }
    }
  
    // Accessing
    scalar& operator[](int i) { return array[i]; }
    const scalar operator[](int i) const { return array[i]; }
    //tolua_end
    union{// data cells
      struct{
	scalar x, y, z, w;//tolua_export
      };
      scalar array[4];//tolua_export
    };
    //tolua_begin
    // documented
    static string __info(string);
    // constants
    static tolua_readonly quat id;
    //
    operator string()const;
  };
}
//tolua_end
