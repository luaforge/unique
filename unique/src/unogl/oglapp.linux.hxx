/************************************************Fenix***

Header file: glapp.linux.hpp

Interface with GNU\Linux(L)

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
#ifdef _LINUX
#  pragma once
#  include"graphcontext.hxx"

#  include<glx.h>
#  include<glext.h>
#  include<Xlib.h>
#  include<xf86vmode.h>

#  include<glxext.h>

namespace unogl{
# define GLEXT_FUNC(name,type,real) extern PFN##type##PROC name;
# include"oglext.platform.func.hxx"
# undef GLEXT_FUNC

  class GLAPP: public GRAPHCONTEXT{
  public:
    enum {// Стили окна
      dflt=0, // Пустой стиль
      none=1, // Просто окно
      bord=2, // Окно c рамкой
      head=4, // Окно с шапкой
      sbtn=8, // Окно с кнопками системного меню
      maxw=10,// Максимальное окно
    };
  protected:
    Display*             xdisplay;
    Window               xwindow;
    Window               xrootwin;
    XSetWindowAttributes xwinattr;
    unsigned long        xwinmask;
    // Fullscreen mask and attrib
    XSetWindowAttributes fxwinattr;
    unsigned long        fxwinmask;
    // Windowed mask and attrib
    XSetWindowAttributes wxwinattr;
    unsigned long        wxwinmask;
    // end
    XVisualInfo*         xvisualInfo;
    Colormap             xcolorMap;
    int                  xmodenum;
    int                  xmodesrc;
    XF86VidModeModeInfo**xmodes;
    //XF86VidModeModeLine *modeline;
    XKeyboardState       xkbstate;
    XKeyboardControl     xkbcontrol;
    Atom                 xdelwin;
    GLXContext           xcontext;
    int                  xscreen;
    XF86VidModeGamma     xgamma;

    XEvent xevent;   // X events
    Cursor xcursor;  // X cursor
    bool   xcursorstate; // Cursor
    vec2   xmouse;   // Window cursor coordinate
    KeySym xkey;     // Active key number
    bool   xkeystate;// Active key state (pressing/releasing)
    
    vec2 start;
    vec2 opos;
    bool ocursor,omode;
    unsigned int osync;
    unsigned int mwheel;
    vec3 ogamma;

    virtual void InitExtensionsLocal();
  public:
    vec3 gamma;
    vec2 pos;
    bool cursor,mode; // cursor visibility / window mode
    unsigned int sync;// vertical sync
    // Methods
    GLAPP();
    ~GLAPP();
    // Window
    bool open();
    void close();
    // Events processing
    bool run();
    // OpenGL
    void bind();
    void ubind();
    // Updates state
    void update();
  };
}
#endif
