#include"unobj.hxx"

// Documatation class OBJECT //
namespace unobj{
  /*
  CLASSINFO(OBJECT,
	    CLASSINFOENT(en_EN,(
				$overview{Generic scene object class.}
				$properties{
				  $property{string name\\object name}
				  $property{bool visible\\object visiblility}
				  $property{vec3 pos\\object position}
				  $property{quat rot\\object rotation}
				  $property{MATERIALS mat\\object materials}
				  $property{GROUP parent\\parent object in objects hierarhy}
				  $property{OBJECT target\\target object for their object}
				  $property{OBJECT locate\\locale object for preset location}
				}
				....to be continued....
				))
	    CLASSINFOENT(ru_RU,(
				$overview{Класс произвольного объекта сцены. Вы можете создавать свои специфические объекты, используя в качестве базового этот. Вы должны использовать полиморфные свойства этого объекта для достижения совместимости с технологической основой lUnique.}
				$properties{
				  $property{string name\\имя объекта}
				  $property{bool visible\\видимость объекта}
				  $property{vec3 pos\\позиция объекта}
				  $property{quat rot\\поворот объекта}
				  $property{MATERIALS mat\\материалы объекта}
				  $property{GROUP parent\\родительский объект в иерархии объектов}
				  $property{OBJECT target\\объект-цель для ориентации данного объекта}
				  $property{OBJECT locate\\локальный реляционный объект}
				}
				....продолжение следует....
				))
	    )

  // Documatation class GROUP //

  CLASSINFO(GROUP,
	    CLASSINFOENT(en_EN,(
				$overview{Generic scene group of objects class. It is logic only group (not relation location  and etc.)}
				....to be continued....
				))
	    CLASSINFOENT(ru_RU,(
				$overview{Класс произвольной группы объектов сцены. Наследует от OBJECT. Это только логическая группа (не добаляет относительное расположение и прочее.)}
				....продолжение следует....
				))
	    )

  // Documatation class SCENE //

  CLASSINFO(SCENE,
	    CLASSINFOENT(en_EN,(
				$overview{Generic scene class.}
				$properties{
				  $property{}
				}
				$methods{
				  $method{}
				}
				....to be continued....
				))
	    CLASSINFOENT(ru_RU,(
				$overview{Произвольный класс сцены. Наследует от GROUP. Вы должны поместить ваши объекты в сцену, чтобы движек работал с ними.}
				$properties{
				  $property{}
				}
				$methods{
				  $method{}
				}
				....продолжение следует....
				))
	    )

  // Documatation class CAMERA //

  CLASSINFO(CAMERA,
	    CLASSINFOENT(en_EN,(
				$overview{}
				$properties{
				  $property{}
				}
				$methods{
				  $method{}
				}
				....to be continued....
				))
	    CLASSINFOENT(ru_RU,(
				$overview{Класс камеры сцены. Наследует от OBJECT.}
				$properties{
				  $property{}
				}
				$methods{
				  $method{}
				}
				....продолжение следует....
				))
	    )

  // Documatation class LIGHT //

  CLASSINFO(LIGHT,
	    CLASSINFOENT(en_EN,(
				$overview{Generic light source class.}
				$properties{
				  $property{}
				
				}
				$methods{
				  $method{}
				
				}
				....to be continued....
				))
	    CLASSINFOENT(ru_RU,(
				$overview{Класс источника света сцены. Наследует от OBJECT.}
				$properties{
				  $property{vec4  ambient\\окружающий свет}
				  $property{vec4  diffuse\\свет источника}
				  $property{vec4  specular\\отраженный свет}
				  $property{float constatten\\постоянный фактор ослабления}
				  $property{float linatten\\линейный фактор ослабления}
				  $property{float quadatten\\квадратичный фактор ослабления}
				  $property{enum LIGHTTYPE type\\тип источника света. Принимаемые значения:
				      $>DIR - направленный источник
				      $>POS - позиционированный источник
				      }
				
				}
				$methods{
				  $method{}
				
				}
				....продолжение следует....
				))
	    )
  */
}
