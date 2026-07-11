#version 460 core
struct Particle
{
    vec2 position;
};

layout(std430, binding = 0) buffer ParticleBuffer
{
    Particle particles[];
};

void main()
{
    vec2 pos = particles[gl_VertexID].position;
    gl_Position = vec4(pos,0,1);
    gl_PointSize = 12.0;
}