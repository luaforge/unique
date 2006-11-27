static unsigned char unmesh_version[4]={0,3,0,4};
static unsigned char unmesh_sign[]="#!UNMESH";

static bool unmesh_load(MDATA& d,undata::STREAM& s){
  // Check type
  char dsig[8];
  s.seekg(0,undata::STREAM::beg); s.read(dsig,8);
  if(memcmp(unmesh_sign,dsig,8))return false;
  // Check version
  unsigned char srcver[4];
  s.read(srcver,4);
  if(srcver[0]!=unmesh_version[0])return false;	// Первый номер версии должен совпадать
  if(srcver[2]> unmesh_version[2])return false;	// Третий номер у файла не должен превышать
  						// номер у загрузчика
  if(srcver[3]>unmesh_version[3]||((srcver[3]&0x1)&&!(unmesh_version[3]&0x0)))return false;
  // 4е номера должны быть одинаковой четности и у файла не больше чем у загрузчика
  if(srcver[1]<(unmesh_version[1]-2))return false; // Второй номер у файла не меньше чем на
  						//2 версии старше, чем у загрузчика
  // Loading chunks
  unsigned int id=0;
  for(;!s.eof();){
    s.read(&id,4);
    for(;s.gcount()==4&&id;s.read(&id,4)){ // Read chunk header
      d.chunk.push_back(MCHUNK());
      MCHUNK& c=d.chunk.back();
      c.id=id;
      s.read(&c.link,4);
      s.read(&c.type,1);
      s.read(&c.size,4);
      s.read(&c.format,1);
      s.read(&c.compon,1);
      s.read(&c.aux,1);
    }
    //vector<MESHCHUNK>::iterator i=d.chunk.begin();
    s.read(&id,4);
    for(;s.gcount()==4&&id;s.read(&id,4)){
      for(vector<MCHUNK>::iterator i=d.chunk.begin();i!=d.chunk.end();i++){
	MCHUNK& c=*i;
	if(c.id==id && c.lim==0){ // Load chunk data
	  c.init();
	  s.read(c.data,c.lim);
	  if(s.gcount()!=c.lim)return false;
	  break;
	}
      }
    }
  }
  return true;
}
