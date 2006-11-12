/***************************************************************************
 *            image.hpp
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
#include"undata.hxx"
#include"unogl.hxx"

namespace unvis{
  using namespace undata;

  class IMAGE{
  public:
    enum {// Image formats (OpenGL compatible)
      und  = 0,
      lum  = GL_LUMINANCE,
      luma = GL_LUMINANCE_ALPHA,
      rgb  = GL_RGB,
      rgba = GL_RGBA
    };
    enum {// raster reversion
      hor_line=0x2, // horisontal
      ver_line=0x4, // vertical
    };
  private:
    //static const int sign;
    //bool arrsel;
    //unsigned int selx,sely;
  public:
    static const int sign;
    unsigned char *pixels; // pixels array pointer
    unsigned int height,width;
    unsigned int channels; // num of channels
    unsigned int format;   // OpneGL texture format
    bool on;               // image exist and correct
    // Methods
    IMAGE();
    IMAGE(IMAGE &im){}
    virtual ~IMAGE();
    void PixelsInit();
    void PixelsDest();
    // Reading
    bool Load(STREAM& ibuf);
    
    virtual bool Read(STREAM& buf);
    
    bool ReadPNG(STREAM& buf);
    bool ReadTGA(STREAM& buf);
    bool ReadJPG(STREAM& buf);
    bool ReadAJP(STREAM& buf);
    
    // Raster working
    void AddAlpha(unsigned char *buf,unsigned int stp);
    bool ReplPix(unsigned int ox,unsigned int oy,unsigned int tx,unsigned int ty);
    bool Reverse(int orr);
    void RevHor();
    void Inverse();
    static const char className[];
  };
  
  class IMPNG: public IMAGE{
  private:
  public:
    static const int sign;
    virtual bool Read(STREAM&res);
    
    static const char className[];
  };
  
  class IMTGA: public IMAGE{
  private:
  public:
    static const int sign;
    virtual bool Read(STREAM&res);
    
    static const char className[];
  };

  class IMJPG: public IMAGE{
  private:
  public:
    static const int sign;
    virtual bool Read(STREAM&res);
    
    static const char className[];
  };
  
  class IMAJP: public IMAGE{
  private:
  public:
    static const int sign;
    virtual bool Read(STREAM&res);
    
    static const char className[];
  };
}
# define SIGN_BYTES 4
