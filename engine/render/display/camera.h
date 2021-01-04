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
        static CameraView* CameraView::GetInstance();

        void UpdateCamera(int w, int h);
        void MoveCamera(double xpos, double ypos);

        bool mousePressed = false;
        bool mousePressedLeft = false;
        double scrollX = 0.0f;
        float camSpeed = 1.0f;

        Math::matrix4D projection;
        Math::matrix4D view;

    private:
        float rad(float d) { return  (PI / 180.f) * d; }

        Math::vector3D camFront;
        Math::vector3D position;
        Math::vector3D origin;
        Math::vector3D headUp;

        double posX = 0.0f;
        double posY = 0.0f;
        double oldPosX = 0.0f;
        double oldPosY = 0.0f;
        double x;
        double y;
        double z = 0.0f;
        float pitch;
        float yaw;
        float zNear = 1.0f;
        float zFar = 100.0f;

        int width;
        int height;

        static CameraView* instance;

        float timeStep = 1.0f / 16.0f;
    };
}

#endif // !_CAMERA_H_
