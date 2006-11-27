/***************************************************************************
 *            text.cpp
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

#include"text.hxx"

namespace ungui{
  /*
    char charcodetable[5][20]={
    {'`','1','2','3','4','5','6','7','8','9','0','-','=','\\','q','w','e','r','','\0'},// Original
    {'`','1','2','3','4','5','6','7','8','9','0','-','=','\\','q','w','e','r','\0'},// Low  register english
    {'~','!','@','#','$','%','^','&','*','(',')','_','+','|', 'Q','W','E','R','\0'},// High register english
    {'ё','1','"','#','4','5','6','7','8','9','0','-','=','\\','й','ц','у','к','\0'},// Low  register russian
    {'Ё','!','"','#',';','%',':','?','*','(',')','_','+','/', 'Й','Ц','У','К','\0'} // High register russian
    };
  */
  char charcodetable[5][50]={
    "`1234567890-=\\qwertyuiop[]asdfghjkl;'zxcvbnm,./ ",// Original
    "`1234567890-=\\qwertyuiop[]asdfghjkl;'zxcvbnm,./ ",// Low  register english
    "~!@#$%^&*()_+|QWERTYUIOP{}ASDFGHJKL:\"ZXCVBNM<>? ",// High register english
    "ё1\"#4567890-=\\йцукенгшщзхъфывапролджэячсмитьбю. ",// Low  register russian
    "Ё!\"#;%:?*()_+/ЙЦУКЕНГШЩЗХЪФЫВАПРОЛДЖЭЯЧСМИТЬБЮ, "
  };
  
  TEXTCARET::TEXTCARET(UNTEXT* t):absol(0),line(0),symb(0),text(t),
				  visible(false),chr('_'){}
  bool TEXTCARET::update(){
    string& s=text->text;
    if(absol>s.length())absol=s.length();
    if(_absol!=absol){ // Change absolute cursor position have max priority
      _absol=absol;
      for(unsigned int i=0;i<absol;i++){ // Analize
	if(s[i]=='\n'){symb=0; line++;}
	symb++;
      }
      _line=line;
      _symb=symb;
      return true;
    }
    if(_line!=line){ // Change line and symb have equal priority
      _line=0;
      for(unsigned int i=0;i<s.length();i++){ // Analize
	if(s[i]=='\n')_line++;
	absol++;
      }
      if(line>_line)line=_line;else _line=line;
    }
    if(_symb!=symb){
      _symb=0;
      for(unsigned int i=0;i<s.length();i++){ // Analize
	if(s[i]=='\n')_line++;
	if(_line==line){
	  _symb++;
	}
      }
      if(symb>_symb)symb=_symb;else _symb=symb;
      _line=line;
      absol+=symb;
    }
    _absol=absol;
  }

  TEXTSPACE::TEXTSPACE():symb(0.0f),line(0.0f),parag(0.02f),inden(0.02f){}
  TEXTSPACE::~TEXTSPACE(){}

  UNTEXT::UNTEXT():OBJECT(),font(NULL),color(vec4::one),caret(this),height(0.1f),
		   size(0.4f,0.1f),align(centr+middle),wrap(perword),editable(false)
  {rtype=unobj::RENDERTYPE::blend;}
  UNTEXT::~UNTEXT(){}

  void UNTEXT::draw(GLenum mode){// Прорисовка текста
    if(!visible)return;
    if(!font)return;
    font->update();
  
    BindLoc();
    BindName(mode);
    BindQuery(mode);
    glColor4fv(color);
  
    vec4 area;
    {
      vec2 s=0.5*size, a=vec2::one-center, b=vec2::one+center;
      area.x=-s.x*a.x; area.y= s.y*a.y;
      area.z= s.x*b.x; area.w=-s.y*b.y;
    }
    vec2 chc=vec2(0.0f,height+space.line);
    vec2 cpos=vec2(area.x,area.y-chc.y);
    unsigned int line=0,i;
    for(i=0;i<text.length();i++){
      if((unsigned int)*((unsigned char*)text.data()+i)==' '){
	chc.x=height*font->poly[(unsigned int)*((unsigned char*)text.data())].w+space.symb;
      }else{
	chc.x=height*font->poly[(unsigned int)*((unsigned char*)text.data()+i)].w+space.symb; 
      }
      if((cpos.x+chc.x)>area.z){// Больше символов не влезает в строку, идем на следующую
	line++;
	cpos.x=area.x;
	cpos.y-=chc.y;
      }
      if(*((unsigned char*)text.data()+i)=='\n'){// На следующую строку
	line++;
	cpos.x=area.x;
	cpos.y-=chc.y;
	continue;
      }
      if(cpos.y<area.w){break;}// Больше строк не войдет
      DrawChar((unsigned int)*((unsigned char*)text.data()+i), cpos);
      if(caret.visible && i==caret.absol){
	glPushMatrix();
	glTranslatef(0.0,0.0,0.001);
	DrawChar((unsigned int)(caret.chr), cpos);
	glPopMatrix();
      }
      cpos.x+=chc.x;// Смещение после печати символа
    }
    if(caret.visible && i==caret.absol){
      glPushMatrix();
      glTranslatef(0.0,0.0,0.001);
      DrawChar((unsigned int)(caret.chr),cpos);
      glPopMatrix();
    }
    if(i<text.length())into=true;else into=false;

    //DrawChar('A',vec2_null);
    // Calc 
    /*
      glBegin(GL_LINE_STRIP);
      glVertex2f(area.x,area.y);
      glVertex2f(area.x,area.w);
      glVertex2f(area.z,area.w);
      glVertex2f(area.z,area.y);
      glEnd();
    */
    uBindQuery(mode);
    uBindName(mode);
    drawaxis(mode);
    uBindLoc();
  }

  void UNTEXT::event(unogl::GRAPHCONTEXT& e){
    OBJECT::event(e);
    if(editable){ // Editing handling
      caret.visible=true;
      for(unogl::KEYS::ITER k=e.key.begin();k!=e.key.end();k++){
	if(k->state){
	  switch(k->key){
	    // Cursor moving //
	  case unogl::KEY::up:    caret.line--;  caret.update(); break;
	  case unogl::KEY::down:  caret.line++;  caret.update(); break;
	  case unogl::KEY::left:  caret.absol--; caret.update(); break;
	  case unogl::KEY::right: caret.absol++; caret.update(); break;
	    // Change register //
	  case unogl::KEY::shift: shift=true; break;
	  case unogl::KEY::capslock: caps=not caps; break;
	    // Change layout //
	  case unogl::KEY::alt: layout=layout?0:1; break;
	    // Text editing //
	  case unogl::KEY::bkspace: delet();    break;
	  case unogl::KEY::space:   paste(' '); break;
	  case unogl::KEY::enter:   if(polyline)paste('\n'); break;
	  default:  paste(charselect((char)k->key)); break;
	  }
	}else{
	  switch(k->key){
	    // Change register //
	  case unogl::KEY::shift: shift=false; break;
	  default:;
	  }
	}
      }
    }else{
      caret.visible=false;
    }
    otext=text;
  }

  char UNTEXT::charselect(char chr){
    for(unsigned int i=0;charcodetable[0][i];i++)if(charcodetable[0][i]==chr){
	char layer=1;
	if(shift && !caps || !shift && caps)layer++;
	if(layout)layer+=2;
	return charcodetable[layer][i];
      }
  }

  bool UNTEXT::paste(char chr){
    char c[2]; c[0]=chr; c[1]='\0';
    if(caret.absol>=text.length())text+=c;
    else text.insert(caret.absol,c);
    caret.absol++; caret.update();
    return true;
  }
  bool UNTEXT::delet(){
    if(text.length()>0){
      if(caret.absol==0)return false;
      if(caret.absol>text.length())return false;
      caret.absol--;
      text.erase(caret.absol,1);
      caret.update();
      return true;
    }
    return false;
  }

  bool UNTEXT::update(){
    OBJECT::update();
    if(otext!=text)caret.update();
  }

  unsigned int UNTEXT::lines(){
    unsigned int count=0;
    for(unsigned int i=0;i<text.length();i++)if(text[i]='\n')count++;
    return count;
  }

  void UNTEXT::DrawChar(unsigned char ch, vec2 vp){
    glBindTexture(GL_TEXTURE_2D,font->textures[ch]);
    //glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
    glTexCoord2d(0,                0);                glVertex2f(vp.x,                         vp.y+font->poly[ch].z*height);
    glTexCoord2d(0,                font->texc[ch].y); glVertex2f(vp.x,                         vp.y+font->poly[ch].y*height);
    glTexCoord2d(font->texc[ch].x, font->texc[ch].y); glVertex2f(vp.x+font->poly[ch].w*height, vp.y+font->poly[ch].y*height);
    glTexCoord2d(font->texc[ch].x, 0);                glVertex2f(vp.x+font->poly[ch].w*height, vp.y+font->poly[ch].z*height);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,0);
    /*
      glBegin(GL_LINE_STRIP);
      glVertex2f(vp.x,                         vp.y+font->poly[ch].z*height);
      glVertex2f(vp.x,                         vp.y+font->poly[ch].y*height);
      glVertex2f(vp.x+font->poly[ch].w*height, vp.y+font->poly[ch].y*height);
      glVertex2f(vp.x+font->poly[ch].w*height, vp.y+font->poly[ch].z*height);
      cout<<font->poly[ch]<<endl;
      glEnd();
    */
  }
}
