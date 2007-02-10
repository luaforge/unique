/***************************************************************************
 *            particle.cpp
 *
 *  Wed Jun 29 17:12:37 2005
 *  Copyright  2005  Fenix
 *  tonder@trktvs.ru
 ****************************************************************************/

/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Library General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#include"particle.hxx"

namespace uneff{
  PARTICLE::PARTICLE():OBJECT(){
    mass=1.0f;
    gravity=vec3::null;
    num=1;
    quant=0.1;
    dispers=vec4::one;
    source=vec3::null;
    geompart=tpoint;
    factor=vec2::one;
    psize=vec4::one;
    popul=1.0f; // Одна частица должна быть, иначе это будет не популяция
  }

  PARTICLE::~PARTICLE(){}
  
  void PARTICLE::drawpart(PART* node){// Рисовка  i частицы
    glColor4fv(node->color);
    vec3 p=node->pos;
  
    glPointSize(psize.x);
    glLineWidth(psize.w);
  
    glPushMatrix();
    mat4 transmat; transmat.translate(p);
    glMultMatrixf(transmat);
    glMultMatrixf(unogl::gl_RotateProjectionMatrix());

    glBegin(geompart);//GL_TRIANGLE_STRIP
    switch(geompart){
    case tquad:
      glTexCoord2d(1,1); glVertex2f( psize.x, psize.y);
      glTexCoord2d(0,1); glVertex2f(-psize.x, psize.y);
      glTexCoord2d(0,0); glVertex2f(-psize.x,-psize.y);
      glTexCoord2d(1,0); glVertex2f( psize.x,-psize.y);
      triangles+=2;
      break;
    case ttria:
      glTexCoord2d(1,1); glVertex2f(psize.x,psize.y);
      glTexCoord2d(0,1); glVertex2f(psize.x,psize.y);
      glTexCoord2d(1,0); glVertex2f(psize.x,psize.y);
      triangles+=1;
      break;
    case tline:
      glTexCoord2d(1,1); glVertex2f(psize.x,psize.y);
      glTexCoord2d(0,1); glVertex2f(psize.x,psize.y);
      triangles+=1;
      break;
    case tpoint:
      glVertex3f(0.0,0.0,0.0);
      triangles+=1;
      break;
    }
    glEnd();

    glPopMatrix();
  
    OGL_DEBUG();
  }

  int numrend=0;

  void PARTICLE::bind_location(){
    glPushMatrix();
  }

  void PARTICLE::draw_geom(const unobj::MODE&m){
    triangles=0;
    //glDisable(GL_LIGHTING);
    glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA,GL_ONE);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
    glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);
    OGL_DEBUG();
    vec3 dir=unogl::gl_RotateProjectionMatrixInv()*vec3::pz;// Считаем вектор, направленный от наблюдателя
    // В каждом шаге будем находить самую дальнюю частицу, но не дальше чем depth и рисовать ее,
    // каждый раз изменяя значение depth на дальность прорисованной частицы, пока более ближних,
    // чем depth не останется....
    vec3 pos=matrix().inv()*unogl::gl_CameraPosition();
    //vec3 pos=gl_CameraPosition()*matrix();
    scalar depth=pos*dir;
    cout<<"\r"<<"depth:"<<depth<<" ";
    for(;;){
      PART* c=NULL;
      scalar z=-100.0f;
      for(std::deque<PART>::iterator i=particle.begin();i!=particle.end();i++){ // сортировка
	if((*i).active){
	  scalar d=(*i).pos*dir;
	  if(d<depth){
	    if(d>z){
	      z=d;
	      c=&(*i);
	    }
	  }
	}
      }
      if(c){
	drawpart(c);
	depth=z;
      }else break;
    }
    OGL_DEBUG();
  }

#define RANDVAL(f) 0.01*(rand()%200-100)*f
  float PARTICLE::FadeCalc(){
    //return (float)((factor.y*rand())/(RAND_MAX+factor.x)+factor.x)*factor.z;
    //return RANDVAL(factor.z);
    return factor.a+RANDVAL(factor.b);
  }
  void PARTICLE::ReGen(std::deque<PART>::iterator node){// Восстановление ind частицы
    node->life=1.0f;
    node->fade=FadeCalc();
    node->pos=pos+vec3(RANDVAL(source.x),RANDVAL(source.y),RANDVAL(source.z))*mat4(rot);
    //  node->speed=vec3(RANDVAL(dispers.x),RANDVAL(dispers.y),RANDVAL(dispers.z));
    quat q;//=quat(vec3(RANDVAL(dispers.x),RANDVAL(dispers.y),RANDVAL(dispers.z)),RANDVAL(dispers.w));
    q.euler(vec3(RANDVAL(dispers.x),RANDVAL(dispers.y),RANDVAL(dispers.z)));
    q.norm();
    node->speed=RANDVAL(dispers.w)*vec3::pz*mat4(q);
    //  node->color=mat?mat->color.emission:vec4(1.0,1.0,1.0,1.0);
    if(mat.begin()!=mat.end())
      node->color=(*mat.begin()).second->color.emission;
    else
      node->color=vec4(1.0,1.0,1.0,1.0);
    node->active=true;
    node->grav=gravity;
  }
  void PARTICLE::step(unbase::TIME&time){
    OBJECT::step(time);
    scalar s=time.delta;
    /*
      int quants=int(time/quant);
      for(int r=0;r<=quants;r++){
      scalar s=r==quants?time-quants*(r-1):quant;
    */
    std::deque<PART>::iterator i;
    if(particle.size()!=num){// тогда мы должны либо продуцировать,
      // либо убивать частицы
      if(popul>=1.0f){ // Запускаем процесс приращения\убыли популяции цастиц
	if(particle.size()<num){ // Приращиваем популяцию на одну частицу
	  particle.push_back(PART());
	  i=particle.end();
	  i--;
	  i->life=0.0f;
	  i->active=true;
	}else{ // Должны навсегда удалить одну погасшую частицу
	  particle.pop_back();
	}
	popfg=FadeCalc(); // Узнаем скорость воспроизводства частицы
	popul=0.0f;       // Устанавливаем счетчик рождения
      }else{ // Считаем мгновения до приращения\убыли популяции цастиц
	popul+=s*popfg;
      }
    }
    int k=0;
    for(i=particle.begin();i!=particle.end();i++){// Пересчет параметров частиц
      if(i->active){       // Если частица активна, вычисляем
	if(i->life<=0.0f){ // Частица уже мертва, если зацикленная генерация, нужно оживить
	  ReGen(i);
	}else{
	  i->pos  +=s*i->speed;     // передвинем частицу
	  i->speed+=s*i->grav*mass; // прибавим ускорение
	  i->life -=s*i->fade;      // укоротим жизнь
	  i->color.A=i->life;       // погасим
	}
      }
    }
    //}
  }

  PARTICLE::operator string(){
    return string("PARTICLE()");
  }
}
