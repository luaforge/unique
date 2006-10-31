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

#include"glapp.win32.hpp" // Системные заголовочные файлы

using namespace unogl;

//#include <map>
//typedef map<HWND, OSAPP*, less<HWND> > WINAPPS;
//WINAPPS wapps;
APP* appw;

typedef BOOL (APIENTRY * wglSwapIntervalEXT_Func)(int);
wglSwapIntervalEXT_Func wglSwapIntervalEXT=wglSwapIntervalEXT_Func(wglGetProcAddress("wglSwapIntervalEXT"));
// Та самая функция расширения управления вертикальной синхронизации

// Реализация

void *OGLEXT::GetProcAddress(const char *func_name){
// Это обеспечивает нахождение функций расширений OpenGL по их имени
  void *func_pointer=NULL;
  func_pointer=wglGetProcAddress(func_name);
  //if(func_pointer==NULL)Luna<OSAPP>::msg("$err_notsupported_ext",func_name);
  return func_pointer;
}

LRESULT CALLBACK MainWindowProc(HWND hWindow,UINT message,WPARAM wParam,LPARAM lParam){
  // Перехват сообщений Windows, ненавистная оконная функция, которая мешает 
  // объектно-ориентированному программированию ;)
  appw->procMessage(hWindow,message,wParam,lParam);
  //OSAPP* wa=wapps[hWindow];
  //wa->  
  return (DefWindowProc(hWindow, message, wParam, lParam));
}

APP::APP(){ // Конструктор
  //memset(this,0,sizeof(OSAPP));
  hWnd=NULL;
  hInst=GetModuleHandle(NULL);
}
APP::~APP(){close();}

void APP::sync(bool state){// Вертикальная синхронизация
  if(wglSwapIntervalEXT){
    vsync_state=state;
    wglSwapIntervalEXT((int)state);
  }
}
bool APP::sync(){
  return vsync_state;
}
void APP::mode(bool m){// Видеорежим true - полноэкранный, false - в окне
  wmode=m;
  if(m){
    DEVMODE dmScreenSettings;	// Полноэкраннаая конфигурация
    // Полноекранное приложение
    memset(&dmScreenSettings,0,sizeof(DEVMODE));
    dmScreenSettings.dmSize      =sizeof(DEVMODE);
    dmScreenSettings.dmPelsWidth =wsize.x;
    dmScreenSettings.dmPelsHeight=wsize.y;
    dmScreenSettings.dmFields    =DM_PELSWIDTH | DM_PELSHEIGHT;
    ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);
  }else{
    ChangeDisplaySettings(NULL,0);// Возврат к предыдущим настройкам
  }
  //Luna<OSAPP>::msg("$OK");
}
bool APP::mode(){
  return wmode;
}
void APP::size(vec2& s){// Установка разрешения \ размера окна
  if(s.x>0 && s.y>0){
    if(hWnd)SetWindowPos(hWnd,HWND_TOP,0,0,(GLuint)s.x,(GLuint)s.y,SWP_NOMOVE);
  }else{
  }
  glViewport(0,0,s.x,s.y);// Порт вывода
}
vec2& APP::size(){
  osize=wsize; // Чтоб проверить потом, был ли изменен размер программно
  return (vec2&)wsize;
}
void APP::pos(vec2& p){
  if(p.x<0 || p.y<0){
  }else{
    if(hWnd)SetWindowPos(hWnd,HWND_TOP,p.x,p.y,0,0,SWP_NOSIZE);
  }
}
vec2& APP::pos(){
  opos=wpos; // Чтоб проверить потом, была ли измена позиция программно
  return (vec2&)wpos;
}
void APP::ReGeom(){ // Check Program Change Window Geometry
  if(wpos!=opos){ pos(wpos); opos=wpos; }
  if(wsize!=osize){ size(wsize); osize=wsize; } // Проверяем, был ли изменен размер программно
}
void APP::ReUser(){ // Check Program Change User Interface (mousing and etc)
  if(omouse!=wmouse){ mouse(wmouse); wmouse=omouse; }
}
//Мышь
void APP::cursor(bool cur){// Видимость курсора
  cursorvis=cur;
  ShowCursor(cur);// Скрываем курсор
}
bool APP::cursor(){// Видимость курсора
  return cursorvis;
}
void APP::mouse(vec2& cpos){// Установка положения курсора в пределах окна
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
//SetCursorPos((1.0+cpos.x)*wwidth/2+wxpos,(1.0-cpos.y)*wheight/2+wypos);

//  Далее я отказался от етой идеи, доверя все программисту на Луа
  SetCursorPos(cpos.x+wpos.x,cpos.y+wpos.y);
}
vec2& APP::mouse(){// Взятие положения курсора в пределах окна
//
//  Здесь следует произвести обратное преобразование.
//
//cpos.x=2.0f*(mXpos-wxpos)/wwidth-1.0;
//cpos.y=-2.0f*(mYpos-wypos)/wheight+1.0;

//  Далее я отказался от етой идеи, доверя все программисту на Луа
  omouse=wmouse; // Чтоб проверить, передвинули ли мышь программно
  return (vec2&)wmouse;
}
/*void OSAPP::WinRect(){
  tagRECT wpos;
  GetWindowRect(hWnd,&wpos);// где начало окна
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
  // Заполняем параметры класса окна
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
  if(!RegisterClass(&WinClass)){// Регистрируем класс окна
    //"Ошибка создания класса окна","Фатальная ошибка!!!"
    return false;
  }
  appw=this;
  Style(style);
  //std::cout<<size.x<<","<<size.y<<":"<<bpp;
  if(!(hWnd=CreateWindow(// Создаем окно
			 WinClass.lpszClassName, // Класс окна
			 WinClass.lpszClassName, // Имя окна	
			 dwstyle,// Стиль окна
			 0,0,// Верхний левый угол
			 size.x,size.y,// Размер
			 NULL,NULL,hInst,NULL))){// Обработка ошибки создания окна
    //"Ошибка создания окна!"    
    return false;
  }

  ShowWindow(hWnd,SW_SHOW); // Показываем окно
  UpdateWindow(hWnd);       // Обновляем
  SetFocus(hWnd);           // Устанавливаем фокус

  //Luna<OSAPP>::msg("$OK");
  // Инициализайия OpenGL
  //Luna<OSAPP>::msg("$gl_init");
  // Установка формата пикселей
  pfd.nSize=sizeof(PIXELFORMATDESCRIPTOR);// размер
  pfd.nVersion=1;							// версия
  pfd.dwFlags=PFD_DRAW_TO_WINDOW|PFD_SUPPORT_OPENGL|PFD_DOUBLEBUFFER;
  // Формат должен поддерживаться Window // Формат должен поддерживатьса OpenGL
  // Должен поддерживать двойной буфер
  pfd.iPixelType=PFD_TYPE_RGBA;			    // требуется RGBA формат
  pfd.cColorBits=32;					    // Глубина цвета
  pfd.cRedBits=16;
  pfd.cRedShift=16;
  pfd.cGreenBits=16;
  pfd.cGreenShift=16;
  pfd.cBlueBits=16;
  pfd.cBlueShift=16;						// Игнорируемые биты цвета
  pfd.cAlphaBits=16;						// Нет альфа буфера
  pfd.cAlphaShift=16;						// бит Игнорирования сдвига 
  pfd.cAccumBits=16;						// Нет буфера накопления
  pfd.cAccumRedBits=16;
  pfd.cAccumGreenBits=16;
  pfd.cAccumBlueBits=16;
  pfd.cAccumAlphaBits=16;					// Игнорируемые биты буфера накопления
  pfd.cDepthBits=32;						// Глубина z-буфера
  pfd.cStencilBits=32;						// Нет стенсил буфера
  pfd.cAuxBuffers=32;						// Нет вспомогательного буфера
  pfd.iLayerType=PFD_MAIN_PLANE;			// Главный слой вывода
  pfd.bReserved=32;						    // Резерв
  pfd.dwLayerMask=32;
  pfd.dwVisibleMask=32;
  pfd.dwDamageMask=32;						// Игнорируемая маска слоя
  
  hDC=GetDC(hWnd);
  if(!(PixelFormat=ChoosePixelFormat(hDC,&pfd))){// выбор формата пикселей
    //"Не могу найти подходящий Формат пикселей"
    //Luna<OSAPP>::msg("$ER","$er_choose_pixel_format");
    return false;
  }
  if(!(SetPixelFormat(hDC, PixelFormat,&pfd))){// Обработка ошибки установки формата пикселей
    //"Не могу установить Формат пикселей","Ошибка"
    //Luna<OSAPP>::msg("$ER","$er_set_pixel_format");
    return false;
  }
  if(!(hRC=wglCreateContext(hDC))){// Установка OpenGL контекста Windows // Обработка ошибки
    //"Не могу создать контекст устройства рендеринга","Ошибка"
    //Luna<OSAPP>::msg("$ER","$er_wgl_create_context");
    return false;
  }
  if(!wglMakeCurrent(hDC,hRC)) {
    //"Не могу установить поток контекста устройства рендеринга","Ошибка"
    //Luna<OSAPP>::msg("$ER","$er_wgl_make_current");
    return false;
  }
  
  //oglext.Init();
  glInitNamesArray(); // Инициализируем массив имен свободными значениями
  vendor=(const char*)glGetString(GL_VENDOR);
  renderer=(const char*)glGetString(GL_RENDERER);
  version=(const char*)glGetString(GL_VERSION);
  extensions=(const char*)glGetString(GL_EXTENSIONS);
  //Size(size);
  return true;
}
void APP::close(){
  // Деинициализация OpenGL
  //Luna<OSAPP>::msg("$gl_dest");
  ChangeDisplaySettings(NULL,0);// Возвращение установок дисплея к первоначальным
  //Luna<OSAPP>::msg("$OK");
  wglMakeCurrent(hDC,NULL);
  //Luna<OSAPP>::msg("$glx_decontext");
  wglDeleteContext(hRC);// Удаление OpenGL контекста Windows
  //Luna<OSAPP>::msg("$OK");
  ReleaseDC(hWnd,hDC);
  // Закрытие окна
  //Luna<OSAPP>::msg("$x_close");
  DestroyWindow(hWnd);
  //Luna<OSAPP>::msg("$OK");
}

bool APP::procMessage(HWND hWindow, UINT message, WPARAM wParam, LPARAM lParam){
  //hWnd=hWindow;
  switch(message){ // Обработка сообщений
  case WM_CREATE:  // Создание окна
    break;
  case WM_CLOSE:   // Закрытие окна
  case WM_DESTROY: // Останов приложения
  case WM_QUIT:  break;
  case WM_MOUSEMOVE:
    tagPOINT pos;
    GetCursorPos(&pos);// где курсор
    wmouse=vec2(pos.x-wpos.x,pos.y-wpos.y);
    break;
  case WM_LBUTTONDOWN: wkey=KEY::mleft;   wkeystate=true;  break;
  case WM_LBUTTONUP:   wkey=KEY::mleft;   wkeystate=false; break;
  case WM_MBUTTONDOWN: wkey=KEY::mcenter; wkeystate=true;  break;
  case WM_MBUTTONUP:   wkey=KEY::mcenter; wkeystate=false; break;
  case WM_RBUTTONDOWN: wkey=KEY::mright;  wkeystate=true;  break;
  case WM_RBUTTONUP:   wkey=KEY::mright;  wkeystate=false; break;
  case 0x020A: // Вертаем колесо мыши
    if(wParam==0x00780000)wkey=KEY::wheel_up;
    if(wParam==0xFF880000)wkey=KEY::wheel_down;
    //mwheel=wParam; 
    break;	// 
  case WM_KEYDOWN:// Нажатие клавиши
	wkey=wParam; wkeystate=true;  break;
  case WM_KEYUP:// Опускание клавиши
	wkey=wParam; wkeystate=false; break;
  case WM_SYSKEYDOWN:// Нажатие клавиши
	wkey=wParam; wkeystate=true;  break;
  case WM_SYSKEYUP:// Опускание клавиши
	wkey=wParam; wkeystate=false; break;
  case WM_MOVE:
  case WM_SIZE:// Изменение размеров окна
    tagRECT wr;
    GetWindowRect(hWnd,&wr);// где начало окна
    wpos=vec2(wr.left,wr.top);
    wsize=vec2(wr.right-wr.left,wr.bottom-wr.top);
    break;
  default:// Обработка остальных сообщений
    return false;
  }
  if(wkey!=0){
	xkeys->push_back(KEY(wkey,wkeystate));
	wkey=0;  wkeystate=false;
	while(xkeys->size()>MAX_KEYS_STATE)xkeys->pop_front();
  }
  return true;
}
bool APP::run(){// Трансляция сообщений
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
    //"Не могу установить поток контекста устройства рендеринга","Ошибка"
  }
}
void APP::ubind(){// Своп буфера
  SwapBuffers(hDC);
  //glClearColor(0.5,0.5,0.5,1.0);
  //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

// Клавиатура
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
bool APP::key(unsigned int& k){// Клавиатура
  k=(unsigned int)wkey;
  wkey=0;
  return wkeystate;
}

#endif
