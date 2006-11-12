#include "unvis.hxx"

using namespace unvis;
/*
CLASSINFO(TEXFUNC,
	  CLASSINFOENT(en_EN,(
			      $overview{Info about Class TEXFUNC}
			      ))
	  CLASSINFOENT(ru_RU,(
			      $overview{С помощью этого поля вы можете установить режим наложения текстуры выбранного текстурного модуля. Поддерживаются как стандартные режимы, так и режимы, устанавливаемые расширениями OpenGL. Также поддерживаются текстурные комбайны.}
			      $properties{
				$property{enum type\\функция наложения. Может принимать следующие значения, определенные в $@
					    $> replace  - замещение цвета фрагмента (C=Ct, A=At)
					    $> modulate - модуляция (C=Cf*Ct, A=Af*At)
					    $> decal    - декалирование (C=Cf*(1-At)+Ct*At, A=Af)
					    $> blend    - блендинг (С=Cf*(1-Ct)+Cc*Ct, A=Af*At)
					    $> add      - суммирование (C=Cf+Ct, A=Af+At)
					    $> combine  - комбинирование (Выбор включает механизм текстурных комбайнов)
					    }
				$property{enum combine_rgb\\комбинирование по RGB. Может принимать значения, определенные в $@
					    $> replace  - замещение (Arg0)
					    $> modulate - модуляция (Arg0*Arg1)
					    $> add      - добавление (Arg0+Arg1)
					    $> adds     - добавление знаковое (Arg0+Arg1-0.5)
					    $> sub      - вычитание (Arg0-Arg1)
					    $> interpol - интерполяция (Arg0*(Arg2)+Arg1*(1-Arg2))
					    $> dot3rgb  - скалярное произведение (Arg0 <dotprod> Arg1)
					    $> dot3rgba - скалярное произведение (Arg0 <dotprod> Arg1)
					    }
				$property{enum combine_alpha\\комбинирование по Альфа. Может принимать значения, определенные в $@ аналогичные combine_rgb}
				$property{float scale_rgb\\масштабирование результирующего RGB цвета фрагмента}
				$property{float scale_alpha\\масштабирование результирующего Альфа канала фрагмента}
				$property{TEXFUNCPAR src[3]\\источники для текстурного комбайна}
				$property{TEXFUNCPAR opr[3]\\операнды текстурного комбайна}
			      }
			      $methods{}))
	  );
CLASSINFO(TEXFUNCPAR,
	  CLASSINFOENT(ru_RU,(
			      $overview{Это поле используется для настройки операндов текстурного комбайна.}
			      $properties{
				$property{enum rgb\\источник или операнд для RGB компонент. Может принимать значения, определенные в TEXFUNC для источника.
					    $> primary  - первичный цвет фрагмента
					    $> texture  - цвет тексела текстуры текущего текстурного модуля
					    $> constant - константный переданный цвет
					    $> previos  - результирующий цвет предыдущего текстурного комбайна
					    Для операнда
					    $> src_color - цвет источника
					    $> one_minus_src_color - первичный цвет минус цвет источника
					    $> src_alpha - альфа источника
					    $> one_munis_src_alpha - первичная цвет минус альфа источника
					    }
				$property{enum alpha\\источник или операнд для Альфа компоненты. Может принимать значения аналогичные rgb}
			      }
			      ))
	  );
CLASSINFO(TEXCRD,
	  CLASSINFOENT(en_EN,(
			      $overview{Info about Class TEXFUNC}
			      ))
	  );
*/
