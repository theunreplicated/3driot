#version 330 core
in vec2 UV;
// Output data
out vec3 color;
uniform sampler2D myTextureSampler;
void main()
{
//https://code.google.com/p/opengl-tutorial-org/source/browse/tutorial05_textured_cube/TextureFragmentShader.fragmentshader
	// Output color = red 
	//color = vec3(1,0,0);
color = texture2D( myTextureSampler, UV ).rgb;
}
