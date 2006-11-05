/***************************************************************************
 *            sse.cpp
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
#include"sse.hxx"

/*            SSE Optimization              */
namespace _SSE{
  scalar sqrtf_scal(const scalar f){
    scalar r=0.0;
#   if _WIN32 && !_MINGW
    __asm{
        movss   xmm0, f
	
	sqrtss  xmm0, xmm0
	
	movss      r, xmm0
	}
#   endif
#   if _LINUX || _MINGW
    __asm__(
	    "movq  (%%eax), %%mm0\n"
	    
	    "pfrsqrt %%mm0, %%mm0\n"
	    "pfrcp   %%mm0, %%mm0\n"
	    
	    "movd  %%mm0, (%%edx)\n"
	    
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
        mov eax, v
	
	movss   xmm0, [eax+8]
	movlhps xmm0, xmm0
	movlps  xmm0, [eax]
	
	mulps   xmm0, xmm0
	
	movaps  xmm1, xmm0
	shufps  xmm1, xmm1, 00001001b
	addss   xmm0, xmm1
	
	shufps  xmm1, xmm1, 00000001b
	addss   xmm0, xmm1
	
	sqrtss  xmm0, xmm0
	
	movss  [edx], xmm0
	
	mov r, edx
	}
#   endif
#   if _LINUX || _MINGW
    __asm__(
	    "movss 8(%%eax), %%xmm0\n"
	    "movlhps %%xmm0, %%xmm0\n"
	    "movlps (%%eax), %%xmm0\n"
	    
	    "mulps %%xmm0, %%xmm0\n"
	    
	    "movaps %%xmm0, %%xmm1\n"
	    "shufps $0b00001001, %%xmm1, %%xmm1\n"
	    "addss %%xmm1, %%xmm0\n"
	    
	    "shufps $0b00000001, %%xmm1, %%xmm1\n"
	    "addss %%xmm1, %%xmm0\n"
	    
	    "sqrtss %%xmm0, %%xmm0\n"
	  
	    "movss %%xmm0, (%%edx)\n"
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
        mov eax, v
	
	movups  xmm0, [eax]
	
	mulps   xmm0, xmm0
	
	movhlps xmm1, xmm0
	addps   xmm0, xmm1
	
	movss   xmm1, xmm0
	shufps  xmm0, xmm0, 00000001b
	addss   xmm0, xmm1
	
	sqrtss  xmm0, xmm0
	
	movss  r, xmm0
	}
#   endif
#   if _LINUX || _MINGW
    __asm__(
	    "movups (%%eax), %%xmm0\n"
	    
	    "mulps %%xmm0, %%xmm0\n"
	    
	    "movhlps %%xmm0, %%xmm1\n"
	    "addps %%xmm1, %%xmm0\n"
	    
	    "movss %%xmm0, %%xmm1\n"
	    "shufps $0b00000001, %%xmm0, %%xmm0\n"
	    "addss %%xmm1, %%xmm0\n"
	    
	    "sqrtss %%xmm0, %%xmm0\n"
	    
	    "movss %%xmm0, (%%edx)\n"
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
	
	movss xmm0, [eax+8]
	movlhps xmm0, xmm0
	movlps xmm0, [eax]
	movaps xmm1, xmm0
	
	mulps xmm1, xmm1
	
	movaps xmm2, xmm1
	shufps xmm2, xmm2, 00001001b
	addss xmm1, xmm2
	
	shufps xmm2, xmm2, 00000001b
	addss xmm1, xmm2
	
	rsqrtss xmm1, xmm1
	shufps xmm1, xmm1, 00000000b
	
	mulps xmm0, xmm1
	
	movlps [eax], xmm0
	movhlps xmm0, xmm0
	movss [eax+8], xmm0
	}
#   endif
#   if _LINUX || _MINGW
    __asm__(
	    "movss 8(%%eax), %%xmm0\n"
	    "movlhps %%xmm0, %%xmm0\n"
	    "movlps (%%eax), %%xmm0\n"
	    
	    "movaps %%xmm0, %%xmm1\n"
	    
	    "mulps %%xmm1, %%xmm1\n"
	    
	    "movaps %%xmm1, %%xmm2\n"
	    "shufps $0b00001001, %%xmm2, %%xmm2\n"
	    "addss %%xmm2, %%xmm1\n"
	    
	    "shufps $0b00000001, %%xmm2, %%xmm2\n"
	    "addss %%xmm2, %%xmm1\n"
	    
	    "rsqrtss %%xmm1, %%xmm1\n"
	    "shufps $0b00000000, %%xmm1, %%xmm1\n"
	    
	    "mulps %%xmm1, %%xmm0\n"
	    
	    "movlps %%xmm0, (%%eax)\n"
	    "movhlps %%xmm0, %%xmm0\n"
	    "movss %%xmm0, 8(%%eax)\n"
	    :
	    : "a"(&v.x)
	    );
#   endif
  }

  void norm_vec4(vec4& v){
#   if _WIN32 && !_MINGW
    __asm{
        mov eax, v
	
	movups  xmm0,  [eax]
	movaps  xmm1,  xmm0
	
	mulps   xmm1,  xmm1
	
	movhlps xmm2,  xmm1
	addps   xmm1,  xmm2
	
	movss   xmm2,  xmm1
	shufps  xmm1,  xmm1, 00000001b
	addss   xmm1,  xmm2
	
	rsqrtss xmm1,  xmm1
	shufps  xmm1,  xmm1, 00000000b
	
	mulps   xmm0,  xmm1
	
	movups  [eax], xmm0
	}
#   endif
#   if _LINUX || _MINGW
    __asm__(
	    "movups (%%eax), %%xmm0\n"
	    "movaps %%xmm0, %%xmm1\n"
	    
	    "mulps %%xmm1, %%xmm1\n"
	    
	    "movhlps %%xmm1, %%xmm2\n"
	    "addps %%xmm2, %%xmm1\n"
	    
	    "movss %%xmm1, %%xmm2\n"
	    "shufps $0b00000001, %%xmm1, %%xmm1\n"
	    "addss %%xmm2, %%xmm1\n"
	    
	    "rsqrtss %%xmm1, %%xmm1\n"
	    "shufps $0b00000000, %%xmm1, %%xmm1\n"
	    
	    "mulps %%xmm1, %%xmm0\n"
	    
	    "movups %%xmm0, (%%eax)\n"
	    :
	    : "a"(&v.x)
	    );
#   endif
  }
  
  vec3& sub_vec3_vec3(vec3& r, const vec3& v1, const vec3& v2){
#   if _WIN32 && !_MINGW
    __asm{
        mov eax, v1
	mov ebx, v2
	mov edx, r
	
	movups  xmm0, [eax]
	movups  xmm1, [ebx]
	
	subps   xmm0, xmm1
	
	movups [edx], xmm0
	}
#   endif
#   if _LINUX || _MINGW
    __asm__(
	    "movups (%%eax), %%xmm0\n"
	    "movups (%%ebx), %%xmm1\n"
	    
	    "subps   %%xmm1, %%xmm0\n"
	    
	    "movups  %%xmm0, (%%edx)\n"
	    :
	    : "a"(&v1.x), "b"(&v2.x), "d"(&r.x)
	    );
#   endif
    return r;
  }
  
  void dot_vec4_vec4(const vec4& v0, const void *v1, int v1_stride, void *result, int result_stride, int count){
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
	
	movups xmm0, [eax]
	
	label:
	  movups xmm1, [ebx]
	  mulps xmm1, xmm0
	  
	  movhlps xmm2, xmm1
	  addps xmm1, xmm2

	  movss xmm2, xmm1
	  shufps xmm1, xmm1, 00000001b
	  addss xmm1, xmm2
	  movss [edx], xmm1
	  
	  add ebx, ecx
	  add edx, esi
	  
	  dec edi
	  jnz label
	  
	  popa
	  }
#   endif
#   if _LINUX || _MINGW
    __asm__(
	    "movups (%%eax), %%xmm0\n"
	    
	    "1:\n"
	    "movups (%%ebx), %%xmm1\n"
	    
	    "mulps %%xmm0, %%xmm1\n"
	    
	    "movhlps %%xmm1, %%xmm2\n"
	    "addps %%xmm2, %%xmm1\n"
	    
	    "movss %%xmm1, %%xmm2\n"
	    "shufps $0b00000001, %%xmm1, %%xmm1\n"
	    "addss %%xmm2, %%xmm1\n"
	    "movss %%xmm1, (%%edx)\n"
	    
	    "addl %%ecx, %%ebx\n"
	    "addl %%esi, %%edx\n"
	    
	    "decl %%edi\n"
	    "jnz 1b\n"
	    :
	    : "a"(&v0.x), "b"(v1), "c"(v1_stride), "d"(result), "S"(result_stride), "D"(count)
	    );
#   endif
  }

  void mul_mat4_mat4(const mat4& m0, const mat4& m1, mat4& res){
#   if _WIN32 && !_MINGW
    __asm{
        push eax
	push ebx
	push ecx
	
	mov eax, m0
	mov ebx, m1
	mov ecx, res
	
	movups xmm0,[eax]
	movups xmm1,[eax+16]
	movups xmm2,[eax+32]
	movups xmm3,[eax+48]
	movups xmm4,[ebx]
	movaps xmm5, xmm4
	movaps xmm6, xmm4
	movaps xmm7, xmm4
	shufps xmm4, xmm4, 00000000b
	shufps xmm5, xmm5, 01010101b
	shufps xmm6, xmm6, 10101010b
	shufps xmm7, xmm7, 11111111b
	mulps xmm4, xmm0
	mulps xmm5, xmm1
	mulps xmm6, xmm2
	mulps xmm7, xmm3
	addps xmm6, xmm7
	addps xmm4, xmm5
	addps xmm4, xmm6
	movups [ecx], xmm4
	
	movups xmm4, [ebx+16]
	movaps xmm5, xmm4
	movaps xmm6, xmm4
	movaps xmm7, xmm4
	shufps xmm4, xmm4, 00000000b
	shufps xmm5, xmm5, 01010101b
	shufps xmm6, xmm6, 10101010b
	shufps xmm7, xmm7, 11111111b
	mulps xmm4, xmm0
	mulps xmm5, xmm1
	mulps xmm6, xmm2
	mulps xmm7, xmm3
	addps xmm6, xmm7
	addps xmm4, xmm5
	addps xmm4, xmm6
	movups [ecx+16], xmm4
	
	movups xmm4,[ebx+32]
	movaps xmm5, xmm4
	movaps xmm6, xmm4
	movaps xmm7, xmm4
	shufps xmm4, xmm4, 00000000b
	shufps xmm5, xmm5, 01010101b
	shufps xmm6, xmm6, 10101010b
	shufps xmm7, xmm7, 11111111b
	mulps xmm4, xmm0
	mulps xmm5, xmm1
	mulps xmm6, xmm2
	mulps xmm7, xmm3
	addps xmm6, xmm7
	addps xmm4, xmm5
	addps xmm4, xmm6
	movups[ecx+32], xmm4
	
	movups xmm4,[ebx+48]
	movaps xmm5, xmm4
	movaps xmm6, xmm4
	movaps xmm7, xmm4
	shufps xmm4, xmm4, 00000000b
	shufps xmm5, xmm5, 01010101b
	shufps xmm6, xmm6, 10101010b
	shufps xmm7, xmm7, 11111111b
	mulps xmm4, xmm0
	mulps xmm5, xmm1
	mulps xmm6, xmm2
	mulps xmm7, xmm3
	addps xmm6, xmm7
	addps xmm4, xmm5
	addps xmm4, xmm6
	movups [ecx+48], xmm4
	
	pop ecx
	pop ebx
	pop eax
	}
#   endif
#   if _LINUX || _MINGW
    __asm__(
	    "movups (%%eax), %%xmm0\n"
	    "movups 16(%%eax), %%xmm1\n"
	    "movups 32(%%eax), %%xmm2\n"
	    "movups 48(%%eax), %%xmm3\n"
	    
	    "movups (%%ebx), %%xmm4\n"
	    "movaps %%xmm4, %%xmm5\n"
	    "movaps %%xmm4, %%xmm6\n"
	    "movaps %%xmm4, %%xmm7\n"
	    "shufps $0b00000000, %%xmm4, %%xmm4\n"
	    "shufps $0b01010101, %%xmm5, %%xmm5\n"
	    "shufps $0b10101010, %%xmm6, %%xmm6\n"
	    "shufps $0b11111111, %%xmm7, %%xmm7\n"
	    "mulps %%xmm0, %%xmm4\n"
	    "mulps %%xmm1, %%xmm5\n"
	    "mulps %%xmm2, %%xmm6\n"
	    "mulps %%xmm3, %%xmm7\n"
	    "addps %%xmm7, %%xmm6\n"
	    "addps %%xmm5, %%xmm4\n"
	    "addps %%xmm6, %%xmm4\n"
	    "movups %%xmm4, (%%ecx)\n"
	    
	    "movups 16(%%ebx), %%xmm4\n"
	    "movaps %%xmm4, %%xmm5\n"
	    "movaps %%xmm4, %%xmm6\n"
	    "movaps %%xmm4, %%xmm7\n"
	    "shufps $0b00000000, %%xmm4, %%xmm4\n"
	    "shufps $0b01010101, %%xmm5, %%xmm5\n"
	    "shufps $0b10101010, %%xmm6, %%xmm6\n"
	    "shufps $0b11111111, %%xmm7, %%xmm7\n"
	    "mulps %%xmm0, %%xmm4\n"
	    "mulps %%xmm1, %%xmm5\n"
	    "mulps %%xmm2, %%xmm6\n"
	    "mulps %%xmm3, %%xmm7\n"
	    "addps %%xmm7, %%xmm6\n"
	    "addps %%xmm5, %%xmm4\n"
	    "addps %%xmm6, %%xmm4\n"
	    "movups %%xmm4, 16(%%ecx)\n"
	    
	    "movups 32(%%ebx), %%xmm4\n"
	    "movaps %%xmm4, %%xmm5\n"
	    "movaps %%xmm4, %%xmm6\n"
	    "movaps %%xmm4, %%xmm7\n"
	    "shufps $0b00000000, %%xmm4, %%xmm4\n"
	    "shufps $0b01010101, %%xmm5, %%xmm5\n"
	    "shufps $0b10101010, %%xmm6, %%xmm6\n"
	    "shufps $0b11111111, %%xmm7, %%xmm7\n"
	    "mulps %%xmm0, %%xmm4\n"
	    "mulps %%xmm1, %%xmm5\n"
	    "mulps %%xmm2, %%xmm6\n"
	    "mulps %%xmm3, %%xmm7\n"
	    "addps %%xmm7, %%xmm6\n"
	    "addps %%xmm5, %%xmm4\n"
	    "addps %%xmm6, %%xmm4\n"
	    "movups %%xmm4, 32(%%ecx)\n"
	    
	    "movups 48(%%ebx), %%xmm4\n"
	    "movaps %%xmm4, %%xmm5\n"
	    "movaps %%xmm4, %%xmm6\n"
	    "movaps %%xmm4, %%xmm7\n"
	    "shufps $0b00000000, %%xmm4, %%xmm4\n"
	    "shufps $0b01010101, %%xmm5, %%xmm5\n"
	    "shufps $0b10101010, %%xmm6, %%xmm6\n"
	    "shufps $0b11111111, %%xmm7, %%xmm7\n"
	    "mulps %%xmm0, %%xmm4\n"
	    "mulps %%xmm1, %%xmm5\n"
	    "mulps %%xmm2, %%xmm6\n"
	    "mulps %%xmm3, %%xmm7\n"
	    "addps %%xmm7, %%xmm6\n"
	    "addps %%xmm5, %%xmm4\n"
	    "addps %%xmm6, %%xmm4\n"
	    "movups %%xmm4, 48(%%ecx)\n"
	    :
	    : "a"(m0.array), "b"(m1.array), "c"(res.array)
	    );
#   endif
  }
  
  void mul_mat4_vec3(const mat4& m, const void *v, int v_stride, void *result, int result_stride, int count){
    if(count==0) return;
#   if _WIN32 && !_MINGW
    __asm{
        pusha
	
	mov eax, m
	mov ebx, v
	mov ecx, v_stride
	mov edx, result
	mov esi, result_stride
	mov edi, count
	
	movups xmm0, [eax]
	movups xmm1, [eax+16]
	movups xmm2, [eax+32]
	movups xmm3, [eax+48]

	label: 
	  movss xmm4, [ebx+8]
	  movlhps xmm4, xmm4
	  movlps xmm4, [ebx]
	  movaps xmm5, xmm4
	  movaps xmm6, xmm4
	  
	  shufps xmm4, xmm4, 00000000b
	  shufps xmm5, xmm5, 01010101b
	  shufps xmm6, xmm6, 10101010b
	  
	  mulps xmm4, xmm0
	  mulps xmm5, xmm1
	  mulps xmm6, xmm2
	  
	  addps xmm6, xmm3
	  addps xmm4, xmm5
	  addps xmm4, xmm6
	  
	  movlps[edx], xmm4
	  movhlps xmm4, xmm4
	  movss[edx+8], xmm4  
	  
	  add ebx, ecx
	  add edx, esi
	  
	  dec edi
	jnz label
	  
	popa
	  }
#   endif
#   if _LINUX || _MINGW
    __asm__ (
	     "movups (%%eax), %%xmm0\n"
	     "movups 16(%%eax), %%xmm1\n"
	     "movups 32(%%eax), %%xmm2\n"
	     "movups 48(%%eax), %%xmm3\n"
	     
	     "1:\n"
	     
	     "movss 8(%%ebx), %%xmm4\n"
	     "movlhps %%xmm4, %%xmm4\n"
	     "movlps (%%ebx), %%xmm4\n"
	     
	     "movaps %%xmm4, %%xmm5\n"
	     "movaps %%xmm4, %%xmm6\n"
	     
	     "shufps $0b00000000, %%xmm4, %%xmm4\n"
	     "shufps $0b01010101, %%xmm5, %%xmm5\n"
	     "shufps $0b10101010, %%xmm6, %%xmm6\n"
	     
	     "mulps %%xmm0, %%xmm4\n"
	     "mulps %%xmm1, %%xmm5\n"
	     "mulps %%xmm2, %%xmm6\n"
	     
	     "addps %%xmm3, %%xmm6\n"
	     "addps %%xmm5, %%xmm4\n"
	     "addps %%xmm6, %%xmm4\n"
	     
	     "movlps %%xmm4, (%%edx)\n"
	     "movhlps %%xmm4, %%xmm4\n"
	     "movss %%xmm4, 8(%%edx)\n"
	     
	     "addl %%ecx, %%ebx\n"
	     "addl %%esi, %%edx\n"
	     
	     "decl %%edi\n"
	     "jnz 1b\n"
	     :
	     : "a"(m.array), "b"(v), "c"(v_stride), "d"(result), "S"(result_stride), "D"(count)
	     );
#   endif
  }

  void mul_mat4_vec4(const mat4& m, const void *v, int v_stride, void *result, int result_stride, int count){
    if(count==0) return;
#   if _WIN32 && !_MINGW
    __asm{
      pusha
	
	mov eax, m
	mov ebx, v
	mov ecx, v_stride
	mov edx, result
	mov esi, result_stride
	mov edi, count
	
	movups xmm0,[eax]
	movups xmm1,[eax+16]
	movups xmm2,[eax+32]
	movups xmm3,[eax+48]
	
	label: 
      movups xmm4,[ebx]
	movaps xmm5, xmm4
	movaps xmm6, xmm4
	movaps xmm7, xmm4
	
	shufps xmm4, xmm4, 00000000b
	shufps xmm5, xmm5, 01010101b
	shufps xmm6, xmm6, 10101010b
	shufps xmm7, xmm7, 11111111b
	
	mulps xmm4, xmm0
	mulps xmm5, xmm1
	mulps xmm6, xmm2
	mulps xmm7, xmm3
	
	addps xmm6, xmm7
	addps xmm4, xmm5
	addps xmm4, xmm6
	
	movups[edx], xmm4  
	
	add ebx, ecx
	add edx, esi
      
	dec edi
	jnz label
	
	popa
	}
#   endif
#   if _LINUX || _MINGW
    __asm__(
	    "movups (%%eax), %%xmm0\n"
	    "movups 16(%%eax), %%xmm1\n"
	    "movups 32(%%eax), %%xmm2\n"
	    "movups 48(%%eax), %%xmm3\n"
	    
	    "1:\n"
	    
	    "movups (%%ebx), %%xmm4\n"
	    "movaps %%xmm4, %%xmm5\n"
	    "movaps %%xmm4, %%xmm6\n"
	    "movaps %%xmm4, %%xmm7\n"
	    
	    "shufps $0b00000000, %%xmm4, %%xmm4\n"
	    "shufps $0b01010101, %%xmm5, %%xmm5\n"
	    "shufps $0b10101010, %%xmm6, %%xmm6\n"
	    "shufps $0b11111111, %%xmm7, %%xmm7\n"
	    
	    "mulps %%xmm0, %%xmm4\n"
	    "mulps %%xmm1, %%xmm5\n"
	    "mulps %%xmm2, %%xmm6\n"
	    "mulps %%xmm3, %%xmm7\n"
	    
	    "addps %%xmm7, %%xmm6\n"
	    "addps %%xmm5, %%xmm4\n"
	    "addps %%xmm6, %%xmm4\n"
	    
	    "movups %%xmm4, (%%edx)\n"
	    
	    "addl %%ecx, %%ebx\n"
	    "addl %%esi, %%edx\n"
	    
	    "decl %%edi\n"
	    "jnz 1b\n"
	    :
	    : "a"(m.array), "b"(v), "c"(v_stride), "d"(result), "S"(result_stride), "D"(count)
	    );
#   endif
  }
  
  bool toggle(){ // Toggle to using SSE
    ::sqrtf_scal=sqrtf_scal;
    
    ::len_vec3=len_vec3;
    ::len_vec4=len_vec4;
    ::norm_vec3=norm_vec3;
    ::norm_vec4=norm_vec4;
    
    ::sub_vec3_vec3=sub_vec3_vec3;

    ::dot_vec4_vec4=dot_vec4_vec4;
    ::mul_mat4_vec3=mul_mat4_vec3;
    ::mul_mat4_mat4=mul_mat4_mat4;
    ::mul_mat4_vec4=mul_mat4_vec4;

    return true;
  }

}
