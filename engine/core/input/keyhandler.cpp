#include "keyhandler.h"
namespace Input
{
    KeyHandler* KeyHandler::instance = 0;

    KeyHandler::KeyHandler()
    {

    }

    KeyHandler* KeyHandler::GetInstance()
    {
        if (instance == 0)
        {
            instance = new KeyHandler();
        }
        return instance;
    }


    //void KeyHandler::Init(Display::Window* window)
    //{
    //    Display::Camera* cam = Display::Camera::GetInstance();

    //    window->SetKeyPressFunction([this, window, cam](int32 key, int32, int32 action, int32)
    //        {
    //            if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    //            {
    //                window->Close();
    //            }
    //            if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_PRESS)
    //            {
    //                leftShift = true;
    //                cam->camSpeed = 100.f;
    //            }
    //            if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_RELEASE)
    //            {
    //                leftShift = false;
    //                cam->camSpeed = 2.5f;
    //            }
    //            if (GLFW_KEY_W == key && action == GLFW_PRESS)
    //            {
    //                W = true;
    //            }
    //            if (GLFW_KEY_W == key && action == GLFW_RELEASE)
    //            {
    //                W = false;
    //            }
    //            if (GLFW_KEY_A == key && action == GLFW_PRESS)
    //            {
    //                A = true;
    //            }
    //            if (GLFW_KEY_A == key && action == GLFW_RELEASE)
    //            {
    //                A = false;
    //            }
    //            if (GLFW_KEY_S == key && action == GLFW_PRESS)
    //            {
    //                S = true;
    //            }
    //            if (GLFW_KEY_S == key && action == GLFW_RELEASE)
    //            {
    //                S = false;
    //            }
    //            if (GLFW_KEY_D == key && action == GLFW_PRESS)
    //            {
    //                D = true;
    //            }
    //            if (GLFW_KEY_D == key && action == GLFW_RELEASE)
    //            {
    //                D = false;
    //            }

    //        });
    //    window->SetMousePressFunction([this, cam](int32 key, int32 state, int32)
    //        {
    //            if (key == GLFW_MOUSE_BUTTON_LEFT && state == GLFW_PRESS)
    //            {
    //                cam->mousePressedLeft = true;
    //            }
    //            if (key == GLFW_MOUSE_BUTTON_LEFT && state == GLFW_RELEASE)
    //            {
    //                cam->mousePressedLeft = false;
    //            }
    //            if (key == GLFW_MOUSE_BUTTON_RIGHT && state == GLFW_PRESS)
    //            {
    //                cam->mousePressed = true;
    //            }
    //            if (key == GLFW_MOUSE_BUTTON_RIGHT && state == GLFW_RELEASE)
    //            {
    //                cam->mousePressed = false;
    //            }
    //        });

    //    window->SetMouseScrollFunction([this, cam](float64 x, float64 y)
    //        {
    //            cam->scrollX += 0.1f * y;
    //        });

    //    window->SetMouseMoveFunction([this, cam](float64 xpos, float64 ypos)
    //        {
    //            if (!cam->mousePressed)
    //            {
    //                cam->oldPosX = xpos;
    //                cam->oldPosY = ypos;
    //                return;
    //            }

    //            GLfloat xoffset = GLfloat(xpos - cam->oldPosX);
    //            GLfloat yoffset = GLfloat(cam->oldPosY - ypos);

    //            float sensitivity = 0.05f;
    //            xoffset *= sensitivity;
    //            yoffset *= sensitivity;

    //            cam->yaw += xoffset;
    //            cam->pitch += yoffset;

    //            if (cam->pitch > 89.0f)
    //                cam->pitch = 89.0f;
    //            if (cam->pitch < -89.0f)
    //                cam->pitch = -89.0f;

    //            vector3D front;
    //            front[0] = (cos(rad(cam->yaw)) * cos(rad(cam->pitch)));
    //            front[1] = (sin(rad(cam->pitch)));
    //            front[2] = (sin(rad(cam->yaw)) * cos(rad(cam->pitch)));
    //            cam->camFront = front.normalizeRe();

    //            cam->oldPosX = xpos;
    //            cam->oldPosY = ypos;
    //        });


    //}

    //float KeyHandler::rad(float d)  //Degrees to rad
    //{
    //    float rad = (PI / 180.f) * d;
    //    return rad;
    //}
}
