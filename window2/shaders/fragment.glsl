#version 120
varying vec2 UV;
uniform sampler2D myTextureSampler;//out vec3 weggelassen
void main()
{

//gl_FragColor.rgb = texture2D( myTextureSampler, UV ).rgb;//vllt.ist das nur so korrekt??
gl_FragColor = texture2D( myTextureSampler, UV );
}
