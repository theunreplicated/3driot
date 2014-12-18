#version 330 core

// Input vertex data, different for all executions of this shader.
//layout(location = 0)
in vec3 vertexPosition_modelspace;
in vec2 vertexUV;

// Output data ; will be interpolated for each fragment.
out vec2 UV;

uniform mat4 MVP;//=Model view Projection//opengl-tutorial.org

void main(){

	//vec4 pos;
  // pos.xyz = vertexPosition_modelspace;
   // pos.w = 1.0;
		//vec4(vertexPosition_modelspace.xyz,1.0);
	//gl_Position=pos*MVP;
	gl_Position =  MVP * vec4(vertexPosition_modelspace,1);
	
	// UV of the vertex. No special space for this one.
	UV = vertexUV;
}
