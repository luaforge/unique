#include"unmath.hxx"
using namespace unmath;

CLASSINFO(vec2,
  CLASSINFOENT(ru_RU,(
		  Класс 'vec2'
		  Модуль: 'unmath'"EL
		  "Значение:"EL
		  "  Двух компонентный вектор. Имеет псевдонимы для своих компонент."EL
		  "Свойства:"EL
		  "       [0],[1]     - интерпретация как массив"EL
		  "  scalar x, y      - как компоненты вектора"EL
		  "         u, v      - как компоненты текстурной UV карты"EL
		  "         s, t      - как компоненты текстурной карты OpenGL"EL
		  "         G, A      - как цветовые компоненты"EL
		  "         a, b      - компоненты a,b"EL
		  "      left, right  - слева и справа"EL
		  "     width, height - ширина и высота"EL
		  "    bottom, top    - сверху и снизу"EL
		  "     pnear, pfar   - ближний дальний"EL
		  "    radius, angle  - радиус и угол"EL
		  "Конструктор:"EL
		  "  new() - конструктор по умолчанию"EL
		  "  new(scalar x,scalar y)"EL
		  "  new(vec2)"EL
		  "  new(vec3)"EL
		  "  new(vec4)"EL
		  "Операции:"EL
		  "  bool ==(vec2)  - равенство"EL
		  "  vec2 +(vec2)   - покомпонентное сложение"EL
		  "  vec2 +(scalar) - прибавление костанты"EL
		  "  vec2 -(vec2)   - покомпонентное вычитание"EL
		  "  vec2 *(scalar) - масштабирование"EL
		  "  vec2 /(scalar) - обратное масштабирование"EL
		  "  scalar *(vec2) - покомпонентное произведение"EL
		  "  vec2 ^(vec2)   - хм ;)"EL
		  "  vec2 /(vec2)   - покомпонентное деление"EL
		  "  vec2 -()       - отрицание"EL
		  "Методы:"EL
		  "  scalar len()              - длина"EL
		  "  scalar sqlen()            - квадрат длины"EL
		  "  vec2   norm()             - нормализация вектора"EL
		  "  vec2   sat()              - сатурация вектора"EL
		  "  vec2   scale(vec2 v)      - покомпонентное масштабирование "EL
		  "  vec2   dec2pol()          - из декартовой в полярную ск"EL
		  "  vec2   pol2dec()          - из полярной в декартовую ск"EL
		  "  vec2   rotate(scalar fov) - поворот на угол"EL
		  )
	)
)

string vec3::__info(string lang){
  if(lang==RU)
    return string(
    );
  else
    return string(
    );
}

string vec4::__info(string lang){
  if(lang==RU)
    return string(
    );
  else
    return string(
    );
}

string mat3::__info(string lang){
  if(lang==RU)
    return string(
    );
  else
    return string(
    );
}

string mat4::__info(string lang){
  if(lang==RU)
    return string(
    );
  else
    return string(
    );
}

string quat::__info(string lang){
  if(lang==RU)
    return string(
    );
  else
    return string(
    );
}
