#pragma once

namespace unmath{
  // Optional tools
  /* Coord system window and opengl geometry */
  extern vec2 glfW2GL(vec2 p, vec2 wh); // Convert window coords to opengl
  extern vec2 glfGL2W(vec2 p, vec2 wh); // Convert opengl coords to window
  /* linear interpolation */
  inline scalar lerp(scalar t, scalar a, scalar b){ return a*(1.0-t)+t*b; }
  inline vec3& lerp(vec3& w, const scalar& t, const vec3& u, const vec3& v){ w.x=lerp(t, u.x, v.x); w.y=lerp(t, u.y, v.y); w.z=lerp(t, u.z, v.z); return w; }
  inline vec4& lerp(vec4& w, const scalar& t, const vec4& u, const vec4& v){ w.x=lerp(t, u.x, v.x); w.y=lerp(t, u.y, v.y); w.z=lerp(t, u.z, v.z); w.w=lerp(t, u.w, v.w); return w; }
  /* utilities */
  inline scalar v_min(const scalar& lambda, const scalar& n){ return (lambda<n)?lambda:n; }
  inline scalar v_max(const scalar& lambda, const scalar& n){ return (lambda>n)?lambda:n; }
  inline scalar v_clamp(scalar u, const scalar min, const scalar max){ u=(u<min)?min:u; u=(u>max)?max:u; return u; }
  inline scalar v_random(){ // Randomize
    const int HALF_RAND=(RAND_MAX/2);
    return (scalar(rand()-HALF_RAND)/scalar(HALF_RAND));
  }
  /* Componentwise maximum and minium */
  inline void v_max(vec3& vOut, const vec3& vFirst, const vec3& vSecond){
    vOut.x=v_max(vFirst.x, vSecond.x);
    vOut.y=v_max(vFirst.y, vSecond.y);
    vOut.z=v_max(vFirst.z, vSecond.z);
  }
  inline void v_min(vec3& vOut, const vec3& vFirst, const vec3& vSecond){
    vOut.x=v_min(vFirst.x, vSecond.x);
    vOut.y=v_min(vFirst.y, vSecond.y);
    vOut.z=v_min(vFirst.z, vSecond.z);
  }

  
  // Decompose Affine Matrix 
  //   A=TQS, where
  // A is the affine transform
  // T is the translation vector
  // Q is the rotation (quaternion)
  // S is the scale vector
  // f is the sign of the determinant
  extern void decomp_affine(const mat4& A, vec3& T, quat& Q, quat& U, vec3& S, scalar& f);
  // quaternion
  extern quat& conj(quat& p);
  extern quat& conj(quat& p, const quat& q);
  extern quat& add_quats(quat& p, const quat& q1, const quat& q2);
  extern quat& axis_to_quat(quat& q, const vec3& a, const scalar phi);
  extern mat3& quat_2_mat(mat3&M, const quat&q);
  extern quat& mat_2_quat(quat&q,const mat3&M);
  extern quat& mat_2_quat(quat&q,const mat4&M);
  // surface properties
  extern mat3& tangent_basis(mat3& basis,const vec3& v0,const vec3& v1,const vec3& v2,const vec2& t0,const vec2& t1,const vec2& t2, const vec3& n);

  extern quat& trackball(quat& q, vec2& pt1, vec2& pt2, scalar trackballsize);
  extern vec3& cube_map_normal(int i, int x, int y, int cubesize, vec3& v);
  // geometry
  extern vec3& reflect(vec3& r, const vec3& n, const vec3& l); // compute reflect vector
  // triangles

  // analysis
  extern scalar tri_sprain(const vec3& v1, const vec3& v2, const vec3& v3); // compute sprain triangle (area attitude to perimeter)

  extern scalar find_in_circle(vec3& center, const vec3& v1, const vec3& v2, const vec3& v3);// find the inscribed circle
  extern scalar find_circ_circle(vec3& center, const vec3& v1, const vec3& v2, const vec3& v3);// find the circumscribed circle
  extern scalar fast_cos(const scalar x);
  extern scalar ffast_cos(const scalar x);
  extern scalar fcos(const scalar x);
}
