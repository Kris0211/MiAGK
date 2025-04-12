#pragma once

#include "../RasTerX/include/Matrix4.hpp"
#include "../RasTerX/include/Vector3.hpp"

class VertexProcessor 
{
private:
    rtx::Matrix4 obj2world;
    rtx::Matrix4 world2view;
    rtx::Matrix4 view2proj;

public:
    static rtx::Matrix4 SetPerspective(const float fovY, const float aspect, const float near, const float far);
    static rtx::Matrix4 SetLookAt(const rtx::Vector3& eye, const rtx::Vector3& center, const rtx::Vector3& up);
};
