//
// Tools functional

// Scalar functions
UNMATH_PFUNC(scalar,sqrtf_scal,(const scalar f));
UNMATH_PFUNC(scalar,oo_scal,(const scalar f));

// Length vectors
UNMATH_PFUNC(scalar,len_vec3,(const vec3& v));
UNMATH_PFUNC(scalar,len_vec4,(const vec4& v));
// Normalize vectors
UNMATH_PFUNC(void,norm_vec3,(vec3& v));
UNMATH_PFUNC(void,norm_vec4,(vec4& v));
// Arithmetic
UNMATH_PFUNC(vec3&,sub_vec3_vec3,(vec3& r, const vec3& v1, const vec3& v2));
//UNMATH_PFUNC(vec3&,subm_vec3_vec3,(vec3* r, const vec3* v1, const vec3* v2, unsigned int count));
//UNMATH_PFUNC(vec4&,sub_vec4_vec4,(vec4& r, const vec4& v1, const vec4& v2));

UNMATH_PFUNC(scalar&,dot_vec3_vec3,(scalar&,const vec3&,const vec3&));
UNMATH_PFUNC(vec3&,cross_vec3_vec3,(vec3&,const vec3&,const vec3&));

UNMATH_PFUNC(void,dot_vec4_vec4,(const vec4& v0, const void *v1, int v1_stride, void *result, int result_stride, int count));

// 3D Operations
/* mat4 begin */
UNMATH_PFUNC(void,mul_mat4_vec3,(const mat4& m, const void *v, int v_stride, void *result, int result_stride, int count));
UNMATH_PFUNC(void,mul_mat4_vec4,(const mat4& m, const void *v, int v_stride, void *result, int result_stride, int count));
UNMATH_PFUNC(void,mul_mat4_scal,(const mat4&, const scalar&, mat4&));
UNMATH_PFUNC(void,mul_mat4_mat4,(const mat4& m0, const mat4& m1, mat4& r0));
UNMATH_PFUNC(void,add_mat4_mat4,(const mat4& m0, const mat4& m1, mat4& r0));
UNMATH_PFUNC(void,sub_mat4_mat4,(const mat4& m0, const mat4& m1, mat4& r0));
UNMATH_PFUNC(scalar,det_mat4,(const mat4& m));
UNMATH_PFUNC(void,inv_mat4,(const mat4& m, mat4& r));
/* mat4 end */
// Geometry
UNMATH_PFUNC(vec3,tri_normal,(const vec3& v1, const vec3& v2, const vec3& v3)); // computes normal to polygon
UNMATH_PFUNC(scalar,tri_area,(const vec3& v1, const vec3& v2, const vec3& v3)); // computes the area of a triangle
UNMATH_PFUNC(scalar,tri_perim,(const vec3& v1, const vec3& v2, const vec3& v3));// computes the perimeter of a triangle
