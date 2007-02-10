/***************************************************************************
 *            particle.hpp
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
#include"unobj.hxx"
#include<deque>

namespace uneff{//tolua_export
  class PARTICLE: public unobj::OBJECT{//tolua_export
  public:
    struct PART{// �������� �������
      bool active; // ���������� �������
      float life;  // ����� ������� [1.0 > 0.0] ��������� ���� �������
      float fade;  // �������� �������� �������
      vec4 color;  // ���� �������
      vec3 pos;    // ������� �������
      vec3 speed;  // �������� �������
      vec3 grav;   // ����������, ����������� �� �������� �������
      int  index;  // ������ ������� �� ����
      
      PART(){}
      ~PART(){}		
    };
  protected:
    std::deque<PART> particle;  // ������ ������
    float popul;                // ���������� ��������� ������ (������� ��������� �� �����)
    float popfg;
  public:
    //tolua_begin
    enum {// ��� ����������, ������������ � �������� �������
      tpoint=GL_POINTS,    // �����
      tline =GL_LINES,     // �����
      ttria =GL_TRIANGLES, // ������������
      tquad =GL_QUADS      // ��������������, �������, ������, ����� ��������������
    };
    
    unmath::vec3 gravity; // Gravitation
    unmath::vec4 dispers; // Dispersion
    float mass; // Mass
    unmath::vec2 factor; // Quench speed and it range
    unmath::vec3 source; // Source area
    float quant; // Simulation quant
    
    unsigned int num; // Num of particles
    int geompart; // Particle geometry
    unmath::vec4 psize; // Particle size
    
    PARTICLE();
    virtual ~PARTICLE();
    
    virtual void bind_location();
    virtual void draw_geom(const unobj::MODE&);
    void step(const unbase::TIME&);
    
    operator string();
    //tolua_end
    scalar FadeCalc();
    void drawpart(PART*);
    void ReGen(std::deque<PART>::iterator node);
    //void Gen();
    unsigned int CurNum()const{return particle.size();}
  };//tolua_export
}//tolua_export
