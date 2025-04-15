#include "../include/VertexProcessor.h"
#include "../RasTerX/include/MathUtils.hpp"

rtx::Matrix4 VertexProcessor::SetPerspective(float fovY, const float aspect, const float near, const float far)
{
    fovY *= PI / 360.f;
    const float f = cos(fovY) / sin(fovY);

    return {
        rtx::Vector4(f / aspect, 0.f, 0.f, 0.f),
        rtx::Vector4(0.f, f, 0.f, 0.f),
        rtx::Vector4(0.f, 0.f, (far + near) / (near - far), -1.f),
        rtx::Vector4(0.f, 0.f, 2.f * far * near / (near - far), 0.f)
    };
}

rtx::Matrix4 VertexProcessor::SetLookAt(const rtx::Vector3& eye, const rtx::Vector3& center, const rtx::Vector3& up)
{
    rtx::Vector3 f = (center - eye).Normal();
    rtx::Vector3 r = rtx::Vector3::CrossProduct(f, up).Normal();
    rtx::Vector3 u = rtx::Vector3::CrossProduct(r, f).Normal();

    rtx::Matrix4 world2view
    {
        rtx::Vector4(r.x, u.x, -f.x, 0.f),
        rtx::Vector4(r.y, u.y, -f.y, 0.f),
        rtx::Vector4(r.z, u.z, -f.z, 0.f),
        rtx::Vector4(0.f, 0.f, 0.f, 1.f)
    };

    return world2view * Translate(rtx::Vector3(-eye.x, -eye.y, -eye.z));
}

rtx::Matrix4 VertexProcessor::Translate(const rtx::Vector3& v)
{
    return 
    {
        rtx::Vector4(1.f, 0.f, 0.f, v.x),
        rtx::Vector4(0.f, 1.f, 0.f, v.y),
        rtx::Vector4(0.f, 0.f, 1.f, v.z),
        rtx::Vector4(0.f, 0.f, 0.f, 1.f)
    };
}

rtx::Matrix4 VertexProcessor::Scale(const rtx::Vector3& v)
{
    return 
    { 
        rtx::Vector4(v.x, 0.f, 0.f, 0.f),
        rtx::Vector4(0.f, v.y, 0.f, 0.f),
        rtx::Vector4(0.f, 0.f, v.z, 0.f),
        rtx::Vector4(0.f, 0.f, 0.f, 1.f)
    };
}

rtx::Matrix4 VertexProcessor::Rotate(const float rot, const rtx::Vector3& v)
{
    float s = sin(rot * PI / 180.f);
    float c = cos(rot * PI / 180.f);
    const rtx::Vector3 vec = v.Normal();

    return 
    { 
        rtx::Vector4(vec.x * vec.x * (1 - c) + c, vec.y * vec.x * (1 - c) + vec.z * s, vec.x * vec.z * (1 - c) - vec.y * s, 0),
        rtx::Vector4(vec.x * vec.y * (1 - c) - vec.z * s, vec.y * vec.y * (1 - c) + c, vec.y * vec.z * (1 - c) + vec.x * s, 0),
        rtx::Vector4(vec.x * vec.z * (1 - c) + vec.y * s, vec.y * vec.z * (1 - c) - vec.x * s, vec.z * vec.z * (1 - c) + c, 0),
        rtx::Vector4(0, 0, 0, 1) 
    };
}
