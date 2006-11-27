#pragma once

namespace unmath{
  class LINE{
  public:
    vec3 v[2];
    // Accessing
    vec3& operator[](int i){return v[i];}
    const vec3 operator[](int i)const{return v[i];}
    inline operator scalar*(){return (scalar*)v;}
    inline operator const scalar*()const{return (scalar*)v;}
  };

  class TRIANGLE{
  public:
    //
    //  0000--00  -  split (-(-front)+(-back);front&back)
    //  0000--01  -  front
    //  0000--10  -  back
    //  0000--11  -  on (front+back;front|back)
    //  000001--  -  vert
    //  000010--  -  edge
    //
    enum {
      FRONT=0x1, // Front
      BACK =0x2, // Back
      VERT =0x4, // Polygon vertex on this polygon
      EDGE =0x8, // Polygon edge on this polygon
      ON   =0x3, // Point on polygon or polygon coinsident polygon
      SPLIT=0x0, // Polygon split this polygon
    };
  public:
    vec3 v[3];
  public:
    TRIANGLE();
    TRIANGLE(const vec3&,const vec3&,const vec3&);
    ~TRIANGLE();

    // Accessing
    vec3& operator[](int i){return v[i];}
    const vec3 operator[](int i)const{return v[i];}
    inline operator scalar*(){return (scalar*)v;}
    inline operator const scalar*()const{return (scalar*)v;}

    inline vec3 normal(){return (v[1]-v[0])^(v[2]-v[0]);}
    inline scalar distant(const vec3& p){return (p-v[0])*normal();}
    char where(const vec3&);     // Point front or back or on polygon
    char where(const TRIANGLE&); // Polygon front or back or on or split polygon
    void shadow(vec3*,const vec3&,scalar);
    bool intersect(const vec3&);       // Point in triangle
    bool collision(vec3&,const LINE&); // Collision line and triangle
  };
  typedef TRIANGLE POLYGON;
}
