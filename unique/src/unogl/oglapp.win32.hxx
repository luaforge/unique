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

#ifdef _WIN32
# ifndef _WINAPP_H
#  define _WINAPP_H

#  include<windows.h>
#  include<gl/gl.h>// ���� �� ������������ ����
#  include<gl/glu.h>// ���������� �� ������������ ����
#  include<gl/glext.h>// ���� �� ����������

// ���������� �����

#  include "oglext.hpp"

class GLAPP: public GRAPHCONTEXT{
 public:
  enum{
    // ����� ����
    dflt=0, // ������ �����
    none=1,    // ������ ����
    bord=2,  // ���� c ������
    head=4,    // ���� � ������
    sbtn=8,  // ���� � �������� ���������� ����
    maxw=10,     // ������������ ����
  };
 protected:
  bool regeom;       // ����������� ��������� ����
  bool reui;         // ����������� ���������
  bool wcrted;
  // �������������� ��������
  HINSTANCE hInst;   // �� ������
  HWND      hWnd;    // �������� ����
  WNDCLASS  WinClass;// ����� ����
  DWORD     dwstyle; // ����� ����
  MSG       mes;     // ��������� �������
  // �������������� ���������� ������
  RECT      Rect;    // ������� ������
  HGLRC     hRC;     // �������� ����������
  HDC       hDC;     // �������� ���������� ������
  PIXELFORMATDESCRIPTOR pfd;// ���������� ������� ��������
  GLuint    PixelFormat;// ������ ��������
  //OGLEXT    oglext;  // �������� ���������� OpenGL
 public:
  // ���������� ���������

  deque<KEY>* xkeys;

  vec2         opos,          // ���������� �������
	           wpos,          // ������� ����
			   osize,         // �������������� ������
               wsize,         // ������ ���� || ����������
			   omouse,
	           wmouse;        // ���������� ������� � �������� ����
  bool         wmode;         // ������ ������ (false - � ���� || true - �� ���� �����)
  unsigned int wkey,          // ��� �������������� �������
               mwheel;
  bool         wkeystate,     // ��������� ��������� (������ ��)
               vsync_state, // ������������ ������������� ���\����
               cursorvis;   // ����� �� ������

  const char* vendor;
  const char* renderer;
  const char* version;
  const char* extensions;
  // ������ ������
  GLAPP();
  ~GLAPP();
  // ����
  bool key(unsigned int& k);// ������� k 
  KEY& keys();
  void  cursor(bool cur);  // ��������� ��������� �������
  bool  cursor();    // �������� ��������� �������
  void  mouse(vec2& cpos); // ��������� ��������� ������� � �������� ����
  vec2& mouse();     // ������ ��������� ������� � �������� ����
  // ����
  void Style(GLuint newstyle); // ��������� ����� ����
  void Title(const char *nwname); // ��������� ��������� ����  
  // ����
  void  pos(vec2& p);
  vec2& pos();
  void  size(vec2& s);
  vec2& size();
  void mode(bool m);
  bool mode();
  void sync(bool state); // ��������� \ ���������� ������������ �������������
  bool sync();
  //bool open(vec2 size=vec2(640,480),int bpp=16,GLuint style=APP::st_none);
  bool open(vec2 size, int bpp, GLuint style);
  bool open(vec2 size, int bpp){ return open(size,bpp,APP::head+APP::bord+APP::sbtn); }
  bool open(vec2 size){ return open(size,16,APP::none); }
  bool open(){ return open(vec2(640,480),16,APP::none); }
  void close();
  // ���������� ���������
  bool procMessage(HWND hWindow, UINT message, WPARAM wParam, LPARAM lParam);
  bool run();    // ���������� ������� (��������� ��������� ����������,
                 // ����� �� �������� ����� �������� � ������������ ��������)
  // OpenGL
  void bind();     // ������ �������� ������� ���������� �������
  void ubind();    // ���� ������ (����� �������� �������� �� �����) � ���������� ���������
  // ���� ������ ������� ��������� � �������� ������� �������
  //LRESULT CALLBACK operator ()(HWND hWindow,UINT message,WPARAM wParam,LPARAM lParam);
  void ReGeom();
  void ReUser();
};

static const vec2 default_size(640,480);

# endif
#endif
