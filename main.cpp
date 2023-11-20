#include <math.h>
#include <stdio.h>
#include <glut.h>

#define res        1                        //0=160x120 1=360x240 4=640x480
#define SW         160*res                  //screen width
#define SH         120*res                  //screen height
#define SW2        (SW/2)                   //half of screen width
#define SH2        (SH/2)                   //half of screen height
#define pixelScale 4/res                    //OpenGL pixel scale
#define GLSW       (SW*pixelScale)          //OpenGL window width
#define GLSH       (SH*pixelScale)          //OpenGL window height
//------------------------------------------------------------------------------
typedef struct
{
 int fr1,fr2;           //frame 1 frame 2, to create constant frame rate
}time; time T;

typedef struct
{
 int w,s,a,d;           //move up, down, left, right
 int sl,sr;             //strafe left, right
 int m;                 //move up, down, look up, down
}keys; keys K;

typedef struct {
 float cos[360];
 float sin[360];
}math; math M;

typedef struct {
 int x, y, z;
 int a;
 int l;
}player; player Player;

//------------------------------------------------------------------------------

void pixel(int x,int y, int c)                  //draw a pixel at x/y with rgb
{int rgb[3];
 if(c==0){ rgb[0]=255; rgb[1]=255; rgb[2]=  0;} //Yellow
 if(c==1){ rgb[0]=160; rgb[1]=160; rgb[2]=  0;} //Yellow darker
 if(c==2){ rgb[0]=  0; rgb[1]=255; rgb[2]=  0;} //Green
 if(c==3){ rgb[0]=  0; rgb[1]=160; rgb[2]=  0;} //Green darker
 if(c==4){ rgb[0]=  0; rgb[1]=255; rgb[2]=255;} //Cyan
 if(c==5){ rgb[0]=  0; rgb[1]=160; rgb[2]=160;} //Cyan darker
 if(c==6){ rgb[0]=160; rgb[1]=100; rgb[2]=  0;} //brown
 if(c==7){ rgb[0]=110; rgb[1]= 50; rgb[2]=  0;} //brown darker
 if(c==8){ rgb[0]=  0; rgb[1]= 60; rgb[2]=130;} //background
 glColor3ub(rgb[0],rgb[1],rgb[2]);
 glBegin(GL_POINTS);
 glVertex2i(x*pixelScale+2,y*pixelScale+2);
 glEnd();
}

void movePlayer()
{
 //move up, down, left, right
 if(K.a ==1 && K.m==0){ Player.a -= 4; if (Player.a < 0) {Player.a += 360;} }
 if(K.d ==1 && K.m==0){ Player.a += 4; if (Player.a >359) {Player.a -= 360;} }

 int dx = M.sin[Player.a]*10.0;
 int dy = M.cos[Player.a]*10.0;

 if(K.w ==1 && K.m==0) { Player.x+=dx; Player.y+=dy; }
 if(K.s ==1 && K.m==0){ Player.x-=dx; Player.y+=dy; }

 if(K.sr==1){ Player.x+=dy; Player.y-=dx; }
 if(K.sl==1){ Player.x-=dy; Player.y+=dx; }


 //move up, down, look up, look down
 if(K.a==1 && K.m==1){ Player.l-=1; }
 if(K.d==1 && K.m==1){ Player.l+=1; }
 if(K.w==1 && K.m==1){ Player.z-=4; }
 if(K.s==1 && K.m==1){ Player.z+=4; }
}

void clearBackground()
{int x,y;
 for(y=0;y<SH;y++)
 {
  for(x=0;x<SW;x++){ pixel(x,y,8);} //clear background color
 }
}

void draw3D()
{
 int wx[4];
 int wy[4];
 int wz[4];

 float cos_f_c = M.cos[Player.a];
 float sin_f_c = M.sin[Player.a];

 int x1 = 40 - Player.x;
 int y1 = 10 - Player.y;

 int x2 = 40 - Player.x;
 int y2 = 290 - Player.y;

 wx[0] = x1*cos_f_c-y1*sin_f_c;
 wx[1] = x2*cos_f_c-y2*sin_f_c;

 wy[0] = y1*cos_f_c+x1*sin_f_c;
 wy[1] = y2*cos_f_c+x2*sin_f_c;

 wz[0] = 0 - Player.z;
 wz[1] = 0 - Player.z;

 wx[0] = wx[0]*200/wy[0] + SW2;
 wy[0] = wz[0]*200/wy[0] + SH2;

 wx[1] = wx[1]*200/wy[1] + SW2;
 wy[1] = wz[1]*200/wy[1] + SH2;

 if(wx[0]>0 && wx[0]<SW && wy[0]>0 && wy[0] < SH) { pixel(wx[0],wy[0],wz[0]); }
 if(wx[0]>0 && wx[0]<SW && wy[0]>0 && wy[0] < SH) { pixel(wx[1],wy[1],wz[1]); }
}

void display()
{int x,y;
 if(T.fr1-T.fr2>=16)                        //only draw 20 frames/second
 {
  clearBackground();
  movePlayer();
  draw3D();

  T.fr2=T.fr1;
  glutSwapBuffers();
  glutReshapeWindow(GLSW,GLSH);             //prevent window scaling
 }

 T.fr1=glutGet(GLUT_ELAPSED_TIME);          //1000 Milliseconds per second
 glutPostRedisplay();
}

void KeysDown(unsigned char key,int x,int y)
{
 if(key=='w'==1){ K.w =1;}
 if(key=='s'==1){ K.s =1;}
 if(key=='a'==1){ K.a =1;}
 if(key=='d'==1){ K.d =1;}
 if(key=='m'==1){ K.m =1;}
 if(key==','==1){ K.sr=1;}
 if(key=='.'==1){ K.sl=1;}
}
void KeysUp(unsigned char key,int x,int y)
{
 if(key=='w'==1){ K.w =0;}
 if(key=='s'==1){ K.s =0;}
 if(key=='a'==1){ K.a =0;}
 if(key=='d'==1){ K.d =0;}
 if(key=='m'==1){ K.m =0;}
 if(key==','==1){ K.sr=0;}
 if(key=='.'==1){ K.sl=0;}
}

void init()
{
 int x;
 for (x=0; x<360; x++) {
  M.cos[x]= cos(x/180.0*M_PI);
  M.sin[x]= sin(x/180.0*M_PI);
 }

 Player.x = 0;
 Player.y = 0;
 Player.z = 0;
 Player.a = 0;
 Player.l = 0;
}

int main(int argc, char* argv[])
{
 glutInit(&argc, argv);
 glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
 glutInitWindowPosition(GLSW/2,GLSH/2);
 glutInitWindowSize(GLSW,GLSH);
 glutCreateWindow("");
 glPointSize(pixelScale);                        //pixel size
 gluOrtho2D(0,GLSW,0,GLSH);                      //origin bottom left
 init();
 glutDisplayFunc(display);
 glutKeyboardFunc(KeysDown);
 glutKeyboardUpFunc(KeysUp);
 glutMainLoop();
 return 0;
}
