#version 120
attribute vec4 vertexPosition_modelspace;
varying vec2 UV;
 
void main(void) {
  gl_Position = vec4(vertexPosition_modelspace.xy, 0, 1);
  UV = vertexPosition_modelspace.zw;
}