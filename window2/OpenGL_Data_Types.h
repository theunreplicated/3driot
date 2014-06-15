#ifndef INC_OPENGL_DATA_TYPES_H
#define INC_OPENGL_DATA_TYPES_H
typedef unsigned char          khronos_uint8_t;//https://chromium.googlesource.com/angle/angle/+/master/include/KHR/khrplatform.h
typedef signed   char          khronos_int8_t;
typedef          float         khronos_float_t;
typedef int                    khronos_int32_t;//abhängig,nicht unbedingt integer,ifdefs im Code


typedef void             GLvoid;
typedef char             GLchar;
typedef unsigned int     GLenum;
typedef unsigned char    GLboolean;
typedef unsigned int     GLbitfield;
typedef khronos_int8_t   GLbyte;
typedef short            GLshort;
typedef int              GLint;
typedef int              GLsizei;

typedef khronos_uint8_t  GLubyte;
typedef unsigned short   GLushort;
typedef unsigned int     GLuint;
typedef float  GLfloat;
typedef khronos_float_t  GLclampf;
typedef khronos_int32_t  GLfixed;
#endif