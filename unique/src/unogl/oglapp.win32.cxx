/************************************************Fenix***

Source file: glapp.win32.cpp

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
    
    I live in Trechgorny small town in Russia. I am 
    programmer. I am developing the SolvEngine. 
    My favorite high level languages of programming
    is C++ and Lua.
    I also programmer on Python, Java, PHP, Pascal.

**********************************************************/

#if _WIN32 || _MINGW
#  include"oglapp.win32.hxx"

namespace unogl{
  using namespace unbase;
  
  map<HWND,GLAPP*> GLAPP::__opened_apps_; // opened windows
  
  static LRESULT CALLBACK MainWindowProc(HWND hWindow,UINT message,WPARAM wParam,LPARAM lParam){
    map<HWND,GLAPP*>::iterator n;
    if((n=GLAPP::__opened_apps_.find(hWindow))!=GLAPP::__opened_apps_.end())
      if(n->second)if(n->second->procMessage(hWindow,message,wParam,lParam))return 1;
    return DefWindowProc(hWindow,message,wParam,lParam);
  }

  GLAPP::GLAPP():GRAPHCONTEXT(),hDC(NULL),hRC(NULL),hWnd(NULL),hInst(GetModuleHandle(NULL)),
		 mode(false),omode(false),cursor(true),ocursor(true),
		 osync(1),sync(0),ogamma(),gamma(vec3::one){
    {
      WORD** g=(WORD**)oGamma;
      HDC hdc = GetDC(GetDesktopWindow());
      GetDeviceGammaRamp(hdc,g);
      ReleaseDC(GetDesktopWindow(),hdc);
      
      //gamma.r=float(g[0])/256.0f;
      //gamma.g=float(g[1])/256.0f;
      //gamma.b=float(g[2])/256.0f;
    }
  }
  GLAPP::~GLAPP(){close();}
  
  void GLAPP::update(){
    if(!hWnd||!hDC||!hRC)return;
    if(osampling!=sampling){
      if(sampling>1)glEnable(GL_MULTISAMPLE);
      else glEnable(GL_MULTISAMPLE);
      osampling=sampling;
    }
    if(ogamma!=gamma){
      {
	//HDC hdc = GetDC(GetDesktopWindow());
	WORD g[3][256];
	if(GetDeviceGammaRamp(hDC,g)){
	  for(int i=0;i<256;i++){
	    g[0][i]=255*(WORD)(255.0f*pow(scalar(i)/255.0f,1.0f/gamma.R));
	    g[1][i]=255*(WORD)(255.0f*pow(scalar(i)/255.0f,1.0f/gamma.G));
	    g[2][i]=255*(WORD)(255.0f*pow(scalar(i)/255.0f,1.0f/gamma.B));
	  }
	  if(!SetDeviceGammaRamp(hDC,g))state=STATE("Set gamma filed!",false);
	}
	//ReleaseDC(GetDesktopWindow(),hDC);
      }
      ogamma=gamma;
    }
    if(omode!=mode){ // Video mode
      if(mode){
	DEVMODE dmScreenSettings;
	
	memset(&dmScreenSettings,0,sizeof(DEVMODE));
	dmScreenSettings.dmSize      =sizeof(DEVMODE);
	dmScreenSettings.dmPelsWidth =int(size.x);
	dmScreenSettings.dmPelsHeight=int(size.y);
	dmScreenSettings.dmFields    =DM_PELSWIDTH|DM_PELSHEIGHT;
	ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN);
      }else{
	ChangeDisplaySettings(NULL,0);
      }
      omode=mode;
    }
    if(osync!=sync){ // Vertical sync
      if(wglSwapInterval){
	//if(sync)wglSwapInterval(default_sync);else wglSwapInterval(0);
	wglSwapInterval(sync);
      }
      osync=sync;
    }
    if(pos!=opos){ // Window position
      SetWindowPos(hWnd,HWND_TOP,int(pos.x),int(pos.y),0,0,SWP_NOSIZE);
      opos=pos;
    }
    if(size!=osize){ // Window density
      if(size.x>0 && size.y>0){
	SetWindowPos(hWnd,HWND_TOP,0,0,int(size.x),int(size.y),SWP_NOMOVE);
	start=vec2::null;
	glViewport(int(start.x),int(start.y),int(size.x-start.x),int(size.y-start.y));
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
      SetCursorPos(int(cpos.x),int(cpos.y));
      pointervel=pointer-opointer;
      opointer=pointer;
    }
    if(cursor!=ocursor){ // Cursor visibility
      ShowCursor(cursor);
      ocursor=cursor;
    }
  }

#define STYLE_CHECK(style,dws,type,name) {	\
    if(style>=type){				\
      dws |= name;				\
      style-=type;				\
    }						\
  }

  bool GLAPP::open(){
    if(hWnd||hDC||hRC)return false;
    
    WinClass.style         = CS_HREDRAW|CS_VREDRAW|CS_OWNDC;
    WinClass.lpfnWndProc   = (WNDPROC)(unogl::MainWindowProc);
    WinClass.cbClsExtra    = 0;
    WinClass.cbWndExtra    = 0;
    WinClass.hInstance     = hInst;
    WinClass.hIcon         = NULL;
    WinClass.hCursor	   = LoadCursor(NULL,IDC_ARROW);
    WinClass.hbrBackground = NULL;
    WinClass.lpszMenuName  = NULL;
    WinClass.lpszClassName = "lUniquE-Win32";
    if(!RegisterClass(&WinClass)){// Register win32 application class
      state=STATE("Register WIN application class",false);
      return false;
    }
    
    dwstyle=0;
    dwstyle|=WS_POPUP;
    dwstyle|=WS_CAPTION|WS_BORDER|WS_SYSMENU;
    //STYLE_CHECK(newstyle,dwstyle,sbtn,WS_SYSMENU);
    //STYLE_CHECK(newstyle,dwstyle,head,WS_CAPTION);
    //STYLE_CHECK(newstyle,dwstyle,bord,WS_BORDER);
    //STYLE_CHECK(newstyle,dwstyle,none,WS_POPUP);
    
    if(!(hWnd=CreateWindow(// Create window
			   WinClass.lpszClassName,// window name
			   WinClass.lpszClassName,// window class
			   dwstyle,// window style
			   //int(pos.x-0.5*size.x),int(pos.y-0.5*size.y),// window position
			   int(pos.x),int(pos.y),
			   int(size.x),int(size.y),// window size
			   NULL,NULL,hInst,NULL))){
      state=STATE("Create window",false);
      return false;
    }
    SetWindowText(hWnd,WinClass.lpszClassName);

    ShowWindow(hWnd,SW_SHOW);
    UpdateWindow(hWnd);
    SetFocus(hWnd);
    
    hDC=GetDC(hWnd);
    
    // OpenGL
    // Init glx extensions
    InitExtensionsLocal();
    if(wglGetExtensionsString)localextensions=wglGetExtensionsString(hDC);
    if(wglGetSwapInterval)default_sync=wglGetSwapInterval();else default_sync=0;
    
    // pixel format
    pfd.nSize=sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion=1;
    pfd.dwFlags=PFD_DRAW_TO_WINDOW|PFD_SUPPORT_OPENGL;
    if(buffering==2)pfd.dwFlags|=PFD_DOUBLEBUFFER;
    pfd.iPixelType=PFD_TYPE_RGBA;
    pfd.cColorBits=pixel.red+pixel.green+pixel.blue+pixel.alpha;
    pfd.cRedBits=pixel.red;
    pfd.cRedShift=0;
    pfd.cGreenBits=pixel.green;
    pfd.cGreenShift=0;
    pfd.cBlueBits=pixel.blue;
    pfd.cBlueShift=0;
    pfd.cAlphaBits=pixel.alpha;
    pfd.cAlphaShift=0;
    pfd.cAccumBits=pfd.cColorBits;
    pfd.cAccumRedBits=pfd.cRedBits;
    pfd.cAccumGreenBits=pfd.cGreenBits;
    pfd.cAccumBlueBits=pfd.cBlueBits;
    pfd.cAccumAlphaBits=pfd.cAlphaBits;
    pfd.cDepthBits=pixel.depth;
    pfd.cStencilBits=pixel.stencil;
    pfd.cAuxBuffers=0;
    pfd.iLayerType=PFD_MAIN_PLANE;
    pfd.bReserved=0;
    pfd.dwLayerMask=0;
    pfd.dwVisibleMask=0;
    pfd.dwDamageMask=0;
    
    vector<int> va;
    va.push_back(WGL_DRAW_TO_WINDOW_ARB);
    va.push_back(true);
    va.push_back(WGL_SUPPORT_OPENGL_ARB);
    va.push_back(true);
    va.push_back(WGL_ACCELERATION_ARB);
    va.push_back(WGL_FULL_ACCELERATION_ARB);
    if(buffering>1){
      va.push_back(WGL_DOUBLE_BUFFER_ARB);
      va.push_back(true);
    }else{
      va.push_back(WGL_DOUBLE_BUFFER_ARB);
      va.push_back(false);
    }
    va.push_back(WGL_RED_BITS_ARB);
    va.push_back(pixel.red);
    va.push_back(WGL_GREEN_BITS_ARB);
    va.push_back(pixel.green);
    va.push_back(WGL_BLUE_BITS_ARB);
    va.push_back(pixel.blue);
    va.push_back(WGL_ALPHA_BITS_ARB);
    va.push_back(pixel.alpha);
    va.push_back(WGL_DEPTH_BITS_ARB);
    va.push_back(pixel.depth);
    va.push_back(WGL_STENCIL_BITS_ARB);
    va.push_back(pixel.stencil);
    if(sampling>1){
      va.push_back(WGL_SAMPLE_BUFFERS_ARB);
      va.push_back(true);
      va.push_back(WGL_SAMPLES_ARB);
      va.push_back(sampling);
    }
    va.push_back(0);
    
    if(wglChoosePixelFormat){
      unsigned int retcode=0;
      wglChoosePixelFormat(hDC,&va[0],NULL,1,&PixelFormat,&retcode);
      if(!retcode){
	state=STATE("Choose pixel format",false);
	return false;
      }
    }else{
      if(!(PixelFormat=ChoosePixelFormat(hDC,&pfd))){
	state=STATE("Choose pixel format",false);
	return false;
      }
    }
    if(!(SetPixelFormat(hDC,PixelFormat,&pfd))){
      state=STATE("Set pixel format",false);
      return false;
    }

    if(!(hRC=wglCreateContext(hDC))){
      state=STATE("Wgl create context",false);
      return false;
    }
    if(!wglMakeCurrent(hDC,hRC)) {
      state=STATE("Wgl make current",false);
      return false;
    }
    
    RendererInfo();
    InitExtensions();
    
    state=STATE("context opened",true);
  
    __opened_apps_[hWnd]=this;
    
    return true;
  }
  
  void GLAPP::close(){
    if(!hWnd||!hDC||!hRC)return;
  
    if(mode){
      ChangeDisplaySettings(NULL,0);
      omode=mode;
    }
    wglMakeCurrent(hDC,NULL);
    wglDeleteContext(hRC);
    ReleaseDC(hWnd,hDC);
    DestroyWindow(hWnd);

    hWnd=NULL; hDC=NULL; hRC=NULL;
  
    __opened_apps_.erase(hWnd);

    state=STATE("Context closed",true);
  }

  bool GLAPP::procMessage(HWND hWindow, UINT message, WPARAM wParam, LPARAM lParam){
    switch(message){
    case WM_CREATE:
      break;
    case WM_CLOSE:
    case WM_DESTROY:
    case WM_QUIT:
      break;
    case WM_LBUTTONDOWN: xkey=KEY::mleft;   xkeystate=true;  break;
    case WM_LBUTTONUP:   xkey=KEY::mleft;   xkeystate=false; break;
    case WM_MBUTTONDOWN: xkey=KEY::mcenter; xkeystate=true;  break;
    case WM_MBUTTONUP:   xkey=KEY::mcenter; xkeystate=false; break;
    case WM_RBUTTONDOWN: xkey=KEY::mright;  xkeystate=true;  break;
    case WM_RBUTTONUP:   xkey=KEY::mright;  xkeystate=false; break;
    case 0x020A:
      if(wParam==0x00780000)xkey=KEY::wheel_up;
      if(wParam==0xFF880000)xkey=KEY::wheel_down;
      break;
    case WM_KEYDOWN:
      xkey=wParam; xkeystate=true;  break;
    case WM_KEYUP:
      xkey=wParam; xkeystate=false; break;
    case WM_SYSKEYDOWN:
      xkey=wParam; xkeystate=true;  break;
    case WM_SYSKEYUP:
      xkey=wParam; xkeystate=false; break;
    case WM_MOUSEMOVE:
      {
	tagPOINT cpos;
	GetCursorPos(&cpos);
	pointer.x=cpos.x;
	pointer.y=cpos.y;
      }
      pointer=glfW2GL(pointer,size);
      pointervel=pointer-opointer;
      opointer=pointer;
      break;
    case WM_MOVE:
    case WM_SIZE:
      tagRECT wr;
      GetWindowRect(hWnd,&wr);
      size.width=wr.right-wr.left;
      size.height=wr.bottom-wr.top;
      osize=size;
      pos.x=wr.left;
      pos.y=wr.top;
      opos=pos;
      break;
    default:
      return false;
      break;
    }
    if(xkey!=0){
      key.array.push_back(KEY(xkey,xkeystate));
      xkey=0; xkeystate=false;
    }
    //cout<<":::procMessage::: "<<endl;
    return true;
  }
  bool GLAPP::run(){
    if(!hWnd||!hDC||!hRC)return false;
    
    pointervel=vec2::null;
    key.clear(); // Erase all key events
    update(); // update states
    for(;PeekMessage(&mes,NULL,0,0,PM_NOREMOVE);){
      if(!GetMessage(&mes,NULL,0,0))break;
      TranslateMessage(&mes);
      DispatchMessage(&mes);
    }
    return true;
  }
  
  void GLAPP::bind(){
    if(!hWnd||!hDC||!hRC)return;
    //cout<<":::bind::: "<<endl;
    run();
    if(!wglMakeCurrent(hDC,hRC))state=STATE(false,"glXMakeCurrent filed!");
  }
  void GLAPP::ubind(){
    if(!hWnd||!hDC||!hRC)return;
    //cout<<":::ubind::: "<<endl;
    if(buffering>1)SwapBuffers(hDC);else glFlush();
    //glClearColor(0.5,0.5,0.5,1.0);
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  }

# define GLEXT_FUNC(name,type,real) PFN##type##PROC name;
# include"oglext.platform.func.hxx"
# undef GLEXT_FUNC
  
# define GLEXT_FUNC(name,type,real) name=(PFN##type##PROC)glGetProcAddress(#real);
  void GLAPP::InitExtensionsLocal(){
    cout<<"Init Wgl extensions...."<<endl;
    # include"oglext.platform.func.hxx"
  }
# undef GLEXT_FUNC
  
}

#endif
