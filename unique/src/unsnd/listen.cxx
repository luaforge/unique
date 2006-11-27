#include"listen.hxx"

namespace unsnd{
  LISTEN::LISTEN():OBJECT(){
    alGetListenerf(AL_GAIN,&gain); ogain=gain;
  }
  LISTEN::~LISTEN(){}

  void LISTEN::bind(){
    mat4 mtx=locatematrix();
    mat4 mtp=mat4(mtx*unmath::vec3::null);
    mat4 mtr=mtx*mtp.inv();
    vec3 gpos=mtx*unmath::vec3::null; // Global position
    vec3 ori[2]={mtr*unmath::vec3::py, // Up vector
		 mtr*unmath::vec3::pz};// At vector
    alListenerfv(AL_POSITION,gpos);
    alListenerfv(AL_ORIENTATION,ori[0]);
    //alListenerfv(AL_VELOCITY,vel);
    //cout<<gpos<<ori[0]<<ori[1]<<vel<<endl;
  }
  void LISTEN::ubind(){}
  
  bool LISTEN::update(){
    if(ogain!=gain){
      ogain=gain;
      alListenerf(AL_GAIN,gain);
    }
    bind();
    return true;
  }
}
