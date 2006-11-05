/***************************************************************************
 *            3dnow.cpp
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

#include"unmath.hxx"
#include"3dnow.hxx"

namespace _3DNOW{
/*    3DNOW!   Optimization    */
  scalar sqrtf_scal(const scalar f){
    scalar r=0.0;
#   if _WIN32 && !_MINGW
    __asm{
      movd  mm0, f
	
	pfrsqrt mm0, mm0
	pfrcp   mm0, mm0
	
	movd    r, mm0
	
	femms
	}
#   endif
#   if _LINUX || _MINGW
    __asm__(
	    "movq  (%%eax), %%mm0\n"
	    
	    "pfrsqrt %%mm0, %%mm0\n"
	    "pfrcp   %%mm0, %%mm0\n"
	    
	    "movd    %%mm0, (%%edx)\n"
	    
	    "femms\n"
	    :
	    : "a"(&f), "d"(&r)
	    );
#   endif
    return r;
  }

  scalar len_vec3(const vec3& v){
    scalar r=0.0;
#   if _WIN32 && !_MINGW
    __asm{
      mov   eax, v
	
	movq  mm0, [eax]
	movd  mm1, [eax+8]
	
	movq  mm2, mm0
	movq  mm3, mm1
	
	pfmul   mm2, mm0
	pfmul   mm3, mm1
	
	pfacc   mm2, mm2
	pfadd   mm2, mm3
	pfrsqrt mm2, mm2
	
	pfrcp   mm2, mm2
	movd    r, mm2
	
	femms
	}
#   endif
#   if _LINUX || _MINGW
    __asm__(
	    "movq  (%%eax), %%mm0\n"
	    "movd 8(%%eax), %%mm1\n"
	    
	    "movq  %%mm0, %%mm2\n"
	    "movq  %%mm1, %%mm3\n"
	    
	    "pfmul   %%mm0, %%mm2\n"
	    "pfmul   %%mm1, %%mm3\n"
	    
	    "pfacc   %%mm2, %%mm2\n"
	    "pfadd   %%mm3, %%mm2\n"
	    "pfrsqrt %%mm2, %%mm2\n"
	    
	    "pfrcp   %%mm2, %%mm2\n"
	    "movd  %%mm2, (%%edx)\n"
	    
	    "femms\n"
	    :
	    : "a"(&v.x), "d"(&r)
	    );
#   endif
    return r;
  }
  
  scalar len_vec4(const vec4& v){
    scalar r=0.0;
#   if _WIN32 && !_MINGW
    __asm{
      mov   eax, v
	
	movq  mm0, [eax]
	movq  mm1, [eax+8]
	
	movq  mm2, mm0
	movq  mm3, mm1
	
	pfmul   mm2, mm0
	pfmul   mm3, mm1
	
	pfacc   mm2, mm3
	pfacc   mm2, mm2
	pfrsqrt mm2, mm2
	
	pfrcp   mm2, mm2
	movd    r, mm2
	
	femms
	}
#   endif
#   if _LINUX || _MINGW
    __asm__(
	    "movq  (%%eax), %%mm0\n"
	    "movq 8(%%eax), %%mm1\n"
	    
	    "movq  %%mm0, %%mm2\n"
	    "movq  %%mm1, %%mm3\n"
	    
	    "pfmul   %%mm0, %%mm2\n"
	    "pfmul   %%mm1, %%mm3\n"
	    
	    "pfacc   %%mm3, %%mm2\n"
	    "pfacc   %%mm2, %%mm2\n"
	    "pfrsqrt %%mm2, %%mm2\n"
	    
	    "pfrcp   %%mm2, %%mm2\n"
	    "movd  %%mm2, (%%edx)\n"
	    
	    "femms\n"
	    :
	    : "a"(&v.x), "d"(&r)
	    );
#   endif
    return r;
  }
  
  void norm_vec3(vec3& v){
#   if _WIN32 && !_MINGW
    __asm{
      mov eax, v
	
	movq     mm0, [eax]
	movd     mm1, [eax+8]
	
	movq     mm2, mm0
	movq     mm3, mm1
	
	pfmul    mm2, mm0
	pfmul    mm3, mm1
	
	pfacc    mm2, mm2
	pfadd    mm2, mm3
	
	pfrsqrt  mm2, mm2
	
	pfmul    mm0, mm2
	pfmul    mm1, mm2
	
	movq   [eax], mm0
	movd [eax+8], mm1
	
	femms
	}
#   endif
#   if _LINUX || _MINGW
    __asm__(
	    "movq (%%eax), %%mm0\n"
	    "movd 8(%%eax), %%mm1\n"
	    
	    "movq %%mm0, %%mm2\n"
	    "movq %%mm1, %%mm3\n"
	    
	    "pfmul %%mm0, %%mm2\n"
	    "pfmul %%mm1, %%mm3\n"
	    
	    "pfacc %%mm2, %%mm2\n"
	    "pfadd %%mm3, %%mm2\n"
	    
	    "pfrsqrt %%mm2, %%mm2\n"
	    
	    "pfmul %%mm2, %%mm0\n"
	    "pfmul %%mm2, %%mm1\n"
	    
	    "movq %%mm0, (%%eax)\n"
	    "movd %%mm1, 8(%%eax)\n"
	    
	    "femms\n"
	    :
	    : "a"(&v.x)
	    );
#   endif
  }
  
  void norm_vec4(vec4& v){
#   if _WIN32 && !_MINGW
    __asm{
      mov eax, v
	
	movq mm0, [eax]
	movq mm1, [eax+8]
	
	movq mm2, mm0
	movq mm3, mm1
	
	pfmul mm2, mm0
	pfmul mm3, mm1
	
	pfacc mm2, mm3
	pfacc mm2, mm2
	pfrsqrt mm2, mm2
	
	pfmul mm0, mm2
	pfmul mm1, mm2
	
	movq [eax], mm0
	movq [eax+8], mm1
	
	femms
	}
#   endif
#   if _LINUX || _MINGW
    __asm__(
	    "movq (%%eax), %%mm0\n"
	    "movq 8(%%eax), %%mm1\n"
	    
	    "movq %%mm0, %%mm2\n"
	    "movq %%mm1, %%mm3\n"
	    
	    "pfmul %%mm0, %%mm2\n"
	    "pfmul %%mm1, %%mm3\n"
	    
	    "pfacc %%mm3, %%mm2\n"
	    "pfacc %%mm2, %%mm2\n"
	    "pfrsqrt %%mm2, %%mm2\n"
	    
	    "pfmul %%mm2, %%mm0\n"
	    "pfmul %%mm2, %%mm1\n"
	    
	    "movq %%mm0, (%%eax)\n"
	    "movq %%mm1, 8(%%eax)\n"
	    
	    "femms\n"
	    :
	    : "a"(&v.x)
	    );
#   endif
  }
  
  static vec3& sub_vec3_vec3(vec3& r, const vec3& v1, const vec3& v2){
#   if _WIN32 && !_MINGW
    __asm{
      mov eax, v1
	mov ebx, v2
	mov edx, r
	
	movq     mm0, [eax]
	movd     mm1, [eax+8]
	movq     mm2, [ebx]
	movd     mm3, [ebx+8]
	
	pfsub    mm0, mm2
	pfsub    mm1, mm3
	
	movq   [edx], mm0
	movd [edx+8], mm1
	}
#   endif
#   if _LINUX || _MINGW
    __asm__(
	    "movq    (%%eax),  %%mm0\n"
	    "movd   8(%%eax),  %%mm1\n"
	    "movq    (%%eax),  %%mm2\n"
	    "movd   8(%%eax),  %%mm3\n"
	    
	    "pfsub     %%mm2,  %%mm0\n"
	    "pfsub     %%mm3,  %%mm1\n"
	    
	    "movq      %%mm0,  (%%edx)\n"
	    "movd      %%mm1, 8(%%edx)\n"
	    :
	    : "a"(&v1.x), "b"(&v2.x), "d"(&r.x)
	    );
#   endif
    return r;
  }
  
  static vec4& sub_vec4_vec4(vec4& r, const vec4& v1, const vec4& v2){
#   if _WIN32 && !_MINGW
    __asm{
      mov eax, v1
	mov ebx, v2
	mov edx, r
	
	movq     mm0, [eax]
	movq     mm1, [eax+8]
	movq     mm2, [ebx]
	movq     mm3, [ebx+8]
	
	pfsub    mm0, mm2
	pfsub    mm1, mm3
	
	movq   [edx], mm0
	movq [edx+8], mm1
	}
#   endif
#   if _LINUX || _MINGW
    __asm__(
	    "movq    (%%eax),  %%mm0\n"
	    "movq   8(%%eax),  %%mm1\n"
	    "movq    (%%eax),  %%mm2\n"
	    "movq   8(%%eax),  %%mm3\n"
	    
	    "pfsub     %%mm2,  %%mm0\n"
	    "pfsub     %%mm3,  %%mm1\n"
	    
	    "movq      %%mm0,  (%%edx)\n"
	    "movq      %%mm1, 8(%%edx)\n"
	    :
	    : "a"(&v1.x), "b"(&v2.x), "d"(&r.x)
	    );
#   endif
    return r;
  }
  
  static void dot_vec4_vec4(const vec4& v0, const void *v1, int v1_stride, void *result, int result_stride, int count){
    if(count==0) return;
#   if _WIN32 && !_MINGW
    __asm{
      pusha
	
	mov eax, v0
	mov ebx, v1
	mov ecx, v1_stride
	mov edx, result
	mov esi, result_stride
	mov edi, count
	
	movq mm0, [eax]
	movq mm1, [eax+8]
	
	label:
      movq mm2, [ebx]
	movq mm3, [ebx+8]
	pfmul mm2, mm0
	pfmul mm3, mm1
	
	pfadd mm3, mm2
	pfacc mm3, mm3
	
	movd [edx], mm3
	
	add ebx, ecx
	add edx, esi
	
	dec edi
	jnz label
	
	femms
	
	popa
	}
#   endif
#   if _LINUX || _MINGW
    __asm__(
	    "movq (%%eax), %%mm0\n"
	    "movq 8(%%eax), %%mm1\n"
	    
	    "1:\n"
	    
	    "movq (%%ebx), %%mm2\n"
	    "movq 8(%%ebx), %%mm3\n"
	    
	    "pfmul %%mm0, %%mm2\n"
	    "pfmul %%mm1, %%mm3\n"
	    
	    "pfadd %%mm2, %%mm3\n"
	    "pfacc %%mm3, %%mm3\n"
	    
	    "movd %%mm3, (%%edx)\n"
	    
	    "addl %%ecx, %%ebx\n"
	    "addl %%esi, %%edx\n"
	    
	    "decl %%edi\n"
	    "jnz 1b\n"
	    
	    "femms\n"
	    :
	    : "a"(& v0.x), "b"(v1), "c"(v1_stride), "d"(result), "S"(result_stride), "D"(count)
	    );
#   endif
  }
  
  bool toggle(){
    ::sqrtf_scal=sqrtf_scal;
    
    ::len_vec3=len_vec3;
    ::len_vec4=len_vec4;
    ::norm_vec3=norm_vec3;
    ::norm_vec4=norm_vec4;
    
    ::sub_vec3_vec3=sub_vec3_vec3;
    
    ::dot_vec4_vec4=dot_vec4_vec4;

    return true;
  }
}
