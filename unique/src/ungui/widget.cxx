/* OpenGL widgets
 *
 * Copyright (C) 2005-2005, Fenix R.S. Elite <tonder@trktvs.ru>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include"widget.hxx"

namespace ungui{
  //GUISTYLE::GUISTYLE(){}
  //GUISTYLE::~GUISTYLE(){}

  //static GUISTYLE _guistyle; // Стиль виджета по умолчанию

  /// Widget ///
  WIDGET::WIDGET():unobj::OBJECT(),size(vec2::one),center(vec2::null),
		   ostyle(NULL),style(NULL){rtype=unobj::RENDERTYPE::blend;}
  WIDGET::~WIDGET(){}

  // align: range of [ -1.0 .. 1.0, -1.0 .. 1.0 ]
  //
  //
  // area[3]                   area[2]
  //    + _______________________
  //     |           |           |
  //     |           V           |
  //     |                       |
  //     |__\                 /__|
  //     |  /                 \  |
  //     |    + align            |
  //     |           ^           |
  //     |___________|___________|
  //                              +
  // area[0]                    area[1]
  //
  //  rect = [ -0.5*size*(1+align) ;  0.5*size*(1-align) ]
  //
  // align = [ 0, 0] => rect = [-size/2 ;  size/2]
  // align = [-1,-1] => rect = [  [0,0] ;  size  ]
  // align = [ 1, 1] => rect = [-size   ;  [0,0] ]

  bool WIDGET::update(){ // Recompuite widget area
    OBJECT::update();
    if(style!=ostyle){
      if(style){
	mat=style->mat;
      }
    }
    /*
      _state=GUISTYLE::normal;
      _state=_sel?GUISTYLE::hover:_state;
      _state=_act?GUISTYLE::active:_state;

      if(_style){
      _style->State(_state);
      _mat=_style->Mat();
      _size=_style->Size();
      _align=_style->Align();
      }

      if(osize!=_size || oalign!=_align){
      oalign=_align;
      osize=_size;
      vec2 s=0.5*_size;
      area[0]=-mult(s,(vec2_one+_align));
      area[2]= mult(s,(vec2_one-_align));
      area[1]= vec2(area[2].x,area[0].y);
      area[3]= vec2(area[0].x,area[2].y);
      // Плоскости отсечения
      _clip.Plane0(PLANE( 1.0, 0.0, 0.0,-area[0].x)); // Левая
      _clip.Plane1(PLANE(-1.0, 0.0, 0.0, area[2].x)); // Правая
      _clip.Plane2(PLANE( 0.0, 1.0, 0.0,-area[0].y)); // Нижняя
      _clip.Plane3(PLANE( 0.0,-1.0, 0.0, area[2].y)); // Верхняя
      }
    */
  }

  void WIDGET::event(unogl::GRAPHCONTEXT& e){
    unobj::OBJECT::event(e);
    for(unogl::KEYS::ITER k=e.key.begin();k!=e.key.end();k++){
      if(k->key==unogl::KEY::mleft){
	if(sel && k->state){
	  act=true;
	}else{
	  if(!k->state)act=false;
	}
      }
    }
    //cout<<"Pointervel="<<e.pointervel<<endl;
    //  if(act){
    //    pos.x+=e.pointervel.x;
    //    pos.y+=e.pointervel.y;
    //}
  }
  void WIDGET::draw(GLenum mode){
    vec4 area;
    {
      vec2 s=0.5*size, a=vec2::one+center, b=vec2::one-center;
      area.x=-s.x*a.x; area.y=-s.y*a.y;
      area.z= s.x*b.x; area.w= s.y*b.y;
    }
    glColor4f(0.0,0.0,0.0,0.0);
    string matname="none";
    if(sel)matname="hover";
    if(act)matname="active";
  
    BindLoc();
    BindName(mode);
    BindMat(mode,matname);
    BindQuery(mode);
    // Draw Code
  
    glBegin(GL_QUADS);
    glNormal3f(0.0,0.0,1.0);
    glTexCoord2f(0.0,0.0); glVertex2f(area.x,area.y);
    glTexCoord2f(1.0,0.0); glVertex2f(area.z,area.y);
    glTexCoord2f(1.0,1.0); glVertex2f(area.z,area.w);
    glTexCoord2f(0.0,1.0); glVertex2f(area.x,area.w);
    glEnd();

    uBindQuery(mode);
    uBindMat(mode,matname);
    uBindName(mode);
    drawaxis(mode);
    uBindLoc();
  }

  /// Button ///
  BUTTON::BUTTON():WIDGET(){}
  BUTTON::~BUTTON(){}
  void BUTTON::draw(GLenum mode){
    WIDGET::draw(mode);
    BindName(mode);
    BindQuery(mode);
    caption.size=size;
    caption.center=center;
    caption.pos=pos;
    caption.pos.z+=WIDGET_OFFSET;
    caption.draw(mode&~(mode&unobj::RENDERMODE::name));
    uBindQuery(mode);
    uBindName(mode);
  }

  /// Text line ///
  TEXTLINE::TEXTLINE():WIDGET(),editable(false){content.polyline=false;}
  TEXTLINE::~TEXTLINE(){}
  bool TEXTLINE::update(){
    content.update();
  }
  void TEXTLINE::event(unogl::GRAPHCONTEXT& e){
    WIDGET::event(e);
    content.editable=editable;
    if(sel)content.event(e);
  }
  void TEXTLINE::draw(GLenum mode){
    WIDGET::draw(mode);
    BindName(mode);
    BindQuery(mode);
    content.size=size;
    content.center=center;
    content.pos=pos;
    content.pos.z+=WIDGET_OFFSET;
    content.draw(mode&~(mode&unobj::RENDERMODE::name));
    uBindQuery(mode);
    uBindName(mode);
  }

  /// Text area ///
  TEXTAREA::TEXTAREA():WIDGET(),editable(false){content.polyline=true;}
  TEXTAREA::~TEXTAREA(){}
  bool TEXTAREA::update(){
    content.update();
  }
  void TEXTAREA::event(unogl::GRAPHCONTEXT& e){
    WIDGET::event(e);
    content.editable=editable;
    if(sel)content.event(e);
  }
  void TEXTAREA::draw(GLenum mode){
    WIDGET::draw(mode);
    BindName(mode);
    BindQuery(mode);
    content.size=size;
    content.center=center;
    content.pos=pos;
    content.pos.z+=WIDGET_OFFSET;
    content.draw(mode&~(mode&unobj::RENDERMODE::name));
    uBindQuery(mode);
    uBindName(mode);
  }

  /// Cursor ///
  CURSOR::CURSOR():WIDGET(){}
  CURSOR::~CURSOR(){}
  void CURSOR::draw(GLenum mode){
    mode=mode&~(mode&unobj::RENDERMODE::name);
    WIDGET::draw(mode);
  }
  //void CURSOR::step(scalar dt){OBJECT::step(dt);}
  void CURSOR::event(unogl::GRAPHCONTEXT& e){
    //e->cursor=false;
    //cout<<"cursor ok"<<endl;
    pos=e.pointer;
  }
  
  WINDOW::WINDOW():GROUP(),size(vec2::one),center(vec2::null),dragable(false),
		   ostyle(NULL),style(NULL){rtype=unobj::RENDERTYPE::blend;}
  WINDOW::~WINDOW(){}
  bool WINDOW::update(){
    GROUP::update();
    if(style!=ostyle){
      if(style){
	mat=style->mat;
      }
    }
  }
  void WINDOW::draw(GLenum mode){
    vec4 area;
    {
      vec2 s=0.5*size, a=vec2::one+center, b=vec2::one-center;
      area.x=-s.x*a.x; area.y=-s.y*a.y;
      area.z= s.x*b.x; area.w= s.y*b.y;
    }

    string matname="none";
    if(sel)matname="hover";
    if(act)matname="active";

    BindLoc();
    BindName(mode);
    BindMat(mode,matname);
    BindQuery(mode);
    // Draw Code

    glBegin(GL_QUADS);
    glNormal3f(0.0,0.0,1.0);
    glTexCoord2f(0.0,0.0); glVertex2f(area.x,area.y);
    glTexCoord2f(1.0,0.0); glVertex2f(area.z,area.y);
    glTexCoord2f(1.0,1.0); glVertex2f(area.z,area.w);
    glTexCoord2f(0.0,1.0); glVertex2f(area.x,area.w);
    glEnd();

    uBindQuery(mode);
    uBindMat(mode,matname);
    uBindName(mode);
    drawaxis(mode);
  
    for(GROUP::ITER i=pool.begin();i!=pool.end();i++){
      unobj::OBJECT& o=*(*i).second;
      o.pos.z=pos.z+WIDGET_OFFSET;
      o.draw(mode);
    }
    uBindLoc();
  }
  void WINDOW::event(unogl::GRAPHCONTEXT& e){
    unobj::GROUP::event(e);
    for(unogl::KEYS::ITER k=e.key.begin();k!=e.key.end();k++){
      if(k->key==unogl::KEY::mleft){
	if(sel && k->state){
	  act=true;
	}else{
	  if(!k->state)act=false;
	}
      }
    }
    //cout<<"Pointervel="<<e.pointervel<<endl;
    if(act){
      if(dragable){
	pos.x+=e.pointervel.x;
	pos.y+=e.pointervel.y;
      }
    }
  }

  /*
    BUTTONSTYLE::BUTTONSTYLE(): GUISTYLE(){
  
    }
    BUTTONSTYLE::BUTTONSTYLE(CONTAIN o): GUISTYLE(o){
    font=CONTAIN_GETVALUE(FONT*, o["font"], NULL);
    font_hover =CONTAIN_GETVALUE(FONT*, o["font_hover"],  font);
    font_active=CONTAIN_GETVALUE(FONT*, o["font_active"], font);
    font_motion=CONTAIN_GETVALUE(FONT*, o["font_motion"], font);
    }
    BUTTONSTYLE::~BUTTONSTYLE(){

    }
    BUTTON::BUTTON(): WIDGET(){}
    BUTTON::~BUTTON(){}

    // Handlers
    void BUTTON::mouseHandler(vec2 event){
  
    }
    void BUTTON::keysHandler(APP::KEY event){
    if(_sel && event.key==APP::KEY::mleft){
    _act=event.state;
    if(_activecall.is_valid()) _activecall(_act);
    }
    if(!_sel)_act=false;
    }
    void BUTTON::Draw(GLenum mode){
    WIDGET::Draw(mode);
    BindLoc();
    _text.Draw(mode);
    uBindLoc();
    }

    void TEXTLINE::ReCulc(){
    WIDGET::ReCulc();

    vec4 a;
    a.x=area[0].x;
    a.y=area[2].x;
    a.z=area[0].y;
    a.w=area[2].y;

    _text.Area(a);
    }

    void TEXTLINE::Draw(GLenum mode){
    ReCulc();
  
    BindLoc();
    BindName(mode);
    BindMat(mode);
    BindQuery(mode);
    
    glBegin(GL_QUADS);
    glNormal3f  (0.0,0.0,1.0);
    glTexCoord2f(0.0,0.0);      glVertex2fv(area[0]);
    glTexCoord2f(1.0,0.0);      glVertex2fv(area[1]);
    glTexCoord2f(1.0,1.0);      glVertex2fv(area[2]);
    glTexCoord2f(0.0,1.0);      glVertex2fv(area[3]);
    glEnd();
  
    uBindQuery(mode);
    uBindMat(mode);
    uBindName(mode);

    _text.Draw(mode);
    DrawAxis(mode);
    uBindLoc();
    }

    ROOTWIN::ROOTWIN(): WIDGET(){
    _cursor=NULL;
    }

    ROOTWIN::ROOTWIN(CONTAIN o): WIDGET(o){
    _cursor=NULL;
    }

    void ROOTWIN::Draw(GLenum mode){
  
    }

    ROOTWIN::~ROOTWIN(){
  
    }

    //void ROOTWIN::Draw(GLenum mode){
    //  
    //}

    void ROOTWIN::Step(scalar step){
  
    }
  */
}
