#version 400
#pragma include "rand.glslinc.frag"

uniform mat4 modelViewMatrix; // oF Default
uniform mat4 modelViewProjectionMatrix; // oF Default
uniform mat4 normalMatrix; // Pass from C++
in vec4 position; // oF Default
in vec4 normal; // oF Default
in vec4 color; // oF Default
in vec2 texcoord; // oF Default

uniform float farClip;
uniform float nearClip;

uniform sampler2DRect tex;
uniform float vol;
uniform vec2 size;
uniform float boxSize;
uniform float trans;

out vec4 vPosition;
out float vDepth;
out vec3 vNormal;
out vec4 vColor;

void main(){
    vec4 p = position;

    vec2 texSize = textureSize(tex);

    float instanceX = mod(gl_InstanceID, size.x);
    float instanceY = floor(gl_InstanceID / size.x);

    vec2 st = vec2(instanceX, size.y - instanceY) / size * texSize;

    vec3 c = texture(tex, st).rgb;
    float grey = (c.r + c.g + c.b) / 3.;
    p.z += 2.5;

    float v = clamp(vol, 0.1, 1.) + 0.3;
    p.x *= v;
    p.y *= v;

    if (grey < 0.02) {
        grey = 0.02;
        c = vec3(0.05);
    }

    float height = grey * 7.5 + v * 2.;
    p.z *= height;
    p.z += abs(p.z) / 2.;

    p.x += (boxSize * 1.1) * (instanceX - size.x * 0.5);
    p.y += (boxSize * 1.1) * (instanceY - size.y * 0.5);

    vec3 rv = getRandomVector(st) * rand(gl_InstanceID) * 500. * trans;
    p.xyz += rv;

    gl_Position = modelViewProjectionMatrix * p;

    vec4 viewPos = modelViewMatrix * p;
    vDepth = - viewPos.z / (farClip - nearClip);
    vNormal = (normalMatrix * normal).xyz;
    vColor = vec4(c, 1.0);
    vPosition = viewPos;
}
