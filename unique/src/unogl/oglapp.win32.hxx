/************************************************Fenix***

Header file: glapp.win32.hpp

Interface with Windows(R)

Copyleft (C) 2005 RareSky Zone

Comments:
    This module for SolvEngine. This module contains
	the object of the interface with operating system.
    SolvEngine this FREE and Open Source graphic 3D 
	engine. This powered by OpenGL(R) and Lua.

Bug report to:
    tonder@trktvs.ru

Author:
    Fenix R.S.

**********************************************************/

#ifdef _WIN32
# ifndef _WINAPP_H
#  define _WINAPP_H

#  include<windows.h>
#  include<gl/gl.h>// Опен ГЛ заголовочный файл
#  include<gl/glu.h>// Дополнение ГЛ заголовочный файл
#  include<gl/glext.h>// Опен ГЛ расширения

// Включаемые файлы

#  include "oglext.hpp"

class GLAPP: public GRAPHCONTEXT{
 public:
  enum{
    // Стили окна
    dflt=0, // Пустой стиль
    none=1,    // Просто окно
    bord=2,  // Окно c рамкой
    head=4,    // Окно с шапкой
    sbtn=8,  // Окно с кнопками системного меню
    maxw=10,     // Максимальное окно
  };
 protected:
  bool regeom;       // Пересчитать геометрию окна
  bool reui;         // пересчитать интерфейс
  bool wcrted;
  // Идентификаторы форточек
  HINSTANCE hInst;   // Ид задачи
  HWND      hWnd;    // Контекст окна
  WNDCLASS  WinClass;// Класс окна
  DWORD     dwstyle; // Стили окна
  MSG       mes;     // Сообщения виндовс
  // Идентификаторы устройства вывода
  RECT      Rect;    // Область вывода
  HGLRC     hRC;     // Контекст рендеринга
  HDC       hDC;     // Контекст устройства вывода
  PIXELFORMATDESCRIPTOR pfd;// Дескриптор Формата пикселов
  GLuint    PixelFormat;// Формат пикселов
  //OGLEXT    oglext;  // Контекст расширений OpenGL
 public:
  // Переменные проложеня

  deque<KEY>* xkeys;

  vec2         opos,          // Предыдущая позиция
	           wpos,          // Позиция окна
			   osize,         // предшествующий размер
               wsize,         // Размер окна || разрешение
			   omouse,
	           wmouse;        // Координаты курсора в пределах окна
  bool         wmode;         // Способ вывода (false - в окно || true - во весь экран)
  unsigned int wkey,          // Код активированной клавиши
               mwheel;
  bool         wkeystate,     // Состояние активации (нажата ли)
               vsync_state, // Вертикальная синхронизация вкл\выкл
               cursorvis;   // Видим ли курсор

  const char* vendor;
  const char* renderer;
  const char* version;
  const char* extensions;
  // Методы класса
  GLAPP();
  ~GLAPP();
  // Мышь
  bool key(unsigned int& k);// Клавиша k 
  KEY& keys();
  void  cursor(bool cur);  // Установка видимости курсора
  bool  cursor();    // Проверка видимости курсора
  void  mouse(vec2& cpos); // Установка положения курсора в пределах окна
  vec2& mouse();     // Взятие положения курсора в пределах окна
  // Окно
  void Style(GLuint newstyle); // Установка стиля окна
  void Title(const char *nwname); // Установка заголовка окна  
  // Окно
  void  pos(vec2& p);
  vec2& pos();
  void  size(vec2& s);
  vec2& size();
  void mode(bool m);
  bool mode();
  void sync(bool state); // Включение \ отключение вертикальной синхронизации
  bool sync();
  //bool open(vec2 size=vec2(640,480),int bpp=16,GLuint style=APP::st_none);
  bool open(vec2 size, int bpp, GLuint style);
  bool open(vec2 size, int bpp){ return open(size,bpp,APP::head+APP::bord+APP::sbtn); }
  bool open(vec2 size){ return open(size,16,APP::none); }
  bool open(){ return open(vec2(640,480),16,APP::none); }
  void close();
  // Процессинг сообщений
  bool procMessage(HWND hWindow, UINT message, WPARAM wParam, LPARAM lParam);
  bool run();    // Транслация событий (требуется выполнять циклически,
                 // чтобы не потерять связь процесса с операционной системой)
  // OpenGL
  void bind();     // Делает контекст буффера рендеринга текущим
  void ubind();    // Своп буфера (чтобы картинка вывелась на экран) и отключение контекста
  // Была идейка сделать следующее в качестве оконной функции
  //LRESULT CALLBACK operator ()(HWND hWindow,UINT message,WPARAM wParam,LPARAM lParam);
  void ReGeom();
  void ReUser();
};

static const vec2 default_size(640,480);

# endif
#endif
