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

  uniform mat4 VP_Matrix;

  varying vec2 oUV;
  varying vec4 oColor;

  void main() {
    gl_Position = vec2(aPos, 0.0, 1.0) * VP_Matrix;
    oUV = aUV;
    oColor = aColor;
  }
#endif
#ifdef FRAGMENT_SHADER
  varying vec2 oUV;
  varying vec4 oColor;

  uniform sampler2D texture0;

  void main() {
    gl_FragColor
    oUV = aUV;
    oColor = aColor;
  }
#endif
