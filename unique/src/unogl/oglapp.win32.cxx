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

#ifdef _WIN32

#include"glapp.win32.hpp" // ��������� ������������ �����

using namespace unogl;

//#include <map>
//typedef map<HWND, OSAPP*, less<HWND> > WINAPPS;
//WINAPPS wapps;
APP* appw;

typedef BOOL (APIENTRY * wglSwapIntervalEXT_Func)(int);
wglSwapIntervalEXT_Func wglSwapIntervalEXT=wglSwapIntervalEXT_Func(wglGetProcAddress("wglSwapIntervalEXT"));
// �� ����� ������� ���������� ���������� ������������ �������������

// ����������

void *OGLEXT::GetProcAddress(const char *func_name){
// ��� ������������ ���������� ������� ���������� OpenGL �� �� �����
  void *func_pointer=NULL;
  func_pointer=wglGetProcAddress(func_name);
  //if(func_pointer==NULL)Luna<OSAPP>::msg("$err_notsupported_ext",func_name);
  return func_pointer;
}

LRESULT CALLBACK MainWindowProc(HWND hWindow,UINT message,WPARAM wParam,LPARAM lParam){
  // �������� ��������� Windows, ����������� ������� �������, ������� ������ 
  // ��������-���������������� ���������������� ;)
  appw->procMessage(hWindow,message,wParam,lParam);
  //OSAPP* wa=wapps[hWindow];
  //wa->  
  return (DefWindowProc(hWindow, message, wParam, lParam));
}

APP::APP(){ // �����������
  //memset(this,0,sizeof(OSAPP));
  hWnd=NULL;
  hInst=GetModuleHandle(NULL);
}
APP::~APP(){close();}

void APP::sync(bool state){// ������������ �������������
  if(wglSwapIntervalEXT){
    vsync_state=state;
    wglSwapIntervalEXT((int)state);
  }
}
bool APP::sync(){
  return vsync_state;
}
void APP::mode(bool m){// ���������� true - �������������, false - � ����
  wmode=m;
  if(m){
    DEVMODE dmScreenSettings;	// �������������� ������������
    // ������������� ����������
    memset(&dmScreenSettings,0,sizeof(DEVMODE));
    dmScreenSettings.dmSize      =sizeof(DEVMODE);
    dmScreenSettings.dmPelsWidth =wsize.x;
    dmScreenSettings.dmPelsHeight=wsize.y;
    dmScreenSettings.dmFields    =DM_PELSWIDTH | DM_PELSHEIGHT;
    ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);
  }else{
    ChangeDisplaySettings(NULL,0);// ������� � ���������� ����������
  }
  //Luna<OSAPP>::msg("$OK");
}
bool APP::mode(){
  return wmode;
}
void APP::size(vec2& s){// ��������� ���������� \ ������� ����
  if(s.x>0 && s.y>0){
    if(hWnd)SetWindowPos(hWnd,HWND_TOP,0,0,(GLuint)s.x,(GLuint)s.y,SWP_NOMOVE);
  }else{
  }
  glViewport(0,0,s.x,s.y);// ���� ������
}
vec2& APP::size(){
  osize=wsize; // ���� ��������� �����, ��� �� ������� ������ ����������
  return (vec2&)wsize;
}
void APP::pos(vec2& p){
  if(p.x<0 || p.y<0){
  }else{
    if(hWnd)SetWindowPos(hWnd,HWND_TOP,p.x,p.y,0,0,SWP_NOSIZE);
  }
}
vec2& APP::pos(){
  opos=wpos; // ���� ��������� �����, ���� �� ������ ������� ����������
  return (vec2&)wpos;
}
void APP::ReGeom(){ // Check Program Change Window Geometry
  if(wpos!=opos){ pos(wpos); opos=wpos; }
  if(wsize!=osize){ size(wsize); osize=wsize; } // ���������, ��� �� ������� ������ ����������
}
void APP::ReUser(){ // Check Program Change User Interface (mousing and etc)
  if(omouse!=wmouse){ mouse(wmouse); wmouse=omouse; }
}
//����
void APP::cursor(bool cur){// ��������� �������
  cursorvis=cur;
  ShowCursor(cur);// �������� ������
}
bool APP::cursor(){// ��������� �������
  return cursorvis;
}
void APP::mouse(vec2& cpos){// ��������� ��������� ������� � �������� ����
// ���������� ������� �������� ��� � OpenGL
//
//     � OpenGL:                   � OS:
//                        _________________
//         ^ 1           |             width
//         |             |
//         |   +         |          
//  _______|_______      |         +
//  -1     |       1     |
//         |             |
//         | -1          | height
//
//  ������� ������� ������������� �� 1-�� �� 2-�.
//
//SetCursorPos((1.0+cpos.x)*wwidth/2+wxpos,(1.0-cpos.y)*wheight/2+wypos);

//  ����� � ��������� �� ���� ����, ������ ��� ������������ �� ���
  SetCursorPos(cpos.x+wpos.x,cpos.y+wpos.y);
}
vec2& APP::mouse(){// ������ ��������� ������� � �������� ����
//
//  ����� ������� ���������� �������� ��������������.
//
//cpos.x=2.0f*(mXpos-wxpos)/wwidth-1.0;
//cpos.y=-2.0f*(mYpos-wypos)/wheight+1.0;

//  ����� � ��������� �� ���� ����, ������ ��� ������������ �� ���
  omouse=wmouse; // ���� ���������, ����������� �� ���� ����������
  return (vec2&)wmouse;
}
/*void OSAPP::WinRect(){
  tagRECT wpos;
  GetWindowRect(hWnd,&wpos);// ��� ������ ����
  wxpos=wpos.left;
  wypos=wpos.top;
  wwidth=wpos.right;
  wheight=wpos.bottom;
}*/
void APP::Title(const char *nwname){
  SetWindowText(hWnd,nwname);
}
#define STYLE_CHECK(style,dws,type,name){ if(style>=type){ dws |= name; style-=type; cout<<"Style:"<<#type<<"\n"; } }
void APP::Style(GLuint newstyle){
  dwstyle=0;
  //int newhstyle=newstyle-st_default;
  //if(!newstyle)dwstyle |=WS_POPUP;
  //if(newhstyle&(char)pow(2,st_none-st_default-1)){dwstyle |=WS_POPUP; /*loger<<msg[st_none];*/ }
  //if(newhstyle&(char)pow(2,st_border-st_default-1)){dwstyle |=WS_BORDER; /*loger<<msg[st_border];*/ }
  //if(newhstyle&(char)pow(2,st_head-st_default-1)){dwstyle |=WS_CAPTION; /*loger<<msg[st_head];*/ }
  //if(newhstyle&(char)pow(2,st_system-st_default-1)){dwstyle |=WS_SYSMENU; /*loger<<msg[st_system];*/ }
  //if(newhstyle&(char)pow(2,st_max-st_default-1)){dwstyle |=WS_MAXIMIZE; /*loger<<msg[st_max];*/ }
  //loger<<msg[A_OK]<<NS;
  
  dwstyle|=WS_POPUP;
  STYLE_CHECK(newstyle,dwstyle,sbtn,WS_SYSMENU);
  STYLE_CHECK(newstyle,dwstyle,head,WS_CAPTION);
  STYLE_CHECK(newstyle,dwstyle,bord,WS_BORDER);
  STYLE_CHECK(newstyle,dwstyle,none,WS_POPUP);
}
bool APP::open(vec2 size,int bpp,GLuint style){
  // ��������� ��������� ������ ����
  WinClass.style		 =CS_HREDRAW|CS_VREDRAW|CS_OWNDC;
  WinClass.lpfnWndProc	 =(WNDPROC)MainWindowProc;
  WinClass.cbClsExtra	 =0;
  WinClass.cbWndExtra	 =0;
  WinClass.hInstance	 =hInst;
  WinClass.hIcon		 =NULL;
  WinClass.hCursor		 =LoadCursor(NULL, IDC_ARROW);
  WinClass.hbrBackground =NULL;
  WinClass.lpszMenuName  =NULL;
  WinClass.lpszClassName ="SolvEngine - Win32";
  if(!RegisterClass(&WinClass)){// ������������ ����� ����
    //"������ �������� ������ ����","��������� ������!!!"
    return false;
  }
  appw=this;
  Style(style);
  //std::cout<<size.x<<","<<size.y<<":"<<bpp;
  if(!(hWnd=CreateWindow(// ������� ����
			 WinClass.lpszClassName, // ����� ����
			 WinClass.lpszClassName, // ��� ����	
			 dwstyle,// ����� ����
			 0,0,// ������� ����� ����
			 size.x,size.y,// ������
			 NULL,NULL,hInst,NULL))){// ��������� ������ �������� ����
    //"������ �������� ����!"    
    return false;
  }

  ShowWindow(hWnd,SW_SHOW); // ���������� ����
  UpdateWindow(hWnd);       // ���������
  SetFocus(hWnd);           // ������������� �����

  //Luna<OSAPP>::msg("$OK");
  // ������������� OpenGL
  //Luna<OSAPP>::msg("$gl_init");
  // ��������� ������� ��������
  pfd.nSize=sizeof(PIXELFORMATDESCRIPTOR);// ������
  pfd.nVersion=1;							// ������
  pfd.dwFlags=PFD_DRAW_TO_WINDOW|PFD_SUPPORT_OPENGL|PFD_DOUBLEBUFFER;
  // ������ ������ �������������� Window // ������ ������ �������������� OpenGL
  // ������ ������������ ������� �����
  pfd.iPixelType=PFD_TYPE_RGBA;			    // ��������� RGBA ������
  pfd.cColorBits=32;					    // ������� �����
  pfd.cRedBits=16;
  pfd.cRedShift=16;
  pfd.cGreenBits=16;
  pfd.cGreenShift=16;
  pfd.cBlueBits=16;
  pfd.cBlueShift=16;						// ������������ ���� �����
  pfd.cAlphaBits=16;						// ��� ����� ������
  pfd.cAlphaShift=16;						// ��� ������������� ������ 
  pfd.cAccumBits=16;						// ��� ������ ����������
  pfd.cAccumRedBits=16;
  pfd.cAccumGreenBits=16;
  pfd.cAccumBlueBits=16;
  pfd.cAccumAlphaBits=16;					// ������������ ���� ������ ����������
  pfd.cDepthBits=32;						// ������� z-������
  pfd.cStencilBits=32;						// ��� ������� ������
  pfd.cAuxBuffers=32;						// ��� ���������������� ������
  pfd.iLayerType=PFD_MAIN_PLANE;			// ������� ���� ������
  pfd.bReserved=32;						    // ������
  pfd.dwLayerMask=32;
  pfd.dwVisibleMask=32;
  pfd.dwDamageMask=32;						// ������������ ����� ����
  
  hDC=GetDC(hWnd);
  if(!(PixelFormat=ChoosePixelFormat(hDC,&pfd))){// ����� ������� ��������
    //"�� ���� ����� ���������� ������ ��������"
    //Luna<OSAPP>::msg("$ER","$er_choose_pixel_format");
    return false;
  }
  if(!(SetPixelFormat(hDC, PixelFormat,&pfd))){// ��������� ������ ��������� ������� ��������
    //"�� ���� ���������� ������ ��������","������"
    //Luna<OSAPP>::msg("$ER","$er_set_pixel_format");
    return false;
  }
  if(!(hRC=wglCreateContext(hDC))){// ��������� OpenGL ��������� Windows // ��������� ������
    //"�� ���� ������� �������� ���������� ����������","������"
    //Luna<OSAPP>::msg("$ER","$er_wgl_create_context");
    return false;
  }
  if(!wglMakeCurrent(hDC,hRC)) {
    //"�� ���� ���������� ����� ��������� ���������� ����������","������"
    //Luna<OSAPP>::msg("$ER","$er_wgl_make_current");
    return false;
  }
  
  //oglext.Init();
  glInitNamesArray(); // �������������� ������ ���� ���������� ����������
  vendor=(const char*)glGetString(GL_VENDOR);
  renderer=(const char*)glGetString(GL_RENDERER);
  version=(const char*)glGetString(GL_VERSION);
  extensions=(const char*)glGetString(GL_EXTENSIONS);
  //Size(size);
  return true;
}
void APP::close(){
  // ��������������� OpenGL
  //Luna<OSAPP>::msg("$gl_dest");
  ChangeDisplaySettings(NULL,0);// ����������� ��������� ������� � ��������������
  //Luna<OSAPP>::msg("$OK");
  wglMakeCurrent(hDC,NULL);
  //Luna<OSAPP>::msg("$glx_decontext");
  wglDeleteContext(hRC);// �������� OpenGL ��������� Windows
  //Luna<OSAPP>::msg("$OK");
  ReleaseDC(hWnd,hDC);
  // �������� ����
  //Luna<OSAPP>::msg("$x_close");
  DestroyWindow(hWnd);
  //Luna<OSAPP>::msg("$OK");
}

bool APP::procMessage(HWND hWindow, UINT message, WPARAM wParam, LPARAM lParam){
  //hWnd=hWindow;
  switch(message){ // ��������� ���������
  case WM_CREATE:  // �������� ����
    break;
  case WM_CLOSE:   // �������� ����
  case WM_DESTROY: // ������� ����������
  case WM_QUIT:  break;
  case WM_MOUSEMOVE:
    tagPOINT pos;
    GetCursorPos(&pos);// ��� ������
    wmouse=vec2(pos.x-wpos.x,pos.y-wpos.y);
    break;
  case WM_LBUTTONDOWN: wkey=KEY::mleft;   wkeystate=true;  break;
  case WM_LBUTTONUP:   wkey=KEY::mleft;   wkeystate=false; break;
  case WM_MBUTTONDOWN: wkey=KEY::mcenter; wkeystate=true;  break;
  case WM_MBUTTONUP:   wkey=KEY::mcenter; wkeystate=false; break;
  case WM_RBUTTONDOWN: wkey=KEY::mright;  wkeystate=true;  break;
  case WM_RBUTTONUP:   wkey=KEY::mright;  wkeystate=false; break;
  case 0x020A: // ������� ������ ����
    if(wParam==0x00780000)wkey=KEY::wheel_up;
    if(wParam==0xFF880000)wkey=KEY::wheel_down;
    //mwheel=wParam; 
    break;	// 
  case WM_KEYDOWN:// ������� �������
	wkey=wParam; wkeystate=true;  break;
  case WM_KEYUP:// ��������� �������
	wkey=wParam; wkeystate=false; break;
  case WM_SYSKEYDOWN:// ������� �������
	wkey=wParam; wkeystate=true;  break;
  case WM_SYSKEYUP:// ��������� �������
	wkey=wParam; wkeystate=false; break;
  case WM_MOVE:
  case WM_SIZE:// ��������� �������� ����
    tagRECT wr;
    GetWindowRect(hWnd,&wr);// ��� ������ ����
    wpos=vec2(wr.left,wr.top);
    wsize=vec2(wr.right-wr.left,wr.bottom-wr.top);
    break;
  default:// ��������� ��������� ���������
    return false;
  }
  if(wkey!=0){
	xkeys->push_back(KEY(wkey,wkeystate));
	wkey=0;  wkeystate=false;
	while(xkeys->size()>MAX_KEYS_STATE)xkeys->pop_front();
  }
  return true;
}
bool APP::run(){// ���������� ���������
  ReGeom();
  ReUser();
  if(PeekMessage(&mes,NULL,0,0,PM_NOREMOVE)){
    if(GetMessage(&mes,NULL,0,0)){
      TranslateMessage(&mes);
      DispatchMessage(&mes);
    }else{
      return false;
    }
  }
  return true;
}

void APP::bind(){
  if(!wglMakeCurrent(hDC,hRC)) {
    //"�� ���� ���������� ����� ��������� ���������� ����������","������"
  }
}
void APP::ubind(){// ���� ������
  SwapBuffers(hDC);
  //glClearColor(0.5,0.5,0.5,1.0);
  //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

// ����������
KEY& APP::keys(){
  KEY kb;
  if(xkeys->size()>0){
    kb=*(xkeys->begin());
	//cout<<"Key state "<<KEYBOARD::f12<<" "<<kb.key<<" "<<kb.state<<"\n";
    xkeys->pop_front();
	//kb.key+=0x20;
  }else{
	kb=KEY(0,false);
  }
  return kb;
}
bool APP::key(unsigned int& k){// ����������
  k=(unsigned int)wkey;
  wkey=0;
  return wkeystate;
}

#endif
