/***************************************************************************
 *            font.hpp
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

#pragma once
#include"unbase.hxx"
#include"unvis.hxx"

#include<vector>
#include<string>

//Используем STD библиотеку для обработки исключений
# include <stdexcept>

# include<ft2build.h>
# include<freetype/freetype.h>
# include<freetype/ftglyph.h>
# include<freetype/ftoutln.h>
# include<freetype/fttrigon.h>

namespace ungui{//tolua_export
  using std::vector;
  using std::string;

# define FLIMIT 256

  class FONT: public unvis::TEXTURE{//tolua_export
  protected:
    FT_Library library; // FreeType font library
    FT_Face    face;    // Font face
    
    float c_space;
    unsigned int odensity;
    
    bool MakeChar(unsigned int ch);
  public:
    GLuint textures[FLIMIT]; // OpenGL texture identifiers
    vec4 poly[FLIMIT];       // Texture polygones
    vec2 texc[FLIMIT];       // Texture coords in polygones
    //tolua_begin
    unsigned int density; // font height (in pixels)
    
    FONT();
    FONT(string);
    virtual ~FONT();
    
    bool update();// Создание шрифта из файла
    //tolua_end
  };//tolua_export
}//tolua_export
