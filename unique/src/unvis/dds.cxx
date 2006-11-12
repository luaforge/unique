/***************************************************************************
 *            dds.cpp
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

#include "image.hxx"

namespace unvis {

# ifdef SUPPORT_TEXTURE_DDS

  struct dds_colorkey {
    unsigned int dwColorSpaceLowValue;
    unsigned int dwColorSpaceHighValue;
  };

  struct dds_header {
    unsigned int magic;
    unsigned int dwSize;
    unsigned int dwFlags;
    unsigned int dwHeight;
    unsigned int dwWidth;
    long lPitch;
    unsigned int dwDepth;
    unsigned int dwMipMapCount;
    unsigned int dwAlphaBitDepth;
    unsigned int dwReserved;
    void *lpSurface;
    dds_colorkey ddckCKDestOverlay;
    dds_colorkey ddckCKDestBlt;
    dds_colorkey ddckCKSrcOverlay;
    dds_colorkey ddckCKSrcBlt;
    unsigned int dwPFSize;
    unsigned int dwPFFlags;
    unsigned int dwFourCC;
    unsigned int dwRGBBitCount;
    unsigned int dwRBitMask;
    unsigned int dwGBitMask;
    unsigned int dwBBitMask;
    unsigned int dwRGBAlphaBitMask;
    unsigned int dwCaps;
    unsigned int dwCaps2;
    unsigned int dwCaps3;
    unsigned int dwVolumeDepth;
    unsigned int dwTextureStage;
  };

  struct dds_color {
    unsigned char r;
    unsigned char g;
    unsigned char b;
  };

  enum {
    DDS_ERROR = -1,
    DDS_RGB,
    DDS_RGBA,
    DDS_DXT1,
    DDS_DXT2,
    DDS_DXT3,
    DDS_DXT4,
    DDS_DXT5
  };

  enum {
    DDPF_ALPHAPIXELS = 0x01,
    DDPF_FOURCC = 0x04,
    DDPF_RGB = 0x40,
    DDPF_RGBA = 0x41
  };

  /*
   */
  unsigned char *::load_dds(const char *name,int &width,int &height) {
    FILE *file = fopen(name,"rb");
    if(!file) {
      fprintf(stderr,"Texture::load_dds(): error open \"%s\" file\n",name);
      return NULL;
    }
    dds_header header;
    fread(&header,sizeof(dds_header),1,file);
    if(header.magic != ('D' | 'D' << 8 | 'S' << 16 | ' ' << 24)) {
      fprintf(stderr,"Texture::load_dds(): wrong magic in \"%s\" file\n",name);
      fclose(file);
      return NULL;
    }
    width = header.dwWidth;
    height = header.dwHeight;
    int format = DDS_ERROR;
    if(header.dwPFFlags & DDPF_FOURCC) {
      if(header.dwFourCC == ('D' | ('X' << 8) | ('T' << 16) | ('1' << 24))) format = DDS_DXT1;
      else if(header.dwFourCC == ('D' | ('X' << 8) | ('T' << 16) | ('2' << 24))) format = DDS_DXT2;
      else if(header.dwFourCC == ('D' | ('X' << 8) | ('T' << 16) | ('3' << 24))) format = DDS_DXT3;
      else if(header.dwFourCC == ('D' | ('X' << 8) | ('T' << 16) | ('4' << 24))) format = DDS_DXT4;
      else if(header.dwFourCC == ('D' | ('X' << 8) | ('T' << 16) | ('5' << 24))) format = DDS_DXT5;
    }
    else if(header.dwPFFlags == DDPF_RGB && header.dwRGBBitCount == 24) format = DDS_RGB;
    else if(header.dwPFFlags == DDPF_RGBA && header.dwRGBBitCount == 32) format = DDS_RGBA;
    if(format == DDS_ERROR) {
      fprintf(stderr,"Texture::load_dds(): unknown format of \"%s\" file\n",name);
      fclose(file);
      return NULL;
    }
    if(format == DDS_DXT2 || format == DDS_DXT4) {
      fprintf(stderr,"Texture::load_dds(): DXT2 or DXT4 is not supported in \"%s\" file\n",name);
      fclose(file);
      return NULL;
    }
    unsigned char *data = new unsigned char[width * height * 4];
    if(format == DDS_RGB) {
      unsigned char *buf = new unsigned char[width * height * 3];
      fread(buf,width * height * 3,1,file);
      unsigned char *src = buf;
      unsigned char *dest = data;
      for(int y = 0; y < height; y++) {
	for(int x = 0; x < width; x++) {
	  *dest++ = *src++;
	  *dest++ = *src++;
	  *dest++ = *src++;
	  *dest++ = 255;
	}
      }
      delete [] buf;
    } else if(format == DDS_RGBA) {
      unsigned char *buf = new unsigned char[width * height * 4];
      fread(buf,width * height * 4,1,file);
      unsigned char *src = buf;
      unsigned char *dest = data;
      for(int y = 0; y < height; y++) {
	for(int x = 0; x < width; x++) {
	  *dest++ = *src++;
	  *dest++ = *src++;
	  *dest++ = *src++;
	  *dest++ = *src++;
	}
      }
      delete [] buf;
    } else {
      unsigned char *buf = new unsigned char[width * height];
      unsigned char *src = buf;
      fread(buf,width * height,1,file);
      for(int y = 0; y < height; y += 4) {
	for(int x = 0; x < width; x += 4) {
	  unsigned long long alpha = 0;
	  unsigned int a0 = 0;
	  unsigned int a1 = 0;
	  if(format == DDS_DXT3) {
	    alpha = *(unsigned long long*)src;
	    src += 8;
	  } else if(format == DDS_DXT5) {
	    alpha = (*(unsigned long long*)src) >> 16;
	    a0 = src[0];
	    a1 = src[1];
	    src += 8;
	  }
	  unsigned int c0 = *(unsigned short*)(src + 0);
	  unsigned int c1 = *(unsigned short*)(src + 2);
	  src += 4;
	  dds_color color[4];
	  color[0].r = ((c0 >> 11) & 0x1f) << 3;
	  color[0].g = ((c0 >> 5) & 0x3f) << 2;
	  color[0].b = (c0 & 0x1f) << 3;
	  color[1].r = ((c1 >> 11) & 0x1f) << 3;
	  color[1].g = ((c1 >> 5) & 0x3f) << 2;
	  color[1].b = (c1 & 0x1f) << 3;
	  if(c0 > c1) {
	    color[2].r = (color[0].r * 2 + color[1].r) / 3;
	    color[2].g = (color[0].g * 2 + color[1].g) / 3;
	    color[2].b = (color[0].b * 2 + color[1].b) / 3;
	    color[3].r = (color[0].r + color[1].r * 2) / 3;
	    color[3].g = (color[0].g + color[1].g * 2) / 3;
	    color[3].b = (color[0].b + color[1].b * 2) / 3;
	  } else {
	    color[2].r = (color[0].r + color[1].r) / 2;
	    color[2].g = (color[0].g + color[1].g) / 2;
	    color[2].b = (color[0].b + color[1].b) / 2;
	    color[3].r = 0;
	    color[3].g = 0;
	    color[3].b = 0;
	  }
	  for(int i = 0; i < 4; i++) {
	    unsigned int index = *src++;
	    unsigned char *dest = data + (width * (y + i) + x) * 4;
	    for(int j = 0; j < 4; j++) {
	      *dest++ = color[index & 0x03].r;
	      *dest++ = color[index & 0x03].g;
	      *dest++ = color[index & 0x03].b;
	      if(format == DDS_DXT1) {
		*dest++ = ((index & 0x03) == 3 && c0 <= c1) ? 0 : 255;
	      } else if(format == DDS_DXT3) {
		*dest++ = (unsigned char)((alpha & 0x0f) << 4);
		alpha >>= 4;
	      } else if(format == DDS_DXT5) {
		unsigned int a = (unsigned int)(alpha & 0x07);
		if(a == 0) *dest++ = a0;
		else if(a == 1) *dest++ = a1;
		else if(a0 > a1) *dest++ = ((8 - a) * a0 + (a - 1) * a1) / 7;
		else if(a > 5) *dest++ = (a == 6) ? 0 : 255;
		else *dest++ = ((6 - a) * a0 + (a - 1) * a1) / 5;
		alpha >>= 3;
	      } else *dest++ = 255;
	      index >>= 2;
	    }
	  }
	}
      }
      delete [] buf;
    }
    fclose(file);
    return data;
  }

# endif

}
