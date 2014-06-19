#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition_modelspace;
uniform mat4 MVP;//=Model view Projection//opengl-tutorial.org

void main(){

	vec4 pos;
   pos.xyz = vertexPosition_modelspace;
    pos.w = 1.0;
		//vec4(vertexPosition_modelspace.xyz,1.0);
	gl_Position=pos*MVP;
}
