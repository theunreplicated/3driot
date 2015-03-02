#version 120
varying vec2 UV;
uniform sampler2D myTextureSampler;
uniform vec4 color;
 //@TODO:check ob typ für glsl-compiler o.k. und das mit color vllt. anders machen
void main(void) {
  gl_FragColor = vec4(1, 1, 1, texture2D(myTextureSampler, UV).a) * color;
}