static unsigned char unmesh_version[4]={0,3,0,4};
static unsigned char unmesh_sign[]="#!UNMESH";

static bool unmesh_load(LOADER&d,undata::STREAM&s){
  d.state=unbase::STATE(false); 
  // Check type
  char dsig[8];
  s.seekg(0,undata::STREAM::beg); s.read(dsig,8);
  if(memcmp(unmesh_sign,dsig,8))return false;
  // Check version
  unsigned char srcver[4];
  s.read(srcver,4);
  if(srcver[0]!=unmesh_version[0])return false;	   // Check if equivalent one numbers of version code
  if(srcver[1]>unmesh_version[1]||srcver[1]<(unmesh_version[1]-2))return false; // Check two version numbers
  if(srcver[2]>unmesh_version[2])return false;	   // Check if not exceed three version number in file
  if(srcver[3]>unmesh_version[3]||((srcver[3]&0x1)&&!(unmesh_version[3]&0x0)))return false;
  // Check if equivalent parity four numbers
  
  // Loading chunks
  unsigned int id=0;
  for(;!s.eof();){
    for(s.read(&id,4);s.gcount()==4&&id;s.read(&id,4)){ // Read chunk header
      d.chunk.push_back(new CHUNK());
      CHUNK& c=*d.chunk.back();
      c.id=id;
      s.read(&c.surf,4);
      s.read(&c.type,1);
      s.read(&c.seq,1);
      s.read(&c.format,1);
      s.read(&c.compon,1);
      s.read(&c.size,4);
    }
    for(s.read(&id,4);s.gcount()==4&&id;s.read(&id,4)){
      for(vector<CHUNK*>::iterator i=d.chunk.begin();i!=d.chunk.end();i++){
	CHUNK& c=*(*i);
	if(c.id==id && c.lim==0){ // Load chunk data
	  c.init();
	  s.read(c.data,c.lim);
	  if(s.gcount()!=c.lim)return false;
	  break;
	}
      }
    }
  }
  d.state=unbase::STATE(true);
  return true;
}
