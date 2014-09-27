
#version 330

in vec4 vPosition;
in vec3 vNormal;

layout ( location = 0 ) out vec4 FragColor;

uniform vec3 lightPosition;

void main(){
    
    vec3    ambient = vec3( .1,.1,.1 );
    
    vec3    normal = normalize( vNormal );
    
    vec3	lightVector = normalize( lightPosition - vPosition.xyz );

    vec3	diffuse = vec3( max( dot( normal, lightVector ), 0.0 ) );
    
    FragColor = vec4( diffuse + ambient, 1. );
    
}