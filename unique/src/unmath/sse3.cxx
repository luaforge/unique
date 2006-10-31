/***************************************************************************
 *            sse3.cpp
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

namespace _SSE3{
# ifdef SSE3_ENABLE  /*     SSE 3 Optimization     */
  void dot_vec4_vec4(const vec4& v0, const void *v1, int v1_stride, void *result, int result_stride, int count){
    if(count==0) return;
#   ifdef _WIN32
    __asm{
      mov eax, v0
	mov ebx, v1
	mov ecx, v1_stride
	mov edx, result
	
	mov esi, result_stride
	mov edi, count
	
	// Effective Code
	movups xmm0, [eax]
	
	label:
      movups xmm1, [ebx]
	
	mulps xmm1, xmm0
	
	haddps xmm1, xmm1
	haddps xmm1, xmm1
	movss [edx], xmm1
	
	addl ebx, ecx
	addl edx, esi
	
	decl edi
	jnz label
	}
#   else 
    __asm__ (
	     "movups (%%eax), %%xmm0\n"
	     
	     "1:\n"
	     "movups (%%ebx), %%xmm1\n"
	     
	     "mulps %%xmm0, %%xmm1\n"
	     
	     "haddps %%xmm1, %%xmm1\n"
	     "haddps %%xmm1, %%xmm1\n"
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
# endif
  bool toggle(){
# ifdef SSE3_ENABLE
    ::dot_vec4_vec4=dot_vec4_vec4;
# endif
	return true;
  }
}
