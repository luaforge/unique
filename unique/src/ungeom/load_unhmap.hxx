
vec2 unhmap_texcrd(0.1,0.1);  // Step texture coords
vec3 unhmap_density(0.001,0.001,0.001); // Step size per height width depth

static bool unhmap_load(MDATA& d,undata::STREAM& s){
  unvis::IMAGE* heightmap=new unvis::IMAGE();
  if(heightmap->load(s)){
    if(heightmap->channels==1){
      vec3* verts;
      { //// Gen vertexes ////
	d.chunk.push_back(MCHUNK());
	MCHUNK& c=d.chunk.back();
	c.id=1;
	c.link=0;
	c.type=MCHUNK::vert;
	c.size=heightmap->height*heightmap->width;
	c.format=4;
	c.compon=3;
	c.init();
	verts=(vec3*)c.data;
	vec3 rcen=vec3(-0.5*heightmap->width*unhmap_density.x, -0.5*heightmap->height*unhmap_density.y, -0.5*256*unhmap_density.z); // Begin center
	for(GLuint i=0;i<heightmap->height;i++)for(GLuint j=0;j<heightmap->width;j++){
	  GLuint index=i*heightmap->width+j;
	  verts[index]=vec3(j*unhmap_density.x+rcen.x, i*unhmap_density.y+rcen.y,scalar(heightmap->pixels[index])*unhmap_density.z+rcen.z);
	}
      }
      { //// Gen faces ////
	d.chunk.push_back(MCHUNK());
	MCHUNK& c=d.chunk.back();
	c.id=2;
	c.link=1;
	c.type=MCHUNK::face;
	c.size=heightmap->height*heightmap->width*2;
	c.format=4;
	c.compon=3;
	c.init();
	GLuint* elem=(GLuint*)c.data;
	for(GLuint i=0;i<heightmap->height-1;i++){
	  for(GLuint j=0;j<heightmap->width-1;j++){
	    GLuint nvert=(i*heightmap->width+j);
	    GLuint index=nvert*6;
	    elem[index+0]=nvert+0;
	    elem[index+1]=nvert+1;
	    elem[index+2]=nvert+0+heightmap->height;
	    elem[index+3]=nvert+1;
	    elem[index+4]=nvert+1+heightmap->height;
	    elem[index+5]=nvert+0+heightmap->height;
	  }
	}
      }
      { //// Gen normals ////
	d.chunk.push_back(MCHUNK());
	MCHUNK& c=d.chunk.back();
	c.id=3;
	c.link=1;
	c.type=MCHUNK::norm;
	c.size=heightmap->height*heightmap->width;
	c.format=4;
	c.compon=3;
	c.init();
	vec3* norms=(vec3*)c.data;
	norms[0]=(verts[1]-verts[0])^(verts[heightmap->width]-verts[0]);// One vertex
	norms[0].norm();
	for(GLuint i=1;i<heightmap->height-1;i++){
	  // One row vectors
	  for(GLuint j=1;j<heightmap->width-1;j++){
	    GLuint index=i*heightmap->width+j;
	    norms[index]=(verts[index+1]-verts[index-1])^(verts[index+heightmap->width]-verts[index-heightmap->width]);
	    norms[index].norm();
	  }
	}
      }
      { //// Gen texture coords ////
	d.chunk.push_back(MCHUNK());
	MCHUNK& c=d.chunk.back();
	c.id=4;
	c.link=1;
	c.type=MCHUNK::texc;
	c.size=heightmap->height*heightmap->width;
	c.format=4;
	c.compon=2;
	c.init();
	vec2* texcs=(vec2*)c.data;
	for(GLuint i=0;i<heightmap->height;i++){
	  // One row vectors
	  for(GLuint j=0;j<heightmap->width;j++){
	    GLuint index=i*heightmap->width+j;
	    texcs[index]=vec2(j*unhmap_texcrd.x,i*unhmap_texcrd.y);
	  }
	}
      }
    }
    delete heightmap;
    return true;
  }
  delete heightmap;
  return false;
}
