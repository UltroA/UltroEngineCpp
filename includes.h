#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <SDL.h>
#ifdef __APPLE__
    #include <OpenGL/glu.h>
    #include <OpenGL/glext.h>
#else
    #include <GL/glu.h>
    #include <GL/glext.h>
    #include <GL/glx.h>
    #include <GL/glxext.h>
    #define glXGetProcAddress(x) (*glXGetProcAddressARB)((const GLubyte*)x)
#endif

#include <math.h>
#include <time.h>
#include <unistd.h>