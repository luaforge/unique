/************************************************Fenix***

Header file: meshgeom.hpp

Copyleft (C) 2005 RareSky Zone

Comments:
    It is module for.

Bug report to:
    tonder@trktvs.ru

Author:
    Fenix R.S.

**********************************************************/

#pragma once
#include"unobj.hxx"

//#define MESH_TEST_MODE

namespace ungeom{//tolua_export
  /*
   *  Poligonal geometry chunk
   */
  class CHUNK{//tolua_export
  public:
    //tolua_begin
    enum { // type of chunk
      vertex=0x0,   // vertexes
      normal=0x1,   // normals
      binormal=0x2, // binormals
      tangent=0x3,  // tangents
      texcoord=0x4, // texture coords
      element=0x5,  // face elements (triangle's vertex indexes)
      material=0x6, // material's indexes
      bone=0x7,     // bone's indexes
      weight=0x8,   // weights
    };
    // Chunk properties
    /* field :  full 
       size  : segment
       _____ : length
       _______________*/
    /*   4   :    4   */unsigned int  id;     // Attrib identifier
    /*   4   :    8   */unsigned int  surf;   // Surface identifier
    /*   1   :    9   */unsigned char type;   // Chunk type
    /*   1   :   10   */unsigned char seq;    // Sequence number
    /*   1   :   11   */unsigned char format; // Component format (or byte per number)
    /*   1   :   12   */unsigned char compon; // Count components per element
    /*   4   :   16   */unsigned int  size;   // Data size
    unsigned int lim;  // Data byte count
    unsigned int glid; // OpenGL identifier
    void*        data; // Data pointer
    void*        offset; // Data offset
    // Chunk methods
    CHUNK();
    ~CHUNK();
    void init();
    void dest();
    //tolua_end
  };//tolua_export
  /*
   *  Poligonal surface
   */
  class SURFACE{//tolua_export
  public:
    vector<CHUNK*> attrib;
    //tolua_begin
    bool smooth;
    unvis::MATERIAL* mat;
    unsigned int maxangle;
    //tolua_end
    vector<unsigned int> nocoincidedvertex;
    vector<vector<unsigned int> > coincidedvertex; // Coincided vertex table
    /*
     *   Coincided vertex table
     *  ________________________________________________________
     * | array entry 1 | vertex index 1 | vertex index 2 | .....
     * |---------------+----------------+----------------+------
     * | array entry 2 | vertex index 1 | .....
     * |---------------+----------------+-------
     * | .....
     * +-------
     * |
     *
     */
    struct AGAINSTTRIANGLE{
      union{
	struct{
	  unsigned int a; // One edge
	  unsigned int b; // Two edge
	  unsigned int c; // Three edge
	};
	unsigned int __t_[3];
      };
      inline unsigned int&operator[](unsigned char i){return __t_[i];}
    };
    vector<AGAINSTTRIANGLE> againsttriangle; // Against triangle table
    /* 
     *   Against triangle table
     *  ___________________________________________________________________________________________________
     * | triangle index 1 | edge1 (triangle index 1) | edge2 (triangle index 2) | edge3 (triangle index 3) |
     * |------------------+--------------------------+--------------------------+--------------------------|
     * | triangle index 2 | edge1 (triangle index 1) | edge2 (triangle index 2) | edge3 (triangle index 3) |
     * |------------------+--------------------------+--------------------------+--------------------------|
     * | .....            | .....                    |
     * |------------------+-------
     *
     */
    struct OPENEDGE{
      unsigned int t; // Triangle number
      char e; // Edge number in triangle
      OPENEDGE(unsigned int __t_, char __e_):t(__t_),e(__e_){}
    };
    vector<OPENEDGE> openedge;
    /*
     *   Open edge table
     *  _____________________________________________
     * | array entry 1 | triangle index | edge index |
     * |---------------+----------------+------------|
     * | array entry 2 | triangle index | edge index |
     * |---------------+----------------+------------|
     * | .....         | .....
     * |---------------+-------
     *
     */
  public:
    //tolua_begin
    SURFACE();
    ~SURFACE();
    void init();
    void dest();
    void draw();
    // Calc functions
    void calc_normal();
    void calc_tangent();
    void calc_coincidedvertexes();
    void calc_againsttriangles();
    void calc_openedges();
    //tolua_end
    CHUNK* findattrib(char type);
    //void casteshadow(const vec3&);
    //tolua_begin
    unsigned int operator~();
    void operator()(int&/** k=-1 asnil**/,ungeom::CHUNK*&);
    /**tolua_getindex {**/
    ungeom::CHUNK* get(int);
    /**}**/
    ///**tolua_setindex {**/
    //void set(int,ungeom::SURFACE*);
    ///**}**/
    //tolua_end
    vector<unsigned int>&coincidedvertexes(vec3); // Return coincided vertexes array
  };//tolua_export
  
  unsigned int GLIndexType(unsigned char); // type of index from num of bytes
  unsigned int GLDrawPrim(unsigned char);  // type of primitive from num of components
  unsigned int GLIndex2uint(void* data, unsigned char node);
  
  /*
   *  Poligonal geometry loader
   */
  class MESH;
  /*
   *  Mesh loader
   */
  class LOADER{
  public:
    typedef bool (*METHOD)(LOADER&,undata::STREAM&);
    typedef vector<METHOD>::iterator ITER;
  protected:
    static vector<METHOD> loader;
  public:
    unbase::STATE state;
    vector<CHUNK*> chunk;
    
    LOADER();
    ~LOADER();
    static void Register(METHOD);
    static void init();
    static bool load(MESH&,undata::STREAM&);
    bool gen(MESH&);
  };
  
  class MESH: public unobj::OBJECT{//tolua_export
  protected:
    string osrc;
  public:
    static bool VBO;//tolua_export
    vector<SURFACE*> surface;
    //tolua_begin
    unsigned int operator~();
    void operator()(int& /** k=-1 asnil**/,ungeom::SURFACE*&);
    /**tolua_getindex {**/
    ungeom::SURFACE* get(int);
    /**}**/
    ///**tolua_setindex {**/
    //void set(int,ungeom::SURFACE*);
    ///**}**/
    
    string src;
    
    MESH();
    virtual ~MESH();
    void draw_geom(const unobj::MODE&);
    bool update();
    operator string();
    //tolua_end
    //void casteshadow(const vec3&);
  };//tolua_export

#define tridex(base,our) (base<2-our?base+our+1:base+our-2)
  // base - first index [0..2]
  // our  - require index [0..1]
  // Берет с одним выбраным индексом вершины в треугольнике 2 других:
  // as example:  tridex(0,0)==1, tridex(0,1)=2
  //              tridex(1,0)==2, tridex(1,1)=0
  //              tridex(2,0)==0, tridex(2,1)=1
#define trinex(base,our) (base+our<3?base+our:base+our-3)
  // base - first index [0..2]
  // our  - require index [0..2]
  // as example:  trinex(0,0)==0, trinex(0,1)=1, trinex(0,2)=2
  //              trinex(1,0)==1, trinex(1,1)=2, trinex(1,2)=0
  //              trinex(2,0)==2, trinex(2,1)=0, trinex(2,2)=1
#define trirel(base) ((unsigned int)(base%3))
  // возвращает относительный индекс в треугольнике по реальному в массиве вершин
#define trinum(base) ((unsigned int)(base/3))
  // возвращает номер треугольника по индексу вершины в массиве
#define outindex ((unsigned int)(-1))
}//tolua_export
