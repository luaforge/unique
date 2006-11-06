/*
 *  OpenGL Extensions Config
 */
/*
 *  Registering extensions:
 *
 *    GLEXT_FUNC(pseudo function name, real extension function type, real extension function name);
 *
 *    type of function is a PFNGL{type}PROC
 *    name of function is a gl{name}
 */

// Common extensions synonyms
// Multitexturing
GLEXT_FUNC(glActiveTexture,           GLACTIVETEXTURE,           glActiveTexture           );
GLEXT_FUNC(glClientActiveTexture,     GLCLIENTACTIVETEXTURE,     glClientActiveTexture     );
// Texture Coords 1D
GLEXT_FUNC(glMultiTexCoord1d,         GLMULTITEXCOORD1D,         glMultiTexCoord1d         );
GLEXT_FUNC(glMultiTexCoord1dv,        GLMULTITEXCOORD1DV,        glMultiTexCoord1dv        );
GLEXT_FUNC(glMultiTexCoord1f,         GLMULTITEXCOORD1F,         glMultiTexCoord1f         );
GLEXT_FUNC(glMultiTexCoord1fv,        GLMULTITEXCOORD1FV,        glMultiTexCoord1fv        );
GLEXT_FUNC(glMultiTexCoord1i,         GLMULTITEXCOORD1I,         glMultiTexCoord1i         );
GLEXT_FUNC(glMultiTexCoord1iv,        GLMULTITEXCOORD1IV,        glMultiTexCoord1iv        );
GLEXT_FUNC(glMultiTexCoord1s,         GLMULTITEXCOORD1S,         glMultiTexCoord1s         );
GLEXT_FUNC(glMultiTexCoord1sv,        GLMULTITEXCOORD1SV,        glMultiTexCoord1sv        );
// Texture Coords 2D
GLEXT_FUNC(glMultiTexCoord2d,         GLMULTITEXCOORD2D,         glMultiTexCoord2d         );
GLEXT_FUNC(glMultiTexCoord2dv,        GLMULTITEXCOORD2DV,        glMultiTexCoord2dv        );
GLEXT_FUNC(glMultiTexCoord2f,         GLMULTITEXCOORD2F,         glMultiTexCoord2f         );
GLEXT_FUNC(glMultiTexCoord2fv,        GLMULTITEXCOORD2FV,        glMultiTexCoord2fv        );
GLEXT_FUNC(glMultiTexCoord2i,         GLMULTITEXCOORD2I,         glMultiTexCoord2i         );
GLEXT_FUNC(glMultiTexCoord2iv,        GLMULTITEXCOORD2IV,        glMultiTexCoord2iv        );
GLEXT_FUNC(glMultiTexCoord2s,         GLMULTITEXCOORD2S,         glMultiTexCoord2s         );
GLEXT_FUNC(glMultiTexCoord2sv,        GLMULTITEXCOORD2SV,        glMultiTexCoord2sv        );
// Texture Coords 3D
GLEXT_FUNC(glMultiTexCoord3d,         GLMULTITEXCOORD3D,         glMultiTexCoord3d         );
GLEXT_FUNC(glMultiTexCoord3dv,        GLMULTITEXCOORD3DV,        glMultiTexCoord3dv        );
GLEXT_FUNC(glMultiTexCoord3f,         GLMULTITEXCOORD3F,         glMultiTexCoord3f         );
GLEXT_FUNC(glMultiTexCoord3fv,        GLMULTITEXCOORD3FV,        glMultiTexCoord3fv        );
GLEXT_FUNC(glMultiTexCoord3i,         GLMULTITEXCOORD3I,         glMultiTexCoord3i         );
GLEXT_FUNC(glMultiTexCoord3iv,        GLMULTITEXCOORD3IV,        glMultiTexCoord3iv        );
GLEXT_FUNC(glMultiTexCoord3s,         GLMULTITEXCOORD3S,         glMultiTexCoord3s         );
GLEXT_FUNC(glMultiTexCoord3sv,        GLMULTITEXCOORD3SV,        glMultiTexCoord3sv        );
// Texture Coords 4D
GLEXT_FUNC(glMultiTexCoord4d,         GLMULTITEXCOORD4D,         glMultiTexCoord4d         );
GLEXT_FUNC(glMultiTexCoord4dv,        GLMULTITEXCOORD4DV,        glMultiTexCoord4dv        );
GLEXT_FUNC(glMultiTexCoord4f,         GLMULTITEXCOORD4F,         glMultiTexCoord4f         );
GLEXT_FUNC(glMultiTexCoord4fv,        GLMULTITEXCOORD4FV,        glMultiTexCoord4fv        );
GLEXT_FUNC(glMultiTexCoord4i,         GLMULTITEXCOORD4I,         glMultiTexCoord4i         );
GLEXT_FUNC(glMultiTexCoord4iv,        GLMULTITEXCOORD4IV,        glMultiTexCoord4iv        );
GLEXT_FUNC(glMultiTexCoord4s,         GLMULTITEXCOORD4S,         glMultiTexCoord4s         );
GLEXT_FUNC(glMultiTexCoord4sv,        GLMULTITEXCOORD4SV,        glMultiTexCoord4sv        );
// Matrixes
GLEXT_FUNC(glLoadTransposeMatrixf,    GLLOADTRANSPOSEMATRIXF,    glLoadTransposeMatrixf    );
GLEXT_FUNC(glLoadTransposeMatrixd,    GLLOADTRANSPOSEMATRIXD,    glLoadTransposeMatrixd    );
GLEXT_FUNC(glMultTransposeMatrixf,    GLMULTTRANSPOSEMATRIXF,    glMultTransposeMatrixf    );
GLEXT_FUNC(glMultTransposeMatrixd,    GLMULTTRANSPOSEMATRIXD,    glMultTransposeMatrixd    );
GLEXT_FUNC(glSampleCoverage,          GLSAMPLECOVERAGE,          glSampleCoverage          );
// Compress texture image extensions
GLEXT_FUNC(glCompressedTexImage1D,    GLCOMPRESSEDTEXIMAGE1D,    glCompressedTexImage1D    );
GLEXT_FUNC(glCompressedTexImage2D,    GLCOMPRESSEDTEXIMAGE2D,    glCompressedTexImage2D    );
GLEXT_FUNC(glCompressedTexImage3D,    GLCOMPRESSEDTEXIMAGE3D,    glCompressedTexImage3D    );
GLEXT_FUNC(glCompressedTexSubImage1D, GLCOMPRESSEDTEXSUBIMAGE1D, glCompressedTexSubImage1D );
GLEXT_FUNC(glCompressedTexSubImage2D, GLCOMPRESSEDTEXSUBIMAGE2D, glCompressedTexSubImage2D );
GLEXT_FUNC(glCompressedTexSubImage3D, GLCOMPRESSEDTEXSUBIMAGE3D, glCompressedTexSubImage3D );
GLEXT_FUNC(glGetCompressedTexImage,   GLGETCOMPRESSEDTEXIMAGE,   glGetCompressedTexImage   );


/*
GLEXT_FUNC(,,);
GLEXT_FUNC(,,);
GLEXT_FUNC(,,);
GLEXT_FUNC(,,);
GLEXT_FUNC(,,);
*/
//GLEXT_FUNC(,,);

// EXT vendor extensions
// MipMap
GLEXT_FUNC(glGenerateMipmap,          GLGENERATEMIPMAPEXT,          glGenerateMipmapEXT          );
// Renderbuffer
GLEXT_FUNC(glGenRenderbuffers,        GLGENRENDERBUFFERSEXT,        glGenRenderbuffersEXT        );
GLEXT_FUNC(glDeleteRenderbuffers,     GLDELETERENDERBUFFERSEXT,     glDeleteRenderbuffersEXT     );
GLEXT_FUNC(glRenderbufferStorage,     GLRENDERBUFFERSTORAGEEXT,     glRenderbufferStorageEXT     );
GLEXT_FUNC(glBindRenderbuffer,        GLBINDRENDERBUFFEREXT,        glBindRenderbufferEXT        );
// Framebuffer
GLEXT_FUNC(glGenFramebuffers,         GLGENFRAMEBUFFERSEXT,         glGenFramebuffersEXT         );
GLEXT_FUNC(glDeleteFramebuffers,      GLDELETEFRAMEBUFFERSEXT,      glDeleteFramebuffersEXT      );
GLEXT_FUNC(glBindFramebuffer,         GLBINDFRAMEBUFFEREXT,         glBindFramebufferEXT         );
GLEXT_FUNC(glFramebufferTexture1D,    GLFRAMEBUFFERTEXTURE1DEXT,    glFramebufferTexture1DEXT    );
GLEXT_FUNC(glFramebufferTexture2D,    GLFRAMEBUFFERTEXTURE2DEXT,    glFramebufferTexture2DEXT    );
GLEXT_FUNC(glFramebufferTexture3D,    GLFRAMEBUFFERTEXTURE3DEXT,    glFramebufferTexture3DEXT    );
GLEXT_FUNC(glFramebufferRenderbuffer, GLFRAMEBUFFERRENDERBUFFEREXT, glFramebufferRenderbufferEXT );
GLEXT_FUNC(glCheckFramebufferStatus,  GLCHECKFRAMEBUFFERSTATUSEXT,  glCheckFramebufferStatusEXT  );

