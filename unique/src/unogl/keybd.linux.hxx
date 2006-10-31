#pragma once
#ifdef _LINUX
#  include"unbase.hxx"
#  include<deque>
#  include<keysym.h>

namespace unogl{
  class KEY{
  public:
    enum {
      /* mouse */
      wheel_up=  (unsigned char)254,
      wheel_down=(unsigned char)255,
      mleft=     (unsigned char)253,
      mcenter=   (unsigned char)252,
      mright=    (unsigned char)251,
      /* special keys */
      tab=   XK_Tab,
      pause= XK_Pause,
      esc=   XK_Escape,
      space= XK_Clear,
      kend=  XK_End,
      home=  XK_Home,
      left=  XK_Left,
      right= XK_Right,
      up=    XK_Up,
      down=  XK_Down,
      ins=   XK_Insert,
      del=   XK_Delete,
    
      shift= XK_Shift_L,
      lshift=XK_Shift_L,
      rshift=XK_Shift_R,
    
      ctrl=  XK_Control_L,
      lctrl= XK_Control_L,
      rctrl= XK_Control_R,
    
      alt=   XK_Alt_L,
      lalt=  XK_Alt_L,
      ralt=  XK_Alt_R,
    
      menu=  XK_Hyper_L,
      lmenu= XK_Hyper_L,
      rmenu= XK_Hyper_R,
    
      lapp=  XK_Super_L,
      rapp=  XK_Super_R,
      apps=  XK_Super_L,
    
      num0=  XK_KP_Insert,
      num1=  XK_KP_End,
      num2=  XK_KP_Down,
      num3=  XK_KP_Page_Down,
      num4=  XK_KP_Left,
      num5=  XK_KP_Begin,
      num6=  XK_KP_Right,
      num7=  XK_KP_Home,
      num8=  XK_KP_Up,
      num9=  XK_KP_Page_Up,
    
      mult=  0,//XK_MULTIPLY,
      add=   0,//XK_ADD,
      sep=   0,//XK_SEPARATOR,
      sub=   0,//XK_SUBTRACT,
      dec=   0,//XK_DECIMAL,
      div=   0,//XK_DIVIDE,
    
      f1=    XK_F1,
      f2=    XK_F2,
      f3=    XK_F3,
      f4=    XK_F4,
      f5=    XK_F5,
      f6=    XK_F6,
      f7=    XK_F7,
      f8=    XK_F8,
      f9=    XK_F9,
      f10=   XK_F10,
      f11=   XK_F11,
      f12=   XK_F12,
      f13=   XK_F13,
      f14=   XK_F14,
      f15=   XK_F15,
      f16=   XK_F16,
      f17=   XK_F17,
      f18=   XK_F18,
      f19=   XK_F19,
      f20=   XK_F20,
      f21=   XK_F21,
      f22=   XK_F22,
      f23=   XK_F23,
      f24=   XK_F24,
    
      numlock= XK_Num_Lock,
      scrlock= XK_Scroll_Lock,
      capslock=XK_Caps_Lock,
      pgdown=  XK_Page_Down,
      pgup=    XK_Page_Up,
      enter=   XK_Return,
      bkspace= XK_BackSpace,
      tilda=   XK_grave,
      grave=   XK_grave,
      press=   0x4,
      release= 0x8
    };
  
    union {
      unsigned int key; // key code
      unsigned int code;
    };
    bool state; // key state
  
    KEY():key(0),state(false){}
    KEY(unsigned int k,bool s):key(k),state(s){}
    ~KEY(){}
  
    operator string(){return string("KEY(key==")+key+",state=="+state+")";}
  };
}

#endif
