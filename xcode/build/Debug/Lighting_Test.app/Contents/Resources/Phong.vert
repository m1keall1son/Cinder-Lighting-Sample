#version 330

in vec4 ciPosition;
in vec3 ciNormal;

uniform mat4 ciModelView;
uniform mat3 ciNormalMatrix;
uniform mat4 ciModelViewProjection;

out vec3 vNormal;
out vec4 vPosition;


void main(){
    
    
    vPosition = ciModelView * ciPosition;
    vNormal = normalize(ciNormalMatrix * ciNormal);
    
    gl_Position = ciModelViewProjection * ciPosition;
    
}