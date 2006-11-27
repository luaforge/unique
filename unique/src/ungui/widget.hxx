/********************************************Fenix***

Header file: widget.hpp

Copyleft (C) 2005 RareSky Zone

Comments:
    It is UI module for SolvEngine.

Bug report to:
    tonder@trktvs.ru

Author:
    Fenix R.S.

**********************************************************/

#pragma once
#include"unobj.hxx"
#include"text.hxx"

namespace ungui{//tolua_export
#define WIDGET_OFFSET 0.00001

  class GUISTYLE{//tolua_export
  public:
    unvis::MATGROUP mat;
  };//tolua_export
  
  class WIDGET: public unobj::OBJECT{//tolua_export
  protected:
    //  CLIP cliplane; // Clipping planes for widget
    vec2  osize,ocenter;
    GUISTYLE* ostyle;
  public:
    //tolua_begin
    GUISTYLE* style;
    unmath::vec2 size;  // widget size
    unmath::vec2 center;// widget align (in range [-1v,1v])
    // Methods
    WIDGET();
    virtual ~WIDGET();
    // Methods
    void draw(GLenum);
    void event(unogl::GRAPHCONTEXT&);
    bool update();
    //tolua_end
  };//tolua_export

  //class WINDOWSTYLE: public GUISTYLE{};
  class WINDOW: public unobj::GROUP{//tolua_export
  protected:
    GUISTYLE* ostyle;
  public:
    //tolua_begin
    GUISTYLE* style;
    unmath::vec2 size;  // widget size
    unmath::vec2 center;// widget align (in range [-1v,1v])
    bool dragable;
    WINDOW();
    virtual ~WINDOW();
    void draw(GLenum);
    void event(unogl::GRAPHCONTEXT&);
    bool update();
    //tolua_end
  };//tolua_export
  //class CURSORSTYLE: public GUISTYLE{};
  class CURSOR: public WIDGET{//tolua_export
  public:
    //tolua_begin
    //  CURSORSTYLE* style;
    CURSOR();
    ~CURSOR();
    void draw(GLenum);
    void event(unogl::GRAPHCONTEXT&);
    //tolua_end
  };//tolua_export
  /*
    class BUTTONSTYLE: public GUISTYLE{
    public:
    FONT font;
    };
  */
  class BUTTON: public WIDGET{//tolua_export
  public:
    //tolua_begin
    UNTEXT caption;
    //  BUTTONSTYLE* style;
    BUTTON();
    ~BUTTON();
    void draw(GLenum mode);
    //tolua_end
  };//tolua_export

  /*
    class TEXTSTYLE: public GUISTYLE{

    };
  */
  class TEXTLINE: public WIDGET{//tolua_export
  public:
    //tolua_begin
    bool editable;
    UNTEXT content;
    TEXTLINE();
    ~TEXTLINE();
    bool update();
    void draw(GLenum);
    void event(unogl::GRAPHCONTEXT&);
    //tolua_end
  };//tolua_export

  class TEXTAREA: public WIDGET{//tolua_export
  public:
    //tolua_begin
    bool editable;
    UNTEXT content;
    TEXTAREA();
    ~TEXTAREA();
    bool update();
    void draw(GLenum);
    void event(unogl::GRAPHCONTEXT&);
    //tolua_end
  };//tolua_export

  /*
   *     Каждый GUI объект можно:
   *  выделить (активизировать), снять выделение (деактивировать),
   *  взять (нажать) и отпустить, эти действия будут инициировать
   *  разные события. Это минимальная и полная группа событий,
   *  то есть больше ничего делать нельзя.
   *     При этом всегда возникают события перемещения курсора
   *  к(cursor move) которые можно использовать.
   */

  /*
    class ROOTWIN: public WIDGET{
    protected:
    bool enable;
    public:
    ROOTWIN();
    virtual ~ROOTWIN();

    void draw(GLenum mode);
    void step(scalar step);

    };
  */
}//tolua_export
