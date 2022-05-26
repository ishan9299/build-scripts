#ifndef WIN32_OPENGL_LOADER
#define WIN32_OPENGL_LOADER

/*
** Copyright (c) 2008-2018 The Khronos Group Inc.
**
** Permission is hereby granted, free of charge, to any person obtaining a
** copy of this software and/or associated documentation files (the
** "Materials"), to deal in the Materials without restriction, including
** without limitation the rights to use, copy, modify, merge, publish,
** distribute, sublicense, and/or sell copies of the Materials, and to
** permit persons to whom the Materials are furnished to do so, subject to
** the following conditions:
**
** The above copyright notice and this permission notice shall be included
** in all copies or substantial portions of the Materials.
**
** THE MATERIALS ARE PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
** MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
** CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
** TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
** MATERIALS OR THE USE OR OTHER DEALINGS IN THE MATERIALS.
*/

/* Khronos platform-specific types and definitions.
 *
 * The master copy of khrplatform.h is maintained in the Khronos EGL
 * Registry repository at https://github.com/KhronosGroup/EGL-Registry
 * The last semantic modification to khrplatform.h was at commit ID:
 *      67a3e0864c2d75ea5287b9f3d2eb74a745936692
 *
 * Adopters may modify this file to suit their platform. Adopters are
 * encouraged to submit platform specific modifications to the Khronos
 * group so that they can be included in future versions of this file.
 * Please submit changes by filing pull requests or issues on
 * the EGL Registry repository linked above.
 *
 *
 * See the Implementer's Guidelines for information about where this file
 * should be located on your system and for more details of its use:
 *    http://www.khronos.org/registry/implementers_guide.pdf
 *
 * This file should be included as
 *        #include <KHR/khrplatform.h>
 * by Khronos client API header files that use its types and defines.
 *
 * The types in khrplatform.h should only be used to define API-specific types.
 *
 * Types defined in khrplatform.h:
 *    khronos_int8_t              signed   8  bit
 *    khronos_uint8_t             unsigned 8  bit
 *    khronos_int16_t             signed   16 bit
 *    khronos_uint16_t            unsigned 16 bit
 *    khronos_int32_t             signed   32 bit
 *    khronos_uint32_t            unsigned 32 bit
 *    khronos_int64_t             signed   64 bit
 *    khronos_uint64_t            unsigned 64 bit
 *    khronos_intptr_t            signed   same number of bits as a pointer
 *    khronos_uintptr_t           unsigned same number of bits as a pointer
 *    khronos_ssize_t             signed   size
 *    khronos_usize_t             unsigned size
 *    khronos_float_t             signed   32 bit floating point
 *    khronos_time_ns_t           unsigned 64 bit time in nanoseconds
 *    khronos_utime_nanoseconds_t unsigned time interval or absolute time in
 *                                         nanoseconds
 *    khronos_stime_nanoseconds_t signed time interval in nanoseconds
 *    khronos_boolean_enum_t      enumerated boolean type. This should
 *      only be used as a base type when a client API's boolean type is
 *      an enum. Client APIs which use an integer or other type for
 *      booleans cannot use this as the base type for their boolean.
 *
 * Tokens defined in khrplatform.h:
 *
 *    KHRONOS_FALSE, KHRONOS_TRUE Enumerated boolean false/true values.
 *
 *    KHRONOS_SUPPORT_INT64 is 1 if 64 bit integers are supported; otherwise 0.
 *    KHRONOS_SUPPORT_FLOAT is 1 if floats are supported; otherwise 0.
 *
 * Calling convention macros defined in this file:
 *    KHRONOS_APICALL
 *    KHRONOS_APIENTRY
 *    KHRONOS_APIATTRIBUTES
 *
 * These may be used in function prototypes as:
 *
 *      KHRONOS_APICALL void KHRONOS_APIENTRY funcname(
 *                                  int arg1,
 *                                  int arg2) KHRONOS_APIATTRIBUTES;
 */

#if defined(__SCITECH_SNAP__) && !defined(KHRONOS_STATIC)
#   define KHRONOS_STATIC 1
#endif

/*-------------------------------------------------------------------------
 * Definition of KHRONOS_APICALL
 *-------------------------------------------------------------------------
 * This precedes the return type of the function in the function prototype.
 */
#if defined(KHRONOS_STATIC)
    /* If the preprocessor constant KHRONOS_STATIC is defined, make the
     * header compatible with static linking. */
#   define KHRONOS_APICALL
#elif defined(_WIN32)
#   define KHRONOS_APICALL __declspec(dllimport)
#elif defined (__SYMBIAN32__)
#   define KHRONOS_APICALL IMPORT_C
#elif defined(__ANDROID__)
#   define KHRONOS_APICALL __attribute__((visibility("default")))
#else
#   define KHRONOS_APICALL
#endif

/*-------------------------------------------------------------------------
 * Definition of KHRONOS_APIENTRY
 *-------------------------------------------------------------------------
 * This follows the return type of the function  and precedes the function
 * name in the function prototype.
 */
#if defined(_WIN32) && !defined(_WIN32_WCE) && !defined(__SCITECH_SNAP__)
    /* Win32 but not WinCE */
#   define KHRONOS_APIENTRY __stdcall
#else
#   define KHRONOS_APIENTRY
#endif

/*-------------------------------------------------------------------------
 * Definition of KHRONOS_APIATTRIBUTES
 *-------------------------------------------------------------------------
 * This follows the closing parenthesis of the function prototype arguments.
 */
#if defined (__ARMCC_2__)
#define KHRONOS_APIATTRIBUTES __softfp
#else
#define KHRONOS_APIATTRIBUTES
#endif

/*-------------------------------------------------------------------------
 * basic type definitions
 *-----------------------------------------------------------------------*/
#if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L) || defined(__GNUC__) || defined(__SCO__) || defined(__USLC__)


/*
 * Using <stdint.h>
 */
#include <stdint.h>
typedef int32_t                 khronos_int32_t;
typedef uint32_t                khronos_uint32_t;
typedef int64_t                 khronos_int64_t;
typedef uint64_t                khronos_uint64_t;
#define KHRONOS_SUPPORT_INT64   1
#define KHRONOS_SUPPORT_FLOAT   1
/*
 * To support platform where unsigned long cannot be used interchangeably with
 * inptr_t (e.g. CHERI-extended ISAs), we can use the stdint.h intptr_t.
 * Ideally, we could just use (u)intptr_t everywhere, but this could result in
 * ABI breakage if khronos_uintptr_t is changed from unsigned long to
 * unsigned long long or similar (this results in different C++ name mangling).
 * To avoid changes for existing platforms, we restrict usage of intptr_t to
 * platforms where the size of a pointer is larger than the size of long.
 */
#if defined(__SIZEOF_LONG__) && defined(__SIZEOF_POINTER__)
#if __SIZEOF_POINTER__ > __SIZEOF_LONG__
#define KHRONOS_USE_INTPTR_T
#endif
#endif

#elif defined(__VMS ) || defined(__sgi)

/*
 * Using <inttypes.h>
 */
#include <inttypes.h>
typedef int32_t                 khronos_int32_t;
typedef uint32_t                khronos_uint32_t;
typedef int64_t                 khronos_int64_t;
typedef uint64_t                khronos_uint64_t;
#define KHRONOS_SUPPORT_INT64   1
#define KHRONOS_SUPPORT_FLOAT   1

#elif defined(_WIN32) && !defined(__SCITECH_SNAP__)

/*
 * Win32
 */
typedef __int32                 khronos_int32_t;
typedef unsigned __int32        khronos_uint32_t;
typedef __int64                 khronos_int64_t;
typedef unsigned __int64        khronos_uint64_t;
#define KHRONOS_SUPPORT_INT64   1
#define KHRONOS_SUPPORT_FLOAT   1

#elif defined(__sun__) || defined(__digital__)

/*
 * Sun or Digital
 */
typedef int                     khronos_int32_t;
typedef unsigned int            khronos_uint32_t;
#if defined(__arch64__) || defined(_LP64)
typedef long int                khronos_int64_t;
typedef unsigned long int       khronos_uint64_t;
#else
typedef long long int           khronos_int64_t;
typedef unsigned long long int  khronos_uint64_t;
#endif /* __arch64__ */
#define KHRONOS_SUPPORT_INT64   1
#define KHRONOS_SUPPORT_FLOAT   1

#elif 0

/*
 * Hypothetical platform with no float or int64 support
 */
typedef int                     khronos_int32_t;
typedef unsigned int            khronos_uint32_t;
#define KHRONOS_SUPPORT_INT64   0
#define KHRONOS_SUPPORT_FLOAT   0

#else

/*
 * Generic fallback
 */
#include <stdint.h>
typedef int32_t                 khronos_int32_t;
typedef uint32_t                khronos_uint32_t;
typedef int64_t                 khronos_int64_t;
typedef uint64_t                khronos_uint64_t;
#define KHRONOS_SUPPORT_INT64   1
#define KHRONOS_SUPPORT_FLOAT   1

#endif


/*
 * Types that are (so far) the same on all platforms
 */
typedef signed   char          khronos_int8_t;
typedef unsigned char          khronos_uint8_t;
typedef signed   short int     khronos_int16_t;
typedef unsigned short int     khronos_uint16_t;

/*
 * Types that differ between LLP64 and LP64 architectures - in LLP64,
 * pointers are 64 bits, but 'long' is still 32 bits. Win64 appears
 * to be the only LLP64 architecture in current use.
 */
#ifdef KHRONOS_USE_INTPTR_T
typedef intptr_t               khronos_intptr_t;
typedef uintptr_t              khronos_uintptr_t;
#elif defined(_WIN64)
typedef signed   long long int khronos_intptr_t;
typedef unsigned long long int khronos_uintptr_t;
#else
typedef signed   long  int     khronos_intptr_t;
typedef unsigned long  int     khronos_uintptr_t;
#endif

#if defined(_WIN64)
typedef signed   long long int khronos_ssize_t;
typedef unsigned long long int khronos_usize_t;
#else
typedef signed   long  int     khronos_ssize_t;
typedef unsigned long  int     khronos_usize_t;
#endif

#if KHRONOS_SUPPORT_FLOAT
/*
 * Float type
 */
typedef          float         khronos_float_t;
#endif

#if KHRONOS_SUPPORT_INT64
/* Time types
 *
 * These types can be used to represent a time interval in nanoseconds or
 * an absolute Unadjusted System Time.  Unadjusted System Time is the number
 * of nanoseconds since some arbitrary system event (e.g. since the last
 * time the system booted).  The Unadjusted System Time is an unsigned
 * 64 bit value that wraps back to 0 every 584 years.  Time intervals
 * may be either signed or unsigned.
 */
typedef khronos_uint64_t       khronos_utime_nanoseconds_t;
typedef khronos_int64_t        khronos_stime_nanoseconds_t;
#endif

/*
 * Dummy value used to pad enum types to 32 bits.
 */
#ifndef KHRONOS_MAX_ENUM
#define KHRONOS_MAX_ENUM 0x7FFFFFFF
#endif

/*
 * Enumerated boolean type
 *
 * Values other than zero should be considered to be true.  Therefore
 * comparisons should not be made against KHRONOS_TRUE.
 */
typedef enum {
    KHRONOS_FALSE = 0,
    KHRONOS_TRUE  = 1,
    KHRONOS_BOOLEAN_ENUM_FORCE_SIZE = KHRONOS_MAX_ENUM
} khronos_boolean_enum_t;



#ifndef OPENGL_VERSION_1_0
#define OPENGL_VERSION_1_0 1
typedef void GLvoid;
typedef unsigned int GLenum;
typedef khronos_float_t GLfloat;
typedef int GLint;
typedef int GLsizei;
typedef unsigned int GLbitfield;
typedef double GLdouble;
typedef unsigned int GLuint;
typedef unsigned char GLboolean;
typedef khronos_uint8_t GLubyte;
#define GL_DEPTH_BUFFER_BIT               0x00000100
#define GL_STENCIL_BUFFER_BIT             0x00000400
#define GL_COLOR_BUFFER_BIT               0x00004000
#define GL_FALSE                          0
#define GL_TRUE                           1
#define GL_POINTS                         0x0000
#define GL_LINES                          0x0001
#define GL_LINE_LOOP                      0x0002
#define GL_LINE_STRIP                     0x0003
#define GL_TRIANGLES                      0x0004
#define GL_TRIANGLE_STRIP                 0x0005
#define GL_TRIANGLE_FAN                   0x0006
#define GL_QUADS                          0x0007
#define GL_NEVER                          0x0200
#define GL_LESS                           0x0201
#define GL_EQUAL                          0x0202
#define GL_LEQUAL                         0x0203
#define GL_GREATER                        0x0204
#define GL_NOTEQUAL                       0x0205
#define GL_GEQUAL                         0x0206
#define GL_ALWAYS                         0x0207
#define GL_ZERO                           0
#define GL_ONE                            1
#define GL_SRC_COLOR                      0x0300
#define GL_ONE_MINUS_SRC_COLOR            0x0301
#define GL_SRC_ALPHA                      0x0302
#define GL_ONE_MINUS_SRC_ALPHA            0x0303
#define GL_DST_ALPHA                      0x0304
#define GL_ONE_MINUS_DST_ALPHA            0x0305
#define GL_DST_COLOR                      0x0306
#define GL_ONE_MINUS_DST_COLOR            0x0307
#define GL_SRC_ALPHA_SATURATE             0x0308
#define GL_NONE                           0
#define GL_FRONT_LEFT                     0x0400
#define GL_FRONT_RIGHT                    0x0401
#define GL_BACK_LEFT                      0x0402
#define GL_BACK_RIGHT                     0x0403
#define GL_FRONT                          0x0404
#define GL_BACK                           0x0405
#define GL_LEFT                           0x0406
#define GL_RIGHT                          0x0407
#define GL_FRONT_AND_BACK                 0x0408
#define GL_NO_ERROR                       0
#define GL_INVALID_ENUM                   0x0500
#define GL_INVALID_VALUE                  0x0501
#define GL_INVALID_OPERATION              0x0502
#define GL_OUT_OF_MEMORY                  0x0505
#define GL_CW                             0x0900
#define GL_CCW                            0x0901
#define GL_POINT_SIZE                     0x0B11
#define GL_POINT_SIZE_RANGE               0x0B12
#define GL_POINT_SIZE_GRANULARITY         0x0B13
#define GL_LINE_SMOOTH                    0x0B20
#define GL_LINE_WIDTH                     0x0B21
#define GL_LINE_WIDTH_RANGE               0x0B22
#define GL_LINE_WIDTH_GRANULARITY         0x0B23
#define GL_POLYGON_MODE                   0x0B40
#define GL_POLYGON_SMOOTH                 0x0B41
#define GL_CULL_FACE                      0x0B44
#define GL_CULL_FACE_MODE                 0x0B45
#define GL_FRONT_FACE                     0x0B46
#define GL_DEPTH_RANGE                    0x0B70
#define GL_DEPTH_TEST                     0x0B71
#define GL_DEPTH_WRITEMASK                0x0B72
#define GL_DEPTH_CLEAR_VALUE              0x0B73
#define GL_DEPTH_FUNC                     0x0B74
#define GL_STENCIL_TEST                   0x0B90
#define GL_STENCIL_CLEAR_VALUE            0x0B91
#define GL_STENCIL_FUNC                   0x0B92
#define GL_STENCIL_VALUE_MASK             0x0B93
#define GL_STENCIL_FAIL                   0x0B94
#define GL_STENCIL_PASS_DEPTH_FAIL        0x0B95
#define GL_STENCIL_PASS_DEPTH_PASS        0x0B96
#define GL_STENCIL_REF                    0x0B97
#define GL_STENCIL_WRITEMASK              0x0B98
#define GL_VIEWPORT                       0x0BA2
#define GL_DITHER                         0x0BD0
#define GL_BLEND_DST                      0x0BE0
#define GL_BLEND_SRC                      0x0BE1
#define GL_BLEND                          0x0BE2
#define GL_LOGIC_OP_MODE                  0x0BF0
#define GL_DRAW_BUFFER                    0x0C01
#define GL_READ_BUFFER                    0x0C02
#define GL_SCISSOR_BOX                    0x0C10
#define GL_SCISSOR_TEST                   0x0C11
#define GL_COLOR_CLEAR_VALUE              0x0C22
#define GL_COLOR_WRITEMASK                0x0C23
#define GL_DOUBLEBUFFER                   0x0C32
#define GL_STEREO                         0x0C33
#define GL_LINE_SMOOTH_HINT               0x0C52
#define GL_POLYGON_SMOOTH_HINT            0x0C53
#define GL_UNPACK_SWAP_BYTES              0x0CF0
#define GL_UNPACK_LSB_FIRST               0x0CF1
#define GL_UNPACK_ROW_LENGTH              0x0CF2
#define GL_UNPACK_SKIP_ROWS               0x0CF3
#define GL_UNPACK_SKIP_PIXELS             0x0CF4
#define GL_UNPACK_ALIGNMENT               0x0CF5
#define GL_PACK_SWAP_BYTES                0x0D00
#define GL_PACK_LSB_FIRST                 0x0D01
#define GL_PACK_ROW_LENGTH                0x0D02
#define GL_PACK_SKIP_ROWS                 0x0D03
#define GL_PACK_SKIP_PIXELS               0x0D04
#define GL_PACK_ALIGNMENT                 0x0D05
#define GL_MAX_TEXTURE_SIZE               0x0D33
#define GL_MAX_VIEWPORT_DIMS              0x0D3A
#define GL_SUBPIXEL_BITS                  0x0D50
#define GL_TEXTURE_1D                     0x0DE0
#define GL_TEXTURE_2D                     0x0DE1
#define GL_TEXTURE_WIDTH                  0x1000
#define GL_TEXTURE_HEIGHT                 0x1001
#define GL_TEXTURE_BORDER_COLOR           0x1004
#define GL_DONT_CARE                      0x1100
#define GL_FASTEST                        0x1101
#define GL_NICEST                         0x1102
#define GL_BYTE                           0x1400
#define GL_UNSIGNED_BYTE                  0x1401
#define GL_SHORT                          0x1402
#define GL_UNSIGNED_SHORT                 0x1403
#define GL_INT                            0x1404
#define GL_UNSIGNED_INT                   0x1405
#define GL_FLOAT                          0x1406
#define GL_STACK_OVERFLOW                 0x0503
#define GL_STACK_UNDERFLOW                0x0504
#define GL_CLEAR                          0x1500
#define GL_AND                            0x1501
#define GL_AND_REVERSE                    0x1502
#define GL_COPY                           0x1503
#define GL_AND_INVERTED                   0x1504
#define GL_NOOP                           0x1505
#define GL_XOR                            0x1506
#define GL_OR                             0x1507
#define GL_NOR                            0x1508
#define GL_EQUIV                          0x1509
#define GL_INVERT                         0x150A
#define GL_OR_REVERSE                     0x150B
#define GL_COPY_INVERTED                  0x150C
#define GL_OR_INVERTED                    0x150D
#define GL_NAND                           0x150E
#define GL_SET                            0x150F
#define GL_TEXTURE                        0x1702
#define GL_COLOR                          0x1800
#define GL_DEPTH                          0x1801
#define GL_STENCIL                        0x1802
#define GL_STENCIL_INDEX                  0x1901
#define GL_DEPTH_COMPONENT                0x1902
#define GL_RED                            0x1903
#define GL_GREEN                          0x1904
#define GL_BLUE                           0x1905
#define GL_ALPHA                          0x1906
#define GL_RGB                            0x1907
#define GL_RGBA                           0x1908
#define GL_POINT                          0x1B00
#define GL_LINE                           0x1B01
#define GL_FILL                           0x1B02
#define GL_KEEP                           0x1E00
#define GL_REPLACE                        0x1E01
#define GL_INCR                           0x1E02
#define GL_DECR                           0x1E03
#define GL_VENDOR                         0x1F00
#define GL_RENDERER                       0x1F01
#define GL_VERSION                        0x1F02
#define GL_EXTENSIONS                     0x1F03
#define GL_NEAREST                        0x2600
#define GL_LINEAR                         0x2601
#define GL_NEAREST_MIPMAP_NEAREST         0x2700
#define GL_LINEAR_MIPMAP_NEAREST          0x2701
#define GL_NEAREST_MIPMAP_LINEAR          0x2702
#define GL_LINEAR_MIPMAP_LINEAR           0x2703
#define GL_TEXTURE_MAG_FILTER             0x2800
#define GL_TEXTURE_MIN_FILTER             0x2801
#define GL_TEXTURE_WRAP_S                 0x2802
#define GL_TEXTURE_WRAP_T                 0x2803
#define GL_REPEAT                         0x2901
typedef void (APIENTRYP PFNGLCULLFACEPROC) (GLenum mode);
typedef void (APIENTRYP PFNGLFRONTFACEPROC) (GLenum mode);
typedef void (APIENTRYP PFNGLHINTPROC) (GLenum target, GLenum mode);
typedef void (APIENTRYP PFNGLLINEWIDTHPROC) (GLfloat width);
typedef void (APIENTRYP PFNGLPOINTSIZEPROC) (GLfloat size);
typedef void (APIENTRYP PFNGLPOLYGONMODEPROC) (GLenum face, GLenum mode);
typedef void (APIENTRYP PFNGLSCISSORPROC) (GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (APIENTRYP PFNGLTEXPARAMETERFPROC) (GLenum target, GLenum pname, GLfloat param);
typedef void (APIENTRYP PFNGLTEXPARAMETERFVPROC) (GLenum target, GLenum pname, const GLfloat *params);
typedef void (APIENTRYP PFNGLTEXPARAMETERIPROC) (GLenum target, GLenum pname, GLint param);
typedef void (APIENTRYP PFNGLTEXPARAMETERIVPROC) (GLenum target, GLenum pname, const GLint *params);
typedef void (APIENTRYP PFNGLTEXIMAGE1DPROC) (GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const void *pixels);
typedef void (APIENTRYP PFNGLTEXIMAGE2DPROC) (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void *pixels);
typedef void (APIENTRYP PFNGLDRAWBUFFERPROC) (GLenum buf);
typedef void (APIENTRYP PFNGLCLEARPROC) (GLbitfield mask);
typedef void (APIENTRYP PFNGLCLEARCOLORPROC) (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
typedef void (APIENTRYP PFNGLCLEARSTENCILPROC) (GLint s);
typedef void (APIENTRYP PFNGLCLEARDEPTHPROC) (GLdouble depth);
typedef void (APIENTRYP PFNGLSTENCILMASKPROC) (GLuint mask);
typedef void (APIENTRYP PFNGLCOLORMASKPROC) (GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
typedef void (APIENTRYP PFNGLDEPTHMASKPROC) (GLboolean flag);
typedef void (APIENTRYP PFNGLDISABLEPROC) (GLenum cap);
typedef void (APIENTRYP PFNGLENABLEPROC) (GLenum cap);
typedef void (APIENTRYP PFNGLFINISHPROC) (void);
typedef void (APIENTRYP PFNGLFLUSHPROC) (void);
typedef void (APIENTRYP PFNGLBLENDFUNCPROC) (GLenum sfactor, GLenum dfactor);
typedef void (APIENTRYP PFNGLLOGICOPPROC) (GLenum opcode);
typedef void (APIENTRYP PFNGLSTENCILFUNCPROC) (GLenum func, GLint ref, GLuint mask);
typedef void (APIENTRYP PFNGLSTENCILOPPROC) (GLenum fail, GLenum zfail, GLenum zpass);
typedef void (APIENTRYP PFNGLDEPTHFUNCPROC) (GLenum func);
typedef void (APIENTRYP PFNGLPIXELSTOREFPROC) (GLenum pname, GLfloat param);
typedef void (APIENTRYP PFNGLPIXELSTOREIPROC) (GLenum pname, GLint param);
typedef void (APIENTRYP PFNGLREADBUFFERPROC) (GLenum src);
typedef void (APIENTRYP PFNGLREADPIXELSPROC) (GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void *pixels);
typedef void (APIENTRYP PFNGLGETBOOLEANVPROC) (GLenum pname, GLboolean *data);
typedef void (APIENTRYP PFNGLGETDOUBLEVPROC) (GLenum pname, GLdouble *data);
typedef GLenum (APIENTRYP PFNGLGETERRORPROC) (void);
typedef void (APIENTRYP PFNGLGETFLOATVPROC) (GLenum pname, GLfloat *data);
typedef void (APIENTRYP PFNGLGETINTEGERVPROC) (GLenum pname, GLint *data);
typedef const GLubyte *(APIENTRYP PFNGLGETSTRINGPROC) (GLenum name);
typedef void (APIENTRYP PFNGLGETTEXIMAGEPROC) (GLenum target, GLint level, GLenum format, GLenum type, void *pixels);
typedef void (APIENTRYP PFNGLGETTEXPARAMETERFVPROC) (GLenum target, GLenum pname, GLfloat *params);
typedef void (APIENTRYP PFNGLGETTEXPARAMETERIVPROC) (GLenum target, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLGETTEXLEVELPARAMETERFVPROC) (GLenum target, GLint level, GLenum pname, GLfloat *params);
typedef void (APIENTRYP PFNGLGETTEXLEVELPARAMETERIVPROC) (GLenum target, GLint level, GLenum pname, GLint *params);
typedef GLboolean (APIENTRYP PFNGLISENABLEDPROC) (GLenum cap);
typedef void (APIENTRYP PFNGLDEPTHRANGEPROC) (GLdouble n, GLdouble f);
typedef void (APIENTRYP PFNGLVIEWPORTPROC) (GLint x, GLint y, GLsizei width, GLsizei height);
#endif /* OPENGL_VERSION_1_0 */

#ifndef OPENGL_VERSION_1_1
#define OPENGL_VERSION_1_1 1
typedef khronos_float_t GLclampf;
typedef double GLclampd;
#define GL_COLOR_LOGIC_OP                 0x0BF2
#define GL_POLYGON_OFFSET_UNITS           0x2A00
#define GL_POLYGON_OFFSET_POINT           0x2A01
#define GL_POLYGON_OFFSET_LINE            0x2A02
#define GL_POLYGON_OFFSET_FILL            0x8037
#define GL_POLYGON_OFFSET_FACTOR          0x8038
#define GL_TEXTURE_BINDING_1D             0x8068
#define GL_TEXTURE_BINDING_2D             0x8069
#define GL_TEXTURE_INTERNAL_FORMAT        0x1003
#define GL_TEXTURE_RED_SIZE               0x805C
#define GL_TEXTURE_GREEN_SIZE             0x805D
#define GL_TEXTURE_BLUE_SIZE              0x805E
#define GL_TEXTURE_ALPHA_SIZE             0x805F
#define GL_DOUBLE                         0x140A
#define GL_PROXY_TEXTURE_1D               0x8063
#define GL_PROXY_TEXTURE_2D               0x8064
#define GL_R3_G3_B2                       0x2A10
#define GL_RGB4                           0x804F
#define GL_RGB5                           0x8050
#define GL_RGB8                           0x8051
#define GL_RGB10                          0x8052
#define GL_RGB12                          0x8053
#define GL_RGB16                          0x8054
#define GL_RGBA2                          0x8055
#define GL_RGBA4                          0x8056
#define GL_RGB5_A1                        0x8057
#define GL_RGBA8                          0x8058
#define GL_RGB10_A2                       0x8059
#define GL_RGBA12                         0x805A
#define GL_RGBA16                         0x805B
#define GL_VERTEX_ARRAY                   0x8074
typedef void (APIENTRYP PFNGLDRAWARRAYSPROC) (GLenum mode, GLint first, GLsizei count);
typedef void (APIENTRYP PFNGLDRAWELEMENTSPROC) (GLenum mode, GLsizei count, GLenum type, const void *indices);
typedef void (APIENTRYP PFNGLGETPOINTERVPROC) (GLenum pname, void **params);
typedef void (APIENTRYP PFNGLPOLYGONOFFSETPROC) (GLfloat factor, GLfloat units);
typedef void (APIENTRYP PFNGLCOPYTEXIMAGE1DPROC) (GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border);
typedef void (APIENTRYP PFNGLCOPYTEXIMAGE2DPROC) (GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border);
typedef void (APIENTRYP PFNGLCOPYTEXSUBIMAGE1DPROC) (GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width);
typedef void (APIENTRYP PFNGLCOPYTEXSUBIMAGE2DPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (APIENTRYP PFNGLTEXSUBIMAGE1DPROC) (GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void *pixels);
typedef void (APIENTRYP PFNGLTEXSUBIMAGE2DPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void *pixels);
typedef void (APIENTRYP PFNGLBINDTEXTUREPROC) (GLenum target, GLuint texture);
typedef void (APIENTRYP PFNGLDELETETEXTURESPROC) (GLsizei n, const GLuint *textures);
typedef void (APIENTRYP PFNGLGENTEXTURESPROC) (GLsizei n, GLuint *textures);
typedef GLboolean (APIENTRYP PFNGLISTEXTUREPROC) (GLuint texture);
#endif /* OPENGL_VERSION_1_1 */

#ifndef OPENGL_VERSION_1_2
#define OPENGL_VERSION_1_2 1
#define GL_UNSIGNED_BYTE_3_3_2            0x8032
#define GL_UNSIGNED_SHORT_4_4_4_4         0x8033
#define GL_UNSIGNED_SHORT_5_5_5_1         0x8034
#define GL_UNSIGNED_INT_8_8_8_8           0x8035
#define GL_UNSIGNED_INT_10_10_10_2        0x8036
#define GL_TEXTURE_BINDING_3D             0x806A
#define GL_PACK_SKIP_IMAGES               0x806B
#define GL_PACK_IMAGE_HEIGHT              0x806C
#define GL_UNPACK_SKIP_IMAGES             0x806D
#define GL_UNPACK_IMAGE_HEIGHT            0x806E
#define GL_TEXTURE_3D                     0x806F
#define GL_PROXY_TEXTURE_3D               0x8070
#define GL_TEXTURE_DEPTH                  0x8071
#define GL_TEXTURE_WRAP_R                 0x8072
#define GL_MAX_3D_TEXTURE_SIZE            0x8073
#define GL_UNSIGNED_BYTE_2_3_3_REV        0x8362
#define GL_UNSIGNED_SHORT_5_6_5           0x8363
#define GL_UNSIGNED_SHORT_5_6_5_REV       0x8364
#define GL_UNSIGNED_SHORT_4_4_4_4_REV     0x8365
#define GL_UNSIGNED_SHORT_1_5_5_5_REV     0x8366
#define GL_UNSIGNED_INT_8_8_8_8_REV       0x8367
#define GL_UNSIGNED_INT_2_10_10_10_REV    0x8368
#define GL_BGR                            0x80E0
#define GL_BGRA                           0x80E1
#define GL_MAX_ELEMENTS_VERTICES          0x80E8
#define GL_MAX_ELEMENTS_INDICES           0x80E9
#define GL_CLAMP_TO_EDGE                  0x812F
#define GL_TEXTURE_MIN_LOD                0x813A
#define GL_TEXTURE_MAX_LOD                0x813B
#define GL_TEXTURE_BASE_LEVEL             0x813C
#define GL_TEXTURE_MAX_LEVEL              0x813D
#define GL_SMOOTH_POINT_SIZE_RANGE        0x0B12
#define GL_SMOOTH_POINT_SIZE_GRANULARITY  0x0B13
#define GL_SMOOTH_LINE_WIDTH_RANGE        0x0B22
#define GL_SMOOTH_LINE_WIDTH_GRANULARITY  0x0B23
#define GL_ALIASED_LINE_WIDTH_RANGE       0x846E
typedef void (APIENTRYP PFNGLDRAWRANGEELEMENTSPROC) (GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void *indices);
typedef void (APIENTRYP PFNGLTEXIMAGE3DPROC) (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void *pixels);
typedef void (APIENTRYP PFNGLTEXSUBIMAGE3DPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void *pixels);
typedef void (APIENTRYP PFNGLCOPYTEXSUBIMAGE3DPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height);
#endif /* OPENGL_VERSION_1_2 */


#ifndef OPENGL_VERSION_1_3
#define OPENGL_VERSION_1_3 1
#define GL_TEXTURE0                       0x84C0
#define GL_TEXTURE1                       0x84C1
#define GL_TEXTURE2                       0x84C2
#define GL_TEXTURE3                       0x84C3
#define GL_TEXTURE4                       0x84C4
#define GL_TEXTURE5                       0x84C5
#define GL_TEXTURE6                       0x84C6
#define GL_TEXTURE7                       0x84C7
#define GL_TEXTURE8                       0x84C8
#define GL_TEXTURE9                       0x84C9
#define GL_TEXTURE10                      0x84CA
#define GL_TEXTURE11                      0x84CB
#define GL_TEXTURE12                      0x84CC
#define GL_TEXTURE13                      0x84CD
#define GL_TEXTURE14                      0x84CE
#define GL_TEXTURE15                      0x84CF
#define GL_TEXTURE16                      0x84D0
#define GL_TEXTURE17                      0x84D1
#define GL_TEXTURE18                      0x84D2
#define GL_TEXTURE19                      0x84D3
#define GL_TEXTURE20                      0x84D4
#define GL_TEXTURE21                      0x84D5
#define GL_TEXTURE22                      0x84D6
#define GL_TEXTURE23                      0x84D7
#define GL_TEXTURE24                      0x84D8
#define GL_TEXTURE25                      0x84D9
#define GL_TEXTURE26                      0x84DA
#define GL_TEXTURE27                      0x84DB
#define GL_TEXTURE28                      0x84DC
#define GL_TEXTURE29                      0x84DD
#define GL_TEXTURE30                      0x84DE
#define GL_TEXTURE31                      0x84DF
#define GL_ACTIVE_TEXTURE                 0x84E0
#define GL_MULTISAMPLE                    0x809D
#define GL_SAMPLE_ALPHA_TO_COVERAGE       0x809E
#define GL_SAMPLE_ALPHA_TO_ONE            0x809F
#define GL_SAMPLE_COVERAGE                0x80A0
#define GL_SAMPLE_BUFFERS                 0x80A8
#define GL_SAMPLES                        0x80A9
#define GL_SAMPLE_COVERAGE_VALUE          0x80AA
#define GL_SAMPLE_COVERAGE_INVERT         0x80AB
#define GL_TEXTURE_CUBE_MAP               0x8513
#define GL_TEXTURE_BINDING_CUBE_MAP       0x8514
#define GL_TEXTURE_CUBE_MAP_POSITIVE_X    0x8515
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_X    0x8516
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Y    0x8517
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Y    0x8518
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Z    0x8519
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Z    0x851A
#define GL_PROXY_TEXTURE_CUBE_MAP         0x851B
#define GL_MAX_CUBE_MAP_TEXTURE_SIZE      0x851C
#define GL_COMPRESSED_RGB                 0x84ED
#define GL_COMPRESSED_RGBA                0x84EE
#define GL_TEXTURE_COMPRESSION_HINT       0x84EF
#define GL_TEXTURE_COMPRESSED_IMAGE_SIZE  0x86A0
#define GL_TEXTURE_COMPRESSED             0x86A1
#define GL_NUM_COMPRESSED_TEXTURE_FORMATS 0x86A2
#define GL_COMPRESSED_TEXTURE_FORMATS     0x86A3
#define GL_CLAMP_TO_BORDER                0x812D
typedef void (APIENTRYP PFNGLACTIVETEXTUREPROC) (GLenum texture);
typedef void (APIENTRYP PFNGLSAMPLECOVERAGEPROC) (GLfloat value, GLboolean invert);
typedef void (APIENTRYP PFNGLCOMPRESSEDTEXIMAGE3DPROC) (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void *data);
typedef void (APIENTRYP PFNGLCOMPRESSEDTEXIMAGE2DPROC) (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void *data);
typedef void (APIENTRYP PFNGLCOMPRESSEDTEXIMAGE1DPROC) (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const void *data);
typedef void (APIENTRYP PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void *data);
typedef void (APIENTRYP PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void *data);
typedef void (APIENTRYP PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC) (GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void *data);
typedef void (APIENTRYP PFNGLGETCOMPRESSEDTEXIMAGEPROC) (GLenum target, GLint level, void *img);
#endif /* OPENGL_VERSION_1_3 */




#ifndef OPENGL_VERSION_1_4
#define OPENGL_VERSION_1_4 1
#define GL_BLEND_DST_RGB                  0x80C8
#define GL_BLEND_SRC_RGB                  0x80C9
#define GL_BLEND_DST_ALPHA                0x80CA
#define GL_BLEND_SRC_ALPHA                0x80CB
#define GL_POINT_FADE_THRESHOLD_SIZE      0x8128
#define GL_DEPTH_COMPONENT16              0x81A5
#define GL_DEPTH_COMPONENT24              0x81A6
#define GL_DEPTH_COMPONENT32              0x81A7
#define GL_MIRRORED_REPEAT                0x8370
#define GL_MAX_TEXTURE_LOD_BIAS           0x84FD
#define GL_TEXTURE_LOD_BIAS               0x8501
#define GL_INCR_WRAP                      0x8507
#define GL_DECR_WRAP                      0x8508
#define GL_TEXTURE_DEPTH_SIZE             0x884A
#define GL_TEXTURE_COMPARE_MODE           0x884C
#define GL_TEXTURE_COMPARE_FUNC           0x884D
#define GL_BLEND_COLOR                    0x8005
#define GL_BLEND_EQUATION                 0x8009
#define GL_CONSTANT_COLOR                 0x8001
#define GL_ONE_MINUS_CONSTANT_COLOR       0x8002
#define GL_CONSTANT_ALPHA                 0x8003
#define GL_ONE_MINUS_CONSTANT_ALPHA       0x8004
#define GL_FUNC_ADD                       0x8006
#define GL_FUNC_REVERSE_SUBTRACT          0x800B
#define GL_FUNC_SUBTRACT                  0x800A
#define GL_MIN                            0x8007
#define GL_MAX                            0x8008
typedef void (APIENTRYP PFNGLBLENDFUNCSEPARATEPROC) (GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha);
typedef void (APIENTRYP PFNGLMULTIDRAWARRAYSPROC) (GLenum mode, const GLint *first, const GLsizei *count, GLsizei drawcount);
typedef void (APIENTRYP PFNGLMULTIDRAWELEMENTSPROC) (GLenum mode, const GLsizei *count, GLenum type, const void *const*indices, GLsizei drawcount);
typedef void (APIENTRYP PFNGLPOINTPARAMETERFPROC) (GLenum pname, GLfloat param);
typedef void (APIENTRYP PFNGLPOINTPARAMETERFVPROC) (GLenum pname, const GLfloat *params);
typedef void (APIENTRYP PFNGLPOINTPARAMETERIPROC) (GLenum pname, GLint param);
typedef void (APIENTRYP PFNGLPOINTPARAMETERIVPROC) (GLenum pname, const GLint *params);
typedef void (APIENTRYP PFNGLBLENDCOLORPROC) (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
typedef void (APIENTRYP PFNGLBLENDEQUATIONPROC) (GLenum mode);
#endif /* OPENGL_VERSION_1_4 */


#ifndef OPENGL_VERSION_1_5
#define OPENGL_VERSION_1_5 1
typedef khronos_ssize_t GLsizeiptr;
typedef khronos_intptr_t GLintptr;
#define GL_BUFFER_SIZE                    0x8764
#define GL_BUFFER_USAGE                   0x8765
#define GL_QUERY_COUNTER_BITS             0x8864
#define GL_CURRENT_QUERY                  0x8865
#define GL_QUERY_RESULT                   0x8866
#define GL_QUERY_RESULT_AVAILABLE         0x8867
#define GL_ARRAY_BUFFER                   0x8892
#define GL_ELEMENT_ARRAY_BUFFER           0x8893
#define GL_ARRAY_BUFFER_BINDING           0x8894
#define GL_ELEMENT_ARRAY_BUFFER_BINDING   0x8895
#define GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING 0x889F
#define GL_READ_ONLY                      0x88B8
#define GL_WRITE_ONLY                     0x88B9
#define GL_READ_WRITE                     0x88BA
#define GL_BUFFER_ACCESS                  0x88BB
#define GL_BUFFER_MAPPED                  0x88BC
#define GL_BUFFER_MAP_POINTER             0x88BD
#define GL_STREAM_DRAW                    0x88E0
#define GL_STREAM_READ                    0x88E1
#define GL_STREAM_COPY                    0x88E2
#define GL_STATIC_DRAW                    0x88E4
#define GL_STATIC_READ                    0x88E5
#define GL_STATIC_COPY                    0x88E6
#define GL_DYNAMIC_DRAW                   0x88E8
#define GL_DYNAMIC_READ                   0x88E9
#define GL_DYNAMIC_COPY                   0x88EA
#define GL_SAMPLES_PASSED                 0x8914
#define GL_SRC1_ALPHA                     0x8589
typedef void (APIENTRYP PFNGLGENQUERIESPROC) (GLsizei n, GLuint *ids);
typedef void (APIENTRYP PFNGLDELETEQUERIESPROC) (GLsizei n, const GLuint *ids);
typedef GLboolean (APIENTRYP PFNGLISQUERYPROC) (GLuint id);
typedef void (APIENTRYP PFNGLBEGINQUERYPROC) (GLenum target, GLuint id);
typedef void (APIENTRYP PFNGLENDQUERYPROC) (GLenum target);
typedef void (APIENTRYP PFNGLGETQUERYIVPROC) (GLenum target, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLGETQUERYOBJECTIVPROC) (GLuint id, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLGETQUERYOBJECTUIVPROC) (GLuint id, GLenum pname, GLuint *params);
typedef void (APIENTRYP PFNGLBINDBUFFERPROC) (GLenum target, GLuint buffer);
typedef void (APIENTRYP PFNGLDELETEBUFFERSPROC) (GLsizei n, const GLuint *buffers);
typedef void (APIENTRYP PFNGLGENBUFFERSPROC) (GLsizei n, GLuint *buffers);
typedef GLboolean (APIENTRYP PFNGLISBUFFERPROC) (GLuint buffer);
typedef void (APIENTRYP PFNGLBUFFERDATAPROC) (GLenum target, GLsizeiptr size, const void *data, GLenum usage);
typedef void (APIENTRYP PFNGLBUFFERSUBDATAPROC) (GLenum target, GLintptr offset, GLsizeiptr size, const void *data);
typedef void (APIENTRYP PFNGLGETBUFFERSUBDATAPROC) (GLenum target, GLintptr offset, GLsizeiptr size, void *data);
typedef void *(APIENTRYP PFNGLMAPBUFFERPROC) (GLenum target, GLenum access);
typedef GLboolean (APIENTRYP PFNGLUNMAPBUFFERPROC) (GLenum target);
typedef void (APIENTRYP PFNGLGETBUFFERPARAMETERIVPROC) (GLenum target, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLGETBUFFERPOINTERVPROC) (GLenum target, GLenum pname, void **params);
#endif /* OPENGL_VERSION_1_5 */

#ifndef OPENGL_VERSION_2_0
#define OPENGL_VERSION_2_0 1
typedef char GLchar;
typedef khronos_int16_t GLshort;
typedef khronos_int8_t GLbyte;
typedef khronos_uint16_t GLushort;
#define GL_BLEND_EQUATION_RGB             0x8009
#define GL_VERTEX_ATTRIB_ARRAY_ENABLED    0x8622
#define GL_VERTEX_ATTRIB_ARRAY_SIZE       0x8623
#define GL_VERTEX_ATTRIB_ARRAY_STRIDE     0x8624
#define GL_VERTEX_ATTRIB_ARRAY_TYPE       0x8625
#define GL_CURRENT_VERTEX_ATTRIB          0x8626
#define GL_VERTEX_PROGRAM_POINT_SIZE      0x8642
#define GL_VERTEX_ATTRIB_ARRAY_POINTER    0x8645
#define GL_STENCIL_BACK_FUNC              0x8800
#define GL_STENCIL_BACK_FAIL              0x8801
#define GL_STENCIL_BACK_PASS_DEPTH_FAIL   0x8802
#define GL_STENCIL_BACK_PASS_DEPTH_PASS   0x8803
#define GL_MAX_DRAW_BUFFERS               0x8824
#define GL_DRAW_BUFFER0                   0x8825
#define GL_DRAW_BUFFER1                   0x8826
#define GL_DRAW_BUFFER2                   0x8827
#define GL_DRAW_BUFFER3                   0x8828
#define GL_DRAW_BUFFER4                   0x8829
#define GL_DRAW_BUFFER5                   0x882A
#define GL_DRAW_BUFFER6                   0x882B
#define GL_DRAW_BUFFER7                   0x882C
#define GL_DRAW_BUFFER8                   0x882D
#define GL_DRAW_BUFFER9                   0x882E
#define GL_DRAW_BUFFER10                  0x882F
#define GL_DRAW_BUFFER11                  0x8830
#define GL_DRAW_BUFFER12                  0x8831
#define GL_DRAW_BUFFER13                  0x8832
#define GL_DRAW_BUFFER14                  0x8833
#define GL_DRAW_BUFFER15                  0x8834
#define GL_BLEND_EQUATION_ALPHA           0x883D
#define GL_MAX_VERTEX_ATTRIBS             0x8869
#define GL_VERTEX_ATTRIB_ARRAY_NORMALIZED 0x886A
#define GL_MAX_TEXTURE_IMAGE_UNITS        0x8872
#define GL_FRAGMENT_SHADER                0x8B30
#define GL_VERTEX_SHADER                  0x8B31
#define GL_MAX_FRAGMENT_UNIFORM_COMPONENTS 0x8B49
#define GL_MAX_VERTEX_UNIFORM_COMPONENTS  0x8B4A
#define GL_MAX_VARYING_FLOATS             0x8B4B
#define GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS 0x8B4C
#define GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS 0x8B4D
#define GL_SHADER_TYPE                    0x8B4F
#define GL_FLOAT_VEC2                     0x8B50
#define GL_FLOAT_VEC3                     0x8B51
#define GL_FLOAT_VEC4                     0x8B52
#define GL_INT_VEC2                       0x8B53
#define GL_INT_VEC3                       0x8B54
#define GL_INT_VEC4                       0x8B55
#define GL_BOOL                           0x8B56
#define GL_BOOL_VEC2                      0x8B57
#define GL_BOOL_VEC3                      0x8B58
#define GL_BOOL_VEC4                      0x8B59
#define GL_FLOAT_MAT2                     0x8B5A
#define GL_FLOAT_MAT3                     0x8B5B
#define GL_FLOAT_MAT4                     0x8B5C
#define GL_SAMPLER_1D                     0x8B5D
#define GL_SAMPLER_2D                     0x8B5E
#define GL_SAMPLER_3D                     0x8B5F
#define GL_SAMPLER_CUBE                   0x8B60
#define GL_SAMPLER_1D_SHADOW              0x8B61
#define GL_SAMPLER_2D_SHADOW              0x8B62
#define GL_DELETE_STATUS                  0x8B80
#define GL_COMPILE_STATUS                 0x8B81
#define GL_LINK_STATUS                    0x8B82
#define GL_VALIDATE_STATUS                0x8B83
#define GL_INFO_LOG_LENGTH                0x8B84
#define GL_ATTACHED_SHADERS               0x8B85
#define GL_ACTIVE_UNIFORMS                0x8B86
#define GL_ACTIVE_UNIFORM_MAX_LENGTH      0x8B87
#define GL_SHADER_SOURCE_LENGTH           0x8B88
#define GL_ACTIVE_ATTRIBUTES              0x8B89
#define GL_ACTIVE_ATTRIBUTE_MAX_LENGTH    0x8B8A
#define GL_FRAGMENT_SHADER_DERIVATIVE_HINT 0x8B8B
#define GL_SHADING_LANGUAGE_VERSION       0x8B8C
#define GL_CURRENT_PROGRAM                0x8B8D
#define GL_POINT_SPRITE_COORD_ORIGIN      0x8CA0
#define GL_LOWER_LEFT                     0x8CA1
#define GL_UPPER_LEFT                     0x8CA2
#define GL_STENCIL_BACK_REF               0x8CA3
#define GL_STENCIL_BACK_VALUE_MASK        0x8CA4
#define GL_STENCIL_BACK_WRITEMASK         0x8CA5
typedef void (APIENTRYP PFNGLBLENDEQUATIONSEPARATEPROC) (GLenum modeRGB, GLenum modeAlpha);
typedef void (APIENTRYP PFNGLDRAWBUFFERSPROC) (GLsizei n, const GLenum *bufs);
typedef void (APIENTRYP PFNGLSTENCILOPSEPARATEPROC) (GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass);
typedef void (APIENTRYP PFNGLSTENCILFUNCSEPARATEPROC) (GLenum face, GLenum func, GLint ref, GLuint mask);
typedef void (APIENTRYP PFNGLSTENCILMASKSEPARATEPROC) (GLenum face, GLuint mask);
typedef void (APIENTRYP PFNGLATTACHSHADERPROC) (GLuint program, GLuint shader);
typedef void (APIENTRYP PFNGLBINDATTRIBLOCATIONPROC) (GLuint program, GLuint index, const GLchar *name);
typedef void (APIENTRYP PFNGLCOMPILESHADERPROC) (GLuint shader);
typedef GLuint (APIENTRYP PFNGLCREATEPROGRAMPROC) (void);
typedef GLuint (APIENTRYP PFNGLCREATESHADERPROC) (GLenum type);
typedef void (APIENTRYP PFNGLDELETEPROGRAMPROC) (GLuint program);
typedef void (APIENTRYP PFNGLDELETESHADERPROC) (GLuint shader);
typedef void (APIENTRYP PFNGLDETACHSHADERPROC) (GLuint program, GLuint shader);
typedef void (APIENTRYP PFNGLDISABLEVERTEXATTRIBARRAYPROC) (GLuint index);
typedef void (APIENTRYP PFNGLENABLEVERTEXATTRIBARRAYPROC) (GLuint index);
typedef void (APIENTRYP PFNGLGETACTIVEATTRIBPROC) (GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name);
typedef void (APIENTRYP PFNGLGETACTIVEUNIFORMPROC) (GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name);
typedef void (APIENTRYP PFNGLGETATTACHEDSHADERSPROC) (GLuint program, GLsizei maxCount, GLsizei *count, GLuint *shaders);
typedef GLint (APIENTRYP PFNGLGETATTRIBLOCATIONPROC) (GLuint program, const GLchar *name);
typedef void (APIENTRYP PFNGLGETPROGRAMIVPROC) (GLuint program, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLGETPROGRAMINFOLOGPROC) (GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
typedef void (APIENTRYP PFNGLGETSHADERIVPROC) (GLuint shader, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLGETSHADERINFOLOGPROC) (GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
typedef void (APIENTRYP PFNGLGETSHADERSOURCEPROC) (GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *source);
typedef GLint (APIENTRYP PFNGLGETUNIFORMLOCATIONPROC) (GLuint program, const GLchar *name);
typedef void (APIENTRYP PFNGLGETUNIFORMFVPROC) (GLuint program, GLint location, GLfloat *params);
typedef void (APIENTRYP PFNGLGETUNIFORMIVPROC) (GLuint program, GLint location, GLint *params);
typedef void (APIENTRYP PFNGLGETVERTEXATTRIBDVPROC) (GLuint index, GLenum pname, GLdouble *params);
typedef void (APIENTRYP PFNGLGETVERTEXATTRIBFVPROC) (GLuint index, GLenum pname, GLfloat *params);
typedef void (APIENTRYP PFNGLGETVERTEXATTRIBIVPROC) (GLuint index, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLGETVERTEXATTRIBPOINTERVPROC) (GLuint index, GLenum pname, void **pointer);
typedef GLboolean (APIENTRYP PFNGLISPROGRAMPROC) (GLuint program);
typedef GLboolean (APIENTRYP PFNGLISSHADERPROC) (GLuint shader);
typedef void (APIENTRYP PFNGLLINKPROGRAMPROC) (GLuint program);
typedef void (APIENTRYP PFNGLSHADERSOURCEPROC) (GLuint shader, GLsizei count, const GLchar *const*string, const GLint *length);
typedef void (APIENTRYP PFNGLUSEPROGRAMPROC) (GLuint program);
typedef void (APIENTRYP PFNGLUNIFORM1FPROC) (GLint location, GLfloat v0);
typedef void (APIENTRYP PFNGLUNIFORM2FPROC) (GLint location, GLfloat v0, GLfloat v1);
typedef void (APIENTRYP PFNGLUNIFORM3FPROC) (GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
typedef void (APIENTRYP PFNGLUNIFORM4FPROC) (GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
typedef void (APIENTRYP PFNGLUNIFORM1IPROC) (GLint location, GLint v0);
typedef void (APIENTRYP PFNGLUNIFORM2IPROC) (GLint location, GLint v0, GLint v1);
typedef void (APIENTRYP PFNGLUNIFORM3IPROC) (GLint location, GLint v0, GLint v1, GLint v2);
typedef void (APIENTRYP PFNGLUNIFORM4IPROC) (GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
typedef void (APIENTRYP PFNGLUNIFORM1FVPROC) (GLint location, GLsizei count, const GLfloat *value);
typedef void (APIENTRYP PFNGLUNIFORM2FVPROC) (GLint location, GLsizei count, const GLfloat *value);
typedef void (APIENTRYP PFNGLUNIFORM3FVPROC) (GLint location, GLsizei count, const GLfloat *value);
typedef void (APIENTRYP PFNGLUNIFORM4FVPROC) (GLint location, GLsizei count, const GLfloat *value);
typedef void (APIENTRYP PFNGLUNIFORM1IVPROC) (GLint location, GLsizei count, const GLint *value);
typedef void (APIENTRYP PFNGLUNIFORM2IVPROC) (GLint location, GLsizei count, const GLint *value);
typedef void (APIENTRYP PFNGLUNIFORM3IVPROC) (GLint location, GLsizei count, const GLint *value);
typedef void (APIENTRYP PFNGLUNIFORM4IVPROC) (GLint location, GLsizei count, const GLint *value);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX2FVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX3FVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX4FVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (APIENTRYP PFNGLVALIDATEPROGRAMPROC) (GLuint program);
typedef void (APIENTRYP PFNGLVERTEXATTRIB1DPROC) (GLuint index, GLdouble x);
typedef void (APIENTRYP PFNGLVERTEXATTRIB1DVPROC) (GLuint index, const GLdouble *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIB1FPROC) (GLuint index, GLfloat x);
typedef void (APIENTRYP PFNGLVERTEXATTRIB1FVPROC) (GLuint index, const GLfloat *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIB1SPROC) (GLuint index, GLshort x);
typedef void (APIENTRYP PFNGLVERTEXATTRIB1SVPROC) (GLuint index, const GLshort *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIB2DPROC) (GLuint index, GLdouble x, GLdouble y);
typedef void (APIENTRYP PFNGLVERTEXATTRIB2DVPROC) (GLuint index, const GLdouble *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIB2FPROC) (GLuint index, GLfloat x, GLfloat y);
typedef void (APIENTRYP PFNGLVERTEXATTRIB2FVPROC) (GLuint index, const GLfloat *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIB2SPROC) (GLuint index, GLshort x, GLshort y);
typedef void (APIENTRYP PFNGLVERTEXATTRIB2SVPROC) (GLuint index, const GLshort *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIB3DPROC) (GLuint index, GLdouble x, GLdouble y, GLdouble z);
typedef void (APIENTRYP PFNGLVERTEXATTRIB3DVPROC) (GLuint index, const GLdouble *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIB3FPROC) (GLuint index, GLfloat x, GLfloat y, GLfloat z);
typedef void (APIENTRYP PFNGLVERTEXATTRIB3FVPROC) (GLuint index, const GLfloat *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIB3SPROC) (GLuint index, GLshort x, GLshort y, GLshort z);
typedef void (APIENTRYP PFNGLVERTEXATTRIB3SVPROC) (GLuint index, const GLshort *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4NBVPROC) (GLuint index, const GLbyte *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4NIVPROC) (GLuint index, const GLint *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4NSVPROC) (GLuint index, const GLshort *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4NUBPROC) (GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4NUBVPROC) (GLuint index, const GLubyte *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4NUIVPROC) (GLuint index, const GLuint *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4NUSVPROC) (GLuint index, const GLushort *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4BVPROC) (GLuint index, const GLbyte *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4DPROC) (GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4DVPROC) (GLuint index, const GLdouble *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4FPROC) (GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4FVPROC) (GLuint index, const GLfloat *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4IVPROC) (GLuint index, const GLint *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4SPROC) (GLuint index, GLshort x, GLshort y, GLshort z, GLshort w);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4SVPROC) (GLuint index, const GLshort *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4UBVPROC) (GLuint index, const GLubyte *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4UIVPROC) (GLuint index, const GLuint *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4USVPROC) (GLuint index, const GLushort *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIBPOINTERPROC) (GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer);
#endif /* OPENGL_VERSION_2_0 */



#ifndef OPENGL_VERSION_2_1
#define OPENGL_VERSION_2_1 1
#define GL_PIXEL_PACK_BUFFER              0x88EB
#define GL_PIXEL_UNPACK_BUFFER            0x88EC
#define GL_PIXEL_PACK_BUFFER_BINDING      0x88ED
#define GL_PIXEL_UNPACK_BUFFER_BINDING    0x88EF
#define GL_FLOAT_MAT2x3                   0x8B65
#define GL_FLOAT_MAT2x4                   0x8B66
#define GL_FLOAT_MAT3x2                   0x8B67
#define GL_FLOAT_MAT3x4                   0x8B68
#define GL_FLOAT_MAT4x2                   0x8B69
#define GL_FLOAT_MAT4x3                   0x8B6A
#define GL_SRGB                           0x8C40
#define GL_SRGB8                          0x8C41
#define GL_SRGB_ALPHA                     0x8C42
#define GL_SRGB8_ALPHA8                   0x8C43
#define GL_COMPRESSED_SRGB                0x8C48
#define GL_COMPRESSED_SRGB_ALPHA          0x8C49
typedef void (APIENTRYP PFNGLUNIFORMMATRIX2X3FVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX3X2FVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX2X4FVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX4X2FVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX3X4FVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX4X3FVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
#endif /* OPENGL_VERSION_2_1 */


#ifndef OPENGL_VERSION_3_0
#define OPENGL_VERSION_3_0 1
typedef khronos_uint16_t GLhalf;
#define GL_COMPARE_REF_TO_TEXTURE         0x884E
#define GL_CLIP_DISTANCE0                 0x3000
#define GL_CLIP_DISTANCE1                 0x3001
#define GL_CLIP_DISTANCE2                 0x3002
#define GL_CLIP_DISTANCE3                 0x3003
#define GL_CLIP_DISTANCE4                 0x3004
#define GL_CLIP_DISTANCE5                 0x3005
#define GL_CLIP_DISTANCE6                 0x3006
#define GL_CLIP_DISTANCE7                 0x3007
#define GL_MAX_CLIP_DISTANCES             0x0D32
#define GL_MAJOR_VERSION                  0x821B
#define GL_MINOR_VERSION                  0x821C
#define GL_NUM_EXTENSIONS                 0x821D
#define GL_CONTEXT_FLAGS                  0x821E
#define GL_COMPRESSED_RED                 0x8225
#define GL_COMPRESSED_RG                  0x8226
#define GL_CONTEXT_FLAG_FORWARD_COMPATIBLE_BIT 0x00000001
#define GL_RGBA32F                        0x8814
#define GL_RGB32F                         0x8815
#define GL_RGBA16F                        0x881A
#define GL_RGB16F                         0x881B
#define GL_VERTEX_ATTRIB_ARRAY_INTEGER    0x88FD
#define GL_MAX_ARRAY_TEXTURE_LAYERS       0x88FF
#define GL_MIN_PROGRAM_TEXEL_OFFSET       0x8904
#define GL_MAX_PROGRAM_TEXEL_OFFSET       0x8905
#define GL_CLAMP_READ_COLOR               0x891C
#define GL_FIXED_ONLY                     0x891D
#define GL_MAX_VARYING_COMPONENTS         0x8B4B
#define GL_TEXTURE_1D_ARRAY               0x8C18
#define GL_PROXY_TEXTURE_1D_ARRAY         0x8C19
#define GL_TEXTURE_2D_ARRAY               0x8C1A
#define GL_PROXY_TEXTURE_2D_ARRAY         0x8C1B
#define GL_TEXTURE_BINDING_1D_ARRAY       0x8C1C
#define GL_TEXTURE_BINDING_2D_ARRAY       0x8C1D
#define GL_R11F_G11F_B10F                 0x8C3A
#define GL_UNSIGNED_INT_10F_11F_11F_REV   0x8C3B
#define GL_RGB9_E5                        0x8C3D
#define GL_UNSIGNED_INT_5_9_9_9_REV       0x8C3E
#define GL_TEXTURE_SHARED_SIZE            0x8C3F
#define GL_TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH 0x8C76
#define GL_TRANSFORM_FEEDBACK_BUFFER_MODE 0x8C7F
#define GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_COMPONENTS 0x8C80
#define GL_TRANSFORM_FEEDBACK_VARYINGS    0x8C83
#define GL_TRANSFORM_FEEDBACK_BUFFER_START 0x8C84
#define GL_TRANSFORM_FEEDBACK_BUFFER_SIZE 0x8C85
#define GL_PRIMITIVES_GENERATED           0x8C87
#define GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN 0x8C88
#define GL_RASTERIZER_DISCARD             0x8C89
#define GL_MAX_TRANSFORM_FEEDBACK_INTERLEAVED_COMPONENTS 0x8C8A
#define GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_ATTRIBS 0x8C8B
#define GL_INTERLEAVED_ATTRIBS            0x8C8C
#define GL_SEPARATE_ATTRIBS               0x8C8D
#define GL_TRANSFORM_FEEDBACK_BUFFER      0x8C8E
#define GL_TRANSFORM_FEEDBACK_BUFFER_BINDING 0x8C8F
#define GL_RGBA32UI                       0x8D70
#define GL_RGB32UI                        0x8D71
#define GL_RGBA16UI                       0x8D76
#define GL_RGB16UI                        0x8D77
#define GL_RGBA8UI                        0x8D7C
#define GL_RGB8UI                         0x8D7D
#define GL_RGBA32I                        0x8D82
#define GL_RGB32I                         0x8D83
#define GL_RGBA16I                        0x8D88
#define GL_RGB16I                         0x8D89
#define GL_RGBA8I                         0x8D8E
#define GL_RGB8I                          0x8D8F
#define GL_RED_INTEGER                    0x8D94
#define GL_GREEN_INTEGER                  0x8D95
#define GL_BLUE_INTEGER                   0x8D96
#define GL_RGB_INTEGER                    0x8D98
#define GL_RGBA_INTEGER                   0x8D99
#define GL_BGR_INTEGER                    0x8D9A
#define GL_BGRA_INTEGER                   0x8D9B
#define GL_SAMPLER_1D_ARRAY               0x8DC0
#define GL_SAMPLER_2D_ARRAY               0x8DC1
#define GL_SAMPLER_1D_ARRAY_SHADOW        0x8DC3
#define GL_SAMPLER_2D_ARRAY_SHADOW        0x8DC4
#define GL_SAMPLER_CUBE_SHADOW            0x8DC5
#define GL_UNSIGNED_INT_VEC2              0x8DC6
#define GL_UNSIGNED_INT_VEC3              0x8DC7
#define GL_UNSIGNED_INT_VEC4              0x8DC8
#define GL_INT_SAMPLER_1D                 0x8DC9
#define GL_INT_SAMPLER_2D                 0x8DCA
#define GL_INT_SAMPLER_3D                 0x8DCB
#define GL_INT_SAMPLER_CUBE               0x8DCC
#define GL_INT_SAMPLER_1D_ARRAY           0x8DCE
#define GL_INT_SAMPLER_2D_ARRAY           0x8DCF
#define GL_UNSIGNED_INT_SAMPLER_1D        0x8DD1
#define GL_UNSIGNED_INT_SAMPLER_2D        0x8DD2
#define GL_UNSIGNED_INT_SAMPLER_3D        0x8DD3
#define GL_UNSIGNED_INT_SAMPLER_CUBE      0x8DD4
#define GL_UNSIGNED_INT_SAMPLER_1D_ARRAY  0x8DD6
#define GL_UNSIGNED_INT_SAMPLER_2D_ARRAY  0x8DD7
#define GL_QUERY_WAIT                     0x8E13
#define GL_QUERY_NO_WAIT                  0x8E14
#define GL_QUERY_BY_REGION_WAIT           0x8E15
#define GL_QUERY_BY_REGION_NO_WAIT        0x8E16
#define GL_BUFFER_ACCESS_FLAGS            0x911F
#define GL_BUFFER_MAP_LENGTH              0x9120
#define GL_BUFFER_MAP_OFFSET              0x9121
#define GL_DEPTH_COMPONENT32F             0x8CAC
#define GL_DEPTH32F_STENCIL8              0x8CAD
#define GL_FLOAT_32_UNSIGNED_INT_24_8_REV 0x8DAD
#define GL_INVALID_FRAMEBUFFER_OPERATION  0x0506
#define GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING 0x8210
#define GL_FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE 0x8211
#define GL_FRAMEBUFFER_ATTACHMENT_RED_SIZE 0x8212
#define GL_FRAMEBUFFER_ATTACHMENT_GREEN_SIZE 0x8213
#define GL_FRAMEBUFFER_ATTACHMENT_BLUE_SIZE 0x8214
#define GL_FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE 0x8215
#define GL_FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE 0x8216
#define GL_FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE 0x8217
#define GL_FRAMEBUFFER_DEFAULT            0x8218
#define GL_FRAMEBUFFER_UNDEFINED          0x8219
#define GL_DEPTH_STENCIL_ATTACHMENT       0x821A
#define GL_MAX_RENDERBUFFER_SIZE          0x84E8
#define GL_DEPTH_STENCIL                  0x84F9
#define GL_UNSIGNED_INT_24_8              0x84FA
#define GL_DEPTH24_STENCIL8               0x88F0
#define GL_TEXTURE_STENCIL_SIZE           0x88F1
#define GL_TEXTURE_RED_TYPE               0x8C10
#define GL_TEXTURE_GREEN_TYPE             0x8C11
#define GL_TEXTURE_BLUE_TYPE              0x8C12
#define GL_TEXTURE_ALPHA_TYPE             0x8C13
#define GL_TEXTURE_DEPTH_TYPE             0x8C16
#define GL_UNSIGNED_NORMALIZED            0x8C17
#define GL_FRAMEBUFFER_BINDING            0x8CA6
#define GL_DRAW_FRAMEBUFFER_BINDING       0x8CA6
#define GL_RENDERBUFFER_BINDING           0x8CA7
#define GL_READ_FRAMEBUFFER               0x8CA8
#define GL_DRAW_FRAMEBUFFER               0x8CA9
#define GL_READ_FRAMEBUFFER_BINDING       0x8CAA
#define GL_RENDERBUFFER_SAMPLES           0x8CAB
#define GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE 0x8CD0
#define GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME 0x8CD1
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL 0x8CD2
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE 0x8CD3
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER 0x8CD4
#define GL_FRAMEBUFFER_COMPLETE           0x8CD5
#define GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT 0x8CD6
#define GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT 0x8CD7
#define GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER 0x8CDB
#define GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER 0x8CDC
#define GL_FRAMEBUFFER_UNSUPPORTED        0x8CDD
#define GL_MAX_COLOR_ATTACHMENTS          0x8CDF
#define GL_COLOR_ATTACHMENT0              0x8CE0
#define GL_COLOR_ATTACHMENT1              0x8CE1
#define GL_COLOR_ATTACHMENT2              0x8CE2
#define GL_COLOR_ATTACHMENT3              0x8CE3
#define GL_COLOR_ATTACHMENT4              0x8CE4
#define GL_COLOR_ATTACHMENT5              0x8CE5
#define GL_COLOR_ATTACHMENT6              0x8CE6
#define GL_COLOR_ATTACHMENT7              0x8CE7
#define GL_COLOR_ATTACHMENT8              0x8CE8
#define GL_COLOR_ATTACHMENT9              0x8CE9
#define GL_COLOR_ATTACHMENT10             0x8CEA
#define GL_COLOR_ATTACHMENT11             0x8CEB
#define GL_COLOR_ATTACHMENT12             0x8CEC
#define GL_COLOR_ATTACHMENT13             0x8CED
#define GL_COLOR_ATTACHMENT14             0x8CEE
#define GL_COLOR_ATTACHMENT15             0x8CEF
#define GL_COLOR_ATTACHMENT16             0x8CF0
#define GL_COLOR_ATTACHMENT17             0x8CF1
#define GL_COLOR_ATTACHMENT18             0x8CF2
#define GL_COLOR_ATTACHMENT19             0x8CF3
#define GL_COLOR_ATTACHMENT20             0x8CF4
#define GL_COLOR_ATTACHMENT21             0x8CF5
#define GL_COLOR_ATTACHMENT22             0x8CF6
#define GL_COLOR_ATTACHMENT23             0x8CF7
#define GL_COLOR_ATTACHMENT24             0x8CF8
#define GL_COLOR_ATTACHMENT25             0x8CF9
#define GL_COLOR_ATTACHMENT26             0x8CFA
#define GL_COLOR_ATTACHMENT27             0x8CFB
#define GL_COLOR_ATTACHMENT28             0x8CFC
#define GL_COLOR_ATTACHMENT29             0x8CFD
#define GL_COLOR_ATTACHMENT30             0x8CFE
#define GL_COLOR_ATTACHMENT31             0x8CFF
#define GL_DEPTH_ATTACHMENT               0x8D00
#define GL_STENCIL_ATTACHMENT             0x8D20
#define GL_FRAMEBUFFER                    0x8D40
#define GL_RENDERBUFFER                   0x8D41
#define GL_RENDERBUFFER_WIDTH             0x8D42
#define GL_RENDERBUFFER_HEIGHT            0x8D43
#define GL_RENDERBUFFER_INTERNAL_FORMAT   0x8D44
#define GL_STENCIL_INDEX1                 0x8D46
#define GL_STENCIL_INDEX4                 0x8D47
#define GL_STENCIL_INDEX8                 0x8D48
#define GL_STENCIL_INDEX16                0x8D49
#define GL_RENDERBUFFER_RED_SIZE          0x8D50
#define GL_RENDERBUFFER_GREEN_SIZE        0x8D51
#define GL_RENDERBUFFER_BLUE_SIZE         0x8D52
#define GL_RENDERBUFFER_ALPHA_SIZE        0x8D53
#define GL_RENDERBUFFER_DEPTH_SIZE        0x8D54
#define GL_RENDERBUFFER_STENCIL_SIZE      0x8D55
#define GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE 0x8D56
#define GL_MAX_SAMPLES                    0x8D57
#define GL_FRAMEBUFFER_SRGB               0x8DB9
#define GL_HALF_FLOAT                     0x140B
#define GL_MAP_READ_BIT                   0x0001
#define GL_MAP_WRITE_BIT                  0x0002
#define GL_MAP_INVALIDATE_RANGE_BIT       0x0004
#define GL_MAP_INVALIDATE_BUFFER_BIT      0x0008
#define GL_MAP_FLUSH_EXPLICIT_BIT         0x0010
#define GL_MAP_UNSYNCHRONIZED_BIT         0x0020
#define GL_COMPRESSED_RED_RGTC1           0x8DBB
#define GL_COMPRESSED_SIGNED_RED_RGTC1    0x8DBC
#define GL_COMPRESSED_RG_RGTC2            0x8DBD
#define GL_COMPRESSED_SIGNED_RG_RGTC2     0x8DBE
#define GL_RG                             0x8227
#define GL_RG_INTEGER                     0x8228
#define GL_R8                             0x8229
#define GL_R16                            0x822A
#define GL_RG8                            0x822B
#define GL_RG16                           0x822C
#define GL_R16F                           0x822D
#define GL_R32F                           0x822E
#define GL_RG16F                          0x822F
#define GL_RG32F                          0x8230
#define GL_R8I                            0x8231
#define GL_R8UI                           0x8232
#define GL_R16I                           0x8233
#define GL_R16UI                          0x8234
#define GL_R32I                           0x8235
#define GL_R32UI                          0x8236
#define GL_RG8I                           0x8237
#define GL_RG8UI                          0x8238
#define GL_RG16I                          0x8239
#define GL_RG16UI                         0x823A
#define GL_RG32I                          0x823B
#define GL_RG32UI                         0x823C
#define GL_VERTEX_ARRAY_BINDING           0x85B5
typedef void (APIENTRYP PFNGLCOLORMASKIPROC) (GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a);
typedef void (APIENTRYP PFNGLGETBOOLEANI_VPROC) (GLenum target, GLuint index, GLboolean *data);
typedef void (APIENTRYP PFNGLGETINTEGERI_VPROC) (GLenum target, GLuint index, GLint *data);
typedef void (APIENTRYP PFNGLENABLEIPROC) (GLenum target, GLuint index);
typedef void (APIENTRYP PFNGLDISABLEIPROC) (GLenum target, GLuint index);
typedef GLboolean (APIENTRYP PFNGLISENABLEDIPROC) (GLenum target, GLuint index);
typedef void (APIENTRYP PFNGLBEGINTRANSFORMFEEDBACKPROC) (GLenum primitiveMode);
typedef void (APIENTRYP PFNGLENDTRANSFORMFEEDBACKPROC) (void);
typedef void (APIENTRYP PFNGLBINDBUFFERRANGEPROC) (GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size);
typedef void (APIENTRYP PFNGLBINDBUFFERBASEPROC) (GLenum target, GLuint index, GLuint buffer);
typedef void (APIENTRYP PFNGLTRANSFORMFEEDBACKVARYINGSPROC) (GLuint program, GLsizei count, const GLchar *const*varyings, GLenum bufferMode);
typedef void (APIENTRYP PFNGLGETTRANSFORMFEEDBACKVARYINGPROC) (GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLsizei *size, GLenum *type, GLchar *name);
typedef void (APIENTRYP PFNGLCLAMPCOLORPROC) (GLenum target, GLenum clamp);
typedef void (APIENTRYP PFNGLBEGINCONDITIONALRENDERPROC) (GLuint id, GLenum mode);
typedef void (APIENTRYP PFNGLENDCONDITIONALRENDERPROC) (void);
typedef void (APIENTRYP PFNGLVERTEXATTRIBIPOINTERPROC) (GLuint index, GLint size, GLenum type, GLsizei stride, const void *pointer);
typedef void (APIENTRYP PFNGLGETVERTEXATTRIBIIVPROC) (GLuint index, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLGETVERTEXATTRIBIUIVPROC) (GLuint index, GLenum pname, GLuint *params);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI1IPROC) (GLuint index, GLint x);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI2IPROC) (GLuint index, GLint x, GLint y);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI3IPROC) (GLuint index, GLint x, GLint y, GLint z);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI4IPROC) (GLuint index, GLint x, GLint y, GLint z, GLint w);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI1UIPROC) (GLuint index, GLuint x);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI2UIPROC) (GLuint index, GLuint x, GLuint y);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI3UIPROC) (GLuint index, GLuint x, GLuint y, GLuint z);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI4UIPROC) (GLuint index, GLuint x, GLuint y, GLuint z, GLuint w);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI1IVPROC) (GLuint index, const GLint *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI2IVPROC) (GLuint index, const GLint *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI3IVPROC) (GLuint index, const GLint *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI4IVPROC) (GLuint index, const GLint *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI1UIVPROC) (GLuint index, const GLuint *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI2UIVPROC) (GLuint index, const GLuint *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI3UIVPROC) (GLuint index, const GLuint *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI4UIVPROC) (GLuint index, const GLuint *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI4BVPROC) (GLuint index, const GLbyte *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI4SVPROC) (GLuint index, const GLshort *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI4UBVPROC) (GLuint index, const GLubyte *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI4USVPROC) (GLuint index, const GLushort *v);
typedef void (APIENTRYP PFNGLGETUNIFORMUIVPROC) (GLuint program, GLint location, GLuint *params);
typedef void (APIENTRYP PFNGLBINDFRAGDATALOCATIONPROC) (GLuint program, GLuint color, const GLchar *name);
typedef GLint (APIENTRYP PFNGLGETFRAGDATALOCATIONPROC) (GLuint program, const GLchar *name);
typedef void (APIENTRYP PFNGLUNIFORM1UIPROC) (GLint location, GLuint v0);
typedef void (APIENTRYP PFNGLUNIFORM2UIPROC) (GLint location, GLuint v0, GLuint v1);
typedef void (APIENTRYP PFNGLUNIFORM3UIPROC) (GLint location, GLuint v0, GLuint v1, GLuint v2);
typedef void (APIENTRYP PFNGLUNIFORM4UIPROC) (GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
typedef void (APIENTRYP PFNGLUNIFORM1UIVPROC) (GLint location, GLsizei count, const GLuint *value);
typedef void (APIENTRYP PFNGLUNIFORM2UIVPROC) (GLint location, GLsizei count, const GLuint *value);
typedef void (APIENTRYP PFNGLUNIFORM3UIVPROC) (GLint location, GLsizei count, const GLuint *value);
typedef void (APIENTRYP PFNGLUNIFORM4UIVPROC) (GLint location, GLsizei count, const GLuint *value);
typedef void (APIENTRYP PFNGLTEXPARAMETERIIVPROC) (GLenum target, GLenum pname, const GLint *params);
typedef void (APIENTRYP PFNGLTEXPARAMETERIUIVPROC) (GLenum target, GLenum pname, const GLuint *params);
typedef void (APIENTRYP PFNGLGETTEXPARAMETERIIVPROC) (GLenum target, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLGETTEXPARAMETERIUIVPROC) (GLenum target, GLenum pname, GLuint *params);
typedef void (APIENTRYP PFNGLCLEARBUFFERIVPROC) (GLenum buffer, GLint drawbuffer, const GLint *value);
typedef void (APIENTRYP PFNGLCLEARBUFFERUIVPROC) (GLenum buffer, GLint drawbuffer, const GLuint *value);
typedef void (APIENTRYP PFNGLCLEARBUFFERFVPROC) (GLenum buffer, GLint drawbuffer, const GLfloat *value);
typedef void (APIENTRYP PFNGLCLEARBUFFERFIPROC) (GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil);
typedef const GLubyte *(APIENTRYP PFNGLGETSTRINGIPROC) (GLenum name, GLuint index);
typedef GLboolean (APIENTRYP PFNGLISRENDERBUFFERPROC) (GLuint renderbuffer);
typedef void (APIENTRYP PFNGLBINDRENDERBUFFERPROC) (GLenum target, GLuint renderbuffer);
typedef void (APIENTRYP PFNGLDELETERENDERBUFFERSPROC) (GLsizei n, const GLuint *renderbuffers);
typedef void (APIENTRYP PFNGLGENRENDERBUFFERSPROC) (GLsizei n, GLuint *renderbuffers);
typedef void (APIENTRYP PFNGLRENDERBUFFERSTORAGEPROC) (GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (APIENTRYP PFNGLGETRENDERBUFFERPARAMETERIVPROC) (GLenum target, GLenum pname, GLint *params);
typedef GLboolean (APIENTRYP PFNGLISFRAMEBUFFERPROC) (GLuint framebuffer);
typedef void (APIENTRYP PFNGLBINDFRAMEBUFFERPROC) (GLenum target, GLuint framebuffer);
typedef void (APIENTRYP PFNGLDELETEFRAMEBUFFERSPROC) (GLsizei n, const GLuint *framebuffers);
typedef void (APIENTRYP PFNGLGENFRAMEBUFFERSPROC) (GLsizei n, GLuint *framebuffers);
typedef GLenum (APIENTRYP PFNGLCHECKFRAMEBUFFERSTATUSPROC) (GLenum target);
typedef void (APIENTRYP PFNGLFRAMEBUFFERTEXTURE1DPROC) (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
typedef void (APIENTRYP PFNGLFRAMEBUFFERTEXTURE2DPROC) (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
typedef void (APIENTRYP PFNGLFRAMEBUFFERTEXTURE3DPROC) (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset);
typedef void (APIENTRYP PFNGLFRAMEBUFFERRENDERBUFFERPROC) (GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
typedef void (APIENTRYP PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC) (GLenum target, GLenum attachment, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLGENERATEMIPMAPPROC) (GLenum target);
typedef void (APIENTRYP PFNGLBLITFRAMEBUFFERPROC) (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter);
typedef void (APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (APIENTRYP PFNGLFRAMEBUFFERTEXTURELAYERPROC) (GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer);
typedef void *(APIENTRYP PFNGLMAPBUFFERRANGEPROC) (GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access);
typedef void (APIENTRYP PFNGLFLUSHMAPPEDBUFFERRANGEPROC) (GLenum target, GLintptr offset, GLsizeiptr length);
typedef void (APIENTRYP PFNGLBINDVERTEXARRAYPROC) (GLuint array);
typedef void (APIENTRYP PFNGLDELETEVERTEXARRAYSPROC) (GLsizei n, const GLuint *arrays);
typedef void (APIENTRYP PFNGLGENVERTEXARRAYSPROC) (GLsizei n, GLuint *arrays);
typedef GLboolean (APIENTRYP PFNGLISVERTEXARRAYPROC) (GLuint array);
#endif /* OPENGL_VERSION_3_0 */

#ifndef OPENGL_VERSION_3_1
#define OPENGL_VERSION_3_1 1
#define GL_SAMPLER_2D_RECT                0x8B63
#define GL_SAMPLER_2D_RECT_SHADOW         0x8B64
#define GL_SAMPLER_BUFFER                 0x8DC2
#define GL_INT_SAMPLER_2D_RECT            0x8DCD
#define GL_INT_SAMPLER_BUFFER             0x8DD0
#define GL_UNSIGNED_INT_SAMPLER_2D_RECT   0x8DD5
#define GL_UNSIGNED_INT_SAMPLER_BUFFER    0x8DD8
#define GL_TEXTURE_BUFFER                 0x8C2A
#define GL_MAX_TEXTURE_BUFFER_SIZE        0x8C2B
#define GL_TEXTURE_BINDING_BUFFER         0x8C2C
#define GL_TEXTURE_BUFFER_DATA_STORE_BINDING 0x8C2D
#define GL_TEXTURE_RECTANGLE              0x84F5
#define GL_TEXTURE_BINDING_RECTANGLE      0x84F6
#define GL_PROXY_TEXTURE_RECTANGLE        0x84F7
#define GL_MAX_RECTANGLE_TEXTURE_SIZE     0x84F8
#define GL_R8_SNORM                       0x8F94
#define GL_RG8_SNORM                      0x8F95
#define GL_RGB8_SNORM                     0x8F96
#define GL_RGBA8_SNORM                    0x8F97
#define GL_R16_SNORM                      0x8F98
#define GL_RG16_SNORM                     0x8F99
#define GL_RGB16_SNORM                    0x8F9A
#define GL_RGBA16_SNORM                   0x8F9B
#define GL_SIGNED_NORMALIZED              0x8F9C
#define GL_PRIMITIVE_RESTART              0x8F9D
#define GL_PRIMITIVE_RESTART_INDEX        0x8F9E
#define GL_COPY_READ_BUFFER               0x8F36
#define GL_COPY_WRITE_BUFFER              0x8F37
#define GL_UNIFORM_BUFFER                 0x8A11
#define GL_UNIFORM_BUFFER_BINDING         0x8A28
#define GL_UNIFORM_BUFFER_START           0x8A29
#define GL_UNIFORM_BUFFER_SIZE            0x8A2A
#define GL_MAX_VERTEX_UNIFORM_BLOCKS      0x8A2B
#define GL_MAX_GEOMETRY_UNIFORM_BLOCKS    0x8A2C
#define GL_MAX_FRAGMENT_UNIFORM_BLOCKS    0x8A2D
#define GL_MAX_COMBINED_UNIFORM_BLOCKS    0x8A2E
#define GL_MAX_UNIFORM_BUFFER_BINDINGS    0x8A2F
#define GL_MAX_UNIFORM_BLOCK_SIZE         0x8A30
#define GL_MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS 0x8A31
#define GL_MAX_COMBINED_GEOMETRY_UNIFORM_COMPONENTS 0x8A32
#define GL_MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS 0x8A33
#define GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT 0x8A34
#define GL_ACTIVE_UNIFORM_BLOCK_MAX_NAME_LENGTH 0x8A35
#define GL_ACTIVE_UNIFORM_BLOCKS          0x8A36
#define GL_UNIFORM_TYPE                   0x8A37
#define GL_UNIFORM_SIZE                   0x8A38
#define GL_UNIFORM_NAME_LENGTH            0x8A39
#define GL_UNIFORM_BLOCK_INDEX            0x8A3A
#define GL_UNIFORM_OFFSET                 0x8A3B
#define GL_UNIFORM_ARRAY_STRIDE           0x8A3C
#define GL_UNIFORM_MATRIX_STRIDE          0x8A3D
#define GL_UNIFORM_IS_ROW_MAJOR           0x8A3E
#define GL_UNIFORM_BLOCK_BINDING          0x8A3F
#define GL_UNIFORM_BLOCK_DATA_SIZE        0x8A40
#define GL_UNIFORM_BLOCK_NAME_LENGTH      0x8A41
#define GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS  0x8A42
#define GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES 0x8A43
#define GL_UNIFORM_BLOCK_REFERENCED_BY_VERTEX_SHADER 0x8A44
#define GL_UNIFORM_BLOCK_REFERENCED_BY_GEOMETRY_SHADER 0x8A45
#define GL_UNIFORM_BLOCK_REFERENCED_BY_FRAGMENT_SHADER 0x8A46
#define GL_INVALID_INDEX                  0xFFFFFFFFu
typedef void (APIENTRYP PFNGLDRAWARRAYSINSTANCEDPROC) (GLenum mode, GLint first, GLsizei count, GLsizei instancecount);
typedef void (APIENTRYP PFNGLDRAWELEMENTSINSTANCEDPROC) (GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei instancecount);
typedef void (APIENTRYP PFNGLTEXBUFFERPROC) (GLenum target, GLenum internalformat, GLuint buffer);
typedef void (APIENTRYP PFNGLPRIMITIVERESTARTINDEXPROC) (GLuint index);
typedef void (APIENTRYP PFNGLCOPYBUFFERSUBDATAPROC) (GLenum readTarget, GLenum writeTarget, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size);
typedef void (APIENTRYP PFNGLGETUNIFORMINDICESPROC) (GLuint program, GLsizei uniformCount, const GLchar *const*uniformNames, GLuint *uniformIndices);
typedef void (APIENTRYP PFNGLGETACTIVEUNIFORMSIVPROC) (GLuint program, GLsizei uniformCount, const GLuint *uniformIndices, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLGETACTIVEUNIFORMNAMEPROC) (GLuint program, GLuint uniformIndex, GLsizei bufSize, GLsizei *length, GLchar *uniformName);
typedef GLuint (APIENTRYP PFNGLGETUNIFORMBLOCKINDEXPROC) (GLuint program, const GLchar *uniformBlockName);
typedef void (APIENTRYP PFNGLGETACTIVEUNIFORMBLOCKIVPROC) (GLuint program, GLuint uniformBlockIndex, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC) (GLuint program, GLuint uniformBlockIndex, GLsizei bufSize, GLsizei *length, GLchar *uniformBlockName);
typedef void (APIENTRYP PFNGLUNIFORMBLOCKBINDINGPROC) (GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding);
#endif /* OPENGL_VERSION_3_1 */


#ifndef OPENGL_VERSION_3_2
#define OPENGL_VERSION_3_2 1
typedef struct __GLsync *GLsync;
typedef khronos_uint64_t GLuint64;
typedef khronos_int64_t GLint64;
#define GL_CONTEXT_CORE_PROFILE_BIT       0x00000001
#define GL_CONTEXT_COMPATIBILITY_PROFILE_BIT 0x00000002
#define GL_LINES_ADJACENCY                0x000A
#define GL_LINE_STRIP_ADJACENCY           0x000B
#define GL_TRIANGLES_ADJACENCY            0x000C
#define GL_TRIANGLE_STRIP_ADJACENCY       0x000D
#define GL_PROGRAM_POINT_SIZE             0x8642
#define GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS 0x8C29
#define GL_FRAMEBUFFER_ATTACHMENT_LAYERED 0x8DA7
#define GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS 0x8DA8
#define GL_GEOMETRY_SHADER                0x8DD9
#define GL_GEOMETRY_VERTICES_OUT          0x8916
#define GL_GEOMETRY_INPUT_TYPE            0x8917
#define GL_GEOMETRY_OUTPUT_TYPE           0x8918
#define GL_MAX_GEOMETRY_UNIFORM_COMPONENTS 0x8DDF
#define GL_MAX_GEOMETRY_OUTPUT_VERTICES   0x8DE0
#define GL_MAX_GEOMETRY_TOTAL_OUTPUT_COMPONENTS 0x8DE1
#define GL_MAX_VERTEX_OUTPUT_COMPONENTS   0x9122
#define GL_MAX_GEOMETRY_INPUT_COMPONENTS  0x9123
#define GL_MAX_GEOMETRY_OUTPUT_COMPONENTS 0x9124
#define GL_MAX_FRAGMENT_INPUT_COMPONENTS  0x9125
#define GL_CONTEXT_PROFILE_MASK           0x9126
#define GL_DEPTH_CLAMP                    0x864F
#define GL_QUADS_FOLLOW_PROVOKING_VERTEX_CONVENTION 0x8E4C
#define GL_FIRST_VERTEX_CONVENTION        0x8E4D
#define GL_LAST_VERTEX_CONVENTION         0x8E4E
#define GL_PROVOKING_VERTEX               0x8E4F
#define GL_TEXTURE_CUBE_MAP_SEAMLESS      0x884F
#define GL_MAX_SERVER_WAIT_TIMEOUT        0x9111
#define GL_OBJECT_TYPE                    0x9112
#define GL_SYNC_CONDITION                 0x9113
#define GL_SYNC_STATUS                    0x9114
#define GL_SYNC_FLAGS                     0x9115
#define GL_SYNC_FENCE                     0x9116
#define GL_SYNC_GPU_COMMANDS_COMPLETE     0x9117
#define GL_UNSIGNALED                     0x9118
#define GL_SIGNALED                       0x9119
#define GL_ALREADY_SIGNALED               0x911A
#define GL_TIMEOUT_EXPIRED                0x911B
#define GL_CONDITION_SATISFIED            0x911C
#define GL_WAIT_FAILED                    0x911D
#define GL_TIMEOUT_IGNORED                0xFFFFFFFFFFFFFFFFull
#define GL_SYNC_FLUSH_COMMANDS_BIT        0x00000001
#define GL_SAMPLE_POSITION                0x8E50
#define GL_SAMPLE_MASK                    0x8E51
#define GL_SAMPLE_MASK_VALUE              0x8E52
#define GL_MAX_SAMPLE_MASK_WORDS          0x8E59
#define GL_TEXTURE_2D_MULTISAMPLE         0x9100
#define GL_PROXY_TEXTURE_2D_MULTISAMPLE   0x9101
#define GL_TEXTURE_2D_MULTISAMPLE_ARRAY   0x9102
#define GL_PROXY_TEXTURE_2D_MULTISAMPLE_ARRAY 0x9103
#define GL_TEXTURE_BINDING_2D_MULTISAMPLE 0x9104
#define GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY 0x9105
#define GL_TEXTURE_SAMPLES                0x9106
#define GL_TEXTURE_FIXED_SAMPLE_LOCATIONS 0x9107
#define GL_SAMPLER_2D_MULTISAMPLE         0x9108
#define GL_INT_SAMPLER_2D_MULTISAMPLE     0x9109
#define GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE 0x910A
#define GL_SAMPLER_2D_MULTISAMPLE_ARRAY   0x910B
#define GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY 0x910C
#define GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY 0x910D
#define GL_MAX_COLOR_TEXTURE_SAMPLES      0x910E
#define GL_MAX_DEPTH_TEXTURE_SAMPLES      0x910F
#define GL_MAX_INTEGER_SAMPLES            0x9110
typedef void (APIENTRYP PFNGLDRAWELEMENTSBASEVERTEXPROC) (GLenum mode, GLsizei count, GLenum type, const void *indices, GLint basevertex);
typedef void (APIENTRYP PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC) (GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void *indices, GLint basevertex);
typedef void (APIENTRYP PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC) (GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei instancecount, GLint basevertex);
typedef void (APIENTRYP PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC) (GLenum mode, const GLsizei *count, GLenum type, const void *const*indices, GLsizei drawcount, const GLint *basevertex);
typedef void (APIENTRYP PFNGLPROVOKINGVERTEXPROC) (GLenum mode);
typedef GLsync (APIENTRYP PFNGLFENCESYNCPROC) (GLenum condition, GLbitfield flags);
typedef GLboolean (APIENTRYP PFNGLISSYNCPROC) (GLsync sync);
typedef void (APIENTRYP PFNGLDELETESYNCPROC) (GLsync sync);
typedef GLenum (APIENTRYP PFNGLCLIENTWAITSYNCPROC) (GLsync sync, GLbitfield flags, GLuint64 timeout);
typedef void (APIENTRYP PFNGLWAITSYNCPROC) (GLsync sync, GLbitfield flags, GLuint64 timeout);
typedef void (APIENTRYP PFNGLGETINTEGER64VPROC) (GLenum pname, GLint64 *data);
typedef void (APIENTRYP PFNGLGETSYNCIVPROC) (GLsync sync, GLenum pname, GLsizei count, GLsizei *length, GLint *values);
typedef void (APIENTRYP PFNGLGETINTEGER64I_VPROC) (GLenum target, GLuint index, GLint64 *data);
typedef void (APIENTRYP PFNGLGETBUFFERPARAMETERI64VPROC) (GLenum target, GLenum pname, GLint64 *params);
typedef void (APIENTRYP PFNGLFRAMEBUFFERTEXTUREPROC) (GLenum target, GLenum attachment, GLuint texture, GLint level);
typedef void (APIENTRYP PFNGLTEXIMAGE2DMULTISAMPLEPROC) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations);
typedef void (APIENTRYP PFNGLTEXIMAGE3DMULTISAMPLEPROC) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations);
typedef void (APIENTRYP PFNGLGETMULTISAMPLEFVPROC) (GLenum pname, GLuint index, GLfloat *val);
typedef void (APIENTRYP PFNGLSAMPLEMASKIPROC) (GLuint maskNumber, GLbitfield mask);
#endif /* OPENGL_VERSION_3_2 */

#ifndef OPENGL_VERSION_3_3
#define OPENGL_VERSION_3_3 1
#define GL_VERTEX_ATTRIB_ARRAY_DIVISOR    0x88FE
#define GL_SRC1_COLOR                     0x88F9
#define GL_ONE_MINUS_SRC1_COLOR           0x88FA
#define GL_ONE_MINUS_SRC1_ALPHA           0x88FB
#define GL_MAX_DUAL_SOURCE_DRAW_BUFFERS   0x88FC
#define GL_ANY_SAMPLES_PASSED             0x8C2F
#define GL_SAMPLER_BINDING                0x8919
#define GL_RGB10_A2UI                     0x906F
#define GL_TEXTURE_SWIZZLE_R              0x8E42
#define GL_TEXTURE_SWIZZLE_G              0x8E43
#define GL_TEXTURE_SWIZZLE_B              0x8E44
#define GL_TEXTURE_SWIZZLE_A              0x8E45
#define GL_TEXTURE_SWIZZLE_RGBA           0x8E46
#define GL_TIME_ELAPSED                   0x88BF
#define GL_TIMESTAMP                      0x8E28
#define GL_INT_2_10_10_10_REV             0x8D9F
typedef void (APIENTRYP PFNGLBINDFRAGDATALOCATIONINDEXEDPROC) (GLuint program, GLuint colorNumber, GLuint index, const GLchar *name);
typedef GLint (APIENTRYP PFNGLGETFRAGDATAINDEXPROC) (GLuint program, const GLchar *name);
typedef void (APIENTRYP PFNGLGENSAMPLERSPROC) (GLsizei count, GLuint *samplers);
typedef void (APIENTRYP PFNGLDELETESAMPLERSPROC) (GLsizei count, const GLuint *samplers);
typedef GLboolean (APIENTRYP PFNGLISSAMPLERPROC) (GLuint sampler);
typedef void (APIENTRYP PFNGLBINDSAMPLERPROC) (GLuint unit, GLuint sampler);
typedef void (APIENTRYP PFNGLSAMPLERPARAMETERIPROC) (GLuint sampler, GLenum pname, GLint param);
typedef void (APIENTRYP PFNGLSAMPLERPARAMETERIVPROC) (GLuint sampler, GLenum pname, const GLint *param);
typedef void (APIENTRYP PFNGLSAMPLERPARAMETERFPROC) (GLuint sampler, GLenum pname, GLfloat param);
typedef void (APIENTRYP PFNGLSAMPLERPARAMETERFVPROC) (GLuint sampler, GLenum pname, const GLfloat *param);
typedef void (APIENTRYP PFNGLSAMPLERPARAMETERIIVPROC) (GLuint sampler, GLenum pname, const GLint *param);
typedef void (APIENTRYP PFNGLSAMPLERPARAMETERIUIVPROC) (GLuint sampler, GLenum pname, const GLuint *param);
typedef void (APIENTRYP PFNGLGETSAMPLERPARAMETERIVPROC) (GLuint sampler, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLGETSAMPLERPARAMETERIIVPROC) (GLuint sampler, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLGETSAMPLERPARAMETERFVPROC) (GLuint sampler, GLenum pname, GLfloat *params);
typedef void (APIENTRYP PFNGLGETSAMPLERPARAMETERIUIVPROC) (GLuint sampler, GLenum pname, GLuint *params);
typedef void (APIENTRYP PFNGLQUERYCOUNTERPROC) (GLuint id, GLenum target);
typedef void (APIENTRYP PFNGLGETQUERYOBJECTI64VPROC) (GLuint id, GLenum pname, GLint64 *params);
typedef void (APIENTRYP PFNGLGETQUERYOBJECTUI64VPROC) (GLuint id, GLenum pname, GLuint64 *params);
typedef void (APIENTRYP PFNGLVERTEXATTRIBDIVISORPROC) (GLuint index, GLuint divisor);
typedef void (APIENTRYP PFNGLVERTEXATTRIBP1UIPROC) (GLuint index, GLenum type, GLboolean normalized, GLuint value);
typedef void (APIENTRYP PFNGLVERTEXATTRIBP1UIVPROC) (GLuint index, GLenum type, GLboolean normalized, const GLuint *value);
typedef void (APIENTRYP PFNGLVERTEXATTRIBP2UIPROC) (GLuint index, GLenum type, GLboolean normalized, GLuint value);
typedef void (APIENTRYP PFNGLVERTEXATTRIBP2UIVPROC) (GLuint index, GLenum type, GLboolean normalized, const GLuint *value);
typedef void (APIENTRYP PFNGLVERTEXATTRIBP3UIPROC) (GLuint index, GLenum type, GLboolean normalized, GLuint value);
typedef void (APIENTRYP PFNGLVERTEXATTRIBP3UIVPROC) (GLuint index, GLenum type, GLboolean normalized, const GLuint *value);
typedef void (APIENTRYP PFNGLVERTEXATTRIBP4UIPROC) (GLuint index, GLenum type, GLboolean normalized, GLuint value);
typedef void (APIENTRYP PFNGLVERTEXATTRIBP4UIVPROC) (GLuint index, GLenum type, GLboolean normalized, const GLuint *value);
#endif /* OPENGL_VERSION_3_3 */

#ifndef OPENGL_VERSION_4_0
#define OPENGL_VERSION_4_0 1
#define GL_SAMPLE_SHADING                 0x8C36
#define GL_MIN_SAMPLE_SHADING_VALUE       0x8C37
#define GL_MIN_PROGRAM_TEXTURE_GATHER_OFFSET 0x8E5E
#define GL_MAX_PROGRAM_TEXTURE_GATHER_OFFSET 0x8E5F
#define GL_TEXTURE_CUBE_MAP_ARRAY         0x9009
#define GL_TEXTURE_BINDING_CUBE_MAP_ARRAY 0x900A
#define GL_PROXY_TEXTURE_CUBE_MAP_ARRAY   0x900B
#define GL_SAMPLER_CUBE_MAP_ARRAY         0x900C
#define GL_SAMPLER_CUBE_MAP_ARRAY_SHADOW  0x900D
#define GL_INT_SAMPLER_CUBE_MAP_ARRAY     0x900E
#define GL_UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY 0x900F
#define GL_DRAW_INDIRECT_BUFFER           0x8F3F
#define GL_DRAW_INDIRECT_BUFFER_BINDING   0x8F43
#define GL_GEOMETRY_SHADER_INVOCATIONS    0x887F
#define GL_MAX_GEOMETRY_SHADER_INVOCATIONS 0x8E5A
#define GL_MIN_FRAGMENT_INTERPOLATION_OFFSET 0x8E5B
#define GL_MAX_FRAGMENT_INTERPOLATION_OFFSET 0x8E5C
#define GL_FRAGMENT_INTERPOLATION_OFFSET_BITS 0x8E5D
#define GL_MAX_VERTEX_STREAMS             0x8E71
#define GL_DOUBLE_VEC2                    0x8FFC
#define GL_DOUBLE_VEC3                    0x8FFD
#define GL_DOUBLE_VEC4                    0x8FFE
#define GL_DOUBLE_MAT2                    0x8F46
#define GL_DOUBLE_MAT3                    0x8F47
#define GL_DOUBLE_MAT4                    0x8F48
#define GL_DOUBLE_MAT2x3                  0x8F49
#define GL_DOUBLE_MAT2x4                  0x8F4A
#define GL_DOUBLE_MAT3x2                  0x8F4B
#define GL_DOUBLE_MAT3x4                  0x8F4C
#define GL_DOUBLE_MAT4x2                  0x8F4D
#define GL_DOUBLE_MAT4x3                  0x8F4E
#define GL_ACTIVE_SUBROUTINES             0x8DE5
#define GL_ACTIVE_SUBROUTINE_UNIFORMS     0x8DE6
#define GL_ACTIVE_SUBROUTINE_UNIFORM_LOCATIONS 0x8E47
#define GL_ACTIVE_SUBROUTINE_MAX_LENGTH   0x8E48
#define GL_ACTIVE_SUBROUTINE_UNIFORM_MAX_LENGTH 0x8E49
#define GL_MAX_SUBROUTINES                0x8DE7
#define GL_MAX_SUBROUTINE_UNIFORM_LOCATIONS 0x8DE8
#define GL_NUM_COMPATIBLE_SUBROUTINES     0x8E4A
#define GL_COMPATIBLE_SUBROUTINES         0x8E4B
#define GL_PATCHES                        0x000E
#define GL_PATCH_VERTICES                 0x8E72
#define GL_PATCH_DEFAULT_INNER_LEVEL      0x8E73
#define GL_PATCH_DEFAULT_OUTER_LEVEL      0x8E74
#define GL_TESS_CONTROL_OUTPUT_VERTICES   0x8E75
#define GL_TESS_GEN_MODE                  0x8E76
#define GL_TESS_GEN_SPACING               0x8E77
#define GL_TESS_GEN_VERTEX_ORDER          0x8E78
#define GL_TESS_GEN_POINT_MODE            0x8E79
#define GL_ISOLINES                       0x8E7A
#define GL_FRACTIONAL_ODD                 0x8E7B
#define GL_FRACTIONAL_EVEN                0x8E7C
#define GL_MAX_PATCH_VERTICES             0x8E7D
#define GL_MAX_TESS_GEN_LEVEL             0x8E7E
#define GL_MAX_TESS_CONTROL_UNIFORM_COMPONENTS 0x8E7F
#define GL_MAX_TESS_EVALUATION_UNIFORM_COMPONENTS 0x8E80
#define GL_MAX_TESS_CONTROL_TEXTURE_IMAGE_UNITS 0x8E81
#define GL_MAX_TESS_EVALUATION_TEXTURE_IMAGE_UNITS 0x8E82
#define GL_MAX_TESS_CONTROL_OUTPUT_COMPONENTS 0x8E83
#define GL_MAX_TESS_PATCH_COMPONENTS      0x8E84
#define GL_MAX_TESS_CONTROL_TOTAL_OUTPUT_COMPONENTS 0x8E85
#define GL_MAX_TESS_EVALUATION_OUTPUT_COMPONENTS 0x8E86
#define GL_MAX_TESS_CONTROL_UNIFORM_BLOCKS 0x8E89
#define GL_MAX_TESS_EVALUATION_UNIFORM_BLOCKS 0x8E8A
#define GL_MAX_TESS_CONTROL_INPUT_COMPONENTS 0x886C
#define GL_MAX_TESS_EVALUATION_INPUT_COMPONENTS 0x886D
#define GL_MAX_COMBINED_TESS_CONTROL_UNIFORM_COMPONENTS 0x8E1E
#define GL_MAX_COMBINED_TESS_EVALUATION_UNIFORM_COMPONENTS 0x8E1F
#define GL_UNIFORM_BLOCK_REFERENCED_BY_TESS_CONTROL_SHADER 0x84F0
#define GL_UNIFORM_BLOCK_REFERENCED_BY_TESS_EVALUATION_SHADER 0x84F1
#define GL_TESS_EVALUATION_SHADER         0x8E87
#define GL_TESS_CONTROL_SHADER            0x8E88
#define GL_TRANSFORM_FEEDBACK             0x8E22
#define GL_TRANSFORM_FEEDBACK_BUFFER_PAUSED 0x8E23
#define GL_TRANSFORM_FEEDBACK_BUFFER_ACTIVE 0x8E24
#define GL_TRANSFORM_FEEDBACK_BINDING     0x8E25
#define GL_MAX_TRANSFORM_FEEDBACK_BUFFERS 0x8E70
typedef void (APIENTRYP PFNGLMINSAMPLESHADINGPROC) (GLfloat value);
typedef void (APIENTRYP PFNGLBLENDEQUATIONIPROC) (GLuint buf, GLenum mode);
typedef void (APIENTRYP PFNGLBLENDEQUATIONSEPARATEIPROC) (GLuint buf, GLenum modeRGB, GLenum modeAlpha);
typedef void (APIENTRYP PFNGLBLENDFUNCIPROC) (GLuint buf, GLenum src, GLenum dst);
typedef void (APIENTRYP PFNGLBLENDFUNCSEPARATEIPROC) (GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
typedef void (APIENTRYP PFNGLDRAWARRAYSINDIRECTPROC) (GLenum mode, const void *indirect);
typedef void (APIENTRYP PFNGLDRAWELEMENTSINDIRECTPROC) (GLenum mode, GLenum type, const void *indirect);
typedef void (APIENTRYP PFNGLUNIFORM1DPROC) (GLint location, GLdouble x);
typedef void (APIENTRYP PFNGLUNIFORM2DPROC) (GLint location, GLdouble x, GLdouble y);
typedef void (APIENTRYP PFNGLUNIFORM3DPROC) (GLint location, GLdouble x, GLdouble y, GLdouble z);
typedef void (APIENTRYP PFNGLUNIFORM4DPROC) (GLint location, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
typedef void (APIENTRYP PFNGLUNIFORM1DVPROC) (GLint location, GLsizei count, const GLdouble *value);
typedef void (APIENTRYP PFNGLUNIFORM2DVPROC) (GLint location, GLsizei count, const GLdouble *value);
typedef void (APIENTRYP PFNGLUNIFORM3DVPROC) (GLint location, GLsizei count, const GLdouble *value);
typedef void (APIENTRYP PFNGLUNIFORM4DVPROC) (GLint location, GLsizei count, const GLdouble *value);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX2DVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX3DVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX4DVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX2X3DVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX2X4DVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX3X2DVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX3X4DVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX4X2DVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX4X3DVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (APIENTRYP PFNGLGETUNIFORMDVPROC) (GLuint program, GLint location, GLdouble *params);
typedef GLint (APIENTRYP PFNGLGETSUBROUTINEUNIFORMLOCATIONPROC) (GLuint program, GLenum shadertype, const GLchar *name);
typedef GLuint (APIENTRYP PFNGLGETSUBROUTINEINDEXPROC) (GLuint program, GLenum shadertype, const GLchar *name);
typedef void (APIENTRYP PFNGLGETACTIVESUBROUTINEUNIFORMIVPROC) (GLuint program, GLenum shadertype, GLuint index, GLenum pname, GLint *values);
typedef void (APIENTRYP PFNGLGETACTIVESUBROUTINEUNIFORMNAMEPROC) (GLuint program, GLenum shadertype, GLuint index, GLsizei bufSize, GLsizei *length, GLchar *name);
typedef void (APIENTRYP PFNGLGETACTIVESUBROUTINENAMEPROC) (GLuint program, GLenum shadertype, GLuint index, GLsizei bufSize, GLsizei *length, GLchar *name);
typedef void (APIENTRYP PFNGLUNIFORMSUBROUTINESUIVPROC) (GLenum shadertype, GLsizei count, const GLuint *indices);
typedef void (APIENTRYP PFNGLGETUNIFORMSUBROUTINEUIVPROC) (GLenum shadertype, GLint location, GLuint *params);
typedef void (APIENTRYP PFNGLGETPROGRAMSTAGEIVPROC) (GLuint program, GLenum shadertype, GLenum pname, GLint *values);
typedef void (APIENTRYP PFNGLPATCHPARAMETERIPROC) (GLenum pname, GLint value);
typedef void (APIENTRYP PFNGLPATCHPARAMETERFVPROC) (GLenum pname, const GLfloat *values);
typedef void (APIENTRYP PFNGLBINDTRANSFORMFEEDBACKPROC) (GLenum target, GLuint id);
typedef void (APIENTRYP PFNGLDELETETRANSFORMFEEDBACKSPROC) (GLsizei n, const GLuint *ids);
typedef void (APIENTRYP PFNGLGENTRANSFORMFEEDBACKSPROC) (GLsizei n, GLuint *ids);
typedef GLboolean (APIENTRYP PFNGLISTRANSFORMFEEDBACKPROC) (GLuint id);
typedef void (APIENTRYP PFNGLPAUSETRANSFORMFEEDBACKPROC) (void);
typedef void (APIENTRYP PFNGLRESUMETRANSFORMFEEDBACKPROC) (void);
typedef void (APIENTRYP PFNGLDRAWTRANSFORMFEEDBACKPROC) (GLenum mode, GLuint id);
typedef void (APIENTRYP PFNGLDRAWTRANSFORMFEEDBACKSTREAMPROC) (GLenum mode, GLuint id, GLuint stream);
typedef void (APIENTRYP PFNGLBEGINQUERYINDEXEDPROC) (GLenum target, GLuint index, GLuint id);
typedef void (APIENTRYP PFNGLENDQUERYINDEXEDPROC) (GLenum target, GLuint index);
typedef void (APIENTRYP PFNGLGETQUERYINDEXEDIVPROC) (GLenum target, GLuint index, GLenum pname, GLint *params);
#endif /* OPENGL_VERSION_4_0 */

#ifndef OPENGL_VERSION_4_1
#define OPENGL_VERSION_4_1 1
#define GL_FIXED                          0x140C
#define GL_IMPLEMENTATION_COLOR_READ_TYPE 0x8B9A
#define GL_IMPLEMENTATION_COLOR_READ_FORMAT 0x8B9B
#define GL_LOW_FLOAT                      0x8DF0
#define GL_MEDIUM_FLOAT                   0x8DF1
#define GL_HIGH_FLOAT                     0x8DF2
#define GL_LOW_INT                        0x8DF3
#define GL_MEDIUM_INT                     0x8DF4
#define GL_HIGH_INT                       0x8DF5
#define GL_SHADER_COMPILER                0x8DFA
#define GL_SHADER_BINARY_FORMATS          0x8DF8
#define GL_NUM_SHADER_BINARY_FORMATS      0x8DF9
#define GL_MAX_VERTEX_UNIFORM_VECTORS     0x8DFB
#define GL_MAX_VARYING_VECTORS            0x8DFC
#define GL_MAX_FRAGMENT_UNIFORM_VECTORS   0x8DFD
#define GL_RGB565                         0x8D62
#define GL_PROGRAM_BINARY_RETRIEVABLE_HINT 0x8257
#define GL_PROGRAM_BINARY_LENGTH          0x8741
#define GL_NUM_PROGRAM_BINARY_FORMATS     0x87FE
#define GL_PROGRAM_BINARY_FORMATS         0x87FF
#define GL_VERTEX_SHADER_BIT              0x00000001
#define GL_FRAGMENT_SHADER_BIT            0x00000002
#define GL_GEOMETRY_SHADER_BIT            0x00000004
#define GL_TESS_CONTROL_SHADER_BIT        0x00000008
#define GL_TESS_EVALUATION_SHADER_BIT     0x00000010
#define GL_ALL_SHADER_BITS                0xFFFFFFFF
#define GL_PROGRAM_SEPARABLE              0x8258
#define GL_ACTIVE_PROGRAM                 0x8259
#define GL_PROGRAM_PIPELINE_BINDING       0x825A
#define GL_MAX_VIEWPORTS                  0x825B
#define GL_VIEWPORT_SUBPIXEL_BITS         0x825C
#define GL_VIEWPORT_BOUNDS_RANGE          0x825D
#define GL_LAYER_PROVOKING_VERTEX         0x825E
#define GL_VIEWPORT_INDEX_PROVOKING_VERTEX 0x825F
#define GL_UNDEFINED_VERTEX               0x8260
typedef void (APIENTRYP PFNGLRELEASESHADERCOMPILERPROC) (void);
typedef void (APIENTRYP PFNGLSHADERBINARYPROC) (GLsizei count, const GLuint *shaders, GLenum binaryFormat, const void *binary, GLsizei length);
typedef void (APIENTRYP PFNGLGETSHADERPRECISIONFORMATPROC) (GLenum shadertype, GLenum precisiontype, GLint *range, GLint *precision);
typedef void (APIENTRYP PFNGLDEPTHRANGEFPROC) (GLfloat n, GLfloat f);
typedef void (APIENTRYP PFNGLCLEARDEPTHFPROC) (GLfloat d);
typedef void (APIENTRYP PFNGLGETPROGRAMBINARYPROC) (GLuint program, GLsizei bufSize, GLsizei *length, GLenum *binaryFormat, void *binary);
typedef void (APIENTRYP PFNGLPROGRAMBINARYPROC) (GLuint program, GLenum binaryFormat, const void *binary, GLsizei length);
typedef void (APIENTRYP PFNGLPROGRAMPARAMETERIPROC) (GLuint program, GLenum pname, GLint value);
typedef void (APIENTRYP PFNGLUSEPROGRAMSTAGESPROC) (GLuint pipeline, GLbitfield stages, GLuint program);
typedef void (APIENTRYP PFNGLACTIVESHADERPROGRAMPROC) (GLuint pipeline, GLuint program);
typedef GLuint (APIENTRYP PFNGLCREATESHADERPROGRAMVPROC) (GLenum type, GLsizei count, const GLchar *const*strings);
typedef void (APIENTRYP PFNGLBINDPROGRAMPIPELINEPROC) (GLuint pipeline);
typedef void (APIENTRYP PFNGLDELETEPROGRAMPIPELINESPROC) (GLsizei n, const GLuint *pipelines);
typedef void (APIENTRYP PFNGLGENPROGRAMPIPELINESPROC) (GLsizei n, GLuint *pipelines);
typedef GLboolean (APIENTRYP PFNGLISPROGRAMPIPELINEPROC) (GLuint pipeline);
typedef void (APIENTRYP PFNGLGETPROGRAMPIPELINEIVPROC) (GLuint pipeline, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM1IPROC) (GLuint program, GLint location, GLint v0);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM1IVPROC) (GLuint program, GLint location, GLsizei count, const GLint *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM1FPROC) (GLuint program, GLint location, GLfloat v0);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM1FVPROC) (GLuint program, GLint location, GLsizei count, const GLfloat *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM1DPROC) (GLuint program, GLint location, GLdouble v0);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM1DVPROC) (GLuint program, GLint location, GLsizei count, const GLdouble *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM1UIPROC) (GLuint program, GLint location, GLuint v0);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM1UIVPROC) (GLuint program, GLint location, GLsizei count, const GLuint *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM2IPROC) (GLuint program, GLint location, GLint v0, GLint v1);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM2IVPROC) (GLuint program, GLint location, GLsizei count, const GLint *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM2FPROC) (GLuint program, GLint location, GLfloat v0, GLfloat v1);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM2FVPROC) (GLuint program, GLint location, GLsizei count, const GLfloat *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM2DPROC) (GLuint program, GLint location, GLdouble v0, GLdouble v1);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM2DVPROC) (GLuint program, GLint location, GLsizei count, const GLdouble *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM2UIPROC) (GLuint program, GLint location, GLuint v0, GLuint v1);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM2UIVPROC) (GLuint program, GLint location, GLsizei count, const GLuint *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM3IPROC) (GLuint program, GLint location, GLint v0, GLint v1, GLint v2);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM3IVPROC) (GLuint program, GLint location, GLsizei count, const GLint *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM3FPROC) (GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM3FVPROC) (GLuint program, GLint location, GLsizei count, const GLfloat *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM3DPROC) (GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM3DVPROC) (GLuint program, GLint location, GLsizei count, const GLdouble *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM3UIPROC) (GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM3UIVPROC) (GLuint program, GLint location, GLsizei count, const GLuint *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM4IPROC) (GLuint program, GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM4IVPROC) (GLuint program, GLint location, GLsizei count, const GLint *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM4FPROC) (GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM4FVPROC) (GLuint program, GLint location, GLsizei count, const GLfloat *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM4DPROC) (GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2, GLdouble v3);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM4DVPROC) (GLuint program, GLint location, GLsizei count, const GLdouble *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM4UIPROC) (GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM4UIVPROC) (GLuint program, GLint location, GLsizei count, const GLuint *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2FVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3FVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4FVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2DVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3DVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4DVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2X3DVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3X2DVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2X4DVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4X2DVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3X4DVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4X3DVPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value);
typedef void (APIENTRYP PFNGLVALIDATEPROGRAMPIPELINEPROC) (GLuint pipeline);
typedef void (APIENTRYP PFNGLGETPROGRAMPIPELINEINFOLOGPROC) (GLuint pipeline, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
typedef void (APIENTRYP PFNGLVERTEXATTRIBL1DPROC) (GLuint index, GLdouble x);
typedef void (APIENTRYP PFNGLVERTEXATTRIBL2DPROC) (GLuint index, GLdouble x, GLdouble y);
typedef void (APIENTRYP PFNGLVERTEXATTRIBL3DPROC) (GLuint index, GLdouble x, GLdouble y, GLdouble z);
typedef void (APIENTRYP PFNGLVERTEXATTRIBL4DPROC) (GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
typedef void (APIENTRYP PFNGLVERTEXATTRIBL1DVPROC) (GLuint index, const GLdouble *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIBL2DVPROC) (GLuint index, const GLdouble *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIBL3DVPROC) (GLuint index, const GLdouble *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIBL4DVPROC) (GLuint index, const GLdouble *v);
typedef void (APIENTRYP PFNGLVERTEXATTRIBLPOINTERPROC) (GLuint index, GLint size, GLenum type, GLsizei stride, const void *pointer);
typedef void (APIENTRYP PFNGLGETVERTEXATTRIBLDVPROC) (GLuint index, GLenum pname, GLdouble *params);
typedef void (APIENTRYP PFNGLVIEWPORTARRAYVPROC) (GLuint first, GLsizei count, const GLfloat *v);
typedef void (APIENTRYP PFNGLVIEWPORTINDEXEDFPROC) (GLuint index, GLfloat x, GLfloat y, GLfloat w, GLfloat h);
typedef void (APIENTRYP PFNGLVIEWPORTINDEXEDFVPROC) (GLuint index, const GLfloat *v);
typedef void (APIENTRYP PFNGLSCISSORARRAYVPROC) (GLuint first, GLsizei count, const GLint *v);
typedef void (APIENTRYP PFNGLSCISSORINDEXEDPROC) (GLuint index, GLint left, GLint bottom, GLsizei width, GLsizei height);
typedef void (APIENTRYP PFNGLSCISSORINDEXEDVPROC) (GLuint index, const GLint *v);
typedef void (APIENTRYP PFNGLDEPTHRANGEARRAYVPROC) (GLuint first, GLsizei count, const GLdouble *v);
typedef void (APIENTRYP PFNGLDEPTHRANGEINDEXEDPROC) (GLuint index, GLdouble n, GLdouble f);
typedef void (APIENTRYP PFNGLGETFLOATI_VPROC) (GLenum target, GLuint index, GLfloat *data);
typedef void (APIENTRYP PFNGLGETDOUBLEI_VPROC) (GLenum target, GLuint index, GLdouble *data);
#endif /* OPENGL_VERSION_4_1 */

#ifndef OPENGL_VERSION_4_2
#define OPENGL_VERSION_4_2 1
#define GL_COPY_READ_BUFFER_BINDING       0x8F36
#define GL_COPY_WRITE_BUFFER_BINDING      0x8F37
#define GL_TRANSFORM_FEEDBACK_ACTIVE      0x8E24
#define GL_TRANSFORM_FEEDBACK_PAUSED      0x8E23
#define GL_UNPACK_COMPRESSED_BLOCK_WIDTH  0x9127
#define GL_UNPACK_COMPRESSED_BLOCK_HEIGHT 0x9128
#define GL_UNPACK_COMPRESSED_BLOCK_DEPTH  0x9129
#define GL_UNPACK_COMPRESSED_BLOCK_SIZE   0x912A
#define GL_PACK_COMPRESSED_BLOCK_WIDTH    0x912B
#define GL_PACK_COMPRESSED_BLOCK_HEIGHT   0x912C
#define GL_PACK_COMPRESSED_BLOCK_DEPTH    0x912D
#define GL_PACK_COMPRESSED_BLOCK_SIZE     0x912E
#define GL_NUM_SAMPLE_COUNTS              0x9380
#define GL_MIN_MAP_BUFFER_ALIGNMENT       0x90BC
#define GL_ATOMIC_COUNTER_BUFFER          0x92C0
#define GL_ATOMIC_COUNTER_BUFFER_BINDING  0x92C1
#define GL_ATOMIC_COUNTER_BUFFER_START    0x92C2
#define GL_ATOMIC_COUNTER_BUFFER_SIZE     0x92C3
#define GL_ATOMIC_COUNTER_BUFFER_DATA_SIZE 0x92C4
#define GL_ATOMIC_COUNTER_BUFFER_ACTIVE_ATOMIC_COUNTERS 0x92C5
#define GL_ATOMIC_COUNTER_BUFFER_ACTIVE_ATOMIC_COUNTER_INDICES 0x92C6
#define GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_VERTEX_SHADER 0x92C7
#define GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_TESS_CONTROL_SHADER 0x92C8
#define GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_TESS_EVALUATION_SHADER 0x92C9
#define GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_GEOMETRY_SHADER 0x92CA
#define GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_FRAGMENT_SHADER 0x92CB
#define GL_MAX_VERTEX_ATOMIC_COUNTER_BUFFERS 0x92CC
#define GL_MAX_TESS_CONTROL_ATOMIC_COUNTER_BUFFERS 0x92CD
#define GL_MAX_TESS_EVALUATION_ATOMIC_COUNTER_BUFFERS 0x92CE
#define GL_MAX_GEOMETRY_ATOMIC_COUNTER_BUFFERS 0x92CF
#define GL_MAX_FRAGMENT_ATOMIC_COUNTER_BUFFERS 0x92D0
#define GL_MAX_COMBINED_ATOMIC_COUNTER_BUFFERS 0x92D1
#define GL_MAX_VERTEX_ATOMIC_COUNTERS     0x92D2
#define GL_MAX_TESS_CONTROL_ATOMIC_COUNTERS 0x92D3
#define GL_MAX_TESS_EVALUATION_ATOMIC_COUNTERS 0x92D4
#define GL_MAX_GEOMETRY_ATOMIC_COUNTERS   0x92D5
#define GL_MAX_FRAGMENT_ATOMIC_COUNTERS   0x92D6
#define GL_MAX_COMBINED_ATOMIC_COUNTERS   0x92D7
#define GL_MAX_ATOMIC_COUNTER_BUFFER_SIZE 0x92D8
#define GL_MAX_ATOMIC_COUNTER_BUFFER_BINDINGS 0x92DC
#define GL_ACTIVE_ATOMIC_COUNTER_BUFFERS  0x92D9
#define GL_UNIFORM_ATOMIC_COUNTER_BUFFER_INDEX 0x92DA
#define GL_UNSIGNED_INT_ATOMIC_COUNTER    0x92DB
#define GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT 0x00000001
#define GL_ELEMENT_ARRAY_BARRIER_BIT      0x00000002
#define GL_UNIFORM_BARRIER_BIT            0x00000004
#define GL_TEXTURE_FETCH_BARRIER_BIT      0x00000008
#define GL_SHADER_IMAGE_ACCESS_BARRIER_BIT 0x00000020
#define GL_COMMAND_BARRIER_BIT            0x00000040
#define GL_PIXEL_BUFFER_BARRIER_BIT       0x00000080
#define GL_TEXTURE_UPDATE_BARRIER_BIT     0x00000100
#define GL_BUFFER_UPDATE_BARRIER_BIT      0x00000200
#define GL_FRAMEBUFFER_BARRIER_BIT        0x00000400
#define GL_TRANSFORM_FEEDBACK_BARRIER_BIT 0x00000800
#define GL_ATOMIC_COUNTER_BARRIER_BIT     0x00001000
#define GL_ALL_BARRIER_BITS               0xFFFFFFFF
#define GL_MAX_IMAGE_UNITS                0x8F38
#define GL_MAX_COMBINED_IMAGE_UNITS_AND_FRAGMENT_OUTPUTS 0x8F39
#define GL_IMAGE_BINDING_NAME             0x8F3A
#define GL_IMAGE_BINDING_LEVEL            0x8F3B
#define GL_IMAGE_BINDING_LAYERED          0x8F3C
#define GL_IMAGE_BINDING_LAYER            0x8F3D
#define GL_IMAGE_BINDING_ACCESS           0x8F3E
#define GL_IMAGE_1D                       0x904C
#define GL_IMAGE_2D                       0x904D
#define GL_IMAGE_3D                       0x904E
#define GL_IMAGE_2D_RECT                  0x904F
#define GL_IMAGE_CUBE                     0x9050
#define GL_IMAGE_BUFFER                   0x9051
#define GL_IMAGE_1D_ARRAY                 0x9052
#define GL_IMAGE_2D_ARRAY                 0x9053
#define GL_IMAGE_CUBE_MAP_ARRAY           0x9054
#define GL_IMAGE_2D_MULTISAMPLE           0x9055
#define GL_IMAGE_2D_MULTISAMPLE_ARRAY     0x9056
#define GL_INT_IMAGE_1D                   0x9057
#define GL_INT_IMAGE_2D                   0x9058
#define GL_INT_IMAGE_3D                   0x9059
#define GL_INT_IMAGE_2D_RECT              0x905A
#define GL_INT_IMAGE_CUBE                 0x905B
#define GL_INT_IMAGE_BUFFER               0x905C
#define GL_INT_IMAGE_1D_ARRAY             0x905D
#define GL_INT_IMAGE_2D_ARRAY             0x905E
#define GL_INT_IMAGE_CUBE_MAP_ARRAY       0x905F
#define GL_INT_IMAGE_2D_MULTISAMPLE       0x9060
#define GL_INT_IMAGE_2D_MULTISAMPLE_ARRAY 0x9061
#define GL_UNSIGNED_INT_IMAGE_1D          0x9062
#define GL_UNSIGNED_INT_IMAGE_2D          0x9063
#define GL_UNSIGNED_INT_IMAGE_3D          0x9064
#define GL_UNSIGNED_INT_IMAGE_2D_RECT     0x9065
#define GL_UNSIGNED_INT_IMAGE_CUBE        0x9066
#define GL_UNSIGNED_INT_IMAGE_BUFFER      0x9067
#define GL_UNSIGNED_INT_IMAGE_1D_ARRAY    0x9068
#define GL_UNSIGNED_INT_IMAGE_2D_ARRAY    0x9069
#define GL_UNSIGNED_INT_IMAGE_CUBE_MAP_ARRAY 0x906A
#define GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE 0x906B
#define GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE_ARRAY 0x906C
#define GL_MAX_IMAGE_SAMPLES              0x906D
#define GL_IMAGE_BINDING_FORMAT           0x906E
#define GL_IMAGE_FORMAT_COMPATIBILITY_TYPE 0x90C7
#define GL_IMAGE_FORMAT_COMPATIBILITY_BY_SIZE 0x90C8
#define GL_IMAGE_FORMAT_COMPATIBILITY_BY_CLASS 0x90C9
#define GL_MAX_VERTEX_IMAGE_UNIFORMS      0x90CA
#define GL_MAX_TESS_CONTROL_IMAGE_UNIFORMS 0x90CB
#define GL_MAX_TESS_EVALUATION_IMAGE_UNIFORMS 0x90CC
#define GL_MAX_GEOMETRY_IMAGE_UNIFORMS    0x90CD
#define GL_MAX_FRAGMENT_IMAGE_UNIFORMS    0x90CE
#define GL_MAX_COMBINED_IMAGE_UNIFORMS    0x90CF
#define GL_COMPRESSED_RGBA_BPTC_UNORM     0x8E8C
#define GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM 0x8E8D
#define GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT 0x8E8E
#define GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT 0x8E8F
#define GL_TEXTURE_IMMUTABLE_FORMAT       0x912F
typedef void (APIENTRYP PFNGLDRAWARRAYSINSTANCEDBASEINSTANCEPROC) (GLenum mode, GLint first, GLsizei count, GLsizei instancecount, GLuint baseinstance);
typedef void (APIENTRYP PFNGLDRAWELEMENTSINSTANCEDBASEINSTANCEPROC) (GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei instancecount, GLuint baseinstance);
typedef void (APIENTRYP PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCEPROC) (GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei instancecount, GLint basevertex, GLuint baseinstance);
typedef void (APIENTRYP PFNGLGETINTERNALFORMATIVPROC) (GLenum target, GLenum internalformat, GLenum pname, GLsizei count, GLint *params);
typedef void (APIENTRYP PFNGLGETACTIVEATOMICCOUNTERBUFFERIVPROC) (GLuint program, GLuint bufferIndex, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLBINDIMAGETEXTUREPROC) (GLuint unit, GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum access, GLenum format);
typedef void (APIENTRYP PFNGLMEMORYBARRIERPROC) (GLbitfield barriers);
typedef void (APIENTRYP PFNGLTEXSTORAGE1DPROC) (GLenum target, GLsizei levels, GLenum internalformat, GLsizei width);
typedef void (APIENTRYP PFNGLTEXSTORAGE2DPROC) (GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (APIENTRYP PFNGLTEXSTORAGE3DPROC) (GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth);
typedef void (APIENTRYP PFNGLDRAWTRANSFORMFEEDBACKINSTANCEDPROC) (GLenum mode, GLuint id, GLsizei instancecount);
typedef void (APIENTRYP PFNGLDRAWTRANSFORMFEEDBACKSTREAMINSTANCEDPROC) (GLenum mode, GLuint id, GLuint stream, GLsizei instancecount);
#endif /* OPENGL_VERSION_4_2 */

#ifndef OPENGL_VERSION_4_3
#define OPENGL_VERSION_4_3 1
typedef void (APIENTRY  *GLDEBUGPROC)(GLenum source,GLenum type,GLuint id,GLenum severity,GLsizei length,const GLchar *message,const void *userParam);
#define GL_NUM_SHADING_LANGUAGE_VERSIONS  0x82E9
#define GL_VERTEX_ATTRIB_ARRAY_LONG       0x874E
#define GL_COMPRESSED_RGB8_ETC2           0x9274
#define GL_COMPRESSED_SRGB8_ETC2          0x9275
#define GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2 0x9276
#define GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2 0x9277
#define GL_COMPRESSED_RGBA8_ETC2_EAC      0x9278
#define GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC 0x9279
#define GL_COMPRESSED_R11_EAC             0x9270
#define GL_COMPRESSED_SIGNED_R11_EAC      0x9271
#define GL_COMPRESSED_RG11_EAC            0x9272
#define GL_COMPRESSED_SIGNED_RG11_EAC     0x9273
#define GL_PRIMITIVE_RESTART_FIXED_INDEX  0x8D69
#define GL_ANY_SAMPLES_PASSED_CONSERVATIVE 0x8D6A
#define GL_MAX_ELEMENT_INDEX              0x8D6B
#define GL_COMPUTE_SHADER                 0x91B9
#define GL_MAX_COMPUTE_UNIFORM_BLOCKS     0x91BB
#define GL_MAX_COMPUTE_TEXTURE_IMAGE_UNITS 0x91BC
#define GL_MAX_COMPUTE_IMAGE_UNIFORMS     0x91BD
#define GL_MAX_COMPUTE_SHARED_MEMORY_SIZE 0x8262
#define GL_MAX_COMPUTE_UNIFORM_COMPONENTS 0x8263
#define GL_MAX_COMPUTE_ATOMIC_COUNTER_BUFFERS 0x8264
#define GL_MAX_COMPUTE_ATOMIC_COUNTERS    0x8265
#define GL_MAX_COMBINED_COMPUTE_UNIFORM_COMPONENTS 0x8266
#define GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS 0x90EB
#define GL_MAX_COMPUTE_WORK_GROUP_COUNT   0x91BE
#define GL_MAX_COMPUTE_WORK_GROUP_SIZE    0x91BF
#define GL_COMPUTE_WORK_GROUP_SIZE        0x8267
#define GL_UNIFORM_BLOCK_REFERENCED_BY_COMPUTE_SHADER 0x90EC
#define GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_COMPUTE_SHADER 0x90ED
#define GL_DISPATCH_INDIRECT_BUFFER       0x90EE
#define GL_DISPATCH_INDIRECT_BUFFER_BINDING 0x90EF
#define GL_COMPUTE_SHADER_BIT             0x00000020
#define GL_DEBUG_OUTPUT_SYNCHRONOUS       0x8242
#define GL_DEBUG_NEXT_LOGGED_MESSAGE_LENGTH 0x8243
#define GL_DEBUG_CALLBACK_FUNCTION        0x8244
#define GL_DEBUG_CALLBACK_USER_PARAM      0x8245
#define GL_DEBUG_SOURCE_API               0x8246
#define GL_DEBUG_SOURCE_WINDOW_SYSTEM     0x8247
#define GL_DEBUG_SOURCE_SHADER_COMPILER   0x8248
#define GL_DEBUG_SOURCE_THIRD_PARTY       0x8249
#define GL_DEBUG_SOURCE_APPLICATION       0x824A
#define GL_DEBUG_SOURCE_OTHER             0x824B
#define GL_DEBUG_TYPE_ERROR               0x824C
#define GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR 0x824D
#define GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR  0x824E
#define GL_DEBUG_TYPE_PORTABILITY         0x824F
#define GL_DEBUG_TYPE_PERFORMANCE         0x8250
#define GL_DEBUG_TYPE_OTHER               0x8251
#define GL_MAX_DEBUG_MESSAGE_LENGTH       0x9143
#define GL_MAX_DEBUG_LOGGED_MESSAGES      0x9144
#define GL_DEBUG_LOGGED_MESSAGES          0x9145
#define GL_DEBUG_SEVERITY_HIGH            0x9146
#define GL_DEBUG_SEVERITY_MEDIUM          0x9147
#define GL_DEBUG_SEVERITY_LOW             0x9148
#define GL_DEBUG_TYPE_MARKER              0x8268
#define GL_DEBUG_TYPE_PUSH_GROUP          0x8269
#define GL_DEBUG_TYPE_POP_GROUP           0x826A
#define GL_DEBUG_SEVERITY_NOTIFICATION    0x826B
#define GL_MAX_DEBUG_GROUP_STACK_DEPTH    0x826C
#define GL_DEBUG_GROUP_STACK_DEPTH        0x826D
#define GL_BUFFER                         0x82E0
#define GL_SHADER                         0x82E1
#define GL_PROGRAM                        0x82E2
#define GL_QUERY                          0x82E3
#define GL_PROGRAM_PIPELINE               0x82E4
#define GL_SAMPLER                        0x82E6
#define GL_MAX_LABEL_LENGTH               0x82E8
#define GL_DEBUG_OUTPUT                   0x92E0
#define GL_CONTEXT_FLAG_DEBUG_BIT         0x00000002
#define GL_MAX_UNIFORM_LOCATIONS          0x826E
#define GL_FRAMEBUFFER_DEFAULT_WIDTH      0x9310
#define GL_FRAMEBUFFER_DEFAULT_HEIGHT     0x9311
#define GL_FRAMEBUFFER_DEFAULT_LAYERS     0x9312
#define GL_FRAMEBUFFER_DEFAULT_SAMPLES    0x9313
#define GL_FRAMEBUFFER_DEFAULT_FIXED_SAMPLE_LOCATIONS 0x9314
#define GL_MAX_FRAMEBUFFER_WIDTH          0x9315
#define GL_MAX_FRAMEBUFFER_HEIGHT         0x9316
#define GL_MAX_FRAMEBUFFER_LAYERS         0x9317
#define GL_MAX_FRAMEBUFFER_SAMPLES        0x9318
#define GL_INTERNALFORMAT_SUPPORTED       0x826F
#define GL_INTERNALFORMAT_PREFERRED       0x8270
#define GL_INTERNALFORMAT_RED_SIZE        0x8271
#define GL_INTERNALFORMAT_GREEN_SIZE      0x8272
#define GL_INTERNALFORMAT_BLUE_SIZE       0x8273
#define GL_INTERNALFORMAT_ALPHA_SIZE      0x8274
#define GL_INTERNALFORMAT_DEPTH_SIZE      0x8275
#define GL_INTERNALFORMAT_STENCIL_SIZE    0x8276
#define GL_INTERNALFORMAT_SHARED_SIZE     0x8277
#define GL_INTERNALFORMAT_RED_TYPE        0x8278
#define GL_INTERNALFORMAT_GREEN_TYPE      0x8279
#define GL_INTERNALFORMAT_BLUE_TYPE       0x827A
#define GL_INTERNALFORMAT_ALPHA_TYPE      0x827B
#define GL_INTERNALFORMAT_DEPTH_TYPE      0x827C
#define GL_INTERNALFORMAT_STENCIL_TYPE    0x827D
#define GL_MAX_WIDTH                      0x827E
#define GL_MAX_HEIGHT                     0x827F
#define GL_MAX_DEPTH                      0x8280
#define GL_MAX_LAYERS                     0x8281
#define GL_MAX_COMBINED_DIMENSIONS        0x8282
#define GL_COLOR_COMPONENTS               0x8283
#define GL_DEPTH_COMPONENTS               0x8284
#define GL_STENCIL_COMPONENTS             0x8285
#define GL_COLOR_RENDERABLE               0x8286
#define GL_DEPTH_RENDERABLE               0x8287
#define GL_STENCIL_RENDERABLE             0x8288
#define GL_FRAMEBUFFER_RENDERABLE         0x8289
#define GL_FRAMEBUFFER_RENDERABLE_LAYERED 0x828A
#define GL_FRAMEBUFFER_BLEND              0x828B
#define GL_READ_PIXELS                    0x828C
#define GL_READ_PIXELS_FORMAT             0x828D
#define GL_READ_PIXELS_TYPE               0x828E
#define GL_TEXTURE_IMAGE_FORMAT           0x828F
#define GL_TEXTURE_IMAGE_TYPE             0x8290
#define GL_GET_TEXTURE_IMAGE_FORMAT       0x8291
#define GL_GET_TEXTURE_IMAGE_TYPE         0x8292
#define GL_MIPMAP                         0x8293
#define GL_MANUAL_GENERATE_MIPMAP         0x8294
#define GL_AUTO_GENERATE_MIPMAP           0x8295
#define GL_COLOR_ENCODING                 0x8296
#define GL_SRGB_READ                      0x8297
#define GL_SRGB_WRITE                     0x8298
#define GL_FILTER                         0x829A
#define GL_VERTEX_TEXTURE                 0x829B
#define GL_TESS_CONTROL_TEXTURE           0x829C
#define GL_TESS_EVALUATION_TEXTURE        0x829D
#define GL_GEOMETRY_TEXTURE               0x829E
#define GL_FRAGMENT_TEXTURE               0x829F
#define GL_COMPUTE_TEXTURE                0x82A0
#define GL_TEXTURE_SHADOW                 0x82A1
#define GL_TEXTURE_GATHER                 0x82A2
#define GL_TEXTURE_GATHER_SHADOW          0x82A3
#define GL_SHADER_IMAGE_LOAD              0x82A4
#define GL_SHADER_IMAGE_STORE             0x82A5
#define GL_SHADER_IMAGE_ATOMIC            0x82A6
#define GL_IMAGE_TEXEL_SIZE               0x82A7
#define GL_IMAGE_COMPATIBILITY_CLASS      0x82A8
#define GL_IMAGE_PIXEL_FORMAT             0x82A9
#define GL_IMAGE_PIXEL_TYPE               0x82AA
#define GL_SIMULTANEOUS_TEXTURE_AND_DEPTH_TEST 0x82AC
#define GL_SIMULTANEOUS_TEXTURE_AND_STENCIL_TEST 0x82AD
#define GL_SIMULTANEOUS_TEXTURE_AND_DEPTH_WRITE 0x82AE
#define GL_SIMULTANEOUS_TEXTURE_AND_STENCIL_WRITE 0x82AF
#define GL_TEXTURE_COMPRESSED_BLOCK_WIDTH 0x82B1
#define GL_TEXTURE_COMPRESSED_BLOCK_HEIGHT 0x82B2
#define GL_TEXTURE_COMPRESSED_BLOCK_SIZE  0x82B3
#define GL_CLEAR_BUFFER                   0x82B4
#define GL_TEXTURE_VIEW                   0x82B5
#define GL_VIEW_COMPATIBILITY_CLASS       0x82B6
#define GL_FULL_SUPPORT                   0x82B7
#define GL_CAVEAT_SUPPORT                 0x82B8
#define GL_IMAGE_CLASS_4_X_32             0x82B9
#define GL_IMAGE_CLASS_2_X_32             0x82BA
#define GL_IMAGE_CLASS_1_X_32             0x82BB
#define GL_IMAGE_CLASS_4_X_16             0x82BC
#define GL_IMAGE_CLASS_2_X_16             0x82BD
#define GL_IMAGE_CLASS_1_X_16             0x82BE
#define GL_IMAGE_CLASS_4_X_8              0x82BF
#define GL_IMAGE_CLASS_2_X_8              0x82C0
#define GL_IMAGE_CLASS_1_X_8              0x82C1
#define GL_IMAGE_CLASS_11_11_10           0x82C2
#define GL_IMAGE_CLASS_10_10_10_2         0x82C3
#define GL_VIEW_CLASS_128_BITS            0x82C4
#define GL_VIEW_CLASS_96_BITS             0x82C5
#define GL_VIEW_CLASS_64_BITS             0x82C6
#define GL_VIEW_CLASS_48_BITS             0x82C7
#define GL_VIEW_CLASS_32_BITS             0x82C8
#define GL_VIEW_CLASS_24_BITS             0x82C9
#define GL_VIEW_CLASS_16_BITS             0x82CA
#define GL_VIEW_CLASS_8_BITS              0x82CB
#define GL_VIEW_CLASS_S3TC_DXT1_RGB       0x82CC
#define GL_VIEW_CLASS_S3TC_DXT1_RGBA      0x82CD
#define GL_VIEW_CLASS_S3TC_DXT3_RGBA      0x82CE
#define GL_VIEW_CLASS_S3TC_DXT5_RGBA      0x82CF
#define GL_VIEW_CLASS_RGTC1_RED           0x82D0
#define GL_VIEW_CLASS_RGTC2_RG            0x82D1
#define GL_VIEW_CLASS_BPTC_UNORM          0x82D2
#define GL_VIEW_CLASS_BPTC_FLOAT          0x82D3
#define GL_UNIFORM                        0x92E1
#define GL_UNIFORM_BLOCK                  0x92E2
#define GL_PROGRAM_INPUT                  0x92E3
#define GL_PROGRAM_OUTPUT                 0x92E4
#define GL_BUFFER_VARIABLE                0x92E5
#define GL_SHADER_STORAGE_BLOCK           0x92E6
#define GL_VERTEX_SUBROUTINE              0x92E8
#define GL_TESS_CONTROL_SUBROUTINE        0x92E9
#define GL_TESS_EVALUATION_SUBROUTINE     0x92EA
#define GL_GEOMETRY_SUBROUTINE            0x92EB
#define GL_FRAGMENT_SUBROUTINE            0x92EC
#define GL_COMPUTE_SUBROUTINE             0x92ED
#define GL_VERTEX_SUBROUTINE_UNIFORM      0x92EE
#define GL_TESS_CONTROL_SUBROUTINE_UNIFORM 0x92EF
#define GL_TESS_EVALUATION_SUBROUTINE_UNIFORM 0x92F0
#define GL_GEOMETRY_SUBROUTINE_UNIFORM    0x92F1
#define GL_FRAGMENT_SUBROUTINE_UNIFORM    0x92F2
#define GL_COMPUTE_SUBROUTINE_UNIFORM     0x92F3
#define GL_TRANSFORM_FEEDBACK_VARYING     0x92F4
#define GL_ACTIVE_RESOURCES               0x92F5
#define GL_MAX_NAME_LENGTH                0x92F6
#define GL_MAX_NUM_ACTIVE_VARIABLES       0x92F7
#define GL_MAX_NUM_COMPATIBLE_SUBROUTINES 0x92F8
#define GL_NAME_LENGTH                    0x92F9
#define GL_TYPE                           0x92FA
#define GL_ARRAY_SIZE                     0x92FB
#define GL_OFFSET                         0x92FC
#define GL_BLOCK_INDEX                    0x92FD
#define GL_ARRAY_STRIDE                   0x92FE
#define GL_MATRIX_STRIDE                  0x92FF
#define GL_IS_ROW_MAJOR                   0x9300
#define GL_ATOMIC_COUNTER_BUFFER_INDEX    0x9301
#define GL_BUFFER_BINDING                 0x9302
#define GL_BUFFER_DATA_SIZE               0x9303
#define GL_NUM_ACTIVE_VARIABLES           0x9304
#define GL_ACTIVE_VARIABLES               0x9305
#define GL_REFERENCED_BY_VERTEX_SHADER    0x9306
#define GL_REFERENCED_BY_TESS_CONTROL_SHADER 0x9307
#define GL_REFERENCED_BY_TESS_EVALUATION_SHADER 0x9308
#define GL_REFERENCED_BY_GEOMETRY_SHADER  0x9309
#define GL_REFERENCED_BY_FRAGMENT_SHADER  0x930A
#define GL_REFERENCED_BY_COMPUTE_SHADER   0x930B
#define GL_TOP_LEVEL_ARRAY_SIZE           0x930C
#define GL_TOP_LEVEL_ARRAY_STRIDE         0x930D
#define GL_LOCATION                       0x930E
#define GL_LOCATION_INDEX                 0x930F
#define GL_IS_PER_PATCH                   0x92E7
#define GL_SHADER_STORAGE_BUFFER          0x90D2
#define GL_SHADER_STORAGE_BUFFER_BINDING  0x90D3
#define GL_SHADER_STORAGE_BUFFER_START    0x90D4
#define GL_SHADER_STORAGE_BUFFER_SIZE     0x90D5
#define GL_MAX_VERTEX_SHADER_STORAGE_BLOCKS 0x90D6
#define GL_MAX_GEOMETRY_SHADER_STORAGE_BLOCKS 0x90D7
#define GL_MAX_TESS_CONTROL_SHADER_STORAGE_BLOCKS 0x90D8
#define GL_MAX_TESS_EVALUATION_SHADER_STORAGE_BLOCKS 0x90D9
#define GL_MAX_FRAGMENT_SHADER_STORAGE_BLOCKS 0x90DA
#define GL_MAX_COMPUTE_SHADER_STORAGE_BLOCKS 0x90DB
#define GL_MAX_COMBINED_SHADER_STORAGE_BLOCKS 0x90DC
#define GL_MAX_SHADER_STORAGE_BUFFER_BINDINGS 0x90DD
#define GL_MAX_SHADER_STORAGE_BLOCK_SIZE  0x90DE
#define GL_SHADER_STORAGE_BUFFER_OFFSET_ALIGNMENT 0x90DF
#define GL_SHADER_STORAGE_BARRIER_BIT     0x00002000
#define GL_MAX_COMBINED_SHADER_OUTPUT_RESOURCES 0x8F39
#define GL_DEPTH_STENCIL_TEXTURE_MODE     0x90EA
#define GL_TEXTURE_BUFFER_OFFSET          0x919D
#define GL_TEXTURE_BUFFER_SIZE            0x919E
#define GL_TEXTURE_BUFFER_OFFSET_ALIGNMENT 0x919F
#define GL_TEXTURE_VIEW_MIN_LEVEL         0x82DB
#define GL_TEXTURE_VIEW_NUM_LEVELS        0x82DC
#define GL_TEXTURE_VIEW_MIN_LAYER         0x82DD
#define GL_TEXTURE_VIEW_NUM_LAYERS        0x82DE
#define GL_TEXTURE_IMMUTABLE_LEVELS       0x82DF
#define GL_VERTEX_ATTRIB_BINDING          0x82D4
#define GL_VERTEX_ATTRIB_RELATIVE_OFFSET  0x82D5
#define GL_VERTEX_BINDING_DIVISOR         0x82D6
#define GL_VERTEX_BINDING_OFFSET          0x82D7
#define GL_VERTEX_BINDING_STRIDE          0x82D8
#define GL_MAX_VERTEX_ATTRIB_RELATIVE_OFFSET 0x82D9
#define GL_MAX_VERTEX_ATTRIB_BINDINGS     0x82DA
#define GL_VERTEX_BINDING_BUFFER          0x8F4F
typedef void (APIENTRYP PFNGLCLEARBUFFERDATAPROC) (GLenum target, GLenum internalformat, GLenum format, GLenum type, const void *data);
typedef void (APIENTRYP PFNGLCLEARBUFFERSUBDATAPROC) (GLenum target, GLenum internalformat, GLintptr offset, GLsizeiptr size, GLenum format, GLenum type, const void *data);
typedef void (APIENTRYP PFNGLDISPATCHCOMPUTEPROC) (GLuint num_groups_x, GLuint num_groups_y, GLuint num_groups_z);
typedef void (APIENTRYP PFNGLDISPATCHCOMPUTEINDIRECTPROC) (GLintptr indirect);
typedef void (APIENTRYP PFNGLCOPYIMAGESUBDATAPROC) (GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei srcWidth, GLsizei srcHeight, GLsizei srcDepth);
typedef void (APIENTRYP PFNGLFRAMEBUFFERPARAMETERIPROC) (GLenum target, GLenum pname, GLint param);
typedef void (APIENTRYP PFNGLGETFRAMEBUFFERPARAMETERIVPROC) (GLenum target, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLGETINTERNALFORMATI64VPROC) (GLenum target, GLenum internalformat, GLenum pname, GLsizei count, GLint64 *params);
typedef void (APIENTRYP PFNGLINVALIDATETEXSUBIMAGEPROC) (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth);
typedef void (APIENTRYP PFNGLINVALIDATETEXIMAGEPROC) (GLuint texture, GLint level);
typedef void (APIENTRYP PFNGLINVALIDATEBUFFERSUBDATAPROC) (GLuint buffer, GLintptr offset, GLsizeiptr length);
typedef void (APIENTRYP PFNGLINVALIDATEBUFFERDATAPROC) (GLuint buffer);
typedef void (APIENTRYP PFNGLINVALIDATEFRAMEBUFFERPROC) (GLenum target, GLsizei numAttachments, const GLenum *attachments);
typedef void (APIENTRYP PFNGLINVALIDATESUBFRAMEBUFFERPROC) (GLenum target, GLsizei numAttachments, const GLenum *attachments, GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (APIENTRYP PFNGLMULTIDRAWARRAYSINDIRECTPROC) (GLenum mode, const void *indirect, GLsizei drawcount, GLsizei stride);
typedef void (APIENTRYP PFNGLMULTIDRAWELEMENTSINDIRECTPROC) (GLenum mode, GLenum type, const void *indirect, GLsizei drawcount, GLsizei stride);
typedef void (APIENTRYP PFNGLGETPROGRAMINTERFACEIVPROC) (GLuint program, GLenum programInterface, GLenum pname, GLint *params);
typedef GLuint (APIENTRYP PFNGLGETPROGRAMRESOURCEINDEXPROC) (GLuint program, GLenum programInterface, const GLchar *name);
typedef void (APIENTRYP PFNGLGETPROGRAMRESOURCENAMEPROC) (GLuint program, GLenum programInterface, GLuint index, GLsizei bufSize, GLsizei *length, GLchar *name);
typedef void (APIENTRYP PFNGLGETPROGRAMRESOURCEIVPROC) (GLuint program, GLenum programInterface, GLuint index, GLsizei propCount, const GLenum *props, GLsizei count, GLsizei *length, GLint *params);
typedef GLint (APIENTRYP PFNGLGETPROGRAMRESOURCELOCATIONPROC) (GLuint program, GLenum programInterface, const GLchar *name);
typedef GLint (APIENTRYP PFNGLGETPROGRAMRESOURCELOCATIONINDEXPROC) (GLuint program, GLenum programInterface, const GLchar *name);
typedef void (APIENTRYP PFNGLSHADERSTORAGEBLOCKBINDINGPROC) (GLuint program, GLuint storageBlockIndex, GLuint storageBlockBinding);
typedef void (APIENTRYP PFNGLTEXBUFFERRANGEPROC) (GLenum target, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size);
typedef void (APIENTRYP PFNGLTEXSTORAGE2DMULTISAMPLEPROC) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations);
typedef void (APIENTRYP PFNGLTEXSTORAGE3DMULTISAMPLEPROC) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations);
typedef void (APIENTRYP PFNGLTEXTUREVIEWPROC) (GLuint texture, GLenum target, GLuint origtexture, GLenum internalformat, GLuint minlevel, GLuint numlevels, GLuint minlayer, GLuint numlayers);
typedef void (APIENTRYP PFNGLBINDVERTEXBUFFERPROC) (GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride);
typedef void (APIENTRYP PFNGLVERTEXATTRIBFORMATPROC) (GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset);
typedef void (APIENTRYP PFNGLVERTEXATTRIBIFORMATPROC) (GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset);
typedef void (APIENTRYP PFNGLVERTEXATTRIBLFORMATPROC) (GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset);
typedef void (APIENTRYP PFNGLVERTEXATTRIBBINDINGPROC) (GLuint attribindex, GLuint bindingindex);
typedef void (APIENTRYP PFNGLVERTEXBINDINGDIVISORPROC) (GLuint bindingindex, GLuint divisor);
typedef void (APIENTRYP PFNGLDEBUGMESSAGECONTROLPROC) (GLenum source, GLenum type, GLenum severity, GLsizei count, const GLuint *ids, GLboolean enabled);
typedef void (APIENTRYP PFNGLDEBUGMESSAGEINSERTPROC) (GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *buf);
typedef void (APIENTRYP PFNGLDEBUGMESSAGECALLBACKPROC) (GLDEBUGPROC callback, const void *userParam);
typedef GLuint (APIENTRYP PFNGLGETDEBUGMESSAGELOGPROC) (GLuint count, GLsizei bufSize, GLenum *sources, GLenum *types, GLuint *ids, GLenum *severities, GLsizei *lengths, GLchar *messageLog);
typedef void (APIENTRYP PFNGLPUSHDEBUGGROUPPROC) (GLenum source, GLuint id, GLsizei length, const GLchar *message);
typedef void (APIENTRYP PFNGLPOPDEBUGGROUPPROC) (void);
typedef void (APIENTRYP PFNGLOBJECTLABELPROC) (GLenum identifier, GLuint name, GLsizei length, const GLchar *label);
typedef void (APIENTRYP PFNGLGETOBJECTLABELPROC) (GLenum identifier, GLuint name, GLsizei bufSize, GLsizei *length, GLchar *label);
typedef void (APIENTRYP PFNGLOBJECTPTRLABELPROC) (const void *ptr, GLsizei length, const GLchar *label);
typedef void (APIENTRYP PFNGLGETOBJECTPTRLABELPROC) (const void *ptr, GLsizei bufSize, GLsizei *length, GLchar *label);
#endif /* OPENGL_VERSION_4_3 */

#ifndef OPENGL_VERSION_4_4
#define OPENGL_VERSION_4_4 1
#define GL_MAX_VERTEX_ATTRIB_STRIDE       0x82E5
#define GL_PRIMITIVE_RESTART_FOR_PATCHES_SUPPORTED 0x8221
#define GL_TEXTURE_BUFFER_BINDING         0x8C2A
#define GL_MAP_PERSISTENT_BIT             0x0040
#define GL_MAP_COHERENT_BIT               0x0080
#define GL_DYNAMIC_STORAGE_BIT            0x0100
#define GL_CLIENT_STORAGE_BIT             0x0200
#define GL_CLIENT_MAPPED_BUFFER_BARRIER_BIT 0x00004000
#define GL_BUFFER_IMMUTABLE_STORAGE       0x821F
#define GL_BUFFER_STORAGE_FLAGS           0x8220
#define GL_CLEAR_TEXTURE                  0x9365
#define GL_LOCATION_COMPONENT             0x934A
#define GL_TRANSFORM_FEEDBACK_BUFFER_INDEX 0x934B
#define GL_TRANSFORM_FEEDBACK_BUFFER_STRIDE 0x934C
#define GL_QUERY_BUFFER                   0x9192
#define GL_QUERY_BUFFER_BARRIER_BIT       0x00008000
#define GL_QUERY_BUFFER_BINDING           0x9193
#define GL_QUERY_RESULT_NO_WAIT           0x9194
#define GL_MIRROR_CLAMP_TO_EDGE           0x8743
typedef void (APIENTRYP PFNGLBUFFERSTORAGEPROC) (GLenum target, GLsizeiptr size, const void *data, GLbitfield flags);
typedef void (APIENTRYP PFNGLCLEARTEXIMAGEPROC) (GLuint texture, GLint level, GLenum format, GLenum type, const void *data);
typedef void (APIENTRYP PFNGLCLEARTEXSUBIMAGEPROC) (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void *data);
typedef void (APIENTRYP PFNGLBINDBUFFERSBASEPROC) (GLenum target, GLuint first, GLsizei count, const GLuint *buffers);
typedef void (APIENTRYP PFNGLBINDBUFFERSRANGEPROC) (GLenum target, GLuint first, GLsizei count, const GLuint *buffers, const GLintptr *offsets, const GLsizeiptr *sizes);
typedef void (APIENTRYP PFNGLBINDTEXTURESPROC) (GLuint first, GLsizei count, const GLuint *textures);
typedef void (APIENTRYP PFNGLBINDSAMPLERSPROC) (GLuint first, GLsizei count, const GLuint *samplers);
typedef void (APIENTRYP PFNGLBINDIMAGETEXTURESPROC) (GLuint first, GLsizei count, const GLuint *textures);
typedef void (APIENTRYP PFNGLBINDVERTEXBUFFERSPROC) (GLuint first, GLsizei count, const GLuint *buffers, const GLintptr *offsets, const GLsizei *strides);
#endif /* OPENGL_VERSION_4_4 */

#ifndef OPENGL_VERSION_4_5
#define OPENGL_VERSION_4_5 1
#define GL_CONTEXT_LOST                   0x0507
#define GL_NEGATIVE_ONE_TO_ONE            0x935E
#define GL_ZERO_TO_ONE                    0x935F
#define GL_CLIP_ORIGIN                    0x935C
#define GL_CLIP_DEPTH_MODE                0x935D
#define GL_QUERY_WAIT_INVERTED            0x8E17
#define GL_QUERY_NO_WAIT_INVERTED         0x8E18
#define GL_QUERY_BY_REGION_WAIT_INVERTED  0x8E19
#define GL_QUERY_BY_REGION_NO_WAIT_INVERTED 0x8E1A
#define GL_MAX_CULL_DISTANCES             0x82F9
#define GL_MAX_COMBINED_CLIP_AND_CULL_DISTANCES 0x82FA
#define GL_TEXTURE_TARGET                 0x1006
#define GL_QUERY_TARGET                   0x82EA
#define GL_GUILTY_CONTEXT_RESET           0x8253
#define GL_INNOCENT_CONTEXT_RESET         0x8254
#define GL_UNKNOWN_CONTEXT_RESET          0x8255
#define GL_RESET_NOTIFICATION_STRATEGY    0x8256
#define GL_LOSE_CONTEXT_ON_RESET          0x8252
#define GL_NO_RESET_NOTIFICATION          0x8261
#define GL_CONTEXT_FLAG_ROBUST_ACCESS_BIT 0x00000004
#define GL_CONTEXT_RELEASE_BEHAVIOR       0x82FB
#define GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH 0x82FC
typedef void (APIENTRYP PFNGLCLIPCONTROLPROC) (GLenum origin, GLenum depth);
typedef void (APIENTRYP PFNGLCREATETRANSFORMFEEDBACKSPROC) (GLsizei n, GLuint *ids);
typedef void (APIENTRYP PFNGLTRANSFORMFEEDBACKBUFFERBASEPROC) (GLuint xfb, GLuint index, GLuint buffer);
typedef void (APIENTRYP PFNGLTRANSFORMFEEDBACKBUFFERRANGEPROC) (GLuint xfb, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size);
typedef void (APIENTRYP PFNGLGETTRANSFORMFEEDBACKIVPROC) (GLuint xfb, GLenum pname, GLint *param);
typedef void (APIENTRYP PFNGLGETTRANSFORMFEEDBACKI_VPROC) (GLuint xfb, GLenum pname, GLuint index, GLint *param);
typedef void (APIENTRYP PFNGLGETTRANSFORMFEEDBACKI64_VPROC) (GLuint xfb, GLenum pname, GLuint index, GLint64 *param);
typedef void (APIENTRYP PFNGLCREATEBUFFERSPROC) (GLsizei n, GLuint *buffers);
typedef void (APIENTRYP PFNGLNAMEDBUFFERSTORAGEPROC) (GLuint buffer, GLsizeiptr size, const void *data, GLbitfield flags);
typedef void (APIENTRYP PFNGLNAMEDBUFFERDATAPROC) (GLuint buffer, GLsizeiptr size, const void *data, GLenum usage);
typedef void (APIENTRYP PFNGLNAMEDBUFFERSUBDATAPROC) (GLuint buffer, GLintptr offset, GLsizeiptr size, const void *data);
typedef void (APIENTRYP PFNGLCOPYNAMEDBUFFERSUBDATAPROC) (GLuint readBuffer, GLuint writeBuffer, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size);
typedef void (APIENTRYP PFNGLCLEARNAMEDBUFFERDATAPROC) (GLuint buffer, GLenum internalformat, GLenum format, GLenum type, const void *data);
typedef void (APIENTRYP PFNGLCLEARNAMEDBUFFERSUBDATAPROC) (GLuint buffer, GLenum internalformat, GLintptr offset, GLsizeiptr size, GLenum format, GLenum type, const void *data);
typedef void *(APIENTRYP PFNGLMAPNAMEDBUFFERPROC) (GLuint buffer, GLenum access);
typedef void *(APIENTRYP PFNGLMAPNAMEDBUFFERRANGEPROC) (GLuint buffer, GLintptr offset, GLsizeiptr length, GLbitfield access);
typedef GLboolean (APIENTRYP PFNGLUNMAPNAMEDBUFFERPROC) (GLuint buffer);
typedef void (APIENTRYP PFNGLFLUSHMAPPEDNAMEDBUFFERRANGEPROC) (GLuint buffer, GLintptr offset, GLsizeiptr length);
typedef void (APIENTRYP PFNGLGETNAMEDBUFFERPARAMETERIVPROC) (GLuint buffer, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLGETNAMEDBUFFERPARAMETERI64VPROC) (GLuint buffer, GLenum pname, GLint64 *params);
typedef void (APIENTRYP PFNGLGETNAMEDBUFFERPOINTERVPROC) (GLuint buffer, GLenum pname, void **params);
typedef void (APIENTRYP PFNGLGETNAMEDBUFFERSUBDATAPROC) (GLuint buffer, GLintptr offset, GLsizeiptr size, void *data);
typedef void (APIENTRYP PFNGLCREATEFRAMEBUFFERSPROC) (GLsizei n, GLuint *framebuffers);
typedef void (APIENTRYP PFNGLNAMEDFRAMEBUFFERRENDERBUFFERPROC) (GLuint framebuffer, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
typedef void (APIENTRYP PFNGLNAMEDFRAMEBUFFERPARAMETERIPROC) (GLuint framebuffer, GLenum pname, GLint param);
typedef void (APIENTRYP PFNGLNAMEDFRAMEBUFFERTEXTUREPROC) (GLuint framebuffer, GLenum attachment, GLuint texture, GLint level);
typedef void (APIENTRYP PFNGLNAMEDFRAMEBUFFERTEXTURELAYERPROC) (GLuint framebuffer, GLenum attachment, GLuint texture, GLint level, GLint layer);
typedef void (APIENTRYP PFNGLNAMEDFRAMEBUFFERDRAWBUFFERPROC) (GLuint framebuffer, GLenum buf);
typedef void (APIENTRYP PFNGLNAMEDFRAMEBUFFERDRAWBUFFERSPROC) (GLuint framebuffer, GLsizei n, const GLenum *bufs);
typedef void (APIENTRYP PFNGLNAMEDFRAMEBUFFERREADBUFFERPROC) (GLuint framebuffer, GLenum src);
typedef void (APIENTRYP PFNGLINVALIDATENAMEDFRAMEBUFFERDATAPROC) (GLuint framebuffer, GLsizei numAttachments, const GLenum *attachments);
typedef void (APIENTRYP PFNGLINVALIDATENAMEDFRAMEBUFFERSUBDATAPROC) (GLuint framebuffer, GLsizei numAttachments, const GLenum *attachments, GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (APIENTRYP PFNGLCLEARNAMEDFRAMEBUFFERIVPROC) (GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLint *value);
typedef void (APIENTRYP PFNGLCLEARNAMEDFRAMEBUFFERUIVPROC) (GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLuint *value);
typedef void (APIENTRYP PFNGLCLEARNAMEDFRAMEBUFFERFVPROC) (GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLfloat *value);
typedef void (APIENTRYP PFNGLCLEARNAMEDFRAMEBUFFERFIPROC) (GLuint framebuffer, GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil);
typedef void (APIENTRYP PFNGLBLITNAMEDFRAMEBUFFERPROC) (GLuint readFramebuffer, GLuint drawFramebuffer, GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter);
typedef GLenum (APIENTRYP PFNGLCHECKNAMEDFRAMEBUFFERSTATUSPROC) (GLuint framebuffer, GLenum target);
typedef void (APIENTRYP PFNGLGETNAMEDFRAMEBUFFERPARAMETERIVPROC) (GLuint framebuffer, GLenum pname, GLint *param);
typedef void (APIENTRYP PFNGLGETNAMEDFRAMEBUFFERATTACHMENTPARAMETERIVPROC) (GLuint framebuffer, GLenum attachment, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLCREATERENDERBUFFERSPROC) (GLsizei n, GLuint *renderbuffers);
typedef void (APIENTRYP PFNGLNAMEDRENDERBUFFERSTORAGEPROC) (GLuint renderbuffer, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (APIENTRYP PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEPROC) (GLuint renderbuffer, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (APIENTRYP PFNGLGETNAMEDRENDERBUFFERPARAMETERIVPROC) (GLuint renderbuffer, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLCREATETEXTURESPROC) (GLenum target, GLsizei n, GLuint *textures);
typedef void (APIENTRYP PFNGLTEXTUREBUFFERPROC) (GLuint texture, GLenum internalformat, GLuint buffer);
typedef void (APIENTRYP PFNGLTEXTUREBUFFERRANGEPROC) (GLuint texture, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size);
typedef void (APIENTRYP PFNGLTEXTURESTORAGE1DPROC) (GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width);
typedef void (APIENTRYP PFNGLTEXTURESTORAGE2DPROC) (GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (APIENTRYP PFNGLTEXTURESTORAGE3DPROC) (GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth);
typedef void (APIENTRYP PFNGLTEXTURESTORAGE2DMULTISAMPLEPROC) (GLuint texture, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations);
typedef void (APIENTRYP PFNGLTEXTURESTORAGE3DMULTISAMPLEPROC) (GLuint texture, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations);
typedef void (APIENTRYP PFNGLTEXTURESUBIMAGE1DPROC) (GLuint texture, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void *pixels);
typedef void (APIENTRYP PFNGLTEXTURESUBIMAGE2DPROC) (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void *pixels);
typedef void (APIENTRYP PFNGLTEXTURESUBIMAGE3DPROC) (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void *pixels);
typedef void (APIENTRYP PFNGLCOMPRESSEDTEXTURESUBIMAGE1DPROC) (GLuint texture, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void *data);
typedef void (APIENTRYP PFNGLCOMPRESSEDTEXTURESUBIMAGE2DPROC) (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void *data);
typedef void (APIENTRYP PFNGLCOMPRESSEDTEXTURESUBIMAGE3DPROC) (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void *data);
typedef void (APIENTRYP PFNGLCOPYTEXTURESUBIMAGE1DPROC) (GLuint texture, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width);
typedef void (APIENTRYP PFNGLCOPYTEXTURESUBIMAGE2DPROC) (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (APIENTRYP PFNGLCOPYTEXTURESUBIMAGE3DPROC) (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (APIENTRYP PFNGLTEXTUREPARAMETERFPROC) (GLuint texture, GLenum pname, GLfloat param);
typedef void (APIENTRYP PFNGLTEXTUREPARAMETERFVPROC) (GLuint texture, GLenum pname, const GLfloat *param);
typedef void (APIENTRYP PFNGLTEXTUREPARAMETERIPROC) (GLuint texture, GLenum pname, GLint param);
typedef void (APIENTRYP PFNGLTEXTUREPARAMETERIIVPROC) (GLuint texture, GLenum pname, const GLint *params);
typedef void (APIENTRYP PFNGLTEXTUREPARAMETERIUIVPROC) (GLuint texture, GLenum pname, const GLuint *params);
typedef void (APIENTRYP PFNGLTEXTUREPARAMETERIVPROC) (GLuint texture, GLenum pname, const GLint *param);
typedef void (APIENTRYP PFNGLGENERATETEXTUREMIPMAPPROC) (GLuint texture);
typedef void (APIENTRYP PFNGLBINDTEXTUREUNITPROC) (GLuint unit, GLuint texture);
typedef void (APIENTRYP PFNGLGETTEXTUREIMAGEPROC) (GLuint texture, GLint level, GLenum format, GLenum type, GLsizei bufSize, void *pixels);
typedef void (APIENTRYP PFNGLGETCOMPRESSEDTEXTUREIMAGEPROC) (GLuint texture, GLint level, GLsizei bufSize, void *pixels);
typedef void (APIENTRYP PFNGLGETTEXTURELEVELPARAMETERFVPROC) (GLuint texture, GLint level, GLenum pname, GLfloat *params);
typedef void (APIENTRYP PFNGLGETTEXTURELEVELPARAMETERIVPROC) (GLuint texture, GLint level, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLGETTEXTUREPARAMETERFVPROC) (GLuint texture, GLenum pname, GLfloat *params);
typedef void (APIENTRYP PFNGLGETTEXTUREPARAMETERIIVPROC) (GLuint texture, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLGETTEXTUREPARAMETERIUIVPROC) (GLuint texture, GLenum pname, GLuint *params);
typedef void (APIENTRYP PFNGLGETTEXTUREPARAMETERIVPROC) (GLuint texture, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLCREATEVERTEXARRAYSPROC) (GLsizei n, GLuint *arrays);
typedef void (APIENTRYP PFNGLDISABLEVERTEXARRAYATTRIBPROC) (GLuint vaobj, GLuint index);
typedef void (APIENTRYP PFNGLENABLEVERTEXARRAYATTRIBPROC) (GLuint vaobj, GLuint index);
typedef void (APIENTRYP PFNGLVERTEXARRAYELEMENTBUFFERPROC) (GLuint vaobj, GLuint buffer);
typedef void (APIENTRYP PFNGLVERTEXARRAYVERTEXBUFFERPROC) (GLuint vaobj, GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride);
typedef void (APIENTRYP PFNGLVERTEXARRAYVERTEXBUFFERSPROC) (GLuint vaobj, GLuint first, GLsizei count, const GLuint *buffers, const GLintptr *offsets, const GLsizei *strides);
typedef void (APIENTRYP PFNGLVERTEXARRAYATTRIBBINDINGPROC) (GLuint vaobj, GLuint attribindex, GLuint bindingindex);
typedef void (APIENTRYP PFNGLVERTEXARRAYATTRIBFORMATPROC) (GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset);
typedef void (APIENTRYP PFNGLVERTEXARRAYATTRIBIFORMATPROC) (GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset);
typedef void (APIENTRYP PFNGLVERTEXARRAYATTRIBLFORMATPROC) (GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset);
typedef void (APIENTRYP PFNGLVERTEXARRAYBINDINGDIVISORPROC) (GLuint vaobj, GLuint bindingindex, GLuint divisor);
typedef void (APIENTRYP PFNGLGETVERTEXARRAYIVPROC) (GLuint vaobj, GLenum pname, GLint *param);
typedef void (APIENTRYP PFNGLGETVERTEXARRAYINDEXEDIVPROC) (GLuint vaobj, GLuint index, GLenum pname, GLint *param);
typedef void (APIENTRYP PFNGLGETVERTEXARRAYINDEXED64IVPROC) (GLuint vaobj, GLuint index, GLenum pname, GLint64 *param);
typedef void (APIENTRYP PFNGLCREATESAMPLERSPROC) (GLsizei n, GLuint *samplers);
typedef void (APIENTRYP PFNGLCREATEPROGRAMPIPELINESPROC) (GLsizei n, GLuint *pipelines);
typedef void (APIENTRYP PFNGLCREATEQUERIESPROC) (GLenum target, GLsizei n, GLuint *ids);
typedef void (APIENTRYP PFNGLGETQUERYBUFFEROBJECTI64VPROC) (GLuint id, GLuint buffer, GLenum pname, GLintptr offset);
typedef void (APIENTRYP PFNGLGETQUERYBUFFEROBJECTIVPROC) (GLuint id, GLuint buffer, GLenum pname, GLintptr offset);
typedef void (APIENTRYP PFNGLGETQUERYBUFFEROBJECTUI64VPROC) (GLuint id, GLuint buffer, GLenum pname, GLintptr offset);
typedef void (APIENTRYP PFNGLGETQUERYBUFFEROBJECTUIVPROC) (GLuint id, GLuint buffer, GLenum pname, GLintptr offset);
typedef void (APIENTRYP PFNGLMEMORYBARRIERBYREGIONPROC) (GLbitfield barriers);
typedef void (APIENTRYP PFNGLGETTEXTURESUBIMAGEPROC) (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, GLsizei bufSize, void *pixels);
typedef void (APIENTRYP PFNGLGETCOMPRESSEDTEXTURESUBIMAGEPROC) (GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLsizei bufSize, void *pixels);
typedef GLenum (APIENTRYP PFNGLGETGRAPHICSRESETSTATUSPROC) (void);
typedef void (APIENTRYP PFNGLGETNCOMPRESSEDTEXIMAGEPROC) (GLenum target, GLint lod, GLsizei bufSize, void *pixels);
typedef void (APIENTRYP PFNGLGETNTEXIMAGEPROC) (GLenum target, GLint level, GLenum format, GLenum type, GLsizei bufSize, void *pixels);
typedef void (APIENTRYP PFNGLGETNUNIFORMDVPROC) (GLuint program, GLint location, GLsizei bufSize, GLdouble *params);
typedef void (APIENTRYP PFNGLGETNUNIFORMFVPROC) (GLuint program, GLint location, GLsizei bufSize, GLfloat *params);
typedef void (APIENTRYP PFNGLGETNUNIFORMIVPROC) (GLuint program, GLint location, GLsizei bufSize, GLint *params);
typedef void (APIENTRYP PFNGLGETNUNIFORMUIVPROC) (GLuint program, GLint location, GLsizei bufSize, GLuint *params);
typedef void (APIENTRYP PFNGLREADNPIXELSPROC) (GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLsizei bufSize, void *data);
typedef void (APIENTRYP PFNGLTEXTUREBARRIERPROC) (void);
#endif /* OPENGL_VERSION_4_5 */

#ifndef OPENGL_VERSION_4_6
#define OPENGL_VERSION_4_6 1
#define GL_SHADER_BINARY_FORMAT_SPIR_V    0x9551
#define GL_SPIR_V_BINARY                  0x9552
#define GL_PARAMETER_BUFFER               0x80EE
#define GL_PARAMETER_BUFFER_BINDING       0x80EF
#define GL_CONTEXT_FLAG_NO_ERROR_BIT      0x00000008
#define GL_VERTICES_SUBMITTED             0x82EE
#define GL_PRIMITIVES_SUBMITTED           0x82EF
#define GL_VERTEX_SHADER_INVOCATIONS      0x82F0
#define GL_TESS_CONTROL_SHADER_PATCHES    0x82F1
#define GL_TESS_EVALUATION_SHADER_INVOCATIONS 0x82F2
#define GL_GEOMETRY_SHADER_PRIMITIVES_EMITTED 0x82F3
#define GL_FRAGMENT_SHADER_INVOCATIONS    0x82F4
#define GL_COMPUTE_SHADER_INVOCATIONS     0x82F5
#define GL_CLIPPING_INPUT_PRIMITIVES      0x82F6
#define GL_CLIPPING_OUTPUT_PRIMITIVES     0x82F7
#define GL_POLYGON_OFFSET_CLAMP           0x8E1B
#define GL_SPIR_V_EXTENSIONS              0x9553
#define GL_NUM_SPIR_V_EXTENSIONS          0x9554
#define GL_TEXTURE_MAX_ANISOTROPY         0x84FE
#define GL_MAX_TEXTURE_MAX_ANISOTROPY     0x84FF
#define GL_TRANSFORM_FEEDBACK_OVERFLOW    0x82EC
#define GL_TRANSFORM_FEEDBACK_STREAM_OVERFLOW 0x82ED
typedef void (APIENTRYP PFNGLSPECIALIZESHADERPROC) (GLuint shader, const GLchar *pEntryPoint, GLuint numSpecializationConstants, const GLuint *pConstantIndex, const GLuint *pConstantValue);
typedef void (APIENTRYP PFNGLMULTIDRAWARRAYSINDIRECTCOUNTPROC) (GLenum mode, const void *indirect, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride);
typedef void (APIENTRYP PFNGLMULTIDRAWELEMENTSINDIRECTCOUNTPROC) (GLenum mode, GLenum type, const void *indirect, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride);
typedef void (APIENTRYP PFNGLPOLYGONOFFSETCLAMPPROC) (GLfloat factor, GLfloat units, GLfloat clamp);
#endif /* OPENGL_VERSION_4_6 */


#ifndef OPENGL_MAJOR_VERSION
#define OPENGL_MAJOR_VERSION 1
#endif

#ifndef OPENGL_MINOR_VERSION
#define OPENGL_MINOR_VERSION 0
#endif

#define OPENGL_TEST_VERSION(major, minor) major < OPENGL_MAJOR_VERSION || major == OPENGL_MAJOR_VERSION && minor <= OPENGL_MINOR_VERSION
#define LOAD_OPENGL_FUNCTIONS(type, name) type name


#define LOAD_OPENGL_FUNCTIONS_1_0
LOAD_OPENGL_FUNCTIONS(PFNGLCULLFACEPROC, glCullFace);
LOAD_OPENGL_FUNCTIONS(PFNGLFRONTFACEPROC, glFrontFace);
LOAD_OPENGL_FUNCTIONS(PFNGLHINTPROC, glHint);
LOAD_OPENGL_FUNCTIONS(PFNGLLINEWIDTHPROC, glLineWidth);
LOAD_OPENGL_FUNCTIONS(PFNGLPOINTSIZEPROC, glPointSize);
LOAD_OPENGL_FUNCTIONS(PFNGLPOLYGONMODEPROC, glPolygonMode);
LOAD_OPENGL_FUNCTIONS(PFNGLSCISSORPROC, glScissor);
LOAD_OPENGL_FUNCTIONS(PFNGLTEXPARAMETERFPROC, glTexParameterf);
LOAD_OPENGL_FUNCTIONS(PFNGLTEXPARAMETERFVPROC, glTexParameterfv);
LOAD_OPENGL_FUNCTIONS(PFNGLTEXPARAMETERIPROC, glTexParameteri);
LOAD_OPENGL_FUNCTIONS(PFNGLTEXPARAMETERIVPROC, glTexParameteriv);
LOAD_OPENGL_FUNCTIONS(PFNGLTEXIMAGE1DPROC, glTexImage1D);
LOAD_OPENGL_FUNCTIONS(PFNGLTEXIMAGE2DPROC, glTexImage2D);
LOAD_OPENGL_FUNCTIONS(PFNGLDRAWBUFFERPROC, glDrawBuffer);
LOAD_OPENGL_FUNCTIONS(PFNGLCLEARPROC, glClear);
LOAD_OPENGL_FUNCTIONS(PFNGLCLEARCOLORPROC, glClearColor);
LOAD_OPENGL_FUNCTIONS(PFNGLCLEARSTENCILPROC, glClearStencil);
LOAD_OPENGL_FUNCTIONS(PFNGLCLEARDEPTHPROC, glClearDepth);
LOAD_OPENGL_FUNCTIONS(PFNGLSTENCILMASKPROC, glStencilMask);
LOAD_OPENGL_FUNCTIONS(PFNGLCOLORMASKPROC, glColorMask);
LOAD_OPENGL_FUNCTIONS(PFNGLDEPTHMASKPROC, glDepthMask);
LOAD_OPENGL_FUNCTIONS(PFNGLDISABLEPROC, glDisable);
LOAD_OPENGL_FUNCTIONS(PFNGLENABLEPROC, glEnable);
LOAD_OPENGL_FUNCTIONS(PFNGLFINISHPROC, glFinish);
LOAD_OPENGL_FUNCTIONS(PFNGLFLUSHPROC, glFlush);
LOAD_OPENGL_FUNCTIONS(PFNGLBLENDFUNCPROC, glBlendFunc);
LOAD_OPENGL_FUNCTIONS(PFNGLLOGICOPPROC, glLogicOp);
LOAD_OPENGL_FUNCTIONS(PFNGLSTENCILFUNCPROC, glStencilFunc);
LOAD_OPENGL_FUNCTIONS(PFNGLSTENCILOPPROC, glStencilOp);
LOAD_OPENGL_FUNCTIONS(PFNGLDEPTHFUNCPROC, glDepthFunc);
LOAD_OPENGL_FUNCTIONS(PFNGLPIXELSTOREFPROC, glPixelStoref);
LOAD_OPENGL_FUNCTIONS(PFNGLPIXELSTOREIPROC, glPixelStorei);
LOAD_OPENGL_FUNCTIONS(PFNGLREADBUFFERPROC, glReadBuffer);
LOAD_OPENGL_FUNCTIONS(PFNGLREADPIXELSPROC, glReadPixels);
LOAD_OPENGL_FUNCTIONS(PFNGLGETBOOLEANVPROC, glGetBooleanv);
LOAD_OPENGL_FUNCTIONS(PFNGLGETDOUBLEVPROC, glGetDoublev);
LOAD_OPENGL_FUNCTIONS(PFNGLGETERRORPROC, glGetError);
LOAD_OPENGL_FUNCTIONS(PFNGLGETFLOATVPROC, glGetFloatv);
LOAD_OPENGL_FUNCTIONS(PFNGLGETINTEGERVPROC, glGetIntegerv);
LOAD_OPENGL_FUNCTIONS(PFNGLGETSTRINGPROC, glGetString );
LOAD_OPENGL_FUNCTIONS(PFNGLGETTEXIMAGEPROC, glGetTexImage);
LOAD_OPENGL_FUNCTIONS(PFNGLGETTEXPARAMETERFVPROC, glGetTexParameterfv);
LOAD_OPENGL_FUNCTIONS(PFNGLGETTEXPARAMETERIVPROC, glGetTexParameteriv);
LOAD_OPENGL_FUNCTIONS(PFNGLGETTEXLEVELPARAMETERFVPROCglGetTexLevelParameterfv);
LOAD_OPENGL_FUNCTIONS(PFNGLGETTEXLEVELPARAMETERIVPROCglGetTexLevelParameteriv);
LOAD_OPENGL_FUNCTIONS(PFNGLISENABLEDPROC, glIsEnabled);
LOAD_OPENGL_FUNCTIONS(PFNGLDEPTHRANGEPROC, glDepthRange);
LOAD_OPENGL_FUNCTIONS(PFNGLVIEWPORTPROC, glViewport);

#define LOAD_OPENGL_FUNCTIONS_1_1
LOAD_OPENGL_FUNCTIONS(PFNGLDRAWARRAYSPROC, glDrawArrays);
LOAD_OPENGL_FUNCTIONS(PFNGLDRAWELEMENTSPROC, glDrawElements);
LOAD_OPENGL_FUNCTIONS(PFNGLGETPOINTERVPROC, glGetPointerv);
LOAD_OPENGL_FUNCTIONS(PFNGLPOLYGONOFFSETPROC, glPolygonOffset);
LOAD_OPENGL_FUNCTIONS(PFNGLCOPYTEXIMAGE1DPROC, glCopyTexImage1D);
LOAD_OPENGL_FUNCTIONS(PFNGLCOPYTEXIMAGE2DPROC, glCopyTexImage2D);
LOAD_OPENGL_FUNCTIONS(PFNGLCOPYTEXSUBIMAGE1DPROC, glCopyTexSubImage1D);
LOAD_OPENGL_FUNCTIONS(PFNGLCOPYTEXSUBIMAGE2DPROC, glCopyTexSubImage2D);
LOAD_OPENGL_FUNCTIONS(PFNGLTEXSUBIMAGE1DPROC, glTexSubImage1D);
LOAD_OPENGL_FUNCTIONS(PFNGLTEXSUBIMAGE2DPROC, glTexSubImage2D);
LOAD_OPENGL_FUNCTIONS(PFNGLBINDTEXTUREPROC, glBindTexture);
LOAD_OPENGL_FUNCTIONS(PFNGLDELETETEXTURESPROC, glDeleteTextures);
LOAD_OPENGL_FUNCTIONS(PFNGLGENTEXTURESPROC, glGenTextures);
LOAD_OPENGL_FUNCTIONS(PFNGLISTEXTUREPROC, glIsTexture);

#define LOAD_OPENGL_FUNCTIONS_1_2
LOAD_OPENGL_FUNCTIONS(PFNGLDRAWRANGEELEMENTSPROC, glDrawRangeElements);
LOAD_OPENGL_FUNCTIONS(PFNGLTEXIMAGE3DPROC, glTexImage3D);
LOAD_OPENGL_FUNCTIONS(PFNGLTEXSUBIMAGE3DPROC, glTexSubImage3D);
LOAD_OPENGL_FUNCTIONS(PFNGLCOPYTEXSUBIMAGE3DPROC, glCopyTexSubImage3D);

#define LOAD_OPENGL_FUNCTIONS_1_3
LOAD_OPENGL_FUNCTIONS(PFNGLACTIVETEXTUREPROC, glActiveTexture);
LOAD_OPENGL_FUNCTIONS(PFNGLSAMPLECOVERAGEPROC, glSampleCoverage);
LOAD_OPENGL_FUNCTIONS(PFNGLCOMPRESSEDTEXIMAGE3DPROC, glCompressedTexImage3D);
LOAD_OPENGL_FUNCTIONS(PFNGLCOMPRESSEDTEXIMAGE2DPROC, glCompressedTexImage2D);
LOAD_OPENGL_FUNCTIONS(PFNGLCOMPRESSEDTEXIMAGE1DPROC, glCompressedTexImage1D);
LOAD_OPENGL_FUNCTIONS(PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC, glCompressedTexSubImage3D);
LOAD_OPENGL_FUNCTIONS(PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC, glCompressedTexSubImage2D);
LOAD_OPENGL_FUNCTIONS(PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC, glCompressedTexSubImage1D);
LOAD_OPENGL_FUNCTIONS(PFNGLGETCOMPRESSEDTEXIMAGEPROC, glGetCompressedTexImage);

#define LOAD_OPENGL_FUNCTIONS_1_4
LOAD_OPENGL_FUNCTIONS(PFNGLBLENDFUNCSEPARATEPROC, glBlendFuncSeparate);
LOAD_OPENGL_FUNCTIONS(PFNGLMULTIDRAWARRAYSPROC, glMultiDrawArrays);
LOAD_OPENGL_FUNCTIONS(PFNGLMULTIDRAWELEMENTSPROC, glMultiDrawElements);
LOAD_OPENGL_FUNCTIONS(PFNGLPOINTPARAMETERFPROC, glPointParameterf);
LOAD_OPENGL_FUNCTIONS(PFNGLPOINTPARAMETERFVPROC, glPointParameterfv);
LOAD_OPENGL_FUNCTIONS(PFNGLPOINTPARAMETERIPROC, glPointParameteri);
LOAD_OPENGL_FUNCTIONS(PFNGLPOINTPARAMETERIVPROC, glPointParameteriv);
LOAD_OPENGL_FUNCTIONS(PFNGLBLENDCOLORPROC, glBlendColor);
LOAD_OPENGL_FUNCTIONS(PFNGLBLENDEQUATIONPROC, glBlendEquation);

#define LOAD_OPENGL_FUNCTIONS_1_5
LOAD_OPENGL_FUNCTIONS(PFNGLGENQUERIESPROC, glGenQueries);
LOAD_OPENGL_FUNCTIONS(PFNGLDELETEQUERIESPROC, glDeleteQueries);
LOAD_OPENGL_FUNCTIONS(PFNGLISQUERYPROC, glIsQuery);
LOAD_OPENGL_FUNCTIONS(PFNGLBEGINQUERYPROC, glBeginQuery);
LOAD_OPENGL_FUNCTIONS(PFNGLENDQUERYPROC, glEndQuery);
LOAD_OPENGL_FUNCTIONS(PFNGLGETQUERYIVPROC, glGetQueryiv);
LOAD_OPENGL_FUNCTIONS(PFNGLGETQUERYOBJECTIVPROC, glGetQueryObjectiv);
LOAD_OPENGL_FUNCTIONS(PFNGLGETQUERYOBJECTUIVPROC, glGetQueryObjectuiv);
LOAD_OPENGL_FUNCTIONS(PFNGLBINDBUFFERPROC, glBindBuffer);
LOAD_OPENGL_FUNCTIONS(PFNGLDELETEBUFFERSPROC, glDeleteBuffers);
LOAD_OPENGL_FUNCTIONS(PFNGLGENBUFFERSPROC, glGenBuffers);
LOAD_OPENGL_FUNCTIONS(PFNGLISBUFFERPROC, glIsBuffer);
LOAD_OPENGL_FUNCTIONS(PFNGLBUFFERDATAPROC, glBufferData);
LOAD_OPENGL_FUNCTIONS(PFNGLBUFFERSUBDATAPROC, glBufferSubData);
LOAD_OPENGL_FUNCTIONS(PFNGLGETBUFFERSUBDATAPROC, glGetBufferSubData);
LOAD_OPENGL_FUNCTIONS(PFNGLMAPBUFFERPROC, glMapBuffer);
LOAD_OPENGL_FUNCTIONS(PFNGLUNMAPBUFFERPROC, glUnmapBuffer);
LOAD_OPENGL_FUNCTIONS(PFNGLGETBUFFERPARAMETERIVPROC, glGetBufferParameteriv);
LOAD_OPENGL_FUNCTIONS(PFNGLGETBUFFERPOINTERVPROC, glGetBufferPointerv);

#define LOAD_OPENGL_FUNCTIONS_2_0
LOAD_OPENGL_FUNCTIONS(PFNGLBLENDEQUATIONSEPARATEPROC, glBlendEquationSeparate);
LOAD_OPENGL_FUNCTIONS(PFNGLDRAWBUFFERSPROC, glDrawBuffers);
LOAD_OPENGL_FUNCTIONS(PFNGLSTENCILOPSEPARATEPROC, glStencilOpSeparate);
LOAD_OPENGL_FUNCTIONS(PFNGLSTENCILFUNCSEPARATEPROC, glStencilFuncSeparate);
LOAD_OPENGL_FUNCTIONS(PFNGLSTENCILMASKSEPARATEPROC, glStencilMaskSeparate);
LOAD_OPENGL_FUNCTIONS(PFNGLATTACHSHADERPROC, glAttachShader);
LOAD_OPENGL_FUNCTIONS(PFNGLBINDATTRIBLOCATIONPROC, glBindAttribLocation);
LOAD_OPENGL_FUNCTIONS(PFNGLCOMPILESHADERPROC, glCompileShader);
LOAD_OPENGL_FUNCTIONS(PFNGLCREATEPROGRAMPROC, glCreateProgram);
LOAD_OPENGL_FUNCTIONS(PFNGLCREATESHADERPROC, glCreateShader);
LOAD_OPENGL_FUNCTIONS(PFNGLDELETEPROGRAMPROC, glDeleteProgram);
LOAD_OPENGL_FUNCTIONS(PFNGLDELETESHADERPROC, glDeleteShader);
LOAD_OPENGL_FUNCTIONS(PFNGLDETACHSHADERPROC, glDetachShader);
LOAD_OPENGL_FUNCTIONS(PFNGLDISABLEVERTEXATTRIBARRAYPROC, glDisableVertexAttribArray);
LOAD_OPENGL_FUNCTIONS(PFNGLENABLEVERTEXATTRIBARRAYPROC, glEnableVertexAttribArray);
LOAD_OPENGL_FUNCTIONS(PFNGLGETACTIVEATTRIBPROC, glGetActiveAttrib);
LOAD_OPENGL_FUNCTIONS(PFNGLGETACTIVEUNIFORMPROC, glGetActiveUniform);
LOAD_OPENGL_FUNCTIONS(PFNGLGETATTACHEDSHADERSPROC, glGetAttachedShaders);
LOAD_OPENGL_FUNCTIONS(PFNGLGETATTRIBLOCATIONPROC, glGetAttribLocation);
LOAD_OPENGL_FUNCTIONS(PFNGLGETPROGRAMIVPROC, glGetProgramiv);
LOAD_OPENGL_FUNCTIONS(PFNGLGETPROGRAMINFOLOGPROC, glGetProgramInfoLog);
LOAD_OPENGL_FUNCTIONS(PFNGLGETSHADERIVPROC, glGetShaderiv);
LOAD_OPENGL_FUNCTIONS(PFNGLGETSHADERINFOLOGPROC, glGetShaderInfoLog);
LOAD_OPENGL_FUNCTIONS(PFNGLGETSHADERSOURCEPROC, glGetShaderSource);
LOAD_OPENGL_FUNCTIONS(PFNGLGETUNIFORMLOCATIONPROC, glGetUniformLocation);
LOAD_OPENGL_FUNCTIONS(PFNGLGETUNIFORMFVPROC, glGetUniformfv);
LOAD_OPENGL_FUNCTIONS(PFNGLGETUNIFORMIVPROC, glGetUniformiv);
LOAD_OPENGL_FUNCTIONS(PFNGLGETVERTEXATTRIBDVPROC, glGetVertexAttribdv);
LOAD_OPENGL_FUNCTIONS(PFNGLGETVERTEXATTRIBFVPROC, glGetVertexAttribfv);
LOAD_OPENGL_FUNCTIONS(PFNGLGETVERTEXATTRIBIVPROC, glGetVertexAttribiv);
LOAD_OPENGL_FUNCTIONS(PFNGLGETVERTEXATTRIBPOINTERVPROC, glGetVertexAttribPointerv);
LOAD_OPENGL_FUNCTIONS(PFNGLISPROGRAMPROC, glIsProgram);
LOAD_OPENGL_FUNCTIONS(PFNGLISSHADERPROC, glIsShader);
LOAD_OPENGL_FUNCTIONS(PFNGLLINKPROGRAMPROC, glLinkProgram);
LOAD_OPENGL_FUNCTIONS(PFNGLSHADERSOURCEPROC, glShaderSource);
LOAD_OPENGL_FUNCTIONS(PFNGLUSEPROGRAMPROC, glUseProgram);
LOAD_OPENGL_FUNCTIONS(PFNGLUNIFORM1FPROC, glUniform1f);
LOAD_OPENGL_FUNCTIONS(PFNGLUNIFORM2FPROC, glUniform2f);
LOAD_OPENGL_FUNCTIONS(PFNGLUNIFORM3FPROC, glUniform3f);
LOAD_OPENGL_FUNCTIONS(PFNGLUNIFORM4FPROC, glUniform4f);
LOAD_OPENGL_FUNCTIONS(PFNGLUNIFORM1IPROC, glUniform1i);
LOAD_OPENGL_FUNCTIONS(PFNGLUNIFORM2IPROC, glUniform2i);
LOAD_OPENGL_FUNCTIONS(PFNGLUNIFORM3IPROC, glUniform3i);
LOAD_OPENGL_FUNCTIONS(PFNGLUNIFORM4IPROC, glUniform4i);
LOAD_OPENGL_FUNCTIONS(PFNGLUNIFORM1FVPROC, glUniform1fv);
LOAD_OPENGL_FUNCTIONS(PFNGLUNIFORM2FVPROC, glUniform2fv);
LOAD_OPENGL_FUNCTIONS(PFNGLUNIFORM3FVPROC, glUniform3fv);
LOAD_OPENGL_FUNCTIONS(PFNGLUNIFORM4FVPROC, glUniform4fv);
LOAD_OPENGL_FUNCTIONS(PFNGLUNIFORM1IVPROC, glUniform1iv);
LOAD_OPENGL_FUNCTIONS(PFNGLUNIFORM2IVPROC, glUniform2iv);
LOAD_OPENGL_FUNCTIONS(PFNGLUNIFORM3IVPROC, glUniform3iv);
LOAD_OPENGL_FUNCTIONS(PFNGLUNIFORM4IVPROC, glUniform4iv);
LOAD_OPENGL_FUNCTIONS(PFNGLUNIFORMMATRIX2FVPROC, glUniformMatrix2fv);
LOAD_OPENGL_FUNCTIONS(PFNGLUNIFORMMATRIX3FVPROC, glUniformMatrix3fv);
LOAD_OPENGL_FUNCTIONS(PFNGLUNIFORMMATRIX4FVPROC, glUniformMatrix4fv);
LOAD_OPENGL_FUNCTIONS(PFNGLVALIDATEPROGRAMPROC, glValidateProgram);
LOAD_OPENGL_FUNCTIONS(PFNGLVERTEXATTRIB1DPROC, glVertexAttrib1d);
LOAD_OPENGL_FUNCTIONS(PFNGLVERTEXATTRIB1DVPROC, glVertexAttrib1dv);
LOAD_OPENGL_FUNCTIONS(PFNGLVERTEXATTRIB1FPROC, glVertexAttrib1f);
LOAD_OPENGL_FUNCTIONS(PFNGLVERTEXATTRIB1FVPROC, glVertexAttrib1fv);
LOAD_OPENGL_FUNCTIONS(PFNGLVERTEXATTRIB1SPROC, glVertexAttrib1s);
LOAD_OPENGL_FUNCTIONS(PFNGLVERTEXATTRIB1SVPROC, glVertexAttrib1sv);
LOAD_OPENGL_FUNCTIONS(PFNGLVERTEXATTRIB2DPROC, glVertexAttrib2d);
LOAD_OPENGL_FUNCTIONS(PFNGLVERTEXATTRIB2DVPROC, glVertexAttrib2dv);
LOAD_OPENGL_FUNCTIONS(PFNGLVERTEXATTRIB2FPROC, glVertexAttrib2f);
LOAD_OPENGL_FUNCTIONS(PFNGLVERTEXATTRIB2FVPROC, glVertexAttrib2fv);
LOAD_OPENGL_FUNCTIONS(PFNGLVERTEXATTRIB2SPROC, glVertexAttrib2s);
LOAD_OPENGL_FUNCTIONS(PFNGLVERTEXATTRIB2SVPROC, glVertexAttrib2sv);
LOAD_OPENGL_FUNCTIONS(PFNGLVERTEXATTRIB3DPROC, glVertexAttrib3d);
LOAD_OPENGL_FUNCTIONS(PFNGLVERTEXATTRIB3DVPROC, glVertexAttrib3dv);
LOAD_OPENGL_FUNCTIONS(PFNGLVERTEXATTRIB3FPROC, glVertexAttrib3f);
LOAD_OPENGL_FUNCTIONS(PFNGLVERTEXATTRIB3FVPROC, glVertexAttrib3fv);
LOAD_OPENGL_FUNCTIONS(PFNGLVERTEXATTRIB3SPROC, glVertexAttrib3s);
LOAD_OPENGL_FUNCTIONS(PFNGLVERTEXATTRIB3SVPROC, glVertexAttrib3sv);
LOAD_OPENGL_FUNCTIONS(PFNGLVERTEXATTRIB4NBVPROC, glVertexAttrib4Nbv);
LOAD_OPENGL_FUNCTIONS(PFNGLVERTEXATTRIB4NIVPROC, glVertexAttrib4Niv);
LOAD_OPENGL_FUNCTIONS(PFNGLVERTEXATTRIB4NSVPROC, glVertexAttrib4Nsv);
LOAD_OPENGL_FUNCTIONS(PFNGLVERTEXATTRIB4NUBPROC, glVertexAttrib4Nub);
LOAD_OPENGL_FUNCTIONS(PFNGLVERTEXATTRIB4NUBVPROC, glVertexAttrib4Nubv);
LOAD_OPENGL_FUNCTIONS(PFNGLVERTEXATTRIB4NUIVPROC, glVertexAttrib4Nuiv);
LOAD_OPENGL_FUNCTIONS(PFNGLVERTEXATTRIB4NUSVPROC, glVertexAttrib4Nusv);
LOAD_OPENGL_FUNCTIONS(PFNGLVERTEXATTRIB4BVPROC, glVertexAttrib4bv);
LOAD_OPENGL_FUNCTIONS(PFNGLVERTEXATTRIB4DPROC, glVertexAttrib4d);
LOAD_OPENGL_FUNCTIONS(PFNGLVERTEXATTRIB4DVPROC, glVertexAttrib4dv);
LOAD_OPENGL_FUNCTIONS(PFNGLVERTEXATTRIB4FPROC, glVertexAttrib4f);
LOAD_OPENGL_FUNCTIONS(PFNGLVERTEXATTRIB4FVPROC, glVertexAttrib4fv);
LOAD_OPENGL_FUNCTIONS(PFNGLVERTEXATTRIB4IVPROC, glVertexAttrib4iv);
LOAD_OPENGL_FUNCTIONS(PFNGLVERTEXATTRIB4SPROC, glVertexAttrib4s);
LOAD_OPENGL_FUNCTIONS(PFNGLVERTEXATTRIB4SVPROC, glVertexAttrib4sv);
LOAD_OPENGL_FUNCTIONS(PFNGLVERTEXATTRIB4UBVPROC, glVertexAttrib4ubv);
LOAD_OPENGL_FUNCTIONS(PFNGLVERTEXATTRIB4UIVPROC, glVertexAttrib4uiv);
LOAD_OPENGL_FUNCTIONS(PFNGLVERTEXATTRIB4USVPROC, glVertexAttrib4usv);
LOAD_OPENGL_FUNCTIONS(PFNGLVERTEXATTRIBPOINTERPROC, glVertexAttribPointer);

#define LOAD_OPENGL_FUNCTIONS_2_1
LOAD_OPENGL_FUNCTIONS(PFNGLUNIFORMMATRIX2X3FVPROC, glUniformMatrix2x3fv);
LOAD_OPENGL_FUNCTIONS(PFNGLUNIFORMMATRIX3X2FVPROC, glUniformMatrix3x2fv);
LOAD_OPENGL_FUNCTIONS(PFNGLUNIFORMMATRIX2X4FVPROC, glUniformMatrix2x4fv);
LOAD_OPENGL_FUNCTIONS(PFNGLUNIFORMMATRIX4X2FVPROC, glUniformMatrix4x2fv);
LOAD_OPENGL_FUNCTIONS(PFNGLUNIFORMMATRIX3X4FVPROC, glUniformMatrix3x4fv);
LOAD_OPENGL_FUNCTIONS(PFNGLUNIFORMMATRIX4X3FVPROC, glUniformMatrix4x3fv);

#define LOAD_OPENGL_FUNCTIONS_3_0
LOAD_OPENGL_FUNCTIONS(PFNGLCOLORMASKIPROC, glColorMaski);
LOAD_OPENGL_FUNCTIONS(PFNGLGETBOOLEANI_VPROC, glGetBooleani_v);
LOAD_OPENGL_FUNCTIONS(PFNGLGETINTEGERI_VPROC, glGetIntegeri_v);
LOAD_OPENGL_FUNCTIONS(PFNGLENABLEIPROC, glEnablei);
LOAD_OPENGL_FUNCTIONS(PFNGLDISABLEIPROC, glDisablei);
LOAD_OPENGL_FUNCTIONS(PFNGLISENABLEDIPROC, glIsEnabledi);
LOAD_OPENGL_FUNCTIONS(PFNGLBEGINTRANSFORMFEEDBACKPROC, glBeginTransformFeedback);
LOAD_OPENGL_FUNCTIONS(PFNGLENDTRANSFORMFEEDBACKPROC, glEndTransformFeedback);
LOAD_OPENGL_FUNCTIONS(PFNGLBINDBUFFERRANGEPROC, glBindBufferRange);
LOAD_OPENGL_FUNCTIONS(PFNGLBINDBUFFERBASEPROC, glBindBufferBase);
LOAD_OPENGL_FUNCTIONS(PFNGLTRANSFORMFEEDBACKVARYINGSPROC, glTransformFeedbackVaryings);
LOAD_OPENGL_FUNCTIONS(PFNGLGETTRANSFORMFEEDBACKVARYINGPROC, glGetTransformFeedbackVarying);
LOAD_OPENGL_FUNCTIONS(PFNGLCLAMPCOLORPROC, glClampColor);
LOAD_OPENGL_FUNCTIONS(PFNGLBEGINCONDITIONALRENDERPROC, glBeginConditionalRender);
LOAD_OPENGL_FUNCTIONS(PFNGLENDCONDITIONALRENDERPROC, glEndConditionalRender);
LOAD_OPENGL_FUNCTIONS(PFNGLVERTEXATTRIBIPOINTERPROC, glVertexAttribIPointer);
LOAD_OPENGL_FUNCTIONS(PFNGLGETVERTEXATTRIBIIVPROC, glGetVertexAttribIiv);
LOAD_OPENGL_FUNCTIONS(PFNGLGETVERTEXATTRIBIUIVPROC, glGetVertexAttribIuiv);
LOAD_OPENGL_FUNCTIONS(PFNGLVERTEXATTRIBI1IPROC, glVertexAttribI1i);
LOAD_OPENGL_FUNCTIONS(PFNGLVERTEXATTRIBI2IPROC, glVertexAttribI2i);
LOAD_OPENGL_FUNCTIONS(PFNGLVERTEXATTRIBI3IPROC, glVertexAttribI3i);
LOAD_OPENGL_FUNCTIONS(PFNGLVERTEXATTRIBI4IPROC, glVertexAttribI4i);
LOAD_OPENGL_FUNCTIONS(PFNGLVERTEXATTRIBI1UIPROC, glVertexAttribI1ui);
LOAD_OPENGL_FUNCTIONS(PFNGLVERTEXATTRIBI2UIPROC, glVertexAttribI2ui);
LOAD_OPENGL_FUNCTIONS(PFNGLVERTEXATTRIBI3UIPROC, glVertexAttribI3ui);
LOAD_OPENGL_FUNCTIONS(PFNGLVERTEXATTRIBI4UIPROC, glVertexAttribI4ui);
LOAD_OPENGL_FUNCTIONS(PFNGLVERTEXATTRIBI1IVPROC, glVertexAttribI1iv);
LOAD_OPENGL_FUNCTIONS(PFNGLVERTEXATTRIBI2IVPROC, glVertexAttribI2iv);
LOAD_OPENGL_FUNCTIONS(PFNGLVERTEXATTRIBI3IVPROC, glVertexAttribI3iv);
LOAD_OPENGL_FUNCTIONS(PFNGLVERTEXATTRIBI4IVPROC, glVertexAttribI4iv);
LOAD_OPENGL_FUNCTIONS(PFNGLVERTEXATTRIBI1UIVPROC, glVertexAttribI1uiv);
LOAD_OPENGL_FUNCTIONS(PFNGLVERTEXATTRIBI2UIVPROC, glVertexAttribI2uiv);
LOAD_OPENGL_FUNCTIONS(PFNGLVERTEXATTRIBI3UIVPROC, glVertexAttribI3uiv);
LOAD_OPENGL_FUNCTIONS(PFNGLVERTEXATTRIBI4UIVPROC, glVertexAttribI4uiv);
LOAD_OPENGL_FUNCTIONS(PFNGLVERTEXATTRIBI4BVPROC, glVertexAttribI4bv);
LOAD_OPENGL_FUNCTIONS(PFNGLVERTEXATTRIBI4SVPROC, glVertexAttribI4sv);
LOAD_OPENGL_FUNCTIONS(PFNGLVERTEXATTRIBI4UBVPROC, glVertexAttribI4ubv);
LOAD_OPENGL_FUNCTIONS(PFNGLVERTEXATTRIBI4USVPROC, glVertexAttribI4usv);
LOAD_OPENGL_FUNCTIONS(PFNGLGETUNIFORMUIVPROC, glGetUniformuiv);
LOAD_OPENGL_FUNCTIONS(PFNGLBINDFRAGDATALOCATIONPROC, glBindFragDataLocation);
LOAD_OPENGL_FUNCTIONS(PFNGLGETFRAGDATALOCATIONPROC, glGetFragDataLocation);
LOAD_OPENGL_FUNCTIONS(PFNGLUNIFORM1UIPROC, glUniform1ui);
LOAD_OPENGL_FUNCTIONS(PFNGLUNIFORM2UIPROC, glUniform2ui);
LOAD_OPENGL_FUNCTIONS(PFNGLUNIFORM3UIPROC, glUniform3ui);
LOAD_OPENGL_FUNCTIONS(PFNGLUNIFORM4UIPROC, glUniform4ui);
LOAD_OPENGL_FUNCTIONS(PFNGLUNIFORM1UIVPROC, glUniform1uiv);
LOAD_OPENGL_FUNCTIONS(PFNGLUNIFORM2UIVPROC, glUniform2uiv);
LOAD_OPENGL_FUNCTIONS(PFNGLUNIFORM3UIVPROC, glUniform3uiv);
LOAD_OPENGL_FUNCTIONS(PFNGLUNIFORM4UIVPROC, glUniform4uiv);
LOAD_OPENGL_FUNCTIONS(PFNGLTEXPARAMETERIIVPROC, glTexParameterIiv);
LOAD_OPENGL_FUNCTIONS(PFNGLTEXPARAMETERIUIVPROC, glTexParameterIuiv);
LOAD_OPENGL_FUNCTIONS(PFNGLGETTEXPARAMETERIIVPROC, glGetTexParameterIiv);
LOAD_OPENGL_FUNCTIONS(PFNGLGETTEXPARAMETERIUIVPROC, glGetTexParameterIuiv);
LOAD_OPENGL_FUNCTIONS(PFNGLCLEARBUFFERIVPROC, glClearBufferiv);
LOAD_OPENGL_FUNCTIONS(PFNGLCLEARBUFFERUIVPROC, glClearBufferuiv);
LOAD_OPENGL_FUNCTIONS(PFNGLCLEARBUFFERFVPROC, glClearBufferfv);
LOAD_OPENGL_FUNCTIONS(PFNGLCLEARBUFFERFIPROC, glClearBufferfi);
LOAD_OPENGL_FUNCTIONS(PFNGLGETSTRINGIPROC, glGetStringi);
LOAD_OPENGL_FUNCTIONS(PFNGLISRENDERBUFFERPROC, glIsRenderbuffer);
LOAD_OPENGL_FUNCTIONS(PFNGLBINDRENDERBUFFERPROC, glBindRenderbuffer);
LOAD_OPENGL_FUNCTIONS(PFNGLDELETERENDERBUFFERSPROC, glDeleteRenderbuffers);
LOAD_OPENGL_FUNCTIONS(PFNGLGENRENDERBUFFERSPROC, glGenRenderbuffers);
LOAD_OPENGL_FUNCTIONS(PFNGLRENDERBUFFERSTORAGEPROC, glRenderbufferStorage);
LOAD_OPENGL_FUNCTIONS(PFNGLGETRENDERBUFFERPARAMETERIVPROC, glGetRenderbufferParameteriv);
LOAD_OPENGL_FUNCTIONS(PFNGLISFRAMEBUFFERPROC, glIsFramebuffer);
LOAD_OPENGL_FUNCTIONS(PFNGLBINDFRAMEBUFFERPROC, glBindFramebuffer);
LOAD_OPENGL_FUNCTIONS(PFNGLDELETEFRAMEBUFFERSPROC, glDeleteFramebuffers);
LOAD_OPENGL_FUNCTIONS(PFNGLGENFRAMEBUFFERSPROC, glGenFramebuffers);
LOAD_OPENGL_FUNCTIONS(PFNGLCHECKFRAMEBUFFERSTATUSPROC, glCheckFramebufferStatus);
LOAD_OPENGL_FUNCTIONS(PFNGLFRAMEBUFFERTEXTURE1DPROC, glFramebufferTexture1D);
LOAD_OPENGL_FUNCTIONS(PFNGLFRAMEBUFFERTEXTURE2DPROC, glFramebufferTexture2D);
LOAD_OPENGL_FUNCTIONS(PFNGLFRAMEBUFFERTEXTURE3DPROC, glFramebufferTexture3D);
LOAD_OPENGL_FUNCTIONS(PFNGLFRAMEBUFFERRENDERBUFFERPROC, glFramebufferRenderbuffer);
LOAD_OPENGL_FUNCTIONS(PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC, glGetFramebufferAttachmentParameteriv);
LOAD_OPENGL_FUNCTIONS(PFNGLGENERATEMIPMAPPROC, glGenerateMipmap);
LOAD_OPENGL_FUNCTIONS(PFNGLBLITFRAMEBUFFERPROC, glBlitFramebuffer);
LOAD_OPENGL_FUNCTIONS(PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC, glRenderbufferStorageMultisample);
LOAD_OPENGL_FUNCTIONS(PFNGLFRAMEBUFFERTEXTURELAYERPROC, glFramebufferTextureLayer);
LOAD_OPENGL_FUNCTIONS(PFNGLMAPBUFFERRANGEPROC, glMapBufferRange);
LOAD_OPENGL_FUNCTIONS(PFNGLFLUSHMAPPEDBUFFERRANGEPROC, glFlushMappedBufferRange);
LOAD_OPENGL_FUNCTIONS(PFNGLBINDVERTEXARRAYPROC, glBindVertexArray);
LOAD_OPENGL_FUNCTIONS(PFNGLDELETEVERTEXARRAYSPROC, glDeleteVertexArrays);
LOAD_OPENGL_FUNCTIONS(PFNGLGENVERTEXARRAYSPROC, glGenVertexArrays);
LOAD_OPENGL_FUNCTIONS(PFNGLISVERTEXARRAYPROC, glIsVertexArray);

#define LOAD_OPENGL_FUNCTIONS_3_1
LOAD_OPENGL_FUNCTIONS(PFNGLDRAWARRAYSINSTANCEDPROC, glDrawArraysInstanced);
LOAD_OPENGL_FUNCTIONS(PFNGLDRAWELEMENTSINSTANCEDPROC, glDrawElementsInstanced);
LOAD_OPENGL_FUNCTIONS(PFNGLTEXBUFFERPROC, glTexBuffer);
LOAD_OPENGL_FUNCTIONS(PFNGLPRIMITIVERESTARTINDEXPROC, glPrimitiveRestartIndex);
LOAD_OPENGL_FUNCTIONS(PFNGLCOPYBUFFERSUBDATAPROC, glCopyBufferSubData);
LOAD_OPENGL_FUNCTIONS(PFNGLGETUNIFORMINDICESPROC, glGetUniformIndices);
LOAD_OPENGL_FUNCTIONS(PFNGLGETACTIVEUNIFORMSIVPROC, glGetActiveUniformsiv);
LOAD_OPENGL_FUNCTIONS(PFNGLGETACTIVEUNIFORMNAMEPROC, glGetActiveUniformName);
LOAD_OPENGL_FUNCTIONS(PFNGLGETUNIFORMBLOCKINDEXPROC, glGetUniformBlockIndex);
LOAD_OPENGL_FUNCTIONS(PFNGLGETACTIVEUNIFORMBLOCKIVPROC, glGetActiveUniformBlockiv);
LOAD_OPENGL_FUNCTIONS(PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC, glGetActiveUniformBlockName);
LOAD_OPENGL_FUNCTIONS(PFNGLUNIFORMBLOCKBINDINGPROC, glUniformBlockBinding);

#define LOAD_OPENGL_FUNCTION_3_2
LOAD_OPENGL_FUNCTIONS(PFNGLDRAWELEMENTSBASEVERTEXPROC, glDrawElementsBaseVertex);
LOAD_OPENGL_FUNCTIONS(PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC, glDrawRangeElementsBaseVertex);
LOAD_OPENGL_FUNCTIONS(PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC, glDrawElementsInstancedBaseVertex);
LOAD_OPENGL_FUNCTIONS(PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC, glMultiDrawElementsBaseVertex);
LOAD_OPENGL_FUNCTIONS(PFNGLPROVOKINGVERTEXPROC, glProvokingVertex);
LOAD_OPENGL_FUNCTIONS(PFNGLFENCESYNCPROC, glFenceSync);
LOAD_OPENGL_FUNCTIONS(PFNGLISSYNCPROC, glIsSync);
LOAD_OPENGL_FUNCTIONS(PFNGLDELETESYNCPROC, glDeleteSync);
LOAD_OPENGL_FUNCTIONS(PFNGLCLIENTWAITSYNCPROC, glClientWaitSync);
LOAD_OPENGL_FUNCTIONS(PFNGLWAITSYNCPROC, glWaitSync);
LOAD_OPENGL_FUNCTIONS(PFNGLGETINTEGER64VPROC, glGetInteger64v);
LOAD_OPENGL_FUNCTIONS(PFNGLGETSYNCIVPROC, glGetSynciv);
LOAD_OPENGL_FUNCTIONS(PFNGLGETINTEGER64I_VPROC, glGetInteger64i_v);
LOAD_OPENGL_FUNCTIONS(PFNGLGETBUFFERPARAMETERI64VPROC, glGetBufferParameteri64v);
LOAD_OPENGL_FUNCTIONS(PFNGLFRAMEBUFFERTEXTUREPROC, glFramebufferTexture);
LOAD_OPENGL_FUNCTIONS(PFNGLTEXIMAGE2DMULTISAMPLEPROC, glTexImage2DMultisample);
LOAD_OPENGL_FUNCTIONS(PFNGLTEXIMAGE3DMULTISAMPLEPROC, glTexImage3DMultisample);
LOAD_OPENGL_FUNCTIONS(PFNGLGETMULTISAMPLEFVPROC, glGetMultisamplefv);
LOAD_OPENGL_FUNCTIONS(PFNGLSAMPLEMASKIPROC, glSampleMaski);

#define LOAD_OPENGL_FUNCTIONS_3_3
LOAD_OPENGL_FUNCTIONS(PFNGLBINDFRAGDATALOCATIONINDEXEDPROC, glBindFragDataLocationIndexed);
LOAD_OPENGL_FUNCTIONS(PFNGLGETFRAGDATAINDEXPROC, glGetFragDataIndex);
LOAD_OPENGL_FUNCTIONS(PFNGLGENSAMPLERSPROC, glGenSamplers);
LOAD_OPENGL_FUNCTIONS(PFNGLDELETESAMPLERSPROC, glDeleteSamplers);
LOAD_OPENGL_FUNCTIONS(PFNGLISSAMPLERPROC, glIsSampler);
LOAD_OPENGL_FUNCTIONS(PFNGLBINDSAMPLERPROC, glBindSampler);
LOAD_OPENGL_FUNCTIONS(PFNGLSAMPLERPARAMETERIPROC, glSamplerParameteri);
LOAD_OPENGL_FUNCTIONS(PFNGLSAMPLERPARAMETERIVPROC, glSamplerParameteriv);
LOAD_OPENGL_FUNCTIONS(PFNGLSAMPLERPARAMETERFPROC, glSamplerParameterf);
LOAD_OPENGL_FUNCTIONS(PFNGLSAMPLERPARAMETERFVPROC, glSamplerParameterfv);
LOAD_OPENGL_FUNCTIONS(PFNGLSAMPLERPARAMETERIIVPROC, glSamplerParameterIiv);
LOAD_OPENGL_FUNCTIONS(PFNGLSAMPLERPARAMETERIUIVPROC, glSamplerParameterIuiv);
LOAD_OPENGL_FUNCTIONS(PFNGLGETSAMPLERPARAMETERIVPROC, glGetSamplerParameteriv);
LOAD_OPENGL_FUNCTIONS(PFNGLGETSAMPLERPARAMETERIIVPROC, glGetSamplerParameterIiv);
LOAD_OPENGL_FUNCTIONS(PFNGLGETSAMPLERPARAMETERFVPROC, glGetSamplerParameterfv);
LOAD_OPENGL_FUNCTIONS(PFNGLGETSAMPLERPARAMETERIUIVPROC, glGetSamplerParameterIuiv);
LOAD_OPENGL_FUNCTIONS(PFNGLQUERYCOUNTERPROC, glQueryCounter);
LOAD_OPENGL_FUNCTIONS(PFNGLGETQUERYOBJECTI64VPROC, glGetQueryObjecti64v);
LOAD_OPENGL_FUNCTIONS(PFNGLGETQUERYOBJECTUI64VPROC, glGetQueryObjectui64v);
LOAD_OPENGL_FUNCTIONS(PFNGLVERTEXATTRIBDIVISORPROC, glVertexAttribDivisor);
LOAD_OPENGL_FUNCTIONS(PFNGLVERTEXATTRIBP1UIPROC, glVertexAttribP1ui);
LOAD_OPENGL_FUNCTIONS(PFNGLVERTEXATTRIBP1UIVPROC, glVertexAttribP1uiv);
LOAD_OPENGL_FUNCTIONS(PFNGLVERTEXATTRIBP2UIPROC, glVertexAttribP2ui);
LOAD_OPENGL_FUNCTIONS(PFNGLVERTEXATTRIBP2UIVPROC, glVertexAttribP2uiv);
LOAD_OPENGL_FUNCTIONS(PFNGLVERTEXATTRIBP3UIPROC, glVertexAttribP3ui);
LOAD_OPENGL_FUNCTIONS(PFNGLVERTEXATTRIBP3UIVPROC, glVertexAttribP3uiv);
LOAD_OPENGL_FUNCTIONS(PFNGLVERTEXATTRIBP4UIPROC, glVertexAttribP4ui);
LOAD_OPENGL_FUNCTIONS(PFNGLVERTEXATTRIBP4UIVPROC, glVertexAttribP4uiv);

#define LOAD_OPENGL_FUNCTION_4_0
LOAD_OPENGL_FUNCTIONS(PFNGLMINSAMPLESHADINGPROC, glMinSampleShading);
LOAD_OPENGL_FUNCTIONS(PFNGLBLENDEQUATIONIPROC, glBlendEquationi);
LOAD_OPENGL_FUNCTIONS(PFNGLBLENDEQUATIONSEPARATEIPROC, glBlendEquationSeparatei);
LOAD_OPENGL_FUNCTIONS(PFNGLBLENDFUNCIPROC, glBlendFunci);
LOAD_OPENGL_FUNCTIONS(PFNGLBLENDFUNCSEPARATEIPROC, glBlendFuncSeparatei);
LOAD_OPENGL_FUNCTIONS(PFNGLDRAWARRAYSINDIRECTPROC, glDrawArraysIndirect);
LOAD_OPENGL_FUNCTIONS(PFNGLDRAWELEMENTSINDIRECTPROC, glDrawElementsIndirect);
LOAD_OPENGL_FUNCTIONS(PFNGLUNIFORM1DPROC, glUniform1d);
LOAD_OPENGL_FUNCTIONS(PFNGLUNIFORM2DPROC, glUniform2d);
LOAD_OPENGL_FUNCTIONS(PFNGLUNIFORM3DPROC, glUniform3d);
LOAD_OPENGL_FUNCTIONS(PFNGLUNIFORM4DPROC, glUniform4d);
LOAD_OPENGL_FUNCTIONS(PFNGLUNIFORM1DVPROC, glUniform1dv);
LOAD_OPENGL_FUNCTIONS(PFNGLUNIFORM2DVPROC, glUniform2dv);
LOAD_OPENGL_FUNCTIONS(PFNGLUNIFORM3DVPROC, glUniform3dv);
LOAD_OPENGL_FUNCTIONS(PFNGLUNIFORM4DVPROC, glUniform4dv);
LOAD_OPENGL_FUNCTIONS(PFNGLUNIFORMMATRIX2DVPROC, glUniformMatrix2dv);
LOAD_OPENGL_FUNCTIONS(PFNGLUNIFORMMATRIX3DVPROC, glUniformMatrix3dv);
LOAD_OPENGL_FUNCTIONS(PFNGLUNIFORMMATRIX4DVPROC, glUniformMatrix4dv);
LOAD_OPENGL_FUNCTIONS(PFNGLUNIFORMMATRIX2X3DVPROC, glUniformMatrix2x3dv);
LOAD_OPENGL_FUNCTIONS(PFNGLUNIFORMMATRIX2X4DVPROC, glUniformMatrix2x4dv);
LOAD_OPENGL_FUNCTIONS(PFNGLUNIFORMMATRIX3X2DVPROC, glUniformMatrix3x2dv);
LOAD_OPENGL_FUNCTIONS(PFNGLUNIFORMMATRIX3X4DVPROC, glUniformMatrix3x4dv);
LOAD_OPENGL_FUNCTIONS(PFNGLUNIFORMMATRIX4X2DVPROC, glUniformMatrix4x2dv);
LOAD_OPENGL_FUNCTIONS(PFNGLUNIFORMMATRIX4X3DVPROC, glUniformMatrix4x3dv);
LOAD_OPENGL_FUNCTIONS(PFNGLGETUNIFORMDVPROC, glGetUniformdv);
LOAD_OPENGL_FUNCTIONS(PFNGLGETSUBROUTINEUNIFORMLOCATIONPROC, glGetSubroutineUniformLocation);
LOAD_OPENGL_FUNCTIONS(PFNGLGETSUBROUTINEINDEXPROC, glGetSubroutineIndex);
LOAD_OPENGL_FUNCTIONS(PFNGLGETACTIVESUBROUTINEUNIFORMIVPROC, glGetActiveSubroutineUniformiv);
LOAD_OPENGL_FUNCTIONS(PFNGLGETACTIVESUBROUTINEUNIFORMNAMEPROC, glGetActiveSubroutineUniformName);
LOAD_OPENGL_FUNCTIONS(PFNGLGETACTIVESUBROUTINENAMEPROC, glGetActiveSubroutineName);
LOAD_OPENGL_FUNCTIONS(PFNGLUNIFORMSUBROUTINESUIVPROC, glUniformSubroutinesuiv);
LOAD_OPENGL_FUNCTIONS(PFNGLGETUNIFORMSUBROUTINEUIVPROC, glGetUniformSubroutineuiv);
LOAD_OPENGL_FUNCTIONS(PFNGLGETPROGRAMSTAGEIVPROC, glGetProgramStageiv);
LOAD_OPENGL_FUNCTIONS(PFNGLPATCHPARAMETERIPROC, glPatchParameteri);
LOAD_OPENGL_FUNCTIONS(PFNGLPATCHPARAMETERFVPROC, glPatchParameterfv);
LOAD_OPENGL_FUNCTIONS(PFNGLBINDTRANSFORMFEEDBACKPROC, glBindTransformFeedback);
LOAD_OPENGL_FUNCTIONS(PFNGLDELETETRANSFORMFEEDBACKSPROC, glDeleteTransformFeedbacks);
LOAD_OPENGL_FUNCTIONS(PFNGLGENTRANSFORMFEEDBACKSPROC, glGenTransformFeedbacks);
LOAD_OPENGL_FUNCTIONS(PFNGLISTRANSFORMFEEDBACKPROC, glIsTransformFeedback);
LOAD_OPENGL_FUNCTIONS(PFNGLPAUSETRANSFORMFEEDBACKPROC, glPauseTransformFeedback);
LOAD_OPENGL_FUNCTIONS(PFNGLRESUMETRANSFORMFEEDBACKPROC, glResumeTransformFeedback);
LOAD_OPENGL_FUNCTIONS(PFNGLDRAWTRANSFORMFEEDBACKPROC, glDrawTransformFeedback);
LOAD_OPENGL_FUNCTIONS(PFNGLDRAWTRANSFORMFEEDBACKSTREAMPROC, glDrawTransformFeedbackStream);
LOAD_OPENGL_FUNCTIONS(PFNGLBEGINQUERYINDEXEDPROC, glBeginQueryIndexed);
LOAD_OPENGL_FUNCTIONS(PFNGLENDQUERYINDEXEDPROC, glEndQueryIndexed);
LOAD_OPENGL_FUNCTIONS(PFNGLGETQUERYINDEXEDIVPROC, glGetQueryIndexediv);

#define LOAD_OPENGL_FUNCTION_4_1
LOAD_OPENGL_FUNCTIONS(PFNGLRELEASESHADERCOMPILERPROC, glReleaseShaderCompiler);
LOAD_OPENGL_FUNCTIONS(PFNGLSHADERBINARYPROC, glShaderBinary);
LOAD_OPENGL_FUNCTIONS(PFNGLGETSHADERPRECISIONFORMATPROC, glGetShaderPrecisionFormat);
LOAD_OPENGL_FUNCTIONS(PFNGLDEPTHRANGEFPROC, glDepthRangef);
LOAD_OPENGL_FUNCTIONS(PFNGLCLEARDEPTHFPROC, glClearDepthf);
LOAD_OPENGL_FUNCTIONS(PFNGLGETPROGRAMBINARYPROC, glGetProgramBinary);
LOAD_OPENGL_FUNCTIONS(PFNGLPROGRAMBINARYPROC, glProgramBinary);
LOAD_OPENGL_FUNCTIONS(PFNGLPROGRAMPARAMETERIPROC, glProgramParameteri);
LOAD_OPENGL_FUNCTIONS(PFNGLUSEPROGRAMSTAGESPROC, glUseProgramStages);
LOAD_OPENGL_FUNCTIONS(PFNGLACTIVESHADERPROGRAMPROC, glActiveShaderProgram);
LOAD_OPENGL_FUNCTIONS(PFNGLCREATESHADERPROGRAMVPROC, glCreateShaderProgramv);
LOAD_OPENGL_FUNCTIONS(PFNGLBINDPROGRAMPIPELINEPROC, glBindProgramPipeline);
LOAD_OPENGL_FUNCTIONS(PFNGLDELETEPROGRAMPIPELINESPROC, glDeleteProgramPipelines);
LOAD_OPENGL_FUNCTIONS(PFNGLGENPROGRAMPIPELINESPROC, glGenProgramPipelines);
LOAD_OPENGL_FUNCTIONS(PFNGLISPROGRAMPIPELINEPROC, glIsProgramPipeline);
LOAD_OPENGL_FUNCTIONS(PFNGLGETPROGRAMPIPELINEIVPROC, glGetProgramPipelineiv);
LOAD_OPENGL_FUNCTIONS(PFNGLPROGRAMUNIFORM1IPROC, glProgramUniform1i);
LOAD_OPENGL_FUNCTIONS(PFNGLPROGRAMUNIFORM1IVPROC, glProgramUniform1iv);
LOAD_OPENGL_FUNCTIONS(PFNGLPROGRAMUNIFORM1FPROC, glProgramUniform1f);
LOAD_OPENGL_FUNCTIONS(PFNGLPROGRAMUNIFORM1FVPROC, glProgramUniform1fv);
LOAD_OPENGL_FUNCTIONS(PFNGLPROGRAMUNIFORM1DPROC, glProgramUniform1d);
LOAD_OPENGL_FUNCTIONS(PFNGLPROGRAMUNIFORM1DVPROC, glProgramUniform1dv);
LOAD_OPENGL_FUNCTIONS(PFNGLPROGRAMUNIFORM1UIPROC, glProgramUniform1ui);
LOAD_OPENGL_FUNCTIONS(PFNGLPROGRAMUNIFORM1UIVPROC, glProgramUniform1uiv);
LOAD_OPENGL_FUNCTIONS(PFNGLPROGRAMUNIFORM2IPROC, glProgramUniform2i);
LOAD_OPENGL_FUNCTIONS(PFNGLPROGRAMUNIFORM2IVPROC, glProgramUniform2iv);
LOAD_OPENGL_FUNCTIONS(PFNGLPROGRAMUNIFORM2FPROC, glProgramUniform2f);
LOAD_OPENGL_FUNCTIONS(PFNGLPROGRAMUNIFORM2FVPROC, glProgramUniform2fv);
LOAD_OPENGL_FUNCTIONS(PFNGLPROGRAMUNIFORM2DPROC, glProgramUniform2d);
LOAD_OPENGL_FUNCTIONS(PFNGLPROGRAMUNIFORM2DVPROC, glProgramUniform2dv);
LOAD_OPENGL_FUNCTIONS(PFNGLPROGRAMUNIFORM2UIPROC, glProgramUniform2ui);
LOAD_OPENGL_FUNCTIONS(PFNGLPROGRAMUNIFORM2UIVPROC, glProgramUniform2uiv);
LOAD_OPENGL_FUNCTIONS(PFNGLPROGRAMUNIFORM3IPROC, glProgramUniform3i);
LOAD_OPENGL_FUNCTIONS(PFNGLPROGRAMUNIFORM3IVPROC, glProgramUniform3iv);
LOAD_OPENGL_FUNCTIONS(PFNGLPROGRAMUNIFORM3FPROC, glProgramUniform3f);
LOAD_OPENGL_FUNCTIONS(PFNGLPROGRAMUNIFORM3FVPROC, glProgramUniform3fv);
LOAD_OPENGL_FUNCTIONS(PFNGLPROGRAMUNIFORM3DPROC, glProgramUniform3d);
LOAD_OPENGL_FUNCTIONS(PFNGLPROGRAMUNIFORM3DVPROC, glProgramUniform3dv);
LOAD_OPENGL_FUNCTIONS(PFNGLPROGRAMUNIFORM3UIPROC, glProgramUniform3ui);
LOAD_OPENGL_FUNCTIONS(PFNGLPROGRAMUNIFORM3UIVPROC, glProgramUniform3uiv);
LOAD_OPENGL_FUNCTIONS(PFNGLPROGRAMUNIFORM4IPROC, glProgramUniform4i);
LOAD_OPENGL_FUNCTIONS(PFNGLPROGRAMUNIFORM4IVPROC, glProgramUniform4iv);
LOAD_OPENGL_FUNCTIONS(PFNGLPROGRAMUNIFORM4FPROC, glProgramUniform4f);
LOAD_OPENGL_FUNCTIONS(PFNGLPROGRAMUNIFORM4FVPROC, glProgramUniform4fv);
LOAD_OPENGL_FUNCTIONS(PFNGLPROGRAMUNIFORM4DPROC, glProgramUniform4d);
LOAD_OPENGL_FUNCTIONS(PFNGLPROGRAMUNIFORM4DVPROC, glProgramUniform4dv);
LOAD_OPENGL_FUNCTIONS(PFNGLPROGRAMUNIFORM4UIPROC, glProgramUniform4ui);
LOAD_OPENGL_FUNCTIONS(PFNGLPROGRAMUNIFORM4UIVPROC, glProgramUniform4uiv);
LOAD_OPENGL_FUNCTIONS(PFNGLPROGRAMUNIFORMMATRIX2FVPROC, glProgramUniformMatrix2fv);
LOAD_OPENGL_FUNCTIONS(PFNGLPROGRAMUNIFORMMATRIX3FVPROC, glProgramUniformMatrix3fv);
LOAD_OPENGL_FUNCTIONS(PFNGLPROGRAMUNIFORMMATRIX4FVPROC, glProgramUniformMatrix4fv);
LOAD_OPENGL_FUNCTIONS(PFNGLPROGRAMUNIFORMMATRIX2DVPROC, glProgramUniformMatrix2dv);
LOAD_OPENGL_FUNCTIONS(PFNGLPROGRAMUNIFORMMATRIX3DVPROC, glProgramUniformMatrix3dv);
LOAD_OPENGL_FUNCTIONS(PFNGLPROGRAMUNIFORMMATRIX4DVPROC, glProgramUniformMatrix4dv);
LOAD_OPENGL_FUNCTIONS(PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC, glProgramUniformMatrix2x3fv);
LOAD_OPENGL_FUNCTIONS(PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC, glProgramUniformMatrix3x2fv);
LOAD_OPENGL_FUNCTIONS(PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC, glProgramUniformMatrix2x4fv);
LOAD_OPENGL_FUNCTIONS(PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC, glProgramUniformMatrix4x2fv);
LOAD_OPENGL_FUNCTIONS(PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC, glProgramUniformMatrix3x4fv);
LOAD_OPENGL_FUNCTIONS(PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC, glProgramUniformMatrix4x3fv);
LOAD_OPENGL_FUNCTIONS(PFNGLPROGRAMUNIFORMMATRIX2X3DVPROC, glProgramUniformMatrix2x3dv);
LOAD_OPENGL_FUNCTIONS(PFNGLPROGRAMUNIFORMMATRIX3X2DVPROC, glProgramUniformMatrix3x2dv);
LOAD_OPENGL_FUNCTIONS(PFNGLPROGRAMUNIFORMMATRIX2X4DVPROC, glProgramUniformMatrix2x4dv);
LOAD_OPENGL_FUNCTIONS(PFNGLPROGRAMUNIFORMMATRIX4X2DVPROC, glProgramUniformMatrix4x2dv);
LOAD_OPENGL_FUNCTIONS(PFNGLPROGRAMUNIFORMMATRIX3X4DVPROC, glProgramUniformMatrix3x4dv);
LOAD_OPENGL_FUNCTIONS(PFNGLPROGRAMUNIFORMMATRIX4X3DVPROC, glProgramUniformMatrix4x3dv);
LOAD_OPENGL_FUNCTIONS(PFNGLVALIDATEPROGRAMPIPELINEPROC, glValidateProgramPipeline);
LOAD_OPENGL_FUNCTIONS(PFNGLGETPROGRAMPIPELINEINFOLOGPROC, glGetProgramPipelineInfoLog);
LOAD_OPENGL_FUNCTIONS(PFNGLVERTEXATTRIBL1DPROC, glVertexAttribL1d);
LOAD_OPENGL_FUNCTIONS(PFNGLVERTEXATTRIBL2DPROC, glVertexAttribL2d);
LOAD_OPENGL_FUNCTIONS(PFNGLVERTEXATTRIBL3DPROC, glVertexAttribL3d);
LOAD_OPENGL_FUNCTIONS(PFNGLVERTEXATTRIBL4DPROC, glVertexAttribL4d);
LOAD_OPENGL_FUNCTIONS(PFNGLVERTEXATTRIBL1DVPROC, glVertexAttribL1dv);
LOAD_OPENGL_FUNCTIONS(PFNGLVERTEXATTRIBL2DVPROC, glVertexAttribL2dv);
LOAD_OPENGL_FUNCTIONS(PFNGLVERTEXATTRIBL3DVPROC, glVertexAttribL3dv);
LOAD_OPENGL_FUNCTIONS(PFNGLVERTEXATTRIBL4DVPROC, glVertexAttribL4dv);
LOAD_OPENGL_FUNCTIONS(PFNGLVERTEXATTRIBLPOINTERPROC, glVertexAttribLPointer);
LOAD_OPENGL_FUNCTIONS(PFNGLGETVERTEXATTRIBLDVPROC, glGetVertexAttribLdv);
LOAD_OPENGL_FUNCTIONS(PFNGLVIEWPORTARRAYVPROC, glViewportArrayv);
LOAD_OPENGL_FUNCTIONS(PFNGLVIEWPORTINDEXEDFPROC, glViewportIndexedf);
LOAD_OPENGL_FUNCTIONS(PFNGLVIEWPORTINDEXEDFVPROC, glViewportIndexedfv);
LOAD_OPENGL_FUNCTIONS(PFNGLSCISSORARRAYVPROC, glScissorArrayv);
LOAD_OPENGL_FUNCTIONS(PFNGLSCISSORINDEXEDPROC, glScissorIndexed);
LOAD_OPENGL_FUNCTIONS(PFNGLSCISSORINDEXEDVPROC, glScissorIndexedv);
LOAD_OPENGL_FUNCTIONS(PFNGLDEPTHRANGEARRAYVPROC, glDepthRangeArrayv);
LOAD_OPENGL_FUNCTIONS(PFNGLDEPTHRANGEINDEXEDPROC, glDepthRangeIndexed);
LOAD_OPENGL_FUNCTIONS(PFNGLGETFLOATI_VPROC, glGetFloati_v);
LOAD_OPENGL_FUNCTIONS(PFNGLGETDOUBLEI_VPROC, glGetDoublei_v);

#define LOAD_OPENGL_FUNCTIONS_4_2
LOAD_OPENGL_FUNCTIONS(PFNGLDRAWARRAYSINSTANCEDBASEINSTANCEPROC, glDrawArraysInstancedBaseInstance);
LOAD_OPENGL_FUNCTIONS(PFNGLDRAWELEMENTSINSTANCEDBASEINSTANCEPROC, glDrawElementsInstancedBaseInstance);
LOAD_OPENGL_FUNCTIONS(PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCEPROC, glDrawElementsInstancedBaseVertexBaseInstance);
LOAD_OPENGL_FUNCTIONS(PFNGLGETINTERNALFORMATIVPROC, glGetInternalformativ);
LOAD_OPENGL_FUNCTIONS(PFNGLGETACTIVEATOMICCOUNTERBUFFERIVPROC, glGetActiveAtomicCounterBufferiv);
LOAD_OPENGL_FUNCTIONS(PFNGLBINDIMAGETEXTUREPROC, glBindImageTexture);
LOAD_OPENGL_FUNCTIONS(PFNGLMEMORYBARRIERPROC, glMemoryBarrier);
LOAD_OPENGL_FUNCTIONS(PFNGLTEXSTORAGE1DPROC, glTexStorage1D);
LOAD_OPENGL_FUNCTIONS(PFNGLTEXSTORAGE2DPROC, glTexStorage2D);
LOAD_OPENGL_FUNCTIONS(PFNGLTEXSTORAGE3DPROC, glTexStorage3D);
LOAD_OPENGL_FUNCTIONS(PFNGLDRAWTRANSFORMFEEDBACKINSTANCEDPROC, glDrawTransformFeedbackInstanced);
LOAD_OPENGL_FUNCTIONS(PFNGLDRAWTRANSFORMFEEDBACKSTREAMINSTANCEDPROC, glDrawTransformFeedbackStreamInstanced);

#define LOAD_OPENGL_FUNCTIONS_4_3
LOAD_OPENGL_FUNCTIONS(PFNGLCLEARBUFFERDATAPROC, glClearBufferData);
LOAD_OPENGL_FUNCTIONS(PFNGLCLEARBUFFERSUBDATAPROC, glClearBufferSubData);
LOAD_OPENGL_FUNCTIONS(PFNGLDISPATCHCOMPUTEPROC, glDispatchCompute);
LOAD_OPENGL_FUNCTIONS(PFNGLDISPATCHCOMPUTEINDIRECTPROC, glDispatchComputeIndirect);
LOAD_OPENGL_FUNCTIONS(PFNGLCOPYIMAGESUBDATAPROC, glCopyImageSubData);
LOAD_OPENGL_FUNCTIONS(PFNGLFRAMEBUFFERPARAMETERIPROC, glFramebufferParameteri);
LOAD_OPENGL_FUNCTIONS(PFNGLGETFRAMEBUFFERPARAMETERIVPROC, glGetFramebufferParameteriv);
LOAD_OPENGL_FUNCTIONS(PFNGLGETINTERNALFORMATI64VPROC, glGetInternalformati64v);
LOAD_OPENGL_FUNCTIONS(PFNGLINVALIDATETEXSUBIMAGEPROC, glInvalidateTexSubImage);
LOAD_OPENGL_FUNCTIONS(PFNGLINVALIDATETEXIMAGEPROC, glInvalidateTexImage);
LOAD_OPENGL_FUNCTIONS(PFNGLINVALIDATEBUFFERSUBDATAPROC, glInvalidateBufferSubData);
LOAD_OPENGL_FUNCTIONS(PFNGLINVALIDATEBUFFERDATAPROC, glInvalidateBufferData);
LOAD_OPENGL_FUNCTIONS(PFNGLINVALIDATEFRAMEBUFFERPROC, glInvalidateFramebuffer);
LOAD_OPENGL_FUNCTIONS(PFNGLINVALIDATESUBFRAMEBUFFERPROC, glInvalidateSubFramebuffer);
LOAD_OPENGL_FUNCTIONS(PFNGLMULTIDRAWARRAYSINDIRECTPROC, glMultiDrawArraysIndirect);
LOAD_OPENGL_FUNCTIONS(PFNGLMULTIDRAWELEMENTSINDIRECTPROC, glMultiDrawElementsIndirect);
LOAD_OPENGL_FUNCTIONS(PFNGLGETPROGRAMINTERFACEIVPROC, glGetProgramInterfaceiv);
LOAD_OPENGL_FUNCTIONS(PFNGLGETPROGRAMRESOURCEINDEXPROC, glGetProgramResourceIndex);
LOAD_OPENGL_FUNCTIONS(PFNGLGETPROGRAMRESOURCENAMEPROC, glGetProgramResourceName);
LOAD_OPENGL_FUNCTIONS(PFNGLGETPROGRAMRESOURCEIVPROC, glGetProgramResourceiv);
LOAD_OPENGL_FUNCTIONS(PFNGLGETPROGRAMRESOURCELOCATIONPROC, glGetProgramResourceLocation);
LOAD_OPENGL_FUNCTIONS(PFNGLGETPROGRAMRESOURCELOCATIONINDEXPROC, glGetProgramResourceLocationIndex);
LOAD_OPENGL_FUNCTIONS(PFNGLSHADERSTORAGEBLOCKBINDINGPROC, glShaderStorageBlockBinding);
LOAD_OPENGL_FUNCTIONS(PFNGLTEXBUFFERRANGEPROC, glTexBufferRange);
LOAD_OPENGL_FUNCTIONS(PFNGLTEXSTORAGE2DMULTISAMPLEPROC, glTexStorage2DMultisample);
LOAD_OPENGL_FUNCTIONS(PFNGLTEXSTORAGE3DMULTISAMPLEPROC, glTexStorage3DMultisample);
LOAD_OPENGL_FUNCTIONS(PFNGLTEXTUREVIEWPROC, glTextureView);
LOAD_OPENGL_FUNCTIONS(PFNGLBINDVERTEXBUFFERPROC, glBindVertexBuffer);
LOAD_OPENGL_FUNCTIONS(PFNGLVERTEXATTRIBFORMATPROC, glVertexAttribFormat);
LOAD_OPENGL_FUNCTIONS(PFNGLVERTEXATTRIBIFORMATPROC, glVertexAttribIFormat);
LOAD_OPENGL_FUNCTIONS(PFNGLVERTEXATTRIBLFORMATPROC, glVertexAttribLFormat);
LOAD_OPENGL_FUNCTIONS(PFNGLVERTEXATTRIBBINDINGPROC, glVertexAttribBinding);
LOAD_OPENGL_FUNCTIONS(PFNGLVERTEXBINDINGDIVISORPROC, glVertexBindingDivisor);
LOAD_OPENGL_FUNCTIONS(PFNGLDEBUGMESSAGECONTROLPROC, glDebugMessageControl);
LOAD_OPENGL_FUNCTIONS(PFNGLDEBUGMESSAGEINSERTPROC, glDebugMessageInsert);
LOAD_OPENGL_FUNCTIONS(PFNGLDEBUGMESSAGECALLBACKPROC, glDebugMessageCallback);
LOAD_OPENGL_FUNCTIONS(PFNGLGETDEBUGMESSAGELOGPROC, glGetDebugMessageLog);
LOAD_OPENGL_FUNCTIONS(PFNGLPUSHDEBUGGROUPPROC, glPushDebugGroup);
LOAD_OPENGL_FUNCTIONS(PFNGLPOPDEBUGGROUPPROC, glPopDebugGroup);
LOAD_OPENGL_FUNCTIONS(PFNGLOBJECTLABELPROC, glObjectLabel);
LOAD_OPENGL_FUNCTIONS(PFNGLGETOBJECTLABELPROC, glGetObjectLabel);
LOAD_OPENGL_FUNCTIONS(PFNGLOBJECTPTRLABELPROC, glObjectPtrLabel);
LOAD_OPENGL_FUNCTIONS(PFNGLGETOBJECTPTRLABELPROC, glGetObjectPtrLabel);

#define LOAD_OPENGL_FUNCTIONS_4_4
LOAD_OPENGL_FUNCTIONS(PFNGLBUFFERSTORAGEPROC, glBufferStorage);
LOAD_OPENGL_FUNCTIONS(PFNGLCLEARTEXIMAGEPROC, glClearTexImage);
LOAD_OPENGL_FUNCTIONS(PFNGLCLEARTEXSUBIMAGEPROC, glClearTexSubImage);
LOAD_OPENGL_FUNCTIONS(PFNGLBINDBUFFERSBASEPROC, glBindBuffersBase);
LOAD_OPENGL_FUNCTIONS(PFNGLBINDBUFFERSRANGEPROC, glBindBuffersRange);
LOAD_OPENGL_FUNCTIONS(PFNGLBINDTEXTURESPROC, glBindTextures);
LOAD_OPENGL_FUNCTIONS(PFNGLBINDSAMPLERSPROC, glBindSamplers);
LOAD_OPENGL_FUNCTIONS(PFNGLBINDIMAGETEXTURESPROC, glBindImageTextures);
LOAD_OPENGL_FUNCTIONS(PFNGLBINDVERTEXBUFFERSPROC, glBindVertexBuffers);

#define LOAD_OPENGL_FUNCTIONS_4_5
LOAD_OPENGL_FUNCTIONS(PFNGLCLIPCONTROLPROC, glClipControl);
LOAD_OPENGL_FUNCTIONS(PFNGLCREATETRANSFORMFEEDBACKSPROC, glCreateTransformFeedbacks);
LOAD_OPENGL_FUNCTIONS(PFNGLTRANSFORMFEEDBACKBUFFERBASEPROC, glTransformFeedbackBufferBase);
LOAD_OPENGL_FUNCTIONS(PFNGLTRANSFORMFEEDBACKBUFFERRANGEPROC, glTransformFeedbackBufferRange);
LOAD_OPENGL_FUNCTIONS(PFNGLGETTRANSFORMFEEDBACKIVPROC, glGetTransformFeedbackiv);
LOAD_OPENGL_FUNCTIONS(PFNGLGETTRANSFORMFEEDBACKI_VPROC, glGetTransformFeedbacki_v);
LOAD_OPENGL_FUNCTIONS(PFNGLGETTRANSFORMFEEDBACKI64_VPROC, glGetTransformFeedbacki64_v);
LOAD_OPENGL_FUNCTIONS(PFNGLCREATEBUFFERSPROC, glCreateBuffers);
LOAD_OPENGL_FUNCTIONS(PFNGLNAMEDBUFFERSTORAGEPROC, glNamedBufferStorage);
LOAD_OPENGL_FUNCTIONS(PFNGLNAMEDBUFFERDATAPROC, glNamedBufferData);
LOAD_OPENGL_FUNCTIONS(PFNGLNAMEDBUFFERSUBDATAPROC, glNamedBufferSubData);
LOAD_OPENGL_FUNCTIONS(PFNGLCOPYNAMEDBUFFERSUBDATAPROC, glCopyNamedBufferSubData);
LOAD_OPENGL_FUNCTIONS(PFNGLCLEARNAMEDBUFFERDATAPROC, glClearNamedBufferData);
LOAD_OPENGL_FUNCTIONS(PFNGLCLEARNAMEDBUFFERSUBDATAPROC, glClearNamedBufferSubData);
LOAD_OPENGL_FUNCTIONS(PFNGLMAPNAMEDBUFFERPROC, glMapNamedBuffer);
LOAD_OPENGL_FUNCTIONS(PFNGLMAPNAMEDBUFFERRANGEPROC, glMapNamedBufferRange);
LOAD_OPENGL_FUNCTIONS(PFNGLUNMAPNAMEDBUFFERPROC, glUnmapNamedBuffer);
LOAD_OPENGL_FUNCTIONS(PFNGLFLUSHMAPPEDNAMEDBUFFERRANGEPROC, glFlushMappedNamedBufferRange);
LOAD_OPENGL_FUNCTIONS(PFNGLGETNAMEDBUFFERPARAMETERIVPROC, glGetNamedBufferParameteriv);
LOAD_OPENGL_FUNCTIONS(PFNGLGETNAMEDBUFFERPARAMETERI64VPROC, glGetNamedBufferParameteri64v);
LOAD_OPENGL_FUNCTIONS(PFNGLGETNAMEDBUFFERPOINTERVPROC, glGetNamedBufferPointerv);
LOAD_OPENGL_FUNCTIONS(PFNGLGETNAMEDBUFFERSUBDATAPROC, glGetNamedBufferSubData);
LOAD_OPENGL_FUNCTIONS(PFNGLCREATEFRAMEBUFFERSPROC, glCreateFramebuffers);
LOAD_OPENGL_FUNCTIONS(PFNGLNAMEDFRAMEBUFFERRENDERBUFFERPROC, glNamedFramebufferRenderbuffer);
LOAD_OPENGL_FUNCTIONS(PFNGLNAMEDFRAMEBUFFERPARAMETERIPROC, glNamedFramebufferParameteri);
LOAD_OPENGL_FUNCTIONS(PFNGLNAMEDFRAMEBUFFERTEXTUREPROC, glNamedFramebufferTexture);
LOAD_OPENGL_FUNCTIONS(PFNGLNAMEDFRAMEBUFFERTEXTURELAYERPROC, glNamedFramebufferTextureLayer);
LOAD_OPENGL_FUNCTIONS(PFNGLNAMEDFRAMEBUFFERDRAWBUFFERPROC, glNamedFramebufferDrawBuffer);
LOAD_OPENGL_FUNCTIONS(PFNGLNAMEDFRAMEBUFFERDRAWBUFFERSPROC, glNamedFramebufferDrawBuffers);
LOAD_OPENGL_FUNCTIONS(PFNGLNAMEDFRAMEBUFFERREADBUFFERPROC, glNamedFramebufferReadBuffer);
LOAD_OPENGL_FUNCTIONS(PFNGLINVALIDATENAMEDFRAMEBUFFERDATAPROC, glInvalidateNamedFramebufferData);
LOAD_OPENGL_FUNCTIONS(PFNGLINVALIDATENAMEDFRAMEBUFFERSUBDATAPROC, glInvalidateNamedFramebufferSubData);
LOAD_OPENGL_FUNCTIONS(PFNGLCLEARNAMEDFRAMEBUFFERIVPROC, glClearNamedFramebufferiv);
LOAD_OPENGL_FUNCTIONS(PFNGLCLEARNAMEDFRAMEBUFFERUIVPROC, glClearNamedFramebufferuiv);
LOAD_OPENGL_FUNCTIONS(PFNGLCLEARNAMEDFRAMEBUFFERFVPROC, glClearNamedFramebufferfv);
LOAD_OPENGL_FUNCTIONS(PFNGLCLEARNAMEDFRAMEBUFFERFIPROC, glClearNamedFramebufferfi);
LOAD_OPENGL_FUNCTIONS(PFNGLBLITNAMEDFRAMEBUFFERPROC, glBlitNamedFramebuffer);
LOAD_OPENGL_FUNCTIONS(PFNGLCHECKNAMEDFRAMEBUFFERSTATUSPROC, glCheckNamedFramebufferStatus);
LOAD_OPENGL_FUNCTIONS(PFNGLGETNAMEDFRAMEBUFFERPARAMETERIVPROC, glGetNamedFramebufferParameteriv);
LOAD_OPENGL_FUNCTIONS(PFNGLGETNAMEDFRAMEBUFFERATTACHMENTPARAMETERIVPROC, glGetNamedFramebufferAttachmentParameteriv);
LOAD_OPENGL_FUNCTIONS(PFNGLCREATERENDERBUFFERSPROC, glCreateRenderbuffers);
LOAD_OPENGL_FUNCTIONS(PFNGLNAMEDRENDERBUFFERSTORAGEPROC, glNamedRenderbufferStorage);
LOAD_OPENGL_FUNCTIONS(PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEPROC, glNamedRenderbufferStorageMultisample);
LOAD_OPENGL_FUNCTIONS(PFNGLGETNAMEDRENDERBUFFERPARAMETERIVPROC, glGetNamedRenderbufferParameteriv);
LOAD_OPENGL_FUNCTIONS(PFNGLCREATETEXTURESPROC, glCreateTextures);
LOAD_OPENGL_FUNCTIONS(PFNGLTEXTUREBUFFERPROC, glTextureBuffer);
LOAD_OPENGL_FUNCTIONS(PFNGLTEXTUREBUFFERRANGEPROC, glTextureBufferRange);
LOAD_OPENGL_FUNCTIONS(PFNGLTEXTURESTORAGE1DPROC, glTextureStorage1D);
LOAD_OPENGL_FUNCTIONS(PFNGLTEXTURESTORAGE2DPROC, glTextureStorage2D);
LOAD_OPENGL_FUNCTIONS(PFNGLTEXTURESTORAGE3DPROC, glTextureStorage3D);
LOAD_OPENGL_FUNCTIONS(PFNGLTEXTURESTORAGE2DMULTISAMPLEPROC, glTextureStorage2DMultisample);
LOAD_OPENGL_FUNCTIONS(PFNGLTEXTURESTORAGE3DMULTISAMPLEPROC, glTextureStorage3DMultisample);
LOAD_OPENGL_FUNCTIONS(PFNGLTEXTURESUBIMAGE1DPROC, glTextureSubImage1D);
LOAD_OPENGL_FUNCTIONS(PFNGLTEXTURESUBIMAGE2DPROC, glTextureSubImage2D);
LOAD_OPENGL_FUNCTIONS(PFNGLTEXTURESUBIMAGE3DPROC, glTextureSubImage3D);
LOAD_OPENGL_FUNCTIONS(PFNGLCOMPRESSEDTEXTURESUBIMAGE1DPROC, glCompressedTextureSubImage1D);
LOAD_OPENGL_FUNCTIONS(PFNGLCOMPRESSEDTEXTURESUBIMAGE2DPROC, glCompressedTextureSubImage2D);
LOAD_OPENGL_FUNCTIONS(PFNGLCOMPRESSEDTEXTURESUBIMAGE3DPROC, glCompressedTextureSubImage3D);
LOAD_OPENGL_FUNCTIONS(PFNGLCOPYTEXTURESUBIMAGE1DPROC, glCopyTextureSubImage1D);
LOAD_OPENGL_FUNCTIONS(PFNGLCOPYTEXTURESUBIMAGE2DPROC, glCopyTextureSubImage2D);
LOAD_OPENGL_FUNCTIONS(PFNGLCOPYTEXTURESUBIMAGE3DPROC, glCopyTextureSubImage3D);
LOAD_OPENGL_FUNCTIONS(PFNGLTEXTUREPARAMETERFPROC, glTextureParameterf);
LOAD_OPENGL_FUNCTIONS(PFNGLTEXTUREPARAMETERFVPROC, glTextureParameterfv);
LOAD_OPENGL_FUNCTIONS(PFNGLTEXTUREPARAMETERIPROC, glTextureParameteri);
LOAD_OPENGL_FUNCTIONS(PFNGLTEXTUREPARAMETERIIVPROC, glTextureParameterIiv);
LOAD_OPENGL_FUNCTIONS(PFNGLTEXTUREPARAMETERIUIVPROC, glTextureParameterIuiv);
LOAD_OPENGL_FUNCTIONS(PFNGLTEXTUREPARAMETERIVPROC, glTextureParameteriv);
LOAD_OPENGL_FUNCTIONS(PFNGLGENERATETEXTUREMIPMAPPROC, glGenerateTextureMipmap);
LOAD_OPENGL_FUNCTIONS(PFNGLBINDTEXTUREUNITPROC, glBindTextureUnit);
LOAD_OPENGL_FUNCTIONS(PFNGLGETTEXTUREIMAGEPROC, glGetTextureImage);
LOAD_OPENGL_FUNCTIONS(PFNGLGETCOMPRESSEDTEXTUREIMAGEPROC, glGetCompressedTextureImage);
LOAD_OPENGL_FUNCTIONS(PFNGLGETTEXTURELEVELPARAMETERFVPROC, glGetTextureLevelParameterfv);
LOAD_OPENGL_FUNCTIONS(PFNGLGETTEXTURELEVELPARAMETERIVPROC, glGetTextureLevelParameteriv);
LOAD_OPENGL_FUNCTIONS(PFNGLGETTEXTUREPARAMETERFVPROC, glGetTextureParameterfv);
LOAD_OPENGL_FUNCTIONS(PFNGLGETTEXTUREPARAMETERIIVPROC, glGetTextureParameterIiv);
LOAD_OPENGL_FUNCTIONS(PFNGLGETTEXTUREPARAMETERIUIVPROC, glGetTextureParameterIuiv);
LOAD_OPENGL_FUNCTIONS(PFNGLGETTEXTUREPARAMETERIVPROC, glGetTextureParameteriv);
LOAD_OPENGL_FUNCTIONS(PFNGLCREATEVERTEXARRAYSPROC, glCreateVertexArrays);
LOAD_OPENGL_FUNCTIONS(PFNGLDISABLEVERTEXARRAYATTRIBPROC, glDisableVertexArrayAttrib);
LOAD_OPENGL_FUNCTIONS(PFNGLENABLEVERTEXARRAYATTRIBPROC, glEnableVertexArrayAttrib);
LOAD_OPENGL_FUNCTIONS(PFNGLVERTEXARRAYELEMENTBUFFERPROC, glVertexArrayElementBuffer);
LOAD_OPENGL_FUNCTIONS(PFNGLVERTEXARRAYVERTEXBUFFERPROC, glVertexArrayVertexBuffer);
LOAD_OPENGL_FUNCTIONS(PFNGLVERTEXARRAYVERTEXBUFFERSPROC, glVertexArrayVertexBuffers);
LOAD_OPENGL_FUNCTIONS(PFNGLVERTEXARRAYATTRIBBINDINGPROC, glVertexArrayAttribBinding);
LOAD_OPENGL_FUNCTIONS(PFNGLVERTEXARRAYATTRIBFORMATPROC, glVertexArrayAttribFormat);
LOAD_OPENGL_FUNCTIONS(PFNGLVERTEXARRAYATTRIBIFORMATPROC, glVertexArrayAttribIFormat);
LOAD_OPENGL_FUNCTIONS(PFNGLVERTEXARRAYATTRIBLFORMATPROC, glVertexArrayAttribLFormat);
LOAD_OPENGL_FUNCTIONS(PFNGLVERTEXARRAYBINDINGDIVISORPROC, glVertexArrayBindingDivisor);
LOAD_OPENGL_FUNCTIONS(PFNGLGETVERTEXARRAYIVPROC, glGetVertexArrayiv);
LOAD_OPENGL_FUNCTIONS(PFNGLGETVERTEXARRAYINDEXEDIVPROC, glGetVertexArrayIndexediv);
LOAD_OPENGL_FUNCTIONS(PFNGLGETVERTEXARRAYINDEXED64IVPROC, glGetVertexArrayIndexed64iv);
LOAD_OPENGL_FUNCTIONS(PFNGLCREATESAMPLERSPROC, glCreateSamplers);
LOAD_OPENGL_FUNCTIONS(PFNGLCREATEPROGRAMPIPELINESPROC, glCreateProgramPipelines);
LOAD_OPENGL_FUNCTIONS(PFNGLCREATEQUERIESPROC, glCreateQueries);
LOAD_OPENGL_FUNCTIONS(PFNGLGETQUERYBUFFEROBJECTI64VPROC, glGetQueryBufferObjecti64v);
LOAD_OPENGL_FUNCTIONS(PFNGLGETQUERYBUFFEROBJECTIVPROC, glGetQueryBufferObjectiv);
LOAD_OPENGL_FUNCTIONS(PFNGLGETQUERYBUFFEROBJECTUI64VPROC, glGetQueryBufferObjectui64v);
LOAD_OPENGL_FUNCTIONS(PFNGLGETQUERYBUFFEROBJECTUIVPROC, glGetQueryBufferObjectuiv);
LOAD_OPENGL_FUNCTIONS(PFNGLMEMORYBARRIERBYREGIONPROC, glMemoryBarrierByRegion);
LOAD_OPENGL_FUNCTIONS(PFNGLGETTEXTURESUBIMAGEPROC, glGetTextureSubImage);
LOAD_OPENGL_FUNCTIONS(PFNGLGETCOMPRESSEDTEXTURESUBIMAGEPROC, glGetCompressedTextureSubImage);
LOAD_OPENGL_FUNCTIONS(PFNGLGETGRAPHICSRESETSTATUSPROC, glGetGraphicsResetStatus);
LOAD_OPENGL_FUNCTIONS(PFNGLGETNCOMPRESSEDTEXIMAGEPROC, glGetnCompressedTexImage);
LOAD_OPENGL_FUNCTIONS(PFNGLGETNTEXIMAGEPROC, glGetnTexImage);
LOAD_OPENGL_FUNCTIONS(PFNGLGETNUNIFORMDVPROC, glGetnUniformdv);
LOAD_OPENGL_FUNCTIONS(PFNGLGETNUNIFORMFVPROC, glGetnUniformfv);
LOAD_OPENGL_FUNCTIONS(PFNGLGETNUNIFORMIVPROC, glGetnUniformiv);
LOAD_OPENGL_FUNCTIONS(PFNGLGETNUNIFORMUIVPROC, glGetnUniformuiv);
LOAD_OPENGL_FUNCTIONS(PFNGLREADNPIXELSPROC, glReadnPixels);
LOAD_OPENGL_FUNCTIONS(PFNGLTEXTUREBARRIERPROC, glTextureBarrier);

#define LOAD_OPENGL_FUNCTIONS_4_6
LOAD_OPENGL_FUNCTIONS(PFNGLSPECIALIZESHADERPROC, glSpecializeShader);
LOAD_OPENGL_FUNCTIONS(PFNGLMULTIDRAWARRAYSINDIRECTCOUNTPROC, glMultiDrawArraysIndirectCount);
LOAD_OPENGL_FUNCTIONS(PFNGLMULTIDRAWELEMENTSINDIRECTCOUNTPROC, glMultiDrawElementsIndirectCount);
LOAD_OPENGL_FUNCTIONS(PFNGLPOLYGONOFFSETCLAMPPROC, glPolygonOffsetClamp);

#if OPENGL_TEST_VERSION(1, 0)
LOAD_OPENGL_FUNCTIONS_1_0
#endif

#if OPENGL_TEST_VERSION(1, 1)
LOAD_OPENGL_FUNCTIONS_1_1
#endif

#if OPENGL_TEST_VERSION(1, 2)
LOAD_OPENGL_FUNCTIONS_1_2
#endif

#if OPENGL_TEST_VERSION(1, 3)
LOAD_OPENGL_FUNCTIONS_1_3
#endif

#if OPENGL_TEST_VERSION(1, 4)
LOAD_OPENGL_FUNCTIONS_1_4
#endif

#if OPENGL_TEST_VERSION(1, 5)
LOAD_OPENGL_FUNCTIONS_1_5
#endif

#if OPENGL_TEST_VERSION(2, 0)
LOAD_OPENGL_FUNCTIONS_2_0
#endif

#if OPENGL_TEST_VERSION(2, 1)
LOAD_OPENGL_FUNCTIONS_2_1
#endif

#if OPENGL_TEST_VERSION(3, 0)
LOAD_OPENGL_FUNCTIONS_3_0
#endif

#if OPENGL_TEST_VERSION(3, 1)
LOAD_OPENGL_FUNCTIONS_3_1
#endif

#if OPENGL_TEST_VERSION(3, 2)
LOAD_OPENGL_FUNCTIONS_3_2
#endif

#if OPENGL_TEST_VERSION(3, 3)
LOAD_OPENGL_FUNCTIONS_3_3
#endif

#if OPENGL_TEST_VERSION(4, 0)
LOAD_OPENGL_FUNCTIONS_4_0
#endif

#if OPENGL_TEST_VERSION(4, 1)
LOAD_OPENGL_FUNCTIONS_4_1
#endif

#if OPENGL_TEST_VERSION(4, 2)
LOAD_OPENGL_FUNCTIONS_4_2
#endif

#if OPENGL_TEST_VERSION(4, 3)
LOAD_OPENGL_FUNCTIONS_4_3
#endif

#if OPENGL_TEST_VERSION(4, 4)
LOAD_OPENGL_FUNCTIONS_4_4
#endif

#if OPENGL_TEST_VERSION(4, 5)
LOAD_OPENGL_FUNCTIONS_4_5
#endif

#if OPENGL_TEST_VERSION(4, 6)
LOAD_OPENGL_FUNCTIONS_4_6
#endif

#define OPENGL_RETRIVE_FUNCTIONS(name, type) = (type)wglGetProcAddress(#name)

#define OPENGL_RETRIVE_FUNCTIONS_1_0
OPENGL_RETRIVE_FUNCTIONS(PFNGLCULLFACEPROC, glCullFace);
OPENGL_RETRIVE_FUNCTIONS(PFNGLFRONTFACEPROC, glFrontFace);
OPENGL_RETRIVE_FUNCTIONS(PFNGLHINTPROC, glHint);
OPENGL_RETRIVE_FUNCTIONS(PFNGLLINEWIDTHPROC, glLineWidth);
OPENGL_RETRIVE_FUNCTIONS(PFNGLPOINTSIZEPROC, glPointSize);
OPENGL_RETRIVE_FUNCTIONS(PFNGLPOLYGONMODEPROC, glPolygonMode);
OPENGL_RETRIVE_FUNCTIONS(PFNGLSCISSORPROC, glScissor);
OPENGL_RETRIVE_FUNCTIONS(PFNGLTEXPARAMETERFPROC, glTexParameterf);
OPENGL_RETRIVE_FUNCTIONS(PFNGLTEXPARAMETERFVPROC, glTexParameterfv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLTEXPARAMETERIPROC, glTexParameteri);
OPENGL_RETRIVE_FUNCTIONS(PFNGLTEXPARAMETERIVPROC, glTexParameteriv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLTEXIMAGE1DPROC, glTexImage1D);
OPENGL_RETRIVE_FUNCTIONS(PFNGLTEXIMAGE2DPROC, glTexImage2D);
OPENGL_RETRIVE_FUNCTIONS(PFNGLDRAWBUFFERPROC, glDrawBuffer);
OPENGL_RETRIVE_FUNCTIONS(PFNGLCLEARPROC, glClear);
OPENGL_RETRIVE_FUNCTIONS(PFNGLCLEARCOLORPROC, glClearColor);
OPENGL_RETRIVE_FUNCTIONS(PFNGLCLEARSTENCILPROC, glClearStencil);
OPENGL_RETRIVE_FUNCTIONS(PFNGLCLEARDEPTHPROC, glClearDepth);
OPENGL_RETRIVE_FUNCTIONS(PFNGLSTENCILMASKPROC, glStencilMask);
OPENGL_RETRIVE_FUNCTIONS(PFNGLCOLORMASKPROC, glColorMask);
OPENGL_RETRIVE_FUNCTIONS(PFNGLDEPTHMASKPROC, glDepthMask);
OPENGL_RETRIVE_FUNCTIONS(PFNGLDISABLEPROC, glDisable);
OPENGL_RETRIVE_FUNCTIONS(PFNGLENABLEPROC, glEnable);
OPENGL_RETRIVE_FUNCTIONS(PFNGLFINISHPROC, glFinish);
OPENGL_RETRIVE_FUNCTIONS(PFNGLFLUSHPROC, glFlush);
OPENGL_RETRIVE_FUNCTIONS(PFNGLBLENDFUNCPROC, glBlendFunc);
OPENGL_RETRIVE_FUNCTIONS(PFNGLLOGICOPPROC, glLogicOp);
OPENGL_RETRIVE_FUNCTIONS(PFNGLSTENCILFUNCPROC, glStencilFunc);
OPENGL_RETRIVE_FUNCTIONS(PFNGLSTENCILOPPROC, glStencilOp);
OPENGL_RETRIVE_FUNCTIONS(PFNGLDEPTHFUNCPROC, glDepthFunc);
OPENGL_RETRIVE_FUNCTIONS(PFNGLPIXELSTOREFPROC, glPixelStoref);
OPENGL_RETRIVE_FUNCTIONS(PFNGLPIXELSTOREIPROC, glPixelStorei);
OPENGL_RETRIVE_FUNCTIONS(PFNGLREADBUFFERPROC, glReadBuffer);
OPENGL_RETRIVE_FUNCTIONS(PFNGLREADPIXELSPROC, glReadPixels);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETBOOLEANVPROC, glGetBooleanv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETDOUBLEVPROC, glGetDoublev);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETERRORPROC, glGetError);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETFLOATVPROC, glGetFloatv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETINTEGERVPROC, glGetIntegerv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETSTRINGPROC, glGetString );
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETTEXIMAGEPROC, glGetTexImage);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETTEXPARAMETERFVPROC, glGetTexParameterfv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETTEXPARAMETERIVPROC, glGetTexParameteriv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETTEXLEVELPARAMETERFVPROCglGetTexLevelParameterfv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETTEXLEVELPARAMETERIVPROCglGetTexLevelParameteriv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLISENABLEDPROC, glIsEnabled);
OPENGL_RETRIVE_FUNCTIONS(PFNGLDEPTHRANGEPROC, glDepthRange);
OPENGL_RETRIVE_FUNCTIONS(PFNGLVIEWPORTPROC, glViewport);

#define OPENGL_RETRIVE_FUNCTIONS_1_1
OPENGL_RETRIVE_FUNCTIONS_1_0
OPENGL_RETRIVE_FUNCTIONS(PFNGLDRAWARRAYSPROC, glDrawArrays);
OPENGL_RETRIVE_FUNCTIONS(PFNGLDRAWELEMENTSPROC, glDrawElements);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETPOINTERVPROC, glGetPointerv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLPOLYGONOFFSETPROC, glPolygonOffset);
OPENGL_RETRIVE_FUNCTIONS(PFNGLCOPYTEXIMAGE1DPROC, glCopyTexImage1D);
OPENGL_RETRIVE_FUNCTIONS(PFNGLCOPYTEXIMAGE2DPROC, glCopyTexImage2D);
OPENGL_RETRIVE_FUNCTIONS(PFNGLCOPYTEXSUBIMAGE1DPROC, glCopyTexSubImage1D);
OPENGL_RETRIVE_FUNCTIONS(PFNGLCOPYTEXSUBIMAGE2DPROC, glCopyTexSubImage2D);
OPENGL_RETRIVE_FUNCTIONS(PFNGLTEXSUBIMAGE1DPROC, glTexSubImage1D);
OPENGL_RETRIVE_FUNCTIONS(PFNGLTEXSUBIMAGE2DPROC, glTexSubImage2D);
OPENGL_RETRIVE_FUNCTIONS(PFNGLBINDTEXTUREPROC, glBindTexture);
OPENGL_RETRIVE_FUNCTIONS(PFNGLDELETETEXTURESPROC, glDeleteTextures);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGENTEXTURESPROC, glGenTextures);
OPENGL_RETRIVE_FUNCTIONS(PFNGLISTEXTUREPROC, glIsTexture);

#define OPENGL_RETRIVE_FUNCTIONS_1_2
OPENGL_RETRIVE_FUNCTIONS_1_1
OPENGL_RETRIVE_FUNCTIONS(PFNGLDRAWRANGEELEMENTSPROC, glDrawRangeElements);
OPENGL_RETRIVE_FUNCTIONS(PFNGLTEXIMAGE3DPROC, glTexImage3D);
OPENGL_RETRIVE_FUNCTIONS(PFNGLTEXSUBIMAGE3DPROC, glTexSubImage3D);
OPENGL_RETRIVE_FUNCTIONS(PFNGLCOPYTEXSUBIMAGE3DPROC, glCopyTexSubImage3D);

#define OPENGL_RETRIVE_FUNCTIONS_1_3
OPENGL_RETRIVE_FUNCTIONS_1_2
OPENGL_RETRIVE_FUNCTIONS(PFNGLACTIVETEXTUREPROC, glActiveTexture);
OPENGL_RETRIVE_FUNCTIONS(PFNGLSAMPLECOVERAGEPROC, glSampleCoverage);
OPENGL_RETRIVE_FUNCTIONS(PFNGLCOMPRESSEDTEXIMAGE3DPROC, glCompressedTexImage3D);
OPENGL_RETRIVE_FUNCTIONS(PFNGLCOMPRESSEDTEXIMAGE2DPROC, glCompressedTexImage2D);
OPENGL_RETRIVE_FUNCTIONS(PFNGLCOMPRESSEDTEXIMAGE1DPROC, glCompressedTexImage1D);
OPENGL_RETRIVE_FUNCTIONS(PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC, glCompressedTexSubImage3D);
OPENGL_RETRIVE_FUNCTIONS(PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC, glCompressedTexSubImage2D);
OPENGL_RETRIVE_FUNCTIONS(PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC, glCompressedTexSubImage1D);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETCOMPRESSEDTEXIMAGEPROC, glGetCompressedTexImage);

#define OPENGL_RETRIVE_FUNCTIONS_1_4
OPENGL_RETRIVE_FUNCTIONS_1_3
OPENGL_RETRIVE_FUNCTIONS(PFNGLBLENDFUNCSEPARATEPROC, glBlendFuncSeparate);
OPENGL_RETRIVE_FUNCTIONS(PFNGLMULTIDRAWARRAYSPROC, glMultiDrawArrays);
OPENGL_RETRIVE_FUNCTIONS(PFNGLMULTIDRAWELEMENTSPROC, glMultiDrawElements);
OPENGL_RETRIVE_FUNCTIONS(PFNGLPOINTPARAMETERFPROC, glPointParameterf);
OPENGL_RETRIVE_FUNCTIONS(PFNGLPOINTPARAMETERFVPROC, glPointParameterfv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLPOINTPARAMETERIPROC, glPointParameteri);
OPENGL_RETRIVE_FUNCTIONS(PFNGLPOINTPARAMETERIVPROC, glPointParameteriv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLBLENDCOLORPROC, glBlendColor);
OPENGL_RETRIVE_FUNCTIONS(PFNGLBLENDEQUATIONPROC, glBlendEquation);

#define OPENGL_RETRIVE_FUNCTIONS_1_5
OPENGL_RETRIVE_FUNCTIONS_1_4
OPENGL_RETRIVE_FUNCTIONS(PFNGLGENQUERIESPROC, glGenQueries);
OPENGL_RETRIVE_FUNCTIONS(PFNGLDELETEQUERIESPROC, glDeleteQueries);
OPENGL_RETRIVE_FUNCTIONS(PFNGLISQUERYPROC, glIsQuery);
OPENGL_RETRIVE_FUNCTIONS(PFNGLBEGINQUERYPROC, glBeginQuery);
OPENGL_RETRIVE_FUNCTIONS(PFNGLENDQUERYPROC, glEndQuery);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETQUERYIVPROC, glGetQueryiv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETQUERYOBJECTIVPROC, glGetQueryObjectiv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETQUERYOBJECTUIVPROC, glGetQueryObjectuiv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLBINDBUFFERPROC, glBindBuffer);
OPENGL_RETRIVE_FUNCTIONS(PFNGLDELETEBUFFERSPROC, glDeleteBuffers);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGENBUFFERSPROC, glGenBuffers);
OPENGL_RETRIVE_FUNCTIONS(PFNGLISBUFFERPROC, glIsBuffer);
OPENGL_RETRIVE_FUNCTIONS(PFNGLBUFFERDATAPROC, glBufferData);
OPENGL_RETRIVE_FUNCTIONS(PFNGLBUFFERSUBDATAPROC, glBufferSubData);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETBUFFERSUBDATAPROC, glGetBufferSubData);
OPENGL_RETRIVE_FUNCTIONS(PFNGLMAPBUFFERPROC, glMapBuffer);
OPENGL_RETRIVE_FUNCTIONS(PFNGLUNMAPBUFFERPROC, glUnmapBuffer);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETBUFFERPARAMETERIVPROC, glGetBufferParameteriv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETBUFFERPOINTERVPROC, glGetBufferPointerv);

#define OPENGL_RETRIVE_FUNCTIONS_2_0
OPENGL_RETRIVE_FUNCTIONS_1_5
OPENGL_RETRIVE_FUNCTIONS(PFNGLBLENDEQUATIONSEPARATEPROC, glBlendEquationSeparate);
OPENGL_RETRIVE_FUNCTIONS(PFNGLDRAWBUFFERSPROC, glDrawBuffers);
OPENGL_RETRIVE_FUNCTIONS(PFNGLSTENCILOPSEPARATEPROC, glStencilOpSeparate);
OPENGL_RETRIVE_FUNCTIONS(PFNGLSTENCILFUNCSEPARATEPROC, glStencilFuncSeparate);
OPENGL_RETRIVE_FUNCTIONS(PFNGLSTENCILMASKSEPARATEPROC, glStencilMaskSeparate);
OPENGL_RETRIVE_FUNCTIONS(PFNGLATTACHSHADERPROC, glAttachShader);
OPENGL_RETRIVE_FUNCTIONS(PFNGLBINDATTRIBLOCATIONPROC, glBindAttribLocation);
OPENGL_RETRIVE_FUNCTIONS(PFNGLCOMPILESHADERPROC, glCompileShader);
OPENGL_RETRIVE_FUNCTIONS(PFNGLCREATEPROGRAMPROC, glCreateProgram);
OPENGL_RETRIVE_FUNCTIONS(PFNGLCREATESHADERPROC, glCreateShader);
OPENGL_RETRIVE_FUNCTIONS(PFNGLDELETEPROGRAMPROC, glDeleteProgram);
OPENGL_RETRIVE_FUNCTIONS(PFNGLDELETESHADERPROC, glDeleteShader);
OPENGL_RETRIVE_FUNCTIONS(PFNGLDETACHSHADERPROC, glDetachShader);
OPENGL_RETRIVE_FUNCTIONS(PFNGLDISABLEVERTEXATTRIBARRAYPROC, glDisableVertexAttribArray);
OPENGL_RETRIVE_FUNCTIONS(PFNGLENABLEVERTEXATTRIBARRAYPROC, glEnableVertexAttribArray);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETACTIVEATTRIBPROC, glGetActiveAttrib);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETACTIVEUNIFORMPROC, glGetActiveUniform);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETATTACHEDSHADERSPROC, glGetAttachedShaders);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETATTRIBLOCATIONPROC, glGetAttribLocation);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETPROGRAMIVPROC, glGetProgramiv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETPROGRAMINFOLOGPROC, glGetProgramInfoLog);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETSHADERIVPROC, glGetShaderiv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETSHADERINFOLOGPROC, glGetShaderInfoLog);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETSHADERSOURCEPROC, glGetShaderSource);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETUNIFORMLOCATIONPROC, glGetUniformLocation);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETUNIFORMFVPROC, glGetUniformfv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETUNIFORMIVPROC, glGetUniformiv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETVERTEXATTRIBDVPROC, glGetVertexAttribdv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETVERTEXATTRIBFVPROC, glGetVertexAttribfv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETVERTEXATTRIBIVPROC, glGetVertexAttribiv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETVERTEXATTRIBPOINTERVPROC, glGetVertexAttribPointerv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLISPROGRAMPROC, glIsProgram);
OPENGL_RETRIVE_FUNCTIONS(PFNGLISSHADERPROC, glIsShader);
OPENGL_RETRIVE_FUNCTIONS(PFNGLLINKPROGRAMPROC, glLinkProgram);
OPENGL_RETRIVE_FUNCTIONS(PFNGLSHADERSOURCEPROC, glShaderSource);
OPENGL_RETRIVE_FUNCTIONS(PFNGLUSEPROGRAMPROC, glUseProgram);
OPENGL_RETRIVE_FUNCTIONS(PFNGLUNIFORM1FPROC, glUniform1f);
OPENGL_RETRIVE_FUNCTIONS(PFNGLUNIFORM2FPROC, glUniform2f);
OPENGL_RETRIVE_FUNCTIONS(PFNGLUNIFORM3FPROC, glUniform3f);
OPENGL_RETRIVE_FUNCTIONS(PFNGLUNIFORM4FPROC, glUniform4f);
OPENGL_RETRIVE_FUNCTIONS(PFNGLUNIFORM1IPROC, glUniform1i);
OPENGL_RETRIVE_FUNCTIONS(PFNGLUNIFORM2IPROC, glUniform2i);
OPENGL_RETRIVE_FUNCTIONS(PFNGLUNIFORM3IPROC, glUniform3i);
OPENGL_RETRIVE_FUNCTIONS(PFNGLUNIFORM4IPROC, glUniform4i);
OPENGL_RETRIVE_FUNCTIONS(PFNGLUNIFORM1FVPROC, glUniform1fv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLUNIFORM2FVPROC, glUniform2fv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLUNIFORM3FVPROC, glUniform3fv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLUNIFORM4FVPROC, glUniform4fv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLUNIFORM1IVPROC, glUniform1iv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLUNIFORM2IVPROC, glUniform2iv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLUNIFORM3IVPROC, glUniform3iv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLUNIFORM4IVPROC, glUniform4iv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLUNIFORMMATRIX2FVPROC, glUniformMatrix2fv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLUNIFORMMATRIX3FVPROC, glUniformMatrix3fv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLUNIFORMMATRIX4FVPROC, glUniformMatrix4fv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLVALIDATEPROGRAMPROC, glValidateProgram);
OPENGL_RETRIVE_FUNCTIONS(PFNGLVERTEXATTRIB1DPROC, glVertexAttrib1d);
OPENGL_RETRIVE_FUNCTIONS(PFNGLVERTEXATTRIB1DVPROC, glVertexAttrib1dv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLVERTEXATTRIB1FPROC, glVertexAttrib1f);
OPENGL_RETRIVE_FUNCTIONS(PFNGLVERTEXATTRIB1FVPROC, glVertexAttrib1fv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLVERTEXATTRIB1SPROC, glVertexAttrib1s);
OPENGL_RETRIVE_FUNCTIONS(PFNGLVERTEXATTRIB1SVPROC, glVertexAttrib1sv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLVERTEXATTRIB2DPROC, glVertexAttrib2d);
OPENGL_RETRIVE_FUNCTIONS(PFNGLVERTEXATTRIB2DVPROC, glVertexAttrib2dv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLVERTEXATTRIB2FPROC, glVertexAttrib2f);
OPENGL_RETRIVE_FUNCTIONS(PFNGLVERTEXATTRIB2FVPROC, glVertexAttrib2fv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLVERTEXATTRIB2SPROC, glVertexAttrib2s);
OPENGL_RETRIVE_FUNCTIONS(PFNGLVERTEXATTRIB2SVPROC, glVertexAttrib2sv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLVERTEXATTRIB3DPROC, glVertexAttrib3d);
OPENGL_RETRIVE_FUNCTIONS(PFNGLVERTEXATTRIB3DVPROC, glVertexAttrib3dv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLVERTEXATTRIB3FPROC, glVertexAttrib3f);
OPENGL_RETRIVE_FUNCTIONS(PFNGLVERTEXATTRIB3FVPROC, glVertexAttrib3fv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLVERTEXATTRIB3SPROC, glVertexAttrib3s);
OPENGL_RETRIVE_FUNCTIONS(PFNGLVERTEXATTRIB3SVPROC, glVertexAttrib3sv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLVERTEXATTRIB4NBVPROC, glVertexAttrib4Nbv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLVERTEXATTRIB4NIVPROC, glVertexAttrib4Niv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLVERTEXATTRIB4NSVPROC, glVertexAttrib4Nsv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLVERTEXATTRIB4NUBPROC, glVertexAttrib4Nub);
OPENGL_RETRIVE_FUNCTIONS(PFNGLVERTEXATTRIB4NUBVPROC, glVertexAttrib4Nubv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLVERTEXATTRIB4NUIVPROC, glVertexAttrib4Nuiv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLVERTEXATTRIB4NUSVPROC, glVertexAttrib4Nusv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLVERTEXATTRIB4BVPROC, glVertexAttrib4bv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLVERTEXATTRIB4DPROC, glVertexAttrib4d);
OPENGL_RETRIVE_FUNCTIONS(PFNGLVERTEXATTRIB4DVPROC, glVertexAttrib4dv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLVERTEXATTRIB4FPROC, glVertexAttrib4f);
OPENGL_RETRIVE_FUNCTIONS(PFNGLVERTEXATTRIB4FVPROC, glVertexAttrib4fv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLVERTEXATTRIB4IVPROC, glVertexAttrib4iv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLVERTEXATTRIB4SPROC, glVertexAttrib4s);
OPENGL_RETRIVE_FUNCTIONS(PFNGLVERTEXATTRIB4SVPROC, glVertexAttrib4sv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLVERTEXATTRIB4UBVPROC, glVertexAttrib4ubv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLVERTEXATTRIB4UIVPROC, glVertexAttrib4uiv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLVERTEXATTRIB4USVPROC, glVertexAttrib4usv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLVERTEXATTRIBPOINTERPROC, glVertexAttribPointer);

#define OPENGL_RETRIVE_FUNCTIONS_2_1
OPENGL_RETRIVE_FUNCTIONS_2_0
OPENGL_RETRIVE_FUNCTIONS(PFNGLUNIFORMMATRIX2X3FVPROC, glUniformMatrix2x3fv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLUNIFORMMATRIX3X2FVPROC, glUniformMatrix3x2fv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLUNIFORMMATRIX2X4FVPROC, glUniformMatrix2x4fv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLUNIFORMMATRIX4X2FVPROC, glUniformMatrix4x2fv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLUNIFORMMATRIX3X4FVPROC, glUniformMatrix3x4fv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLUNIFORMMATRIX4X3FVPROC, glUniformMatrix4x3fv);

#define OPENGL_RETRIVE_FUNCTIONS_3_0
OPENGL_RETRIVE_FUNCTIONS_2_1
OPENGL_RETRIVE_FUNCTIONS(PFNGLCOLORMASKIPROC, glColorMaski);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETBOOLEANI_VPROC, glGetBooleani_v);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETINTEGERI_VPROC, glGetIntegeri_v);
OPENGL_RETRIVE_FUNCTIONS(PFNGLENABLEIPROC, glEnablei);
OPENGL_RETRIVE_FUNCTIONS(PFNGLDISABLEIPROC, glDisablei);
OPENGL_RETRIVE_FUNCTIONS(PFNGLISENABLEDIPROC, glIsEnabledi);
OPENGL_RETRIVE_FUNCTIONS(PFNGLBEGINTRANSFORMFEEDBACKPROC, glBeginTransformFeedback);
OPENGL_RETRIVE_FUNCTIONS(PFNGLENDTRANSFORMFEEDBACKPROC, glEndTransformFeedback);
OPENGL_RETRIVE_FUNCTIONS(PFNGLBINDBUFFERRANGEPROC, glBindBufferRange);
OPENGL_RETRIVE_FUNCTIONS(PFNGLBINDBUFFERBASEPROC, glBindBufferBase);
OPENGL_RETRIVE_FUNCTIONS(PFNGLTRANSFORMFEEDBACKVARYINGSPROC, glTransformFeedbackVaryings);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETTRANSFORMFEEDBACKVARYINGPROC, glGetTransformFeedbackVarying);
OPENGL_RETRIVE_FUNCTIONS(PFNGLCLAMPCOLORPROC, glClampColor);
OPENGL_RETRIVE_FUNCTIONS(PFNGLBEGINCONDITIONALRENDERPROC, glBeginConditionalRender);
OPENGL_RETRIVE_FUNCTIONS(PFNGLENDCONDITIONALRENDERPROC, glEndConditionalRender);
OPENGL_RETRIVE_FUNCTIONS(PFNGLVERTEXATTRIBIPOINTERPROC, glVertexAttribIPointer);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETVERTEXATTRIBIIVPROC, glGetVertexAttribIiv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETVERTEXATTRIBIUIVPROC, glGetVertexAttribIuiv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLVERTEXATTRIBI1IPROC, glVertexAttribI1i);
OPENGL_RETRIVE_FUNCTIONS(PFNGLVERTEXATTRIBI2IPROC, glVertexAttribI2i);
OPENGL_RETRIVE_FUNCTIONS(PFNGLVERTEXATTRIBI3IPROC, glVertexAttribI3i);
OPENGL_RETRIVE_FUNCTIONS(PFNGLVERTEXATTRIBI4IPROC, glVertexAttribI4i);
OPENGL_RETRIVE_FUNCTIONS(PFNGLVERTEXATTRIBI1UIPROC, glVertexAttribI1ui);
OPENGL_RETRIVE_FUNCTIONS(PFNGLVERTEXATTRIBI2UIPROC, glVertexAttribI2ui);
OPENGL_RETRIVE_FUNCTIONS(PFNGLVERTEXATTRIBI3UIPROC, glVertexAttribI3ui);
OPENGL_RETRIVE_FUNCTIONS(PFNGLVERTEXATTRIBI4UIPROC, glVertexAttribI4ui);
OPENGL_RETRIVE_FUNCTIONS(PFNGLVERTEXATTRIBI1IVPROC, glVertexAttribI1iv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLVERTEXATTRIBI2IVPROC, glVertexAttribI2iv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLVERTEXATTRIBI3IVPROC, glVertexAttribI3iv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLVERTEXATTRIBI4IVPROC, glVertexAttribI4iv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLVERTEXATTRIBI1UIVPROC, glVertexAttribI1uiv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLVERTEXATTRIBI2UIVPROC, glVertexAttribI2uiv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLVERTEXATTRIBI3UIVPROC, glVertexAttribI3uiv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLVERTEXATTRIBI4UIVPROC, glVertexAttribI4uiv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLVERTEXATTRIBI4BVPROC, glVertexAttribI4bv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLVERTEXATTRIBI4SVPROC, glVertexAttribI4sv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLVERTEXATTRIBI4UBVPROC, glVertexAttribI4ubv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLVERTEXATTRIBI4USVPROC, glVertexAttribI4usv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETUNIFORMUIVPROC, glGetUniformuiv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLBINDFRAGDATALOCATIONPROC, glBindFragDataLocation);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETFRAGDATALOCATIONPROC, glGetFragDataLocation);
OPENGL_RETRIVE_FUNCTIONS(PFNGLUNIFORM1UIPROC, glUniform1ui);
OPENGL_RETRIVE_FUNCTIONS(PFNGLUNIFORM2UIPROC, glUniform2ui);
OPENGL_RETRIVE_FUNCTIONS(PFNGLUNIFORM3UIPROC, glUniform3ui);
OPENGL_RETRIVE_FUNCTIONS(PFNGLUNIFORM4UIPROC, glUniform4ui);
OPENGL_RETRIVE_FUNCTIONS(PFNGLUNIFORM1UIVPROC, glUniform1uiv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLUNIFORM2UIVPROC, glUniform2uiv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLUNIFORM3UIVPROC, glUniform3uiv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLUNIFORM4UIVPROC, glUniform4uiv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLTEXPARAMETERIIVPROC, glTexParameterIiv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLTEXPARAMETERIUIVPROC, glTexParameterIuiv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETTEXPARAMETERIIVPROC, glGetTexParameterIiv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETTEXPARAMETERIUIVPROC, glGetTexParameterIuiv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLCLEARBUFFERIVPROC, glClearBufferiv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLCLEARBUFFERUIVPROC, glClearBufferuiv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLCLEARBUFFERFVPROC, glClearBufferfv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLCLEARBUFFERFIPROC, glClearBufferfi);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETSTRINGIPROC, glGetStringi);
OPENGL_RETRIVE_FUNCTIONS(PFNGLISRENDERBUFFERPROC, glIsRenderbuffer);
OPENGL_RETRIVE_FUNCTIONS(PFNGLBINDRENDERBUFFERPROC, glBindRenderbuffer);
OPENGL_RETRIVE_FUNCTIONS(PFNGLDELETERENDERBUFFERSPROC, glDeleteRenderbuffers);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGENRENDERBUFFERSPROC, glGenRenderbuffers);
OPENGL_RETRIVE_FUNCTIONS(PFNGLRENDERBUFFERSTORAGEPROC, glRenderbufferStorage);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETRENDERBUFFERPARAMETERIVPROC, glGetRenderbufferParameteriv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLISFRAMEBUFFERPROC, glIsFramebuffer);
OPENGL_RETRIVE_FUNCTIONS(PFNGLBINDFRAMEBUFFERPROC, glBindFramebuffer);
OPENGL_RETRIVE_FUNCTIONS(PFNGLDELETEFRAMEBUFFERSPROC, glDeleteFramebuffers);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGENFRAMEBUFFERSPROC, glGenFramebuffers);
OPENGL_RETRIVE_FUNCTIONS(PFNGLCHECKFRAMEBUFFERSTATUSPROC, glCheckFramebufferStatus);
OPENGL_RETRIVE_FUNCTIONS(PFNGLFRAMEBUFFERTEXTURE1DPROC, glFramebufferTexture1D);
OPENGL_RETRIVE_FUNCTIONS(PFNGLFRAMEBUFFERTEXTURE2DPROC, glFramebufferTexture2D);
OPENGL_RETRIVE_FUNCTIONS(PFNGLFRAMEBUFFERTEXTURE3DPROC, glFramebufferTexture3D);
OPENGL_RETRIVE_FUNCTIONS(PFNGLFRAMEBUFFERRENDERBUFFERPROC, glFramebufferRenderbuffer);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC, glGetFramebufferAttachmentParameteriv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGENERATEMIPMAPPROC, glGenerateMipmap);
OPENGL_RETRIVE_FUNCTIONS(PFNGLBLITFRAMEBUFFERPROC, glBlitFramebuffer);
OPENGL_RETRIVE_FUNCTIONS(PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC, glRenderbufferStorageMultisample);
OPENGL_RETRIVE_FUNCTIONS(PFNGLFRAMEBUFFERTEXTURELAYERPROC, glFramebufferTextureLayer);
OPENGL_RETRIVE_FUNCTIONS(PFNGLMAPBUFFERRANGEPROC, glMapBufferRange);
OPENGL_RETRIVE_FUNCTIONS(PFNGLFLUSHMAPPEDBUFFERRANGEPROC, glFlushMappedBufferRange);
OPENGL_RETRIVE_FUNCTIONS(PFNGLBINDVERTEXARRAYPROC, glBindVertexArray);
OPENGL_RETRIVE_FUNCTIONS(PFNGLDELETEVERTEXARRAYSPROC, glDeleteVertexArrays);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGENVERTEXARRAYSPROC, glGenVertexArrays);
OPENGL_RETRIVE_FUNCTIONS(PFNGLISVERTEXARRAYPROC, glIsVertexArray);

#define OPENGL_RETRIVE_FUNCTIONS_3_1
OPENGL_RETRIVE_FUNCTIONS_3_0
OPENGL_RETRIVE_FUNCTIONS(PFNGLDRAWARRAYSINSTANCEDPROC, glDrawArraysInstanced);
OPENGL_RETRIVE_FUNCTIONS(PFNGLDRAWELEMENTSINSTANCEDPROC, glDrawElementsInstanced);
OPENGL_RETRIVE_FUNCTIONS(PFNGLTEXBUFFERPROC, glTexBuffer);
OPENGL_RETRIVE_FUNCTIONS(PFNGLPRIMITIVERESTARTINDEXPROC, glPrimitiveRestartIndex);
OPENGL_RETRIVE_FUNCTIONS(PFNGLCOPYBUFFERSUBDATAPROC, glCopyBufferSubData);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETUNIFORMINDICESPROC, glGetUniformIndices);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETACTIVEUNIFORMSIVPROC, glGetActiveUniformsiv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETACTIVEUNIFORMNAMEPROC, glGetActiveUniformName);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETUNIFORMBLOCKINDEXPROC, glGetUniformBlockIndex);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETACTIVEUNIFORMBLOCKIVPROC, glGetActiveUniformBlockiv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC, glGetActiveUniformBlockName);
OPENGL_RETRIVE_FUNCTIONS(PFNGLUNIFORMBLOCKBINDINGPROC, glUniformBlockBinding);

#define LOAD_OPENGL_FUNCTION_3_2
OPENGL_RETRIVE_FUNCTIONS_3_1
OPENGL_RETRIVE_FUNCTIONS(PFNGLDRAWELEMENTSBASEVERTEXPROC, glDrawElementsBaseVertex);
OPENGL_RETRIVE_FUNCTIONS(PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC, glDrawRangeElementsBaseVertex);
OPENGL_RETRIVE_FUNCTIONS(PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC, glDrawElementsInstancedBaseVertex);
OPENGL_RETRIVE_FUNCTIONS(PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC, glMultiDrawElementsBaseVertex);
OPENGL_RETRIVE_FUNCTIONS(PFNGLPROVOKINGVERTEXPROC, glProvokingVertex);
OPENGL_RETRIVE_FUNCTIONS(PFNGLFENCESYNCPROC, glFenceSync);
OPENGL_RETRIVE_FUNCTIONS(PFNGLISSYNCPROC, glIsSync);
OPENGL_RETRIVE_FUNCTIONS(PFNGLDELETESYNCPROC, glDeleteSync);
OPENGL_RETRIVE_FUNCTIONS(PFNGLCLIENTWAITSYNCPROC, glClientWaitSync);
OPENGL_RETRIVE_FUNCTIONS(PFNGLWAITSYNCPROC, glWaitSync);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETINTEGER64VPROC, glGetInteger64v);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETSYNCIVPROC, glGetSynciv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETINTEGER64I_VPROC, glGetInteger64i_v);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETBUFFERPARAMETERI64VPROC, glGetBufferParameteri64v);
OPENGL_RETRIVE_FUNCTIONS(PFNGLFRAMEBUFFERTEXTUREPROC, glFramebufferTexture);
OPENGL_RETRIVE_FUNCTIONS(PFNGLTEXIMAGE2DMULTISAMPLEPROC, glTexImage2DMultisample);
OPENGL_RETRIVE_FUNCTIONS(PFNGLTEXIMAGE3DMULTISAMPLEPROC, glTexImage3DMultisample);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETMULTISAMPLEFVPROC, glGetMultisamplefv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLSAMPLEMASKIPROC, glSampleMaski);

#define OPENGL_RETRIVE_FUNCTIONS_3_3
OPENGL_RETRIVE_FUNCTIONS(PFNGLBINDFRAGDATALOCATIONINDEXEDPROC, glBindFragDataLocationIndexed);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETFRAGDATAINDEXPROC, glGetFragDataIndex);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGENSAMPLERSPROC, glGenSamplers);
OPENGL_RETRIVE_FUNCTIONS(PFNGLDELETESAMPLERSPROC, glDeleteSamplers);
OPENGL_RETRIVE_FUNCTIONS(PFNGLISSAMPLERPROC, glIsSampler);
OPENGL_RETRIVE_FUNCTIONS(PFNGLBINDSAMPLERPROC, glBindSampler);
OPENGL_RETRIVE_FUNCTIONS(PFNGLSAMPLERPARAMETERIPROC, glSamplerParameteri);
OPENGL_RETRIVE_FUNCTIONS(PFNGLSAMPLERPARAMETERIVPROC, glSamplerParameteriv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLSAMPLERPARAMETERFPROC, glSamplerParameterf);
OPENGL_RETRIVE_FUNCTIONS(PFNGLSAMPLERPARAMETERFVPROC, glSamplerParameterfv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLSAMPLERPARAMETERIIVPROC, glSamplerParameterIiv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLSAMPLERPARAMETERIUIVPROC, glSamplerParameterIuiv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETSAMPLERPARAMETERIVPROC, glGetSamplerParameteriv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETSAMPLERPARAMETERIIVPROC, glGetSamplerParameterIiv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETSAMPLERPARAMETERFVPROC, glGetSamplerParameterfv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETSAMPLERPARAMETERIUIVPROC, glGetSamplerParameterIuiv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLQUERYCOUNTERPROC, glQueryCounter);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETQUERYOBJECTI64VPROC, glGetQueryObjecti64v);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETQUERYOBJECTUI64VPROC, glGetQueryObjectui64v);
OPENGL_RETRIVE_FUNCTIONS(PFNGLVERTEXATTRIBDIVISORPROC, glVertexAttribDivisor);
OPENGL_RETRIVE_FUNCTIONS(PFNGLVERTEXATTRIBP1UIPROC, glVertexAttribP1ui);
OPENGL_RETRIVE_FUNCTIONS(PFNGLVERTEXATTRIBP1UIVPROC, glVertexAttribP1uiv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLVERTEXATTRIBP2UIPROC, glVertexAttribP2ui);
OPENGL_RETRIVE_FUNCTIONS(PFNGLVERTEXATTRIBP2UIVPROC, glVertexAttribP2uiv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLVERTEXATTRIBP3UIPROC, glVertexAttribP3ui);
OPENGL_RETRIVE_FUNCTIONS(PFNGLVERTEXATTRIBP3UIVPROC, glVertexAttribP3uiv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLVERTEXATTRIBP4UIPROC, glVertexAttribP4ui);
OPENGL_RETRIVE_FUNCTIONS(PFNGLVERTEXATTRIBP4UIVPROC, glVertexAttribP4uiv);

#define LOAD_OPENGL_FUNCTION_4_0
LOAD_OPENGL_FUNCTION_3_3
OPENGL_RETRIVE_FUNCTIONS(PFNGLMINSAMPLESHADINGPROC, glMinSampleShading);
OPENGL_RETRIVE_FUNCTIONS(PFNGLBLENDEQUATIONIPROC, glBlendEquationi);
OPENGL_RETRIVE_FUNCTIONS(PFNGLBLENDEQUATIONSEPARATEIPROC, glBlendEquationSeparatei);
OPENGL_RETRIVE_FUNCTIONS(PFNGLBLENDFUNCIPROC, glBlendFunci);
OPENGL_RETRIVE_FUNCTIONS(PFNGLBLENDFUNCSEPARATEIPROC, glBlendFuncSeparatei);
OPENGL_RETRIVE_FUNCTIONS(PFNGLDRAWARRAYSINDIRECTPROC, glDrawArraysIndirect);
OPENGL_RETRIVE_FUNCTIONS(PFNGLDRAWELEMENTSINDIRECTPROC, glDrawElementsIndirect);
OPENGL_RETRIVE_FUNCTIONS(PFNGLUNIFORM1DPROC, glUniform1d);
OPENGL_RETRIVE_FUNCTIONS(PFNGLUNIFORM2DPROC, glUniform2d);
OPENGL_RETRIVE_FUNCTIONS(PFNGLUNIFORM3DPROC, glUniform3d);
OPENGL_RETRIVE_FUNCTIONS(PFNGLUNIFORM4DPROC, glUniform4d);
OPENGL_RETRIVE_FUNCTIONS(PFNGLUNIFORM1DVPROC, glUniform1dv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLUNIFORM2DVPROC, glUniform2dv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLUNIFORM3DVPROC, glUniform3dv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLUNIFORM4DVPROC, glUniform4dv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLUNIFORMMATRIX2DVPROC, glUniformMatrix2dv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLUNIFORMMATRIX3DVPROC, glUniformMatrix3dv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLUNIFORMMATRIX4DVPROC, glUniformMatrix4dv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLUNIFORMMATRIX2X3DVPROC, glUniformMatrix2x3dv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLUNIFORMMATRIX2X4DVPROC, glUniformMatrix2x4dv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLUNIFORMMATRIX3X2DVPROC, glUniformMatrix3x2dv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLUNIFORMMATRIX3X4DVPROC, glUniformMatrix3x4dv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLUNIFORMMATRIX4X2DVPROC, glUniformMatrix4x2dv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLUNIFORMMATRIX4X3DVPROC, glUniformMatrix4x3dv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETUNIFORMDVPROC, glGetUniformdv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETSUBROUTINEUNIFORMLOCATIONPROC, glGetSubroutineUniformLocation);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETSUBROUTINEINDEXPROC, glGetSubroutineIndex);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETACTIVESUBROUTINEUNIFORMIVPROC, glGetActiveSubroutineUniformiv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETACTIVESUBROUTINEUNIFORMNAMEPROC, glGetActiveSubroutineUniformName);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETACTIVESUBROUTINENAMEPROC, glGetActiveSubroutineName);
OPENGL_RETRIVE_FUNCTIONS(PFNGLUNIFORMSUBROUTINESUIVPROC, glUniformSubroutinesuiv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETUNIFORMSUBROUTINEUIVPROC, glGetUniformSubroutineuiv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETPROGRAMSTAGEIVPROC, glGetProgramStageiv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLPATCHPARAMETERIPROC, glPatchParameteri);
OPENGL_RETRIVE_FUNCTIONS(PFNGLPATCHPARAMETERFVPROC, glPatchParameterfv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLBINDTRANSFORMFEEDBACKPROC, glBindTransformFeedback);
OPENGL_RETRIVE_FUNCTIONS(PFNGLDELETETRANSFORMFEEDBACKSPROC, glDeleteTransformFeedbacks);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGENTRANSFORMFEEDBACKSPROC, glGenTransformFeedbacks);
OPENGL_RETRIVE_FUNCTIONS(PFNGLISTRANSFORMFEEDBACKPROC, glIsTransformFeedback);
OPENGL_RETRIVE_FUNCTIONS(PFNGLPAUSETRANSFORMFEEDBACKPROC, glPauseTransformFeedback);
OPENGL_RETRIVE_FUNCTIONS(PFNGLRESUMETRANSFORMFEEDBACKPROC, glResumeTransformFeedback);
OPENGL_RETRIVE_FUNCTIONS(PFNGLDRAWTRANSFORMFEEDBACKPROC, glDrawTransformFeedback);
OPENGL_RETRIVE_FUNCTIONS(PFNGLDRAWTRANSFORMFEEDBACKSTREAMPROC, glDrawTransformFeedbackStream);
OPENGL_RETRIVE_FUNCTIONS(PFNGLBEGINQUERYINDEXEDPROC, glBeginQueryIndexed);
OPENGL_RETRIVE_FUNCTIONS(PFNGLENDQUERYINDEXEDPROC, glEndQueryIndexed);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETQUERYINDEXEDIVPROC, glGetQueryIndexediv);

#define LOAD_OPENGL_FUNCTION_4_1
OPENGL_RETRIVE_FUNCTIONS(PFNGLRELEASESHADERCOMPILERPROC, glReleaseShaderCompiler);
OPENGL_RETRIVE_FUNCTIONS(PFNGLSHADERBINARYPROC, glShaderBinary);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETSHADERPRECISIONFORMATPROC, glGetShaderPrecisionFormat);
OPENGL_RETRIVE_FUNCTIONS(PFNGLDEPTHRANGEFPROC, glDepthRangef);
OPENGL_RETRIVE_FUNCTIONS(PFNGLCLEARDEPTHFPROC, glClearDepthf);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETPROGRAMBINARYPROC, glGetProgramBinary);
OPENGL_RETRIVE_FUNCTIONS(PFNGLPROGRAMBINARYPROC, glProgramBinary);
OPENGL_RETRIVE_FUNCTIONS(PFNGLPROGRAMPARAMETERIPROC, glProgramParameteri);
OPENGL_RETRIVE_FUNCTIONS(PFNGLUSEPROGRAMSTAGESPROC, glUseProgramStages);
OPENGL_RETRIVE_FUNCTIONS(PFNGLACTIVESHADERPROGRAMPROC, glActiveShaderProgram);
OPENGL_RETRIVE_FUNCTIONS(PFNGLCREATESHADERPROGRAMVPROC, glCreateShaderProgramv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLBINDPROGRAMPIPELINEPROC, glBindProgramPipeline);
OPENGL_RETRIVE_FUNCTIONS(PFNGLDELETEPROGRAMPIPELINESPROC, glDeleteProgramPipelines);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGENPROGRAMPIPELINESPROC, glGenProgramPipelines);
OPENGL_RETRIVE_FUNCTIONS(PFNGLISPROGRAMPIPELINEPROC, glIsProgramPipeline);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETPROGRAMPIPELINEIVPROC, glGetProgramPipelineiv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLPROGRAMUNIFORM1IPROC, glProgramUniform1i);
OPENGL_RETRIVE_FUNCTIONS(PFNGLPROGRAMUNIFORM1IVPROC, glProgramUniform1iv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLPROGRAMUNIFORM1FPROC, glProgramUniform1f);
OPENGL_RETRIVE_FUNCTIONS(PFNGLPROGRAMUNIFORM1FVPROC, glProgramUniform1fv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLPROGRAMUNIFORM1DPROC, glProgramUniform1d);
OPENGL_RETRIVE_FUNCTIONS(PFNGLPROGRAMUNIFORM1DVPROC, glProgramUniform1dv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLPROGRAMUNIFORM1UIPROC, glProgramUniform1ui);
OPENGL_RETRIVE_FUNCTIONS(PFNGLPROGRAMUNIFORM1UIVPROC, glProgramUniform1uiv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLPROGRAMUNIFORM2IPROC, glProgramUniform2i);
OPENGL_RETRIVE_FUNCTIONS(PFNGLPROGRAMUNIFORM2IVPROC, glProgramUniform2iv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLPROGRAMUNIFORM2FPROC, glProgramUniform2f);
OPENGL_RETRIVE_FUNCTIONS(PFNGLPROGRAMUNIFORM2FVPROC, glProgramUniform2fv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLPROGRAMUNIFORM2DPROC, glProgramUniform2d);
OPENGL_RETRIVE_FUNCTIONS(PFNGLPROGRAMUNIFORM2DVPROC, glProgramUniform2dv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLPROGRAMUNIFORM2UIPROC, glProgramUniform2ui);
OPENGL_RETRIVE_FUNCTIONS(PFNGLPROGRAMUNIFORM2UIVPROC, glProgramUniform2uiv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLPROGRAMUNIFORM3IPROC, glProgramUniform3i);
OPENGL_RETRIVE_FUNCTIONS(PFNGLPROGRAMUNIFORM3IVPROC, glProgramUniform3iv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLPROGRAMUNIFORM3FPROC, glProgramUniform3f);
OPENGL_RETRIVE_FUNCTIONS(PFNGLPROGRAMUNIFORM3FVPROC, glProgramUniform3fv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLPROGRAMUNIFORM3DPROC, glProgramUniform3d);
OPENGL_RETRIVE_FUNCTIONS(PFNGLPROGRAMUNIFORM3DVPROC, glProgramUniform3dv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLPROGRAMUNIFORM3UIPROC, glProgramUniform3ui);
OPENGL_RETRIVE_FUNCTIONS(PFNGLPROGRAMUNIFORM3UIVPROC, glProgramUniform3uiv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLPROGRAMUNIFORM4IPROC, glProgramUniform4i);
OPENGL_RETRIVE_FUNCTIONS(PFNGLPROGRAMUNIFORM4IVPROC, glProgramUniform4iv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLPROGRAMUNIFORM4FPROC, glProgramUniform4f);
OPENGL_RETRIVE_FUNCTIONS(PFNGLPROGRAMUNIFORM4FVPROC, glProgramUniform4fv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLPROGRAMUNIFORM4DPROC, glProgramUniform4d);
OPENGL_RETRIVE_FUNCTIONS(PFNGLPROGRAMUNIFORM4DVPROC, glProgramUniform4dv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLPROGRAMUNIFORM4UIPROC, glProgramUniform4ui);
OPENGL_RETRIVE_FUNCTIONS(PFNGLPROGRAMUNIFORM4UIVPROC, glProgramUniform4uiv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLPROGRAMUNIFORMMATRIX2FVPROC, glProgramUniformMatrix2fv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLPROGRAMUNIFORMMATRIX3FVPROC, glProgramUniformMatrix3fv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLPROGRAMUNIFORMMATRIX4FVPROC, glProgramUniformMatrix4fv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLPROGRAMUNIFORMMATRIX2DVPROC, glProgramUniformMatrix2dv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLPROGRAMUNIFORMMATRIX3DVPROC, glProgramUniformMatrix3dv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLPROGRAMUNIFORMMATRIX4DVPROC, glProgramUniformMatrix4dv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC, glProgramUniformMatrix2x3fv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC, glProgramUniformMatrix3x2fv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC, glProgramUniformMatrix2x4fv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC, glProgramUniformMatrix4x2fv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC, glProgramUniformMatrix3x4fv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC, glProgramUniformMatrix4x3fv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLPROGRAMUNIFORMMATRIX2X3DVPROC, glProgramUniformMatrix2x3dv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLPROGRAMUNIFORMMATRIX3X2DVPROC, glProgramUniformMatrix3x2dv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLPROGRAMUNIFORMMATRIX2X4DVPROC, glProgramUniformMatrix2x4dv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLPROGRAMUNIFORMMATRIX4X2DVPROC, glProgramUniformMatrix4x2dv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLPROGRAMUNIFORMMATRIX3X4DVPROC, glProgramUniformMatrix3x4dv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLPROGRAMUNIFORMMATRIX4X3DVPROC, glProgramUniformMatrix4x3dv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLVALIDATEPROGRAMPIPELINEPROC, glValidateProgramPipeline);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETPROGRAMPIPELINEINFOLOGPROC, glGetProgramPipelineInfoLog);
OPENGL_RETRIVE_FUNCTIONS(PFNGLVERTEXATTRIBL1DPROC, glVertexAttribL1d);
OPENGL_RETRIVE_FUNCTIONS(PFNGLVERTEXATTRIBL2DPROC, glVertexAttribL2d);
OPENGL_RETRIVE_FUNCTIONS(PFNGLVERTEXATTRIBL3DPROC, glVertexAttribL3d);
OPENGL_RETRIVE_FUNCTIONS(PFNGLVERTEXATTRIBL4DPROC, glVertexAttribL4d);
OPENGL_RETRIVE_FUNCTIONS(PFNGLVERTEXATTRIBL1DVPROC, glVertexAttribL1dv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLVERTEXATTRIBL2DVPROC, glVertexAttribL2dv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLVERTEXATTRIBL3DVPROC, glVertexAttribL3dv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLVERTEXATTRIBL4DVPROC, glVertexAttribL4dv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLVERTEXATTRIBLPOINTERPROC, glVertexAttribLPointer);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETVERTEXATTRIBLDVPROC, glGetVertexAttribLdv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLVIEWPORTARRAYVPROC, glViewportArrayv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLVIEWPORTINDEXEDFPROC, glViewportIndexedf);
OPENGL_RETRIVE_FUNCTIONS(PFNGLVIEWPORTINDEXEDFVPROC, glViewportIndexedfv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLSCISSORARRAYVPROC, glScissorArrayv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLSCISSORINDEXEDPROC, glScissorIndexed);
OPENGL_RETRIVE_FUNCTIONS(PFNGLSCISSORINDEXEDVPROC, glScissorIndexedv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLDEPTHRANGEARRAYVPROC, glDepthRangeArrayv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLDEPTHRANGEINDEXEDPROC, glDepthRangeIndexed);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETFLOATI_VPROC, glGetFloati_v);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETDOUBLEI_VPROC, glGetDoublei_v);

#define OPENGL_RETRIVE_FUNCTIONS_4_2
OPENGL_RETRIVE_FUNCTIONS_4_1
OPENGL_RETRIVE_FUNCTIONS(PFNGLDRAWARRAYSINSTANCEDBASEINSTANCEPROC, glDrawArraysInstancedBaseInstance);
OPENGL_RETRIVE_FUNCTIONS(PFNGLDRAWELEMENTSINSTANCEDBASEINSTANCEPROC, glDrawElementsInstancedBaseInstance);
OPENGL_RETRIVE_FUNCTIONS(PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCEPROC, glDrawElementsInstancedBaseVertexBaseInstance);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETINTERNALFORMATIVPROC, glGetInternalformativ);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETACTIVEATOMICCOUNTERBUFFERIVPROC, glGetActiveAtomicCounterBufferiv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLBINDIMAGETEXTUREPROC, glBindImageTexture);
OPENGL_RETRIVE_FUNCTIONS(PFNGLMEMORYBARRIERPROC, glMemoryBarrier);
OPENGL_RETRIVE_FUNCTIONS(PFNGLTEXSTORAGE1DPROC, glTexStorage1D);
OPENGL_RETRIVE_FUNCTIONS(PFNGLTEXSTORAGE2DPROC, glTexStorage2D);
OPENGL_RETRIVE_FUNCTIONS(PFNGLTEXSTORAGE3DPROC, glTexStorage3D);
OPENGL_RETRIVE_FUNCTIONS(PFNGLDRAWTRANSFORMFEEDBACKINSTANCEDPROC, glDrawTransformFeedbackInstanced);
OPENGL_RETRIVE_FUNCTIONS(PFNGLDRAWTRANSFORMFEEDBACKSTREAMINSTANCEDPROC, glDrawTransformFeedbackStreamInstanced);

#define OPENGL_RETRIVE_FUNCTIONS_4_3
OPENGL_RETRIVE_FUNCTIONS_4_2
OPENGL_RETRIVE_FUNCTIONS(PFNGLCLEARBUFFERDATAPROC, glClearBufferData);
OPENGL_RETRIVE_FUNCTIONS(PFNGLCLEARBUFFERSUBDATAPROC, glClearBufferSubData);
OPENGL_RETRIVE_FUNCTIONS(PFNGLDISPATCHCOMPUTEPROC, glDispatchCompute);
OPENGL_RETRIVE_FUNCTIONS(PFNGLDISPATCHCOMPUTEINDIRECTPROC, glDispatchComputeIndirect);
OPENGL_RETRIVE_FUNCTIONS(PFNGLCOPYIMAGESUBDATAPROC, glCopyImageSubData);
OPENGL_RETRIVE_FUNCTIONS(PFNGLFRAMEBUFFERPARAMETERIPROC, glFramebufferParameteri);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETFRAMEBUFFERPARAMETERIVPROC, glGetFramebufferParameteriv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETINTERNALFORMATI64VPROC, glGetInternalformati64v);
OPENGL_RETRIVE_FUNCTIONS(PFNGLINVALIDATETEXSUBIMAGEPROC, glInvalidateTexSubImage);
OPENGL_RETRIVE_FUNCTIONS(PFNGLINVALIDATETEXIMAGEPROC, glInvalidateTexImage);
OPENGL_RETRIVE_FUNCTIONS(PFNGLINVALIDATEBUFFERSUBDATAPROC, glInvalidateBufferSubData);
OPENGL_RETRIVE_FUNCTIONS(PFNGLINVALIDATEBUFFERDATAPROC, glInvalidateBufferData);
OPENGL_RETRIVE_FUNCTIONS(PFNGLINVALIDATEFRAMEBUFFERPROC, glInvalidateFramebuffer);
OPENGL_RETRIVE_FUNCTIONS(PFNGLINVALIDATESUBFRAMEBUFFERPROC, glInvalidateSubFramebuffer);
OPENGL_RETRIVE_FUNCTIONS(PFNGLMULTIDRAWARRAYSINDIRECTPROC, glMultiDrawArraysIndirect);
OPENGL_RETRIVE_FUNCTIONS(PFNGLMULTIDRAWELEMENTSINDIRECTPROC, glMultiDrawElementsIndirect);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETPROGRAMINTERFACEIVPROC, glGetProgramInterfaceiv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETPROGRAMRESOURCEINDEXPROC, glGetProgramResourceIndex);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETPROGRAMRESOURCENAMEPROC, glGetProgramResourceName);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETPROGRAMRESOURCEIVPROC, glGetProgramResourceiv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETPROGRAMRESOURCELOCATIONPROC, glGetProgramResourceLocation);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETPROGRAMRESOURCELOCATIONINDEXPROC, glGetProgramResourceLocationIndex);
OPENGL_RETRIVE_FUNCTIONS(PFNGLSHADERSTORAGEBLOCKBINDINGPROC, glShaderStorageBlockBinding);
OPENGL_RETRIVE_FUNCTIONS(PFNGLTEXBUFFERRANGEPROC, glTexBufferRange);
OPENGL_RETRIVE_FUNCTIONS(PFNGLTEXSTORAGE2DMULTISAMPLEPROC, glTexStorage2DMultisample);
OPENGL_RETRIVE_FUNCTIONS(PFNGLTEXSTORAGE3DMULTISAMPLEPROC, glTexStorage3DMultisample);
OPENGL_RETRIVE_FUNCTIONS(PFNGLTEXTUREVIEWPROC, glTextureView);
OPENGL_RETRIVE_FUNCTIONS(PFNGLBINDVERTEXBUFFERPROC, glBindVertexBuffer);
OPENGL_RETRIVE_FUNCTIONS(PFNGLVERTEXATTRIBFORMATPROC, glVertexAttribFormat);
OPENGL_RETRIVE_FUNCTIONS(PFNGLVERTEXATTRIBIFORMATPROC, glVertexAttribIFormat);
OPENGL_RETRIVE_FUNCTIONS(PFNGLVERTEXATTRIBLFORMATPROC, glVertexAttribLFormat);
OPENGL_RETRIVE_FUNCTIONS(PFNGLVERTEXATTRIBBINDINGPROC, glVertexAttribBinding);
OPENGL_RETRIVE_FUNCTIONS(PFNGLVERTEXBINDINGDIVISORPROC, glVertexBindingDivisor);
OPENGL_RETRIVE_FUNCTIONS(PFNGLDEBUGMESSAGECONTROLPROC, glDebugMessageControl);
OPENGL_RETRIVE_FUNCTIONS(PFNGLDEBUGMESSAGEINSERTPROC, glDebugMessageInsert);
OPENGL_RETRIVE_FUNCTIONS(PFNGLDEBUGMESSAGECALLBACKPROC, glDebugMessageCallback);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETDEBUGMESSAGELOGPROC, glGetDebugMessageLog);
OPENGL_RETRIVE_FUNCTIONS(PFNGLPUSHDEBUGGROUPPROC, glPushDebugGroup);
OPENGL_RETRIVE_FUNCTIONS(PFNGLPOPDEBUGGROUPPROC, glPopDebugGroup);
OPENGL_RETRIVE_FUNCTIONS(PFNGLOBJECTLABELPROC, glObjectLabel);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETOBJECTLABELPROC, glGetObjectLabel);
OPENGL_RETRIVE_FUNCTIONS(PFNGLOBJECTPTRLABELPROC, glObjectPtrLabel);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETOBJECTPTRLABELPROC, glGetObjectPtrLabel);

#define OPENGL_RETRIVE_FUNCTIONS_4_4
OPENGL_RETRIVE_FUNCTIONS_4_3
OPENGL_RETRIVE_FUNCTIONS(PFNGLBUFFERSTORAGEPROC, glBufferStorage);
OPENGL_RETRIVE_FUNCTIONS(PFNGLCLEARTEXIMAGEPROC, glClearTexImage);
OPENGL_RETRIVE_FUNCTIONS(PFNGLCLEARTEXSUBIMAGEPROC, glClearTexSubImage);
OPENGL_RETRIVE_FUNCTIONS(PFNGLBINDBUFFERSBASEPROC, glBindBuffersBase);
OPENGL_RETRIVE_FUNCTIONS(PFNGLBINDBUFFERSRANGEPROC, glBindBuffersRange);
OPENGL_RETRIVE_FUNCTIONS(PFNGLBINDTEXTURESPROC, glBindTextures);
OPENGL_RETRIVE_FUNCTIONS(PFNGLBINDSAMPLERSPROC, glBindSamplers);
OPENGL_RETRIVE_FUNCTIONS(PFNGLBINDIMAGETEXTURESPROC, glBindImageTextures);
OPENGL_RETRIVE_FUNCTIONS(PFNGLBINDVERTEXBUFFERSPROC, glBindVertexBuffers);

#define OPENGL_RETRIVE_FUNCTIONS_4_5
OPENGL_RETRIVE_FUNCTIONS_4_4
OPENGL_RETRIVE_FUNCTIONS(PFNGLCLIPCONTROLPROC, glClipControl);
OPENGL_RETRIVE_FUNCTIONS(PFNGLCREATETRANSFORMFEEDBACKSPROC, glCreateTransformFeedbacks);
OPENGL_RETRIVE_FUNCTIONS(PFNGLTRANSFORMFEEDBACKBUFFERBASEPROC, glTransformFeedbackBufferBase);
OPENGL_RETRIVE_FUNCTIONS(PFNGLTRANSFORMFEEDBACKBUFFERRANGEPROC, glTransformFeedbackBufferRange);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETTRANSFORMFEEDBACKIVPROC, glGetTransformFeedbackiv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETTRANSFORMFEEDBACKI_VPROC, glGetTransformFeedbacki_v);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETTRANSFORMFEEDBACKI64_VPROC, glGetTransformFeedbacki64_v);
OPENGL_RETRIVE_FUNCTIONS(PFNGLCREATEBUFFERSPROC, glCreateBuffers);
OPENGL_RETRIVE_FUNCTIONS(PFNGLNAMEDBUFFERSTORAGEPROC, glNamedBufferStorage);
OPENGL_RETRIVE_FUNCTIONS(PFNGLNAMEDBUFFERDATAPROC, glNamedBufferData);
OPENGL_RETRIVE_FUNCTIONS(PFNGLNAMEDBUFFERSUBDATAPROC, glNamedBufferSubData);
OPENGL_RETRIVE_FUNCTIONS(PFNGLCOPYNAMEDBUFFERSUBDATAPROC, glCopyNamedBufferSubData);
OPENGL_RETRIVE_FUNCTIONS(PFNGLCLEARNAMEDBUFFERDATAPROC, glClearNamedBufferData);
OPENGL_RETRIVE_FUNCTIONS(PFNGLCLEARNAMEDBUFFERSUBDATAPROC, glClearNamedBufferSubData);
OPENGL_RETRIVE_FUNCTIONS(PFNGLMAPNAMEDBUFFERPROC, glMapNamedBuffer);
OPENGL_RETRIVE_FUNCTIONS(PFNGLMAPNAMEDBUFFERRANGEPROC, glMapNamedBufferRange);
OPENGL_RETRIVE_FUNCTIONS(PFNGLUNMAPNAMEDBUFFERPROC, glUnmapNamedBuffer);
OPENGL_RETRIVE_FUNCTIONS(PFNGLFLUSHMAPPEDNAMEDBUFFERRANGEPROC, glFlushMappedNamedBufferRange);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETNAMEDBUFFERPARAMETERIVPROC, glGetNamedBufferParameteriv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETNAMEDBUFFERPARAMETERI64VPROC, glGetNamedBufferParameteri64v);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETNAMEDBUFFERPOINTERVPROC, glGetNamedBufferPointerv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETNAMEDBUFFERSUBDATAPROC, glGetNamedBufferSubData);
OPENGL_RETRIVE_FUNCTIONS(PFNGLCREATEFRAMEBUFFERSPROC, glCreateFramebuffers);
OPENGL_RETRIVE_FUNCTIONS(PFNGLNAMEDFRAMEBUFFERRENDERBUFFERPROC, glNamedFramebufferRenderbuffer);
OPENGL_RETRIVE_FUNCTIONS(PFNGLNAMEDFRAMEBUFFERPARAMETERIPROC, glNamedFramebufferParameteri);
OPENGL_RETRIVE_FUNCTIONS(PFNGLNAMEDFRAMEBUFFERTEXTUREPROC, glNamedFramebufferTexture);
OPENGL_RETRIVE_FUNCTIONS(PFNGLNAMEDFRAMEBUFFERTEXTURELAYERPROC, glNamedFramebufferTextureLayer);
OPENGL_RETRIVE_FUNCTIONS(PFNGLNAMEDFRAMEBUFFERDRAWBUFFERPROC, glNamedFramebufferDrawBuffer);
OPENGL_RETRIVE_FUNCTIONS(PFNGLNAMEDFRAMEBUFFERDRAWBUFFERSPROC, glNamedFramebufferDrawBuffers);
OPENGL_RETRIVE_FUNCTIONS(PFNGLNAMEDFRAMEBUFFERREADBUFFERPROC, glNamedFramebufferReadBuffer);
OPENGL_RETRIVE_FUNCTIONS(PFNGLINVALIDATENAMEDFRAMEBUFFERDATAPROC, glInvalidateNamedFramebufferData);
OPENGL_RETRIVE_FUNCTIONS(PFNGLINVALIDATENAMEDFRAMEBUFFERSUBDATAPROC, glInvalidateNamedFramebufferSubData);
OPENGL_RETRIVE_FUNCTIONS(PFNGLCLEARNAMEDFRAMEBUFFERIVPROC, glClearNamedFramebufferiv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLCLEARNAMEDFRAMEBUFFERUIVPROC, glClearNamedFramebufferuiv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLCLEARNAMEDFRAMEBUFFERFVPROC, glClearNamedFramebufferfv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLCLEARNAMEDFRAMEBUFFERFIPROC, glClearNamedFramebufferfi);
OPENGL_RETRIVE_FUNCTIONS(PFNGLBLITNAMEDFRAMEBUFFERPROC, glBlitNamedFramebuffer);
OPENGL_RETRIVE_FUNCTIONS(PFNGLCHECKNAMEDFRAMEBUFFERSTATUSPROC, glCheckNamedFramebufferStatus);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETNAMEDFRAMEBUFFERPARAMETERIVPROC, glGetNamedFramebufferParameteriv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETNAMEDFRAMEBUFFERATTACHMENTPARAMETERIVPROC, glGetNamedFramebufferAttachmentParameteriv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLCREATERENDERBUFFERSPROC, glCreateRenderbuffers);
OPENGL_RETRIVE_FUNCTIONS(PFNGLNAMEDRENDERBUFFERSTORAGEPROC, glNamedRenderbufferStorage);
OPENGL_RETRIVE_FUNCTIONS(PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEPROC, glNamedRenderbufferStorageMultisample);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETNAMEDRENDERBUFFERPARAMETERIVPROC, glGetNamedRenderbufferParameteriv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLCREATETEXTURESPROC, glCreateTextures);
OPENGL_RETRIVE_FUNCTIONS(PFNGLTEXTUREBUFFERPROC, glTextureBuffer);
OPENGL_RETRIVE_FUNCTIONS(PFNGLTEXTUREBUFFERRANGEPROC, glTextureBufferRange);
OPENGL_RETRIVE_FUNCTIONS(PFNGLTEXTURESTORAGE1DPROC, glTextureStorage1D);
OPENGL_RETRIVE_FUNCTIONS(PFNGLTEXTURESTORAGE2DPROC, glTextureStorage2D);
OPENGL_RETRIVE_FUNCTIONS(PFNGLTEXTURESTORAGE3DPROC, glTextureStorage3D);
OPENGL_RETRIVE_FUNCTIONS(PFNGLTEXTURESTORAGE2DMULTISAMPLEPROC, glTextureStorage2DMultisample);
OPENGL_RETRIVE_FUNCTIONS(PFNGLTEXTURESTORAGE3DMULTISAMPLEPROC, glTextureStorage3DMultisample);
OPENGL_RETRIVE_FUNCTIONS(PFNGLTEXTURESUBIMAGE1DPROC, glTextureSubImage1D);
OPENGL_RETRIVE_FUNCTIONS(PFNGLTEXTURESUBIMAGE2DPROC, glTextureSubImage2D);
OPENGL_RETRIVE_FUNCTIONS(PFNGLTEXTURESUBIMAGE3DPROC, glTextureSubImage3D);
OPENGL_RETRIVE_FUNCTIONS(PFNGLCOMPRESSEDTEXTURESUBIMAGE1DPROC, glCompressedTextureSubImage1D);
OPENGL_RETRIVE_FUNCTIONS(PFNGLCOMPRESSEDTEXTURESUBIMAGE2DPROC, glCompressedTextureSubImage2D);
OPENGL_RETRIVE_FUNCTIONS(PFNGLCOMPRESSEDTEXTURESUBIMAGE3DPROC, glCompressedTextureSubImage3D);
OPENGL_RETRIVE_FUNCTIONS(PFNGLCOPYTEXTURESUBIMAGE1DPROC, glCopyTextureSubImage1D);
OPENGL_RETRIVE_FUNCTIONS(PFNGLCOPYTEXTURESUBIMAGE2DPROC, glCopyTextureSubImage2D);
OPENGL_RETRIVE_FUNCTIONS(PFNGLCOPYTEXTURESUBIMAGE3DPROC, glCopyTextureSubImage3D);
OPENGL_RETRIVE_FUNCTIONS(PFNGLTEXTUREPARAMETERFPROC, glTextureParameterf);
OPENGL_RETRIVE_FUNCTIONS(PFNGLTEXTUREPARAMETERFVPROC, glTextureParameterfv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLTEXTUREPARAMETERIPROC, glTextureParameteri);
OPENGL_RETRIVE_FUNCTIONS(PFNGLTEXTUREPARAMETERIIVPROC, glTextureParameterIiv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLTEXTUREPARAMETERIUIVPROC, glTextureParameterIuiv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLTEXTUREPARAMETERIVPROC, glTextureParameteriv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGENERATETEXTUREMIPMAPPROC, glGenerateTextureMipmap);
OPENGL_RETRIVE_FUNCTIONS(PFNGLBINDTEXTUREUNITPROC, glBindTextureUnit);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETTEXTUREIMAGEPROC, glGetTextureImage);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETCOMPRESSEDTEXTUREIMAGEPROC, glGetCompressedTextureImage);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETTEXTURELEVELPARAMETERFVPROC, glGetTextureLevelParameterfv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETTEXTURELEVELPARAMETERIVPROC, glGetTextureLevelParameteriv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETTEXTUREPARAMETERFVPROC, glGetTextureParameterfv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETTEXTUREPARAMETERIIVPROC, glGetTextureParameterIiv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETTEXTUREPARAMETERIUIVPROC, glGetTextureParameterIuiv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETTEXTUREPARAMETERIVPROC, glGetTextureParameteriv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLCREATEVERTEXARRAYSPROC, glCreateVertexArrays);
OPENGL_RETRIVE_FUNCTIONS(PFNGLDISABLEVERTEXARRAYATTRIBPROC, glDisableVertexArrayAttrib);
OPENGL_RETRIVE_FUNCTIONS(PFNGLENABLEVERTEXARRAYATTRIBPROC, glEnableVertexArrayAttrib);
OPENGL_RETRIVE_FUNCTIONS(PFNGLVERTEXARRAYELEMENTBUFFERPROC, glVertexArrayElementBuffer);
OPENGL_RETRIVE_FUNCTIONS(PFNGLVERTEXARRAYVERTEXBUFFERPROC, glVertexArrayVertexBuffer);
OPENGL_RETRIVE_FUNCTIONS(PFNGLVERTEXARRAYVERTEXBUFFERSPROC, glVertexArrayVertexBuffers);
OPENGL_RETRIVE_FUNCTIONS(PFNGLVERTEXARRAYATTRIBBINDINGPROC, glVertexArrayAttribBinding);
OPENGL_RETRIVE_FUNCTIONS(PFNGLVERTEXARRAYATTRIBFORMATPROC, glVertexArrayAttribFormat);
OPENGL_RETRIVE_FUNCTIONS(PFNGLVERTEXARRAYATTRIBIFORMATPROC, glVertexArrayAttribIFormat);
OPENGL_RETRIVE_FUNCTIONS(PFNGLVERTEXARRAYATTRIBLFORMATPROC, glVertexArrayAttribLFormat);
OPENGL_RETRIVE_FUNCTIONS(PFNGLVERTEXARRAYBINDINGDIVISORPROC, glVertexArrayBindingDivisor);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETVERTEXARRAYIVPROC, glGetVertexArrayiv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETVERTEXARRAYINDEXEDIVPROC, glGetVertexArrayIndexediv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETVERTEXARRAYINDEXED64IVPROC, glGetVertexArrayIndexed64iv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLCREATESAMPLERSPROC, glCreateSamplers);
OPENGL_RETRIVE_FUNCTIONS(PFNGLCREATEPROGRAMPIPELINESPROC, glCreateProgramPipelines);
OPENGL_RETRIVE_FUNCTIONS(PFNGLCREATEQUERIESPROC, glCreateQueries);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETQUERYBUFFEROBJECTI64VPROC, glGetQueryBufferObjecti64v);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETQUERYBUFFEROBJECTIVPROC, glGetQueryBufferObjectiv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETQUERYBUFFEROBJECTUI64VPROC, glGetQueryBufferObjectui64v);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETQUERYBUFFEROBJECTUIVPROC, glGetQueryBufferObjectuiv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLMEMORYBARRIERBYREGIONPROC, glMemoryBarrierByRegion);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETTEXTURESUBIMAGEPROC, glGetTextureSubImage);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETCOMPRESSEDTEXTURESUBIMAGEPROC, glGetCompressedTextureSubImage);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETGRAPHICSRESETSTATUSPROC, glGetGraphicsResetStatus);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETNCOMPRESSEDTEXIMAGEPROC, glGetnCompressedTexImage);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETNTEXIMAGEPROC, glGetnTexImage);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETNUNIFORMDVPROC, glGetnUniformdv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETNUNIFORMFVPROC, glGetnUniformfv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETNUNIFORMIVPROC, glGetnUniformiv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLGETNUNIFORMUIVPROC, glGetnUniformuiv);
OPENGL_RETRIVE_FUNCTIONS(PFNGLREADNPIXELSPROC, glReadnPixels);
OPENGL_RETRIVE_FUNCTIONS(PFNGLTEXTUREBARRIERPROC, glTextureBarrier);

#define OPENGL_RETRIVE_FUNCTIONS_4_6
OPENGL_RETRIVE_FUNCTIONS_4_5
OPENGL_RETRIVE_FUNCTIONS(PFNGLSPECIALIZESHADERPROC, glSpecializeShader);
OPENGL_RETRIVE_FUNCTIONS(PFNGLMULTIDRAWARRAYSINDIRECTCOUNTPROC, glMultiDrawArraysIndirectCount);
OPENGL_RETRIVE_FUNCTIONS(PFNGLMULTIDRAWELEMENTSINDIRECTCOUNTPROC, glMultiDrawElementsIndirectCount);
OPENGL_RETRIVE_FUNCTIONS(PFNGLPOLYGONOFFSETCLAMPPROC, glPolygonOffsetClamp);

void
WIN32OpenglRetriveFunctions(uint32_t major, uint32_t minor) {
    switch(major) {
        case 1:
        {
            if (minor == 0) { OPENGL_RETRIVE_FUNCTIONS_1_0 }
            if (minor == 1) { OPENGL_RETRIVE_FUNCTIONS_1_1 }
            if (minor == 2) { OPENGL_RETRIVE_FUNCTIONS_1_2 }
            if (minor == 3) { OPENGL_RETRIVE_FUNCTIONS_1_3 }
            if (minor == 4) { OPENGL_RETRIVE_FUNCTIONS_1_4 }
            if (minor == 5) { OPENGL_RETRIVE_FUNCTIONS_1_5 }
        }
        break;
        case 2:
        {
            if (minor == 0) { OPENGL_RETRIVE_FUNCTIONS_2_0 }
            if (minor == 1) { OPENGL_RETRIVE_FUNCTIONS_2_1 }
        }
        break;
        case 3:
        {
            if (minor == 0) { OPENGL_RETRIVE_FUNCTIONS_3_0 }
            if (minor == 1) { OPENGL_RETRIVE_FUNCTIONS_3_1 }
            if (minor == 2) { OPENGL_RETRIVE_FUNCTIONS_3_2 }
            if (minor == 3) { OPENGL_RETRIVE_FUNCTIONS_3_3 }
        }
        break;
        case 4:
        {
            if (minor == 0) { OPENGL_RETRIVE_FUNCTIONS_4_0 }
            if (minor == 1) { OPENGL_RETRIVE_FUNCTIONS_4_1 }
            if (minor == 2) { OPENGL_RETRIVE_FUNCTIONS_4_2 }
            if (minor == 3) { OPENGL_RETRIVE_FUNCTIONS_4_3 }
            if (minor == 4) { OPENGL_RETRIVE_FUNCTIONS_4_4 }
            if (minor == 5) { OPENGL_RETRIVE_FUNCTIONS_4_5 }
            if (minor == 6) { OPENGL_RETRIVE_FUNCTIONS_4_6 }
        }
        break;
        default:
        {
        }
        break;
    }
}


#endif WIN32_OPENGL_LOADER // #ifndef WIN32_OPENGL_LOADER
