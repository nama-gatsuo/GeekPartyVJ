#version 400
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

out vec4 vPosition;
out float vDepth;
out vec3 vNormal;
out vec4 vColor;

void main(){
    vec4 p = position;

    vec2 size = textureSize(tex);

    float instanceX = mod(gl_InstanceID, size.x);
    float instanceY = floor(gl_InstanceID / size.x);

    vec3 c = texture(tex, vec2(instanceX, instanceY)).rgb;
    float grey = (c.r + c.g + c.b) / 3.;

    if (grey < 0.02) {
        grey = 0.02;
        c = vec3(0.5);
    }
    vec2 offset = vec2(1.0);
    float height = grey * 30.0;
    p.y *= height;
    p.y += abs(p.y) / 2.;

    p.x += (5.0 + offset.x) * (instanceX - size.x * 0.5);
    p.z += (5.0 + offset.y) * (instanceY - size.y * 0.5);

    gl_Position = modelViewProjectionMatrix * p;

    vec4 viewPos = modelViewMatrix * p;
    vDepth = - viewPos.z / (farClip - nearClip);
    vNormal = (normalMatrix * normal).xyz;
    vColor = vec4(c, 1.0);
    vPosition = viewPos;
}
