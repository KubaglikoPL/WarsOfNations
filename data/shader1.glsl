#ifdef GLES
  #ifdef VERTEX_SHADER
    precision highp float;
    precision highp int;
    precision lowp sampler2D;
    precision lowp samplerCube;
  #endif
  #ifdef FRAGMENT_SHADER
    precision mediump float;
    precision mediump int;
    precision lowp sampler2D;
    precision lowp samplerCube;
  #endif
#endif
#ifdef VERTEX_SHADER
  attribute vec2 aPos;
  attribute vec2 aUV;
  attribute vec4 aColor;

#ifdef USE_VP_MATRIX
  uniform mat4 VP_Matrix;
#endif

  varying vec2 oUV;
  varying vec4 oColor;

  void main() {
    #ifdef USE_VP_MATRIX
      gl_Position = vec4(aPos, 0.0, 1.0) * VP_Matrix;
    #else
      gl_Position = vec4(aPos, 0.0, 1.0);
    #endif
    oUV = aUV;
    oColor = aColor;
  }
#endif
#ifdef FRAGMENT_SHADER
  varying vec2 oUV;
  varying vec4 oColor;

  uniform sampler2D texture0;

  void main() {
    gl_FragColor = texture2D(texture0, oUV) * oColor;
  }
#endif
