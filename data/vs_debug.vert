#version 150

in  vec3 in_Position;
in  mat4 in_ModelMatrix;

uniform mat4 view;
uniform mat4 proj;
uniform mat4 model;

void main(void) {


	mat4 mv = view * in_ModelMatrix;
    gl_Position = proj * mv * vec4( in_Position, 1.0 );

}

