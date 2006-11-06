/*
 *  OpenGL Extensions Config
 */
/*
 *  Registering extensions:
 *
 *    GLEXT_FUNC(pseudo function name, real extension function type, real extension function name);
 *
 *    type of function is a PFN{type}PROC
 *    name of function is a {name}
 */
#ifdef GL_VERSION_1_2
/* >> Extensions `GL_VERSION_1_2` >> */
GLEXT_FUNC(glBlendColor,                GLBLENDCOLOR,                glBlendColor                );
GLEXT_FUNC(glBlendEquation,             GLBLENDEQUATION,             glBlendEquation             );
GLEXT_FUNC(glDrawRangeElements,         GLDRAWRANGEELEMENTS,         glDrawRangeElements         );
GLEXT_FUNC(glColorTable,                GLCOLORTABLE,                glColorTable                );
GLEXT_FUNC(glColorTableParameterfv,     GLCOLORTABLEPARAMETERFV,     glColorTableParameterfv     );
GLEXT_FUNC(glColorTableParameteriv,     GLCOLORTABLEPARAMETERIV,     glColorTableParameteriv     );
GLEXT_FUNC(glCopyColorTable,            GLCOPYCOLORTABLE,            glCopyColorTable            );
GLEXT_FUNC(glGetColorTable,             GLGETCOLORTABLE,             glGetColorTable             );
GLEXT_FUNC(glGetColorTableParameterfv,  GLGETCOLORTABLEPARAMETERFV,  glGetColorTableParameterfv  );
GLEXT_FUNC(glGetColorTableParameteriv,  GLGETCOLORTABLEPARAMETERIV,  glGetColorTableParameteriv  );
GLEXT_FUNC(glColorSubTable,             GLCOLORSUBTABLE,             glColorSubTable             );
GLEXT_FUNC(glCopyColorSubTable,         GLCOPYCOLORSUBTABLE,         glCopyColorSubTable         );
GLEXT_FUNC(glConvolutionFilter1D,       GLCONVOLUTIONFILTER1D,       glConvolutionFilter1D       );
GLEXT_FUNC(glConvolutionFilter2D,       GLCONVOLUTIONFILTER2D,       glConvolutionFilter2D       );
GLEXT_FUNC(glConvolutionParameterf,     GLCONVOLUTIONPARAMETERF,     glConvolutionParameterf     );
GLEXT_FUNC(glConvolutionParameterfv,    GLCONVOLUTIONPARAMETERFV,    glConvolutionParameterfv    );
GLEXT_FUNC(glConvolutionParameteri,     GLCONVOLUTIONPARAMETERI,     glConvolutionParameteri     );
GLEXT_FUNC(glConvolutionParameteriv,    GLCONVOLUTIONPARAMETERIV,    glConvolutionParameteriv    );
GLEXT_FUNC(glCopyConvolutionFilter1D,   GLCOPYCONVOLUTIONFILTER1D,   glCopyConvolutionFilter1D   );
GLEXT_FUNC(glCopyConvolutionFilter2D,   GLCOPYCONVOLUTIONFILTER2D,   glCopyConvolutionFilter2D   );
GLEXT_FUNC(glGetConvolutionFilter,      GLGETCONVOLUTIONFILTER,      glGetConvolutionFilter      );
GLEXT_FUNC(glGetConvolutionParameterfv, GLGETCONVOLUTIONPARAMETERFV, glGetConvolutionParameterfv );
GLEXT_FUNC(glGetConvolutionParameteriv, GLGETCONVOLUTIONPARAMETERIV, glGetConvolutionParameteriv );
GLEXT_FUNC(glGetSeparableFilter,        GLGETSEPARABLEFILTER,        glGetSeparableFilter        );
GLEXT_FUNC(glSeparableFilter2D,         GLSEPARABLEFILTER2D,         glSeparableFilter2D         );
GLEXT_FUNC(glGetHistogram,              GLGETHISTOGRAM,              glGetHistogram              );
GLEXT_FUNC(glGetHistogramParameterfv,   GLGETHISTOGRAMPARAMETERFV,   glGetHistogramParameterfv   );
GLEXT_FUNC(glGetHistogramParameteriv,   GLGETHISTOGRAMPARAMETERIV,   glGetHistogramParameteriv   );
GLEXT_FUNC(glGetMinmax,                 GLGETMINMAX,                 glGetMinmax                 );
GLEXT_FUNC(glGetMinmaxParameterfv,      GLGETMINMAXPARAMETERFV,      glGetMinmaxParameterfv      );
GLEXT_FUNC(glGetMinmaxParameteriv,      GLGETMINMAXPARAMETERIV,      glGetMinmaxParameteriv      );
GLEXT_FUNC(glHistogram,                 GLHISTOGRAM,                 glHistogram                 );
GLEXT_FUNC(glMinmax,                    GLMINMAX,                    glMinmax                    );
GLEXT_FUNC(glResetHistogram,            GLRESETHISTOGRAM,            glResetHistogram            );
GLEXT_FUNC(glResetMinmax,               GLRESETMINMAX,               glResetMinmax               );
GLEXT_FUNC(glTexImage3D,                GLTEXIMAGE3D,                glTexImage3D                );
GLEXT_FUNC(glTexSubImage3D,             GLTEXSUBIMAGE3D,             glTexSubImage3D             );
GLEXT_FUNC(glCopyTexSubImage3D,         GLCOPYTEXSUBIMAGE3D,         glCopyTexSubImage3D         );
/* << Extensions `GL_VERSION_1_2` << */
#endif
#ifdef GL_VERSION_1_3
/* >> Extensions `GL_VERSION_1_3` >> */
GLEXT_FUNC(glActiveTexture,           GLACTIVETEXTURE,           glActiveTexture           );
GLEXT_FUNC(glClientActiveTexture,     GLCLIENTACTIVETEXTURE,     glClientActiveTexture     );
GLEXT_FUNC(glMultiTexCoord1d,         GLMULTITEXCOORD1D,         glMultiTexCoord1d         );
GLEXT_FUNC(glMultiTexCoord1dv,        GLMULTITEXCOORD1DV,        glMultiTexCoord1dv        );
GLEXT_FUNC(glMultiTexCoord1f,         GLMULTITEXCOORD1F,         glMultiTexCoord1f         );
GLEXT_FUNC(glMultiTexCoord1fv,        GLMULTITEXCOORD1FV,        glMultiTexCoord1fv        );
GLEXT_FUNC(glMultiTexCoord1i,         GLMULTITEXCOORD1I,         glMultiTexCoord1i         );
GLEXT_FUNC(glMultiTexCoord1iv,        GLMULTITEXCOORD1IV,        glMultiTexCoord1iv        );
GLEXT_FUNC(glMultiTexCoord1s,         GLMULTITEXCOORD1S,         glMultiTexCoord1s         );
GLEXT_FUNC(glMultiTexCoord1sv,        GLMULTITEXCOORD1SV,        glMultiTexCoord1sv        );
GLEXT_FUNC(glMultiTexCoord2d,         GLMULTITEXCOORD2D,         glMultiTexCoord2d         );
GLEXT_FUNC(glMultiTexCoord2dv,        GLMULTITEXCOORD2DV,        glMultiTexCoord2dv        );
GLEXT_FUNC(glMultiTexCoord2f,         GLMULTITEXCOORD2F,         glMultiTexCoord2f         );
GLEXT_FUNC(glMultiTexCoord2fv,        GLMULTITEXCOORD2FV,        glMultiTexCoord2fv        );
GLEXT_FUNC(glMultiTexCoord2i,         GLMULTITEXCOORD2I,         glMultiTexCoord2i         );
GLEXT_FUNC(glMultiTexCoord2iv,        GLMULTITEXCOORD2IV,        glMultiTexCoord2iv        );
GLEXT_FUNC(glMultiTexCoord2s,         GLMULTITEXCOORD2S,         glMultiTexCoord2s         );
GLEXT_FUNC(glMultiTexCoord2sv,        GLMULTITEXCOORD2SV,        glMultiTexCoord2sv        );
GLEXT_FUNC(glMultiTexCoord3d,         GLMULTITEXCOORD3D,         glMultiTexCoord3d         );
GLEXT_FUNC(glMultiTexCoord3dv,        GLMULTITEXCOORD3DV,        glMultiTexCoord3dv        );
GLEXT_FUNC(glMultiTexCoord3f,         GLMULTITEXCOORD3F,         glMultiTexCoord3f         );
GLEXT_FUNC(glMultiTexCoord3fv,        GLMULTITEXCOORD3FV,        glMultiTexCoord3fv        );
GLEXT_FUNC(glMultiTexCoord3i,         GLMULTITEXCOORD3I,         glMultiTexCoord3i         );
GLEXT_FUNC(glMultiTexCoord3iv,        GLMULTITEXCOORD3IV,        glMultiTexCoord3iv        );
GLEXT_FUNC(glMultiTexCoord3s,         GLMULTITEXCOORD3S,         glMultiTexCoord3s         );
GLEXT_FUNC(glMultiTexCoord3sv,        GLMULTITEXCOORD3SV,        glMultiTexCoord3sv        );
GLEXT_FUNC(glMultiTexCoord4d,         GLMULTITEXCOORD4D,         glMultiTexCoord4d         );
GLEXT_FUNC(glMultiTexCoord4dv,        GLMULTITEXCOORD4DV,        glMultiTexCoord4dv        );
GLEXT_FUNC(glMultiTexCoord4f,         GLMULTITEXCOORD4F,         glMultiTexCoord4f         );
GLEXT_FUNC(glMultiTexCoord4fv,        GLMULTITEXCOORD4FV,        glMultiTexCoord4fv        );
GLEXT_FUNC(glMultiTexCoord4i,         GLMULTITEXCOORD4I,         glMultiTexCoord4i         );
GLEXT_FUNC(glMultiTexCoord4iv,        GLMULTITEXCOORD4IV,        glMultiTexCoord4iv        );
GLEXT_FUNC(glMultiTexCoord4s,         GLMULTITEXCOORD4S,         glMultiTexCoord4s         );
GLEXT_FUNC(glMultiTexCoord4sv,        GLMULTITEXCOORD4SV,        glMultiTexCoord4sv        );
GLEXT_FUNC(glLoadTransposeMatrixf,    GLLOADTRANSPOSEMATRIXF,    glLoadTransposeMatrixf    );
GLEXT_FUNC(glLoadTransposeMatrixd,    GLLOADTRANSPOSEMATRIXD,    glLoadTransposeMatrixd    );
GLEXT_FUNC(glMultTransposeMatrixf,    GLMULTTRANSPOSEMATRIXF,    glMultTransposeMatrixf    );
GLEXT_FUNC(glMultTransposeMatrixd,    GLMULTTRANSPOSEMATRIXD,    glMultTransposeMatrixd    );
GLEXT_FUNC(glSampleCoverage,          GLSAMPLECOVERAGE,          glSampleCoverage          );
GLEXT_FUNC(glCompressedTexImage3D,    GLCOMPRESSEDTEXIMAGE3D,    glCompressedTexImage3D    );
GLEXT_FUNC(glCompressedTexImage2D,    GLCOMPRESSEDTEXIMAGE2D,    glCompressedTexImage2D    );
GLEXT_FUNC(glCompressedTexImage1D,    GLCOMPRESSEDTEXIMAGE1D,    glCompressedTexImage1D    );
GLEXT_FUNC(glCompressedTexSubImage3D, GLCOMPRESSEDTEXSUBIMAGE3D, glCompressedTexSubImage3D );
GLEXT_FUNC(glCompressedTexSubImage2D, GLCOMPRESSEDTEXSUBIMAGE2D, glCompressedTexSubImage2D );
GLEXT_FUNC(glCompressedTexSubImage1D, GLCOMPRESSEDTEXSUBIMAGE1D, glCompressedTexSubImage1D );
GLEXT_FUNC(glGetCompressedTexImage,   GLGETCOMPRESSEDTEXIMAGE,   glGetCompressedTexImage   );
/* << Extensions `GL_VERSION_1_3` << */
#endif
#ifdef GL_VERSION_1_4
/* >> Extensions `GL_VERSION_1_4` >> */
GLEXT_FUNC(glBlendFuncSeparate,     GLBLENDFUNCSEPARATE,     glBlendFuncSeparate     );
GLEXT_FUNC(glFogCoordf,             GLFOGCOORDF,             glFogCoordf             );
GLEXT_FUNC(glFogCoordfv,            GLFOGCOORDFV,            glFogCoordfv            );
GLEXT_FUNC(glFogCoordd,             GLFOGCOORDD,             glFogCoordd             );
GLEXT_FUNC(glFogCoorddv,            GLFOGCOORDDV,            glFogCoorddv            );
GLEXT_FUNC(glFogCoordPointer,       GLFOGCOORDPOINTER,       glFogCoordPointer       );
GLEXT_FUNC(glMultiDrawArrays,       GLMULTIDRAWARRAYS,       glMultiDrawArrays       );
GLEXT_FUNC(glMultiDrawElements,     GLMULTIDRAWELEMENTS,     glMultiDrawElements     );
GLEXT_FUNC(glPointParameterf,       GLPOINTPARAMETERF,       glPointParameterf       );
GLEXT_FUNC(glPointParameterfv,      GLPOINTPARAMETERFV,      glPointParameterfv      );
GLEXT_FUNC(glPointParameteri,       GLPOINTPARAMETERI,       glPointParameteri       );
GLEXT_FUNC(glPointParameteriv,      GLPOINTPARAMETERIV,      glPointParameteriv      );
GLEXT_FUNC(glSecondaryColor3b,      GLSECONDARYCOLOR3B,      glSecondaryColor3b      );
GLEXT_FUNC(glSecondaryColor3bv,     GLSECONDARYCOLOR3BV,     glSecondaryColor3bv     );
GLEXT_FUNC(glSecondaryColor3d,      GLSECONDARYCOLOR3D,      glSecondaryColor3d      );
GLEXT_FUNC(glSecondaryColor3dv,     GLSECONDARYCOLOR3DV,     glSecondaryColor3dv     );
GLEXT_FUNC(glSecondaryColor3f,      GLSECONDARYCOLOR3F,      glSecondaryColor3f      );
GLEXT_FUNC(glSecondaryColor3fv,     GLSECONDARYCOLOR3FV,     glSecondaryColor3fv     );
GLEXT_FUNC(glSecondaryColor3i,      GLSECONDARYCOLOR3I,      glSecondaryColor3i      );
GLEXT_FUNC(glSecondaryColor3iv,     GLSECONDARYCOLOR3IV,     glSecondaryColor3iv     );
GLEXT_FUNC(glSecondaryColor3s,      GLSECONDARYCOLOR3S,      glSecondaryColor3s      );
GLEXT_FUNC(glSecondaryColor3sv,     GLSECONDARYCOLOR3SV,     glSecondaryColor3sv     );
GLEXT_FUNC(glSecondaryColor3ub,     GLSECONDARYCOLOR3UB,     glSecondaryColor3ub     );
GLEXT_FUNC(glSecondaryColor3ubv,    GLSECONDARYCOLOR3UBV,    glSecondaryColor3ubv    );
GLEXT_FUNC(glSecondaryColor3ui,     GLSECONDARYCOLOR3UI,     glSecondaryColor3ui     );
GLEXT_FUNC(glSecondaryColor3uiv,    GLSECONDARYCOLOR3UIV,    glSecondaryColor3uiv    );
GLEXT_FUNC(glSecondaryColor3us,     GLSECONDARYCOLOR3US,     glSecondaryColor3us     );
GLEXT_FUNC(glSecondaryColor3usv,    GLSECONDARYCOLOR3USV,    glSecondaryColor3usv    );
GLEXT_FUNC(glSecondaryColorPointer, GLSECONDARYCOLORPOINTER, glSecondaryColorPointer );
GLEXT_FUNC(glWindowPos2d,           GLWINDOWPOS2D,           glWindowPos2d           );
GLEXT_FUNC(glWindowPos2dv,          GLWINDOWPOS2DV,          glWindowPos2dv          );
GLEXT_FUNC(glWindowPos2f,           GLWINDOWPOS2F,           glWindowPos2f           );
GLEXT_FUNC(glWindowPos2fv,          GLWINDOWPOS2FV,          glWindowPos2fv          );
GLEXT_FUNC(glWindowPos2i,           GLWINDOWPOS2I,           glWindowPos2i           );
GLEXT_FUNC(glWindowPos2iv,          GLWINDOWPOS2IV,          glWindowPos2iv          );
GLEXT_FUNC(glWindowPos2s,           GLWINDOWPOS2S,           glWindowPos2s           );
GLEXT_FUNC(glWindowPos2sv,          GLWINDOWPOS2SV,          glWindowPos2sv          );
GLEXT_FUNC(glWindowPos3d,           GLWINDOWPOS3D,           glWindowPos3d           );
GLEXT_FUNC(glWindowPos3dv,          GLWINDOWPOS3DV,          glWindowPos3dv          );
GLEXT_FUNC(glWindowPos3f,           GLWINDOWPOS3F,           glWindowPos3f           );
GLEXT_FUNC(glWindowPos3fv,          GLWINDOWPOS3FV,          glWindowPos3fv          );
GLEXT_FUNC(glWindowPos3i,           GLWINDOWPOS3I,           glWindowPos3i           );
GLEXT_FUNC(glWindowPos3iv,          GLWINDOWPOS3IV,          glWindowPos3iv          );
GLEXT_FUNC(glWindowPos3s,           GLWINDOWPOS3S,           glWindowPos3s           );
GLEXT_FUNC(glWindowPos3sv,          GLWINDOWPOS3SV,          glWindowPos3sv          );
/* << Extensions `GL_VERSION_1_4` << */
#endif
#ifdef GL_VERSION_1_5
/* >> Extensions `GL_VERSION_1_5` >> */
GLEXT_FUNC(glGenQueries,           GLGENQUERIES,           glGenQueries           );
GLEXT_FUNC(glDeleteQueries,        GLDELETEQUERIES,        glDeleteQueries        );
GLEXT_FUNC(glIsQuery,              GLISQUERY,              glIsQuery              );
GLEXT_FUNC(glBeginQuery,           GLBEGINQUERY,           glBeginQuery           );
GLEXT_FUNC(glEndQuery,             GLENDQUERY,             glEndQuery             );
GLEXT_FUNC(glGetQueryiv,           GLGETQUERYIV,           glGetQueryiv           );
GLEXT_FUNC(glGetQueryObjectiv,     GLGETQUERYOBJECTIV,     glGetQueryObjectiv     );
GLEXT_FUNC(glGetQueryObjectuiv,    GLGETQUERYOBJECTUIV,    glGetQueryObjectuiv    );
GLEXT_FUNC(glBindBuffer,           GLBINDBUFFER,           glBindBuffer           );
GLEXT_FUNC(glDeleteBuffers,        GLDELETEBUFFERS,        glDeleteBuffers        );
GLEXT_FUNC(glGenBuffers,           GLGENBUFFERS,           glGenBuffers           );
GLEXT_FUNC(glIsBuffer,             GLISBUFFER,             glIsBuffer             );
GLEXT_FUNC(glBufferData,           GLBUFFERDATA,           glBufferData           );
GLEXT_FUNC(glBufferSubData,        GLBUFFERSUBDATA,        glBufferSubData        );
GLEXT_FUNC(glGetBufferSubData,     GLGETBUFFERSUBDATA,     glGetBufferSubData     );
GLEXT_FUNC(glMapBuffer,            GLMAPBUFFER,            glMapBuffer            );
GLEXT_FUNC(glUnmapBuffer,          GLUNMAPBUFFER,          glUnmapBuffer          );
GLEXT_FUNC(glGetBufferParameteriv, GLGETBUFFERPARAMETERIV, glGetBufferParameteriv );
GLEXT_FUNC(glGetBufferPointerv,    GLGETBUFFERPOINTERV,    glGetBufferPointerv    );
/* << Extensions `GL_VERSION_1_5` << */
#endif
#ifdef GL_VERSION_2_0
/* >> Extensions `GL_VERSION_2_0` >> */
GLEXT_FUNC(glBlendEquationSeparate,    GLBLENDEQUATIONSEPARATE,    glBlendEquationSeparate    );
GLEXT_FUNC(glDrawBuffers,              GLDRAWBUFFERS,              glDrawBuffers              );
GLEXT_FUNC(glStencilOpSeparate,        GLSTENCILOPSEPARATE,        glStencilOpSeparate        );
GLEXT_FUNC(glStencilFuncSeparate,      GLSTENCILFUNCSEPARATE,      glStencilFuncSeparate      );
GLEXT_FUNC(glStencilMaskSeparate,      GLSTENCILMASKSEPARATE,      glStencilMaskSeparate      );
GLEXT_FUNC(glAttachShader,             GLATTACHSHADER,             glAttachShader             );
GLEXT_FUNC(glBindAttribLocation,       GLBINDATTRIBLOCATION,       glBindAttribLocation       );
GLEXT_FUNC(glCompileShader,            GLCOMPILESHADER,            glCompileShader            );
GLEXT_FUNC(glCreateProgram,            GLCREATEPROGRAM,            glCreateProgram            );
GLEXT_FUNC(glCreateShader,             GLCREATESHADER,             glCreateShader             );
GLEXT_FUNC(glDeleteProgram,            GLDELETEPROGRAM,            glDeleteProgram            );
GLEXT_FUNC(glDeleteShader,             GLDELETESHADER,             glDeleteShader             );
GLEXT_FUNC(glDetachShader,             GLDETACHSHADER,             glDetachShader             );
GLEXT_FUNC(glDisableVertexAttribArray, GLDISABLEVERTEXATTRIBARRAY, glDisableVertexAttribArray );
GLEXT_FUNC(glEnableVertexAttribArray,  GLENABLEVERTEXATTRIBARRAY,  glEnableVertexAttribArray  );
GLEXT_FUNC(glGetActiveAttrib,          GLGETACTIVEATTRIB,          glGetActiveAttrib          );
GLEXT_FUNC(glGetActiveUniform,         GLGETACTIVEUNIFORM,         glGetActiveUniform         );
GLEXT_FUNC(glGetAttachedShaders,       GLGETATTACHEDSHADERS,       glGetAttachedShaders       );
GLEXT_FUNC(glGetAttribLocation,        GLGETATTRIBLOCATION,        glGetAttribLocation        );
GLEXT_FUNC(glGetProgramiv,             GLGETPROGRAMIV,             glGetProgramiv             );
GLEXT_FUNC(glGetProgramInfoLog,        GLGETPROGRAMINFOLOG,        glGetProgramInfoLog        );
GLEXT_FUNC(glGetShaderiv,              GLGETSHADERIV,              glGetShaderiv              );
GLEXT_FUNC(glGetShaderInfoLog,         GLGETSHADERINFOLOG,         glGetShaderInfoLog         );
GLEXT_FUNC(glGetShaderSource,          GLGETSHADERSOURCE,          glGetShaderSource          );
GLEXT_FUNC(glGetUniformLocation,       GLGETUNIFORMLOCATION,       glGetUniformLocation       );
GLEXT_FUNC(glGetUniformfv,             GLGETUNIFORMFV,             glGetUniformfv             );
GLEXT_FUNC(glGetUniformiv,             GLGETUNIFORMIV,             glGetUniformiv             );
GLEXT_FUNC(glGetVertexAttribdv,        GLGETVERTEXATTRIBDV,        glGetVertexAttribdv        );
GLEXT_FUNC(glGetVertexAttribfv,        GLGETVERTEXATTRIBFV,        glGetVertexAttribfv        );
GLEXT_FUNC(glGetVertexAttribiv,        GLGETVERTEXATTRIBIV,        glGetVertexAttribiv        );
GLEXT_FUNC(glGetVertexAttribPointerv,  GLGETVERTEXATTRIBPOINTERV,  glGetVertexAttribPointerv  );
GLEXT_FUNC(glIsProgram,                GLISPROGRAM,                glIsProgram                );
GLEXT_FUNC(glIsShader,                 GLISSHADER,                 glIsShader                 );
GLEXT_FUNC(glLinkProgram,              GLLINKPROGRAM,              glLinkProgram              );
GLEXT_FUNC(glShaderSource,             GLSHADERSOURCE,             glShaderSource             );
GLEXT_FUNC(glUseProgram,               GLUSEPROGRAM,               glUseProgram               );
GLEXT_FUNC(glUniform1f,                GLUNIFORM1F,                glUniform1f                );
GLEXT_FUNC(glUniform2f,                GLUNIFORM2F,                glUniform2f                );
GLEXT_FUNC(glUniform3f,                GLUNIFORM3F,                glUniform3f                );
GLEXT_FUNC(glUniform4f,                GLUNIFORM4F,                glUniform4f                );
GLEXT_FUNC(glUniform1i,                GLUNIFORM1I,                glUniform1i                );
GLEXT_FUNC(glUniform2i,                GLUNIFORM2I,                glUniform2i                );
GLEXT_FUNC(glUniform3i,                GLUNIFORM3I,                glUniform3i                );
GLEXT_FUNC(glUniform4i,                GLUNIFORM4I,                glUniform4i                );
GLEXT_FUNC(glUniform1fv,               GLUNIFORM1FV,               glUniform1fv               );
GLEXT_FUNC(glUniform2fv,               GLUNIFORM2FV,               glUniform2fv               );
GLEXT_FUNC(glUniform3fv,               GLUNIFORM3FV,               glUniform3fv               );
GLEXT_FUNC(glUniform4fv,               GLUNIFORM4FV,               glUniform4fv               );
GLEXT_FUNC(glUniform1iv,               GLUNIFORM1IV,               glUniform1iv               );
GLEXT_FUNC(glUniform2iv,               GLUNIFORM2IV,               glUniform2iv               );
GLEXT_FUNC(glUniform3iv,               GLUNIFORM3IV,               glUniform3iv               );
GLEXT_FUNC(glUniform4iv,               GLUNIFORM4IV,               glUniform4iv               );
GLEXT_FUNC(glUniformMatrix2fv,         GLUNIFORMMATRIX2FV,         glUniformMatrix2fv         );
GLEXT_FUNC(glUniformMatrix3fv,         GLUNIFORMMATRIX3FV,         glUniformMatrix3fv         );
GLEXT_FUNC(glUniformMatrix4fv,         GLUNIFORMMATRIX4FV,         glUniformMatrix4fv         );
GLEXT_FUNC(glValidateProgram,          GLVALIDATEPROGRAM,          glValidateProgram          );
GLEXT_FUNC(glVertexAttrib1d,           GLVERTEXATTRIB1D,           glVertexAttrib1d           );
GLEXT_FUNC(glVertexAttrib1dv,          GLVERTEXATTRIB1DV,          glVertexAttrib1dv          );
GLEXT_FUNC(glVertexAttrib1f,           GLVERTEXATTRIB1F,           glVertexAttrib1f           );
GLEXT_FUNC(glVertexAttrib1fv,          GLVERTEXATTRIB1FV,          glVertexAttrib1fv          );
GLEXT_FUNC(glVertexAttrib1s,           GLVERTEXATTRIB1S,           glVertexAttrib1s           );
GLEXT_FUNC(glVertexAttrib1sv,          GLVERTEXATTRIB1SV,          glVertexAttrib1sv          );
GLEXT_FUNC(glVertexAttrib2d,           GLVERTEXATTRIB2D,           glVertexAttrib2d           );
GLEXT_FUNC(glVertexAttrib2dv,          GLVERTEXATTRIB2DV,          glVertexAttrib2dv          );
GLEXT_FUNC(glVertexAttrib2f,           GLVERTEXATTRIB2F,           glVertexAttrib2f           );
GLEXT_FUNC(glVertexAttrib2fv,          GLVERTEXATTRIB2FV,          glVertexAttrib2fv          );
GLEXT_FUNC(glVertexAttrib2s,           GLVERTEXATTRIB2S,           glVertexAttrib2s           );
GLEXT_FUNC(glVertexAttrib2sv,          GLVERTEXATTRIB2SV,          glVertexAttrib2sv          );
GLEXT_FUNC(glVertexAttrib3d,           GLVERTEXATTRIB3D,           glVertexAttrib3d           );
GLEXT_FUNC(glVertexAttrib3dv,          GLVERTEXATTRIB3DV,          glVertexAttrib3dv          );
GLEXT_FUNC(glVertexAttrib3f,           GLVERTEXATTRIB3F,           glVertexAttrib3f           );
GLEXT_FUNC(glVertexAttrib3fv,          GLVERTEXATTRIB3FV,          glVertexAttrib3fv          );
GLEXT_FUNC(glVertexAttrib3s,           GLVERTEXATTRIB3S,           glVertexAttrib3s           );
GLEXT_FUNC(glVertexAttrib3sv,          GLVERTEXATTRIB3SV,          glVertexAttrib3sv          );
GLEXT_FUNC(glVertexAttrib4Nbv,         GLVERTEXATTRIB4NBV,         glVertexAttrib4Nbv         );
GLEXT_FUNC(glVertexAttrib4Niv,         GLVERTEXATTRIB4NIV,         glVertexAttrib4Niv         );
GLEXT_FUNC(glVertexAttrib4Nsv,         GLVERTEXATTRIB4NSV,         glVertexAttrib4Nsv         );
GLEXT_FUNC(glVertexAttrib4Nub,         GLVERTEXATTRIB4NUB,         glVertexAttrib4Nub         );
GLEXT_FUNC(glVertexAttrib4Nubv,        GLVERTEXATTRIB4NUBV,        glVertexAttrib4Nubv        );
GLEXT_FUNC(glVertexAttrib4Nuiv,        GLVERTEXATTRIB4NUIV,        glVertexAttrib4Nuiv        );
GLEXT_FUNC(glVertexAttrib4Nusv,        GLVERTEXATTRIB4NUSV,        glVertexAttrib4Nusv        );
GLEXT_FUNC(glVertexAttrib4bv,          GLVERTEXATTRIB4BV,          glVertexAttrib4bv          );
GLEXT_FUNC(glVertexAttrib4d,           GLVERTEXATTRIB4D,           glVertexAttrib4d           );
GLEXT_FUNC(glVertexAttrib4dv,          GLVERTEXATTRIB4DV,          glVertexAttrib4dv          );
GLEXT_FUNC(glVertexAttrib4f,           GLVERTEXATTRIB4F,           glVertexAttrib4f           );
GLEXT_FUNC(glVertexAttrib4fv,          GLVERTEXATTRIB4FV,          glVertexAttrib4fv          );
GLEXT_FUNC(glVertexAttrib4iv,          GLVERTEXATTRIB4IV,          glVertexAttrib4iv          );
GLEXT_FUNC(glVertexAttrib4s,           GLVERTEXATTRIB4S,           glVertexAttrib4s           );
GLEXT_FUNC(glVertexAttrib4sv,          GLVERTEXATTRIB4SV,          glVertexAttrib4sv          );
GLEXT_FUNC(glVertexAttrib4ubv,         GLVERTEXATTRIB4UBV,         glVertexAttrib4ubv         );
GLEXT_FUNC(glVertexAttrib4uiv,         GLVERTEXATTRIB4UIV,         glVertexAttrib4uiv         );
GLEXT_FUNC(glVertexAttrib4usv,         GLVERTEXATTRIB4USV,         glVertexAttrib4usv         );
GLEXT_FUNC(glVertexAttribPointer,      GLVERTEXATTRIBPOINTER,      glVertexAttribPointer      );
/* << Extensions `GL_VERSION_2_0` << */
#endif
#ifdef GL_EXT_coordinate_frame
/* >> Extensions `GL_EXT_coordinate_frame` >> */
GLEXT_FUNC(glTangent3b,       GLTANGENT3BEXT,       glTangent3bEXT       );
GLEXT_FUNC(glTangent3bv,      GLTANGENT3BVEXT,      glTangent3bvEXT      );
GLEXT_FUNC(glTangent3d,       GLTANGENT3DEXT,       glTangent3dEXT       );
GLEXT_FUNC(glTangent3dv,      GLTANGENT3DVEXT,      glTangent3dvEXT      );
GLEXT_FUNC(glTangent3f,       GLTANGENT3FEXT,       glTangent3fEXT       );
GLEXT_FUNC(glTangent3fv,      GLTANGENT3FVEXT,      glTangent3fvEXT      );
GLEXT_FUNC(glTangent3i,       GLTANGENT3IEXT,       glTangent3iEXT       );
GLEXT_FUNC(glTangent3iv,      GLTANGENT3IVEXT,      glTangent3ivEXT      );
GLEXT_FUNC(glTangent3s,       GLTANGENT3SEXT,       glTangent3sEXT       );
GLEXT_FUNC(glTangent3sv,      GLTANGENT3SVEXT,      glTangent3svEXT      );
GLEXT_FUNC(glBinormal3b,      GLBINORMAL3BEXT,      glBinormal3bEXT      );
GLEXT_FUNC(glBinormal3bv,     GLBINORMAL3BVEXT,     glBinormal3bvEXT     );
GLEXT_FUNC(glBinormal3d,      GLBINORMAL3DEXT,      glBinormal3dEXT      );
GLEXT_FUNC(glBinormal3dv,     GLBINORMAL3DVEXT,     glBinormal3dvEXT     );
GLEXT_FUNC(glBinormal3f,      GLBINORMAL3FEXT,      glBinormal3fEXT      );
GLEXT_FUNC(glBinormal3fv,     GLBINORMAL3FVEXT,     glBinormal3fvEXT     );
GLEXT_FUNC(glBinormal3i,      GLBINORMAL3IEXT,      glBinormal3iEXT      );
GLEXT_FUNC(glBinormal3iv,     GLBINORMAL3IVEXT,     glBinormal3ivEXT     );
GLEXT_FUNC(glBinormal3s,      GLBINORMAL3SEXT,      glBinormal3sEXT      );
GLEXT_FUNC(glBinormal3sv,     GLBINORMAL3SVEXT,     glBinormal3svEXT     );
GLEXT_FUNC(glTangentPointer,  GLTANGENTPOINTEREXT,  glTangentPointerEXT  );
GLEXT_FUNC(glBinormalPointer, GLBINORMALPOINTEREXT, glBinormalPointerEXT );
/* << Extensions `GL_EXT_coordinate_frame` << */
#endif
#ifdef GL_EXT_multisample
/* >> Extensions `GL_EXT_multisample` >> */
GLEXT_FUNC(glSampleMask,    GLSAMPLEMASKEXT,    glSampleMaskEXT    );
GLEXT_FUNC(glSamplePattern, GLSAMPLEPATTERNEXT, glSamplePatternEXT );
/* << Extensions `GL_EXT_multisample` << */
#endif
#ifdef GL_EXT_vertex_shader
/* >> Extensions `GL_EXT_vertex_shader` >> */
GLEXT_FUNC(glBeginVertexShader,         GLBEGINVERTEXSHADEREXT,         glBeginVertexShaderEXT         );
GLEXT_FUNC(glEndVertexShader,           GLENDVERTEXSHADEREXT,           glEndVertexShaderEXT           );
GLEXT_FUNC(glBindVertexShader,          GLBINDVERTEXSHADEREXT,          glBindVertexShaderEXT          );
GLEXT_FUNC(glGenVertexShaders,          GLGENVERTEXSHADERSEXT,          glGenVertexShadersEXT          );
GLEXT_FUNC(glDeleteVertexShader,        GLDELETEVERTEXSHADEREXT,        glDeleteVertexShaderEXT        );
GLEXT_FUNC(glShaderOp1,                 GLSHADEROP1EXT,                 glShaderOp1EXT                 );
GLEXT_FUNC(glShaderOp2,                 GLSHADEROP2EXT,                 glShaderOp2EXT                 );
GLEXT_FUNC(glShaderOp3,                 GLSHADEROP3EXT,                 glShaderOp3EXT                 );
GLEXT_FUNC(glSwizzle,                   GLSWIZZLEEXT,                   glSwizzleEXT                   );
GLEXT_FUNC(glWriteMask,                 GLWRITEMASKEXT,                 glWriteMaskEXT                 );
GLEXT_FUNC(glInsertComponent,           GLINSERTCOMPONENTEXT,           glInsertComponentEXT           );
GLEXT_FUNC(glExtractComponent,          GLEXTRACTCOMPONENTEXT,          glExtractComponentEXT          );
GLEXT_FUNC(glGenSymbols,                GLGENSYMBOLSEXT,                glGenSymbolsEXT                );
GLEXT_FUNC(glSetInvariant,              GLSETINVARIANTEXT,              glSetInvariantEXT              );
GLEXT_FUNC(glSetLocalConstant,          GLSETLOCALCONSTANTEXT,          glSetLocalConstantEXT          );
GLEXT_FUNC(glVariantbv,                 GLVARIANTBVEXT,                 glVariantbvEXT                 );
GLEXT_FUNC(glVariantsv,                 GLVARIANTSVEXT,                 glVariantsvEXT                 );
GLEXT_FUNC(glVariantiv,                 GLVARIANTIVEXT,                 glVariantivEXT                 );
GLEXT_FUNC(glVariantfv,                 GLVARIANTFVEXT,                 glVariantfvEXT                 );
GLEXT_FUNC(glVariantdv,                 GLVARIANTDVEXT,                 glVariantdvEXT                 );
GLEXT_FUNC(glVariantubv,                GLVARIANTUBVEXT,                glVariantubvEXT                );
GLEXT_FUNC(glVariantusv,                GLVARIANTUSVEXT,                glVariantusvEXT                );
GLEXT_FUNC(glVariantuiv,                GLVARIANTUIVEXT,                glVariantuivEXT                );
GLEXT_FUNC(glVariantPointer,            GLVARIANTPOINTEREXT,            glVariantPointerEXT            );
GLEXT_FUNC(glEnableVariantClientState,  GLENABLEVARIANTCLIENTSTATEEXT,  glEnableVariantClientStateEXT  );
GLEXT_FUNC(glDisableVariantClientState, GLDISABLEVARIANTCLIENTSTATEEXT, glDisableVariantClientStateEXT );
GLEXT_FUNC(glBindLightParameter,        GLBINDLIGHTPARAMETEREXT,        glBindLightParameterEXT        );
GLEXT_FUNC(glBindMaterialParameter,     GLBINDMATERIALPARAMETEREXT,     glBindMaterialParameterEXT     );
GLEXT_FUNC(glBindTexGenParameter,       GLBINDTEXGENPARAMETEREXT,       glBindTexGenParameterEXT       );
GLEXT_FUNC(glBindTextureUnitParameter,  GLBINDTEXTUREUNITPARAMETEREXT,  glBindTextureUnitParameterEXT  );
GLEXT_FUNC(glBindParameter,             GLBINDPARAMETEREXT,             glBindParameterEXT             );
GLEXT_FUNC(glIsVariantEnabled,          GLISVARIANTENABLEDEXT,          glIsVariantEnabledEXT          );
GLEXT_FUNC(glGetVariantBooleanv,        GLGETVARIANTBOOLEANVEXT,        glGetVariantBooleanvEXT        );
GLEXT_FUNC(glGetVariantIntegerv,        GLGETVARIANTINTEGERVEXT,        glGetVariantIntegervEXT        );
GLEXT_FUNC(glGetVariantFloatv,          GLGETVARIANTFLOATVEXT,          glGetVariantFloatvEXT          );
GLEXT_FUNC(glGetVariantPointerv,        GLGETVARIANTPOINTERVEXT,        glGetVariantPointervEXT        );
GLEXT_FUNC(glGetInvariantBooleanv,      GLGETINVARIANTBOOLEANVEXT,      glGetInvariantBooleanvEXT      );
GLEXT_FUNC(glGetInvariantIntegerv,      GLGETINVARIANTINTEGERVEXT,      glGetInvariantIntegervEXT      );
GLEXT_FUNC(glGetInvariantFloatv,        GLGETINVARIANTFLOATVEXT,        glGetInvariantFloatvEXT        );
GLEXT_FUNC(glGetLocalConstantBooleanv,  GLGETLOCALCONSTANTBOOLEANVEXT,  glGetLocalConstantBooleanvEXT  );
GLEXT_FUNC(glGetLocalConstantIntegerv,  GLGETLOCALCONSTANTINTEGERVEXT,  glGetLocalConstantIntegervEXT  );
GLEXT_FUNC(glGetLocalConstantFloatv,    GLGETLOCALCONSTANTFLOATVEXT,    glGetLocalConstantFloatvEXT    );
/* << Extensions `GL_EXT_vertex_shader` << */
#endif
#ifdef GL_EXT_framebuffer_object
/* >> Extensions `GL_EXT_framebuffer_object` >> */
GLEXT_FUNC(glIsRenderbuffer,                      GLISRENDERBUFFEREXT,                      glIsRenderbufferEXT                      );
GLEXT_FUNC(glBindRenderbuffer,                    GLBINDRENDERBUFFEREXT,                    glBindRenderbufferEXT                    );
GLEXT_FUNC(glDeleteRenderbuffers,                 GLDELETERENDERBUFFERSEXT,                 glDeleteRenderbuffersEXT                 );
GLEXT_FUNC(glGenRenderbuffers,                    GLGENRENDERBUFFERSEXT,                    glGenRenderbuffersEXT                    );
GLEXT_FUNC(glRenderbufferStorage,                 GLRENDERBUFFERSTORAGEEXT,                 glRenderbufferStorageEXT                 );
GLEXT_FUNC(glGetRenderbufferParameteriv,          GLGETRENDERBUFFERPARAMETERIVEXT,          glGetRenderbufferParameterivEXT          );
GLEXT_FUNC(glIsFramebuffer,                       GLISFRAMEBUFFEREXT,                       glIsFramebufferEXT                       );
GLEXT_FUNC(glBindFramebuffer,                     GLBINDFRAMEBUFFEREXT,                     glBindFramebufferEXT                     );
GLEXT_FUNC(glDeleteFramebuffers,                  GLDELETEFRAMEBUFFERSEXT,                  glDeleteFramebuffersEXT                  );
GLEXT_FUNC(glGenFramebuffers,                     GLGENFRAMEBUFFERSEXT,                     glGenFramebuffersEXT                     );
GLEXT_FUNC(glCheckFramebufferStatus,              GLCHECKFRAMEBUFFERSTATUSEXT,              glCheckFramebufferStatusEXT              );
GLEXT_FUNC(glFramebufferTexture1D,                GLFRAMEBUFFERTEXTURE1DEXT,                glFramebufferTexture1DEXT                );
GLEXT_FUNC(glFramebufferTexture2D,                GLFRAMEBUFFERTEXTURE2DEXT,                glFramebufferTexture2DEXT                );
GLEXT_FUNC(glFramebufferTexture3D,                GLFRAMEBUFFERTEXTURE3DEXT,                glFramebufferTexture3DEXT                );
GLEXT_FUNC(glFramebufferRenderbuffer,             GLFRAMEBUFFERRENDERBUFFEREXT,             glFramebufferRenderbufferEXT             );
GLEXT_FUNC(glGetFramebufferAttachmentParameteriv, GLGETFRAMEBUFFERATTACHMENTPARAMETERIVEXT, glGetFramebufferAttachmentParameterivEXT );
GLEXT_FUNC(glGenerateMipmap,                      GLGENERATEMIPMAPEXT,                      glGenerateMipmapEXT                      );
/* << Extensions `GL_EXT_framebuffer_object` << */
#endif

/*
 *  End of OpenGL extensions config
 */
