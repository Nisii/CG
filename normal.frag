#version 130
varying vec4 texC;
varying vec4 norC;

uniform sampler2D texture;

void main(){
    gl_FragColor = norC;
}
