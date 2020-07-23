#include "camera.h"

namespace Display
{
    CameraView::CameraView()
	{
        //m_width = srv->width;
        //m_height = srv->height;
        position.setValues(0, 0, 2);
        origin.setValues(0, 0, 0);
        headUp.setValues(0, 1, 0);
        camFront.setValues(0.0f, 0.0f, -1.0f);
        yaw = -90.0f;    // Yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right (due to how Eular angles work) so we initially rotate a bit to the left.
        pitch = 0.0f;
	}
    void CameraView::UpdateCamera(int w, int h)
    {
        width = w;
        height = h;
        projection = projection.setPerspective(45.0f, (float)(width / height), zNear, zFar);
        view = view.LookAtRH(position, position + camFront, headUp);

        /*if (key->leftShift)
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
        }*/
    /*}*/
    }
}