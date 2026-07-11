#version 460 core
struct Particle
{
    vec2 position;
};

layout(std430, binding = 0) buffer ParticleBuffer
{
    Particle particles[];
};

uniform vec2 screenSize;
uniform float particleRadius;

void main()
{
    vec2 pos = particles[gl_VertexID].position;

    vec2 clipPos = (pos / screenSize) * 2.0 - 1.0;

    gl_Position = vec4(clipPos,0,1);
    gl_PointSize = particleRadius * 2.0;
}