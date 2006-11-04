#include"data.hxx"
using namespace undata;

CLASSINFO(DATA,
	  CLASSINFOENT(ru_RU,(
			      $overview{Интегрированный менеджер ресурсов}
			      $properties{
				$property{static PATHS path\\ассоциативная таблица путей к ресурсам}
				$property{static NAMES ext\\ассоциативная таблица расширений ресурсов}
			      }
			      $methods{
				$method{DRES*open(string name,int mode)\\открыть ресурс с именем name, методом mode}
				$method{DRES*open(string name,string type,int mode)\\открыть ресурс с именем name типа type, методом mode}
				$method{close(DRES*)\\закрыть ресурс}
			      }
			      )
		       )
	  )
