#pragma once
#ifdef _WIN32
#  include"unbase.hxx"
#  include<deque>
#  include<windows.h>

namespace unogl{
  class KEY{
  public:
    enum {// Клавиши
      tab=   VK_TAB,
      pause= VK_PAUSE,
      esc=   VK_ESCAPE,
      space= VK_SPACE,
      end=   VK_END,
      home=  VK_HOME,
      left=  VK_LEFT,
      right= VK_RIGHT,
      up=    VK_UP,
      down=  VK_DOWN,
      ins=   VK_INSERT,
      del=   VK_DELETE,

      shift= VK_SHIFT,
      lshift=VK_LSHIFT,
      rshift=VK_RSHIFT,

      ctrl=  VK_CONTROL,
      lctrl= VK_LCONTROL,
      rctrl= VK_RCONTROL,

      alt=  18,//,VK_ALT
      lalt= 18,//,VK_LALT
      ralt= 18,//,VK_RALT

      menu=  93,//VK_MENU,
      lmenu= VK_LMENU,
      rmenu= VK_RMENU,
      //win=   VK_WIN,
      lapp=  VK_LWIN,
      rapp=  VK_RWIN,
      apps=  VK_APPS,

      num0=  VK_NUMPAD0,
      num1=  VK_NUMPAD1,
      num2=  VK_NUMPAD2,
      num3=  VK_NUMPAD3,
      num4=  VK_NUMPAD4,
      num5=  VK_NUMPAD5,
      num6=  VK_NUMPAD6,
      num7=  VK_NUMPAD7,
      num8=  VK_NUMPAD8,
      num9=  VK_NUMPAD9,

      mult=  VK_MULTIPLY,
      add=   VK_ADD,
      sep=   VK_SEPARATOR,
      sub=   VK_SUBTRACT,
      dec=   VK_DECIMAL,
      div=   VK_DIVIDE,

      f1=    VK_F1,
      f2=    VK_F2,
      f3=    VK_F3,
      f4=    VK_F4,
      f5=    VK_F5,
      f6=    VK_F6,
      f7=    VK_F7,
      f8=    VK_F8,
      f9=    VK_F9,
      f10=   VK_F10,
      f11=   VK_F11,
      f12=   VK_F12,
      f13=   VK_F13,
      f14=   VK_F14,
      f15=   VK_F15,
      f16=   VK_F16,
      f17=   VK_F17,
      f18=   VK_F18,
      f19=   VK_F19,
      f20=   VK_F20,
      f21=   VK_F21,
      f22=   VK_F22,
      f23=   VK_F23,
      f24=   VK_F24,

      numlock= VK_NUMLOCK,
      scrlock= VK_SCROLL,
      capslock=VK_CAPITAL,
      pgdown=  VK_NEXT,
      pgup=    VK_PRIOR,
      enter=   VK_RETURN,
      bkspace= VK_BACK,
      tilda=   (unsigned char)0xC0,
      press=   0x4,
      release= 0x8,
   
      wheel_up=  (unsigned char)254,
      wheel_down=(unsigned char)255,
      mleft=     (unsigned char)253,
      mcenter=   (unsigned char)252,
      mright=    (unsigned char)251
    };
    union {
      unsigned int key;  // Номер активированной клавиши
      unsigned int code;
    };
    bool   state;// Нажата \ отпущена
    
    KEY():key(0),state(false){}
    KEY(unsigned int k,bool s):key(k),state(s){}
    ~KEY(){}
    
    operator string(){return string("KEY(key==")+string(/*key*/)+",state=="+string(/*state*/)+")";}
  };
}

#endif
