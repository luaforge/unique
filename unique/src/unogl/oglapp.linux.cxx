/************************************************Fenix***

Source file: glapp.linux.cpp

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
	
	I life in Russia Trechgorny small town. I am
	programer. I am developing the SolvEngine.
	My favorite high level languages of programing
	is C++ and Lua.
	I also programme on Python, Java, PHP, Pascal.

**********************************************************/

#if _LINUX
#  include"oglapp.linux.hxx"

#  include<vector>

namespace unogl{
  using namespace unbase;

#  define PROUT(o) {cout<<#o<<" = "<<o<<endl;}

  GLAPP::GLAPP():GRAPHCONTEXT(),xdisplay(NULL),xcontext(NULL),xcursor(0),xwindow(0),
		 mode(false),omode(false),cursor(true),ocursor(true),
		 osync(1),sync(0),ogamma(),gamma(vec3::one){
    // Fullscreen window mask
    fxwinmask=\
      CWBackPixel        |
      CWColormap         |
      CWOverrideRedirect |
      CWSaveUnder        |
      CWBackingStore     |
      CWEventMask;
    // Windowed window mask
    wxwinmask=\
      CWBackPixel   |
      CWBorderPixel |
      CWColormap    |
      CWEventMask;
    // Fullscreen window attributes
    fxwinattr.background_pixel=0;
    fxwinattr.border_pixel=0;
    fxwinattr.event_mask=\
      ExposureMask           |
      VisibilityChangeMask   |
      KeyPressMask           |
      KeyReleaseMask         |
      ButtonPressMask        |
      ButtonReleaseMask      |
      PointerMotionMask      |
      StructureNotifyMask    |
      SubstructureNotifyMask |
      FocusChangeMask;
    fxwinattr.override_redirect=True;
    fxwinattr.backing_store=NotUseful;
    fxwinattr.save_under=False;
    // Windowed window attributes
    wxwinattr.background_pixel=0;
    wxwinattr.border_pixel=0;
    wxwinattr.event_mask=\
      ExposureMask           |
      VisibilityChangeMask   |
      KeyPressMask           |
      KeyReleaseMask         |
      ButtonPressMask        |
      ButtonReleaseMask      |
      PointerMotionMask      |
      StructureNotifyMask    |
      SubstructureNotifyMask |
      FocusChangeMask;
    state=STATE("context inited",true);
  }
  GLAPP::~GLAPP(){}

  bool GLAPP::open(){
    if(xdisplay||xwindow)return false;
  
    int st=GLAPP::none;
    int errorBase;
    int eventBase;
    xdisplay=XOpenDisplay(":0.0"); // Connect to default X server
    if(!xdisplay){state=STATE(false,"No connect to X server");return false;}
    // Make sure OpenGL's GLX extension supported
    if(!glXQueryExtension(xdisplay,&errorBase,&eventBase)){
      state=STATE(false,"X server has no OpenGL GLX extension");return false;}
    //
    xscreen=DefaultScreen(xdisplay);
    { // get all modes
      XF86VidModeGetAllModeLines(xdisplay,xscreen,&xmodenum,&xmodes);
      // find current source mode number (xmodesrc)
      int dotclock;
      XF86VidModeModeLine modeline;
      XF86VidModeGetModeLine(xdisplay,xscreen,&dotclock,&modeline);
      for(int i=0;i<xmodenum;i++){
	if(xmodes[i]->hdisplay   == modeline.hdisplay   && xmodes[i]->vdisplay   == modeline.vdisplay   &&
	   xmodes[i]->htotal     == modeline.htotal     && xmodes[i]->vtotal     == modeline.vtotal     &&
	   xmodes[i]->hsyncstart == modeline.hsyncstart && xmodes[i]->vsyncstart == modeline.vsyncstart &&
	   xmodes[i]->hsyncend   == modeline.hsyncend   && xmodes[i]->vsyncend   == modeline.vsyncend   &&
	   xmodes[i]->hskew      == modeline.hskew      && xmodes[i]->dotclock   == dotclock){
	  xmodesrc=i;
	  break;
	}
      }
    }
    xrootwin=RootWindow(xdisplay,xscreen);
    // Find an appropriate visual
    vector<int> va;
    //if(pixel.red>0&&pixel.green>0&&pixel.blue>0){
    //if(pixel.alpha>0)
    va.push_back(GLX_RGBA);
    //else va.push_back(GLX_RGB);
    //}
    if(buffering==2)va.push_back(GLX_DOUBLEBUFFER);
    va.push_back(GLX_RED_SIZE);
    va.push_back(pixel.red);
    va.push_back(GLX_GREEN_SIZE);
    va.push_back(pixel.green);
    va.push_back(GLX_BLUE_SIZE);
    va.push_back(pixel.blue);
    va.push_back(GLX_ALPHA_SIZE);
    va.push_back(pixel.alpha);
    va.push_back(GLX_DEPTH_SIZE);
    va.push_back(pixel.depth);
    va.push_back(GLX_STENCIL_SIZE);
    va.push_back(pixel.stencil);
    if(sampling>1){
      va.push_back(GLX_SAMPLE_BUFFERS_ARB);
      va.push_back(true);
      va.push_back(GLX_SAMPLES_ARB);
      va.push_back(sampling);
    }
    va.push_back(0);
    // Try with double buffer
    xvisualInfo=glXChooseVisual(xdisplay,xscreen,&va[0]);
    if(!xvisualInfo){state=STATE(false,"glXChooseVisual not possible choose xvisualInfo");return false;}
    // Create an X colormap since we're probably not using the default visual
    xcolorMap=XCreateColormap(xdisplay,xrootwin,
			      xvisualInfo->visual,AllocNone);
    if(!xcolorMap){state=STATE(false,"Error create colormap for context");return false;}
    fxwinattr.colormap=xcolorMap;
    wxwinattr.colormap=xcolorMap;
    // Create an X window with the selected visual
    xwinattr=wxwinattr; xwinmask=wxwinmask; // Windowed
    xwindow=XCreateWindow(xdisplay,
			  xrootwin,
			  int(pos.x),int(pos.y),     // x/y position of top-left outside corner of the window
			  int(size.x),int(size.y), // Width and height of window
			  0,        // Border width
			  xvisualInfo->depth,
			  InputOutput,
			  xvisualInfo->visual,
			  xwinmask,
			  &xwinattr);
    if(!xwindow){state=STATE(false,"Error create window");return false;}
    //XSetStandardProperties(xdisplay,xwindow,"GLX Unique","GLX Unique",None,None,None,NULL);
    XMapWindow(xdisplay,xwindow);
    // The OpenGL Rendering Context
    xcontext=glXCreateContext(xdisplay,xvisualInfo,
			      NULL,  // No sharing of display lists
			      True); // Direct rendering, if possible
    if(!xcontext){state=STATE(false,"Error create rendering context");return false;}
    glXMakeCurrent(xdisplay,xwindow,xcontext);

    XGetKeyboardControl(xdisplay,&xkbstate);
    XAutoRepeatOff(xdisplay);
  
    RendererInfo();
    InitExtensions();
  
    state=STATE("context opened",true);
  
    return true;
  }
  void GLAPP::close(){
    if(!xdisplay||!xwindow)return;
  
    XF86VidModeSwitchToMode(xdisplay,xscreen,xmodes[xmodesrc]);
    if(xkbstate.global_auto_repeat==AutoRepeatModeOn){
      XAutoRepeatOn(xdisplay);
    }
    if(xkbstate.global_auto_repeat==AutoRepeatModeOff){
      XAutoRepeatOff(xdisplay);
    }
    XAutoRepeatOn(xdisplay);// Потом надо убрать!
    if(xcontext)glXDestroyContext(xdisplay,xcontext);
    if(xwindow) XDestroyWindow(xdisplay,xwindow);
    if(xdisplay)XCloseDisplay(xdisplay);
    xdisplay=NULL;

    state=STATE("context closed",true);
  }

  void GLAPP::update(){ // Check Program Change Window Geometry
    if(!xdisplay||!xwindow)return;
    if(osampling!=sampling){
      if(sampling>1)glEnable(GL_MULTISAMPLE);
      else glEnable(GL_MULTISAMPLE);
      osampling=sampling;
    }
    if(ogamma!=gamma){
      ogamma=gamma;
      xgamma.red=gamma.R;
      xgamma.green=gamma.G;
      xgamma.blue=gamma.B;
      XF86VidModeGetGamma(xdisplay,xscreen,&xgamma);
    }
    if(omode!=mode){ // Video mode
      omode=mode;
      unsigned int xnumcurmode;
      if(mode){ // selection video mode
	map<int,int> xmodes_approx;
	for(int i=0;i<xmodenum;i++)xmodes_approx[abs(int(size.x)-xmodes[i]->hdisplay)+
						 abs(int(size.y)-xmodes[i]->vdisplay)]=i;
	xnumcurmode=xmodes_approx.begin()->second;
	xwinmask=fxwinmask; // Window mask
	xwinattr=fxwinattr; // Window attributes
      }else{
	xnumcurmode=xmodesrc;
	xwinmask=wxwinmask; // Window mask
	xwinattr=wxwinattr; // Window attributes
      }
      XUnmapWindow(xdisplay,xwindow);
      XF86VidModeSwitchToMode(xdisplay,xscreen,xmodes[xnumcurmode]);
      { size.x=scalar(xmodes[xnumcurmode]->hdisplay);
	size.y=scalar(xmodes[xnumcurmode]->vdisplay); }
      XChangeWindowAttributes(xdisplay,xwindow,xwinmask,&xwinattr);
      XClearWindow(xdisplay,xwindow);
      XMapWindow(xdisplay,xwindow);
      if(mode){
	XMoveWindow(xdisplay,xwindow,0,0);
	XRaiseWindow(xdisplay,xwindow);
	XWarpPointer(xdisplay,None,xwindow,0,0,0,0,
		     (int)size.x/2,(int)size.y/2);
	XGrabPointer(xdisplay,xwindow,True,0,GrabModeAsync,
		     GrabModeAsync,xwindow,None,CurrentTime);
	XGrabKeyboard(xdisplay,xwindow,True,GrabModeAsync,
		      GrabModeAsync,CurrentTime);
	XF86VidModeSetViewPort(xdisplay,xscreen,0,0);
      }else{
	XMoveWindow(xdisplay,xwindow,(int)pos.x,(int)pos.y);
	XLowerWindow(xdisplay,xwindow);
	XUngrabPointer(xdisplay,CurrentTime);
	XUngrabKeyboard(xdisplay,CurrentTime);
      }
      XClearWindow(xdisplay,xwindow);
    }
    if(osync!=sync){ // Vertical sync
      if(glXSwapInterval){
        glXSwapInterval(sync);
      }
      osync=sync;
    }
    if(pos!=opos){ // Window position
      XMoveWindow(xdisplay,xwindow,(int)pos.x,(int)pos.y);
      opos=pos;
    }
    if(size!=osize){ // Window density
      if(size.x>0 && size.y>0){
	XResizeWindow(xdisplay,xwindow,(unsigned int)size.x,(unsigned int)size.y);
	//start.x=size.x>size.y?0:(size.x-size.y);
	//start.y=size.y>size.x?0:(size.y-size.x);
	start=vec2::null;
	glViewport((int)start.x,(int)start.y,(int)(size.x-start.x),(int)(size.y-start.y));
      }
      osize=size;
    }
    // Check Program Change User Interface (mousing and etc)
    if(opointer!=pointer){ // Mouse move
      // Координаты курсора задаются как в OpenGL
      //
      //     В OpenGL:                   В OS:
      //                        _________________
      //         ^ 1           |             width
      //         |             |
      //         |   +         |
      //  _______|_______      |         +
      //  -1     |       1     |
      //         |             |
      //         | -1          | height
      //
      //  Поэтому следует преобразовать из 1-го во 2-й.
      //
      vec2 cpos=glfGL2W(pointer,size);
      XWarpPointer(xdisplay,None,xwindow,0,0,0,0,(int)cpos.x,(int)cpos.y);
      XFlush(xdisplay);
      pointervel=pointer-opointer;
      opointer=pointer;
    }
    if(cursor!=ocursor){ // Cursor visibility
      if(cursor){
	XDefineCursor(xdisplay,xwindow,0);
	//XFreeCursor(xdisplay,xcursor);
      }else{
	if(!xcursor){
	  char data[]={0};
	  Pixmap blank;
	  XColor dummy;
	  blank=XCreateBitmapFromData(xdisplay,xwindow,data,1,1);
	  xcursor=XCreatePixmapCursor(xdisplay,blank,blank,&dummy,&dummy,0,0);
	  XFreePixmap(xdisplay,blank);
	}
	XDefineCursor(xdisplay,xwindow,xcursor);
      }
      ocursor=cursor;
    }
  }

  bool GLAPP::run(){ // X message translation
    if(!(xdisplay&&xwindow))return false;
  
    pointervel=vec2::null;
    //while(key.array.size()>0)key.array.pop_front();
    key.clear(); // Erase all key events
    update(); // update states
    while(XPending(xdisplay)>0){ // Loop to compress events
      XNextEvent(xdisplay,&xevent);
      switch(xevent.type){
      case ButtonPress:{
	if(xevent.xbutton.button==1){ xkey=KEY::mleft;   xkeystate=true; }
	if(xevent.xbutton.button==2){ xkey=KEY::mcenter; xkeystate=true; }
	if(xevent.xbutton.button==3){ xkey=KEY::mright;  xkeystate=true; }
      }break;
      case ButtonRelease:{
	if(xevent.xbutton.button==1){ xkey=KEY::mleft;   xkeystate=false; }
	if(xevent.xbutton.button==2){ xkey=KEY::mcenter; xkeystate=false; }
	if(xevent.xbutton.button==3){ xkey=KEY::mright;  xkeystate=false; }
      }break;
      case KeyPress:{
	xkey=XLookupKeysym(&xevent.xkey,0);
	xkeystate=true;
      }break;
      case KeyRelease:{
	xkey=XLookupKeysym(&xevent.xkey,0);
	xkeystate=false;
      }break;
      case MotionNotify:{
	pointer.x=xevent.xmotion.x;
	pointer.y=xevent.xmotion.y;
	pointer=glfW2GL(pointer,size);
	pointervel=pointer-opointer;
	opointer=pointer;
      }break;
      case Expose:{
      }break;
      case ConfigureNotify:{
	size.width=xevent.xconfigure.width;
	size.height=xevent.xconfigure.height;
	osize=size;
	pos.x=xevent.xconfigure.x;
	pos.y=xevent.xconfigure.y;
	opos=pos;
      }
      }
      if(xkey!=0){
	key.array.push_back(KEY(xkey,xkeystate));
	xkey=0; xkeystate=false;
      }
    }
    //while(key.array.size()>MAX_KEYS_STATE)key.array.pop_front(); // Erase extra key events
    return true;
  }
  void GLAPP::bind(){
    if(!xdisplay||!xwindow)return;
    run();
    if(!glXMakeCurrent(xdisplay,xwindow,xcontext))state=STATE(false,"glXMakeCurrent filed!");
  }
  void GLAPP::ubind(){
    if(!xdisplay||!xwindow)return;
    if(buffering>1)glXSwapBuffers(xdisplay,xwindow);else glFlush();
    //glXMakeCurrent(xdisplay,xwindow,NULL);
  }

# define GLEXT_FUNC(name,type,real) PFN##type##PROC name;
# include"oglext.platform.func.hxx"
# undef GLEXT_FUNC
  
# define GLEXT_FUNC(name,type,real) name=(PFN##type##PROC)glGetProcAddress(#real);
  void GLAPP::InitExtensionsLocal(){
    cout<<"Init glX extensions...."<<endl;
    # include"oglext.platform.func.hxx"
  }
# undef GLEXT_FUNC
  
}

#endif
