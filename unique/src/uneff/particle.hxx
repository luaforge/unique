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
    struct PART{// Описание частицы
      bool active; // Активность частицы
      float life;  // Жизнь частицы [1.0 > 0.0] насколько жива частица
      float fade;  // Скорость умирания частицы
      vec4 color;  // Цвет частицы
      vec3 pos;    // Позиция частицы
      vec3 speed;  // Скорость частицы
      vec3 grav;   // Зравитация, действующая на скорость частицы
      int  index;  // Индекс частицы по типу
      
      PART(){}
      ~PART(){}		
    };
  protected:
    std::deque<PART> particle;  // Массив частиц
    float popul;                // Контроллер популяции частиц (процесс изменения их числа)
    float popfg;
  public:
    //tolua_begin
    enum {// Тип примитивов, используемых в качестве частицы
      tpoint=GL_POINTS,    // Точки
      tline =GL_LINES,     // Линии
      ttria =GL_TRIANGLES, // Треугольники
      tquad =GL_QUADS      // Прямоугольники, которые, кстати, можно текстурировать
    };
    
    vec3   gravity; // Глобальная гравитация
    vec4   dispers; // Разброс начальных скоростей частиц
    scalar mass;    // Масса частиц
    vec2   factor;  // Скорость умирания минимальная и диапазон
    vec3   source;  // Простаранство-источник
    scalar quant;   // Размер кванта симуляции (чем меньше тем больше расчетов и медленнее работает)
    
    unsigned int num;// Число частиц
    int   geompart;  // Тип геометрии для частицы
    vec4  psize;     // Размер частиц
    
    PARTICLE();
    virtual ~PARTICLE();
    
    void draw(GLenum mode=unobj::RENDERMODE::geom|unobj::RENDERMODE::matl);                  // Прорисовка системы частиц
    void step(unbase::TIME&);           // Шаг моделирования системы
    
    operator string();
    //tolua_end
    scalar FadeCalc();
    void drawpart(PART* node);// Рисовка i-той частицы
    void ReGen(std::deque<PART>::iterator node);   // Регенерация умершей частицы
    //void Gen();
    unsigned int CurNum()const{return particle.size();}
  };//tolua_export
}//tolua_export
