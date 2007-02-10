
// Copyright (C) 2006 by PhoenixIV

#include"engine.hxx"

namespace unique{
  using namespace unbase;
  using namespace unobj;
  using namespace unogl;

  //ENGINE engine;

  ENGINE::ENGINE():run(false),eventer(NULL){
    
  }
  ENGINE::~ENGINE(){
    
  }
  
  struct SCNCMR{
    unobj::SCENE* scene;
    unobj::CAMERA* camera;
    SCNCMR(unobj::SCENE* s,unobj::CAMERA* c):scene(s),camera(c){}
  };
  
  void ENGINE::draw(){
    drawtime();
    for(CTXGROUP::ITER cti=render.begin();cti!=render.end();cti++){
      GRAPHCONTEXT* ctx=dynamic_cast<GRAPHCONTEXT*>((*cti).second);
      if(!ctx)continue;
      deque<SCNCMR> layers;
      for(SCNGROUP::ITER sci=scene.begin();sci!=scene.end();sci++){
	SCENE* scn=(*sci).second;
	for(CAMGROUP::ITER cmi=scn->camera.begin();cmi!=scn->camera.end();cmi++){
	  CAMERA* cmr=(*cmi).second;
	  if(cmr->context==ctx){
	    if(layers.begin()==layers.end())layers.push_back(SCNCMR(scn,cmr));else
	      for(deque<SCNCMR>::iterator lri=layers.begin();lri!=layers.end();lri++){
		if(cmr->layer>lri->camera->layer){
		  deque<SCNCMR>::iterator next=lri+1;
		  if(next!=layers.end()){if(cmr->layer<next->camera->layer){layers.insert(lri,SCNCMR(scn,cmr));break;}
		  }else{layers.push_back(SCNCMR(scn,cmr));break;}
		}else{layers.push_front(SCNCMR(scn,cmr));break;}
	      }
	  }
	}
      }
      ctx->bind();
      if(layers.size()){
	if(ctx->state.state){
	  glClear(GL_DEPTH_BUFFER_BIT);
	  glClear(GL_COLOR_BUFFER_BIT);
	  for(deque<SCNCMR>::iterator lri=layers.begin();lri!=layers.end();lri++){
	    SCNCMR& l=(*lri);
	    
	    l.camera->bind();
	    unobj::MODE m;
	    l.scene->draw(m);
	    l.camera->ubind();
	    
	    if(l.camera->selection){
	      l.camera->pointer.pos=((GRAPHCONTEXT*)ctx)->pointer;
	      l.camera->pointer.bind();
	      l.camera->bind();
	      unobj::MODE m; m.name=true;
	      l.scene->draw(m);
	      l.camera->ubind();
	      l.camera->pointer.ubind();
	      //l.scene->object->id==l.camera->pointer.top();
	      //l.scene->object->select=true;
	      //l.scene->object.select(l.camera->pointer.top());
	      //cout<<"ok  "<<(*lri).camera->pointer.top()<<endl;
	    }
	  }
	}
      }
      ctx->ubind();
    }
    drawtime();
  }

  void ENGINE::step(){
    time();
    steptime();
    for(SCNGROUP::ITER sci=scene.begin();sci!=scene.end();sci++){
      (*sci).second->step(time);
    }
    steptime();
    fps=unmath::oo_scalar(time.delta);
  }
  void ENGINE::event(){
    for(SCNGROUP::ITER sci=scene.begin();sci!=scene.end();sci++){
      (*sci).second->event();
    }
  }

  void ENGINE::loop(){
    run=true;
    while(run){
      event();
      step();
      draw();
    }
  }

  ENGINE::operator string(){
    return string("ENGINE()");
  }
}
