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
//#include"bsp.hxx"
//#include"portal.hxx"

#include"unobj.hxx"

#define MESH_TEST_MODE

namespace ungeom{//tolua_export
  /*
   *  Poligonal geometry chunk
   */
  class MCHUNK{
  public:
    enum { // type of chunk
      vert=0x01,// vertexes
      norm=0x02,// normals
      binm=0x04,// binormals
      tang=0x05,// tangents
      texc=0x03,// texture coords
      face=0x06,// faces
      matl=0x07,// materials
      bone=0x08 // bones
    };
    // Chunk properties
    unsigned int  id;   // Chunk identifier
    unsigned int  link; // Target link
    unsigned char type; // Chunk type
    unsigned int  size; // Data size
    unsigned int  lim;  // Data byte count
    unsigned char format; // Component format (or byte per number)
    unsigned char compon; // Count components per element
    unsigned char aux;
    unsigned int  glid; // OpenGL identifier
    void*         data; // Data pointer
    void*         offset;
    // Chunk methods
    MCHUNK();
    ~MCHUNK();
    void init();
    void dest();
  };
  /*
   *  Poligonal surface
   */
  class MSURF{
  public:
    vector<MCHUNK*> attrib;
    bool smooth;
    unsigned int maxangle;
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
    MSURF();
    ~MSURF();
    MCHUNK* findattrib(char type);
    void init();
    void dest();
    void draw();
    // Calc functions
    void calc_normal();
    void calc_tangent();
    void calc_coincidedvertexes();
    void calc_againsttriangles();
    void calc_openedges();

    void casteshadow(const vec3&);

    unsigned int chunks(){return attrib.size();}
    MCHUNK* chunk(unsigned int i){
      if(i>=0&&i<attrib.size())return attrib[i];else return NULL;
    }
  
    vector<unsigned int>&coincidedvertexes(vec3); // Return coincided vertexes array
  
  };

  class MDATA;
  /*
   *  Mesh processor
   */
  class MPROC{
  protected:
    MDATA* data;
  public:
    MPROC();
    ~MPROC();
    void init(MDATA*);
    void compile();
    void draw();
  };
  /*
   *  Poligonal geometry loader
   */
  class MDATA{
  protected:
    static map<string,MDATA*> mesh; // loaded meshes
    unsigned int used; // Num of geted
  public:
    struct TRIANGLENODE{
      unsigned int t; // triangle number
      unsigned int s; // surface number
    };
    struct AGAINSTTRIANGLE{
      union{
	struct{
	  TRIANGLENODE a,b,c;
	};
	TRIANGLENODE __t_[3];
      };
      inline TRIANGLENODE&operator[](unsigned char i){return __t_[i];}
    };
  public:
    static bool Enable_VBO; // Vertex Buffer Object
    // get / put
    static MDATA* get(string);
    static void put(MDATA*);
    // constructor
    string src;
    unbase::STATE state;
    bool bsp;
    vector<MCHUNK> chunk;
    vector<MSURF> surface;
    MDATA();
    ~MDATA();
    // loading / saving
    virtual bool load(undata::STREAM&);
    bool GenData();
    // Surface
    unsigned int surfs(){return surface.size();}
    MSURF* surf(unsigned int n){if(n>=0&&n<surface.size())return &surface[n];else return NULL;}
  };

  unsigned int GLIndexType(unsigned char); // Выставляет тип индеска по размеру
  unsigned int GLDrawPrim(unsigned char);  // Выставляет тип примитивов по числу компонент
  unsigned int GLIndex2uint(void* data, unsigned char node);
  
  /*
   *  Mesh loader
   */
  class MLOADER{
  public:
    typedef bool (*METHOD)(MDATA&,undata::STREAM&);
    typedef vector<METHOD>::iterator ITER;
  protected:
    static vector<METHOD> loader;
  public:
    MLOADER();
    ~MLOADER();
    static void Register(METHOD);
    static void init();
    static bool load(MDATA&,undata::STREAM&);
  };
  
  class MDISPATCHER{
  public:
    MDISPATCHER();
    virtual ~MDISPATCHER();
  };
  
  class MESH: public unobj::OBJECT{//tolua_export
  protected:
    string osrc;
  public:
    //tolua_begin
    /**tolua_readonly **/MDATA* data;
    string src;
    
    MESH();
    virtual ~MESH();
    
    void draw(unsigned int mode=unobj::RENDERMODE::geom|unobj::RENDERMODE::matl);
    bool update();
    operator string();
    
    int maxvertexattribs;
    //tolua_end
    void casteshadow(const vec3&);
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
