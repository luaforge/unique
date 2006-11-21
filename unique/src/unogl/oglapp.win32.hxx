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
#if _WIN32 || _MINGW
#  pragma once
#  include"graphcontext.hxx"

#  include<windows.h>
#  include<gl.h>
#  include<glu.h>
#  include<glext.h>

#  include<wglext.h>

namespace unogl{
# define GLEXT_FUNC(name,type,real) extern PFN##type##PROC name;
# include"oglext.platform.func.hxx"
# undef GLEXT_FUNC

  class GLAPP: public GRAPHCONTEXT{
  public:
    enum {
      // Стили окна
      dflt=0, // Пустой стиль
      none=1, // Просто окно
      bord=2, // Окно c рамкой
      head=4, // Окно с шапкой
      sbtn=8, // Окно с кнопками системного меню
      maxw=10 // Максимальное окно
    };
  protected:
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
    WORD      oGamma[3][256];
    int       PixelFormat;// Формат пикселов
    int       default_sync;
    
    int       xkey;     // Active key number
    bool      xkeystate;// Active key state (pressing/releasing)
    
    vec2 opos;
    bool ocursor,omode;
    unsigned int osync;
    unsigned int mwheel;
    vec3 ogamma;
    
    // wgl extensions init
    virtual void InitExtensionsLocal();
  public:
    static map<HWND,GLAPP*> __opened_apps_; // opened windows
    
    vec3 gamma;
    vec2 pos,start;
    bool cursor,mode; // cursor visibility / window mode 
    unsigned int sync;// vertical sync
    
    GLAPP();
    ~GLAPP();
    
    bool open();
    void close();
    
    bool run();
    
    // OpenGL
    void bind();
    void ubind();
    
    // Updates state
    void update();
    // window proc
    bool procMessage(HWND hWindow, UINT message, WPARAM wParam, LPARAM lParam);
    
  };
}

#endif
