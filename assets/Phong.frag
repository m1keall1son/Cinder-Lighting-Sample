
#version 330

in vec4 vPosition;
in vec3 vNormal;

layout ( location = 0 ) out vec4 FragColor;

uniform vec3 lightPosition;

void main(){
    
    vec3    ambient = vec3( .1,.1,.1 );
    
    vec3    normal = vNormal;
    
    vec3	lightVector = normalize( lightPosition - vPosition.xyz );
    //light attenuation
    float   dist = length(lightVector);
    
    float   attenuation = 1. / ( dist +  dist * dist );
    // To camera vector
    vec3	cameraVector = normalize( -vPosition.xyz );
    // Surface reflection vector
    vec3	reflection = normalize( -reflect( lightVector, normal) );
    
    // Diffuse factor
    vec3	diffuse = vec3( max( dot( normal, lightVector ), 0.0 ) );
    // Specular factor
    
    const float shininess_factor = 128.;
    
    vec3    specular =	vec3(  pow( max( dot( reflection, cameraVector ), 0.0 ), shininess_factor ) );
    
    FragColor = vec4( attenuation*( specular + diffuse ) + ambient, 1. );
    
}