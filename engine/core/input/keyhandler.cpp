#include "keyhandler.h"
#include "render/camera.h"
#include "core/math/vector3D.h"
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

    void KeyHandler::Init(Display::Window* window)
    {
        Display::CameraView* cam = Display::CameraView::GetInstance();

        window->SetKeyPressFunction([this, window, cam](int key, int, int action, int)
            {
                if ((key == GLFW_KEY_ESCAPE || key == GLFW_KEY_Q) && action == GLFW_PRESS)
                {
                    glfwSetWindowShouldClose(window->window, 1);
                }
                if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_PRESS)
                {
                    leftShift = true;
                    cam->camSpeed = 100.f;
                }
                if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_RELEASE)
                {
                    leftShift = false;
                    cam->camSpeed = 2.5f;
                }
                if (GLFW_KEY_W == key && action == GLFW_PRESS)
                {
                    W = true;
                }
                if (GLFW_KEY_W == key && action == GLFW_RELEASE)
                {
                    W = false;
                }
                if (GLFW_KEY_A == key && action == GLFW_PRESS)
                {
                    A = true;
                }
                if (GLFW_KEY_A == key && action == GLFW_RELEASE)
                {
                    A = false;
                }
                if (GLFW_KEY_S == key && action == GLFW_PRESS)
                {
                    S = true;
                }
                if (GLFW_KEY_S == key && action == GLFW_RELEASE)
                {
                    S = false;
                }
                if (GLFW_KEY_D == key && action == GLFW_PRESS)
                {
                    D = true;
                }
                if (GLFW_KEY_D == key && action == GLFW_RELEASE)
                {
                    D = false;
                }

            });
        window->SetMousePressFunction([this, cam](int key, int state, int)
            {
                if (key == GLFW_MOUSE_BUTTON_LEFT && state == GLFW_PRESS)
                {
                    cam->mousePressedLeft = true;
                }
                if (key == GLFW_MOUSE_BUTTON_LEFT && state == GLFW_RELEASE)
                {
                    cam->mousePressedLeft = false;
                }
                if (key == GLFW_MOUSE_BUTTON_RIGHT && state == GLFW_PRESS)
                {
                    cam->mousePressed = true;
                }
                if (key == GLFW_MOUSE_BUTTON_RIGHT && state == GLFW_RELEASE)
                {
                    cam->mousePressed = false;
                }
            });

        window->SetMouseScrollFunction([this, cam](double x, double y)
            {
                cam->scrollX += 0.1f * y;
            });

        window->SetMouseMoveFunction([this, cam](double xpos, double ypos)
            {
                cam->MoveCamera(xpos, ypos);
            });
    }


}
