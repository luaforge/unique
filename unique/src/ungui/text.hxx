/***************************************************************************
 *            text.hpp
 *
 *  Wed Jun 29 17:12:37 2005
 *  Copyright  2005  FeniX11
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
#include"font.hxx"
#include"unobj.hxx"

namespace ungui{//tolua_export
  class UNTEXT;
  
  class TEXTCARET{//tolua_export
  protected:
    unsigned int _absol;
    unsigned int _line;
    unsigned int _symb;
    UNTEXT* text;
  public:
    //tolua_begin
    unsigned int absol;// Absolute position
    unsigned int line; // Current line
    unsigned int symb; // Current symbol in line
    char chr;          // Caret symbol
    bool visible;      // Caret visibility
    
    TEXTCARET(UNTEXT*);
    bool update();
    //tolua_end
  };//tolua_export
  class TEXTSPACE{//tolua_export
  public:
    //tolua_begin
    scalar symb; // horizontal between symbols
    scalar line; // vertical between lines
    scalar parag;// vertical between paragraphs
    scalar inden;// horizontal before new paragraph
    TEXTSPACE();
    ~TEXTSPACE();
    //tolua_end
  };//tolua_export
  class UNTEXT: public unobj::OBJECT{//tolua_export
  protected:
    string otext;
    void DrawChar(unsigned char ch, vec2 vp);
  public:
    //tolua_begin
    enum { // Aligning
      left=0x1,
      centr=0x2,
      right=0x4,
      top=0x8,
      middle=0x10,
      bottom=0x20
    };
    unsigned char align;
    enum { // Wraping
      nowrap=0x0,
      perword=0x1,
      perchar=0x2
    };
    bool polyline;   // Poly line text area
    unsigned char wrap;
    bool   into;     // All text into area
    
    // Input state //
    bool      shift; // Change register
    bool      caps;  // Change active register
    unsigned char layout;// Active layout
    // Visual parameters
    FONT*     font;  // Text font
    string    text;  // Text string
    scalar    height;// Text size
    vec2      size;  // Text area size
    vec2      center;// Text area center
    vec4      color; // Text color
    TEXTCARET caret; // Text cursor
    TEXTSPACE space; // Text space
    bool      editable;// Edit enable
    vec2      scroll;// Text scroll
    // Methods
    UNTEXT();
    virtual ~UNTEXT();
    
    void draw(GLenum);
    void event(unogl::GRAPHCONTEXT&);
    bool update();
    // Advanced
    unsigned int lines();
    bool paste(char);
    bool delet();
    char charselect(char chr);
    //tolua_end
  };//tolua_export
}//tolua_export
