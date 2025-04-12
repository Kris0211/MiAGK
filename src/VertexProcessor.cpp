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
    rtx::Vector3 s = rtx::Vector3::CrossProduct(s, up);
    rtx::Vector3 u = s.Cross(f);

    rtx::Matrix4 world2view
    {
        rtx::Vector4(s.x, u.x, -f.x, 0.f),
        rtx::Vector4(s.y, u.y, -f.y, 0.f),
        rtx::Vector4(s.z, u.z, -f.z, 0.f),
        rtx::Vector4(0.f, 0.f, 0.f, 1.f)
    };

    rtx::Matrix4 m;
    m.SetRow(3, rtx::Vector4(-eye.x, -eye.y, -eye.z, 1.0));

    return world2view.Mul(m);
}
