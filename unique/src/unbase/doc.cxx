#include"unbase.hxx"
using namespace unbase;

CLASSINFO(STATE,
	  CLASSINFOENT(ru_RU,(
			      $overview{Класс состояния объекта.
				  Объект может находится в нормальном состоянии (state==true) и состоянии ошибки (state==false).}
			      $properties{
				$property{string msg\\строка сообщения состояния}
				$property{bool state\\текущее состояние}
				$property{int code\\числовой код систояния}
			      }
			      $methods{
				$method{new()\\конструктор по умолчанию}
				$method{new(string)\\конструктор с сообщением о состоянии ошибки (state=false)}
				$method{new(bool)\\конструктор с установкой нужного состояния}
				$method{new(bool,string)\\конструктор с установкой нужного состояния и сообщения}
				$method{new(string,bool)\\конструктор с установкой нужногосообщения и состояния}
			      }
			      ))
	  CLASSINFOENT(en_EN,(
			      $overview{This class is an object state.}
			      $properties{
				$property{string msg\\state message string}
				$property{bool state\\current state}
				$property{int code\\state numeric code}
			      }
			      $methods{
				$method{new()\\default constructor}
				$method{new(string)\\error message constructor (state=false)}
				$method{new(bool)\\set required state constructor}
				$method{new(bool,string)\\set required state and message constructor}
				$method{new(string,bool)\\set required message and state constructor}
			      }
			      )
		       )
	  )

CLASSINFO(TIME,
	  CLASSINFOENT(ru_RU,(
			      $overview{Комплексная переменная времени}
			      $properties{
				$property{double time\\время в секундах}
				$property{double delta\\изменение времени}
				$property{double lambda\\скорость изменения времени}
			      }
			      )
		       )
	  )
