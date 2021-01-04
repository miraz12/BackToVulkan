#include "camera.h"
#include "core/input/keyhandler.h"

namespace Display
{
    CameraView* CameraView::instance = 0;

    CameraView* CameraView::GetInstance()
    {
        if (instance == 0)
        {
            instance = new CameraView();
        }
        return instance;
    }

    CameraView::CameraView()
	{
        //m_width = srv->width;
        //m_height = srv->height;
        position.setValues(0.0f, 25.0f, 25.0f);
        origin.setValues(0.0f, 0.0f, 0.0f);
        headUp.setValues(0.0f, 1.0f, 0.0f);
        camFront.setValues(0.0f, 0.0f, -1.0f);
        yaw = -90.0f;    // Yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right (due to how Eular angles work) so we initially rotate a bit to the left.
        pitch = 0.0f;
	}
    void CameraView::UpdateCamera(int w, int h)
    {
        Input::KeyHandler* key = Input::KeyHandler::GetInstance();

        width = w;
        height = h;
        projection = projection.setPerspective(45.0f, (width / (float)height), zNear, zFar);
        projection[1][1] *= -1;
        view = view.LookAtRH(position, position + camFront, headUp);

        if (key->leftShift)
        {
            camSpeed = 50.f;
        }
        else
        {
            camSpeed = .5f;
        }
        if (key->W)
        {
            position[0] += (camFront * camSpeed * timeStep)[0];
            position[1] += (camFront * camSpeed * timeStep)[1];
            position[2] += (camFront * camSpeed * timeStep)[2];
        }
        if (key->A)
        {
            position[0] -= (camFront.cross(headUp).normalizeRe() * camSpeed * timeStep)[0];
            position[1] -= (camFront.cross(headUp).normalizeRe() * camSpeed * timeStep)[1];
            position[2] -= ((camFront.cross(headUp).normalizeRe()) * camSpeed * timeStep)[2];
        }
        if (key->S)
        {
            position[0] -= (camFront * camSpeed * timeStep)[0];
            position[1] -= (camFront * camSpeed * timeStep)[1];
            position[2] -= (camFront * camSpeed * timeStep)[2];
        }
        if (key->D)
        {
            position[0] += (camFront.cross(headUp).normalizeRe() * camSpeed * timeStep)[0];
            position[1] += (camFront.cross(headUp).normalizeRe() * camSpeed * timeStep)[1];
            position[2] += ((camFront.cross(headUp).normalizeRe()) * camSpeed * timeStep)[2];
        }
    
    }
    void CameraView::MoveCamera(double xpos, double ypos)
    {
        if (!mousePressed)
        {
            oldPosX = xpos;
            oldPosY = ypos;
            return;
        }

        GLfloat xoffset = GLfloat(xpos - oldPosX);
        GLfloat yoffset = GLfloat(oldPosY - ypos);

        float sensitivity = 0.05f;
        xoffset *= sensitivity;
        yoffset *= sensitivity;

        yaw += xoffset;
        pitch += yoffset;

        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;

        Math::vector3D front;
        front[0] = (cos(rad(yaw)) * cos(rad(pitch)));
        front[1] = (sin(rad(pitch)));
        front[2] = (sin(rad(yaw)) * cos(rad(pitch)));
        camFront = front.normalizeRe();

        oldPosX = xpos;
        oldPosY = ypos;
    }
}