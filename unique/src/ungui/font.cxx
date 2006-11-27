/***************************************************************************
 *            font.cpp
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

#include"font.hxx"

namespace ungui{
  inline int next_p2(int a){
    int rval=1;
    while(rval<a) rval<<=1;
    return rval;
  }

  bool FONT::MakeChar(unsigned int ch){
    if(FT_Load_Glyph(face,FT_Get_Char_Index(face,ch),FT_LOAD_DEFAULT)){ // load Glyph for char
      state=unbase::STATE(false,"FT_Load_Glyph failed"); return false; }//std::runtime_error("FT_Load_Glyph failed");
    FT_Glyph glyph;
    if(FT_Get_Glyph(face->glyph,&glyph)){ // Get faces from glyph to Glyph.
      state=unbase::STATE(false,"FT_Get_Glyph failed"); return false; }//std::runtime_error("FT_Get_Glyph failed");
    FT_Glyph_To_Bitmap(&glyph,ft_render_mode_normal,0,1);// Convert glyph to bitmap.
    FT_BitmapGlyph bitmap_glyph=(FT_BitmapGlyph)glyph;
    FT_Bitmap& bitmap=bitmap_glyph->bitmap;
  
    // Используем нашу вспомогательную функцию, чтобы получить ширину данные
    // побитового отображения, это нам нужно для того, чтобы создать нашу текстуру.
    unsigned int width=next_p2(bitmap.width);
    unsigned int height=next_p2(bitmap.rows);
    GLubyte* expanded_data=new GLubyte[2*width*height];
  
    // Здесь мы заполняем данные для расширенного побитового отображения.
    // Обратите внимание как мы использовали два канальных побитовых отображения
    // (за luminocity и за альфы), но мы назначаем как luminocity так и альфе
    // величину, которую мы находим в побитовом отображении FreeType.
    // Мы используем ?: оператор чтобы величина которую мы используем была 0,
    // если мы - в заполняемой зоне, и все, что вне этой зоны заменяем
    // на побитовое изображение Freetype в противном случае.
    for(unsigned int j=0;j<height;j++)for(unsigned int i=0;i<width;i++){
	expanded_data[2*(i+j*width)]=(i>=bitmap.width || j>=bitmap.rows)?0:bitmap.buffer[i+bitmap.width*j];
	//expanded_data[2*(i+j*width)+1]=(expanded_data[2*(i+j*width)]>128)?255:0;
	expanded_data[2*(i+j*width)+1]=expanded_data[2*(i+j*width)];
      }
    // Set texture parameters
    glBindTexture(GL_TEXTURE_2D,textures[ch]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    //glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_LUMINANCE_ALPHA,GL_UNSIGNED_BYTE,expanded_data);
    glBindTexture(GL_TEXTURE_2D,0);
    delete[]expanded_data;
  
    poly[ch]=vec4(float(bitmap_glyph->left)           /(float)density,// Calc polygon for char
		  float(bitmap_glyph->top-bitmap.rows)/(float)density,
		  float(bitmap_glyph->top)            /(float)density,
		  float(bitmap.width)                 /(float)density );
    texc[ch]=vec2(float(bitmap.width)/float(width),float(bitmap.rows)/float(height));// Calc texture coords for char
    return true;
  }

  FONT::FONT():density(12){
    textures[0]=0;
    if(!FT_Init_FreeType(&library))state=unbase::STATE(false,"FT_Init_FreeType failed"); //std::runtime_error("FT_Init_FreeType failed");
  }
  FONT::FONT(string n):density(12){
    src=n;
    textures[0]=0;
    if(!FT_Init_FreeType(&library))state=unbase::STATE(false,"FT_Init_FreeType failed"); //std::runtime_error("FT_Init_FreeType failed");
    update();
  }
  FONT::~FONT(){
    if(textures)glDeleteTextures(FLIMIT,textures);
    FT_Done_FreeType(library);
  }

  bool FONT::update(){
    if(src!=osrc||density!=odensity){
      if(density<5)density=5;
      odensity=density;
      osrc=src;
      undata::RESOURCE r=undata::resource(src,"fontdata");
      if(r.type==undata::RESOURCE::stm&&r.access&undata::STREAM::inp){
	undata::STREAM s=r.stream();
	FT_Byte* d=new FT_Byte[s.length()];
	s.read(d,s.length());
	FT_Long l=s.gcount();
	if(l!=s.length())
	  state=unbase::STATE(false,"Stream failed");
	if(!FT_New_Memory_Face(library,d,l,0,&face)) // Create faces
	  state=unbase::STATE(false,"FT_New_Face failed (there is probably a problem with your font file)");
	//std::runtime_error("FT_New_Face failed (there is probably a problem with your font file)");
	// Select charmap
	FT_CharMap found=0;
	FT_CharMap charmap;
	unsigned int my_platform_id=3;
	unsigned int my_encoding_id=1;
	unsigned int n;
	for(n=0;n<face->num_charmaps;n++){
	  charmap=face->charmaps[n];
	  if(charmap->platform_id==my_platform_id && charmap->encoding_id==my_encoding_id){found=charmap;break;}
	}
	if(!found){state=unbase::STATE(false,"FT_Select_CharMap error");return false;} //std::runtime_error("FT_Select_CharMap error");
	if(!FT_Set_Charmap(face,found))state=unbase::STATE(false,"FT_Set_CharMap error"); //std::runtime_error("FT_Set_CharMap error");
	FT_Set_Char_Size(face,density<<6,density<<6,96,96);
      
	if(textures[0])glDeleteTextures(FLIMIT,textures);
	glGenTextures(FLIMIT,textures);
	for(unsigned int i=0;i<FLIMIT;i++)if(!MakeChar(i)){return false;}
	c_space=face->glyph->advance.x>>6/density;
      
	FT_Done_Face(face); // Close faces
	state=unbase::STATE(true,"font created normaly");
	return true;
      }
    }
    return false;
  }
}
