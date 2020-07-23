#ifndef _CAMERA_H_
#define _CAMERA_H_
#include "core/math/matrix4D.h"

namespace Display
{
    class CameraView
    {
    public:
        CameraView();
        ~CameraView() = default;

        void UpdateCamera(int w, int h);

    private:
        Math::vector3D position;
        Math::vector3D origin;
        Math::vector3D headUp;
        Math::vector3D camFront;
        bool firstM = true;
        float pitch;
        float yaw;

        float zNear = 1.0f;
        float zFar = 100.0f;

        Math::matrix4D projection;
        Math::matrix4D view;

        int width;
        int height;

        float camSpeed = 1.0f;
    };
}

#endif // !_CAMERA_H_
