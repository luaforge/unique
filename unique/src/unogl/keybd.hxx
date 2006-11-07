#include "keybd.linux.hxx"
#include "keybd.win32.hxx"

//tolua_begin
/**
namespace unogl{
class KEY{
  enum {
    wheel_up,
    wheel_down,
    mleft,
    mcenter,
    mright,

    tab,
    pause,
    esc,
    space,
    kend,
    home,

    left,
    right,
    up,
    down,

    ins,
    del,
    shift,
    lshift,
    rshift,
	
    ctrl,
    lctrl,
    rctrl,
	
    alt,
    lalt,
    ralt,
	
    menu,
    lmenu,
    rmenu,
	
    lapp,
    rapp,
    apps,
	
    num0,
    num1,
    num2,
    num3,
    num4,
    num5,
    num6,
    num7,
    num8,
    num9,
	
    mult,
    add,
    sep,
    sub,
    dec,
    div,
	
    f1,
    f2,
    f3,
    f4,
    f5,
    f6,
    f7,
    f8,
    f9,
    f10,
    f11,
    f12,
    f13,
    f14,
    f15,
    f16,
    f17,
    f18,
    f19,
    f20,
    f21,
    f22,
    f23,
    f24,
	
    numlock,
    scrlock,
    capslock,
    pgdown,
    pgup,
    enter,
    bkspace,
    tilda,
    grave,
    press,
    release
  };

  KEY();
  KEY(unsigned int k, bool s);
  ~KEY();
  
  unsigned int key;
  unsigned int code;
  bool state;

  operator string();
};
}
**/
//tolua_end
