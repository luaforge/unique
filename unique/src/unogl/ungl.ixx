
module gl{
  // OpenGL functions
  typedef unsigned int GLenum;
  typedef unsigned char GLboolean;
  typedef unsigned int GLbitfield;
  typedef signed char GLbyte;
  typedef short GLshort;
  typedef int GLint;
  typedef int GLsizei;
  typedef unsigned char GLubyte;
  typedef unsigned short GLushort;
  typedef unsigned int GLuint;
  typedef float GLfloat;
  typedef float GLclampf;
  typedef double GLdouble;
  typedef double GLclampd;
  typedef void GLvoid;

  /* Version */
#define GL_VERSION_1_1

  /* AttribMask */
#define GL_CURRENT_BIT
#define GL_POINT_BIT
#define GL_LINE_BIT
#define GL_POLYGON_BIT
#define GL_POLYGON_STIPPLE_BIT
#define GL_PIXEL_MODE_BIT
#define GL_LIGHTING_BIT
#define GL_FOG_BIT
#define GL_DEPTH_BUFFER_BIT
#define GL_ACCUM_BUFFER_BIT
#define GL_STENCIL_BUFFER_BIT
#define GL_VIEWPORT_BIT
#define GL_TRANSFORM_BIT
#define GL_ENABLE_BIT
#define GL_COLOR_BUFFER_BIT
#define GL_HINT_BIT
#define GL_EVAL_BIT
#define GL_LIST_BIT
#define GL_TEXTURE_BIT
#define GL_SCISSOR_BIT
#define GL_ALL_ATTRIB_BITS

  /* ClientAttribMask */
#define GL_CLIENT_PIXEL_STORE_BIT
#define GL_CLIENT_VERTEX_ARRAY_BIT
#define GL_CLIENT_ALL_ATTRIB_BITS

  /* Boolean */
#define GL_FALSE
#define GL_TRUE

  /* BeginMode */
#define GL_POINTS
#define GL_LINES
#define GL_LINE_LOOP
#define GL_LINE_STRIP
#define GL_TRIANGLES
#define GL_TRIANGLE_STRIP
#define GL_TRIANGLE_FAN
#define GL_QUADS
#define GL_QUAD_STRIP
#define GL_POLYGON

  /* AccumOp */
#define GL_ACCUM
#define GL_LOAD
#define GL_RETURN
#define GL_MULT
#define GL_ADD

  /* AlphaFunction */
#define GL_NEVER
#define GL_LESS
#define GL_EQUAL
#define GL_LEQUAL
#define GL_GREATER
#define GL_NOTEQUAL
#define GL_GEQUAL
#define GL_ALWAYS

  /* BlendingFactorDest */
#define GL_ZERO
#define GL_ONE
#define GL_SRC_COLOR
#define GL_ONE_MINUS_SRC_COLOR
#define GL_SRC_ALPHA
#define GL_ONE_MINUS_SRC_ALPHA
#define GL_DST_ALPHA
#define GL_ONE_MINUS_DST_ALPHA

  /* BlendingFactorSrc */
#define GL_DST_COLOR
#define GL_ONE_MINUS_DST_COLOR
#define GL_SRC_ALPHA_SATURATE

  /* DrawBufferMode */
#define GL_NONE
#define GL_FRONT_LEFT
#define GL_FRONT_RIGHT
#define GL_BACK_LEFT
#define GL_BACK_RIGHT
#define GL_FRONT
#define GL_BACK
#define GL_LEFT
#define GL_RIGHT
#define GL_FRONT_AND_BACK
#define GL_AUX0
#define GL_AUX1
#define GL_AUX2
#define GL_AUX3

  /* ErrorCode */
#define GL_NO_ERROR
#define GL_INVALID_ENUM
#define GL_INVALID_VALUE
#define GL_INVALID_OPERATION
#define GL_STACK_OVERFLOW
#define GL_STACK_UNDERFLOW
#define GL_OUT_OF_MEMORY
#define GL_TABLE_TOO_LARGE

  /* FeedbackType */
#define GL_2D
#define GL_3D
#define GL_3D_COLOR
#define GL_3D_COLOR_TEXTURE
#define GL_4D_COLOR_TEXTURE

  /* FeedBackToken */
#define GL_PASS_THROUGH_TOKEN
#define GL_POINT_TOKEN
#define GL_LINE_TOKEN
#define GL_POLYGON_TOKEN
#define GL_BITMAP_TOKEN
#define GL_DRAW_PIXEL_TOKEN
#define GL_COPY_PIXEL_TOKEN
#define GL_LINE_RESET_TOKEN

  /* FogMode */
#define GL_EXP
#define GL_EXP2

  /* FrontFaceDirection */
#define GL_CW
#define GL_CCW

  /* GetMapQuery */
#define GL_COEFF
#define GL_ORDER
#define GL_DOMAIN

  /* GetPixelMap */
#define GL_PIXEL_MAP_I_TO_I
#define GL_PIXEL_MAP_S_TO_S
#define GL_PIXEL_MAP_I_TO_R
#define GL_PIXEL_MAP_I_TO_G
#define GL_PIXEL_MAP_I_TO_B
#define GL_PIXEL_MAP_I_TO_A
#define GL_PIXEL_MAP_R_TO_R
#define GL_PIXEL_MAP_G_TO_G
#define GL_PIXEL_MAP_B_TO_B
#define GL_PIXEL_MAP_A_TO_A

  /* GetPointervPName */
#define GL_VERTEX_ARRAY_POINTER
#define GL_NORMAL_ARRAY_POINTER
#define GL_COLOR_ARRAY_POINTER
#define GL_INDEX_ARRAY_POINTER
#define GL_TEXTURE_COORD_ARRAY_POINTER
#define GL_EDGE_FLAG_ARRAY_POINTER

  /* GetPName */
#define GL_CURRENT_COLOR
#define GL_CURRENT_INDEX
#define GL_CURRENT_NORMAL
#define GL_CURRENT_TEXTURE_COORDS
#define GL_CURRENT_RASTER_COLOR
#define GL_CURRENT_RASTER_INDEX
#define GL_CURRENT_RASTER_TEXTURE_COORDS
#define GL_CURRENT_RASTER_POSITION
#define GL_CURRENT_RASTER_POSITION_VALID
#define GL_CURRENT_RASTER_DISTANCE
#define GL_POINT_SMOOTH
#define GL_POINT_SIZE
#define GL_SMOOTH_POINT_SIZE_RANGE
#define GL_SMOOTH_POINT_SIZE_GRANULARITY
#define GL_POINT_SIZE_RANGE
#define GL_POINT_SIZE_GRANULARITY
#define GL_LINE_SMOOTH
#define GL_LINE_WIDTH
#define GL_SMOOTH_LINE_WIDTH_RANGE
#define GL_SMOOTH_LINE_WIDTH_GRANULARITY
#define GL_LINE_WIDTH_RANGE
#define GL_LINE_WIDTH_GRANULARITY
#define GL_LINE_STIPPLE
#define GL_LINE_STIPPLE_PATTERN
#define GL_LINE_STIPPLE_REPEAT
#define GL_LIST_MODE
#define GL_MAX_LIST_NESTING
#define GL_LIST_BASE
#define GL_LIST_INDEX
#define GL_POLYGON_MODE
#define GL_POLYGON_SMOOTH
#define GL_POLYGON_STIPPLE
#define GL_EDGE_FLAG
#define GL_CULL_FACE
#define GL_CULL_FACE_MODE
#define GL_FRONT_FACE
#define GL_LIGHTING
#define GL_LIGHT_MODEL_LOCAL_VIEWER
#define GL_LIGHT_MODEL_TWO_SIDE
#define GL_LIGHT_MODEL_AMBIENT
#define GL_SHADE_MODEL
#define GL_COLOR_MATERIAL_FACE
#define GL_COLOR_MATERIAL_PARAMETER
#define GL_COLOR_MATERIAL
#define GL_FOG
#define GL_FOG_INDEX
#define GL_FOG_DENSITY
#define GL_FOG_START
#define GL_FOG_END
#define GL_FOG_MODE
#define GL_FOG_COLOR
#define GL_DEPTH_RANGE
#define GL_DEPTH_TEST
#define GL_DEPTH_WRITEMASK
#define GL_DEPTH_CLEAR_VALUE
#define GL_DEPTH_FUNC
#define GL_ACCUM_CLEAR_VALUE
#define GL_STENCIL_TEST
#define GL_STENCIL_CLEAR_VALUE
#define GL_STENCIL_FUNC
#define GL_STENCIL_VALUE_MASK
#define GL_STENCIL_FAIL
#define GL_STENCIL_PASS_DEPTH_FAIL
#define GL_STENCIL_PASS_DEPTH_PASS
#define GL_STENCIL_REF
#define GL_STENCIL_WRITEMASK
#define GL_MATRIX_MODE
#define GL_NORMALIZE
#define GL_VIEWPORT
#define GL_MODELVIEW_STACK_DEPTH
#define GL_PROJECTION_STACK_DEPTH
#define GL_TEXTURE_STACK_DEPTH
#define GL_MODELVIEW_MATRIX
#define GL_PROJECTION_MATRIX
#define GL_TEXTURE_MATRIX
#define GL_ATTRIB_STACK_DEPTH
#define GL_CLIENT_ATTRIB_STACK_DEPTH
#define GL_ALPHA_TEST
#define GL_ALPHA_TEST_FUNC
#define GL_ALPHA_TEST_REF
#define GL_DITHER
#define GL_BLEND_DST
#define GL_BLEND_SRC
#define GL_BLEND
#define GL_LOGIC_OP_MODE
#define GL_INDEX_LOGIC_OP
#define GL_LOGIC_OP
#define GL_COLOR_LOGIC_OP
#define GL_AUX_BUFFERS
#define GL_DRAW_BUFFER
#define GL_READ_BUFFER
#define GL_SCISSOR_BOX
#define GL_SCISSOR_TEST
#define GL_INDEX_CLEAR_VALUE
#define GL_INDEX_WRITEMASK
#define GL_COLOR_CLEAR_VALUE
#define GL_COLOR_WRITEMASK
#define GL_INDEX_MODE
#define GL_RGBA_MODE
#define GL_DOUBLEBUFFER
#define GL_STEREO
#define GL_RENDER_MODE
#define GL_PERSPECTIVE_CORRECTION_HINT
#define GL_POINT_SMOOTH_HINT
#define GL_LINE_SMOOTH_HINT
#define GL_POLYGON_SMOOTH_HINT
#define GL_FOG_HINT
#define GL_TEXTURE_GEN_S
#define GL_TEXTURE_GEN_T
#define GL_TEXTURE_GEN_R
#define GL_TEXTURE_GEN_Q
#define GL_PIXEL_MAP_I_TO_I_SIZE
#define GL_PIXEL_MAP_S_TO_S_SIZE
#define GL_PIXEL_MAP_I_TO_R_SIZE
#define GL_PIXEL_MAP_I_TO_G_SIZE
#define GL_PIXEL_MAP_I_TO_B_SIZE
#define GL_PIXEL_MAP_I_TO_A_SIZE
#define GL_PIXEL_MAP_R_TO_R_SIZE
#define GL_PIXEL_MAP_G_TO_G_SIZE
#define GL_PIXEL_MAP_B_TO_B_SIZE
#define GL_PIXEL_MAP_A_TO_A_SIZE
#define GL_UNPACK_SWAP_BYTES
#define GL_UNPACK_LSB_FIRST
#define GL_UNPACK_ROW_LENGTH
#define GL_UNPACK_SKIP_ROWS
#define GL_UNPACK_SKIP_PIXELS
#define GL_UNPACK_ALIGNMENT
#define GL_PACK_SWAP_BYTES
#define GL_PACK_LSB_FIRST
#define GL_PACK_ROW_LENGTH
#define GL_PACK_SKIP_ROWS
#define GL_PACK_SKIP_PIXELS
#define GL_PACK_ALIGNMENT
#define GL_MAP_COLOR
#define GL_MAP_STENCIL
#define GL_INDEX_SHIFT
#define GL_INDEX_OFFSET
#define GL_RED_SCALE
#define GL_RED_BIAS
#define GL_ZOOM_X
#define GL_ZOOM_Y
#define GL_GREEN_SCALE
#define GL_GREEN_BIAS
#define GL_BLUE_SCALE
#define GL_BLUE_BIAS
#define GL_ALPHA_SCALE
#define GL_ALPHA_BIAS
#define GL_DEPTH_SCALE
#define GL_DEPTH_BIAS
#define GL_MAX_EVAL_ORDER
#define GL_MAX_LIGHTS
#define GL_MAX_CLIP_PLANES
#define GL_MAX_TEXTURE_SIZE
#define GL_MAX_PIXEL_MAP_TABLE
#define GL_MAX_ATTRIB_STACK_DEPTH
#define GL_MAX_MODELVIEW_STACK_DEPTH
#define GL_MAX_NAME_STACK_DEPTH
#define GL_MAX_PROJECTION_STACK_DEPTH
#define GL_MAX_TEXTURE_STACK_DEPTH
#define GL_MAX_VIEWPORT_DIMS
#define GL_MAX_CLIENT_ATTRIB_STACK_DEPTH
#define GL_SUBPIXEL_BITS
#define GL_INDEX_BITS
#define GL_RED_BITS
#define GL_GREEN_BITS
#define GL_BLUE_BITS
#define GL_ALPHA_BITS
#define GL_DEPTH_BITS
#define GL_STENCIL_BITS
#define GL_ACCUM_RED_BITS
#define GL_ACCUM_GREEN_BITS
#define GL_ACCUM_BLUE_BITS
#define GL_ACCUM_ALPHA_BITS
#define GL_NAME_STACK_DEPTH
#define GL_AUTO_NORMAL
#define GL_MAP1_COLOR_4
#define GL_MAP1_INDEX
#define GL_MAP1_NORMAL
#define GL_MAP1_TEXTURE_COORD_1
#define GL_MAP1_TEXTURE_COORD_2
#define GL_MAP1_TEXTURE_COORD_3
#define GL_MAP1_TEXTURE_COORD_4
#define GL_MAP1_VERTEX_3
#define GL_MAP1_VERTEX_4
#define GL_MAP2_COLOR_4
#define GL_MAP2_INDEX
#define GL_MAP2_NORMAL
#define GL_MAP2_TEXTURE_COORD_1
#define GL_MAP2_TEXTURE_COORD_2
#define GL_MAP2_TEXTURE_COORD_3
#define GL_MAP2_TEXTURE_COORD_4
#define GL_MAP2_VERTEX_3
#define GL_MAP2_VERTEX_4
#define GL_MAP1_GRID_DOMAIN
#define GL_MAP1_GRID_SEGMENTS
#define GL_MAP2_GRID_DOMAIN
#define GL_MAP2_GRID_SEGMENTS
#define GL_TEXTURE_1D
#define GL_TEXTURE_2D
#define GL_FEEDBACK_BUFFER_POINTER
#define GL_FEEDBACK_BUFFER_SIZE
#define GL_FEEDBACK_BUFFER_TYPE
#define GL_SELECTION_BUFFER_POINTER
#define GL_SELECTION_BUFFER_SIZE
#define GL_POLYGON_OFFSET_UNITS
#define GL_POLYGON_OFFSET_POINT
#define GL_POLYGON_OFFSET_LINE
#define GL_POLYGON_OFFSET_FILL
#define GL_POLYGON_OFFSET_FACTOR
#define GL_TEXTURE_BINDING_1D
#define GL_TEXTURE_BINDING_2D
#define GL_TEXTURE_BINDING_3D
#define GL_VERTEX_ARRAY
#define GL_NORMAL_ARRAY
#define GL_COLOR_ARRAY
#define GL_INDEX_ARRAY
#define GL_TEXTURE_COORD_ARRAY
#define GL_EDGE_FLAG_ARRAY
#define GL_VERTEX_ARRAY_SIZE
#define GL_VERTEX_ARRAY_TYPE
#define GL_VERTEX_ARRAY_STRIDE
#define GL_NORMAL_ARRAY_TYPE
#define GL_NORMAL_ARRAY_STRIDE
#define GL_COLOR_ARRAY_SIZE
#define GL_COLOR_ARRAY_TYPE
#define GL_COLOR_ARRAY_STRIDE
#define GL_INDEX_ARRAY_TYPE
#define GL_INDEX_ARRAY_STRIDE
#define GL_TEXTURE_COORD_ARRAY_SIZE
#define GL_TEXTURE_COORD_ARRAY_TYPE
#define GL_TEXTURE_COORD_ARRAY_STRIDE
#define GL_EDGE_FLAG_ARRAY_STRIDE
  /*      GL_VERTEX_ARRAY_COUNT_EXT */
  /*      GL_NORMAL_ARRAY_COUNT_EXT */
  /*      GL_COLOR_ARRAY_COUNT_EXT */
  /*      GL_INDEX_ARRAY_COUNT_EXT */
  /*      GL_TEXTURE_COORD_ARRAY_COUNT_EXT */
  /*      GL_EDGE_FLAG_ARRAY_COUNT_EXT */

  /* GetTextureParameter */
  /*      GL_TEXTURE_MAG_FILTER */
  /*      GL_TEXTURE_MIN_FILTER */
  /*      GL_TEXTURE_WRAP_S */
  /*      GL_TEXTURE_WRAP_T */
#define GL_TEXTURE_WIDTH
#define GL_TEXTURE_HEIGHT
#define GL_TEXTURE_INTERNAL_FORMAT
#define GL_TEXTURE_COMPONENTS
#define GL_TEXTURE_BORDER_COLOR
#define GL_TEXTURE_BORDER
#define GL_TEXTURE_RED_SIZE
#define GL_TEXTURE_GREEN_SIZE
#define GL_TEXTURE_BLUE_SIZE
#define GL_TEXTURE_ALPHA_SIZE
#define GL_TEXTURE_LUMINANCE_SIZE
#define GL_TEXTURE_INTENSITY_SIZE
#define GL_TEXTURE_PRIORITY
#define GL_TEXTURE_RESIDENT

  /* HintMode */
#define GL_DONT_CARE
#define GL_FASTEST
#define GL_NICEST

  /* HintTarget */
  /*      GL_PERSPECTIVE_CORRECTION_HINT */
  /*      GL_POINT_SMOOTH_HINT */
  /*      GL_LINE_SMOOTH_HINT */
  /*      GL_POLYGON_SMOOTH_HINT */
  /*      GL_FOG_HINT */

  /* IndexMaterialParameterSGI */
  /*      GL_INDEX_OFFSET */

  /* IndexPointerType */
  /*      GL_SHORT */
  /*      GL_INT */
  /*      GL_FLOAT */
  /*      GL_DOUBLE */

  /* IndexFunctionSGI */
  /*      GL_NEVER */
  /*      GL_LESS */
  /*      GL_EQUAL */
  /*      GL_LEQUAL */
  /*      GL_GREATER */
  /*      GL_NOTEQUAL */
  /*      GL_GEQUAL */
  /*      GL_ALWAYS */

  /* LightModelParameter */
  /*      GL_LIGHT_MODEL_AMBIENT */
  /*      GL_LIGHT_MODEL_LOCAL_VIEWER */
  /*      GL_LIGHT_MODEL_TWO_SIDE */

  /* LightParameter */
#define GL_AMBIENT
#define GL_DIFFUSE
#define GL_SPECULAR
#define GL_POSITION
#define GL_SPOT_DIRECTION
#define GL_SPOT_EXPONENT
#define GL_SPOT_CUTOFF
#define GL_CONSTANT_ATTENUATION
#define GL_LINEAR_ATTENUATION
#define GL_QUADRATIC_ATTENUATION

  /* ListMode */
#define GL_COMPILE
#define GL_COMPILE_AND_EXECUTE

  /* DataType */
#define GL_BYTE
#define GL_UNSIGNED_BYTE
#define GL_SHORT
#define GL_UNSIGNED_SHORT
#define GL_INT
#define GL_UNSIGNED_INT
#define GL_FLOAT
#define GL_2_BYTES
#define GL_3_BYTES
#define GL_4_BYTES
#define GL_DOUBLE
  //#define GL_DOUBLE_EXT

  /* LogicOp */
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

  /* MaterialParameter */
#define GL_EMISSION                       0x1600
#define GL_SHININESS                      0x1601
#define GL_AMBIENT_AND_DIFFUSE            0x1602
#define GL_COLOR_INDEXES                  0x1603
  /*      GL_AMBIENT */
  /*      GL_DIFFUSE */
  /*      GL_SPECULAR */

  /* MatrixMode */
#define GL_MODELVIEW                      0x1700
#define GL_PROJECTION                     0x1701
#define GL_TEXTURE                        0x1702

  /* PixelCopyType */
#define GL_COLOR                          0x1800
#define GL_DEPTH                          0x1801
#define GL_STENCIL                        0x1802

  /* PixelFormat */
#define GL_COLOR_INDEX                    0x1900
#define GL_STENCIL_INDEX                  0x1901
#define GL_DEPTH_COMPONENT                0x1902
#define GL_RED                            0x1903
#define GL_GREEN                          0x1904
#define GL_BLUE                           0x1905
#define GL_ALPHA                          0x1906
#define GL_RGB                            0x1907
#define GL_RGBA                           0x1908
#define GL_LUMINANCE                      0x1909
#define GL_LUMINANCE_ALPHA                0x190A
  /*      GL_ABGR_EXT */

  /* PixelType */
#define GL_BITMAP
  /*      GL_BYTE */
  /*      GL_UNSIGNED_BYTE */
  /*      GL_SHORT */
  /*      GL_UNSIGNED_SHORT */
  /*      GL_INT */
  /*      GL_UNSIGNED_INT */
  /*      GL_FLOAT */
  /*      GL_UNSIGNED_BYTE_3_3_2_EXT */
  /*      GL_UNSIGNED_SHORT_4_4_4_4_EXT */
  /*      GL_UNSIGNED_SHORT_5_5_5_1_EXT */
  /*      GL_UNSIGNED_INT_8_8_8_8_EXT */
  /*      GL_UNSIGNED_INT_10_10_10_2_EXT */

  /* PolygonMode */
#define GL_POINT
#define GL_LINE
#define GL_FILL

  /* ReadBufferMode */
  /*      GL_FRONT_LEFT */
  /*      GL_FRONT_RIGHT */
  /*      GL_BACK_LEFT */
  /*      GL_BACK_RIGHT */
  /*      GL_FRONT */
  /*      GL_BACK */
  /*      GL_LEFT */
  /*      GL_RIGHT */
  /*      GL_AUX0 */
  /*      GL_AUX1 */
  /*      GL_AUX2 */
  /*      GL_AUX3 */

  /* RenderingMode */
#define GL_RENDER
#define GL_FEEDBACK
#define GL_SELECT

  /* ShadingModel */
#define GL_FLAT                           0x1D00
#define GL_SMOOTH                         0x1D01

  /* StencilFunction */
  /*      GL_NEVER */
  /*      GL_LESS */
  /*      GL_EQUAL */
  /*      GL_LEQUAL */
  /*      GL_GREATER */
  /*      GL_NOTEQUAL */
  /*      GL_GEQUAL */
  /*      GL_ALWAYS */

  /* StencilOp */
  /*      GL_ZERO */
#define GL_KEEP                           0x1E00
#define GL_REPLACE                        0x1E01
#define GL_INCR                           0x1E02
#define GL_DECR                           0x1E03
  /*      GL_INVERT */

  /* StringName */
#define GL_VENDOR                         0x1F00
#define GL_RENDERER                       0x1F01
#define GL_VERSION                        0x1F02
#define GL_EXTENSIONS                     0x1F03

  /* TexCoordPointerType */
  /*      GL_SHORT */
  /*      GL_INT */
  /*      GL_FLOAT */
  /*      GL_DOUBLE */

  /* TextureCoordName */
#define GL_S                              0x2000
#define GL_T                              0x2001
#define GL_R                              0x2002
#define GL_Q                              0x2003

  /* TextureEnvMode */
#define GL_MODULATE                       0x2100
#define GL_DECAL                          0x2101
  /*      GL_BLEND */
  /*      GL_REPLACE */
  /*      GL_ADD */

  /* TextureEnvParameter */
#define GL_TEXTURE_ENV_MODE               0x2200
#define GL_TEXTURE_ENV_COLOR              0x2201

  /* TextureEnvTarget */
#define GL_TEXTURE_ENV                    0x2300

  /* TextureGenMode */
#define GL_EYE_LINEAR                     0x2400
#define GL_OBJECT_LINEAR                  0x2401
#define GL_SPHERE_MAP                     0x2402

  /* TextureGenParameter */
#define GL_TEXTURE_GEN_MODE               0x2500
#define GL_OBJECT_PLANE                   0x2501
#define GL_EYE_PLANE                      0x2502

  /* TextureMagFilter */
#define GL_NEAREST                        0x2600
#define GL_LINEAR                         0x2601

  /* TextureMinFilter */
  /*      GL_NEAREST */
  /*      GL_LINEAR */
#define GL_NEAREST_MIPMAP_NEAREST         0x2700
#define GL_LINEAR_MIPMAP_NEAREST          0x2701
#define GL_NEAREST_MIPMAP_LINEAR          0x2702
#define GL_LINEAR_MIPMAP_LINEAR           0x2703

  /* TextureParameterName */
#define GL_TEXTURE_MAG_FILTER             0x2800
#define GL_TEXTURE_MIN_FILTER             0x2801
#define GL_TEXTURE_WRAP_S                 0x2802
#define GL_TEXTURE_WRAP_T                 0x2803
  /*      GL_TEXTURE_BORDER_COLOR */
  /*      GL_TEXTURE_PRIORITY */

  /* TextureTarget */
  /*      GL_TEXTURE_1D */
  /*      GL_TEXTURE_2D */
#define GL_PROXY_TEXTURE_1D               0x8063
#define GL_PROXY_TEXTURE_2D               0x8064

  /* TextureWrapMode */
#define GL_CLAMP                          0x2900
#define GL_REPEAT                         0x2901

  /* PixelInternalFormat */
#define GL_R3_G3_B2                       0x2A10
#define GL_ALPHA4                         0x803B
#define GL_ALPHA8                         0x803C
#define GL_ALPHA12                        0x803D
#define GL_ALPHA16                        0x803E
#define GL_LUMINANCE4                     0x803F
#define GL_LUMINANCE8                     0x8040
#define GL_LUMINANCE12                    0x8041
#define GL_LUMINANCE16                    0x8042
#define GL_LUMINANCE4_ALPHA4              0x8043
#define GL_LUMINANCE6_ALPHA2              0x8044
#define GL_LUMINANCE8_ALPHA8              0x8045
#define GL_LUMINANCE12_ALPHA4             0x8046
#define GL_LUMINANCE12_ALPHA12            0x8047
#define GL_LUMINANCE16_ALPHA16            0x8048
#define GL_INTENSITY                      0x8049
#define GL_INTENSITY4                     0x804A
#define GL_INTENSITY8                     0x804B
#define GL_INTENSITY12                    0x804C
#define GL_INTENSITY16                    0x804D
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

  /* InterleavedArrayFormat */
#define GL_V2F                            0x2A20
#define GL_V3F                            0x2A21
#define GL_C4UB_V2F                       0x2A22
#define GL_C4UB_V3F                       0x2A23
#define GL_C3F_V3F                        0x2A24
#define GL_N3F_V3F                        0x2A25
#define GL_C4F_N3F_V3F                    0x2A26
#define GL_T2F_V3F                        0x2A27
#define GL_T4F_V4F                        0x2A28
#define GL_T2F_C4UB_V3F                   0x2A29
#define GL_T2F_C3F_V3F                    0x2A2A
#define GL_T2F_N3F_V3F                    0x2A2B
#define GL_T2F_C4F_N3F_V3F                0x2A2C
#define GL_T4F_C4F_N3F_V4F                0x2A2D

  /* VertexPointerType */
  /*      GL_SHORT */
  /*      GL_INT */
  /*      GL_FLOAT */
  /*      GL_DOUBLE */

  /* ClipPlaneName */
#define GL_CLIP_PLANE0                    0x3000
#define GL_CLIP_PLANE1                    0x3001
#define GL_CLIP_PLANE2                    0x3002
#define GL_CLIP_PLANE3                    0x3003
#define GL_CLIP_PLANE4                    0x3004
#define GL_CLIP_PLANE5                    0x3005

  /* LightName */
#define GL_LIGHT0                         0x4000
#define GL_LIGHT1                         0x4001
#define GL_LIGHT2                         0x4002
#define GL_LIGHT3                         0x4003
#define GL_LIGHT4                         0x4004
#define GL_LIGHT5                         0x4005
#define GL_LIGHT6                         0x4006
#define GL_LIGHT7                         0x4007

  /* EXT_abgr */
#define GL_ABGR_EXT                       0x8000

  /* EXT_blend_subtract */
#define GL_FUNC_SUBTRACT_EXT              0x800A
#define GL_FUNC_REVERSE_SUBTRACT_EXT      0x800B

  /* EXT_packed_pixels */
#define GL_UNSIGNED_BYTE_3_3_2_EXT        0x8032
#define GL_UNSIGNED_SHORT_4_4_4_4_EXT     0x8033
#define GL_UNSIGNED_SHORT_5_5_5_1_EXT     0x8034
#define GL_UNSIGNED_INT_8_8_8_8_EXT       0x8035
#define GL_UNSIGNED_INT_10_10_10_2_EXT    0x8036

  /* OpenGL12 */
#define GL_PACK_SKIP_IMAGES               0x806B
#define GL_PACK_IMAGE_HEIGHT              0x806C
#define GL_UNPACK_SKIP_IMAGES             0x806D
#define GL_UNPACK_IMAGE_HEIGHT            0x806E
#define GL_TEXTURE_3D                     0x806F
#define GL_PROXY_TEXTURE_3D               0x8070
#define GL_TEXTURE_DEPTH                  0x8071
#define GL_TEXTURE_WRAP_R                 0x8072
#define GL_MAX_3D_TEXTURE_SIZE            0x8073
#define GL_BGR                            0x80E0
#define GL_BGRA                           0x80E1
#define GL_UNSIGNED_BYTE_3_3_2            0x8032
#define GL_UNSIGNED_BYTE_2_3_3_REV        0x8362
#define GL_UNSIGNED_SHORT_5_6_5           0x8363
#define GL_UNSIGNED_SHORT_5_6_5_REV       0x8364
#define GL_UNSIGNED_SHORT_4_4_4_4         0x8033
#define GL_UNSIGNED_SHORT_4_4_4_4_REV     0x8365
#define GL_UNSIGNED_SHORT_5_5_5_1         0x8034
#define GL_UNSIGNED_SHORT_1_5_5_5_REV     0x8366
#define GL_UNSIGNED_INT_8_8_8_8           0x8035
#define GL_UNSIGNED_INT_8_8_8_8_REV       0x8367
#define GL_UNSIGNED_INT_10_10_10_2        0x8036
#define GL_UNSIGNED_INT_2_10_10_10_REV    0x8368
#define GL_RESCALE_NORMAL                 0x803A
#define GL_LIGHT_MODEL_COLOR_CONTROL      0x81F8
#define GL_SINGLE_COLOR                   0x81F9
#define GL_SEPARATE_SPECULAR_COLOR        0x81FA
#define GL_CLAMP_TO_EDGE                  0x812F
#define GL_TEXTURE_MIN_LOD                0x813A
#define GL_TEXTURE_MAX_LOD                0x813B
#define GL_TEXTURE_BASE_LEVEL             0x813C
#define GL_TEXTURE_MAX_LEVEL              0x813D
#define GL_MAX_ELEMENTS_VERTICES          0x80E8
#define GL_MAX_ELEMENTS_INDICES           0x80E9
#define GL_ALIASED_POINT_SIZE_RANGE       0x846D
#define GL_ALIASED_LINE_WIDTH_RANGE       0x846E

  /* OpenGL13 */
#define GL_ACTIVE_TEXTURE                 0x84E0
#define GL_CLIENT_ACTIVE_TEXTURE          0x84E1
#define GL_MAX_TEXTURE_UNITS              0x84E2
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
#define GL_NORMAL_MAP                     0x8511
#define GL_REFLECTION_MAP                 0x8512
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
#define GL_COMBINE                        0x8570
#define GL_COMBINE_RGB                    0x8571
#define GL_COMBINE_ALPHA                  0x8572
#define GL_RGB_SCALE                      0x8573
#define GL_ADD_SIGNED                     0x8574
#define GL_INTERPOLATE                    0x8575
#define GL_CONSTANT                       0x8576
#define GL_PRIMARY_COLOR                  0x8577
#define GL_PREVIOUS                       0x8578
#define GL_SOURCE0_RGB                    0x8580
#define GL_SOURCE1_RGB                    0x8581
#define GL_SOURCE2_RGB                    0x8582
#define GL_SOURCE0_ALPHA                  0x8588
#define GL_SOURCE1_ALPHA                  0x8589
#define GL_SOURCE2_ALPHA                  0x858A
#define GL_OPERAND0_RGB                   0x8590
#define GL_OPERAND1_RGB                   0x8591
#define GL_OPERAND2_RGB                   0x8592
#define GL_OPERAND0_ALPHA                 0x8598
#define GL_OPERAND1_ALPHA
#define GL_OPERAND2_ALPHA
#define GL_SUBTRACT
#define GL_TRANSPOSE_MODELVIEW_MATRIX
#define GL_TRANSPOSE_PROJECTION_MATRIX
#define GL_TRANSPOSE_TEXTURE_MATRIX
#define GL_TRANSPOSE_COLOR_MATRIX
#define GL_COMPRESSED_ALPHA
#define GL_COMPRESSED_LUMINANCE
#define GL_COMPRESSED_LUMINANCE_ALPHA
#define GL_COMPRESSED_INTENSITY
#define GL_COMPRESSED_RGB
#define GL_COMPRESSED_RGBA
#define GL_TEXTURE_COMPRESSION_HINT
#define GL_TEXTURE_COMPRESSED_IMAGE_SIZE
#define GL_TEXTURE_COMPRESSED
#define GL_NUM_COMPRESSED_TEXTURE_FORMATS
#define GL_COMPRESSED_TEXTURE_FORMATS
#define GL_DOT3_RGB
#define GL_DOT3_RGBA
#define GL_CLAMP_TO_BORDER
#define GL_MULTISAMPLE
#define GL_SAMPLE_ALPHA_TO_COVERAGE
#define GL_SAMPLE_ALPHA_TO_ONE
#define GL_SAMPLE_COVERAGE
#define GL_SAMPLE_BUFFERS
#define GL_SAMPLES
#define GL_SAMPLE_COVERAGE_VALUE
#define GL_SAMPLE_COVERAGE_INVERT
#define GL_MULTISAMPLE_BIT

  /* EXT_vertex_array */
#define GL_VERTEX_ARRAY_EXT
#define GL_NORMAL_ARRAY_EXT
#define GL_COLOR_ARRAY_EXT
#define GL_INDEX_ARRAY_EXT
#define GL_TEXTURE_COORD_ARRAY_EXT
#define GL_EDGE_FLAG_ARRAY_EXT
#define GL_VERTEX_ARRAY_SIZE_EXT
#define GL_VERTEX_ARRAY_TYPE_EXT
#define GL_VERTEX_ARRAY_STRIDE_EXT
#define GL_VERTEX_ARRAY_COUNT_EXT
#define GL_NORMAL_ARRAY_TYPE_EXT
#define GL_NORMAL_ARRAY_STRIDE_EXT
#define GL_NORMAL_ARRAY_COUNT_EXT
#define GL_COLOR_ARRAY_SIZE_EXT
#define GL_COLOR_ARRAY_TYPE_EXT
#define GL_COLOR_ARRAY_STRIDE_EXT
#define GL_COLOR_ARRAY_COUNT_EXT
#define GL_INDEX_ARRAY_TYPE_EXT
#define GL_INDEX_ARRAY_STRIDE_EXT
#define GL_INDEX_ARRAY_COUNT_EXT
#define GL_TEXTURE_COORD_ARRAY_SIZE_EXT
#define GL_TEXTURE_COORD_ARRAY_TYPE_EXT
#define GL_TEXTURE_COORD_ARRAY_STRIDE_EXT
#define GL_TEXTURE_COORD_ARRAY_COUNT_EXT
#define GL_EDGE_FLAG_ARRAY_STRIDE_EXT
#define GL_EDGE_FLAG_ARRAY_COUNT_EXT
#define GL_VERTEX_ARRAY_POINTER_EXT
#define GL_NORMAL_ARRAY_POINTER_EXT
#define GL_COLOR_ARRAY_POINTER_EXT
#define GL_INDEX_ARRAY_POINTER_EXT
#define GL_TEXTURE_COORD_ARRAY_POINTER_EXT
#define GL_EDGE_FLAG_ARRAY_POINTER_EXT

  /* SGIS_texture_lod */
#define GL_TEXTURE_MIN_LOD_SGIS
#define GL_TEXTURE_MAX_LOD_SGIS
#define GL_TEXTURE_BASE_LEVEL_SGIS
#define GL_TEXTURE_MAX_LEVEL_SGIS

  /* EXT_shared_texture_palette */
#define GL_SHARED_TEXTURE_PALETTE_EXT

  /* EXT_rescale_normal */
#define GL_RESCALE_NORMAL_EXT

  /* SGIX_shadow */
#define GL_TEXTURE_COMPARE_SGIX
#define GL_TEXTURE_COMPARE_OPERATOR_SGIX
#define GL_TEXTURE_LEQUAL_R_SGIX
#define GL_TEXTURE_GEQUAL_R_SGIX

  /* SGIX_depth_texture */
#define GL_DEPTH_COMPONENT16_SGIX
#define GL_DEPTH_COMPONENT24_SGIX
#define GL_DEPTH_COMPONENT32_SGIX

  /* SGIS_generate_mipmap */
#define GL_GENERATE_MIPMAP_SGIS
#define GL_GENERATE_MIPMAP_HINT_SGIS

  /* OpenGL14 */
#define GL_POINT_SIZE_MIN
#define GL_POINT_SIZE_MAX
#define GL_POINT_FADE_THRESHOLD_SIZE
#define GL_POINT_DISTANCE_ATTENUATION
#define GL_FOG_COORDINATE_SOURCE
#define GL_FOG_COORDINATE
#define GL_FRAGMENT_DEPTH
#define GL_CURRENT_FOG_COORDINATE
#define GL_FOG_COORDINATE_ARRAY_TYPE
#define GL_FOG_COORDINATE_ARRAY_STRIDE
#define GL_FOG_COORDINATE_ARRAY_POINTER
#define GL_FOG_COORDINATE_ARRAY
#define GL_COLOR_SUM
#define GL_CURRENT_SECONDARY_COLOR
#define GL_SECONDARY_COLOR_ARRAY_SIZE
#define GL_SECONDARY_COLOR_ARRAY_TYPE
#define GL_SECONDARY_COLOR_ARRAY_STRIDE
#define GL_SECONDARY_COLOR_ARRAY_POINTER
#define GL_SECONDARY_COLOR_ARRAY
#define GL_INCR_WRAP
#define GL_DECR_WRAP
#define GL_MAX_TEXTURE_LOD_BIAS
#define GL_TEXTURE_FILTER_CONTROL
#define GL_TEXTURE_LOD_BIAS
#define GL_GENERATE_MIPMAP
#define GL_GENERATE_MIPMAP_HINT
#define GL_BLEND_DST_RGB
#define GL_BLEND_SRC_RGB
#define GL_BLEND_DST_ALPHA
#define GL_BLEND_SRC_ALPHA
#define GL_MIRRORED_REPEAT
#define GL_DEPTH_COMPONENT16
#define GL_DEPTH_COMPONENT24
#define GL_DEPTH_COMPONENT32
#define GL_TEXTURE_DEPTH_SIZE
#define GL_DEPTH_TEXTURE_MODE
#define GL_TEXTURE_COMPARE_MODE
#define GL_TEXTURE_COMPARE_FUNC
#define GL_COMPARE_R_TO_TEXTURE

  /*************************************************************/

  void glAccum (GLenum op, GLfloat value);
  void glAlphaFunc (GLenum func, GLclampf ref);
  GLboolean glAreTexturesResident (GLsizei n, GLuint *textures, GLboolean *residences);
  void glArrayElement (GLint i);
  void glBegin (GLenum mode);
  void glBindTexture (GLenum target, GLuint texture);
  void glBitmap (GLsizei width, GLsizei height, GLfloat xorig, GLfloat yorig, GLfloat xmove, GLfloat ymove, GLubyte *bitmap);
  void glBlendFunc (GLenum sfactor, GLenum dfactor);

  void glCallList (GLuint);
  void glCallLists (GLsizei n, GLenum type, GLuint *lists);
  void glClear (GLbitfield mask);
  void glClearAccum (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
  void glClearColor (GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
  void glClearDepth (GLclampd depth);
  void glClearIndex (GLfloat c);
  void glClearStencil (GLint s);
  void glClipPlane (GLenum plane, GLdouble *equation);
  void glColor3d (GLdouble red, GLdouble green, GLdouble blue);
  void glColor3dv (GLdouble v[3]);
  void glColor3i (GLint red, GLint green, GLint blue);
  void glColor3iv (GLint v[3]);
  void glColor4d (GLdouble red, GLdouble green, GLdouble blue, GLdouble alpha);
  void glColor4dv (GLdouble v[4]);
  void glColor4i (GLint red, GLint green, GLint blue, GLint alpha);
  void glColor4iv (GLint v[4]);
  void glColorMask (GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
  void glColorMaterial (GLenum face, GLenum mode);
  void glColorPointer (GLint size, GLenum type, GLsizei stride, GLdouble *pointer);
  void glCopyPixels (GLint x, GLint y, GLsizei width, GLsizei height, GLenum type);
  void glCopyTexImage1D (GLenum target, GLint level, GLenum internalFormat, GLint x, GLint y, GLsizei width, GLint border);
  void glCopyTexImage2D (GLenum target, GLint level, GLenum internalFormat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border);
  void glCopyTexSubImage1D (GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width);
  void glCopyTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
  void glCullFace (GLenum mode);
  void glDeleteLists (GLuint list, GLsizei range);
  void glDeleteTextures (GLsizei n, GLuint *textures);
  void glDepthFunc (GLenum func);
  void glDepthMask (GLboolean flag);
  void glDepthRange (GLclampd zNear, GLclampd zFar);
  void glDisable (GLenum cap);
  void glDisableClientState (GLenum array);
  void glDrawArrays (GLenum mode, GLint first, GLsizei count);
  void glDrawBuffer (GLenum mode);
  void glDrawElements (GLenum mode, GLsizei count, GLenum type, GLuint *indices);
  void glDrawPixels (GLsizei width, GLsizei height, GLenum format, GLenum type, GLuint *pixels);
  void glEdgeFlag (GLboolean flag);
  void glEdgeFlagPointer (GLsizei stride, GLuint *pointer);
  void glEdgeFlagv (GLboolean *flag);
  void glEnable (GLenum cap);
  void glEnableClientState (GLenum array);
  void glEnd (void);
  void glEndList (void);
  void glEvalCoord1d (GLdouble u);
  void glEvalCoord1dv (GLdouble *u);
  void glEvalCoord1f (GLfloat u);
  void glEvalCoord1fv (GLfloat *u);
  void glEvalCoord2d (GLdouble u, GLdouble v);
  void glEvalCoord2dv (GLdouble *u);
  void glEvalCoord2f (GLfloat u, GLfloat v);
  void glEvalCoord2fv (GLfloat *u);
  void glEvalMesh1 (GLenum mode, GLint i1, GLint i2);
  void glEvalMesh2 (GLenum mode, GLint i1, GLint i2, GLint j1, GLint j2);
  void glEvalPoint1 (GLint i);
  void glEvalPoint2 (GLint i, GLint j);
  void glFeedbackBuffer (GLsizei size, GLenum type, GLfloat *buffer);
  void glFinish (void);
  void glFlush (void);
  void glFogf (GLenum pname, GLfloat param);
  void glFogfv (GLenum pname, GLfloat *params);
  void glFogi (GLenum pname, GLint param);
  void glFogiv (GLenum pname, GLint *params);
  void glFrontFace (GLenum mode);
  void glFrustum (GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar);
  GLuint glGenLists (GLsizei range);
  void glGenTextures (GLsizei n, GLuint *textures);
  void glGetBooleanv (GLenum pname, GLboolean *params);
  void glGetClipPlane (GLenum plane, GLdouble *equation);
  void glGetDoublev (GLenum pname, GLdouble *params);
  GLenum glGetError (void);
  void glGetFloatv (GLenum pname, GLfloat *params);
  void glGetIntegerv (GLenum pname, GLint *params);
  void glGetLightfv (GLenum light, GLenum pname, GLfloat *params);
  void glGetLightiv (GLenum light, GLenum pname, GLint *params);
  void glGetMapdv (GLenum target, GLenum query, GLdouble *v);
  void glGetMapfv (GLenum target, GLenum query, GLfloat *v);
  void glGetMapiv (GLenum target, GLenum query, GLint *v);
  void glGetMaterialfv (GLenum face, GLenum pname, GLfloat *params);
  void glGetMaterialiv (GLenum face, GLenum pname, GLint *params);
  void glGetPixelMapfv (GLenum map, GLfloat *values);
  void glGetPixelMapuiv (GLenum map, GLuint *values);
  void glGetPixelMapusv (GLenum map, GLushort *values);
  //void glGetPointerv (GLenum pname, GLuint **params);
  void glGetPolygonStipple (GLubyte *mask);
  const char* glGetString(GLenum name);
  void glGetTexEnvfv (GLenum target, GLenum pname, GLfloat *params);
  void glGetTexEnviv (GLenum target, GLenum pname, GLint *params);
  void glGetTexGendv (GLenum coord, GLenum pname, GLdouble *params);
  void glGetTexGenfv (GLenum coord, GLenum pname, GLfloat *params);
  void glGetTexGeniv (GLenum coord, GLenum pname, GLint *params);
  void glGetTexImage (GLenum target, GLint level, GLenum format, GLenum type, GLuint *pixels);
  void glGetTexLevelParameterfv (GLenum target, GLint level, GLenum pname, GLfloat *params);
  void glGetTexLevelParameteriv (GLenum target, GLint level, GLenum pname, GLint *params);
  void glGetTexParameterfv (GLenum target, GLenum pname, GLfloat *params);
  void glGetTexParameteriv (GLenum target, GLenum pname, GLint *params);
  void glHint (GLenum target, GLenum mode);
  void glIndexMask (GLuint mask);
  void glIndexPointer (GLenum type, GLsizei stride, GLuint *pointer);
  void glIndexd (GLdouble c);
  void glIndexdv (GLdouble *c);
  void glIndexf (GLfloat c);
  void glIndexfv (GLfloat *c);
  void glIndexi (GLint c);
  void glIndexiv (GLint *c);
  void glIndexs (GLshort c);
  void glIndexsv (GLshort *c);
  void glIndexub (GLubyte c);
  void glIndexubv (GLubyte *c);
  void glInitNames (void);
  void glInterleavedArrays (GLenum format, GLsizei stride, GLuint *pointer);
  GLboolean glIsEnabled (GLenum cap);
  GLboolean glIsList (GLuint list);
  GLboolean glIsTexture (GLuint texture);
  void glLightModelf (GLenum pname, GLfloat param);
  void glLightModelfv (GLenum pname, GLfloat *params);
  void glLightModeli (GLenum pname, GLint param);
  void glLightModeliv (GLenum pname, GLint *params);
  void glLightf (GLenum light, GLenum pname, GLfloat param);
  void glLightfv (GLenum light, GLenum pname, GLfloat *params);
  void glLighti (GLenum light, GLenum pname, GLint param);
  void glLightiv (GLenum light, GLenum pname, GLint *params);
  void glLineStipple (GLint factor, GLushort pattern);
  void glLineWidth (GLfloat width);
  void glListBase (GLuint base);
  void glLoadIdentity (void);
  void glLoadMatrixd (GLdouble *m);
  void glLoadMatrixf (GLfloat *m);
  void glLoadName (GLuint name);
  void glLogicOp (GLenum opcode);
  void glMap1d (GLenum target, GLdouble u1, GLdouble u2, GLint stride, GLint order, GLdouble *points);
  void glMap1f (GLenum target, GLfloat u1, GLfloat u2, GLint stride, GLint order, GLfloat *points);
  void glMap2d (GLenum target, GLdouble u1, GLdouble u2, GLint ustride, GLint uorder, GLdouble v1, GLdouble v2, GLint vstride, GLint vorder, GLdouble *points);
  void glMap2f (GLenum target, GLfloat u1, GLfloat u2, GLint ustride, GLint uorder, GLfloat v1, GLfloat v2, GLint vstride, GLint vorder, GLfloat *points);
  void glMapGrid1d (GLint un, GLdouble u1, GLdouble u2);
  void glMapGrid1f (GLint un, GLfloat u1, GLfloat u2);
  void glMapGrid2d (GLint un, GLdouble u1, GLdouble u2, GLint vn, GLdouble v1, GLdouble v2);
  void glMapGrid2f (GLint un, GLfloat u1, GLfloat u2, GLint vn, GLfloat v1, GLfloat v2);
  void glMaterialf (GLenum face, GLenum pname, GLfloat param);
  void glMaterialfv (GLenum face, GLenum pname, GLfloat *params);
  void glMateriali (GLenum face, GLenum pname, GLint param);
  void glMaterialiv (GLenum face, GLenum pname, GLint *params);
  void glMatrixMode (GLenum mode);
  void glMultMatrixd (GLdouble *m);
  void glMultMatrixf (GLfloat *m);
  void glNewList (GLuint list, GLenum mode);
  void glNormal3b (GLbyte nx, GLbyte ny, GLbyte nz);
  void glNormal3bv (GLbyte *v);
  void glNormal3d (GLdouble nx, GLdouble ny, GLdouble nz);
  void glNormal3dv (GLdouble *v);
  void glNormal3f (GLfloat nx, GLfloat ny, GLfloat nz);
  void glNormal3fv (GLfloat *v);
  void glNormal3i (GLint nx, GLint ny, GLint nz);
  void glNormal3iv (GLint *v);
  void glNormal3s (GLshort nx, GLshort ny, GLshort nz);
  void glNormal3sv (GLshort *v);
  void glNormalPointer (GLenum type, GLsizei stride, GLuint *pointer);
  void glOrtho (GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar);
  void glPassThrough (GLfloat token);
  void glPixelMapfv (GLenum map, GLsizei mapsize, GLfloat *values);
  void glPixelMapuiv (GLenum map, GLsizei mapsize, GLuint *values);
  void glPixelMapusv (GLenum map, GLsizei mapsize, GLushort *values);
  void glPixelStoref (GLenum pname, GLfloat param);
  void glPixelStorei (GLenum pname, GLint param);
  void glPixelTransferf (GLenum pname, GLfloat param);
  void glPixelTransferi (GLenum pname, GLint param);
  void glPixelZoom (GLfloat xfactor, GLfloat yfactor);
  void glPointSize (GLfloat size);
  void glPolygonMode (GLenum face, GLenum mode);
  void glPolygonOffset (GLfloat factor, GLfloat units);
  void glPolygonStipple (GLubyte *mask);
  void glPopAttrib (void);
  void glPopClientAttrib (void);
  void glPopMatrix (void);
  void glPopName (void);
  void glPrioritizeTextures (GLsizei n, GLuint *textures, GLclampf *priorities);
  void glPushAttrib (GLbitfield mask);
  void glPushClientAttrib (GLbitfield mask);
  void glPushMatrix (void);
  void glPushName (GLuint name);
  void glRasterPos2d (GLdouble x, GLdouble y);
  void glRasterPos2dv (GLdouble *v);
  void glRasterPos2f (GLfloat x, GLfloat y);
  void glRasterPos2fv (GLfloat *v);
  void glRasterPos2i (GLint x, GLint y);
  void glRasterPos2iv (GLint *v);
  void glRasterPos2s (GLshort x, GLshort y);
  void glRasterPos2sv (GLshort *v);
  void glRasterPos3d (GLdouble x, GLdouble y, GLdouble z);
  void glRasterPos3dv (GLdouble *v);
  void glRasterPos3f (GLfloat x, GLfloat y, GLfloat z);
  void glRasterPos3fv (GLfloat *v);
  void glRasterPos3i (GLint x, GLint y, GLint z);
  void glRasterPos3iv (GLint *v);
  void glRasterPos3s (GLshort x, GLshort y, GLshort z);
  void glRasterPos3sv (GLshort *v);
  void glRasterPos4d (GLdouble x, GLdouble y, GLdouble z, GLdouble w);
  void glRasterPos4dv (GLdouble *v);
  void glRasterPos4f (GLfloat x, GLfloat y, GLfloat z, GLfloat w);
  void glRasterPos4fv (GLfloat *v);
  void glRasterPos4i (GLint x, GLint y, GLint z, GLint w);
  void glRasterPos4iv (GLint *v);
  void glRasterPos4s (GLshort x, GLshort y, GLshort z, GLshort w);
  void glRasterPos4sv (GLshort *v);
  void glReadBuffer (GLenum mode);
  void glReadPixels (GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLuint *pixels);
  void glRectd (GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2);
  void glRectdv (GLdouble *v1, GLdouble *v2);
  void glRectf (GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2);
  void glRectfv (GLfloat *v1, GLfloat *v2);
  void glRecti (GLint x1, GLint y1, GLint x2, GLint y2);
  void glRectiv (GLint *v1, GLint *v2);
  void glRects (GLshort x1, GLshort y1, GLshort x2, GLshort y2);
  void glRectsv (GLshort *v1, GLshort *v2);
  GLint glRenderMode (GLenum mode);
  void glRotated (GLdouble angle, GLdouble x, GLdouble y, GLdouble z);
  void glRotatef (GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
  void glScaled (GLdouble x, GLdouble y, GLdouble z);
  void glScalef (GLfloat x, GLfloat y, GLfloat z);
  void glScissor (GLint x, GLint y, GLsizei width, GLsizei height);
  void glSelectBuffer (GLsizei size, GLuint *buffer);
  void glShadeModel (GLenum mode);
  void glStencilFunc (GLenum func, GLint ref, GLuint mask);
  void glStencilMask (GLuint mask);
  void glStencilOp (GLenum fail, GLenum zfail, GLenum zpass);
  void glTexCoord1d (GLdouble s);
  void glTexCoord1dv (GLdouble *v);
  void glTexCoord1f (GLfloat s);
  void glTexCoord1fv (GLfloat *v);
  void glTexCoord1i (GLint s);
  void glTexCoord1iv (GLint *v);
  void glTexCoord1s (GLshort s);
  void glTexCoord1sv (GLshort *v);
  void glTexCoord2d (GLdouble s, GLdouble t);
  void glTexCoord2dv (GLdouble *v);
  void glTexCoord2f (GLfloat s, GLfloat t);
  void glTexCoord2fv (GLfloat *v);
  void glTexCoord2i (GLint s, GLint t);
  void glTexCoord2iv (GLint *v);
  void glTexCoord2s (GLshort s, GLshort t);
  void glTexCoord2sv (GLshort *v);
  void glTexCoord3d (GLdouble s, GLdouble t, GLdouble r);
  void glTexCoord3dv (GLdouble *v);
  void glTexCoord3f (GLfloat s, GLfloat t, GLfloat r);
  void glTexCoord3fv (GLfloat *v);
  void glTexCoord3i (GLint s, GLint t, GLint r);
  void glTexCoord3iv (GLint *v);
  void glTexCoord3s (GLshort s, GLshort t, GLshort r);
  void glTexCoord3sv (GLshort *v);
  void glTexCoord4d (GLdouble s, GLdouble t, GLdouble r, GLdouble q);
  void glTexCoord4dv (GLdouble *v);
  void glTexCoord4f (GLfloat s, GLfloat t, GLfloat r, GLfloat q);
  void glTexCoord4fv (GLfloat *v);
  void glTexCoord4i (GLint s, GLint t, GLint r, GLint q);
  void glTexCoord4iv (GLint *v);
  void glTexCoord4s (GLshort s, GLshort t, GLshort r, GLshort q);
  void glTexCoord4sv (GLshort *v);
  void glTexCoordPointer (GLint size, GLenum type, GLsizei stride, GLuint *pointer);
  void glTexEnvf (GLenum target, GLenum pname, GLfloat param);
  void glTexEnvfv (GLenum target, GLenum pname, GLfloat *params);
  void glTexEnvi (GLenum target, GLenum pname, GLint param);
  void glTexEnviv (GLenum target, GLenum pname, GLint *params);
  void glTexGend (GLenum coord, GLenum pname, GLdouble param);
  void glTexGendv (GLenum coord, GLenum pname, GLdouble *params);
  void glTexGenf (GLenum coord, GLenum pname, GLfloat param);
  void glTexGenfv (GLenum coord, GLenum pname, GLfloat *params);
  void glTexGeni (GLenum coord, GLenum pname, GLint param);
  void glTexGeniv (GLenum coord, GLenum pname, GLint *params);
  void glTexImage1D (GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, GLuint *pixels);
  void glTexImage2D (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, GLuint *pixels);
  void glTexParameterf (GLenum target, GLenum pname, GLfloat param);
  void glTexParameterfv (GLenum target, GLenum pname, GLfloat *params);
  void glTexParameteri (GLenum target, GLenum pname, GLint param);
  void glTexParameteriv (GLenum target, GLenum pname, GLint *params);
  void glTexSubImage1D (GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, GLuint *pixels);
  void glTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, GLuint *pixels);
  void glTranslated (GLdouble x, GLdouble y, GLdouble z);
  void glTranslatef (GLfloat x, GLfloat y, GLfloat z);
  void glVertex2d (GLdouble x, GLdouble y);
  void glVertex2dv (GLdouble v[2]);
  void glVertex2i (GLint x, GLint y);
  void glVertex2iv (GLint v[2]);
  void glVertex3d (GLdouble x, GLdouble y, GLdouble z);
  void glVertex3dv (GLdouble v[3]);
  void glVertex3i (GLint x, GLint y, GLint z);
  void glVertex3iv (GLint v[3]);
  void glVertex4d (GLdouble x, GLdouble y, GLdouble z, GLdouble w);
  void glVertex4dv (GLdouble v[4]);
  void glVertex4i (GLint x, GLint y, GLint z, GLint w);
  void glVertex4iv (GLint v[4]);
  void glVertexPointer (GLint size, GLenum type, GLsizei stride, GLuint *pointer);
  void glViewport (GLint x, GLint y, GLsizei width, GLsizei height);

  //void glVertex3d @ glVertex(double x, double y, double z=0.0);

  void unogl::glInitNamesArray();
  void unogl::glGenNames(GLsizei n,GLuint* names);
  void unogl::glDeleteNames(GLsizei n,GLuint* names);
}
