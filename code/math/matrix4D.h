#pragma once
#include <iostream>
#include "vector4D.h"
#include "vector3D.h"
#include "matrix3D.h"

namespace Math
{

	class matrix4D
	{
	public:


		//2D array
		float values2D[4][4];

		inline matrix4D(matrix3D m)
		{
			this->values2D[0][0] = m.values2D[0][0];
			this->values2D[0][1] = m.values2D[0][1];
			this->values2D[0][2] = m.values2D[0][2];
			this->values2D[0][3] = 0;

			this->values2D[1][0] = m.values2D[1][0];
			this->values2D[1][1] = m.values2D[1][1];
			this->values2D[1][2] = m.values2D[1][2];
			this->values2D[1][3] = 0;

			this->values2D[2][0] = m.values2D[2][0];
			this->values2D[2][1] = m.values2D[2][1];
			this->values2D[2][2] = m.values2D[2][2];
			this->values2D[2][3] = 0;

			this->values2D[3][0] = 0;
			this->values2D[3][1] = 0;
			this->values2D[3][2] = 0;
			this->values2D[3][3] = 1;
		}

		inline matrix4D(void)
		{
			this->values2D[0][0] = 1;
			this->values2D[0][1] = 0;
			this->values2D[0][2] = 0;
			this->values2D[0][3] = 0;

			this->values2D[1][0] = 0;
			this->values2D[1][1] = 1;
			this->values2D[1][2] = 0;
			this->values2D[1][3] = 0;

			this->values2D[2][0] = 0;
			this->values2D[2][1] = 0;
			this->values2D[2][2] = 1;
			this->values2D[2][3] = 0;

			this->values2D[3][0] = 0;
			this->values2D[3][1] = 0;
			this->values2D[3][2] = 0;
			this->values2D[3][3] = 1;
		}

		inline ~matrix4D(void)
		{

		}


		// matrix4D LookAtRH(vector3D eye, vector3D target, vector3D up)
		// {
		// 	vector3D zaxis = (eye - target).normalize();    // The "forward" vector.
		// 	vector3D xaxis = (up.cross(zaxis)).normalize();// The "right" vector.
		// 	vector3D yaxis = zaxis.cross(xaxis);     // The "up" vector.
		//
		// 	// Create a 4x4 orientation matrix from the right, up, and forward vectors
		// 	// This is transposed which is equivalent to performing an inverse
		// 	// if the matrix is orthonormalized (in this case, it is).
		//
		// 	matrix4D orientation;
		//
		// 		orientation[0][0] = xaxis[0];
		// 		orientation[0][1] = xaxis[1];
		// 		orientation[0][2] = xaxis[2];
		// 		orientation[0][3] = 0;
		//
		// 		orientation[1][0] = yaxis[0];
		// 		orientation[1][1] = yaxis[1];
		// 		orientation[1][2] = yaxis[2];
		// 		orientation[1][3] = 0;
		//
		// 		orientation[2][0] = zaxis[0];
		// 		orientation[2][1] = zaxis[1];
		// 		orientation[2][2] = zaxis[2];
		// 		orientation[2][3] = 0;
		//
		// 		orientation[3][0] = 0;
		// 		orientation[3][1] = 0;
		// 		orientation[3][2] = 0;
		// 		orientation[3][3] = 1;
		//
		//
		// 	// Create a 4x4 translation matrix.
		// 	// The eye position is negated which is equivalent
		// 	// to the inverse of the translation matrix.
		// 	// T(v)^-1 == T(-v)
		// 		matrix4D translation;
		//
		// 		values2D[3][0] = -(eye[0]);
		// 		values2D[3][1] = -(eye[1]);
		// 		values2D[3][2] = -(eye[2]);
		//
		//
		// 	// Combine the orientation and translation to compute
		// 	// the final view matrix
		// 	return (orientation * translation);
		// }


		inline vector4D transform(vector4D v)
		{
			vector4D res;
			for (int i = 0; i < 4; ++i)
			{
				res[i] = v[0] * this->values2D[0][i] + v[1] * this->values2D[1][i] + v[2] * this->values2D[2][i] + v[3] * this->values2D[3][i];
			}

			res[0] = res[0] / res[3];
			res[1] = res[1] / res[3];
			res[2] = res[2] / res[3];
			return res;
		}

		inline vector3D transform(vector3D v)
		{
			vector4D v4(v);
			vector4D res;
			for (int i = 0; i < 4; ++i)
			{
				res[i] = v4[0] * this->values2D[0][i] + v4[1] * this->values2D[1][i] + v4[2] * this->values2D[2][i] + v4[3] * this->values2D[3][i];
			}

			vector3D res3(res[0], res[1], res[2]);
			return res3;
		}

		inline matrix4D ViewFPS(vector3D eye, float pitch, float yaw)
		{
			// If the pitch and yaw angles are in degrees,
			// they need to be converted to radians. Here
			// I assume the values are already converted to radians.
			float cosPitch = cos(pitch);
			float sinPitch = sin(pitch);
			float cosYaw = cos(yaw);
			float sinYaw = sin(yaw);

			vector3D xaxis = { cosYaw, 0, -sinYaw };
			vector3D yaxis = { sinYaw * sinPitch, cosPitch, cosYaw * sinPitch };
			vector3D zaxis = { sinYaw * cosPitch, -sinPitch, cosPitch * cosYaw };

			matrix4D viewMatrix;
			viewMatrix[0][0] = xaxis[0];
			viewMatrix[1][0] = xaxis[1];
			viewMatrix[2][0] = xaxis[2];
			viewMatrix[3][0] = -(xaxis.dot(eye));

			viewMatrix[0][1] = yaxis[0];
			viewMatrix[1][1] = yaxis[1];
			viewMatrix[2][1] = yaxis[2];
			viewMatrix[3][1] = -(yaxis.dot(eye));

			viewMatrix[0][2] = zaxis[0];
			viewMatrix[1][2] = zaxis[1];
			viewMatrix[2][2] = zaxis[2];
			viewMatrix[3][2] = -(zaxis.dot(eye));

			viewMatrix[0][3] = 0.0f;
			viewMatrix[1][3] = 0.0f;
			viewMatrix[2][3] = 0.0f;
			viewMatrix[3][3] = 1.0f;

			~viewMatrix;

			return viewMatrix;

		}

		//asd
		inline matrix4D View(vector3D eye, vector3D target, vector3D up)
		{
			vector3D x, y, z;
			vector3D vect(0, 0, 0);

			z = target - eye;
			z = z.normalize(z);
			x = up.cross(z);
			x = x.normalize(x);
			y = z.cross(x);


			matrix4D viewm;
			viewm[0][0] = x[0];
			viewm[0][1] = x[1];
			viewm[0][2] = x[2];
			viewm[0][3] = -x.dot(eye);

			viewm[1][0] = y[0];
			viewm[1][1] = y[1];
			viewm[1][2] = y[2];
			viewm[1][3] = -y.dot(eye);

			viewm[2][0] = z[0];
			viewm[2][1] = z[1];
			viewm[2][2] = z[2];
			viewm[2][3] = -z.dot(eye);

			viewm[3][0] = 0.0f;
			viewm[3][1] = 0.0f;
			viewm[3][2] = 0.0f;
			viewm[3][3] = 1.0f;

			return viewm;
		}


		matrix4D LookAtRH(vector3D eye, vector3D target, vector3D up)
		{

			/*    vector3D zaxis = (eye - target);
				zaxis.normalize();
				vector3D xaxis = (up.cross(zaxis));// The "right" vector.
				xaxis.normalize();
				vector3D yaxis = zaxis.cross(xaxis);    // The "forward" vector.

				matrix4D orientation;

				orientation[0][0] = xaxis[0];
				orientation[1][0] = xaxis[1];
				orientation[2][0] = xaxis[2];
				orientation[3][0] = 0;

				orientation[0][1] = yaxis[0];
				orientation[1][1] = yaxis[1];
				orientation[2][1] = yaxis[2];
				orientation[3][1] = 0;

				orientation[0][2] = zaxis[0];
				orientation[1][2] = zaxis[1];
				orientation[2][2] = zaxis[2];
				orientation[3][2] = 0;

				orientation[0][3] = 0.0f;
				orientation[1][3] = 0.0f;
				orientation[2][3] = 0.0f;
				orientation[3][3] = 1.0f;

				matrix4D translation;

				translation[0][3] = -eye[0];
				translation[1][3] = -eye[1];
				translation[2][3] = -eye[2];
				translation[3][3] = 1.0f;

				matrix4D viewMatrix;
				viewMatrix = orientation * translation;

				~viewMatrix;
				return  viewMatrix;*/


			vector3D zaxis = (eye - target);
			zaxis.normalize();
			vector3D normUp = up.normalizeRe();
			vector3D xaxis = (normUp.cross(zaxis));// The "right" vector.
			xaxis.normalize();
			vector3D yaxis = zaxis.cross(xaxis);    // The "forward" vector.

			 // The "up" vector.

			// Create a 4x4 view matrix from the right, up, forward and eye position vectors
			matrix4D viewMatrix;

			/*
			viewMatrix[0][0] =
			viewMatrix[0][1] =
			viewMatrix[0][2] =
			viewMatrix[0][3] =

			viewMatrix[1][0] =
			viewMatrix[1][1] =
			viewMatrix[1][2] =
			viewMatrix[1][3] =

			viewMatrix[2][0] =
			viewMatrix[2][1] =
			viewMatrix[2][2] =
			viewMatrix[2][3] =

			viewMatrix[3][0] =
			viewMatrix[3][1] =
			viewMatrix[3][2] =
			viewMatrix[3][3] = */

			viewMatrix[0][0] = xaxis[0];
			viewMatrix[1][0] = xaxis[1];
			viewMatrix[2][0] = xaxis[2];
			viewMatrix[3][0] = -(xaxis.dot(eye));

			viewMatrix[0][1] = yaxis[0];
			viewMatrix[1][1] = yaxis[1];
			viewMatrix[2][1] = yaxis[2];
			viewMatrix[3][1] = -(yaxis.dot(eye));

			viewMatrix[0][2] = zaxis[0];
			viewMatrix[1][2] = zaxis[1];
			viewMatrix[2][2] = zaxis[2];
			viewMatrix[3][2] = -(zaxis.dot(eye));

			viewMatrix[0][3] = 0.0f;
			viewMatrix[1][3] = 0.0f;
			viewMatrix[2][3] = 0.0f;
			viewMatrix[3][3] = 1.0f;

			return viewMatrix;
		}

		matrix4D setPerspective(float fovY, float aspect, float zNear, float zFar)
		{
			matrix4D temp;

			//float halfFov = 0.5f * fovY;
			//float sinFov = sin(halfFov);
			//float cosFov = cos(halfFov);

			float D2R = PI / 180.0f;
			float height = 1.0f / tan(D2R * fovY / 2);
			float width = height / aspect;

			float dist = zFar / (zNear - zFar);

			dist *= 0.5f;

			temp[0][0] = width;
			temp[0][1] = 0.0f;
			temp[0][2] = 0.0f;
			temp[0][3] = 0.0f;

			temp[1][0] = 0.0f;
			temp[1][1] = height;
			temp[1][2] = 0.0f;
			temp[1][3] = 0.0f;

			temp[2][0] = 0.0f;
			temp[2][1] = 0.0f;
			temp[2][2] = dist;
			temp[2][3] = -1.0f;

			temp[3][0] = 0.0f;
			temp[3][1] = 0.0f;
			temp[3][2] = dist * zNear;
			temp[3][3] = 0.0f;

			return temp;


			/*

			const float zRange = zNear - zFar;
			const float tanHalfFOV = tanf((PI / 180.0f)*(fovY * 0.5f));

			temp[0][0] = 1.0f / (tanHalfFOV * aspect);
			temp[0][1] = 0.0f;
			temp[0][2] = 0.0f;
			temp[0][3] = 0.0f;

			temp[1][0] = 0.0f;
			temp[1][1] = 1.0f / tanHalfFOV;
			temp[1][2] = 0.0f;
			temp[1][3] = 0.0f;

			temp[2][0] = 0.0f;
			temp[2][1] = 0.0f;
			temp[2][2] = ((-zNear) - zFar) / zRange;
			temp[2][3] = 2.0f * zFar * zNear / zRange;

			temp[3][0] = 0.0f;
			temp[3][1] = 0.0f;
			temp[3][2] = 1.0f;
			temp[3][3] = 0.0f;
		*/

		// params: left, right, bottom, top, near, far
	//	return temp;
		}

		inline float* get()
		{

			return (float*)values2D;
		}

		inline void scale(float x, float y, float z)
		{
			matrix4D temp;
			values2D[0][0] *= x;
			values2D[1][1] *= y;
			values2D[2][2] *= z;
		}

		inline matrix4D setPos(float x, float y, float z)
		{
			values2D[3][0] = x;
			values2D[3][1] = y;
			values2D[3][2] = z;
			return (*this);
		}

		inline matrix4D setPos(vector3D v)
		{
			values2D[3][0] = v.x();
			values2D[3][1] = v.y();
			values2D[3][2] = v.z();
			return (*this);
		}


		inline vector3D getPosition()
		{
			return  vector3D(values2D[3][0], values2D[3][1], values2D[3][2]);
		}

		inline matrix4D rot_x(float r)
		{
			matrix4D x;
			float c = cosf(r * PI / 180.0f);
			float s = sinf(r * PI / 180.0f);

			x.values2D[0][0] = 1;
			x.values2D[0][1] = 0;
			x.values2D[0][2] = 0;
			x.values2D[1][0] = 0;
			x.values2D[1][1] = c;
			x.values2D[1][2] = -s;
			x.values2D[2][0] = 0;
			x.values2D[2][1] = s;
			x.values2D[2][2] = c;


			return  x;
		}
		inline matrix4D rot_y(float r)
		{
			matrix4D y;
			float c = cosf(r * PI / 180.0f);
			float s = sinf(r * PI / 180.0f);

			y.values2D[0][0] = c;
			y.values2D[0][1] = 0;
			y.values2D[0][2] = s;
			y.values2D[1][0] = 0;
			y.values2D[1][1] = 1;
			y.values2D[1][2] = 0;
			y.values2D[2][0] = -s;
			y.values2D[2][1] = 0;
			y.values2D[2][2] = c;

			~y;

			return  y;
		}
		inline matrix4D rot_z(float r)
		{
			matrix4D z;
			float c = cosf(r * PI / 180.0f);
			float s = sinf(r * PI / 180.0f);

			z.values2D[0][0] = c;
			z.values2D[0][1] = -s;
			z.values2D[0][2] = 0;
			z.values2D[1][0] = s;
			z.values2D[1][1] = c;
			z.values2D[1][2] = 0;
			z.values2D[2][0] = 0;
			z.values2D[2][1] = 0;
			z.values2D[2][2] = 1;

			return z;
		}
		inline matrix4D rot_v(const vector4D v, float r)
		{
			matrix4D temp;

			float c = cosf(r * PI / 180.0f);
			float s = sinf(r * PI / 180.0f);
			float x = v.Varray[0];
			float y = v.Varray[1];
			float z = v.Varray[2];

			temp.values2D[0][0] = pow(x, 2) + (1 - pow(x, 2)) * c;
			temp.values2D[0][1] = x * y * (1 - c) - x * s;
			temp.values2D[0][2] = x * z * (1 - c) + y * s;
			temp.values2D[1][0] = x * y * (1 - c) + z * s;
			temp.values2D[1][1] = pow(y, 2) + (1 - pow(y, 2)) * c;
			temp.values2D[1][2] = x * z * (1 - c) - x * s;
			temp.values2D[2][0] = x * z * (1 - c) - y * s;
			temp.values2D[2][1] = y * z * (1 - c) + x * s;
			temp.values2D[2][2] = pow(z, 2) + (1 - pow(z, 2)) * c;

			return temp;

		}
		inline matrix4D operator*(const matrix4D& m)
		{
			matrix4D temp(*this);
			matrix4D m2;

			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					m2.values2D[i][j] = 0;

					for (int k = 0; k < 4; k++)
					{
						m2.values2D[i][j] += temp.values2D[i][k] * m.values2D[k][j];
					}
				}
			}
			return m2;
		}
		inline vector4D operator*(const vector4D& v)
		{
			vector4D temp;
			temp.setValues(0);

			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					temp.Varray[i] += (this->values2D[i][j] * v.Varray[i]);
				}
			}
			return temp;
		}

		inline vector3D operator*(const vector3D& v)
		{
			vector3D temp;
			temp.setValues(0);
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					temp.Varray[i] += (this->values2D[i][j] * v.Varray[i]);
				}
			}
			return temp;
		}
		inline friend std::ostream& operator<<(std::ostream& os, const matrix4D& m)
		{
			for (int i = 0; i < 4 + 1; i++)
			{
				for (int j = 0; j < 4 + 1; j++)
				{
					os << m.values2D[i][j] << "\t";
				}
				os << std::endl;
			}
			return os;
		}
		inline void setValues(float v)
		{
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					values2D[i][j] = v;
				}
			}
		}
		inline void operator~()
		{

			matrix4D temp;
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					temp[i][j] = values2D[i][j];
				}
			}

			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					values2D[j][i] = temp[i][j];
				}
			}

		}
		float* operator[](int n)
		{

			return this->values2D[n];

		}
		inline matrix4D operator+(const matrix4D& M)
		{
			matrix4D M1 = *this;
			matrix4D temp;
			temp[0][0] = M1[0][0] + M.values2D[0][0];
			temp[0][1] = M1[0][1] + M.values2D[0][1];
			temp[0][2] = M1[0][2] + M.values2D[0][2];
			temp[0][3] = M1[0][3] + M.values2D[0][3];

			temp[1][0] = M1[1][0] + M.values2D[1][0];
			temp[1][1] = M1[1][1] + M.values2D[1][1];
			temp[1][2] = M1[1][2] + M.values2D[1][2];
			temp[1][3] = M1[1][3] + M.values2D[1][3];

			temp[2][0] = M1[2][0] + M.values2D[2][0];
			temp[2][1] = M1[2][1] + M.values2D[2][1];
			temp[2][2] = M1[2][2] + M.values2D[2][2];
			temp[2][3] = M1[2][3] + M.values2D[2][3];

			temp[3][0] = M1[3][0] + M.values2D[3][0];
			temp[3][1] = M1[3][1] + M.values2D[3][1];
			temp[3][2] = M1[3][2] + M.values2D[3][2];
			temp[3][3] = M1[3][3] + M.values2D[3][3];

			return temp;

		}

		inline float det(void)
		{
			float deta;
			deta = ((this->values2D[0][0] * this->values2D[1][1] * this->values2D[2][2] * this->values2D[3][3]) + (this->values2D[0][0] * this->values2D[1][2] * this->values2D[2][3] * this->values2D[3][1]) + (this->values2D[0][0] * this->values2D[1][3] * this->values2D[2][1] * this->values2D[3][2])
				+ (this->values2D[0][1] * this->values2D[1][0] * this->values2D[2][3] * this->values2D[3][2]) + (this->values2D[0][1] * this->values2D[1][2] * this->values2D[2][0] * this->values2D[3][3]) + (this->values2D[0][1] * this->values2D[1][3] * this->values2D[2][2] * this->values2D[3][0])
				+ (this->values2D[0][2] * this->values2D[1][0] * this->values2D[2][1] * this->values2D[3][3]) + (this->values2D[0][2] * this->values2D[1][1] * this->values2D[2][3] * this->values2D[3][0]) + (this->values2D[0][2] * this->values2D[1][3] * this->values2D[2][0] * this->values2D[3][1])
				+ (this->values2D[0][3] * this->values2D[1][0] * this->values2D[2][2] * this->values2D[3][1]) + (this->values2D[0][3] * this->values2D[1][1] * this->values2D[2][0] * this->values2D[2][2]) + (this->values2D[0][3] * this->values2D[1][2] * this->values2D[2][1] * this->values2D[2][0])
				- (this->values2D[0][0] * this->values2D[1][1] * this->values2D[2][3] * this->values2D[3][2]) - (this->values2D[0][0] * this->values2D[1][2] * this->values2D[2][1] * this->values2D[3][3]) - (this->values2D[0][0] * this->values2D[1][3] * this->values2D[2][2] * this->values2D[2][1])
				- (this->values2D[0][1] * this->values2D[1][0] * this->values2D[2][2] * this->values2D[3][3]) - (this->values2D[0][1] * this->values2D[1][2] * this->values2D[2][3] * this->values2D[3][0]) - (this->values2D[0][1] * this->values2D[1][3] * this->values2D[2][0] * this->values2D[3][2])
				- (this->values2D[0][2] * this->values2D[1][0] * this->values2D[2][3] * this->values2D[3][1]) - (this->values2D[0][2] * this->values2D[1][1] * this->values2D[2][0] * this->values2D[3][3]) - (this->values2D[0][2] * this->values2D[0][3] * this->values2D[2][1] * this->values2D[3][0])
				- (this->values2D[0][3] * this->values2D[1][0] * this->values2D[2][1] * this->values2D[3][2]) - (this->values2D[0][3] * this->values2D[1][1] * this->values2D[2][2] * this->values2D[3][0]) - (this->values2D[0][3] * this->values2D[1][2] * this->values2D[2][0] * this->values2D[3][1])
				);

			return deta;
		}
		inline matrix4D adj(void)
		{
			matrix4D temp;

			temp.values2D[0][0] = this->values2D[1][1] * this->values2D[2][2] - this->values2D[2][1] * this->values2D[1][2];
			temp.values2D[0][1] = -(this->values2D[0][1] * this->values2D[2][2] - this->values2D[2][1] * this->values2D[0][2]);
			temp.values2D[0][2] = this->values2D[0][1] * this->values2D[2][2] - this->values2D[2][1] * this->values2D[0][2];
			temp.values2D[1][0] = -(this->values2D[1][0] * this->values2D[2][2] - this->values2D[2][0] * this->values2D[1][2]);
			temp.values2D[1][1] = this->values2D[0][0] * this->values2D[2][2] - this->values2D[2][0] * this->values2D[0][2];
			temp.values2D[1][2] = -(this->values2D[0][0] * this->values2D[2][1] - this->values2D[2][0] * this->values2D[0][1]);
			temp.values2D[2][0] = this->values2D[0][1] * this->values2D[1][2] - this->values2D[1][1] * this->values2D[0][2];
			temp.values2D[2][1] = -(this->values2D[0][0] * this->values2D[0][2] - this->values2D[1][0] * this->values2D[1][2]);
			temp.values2D[2][2] = this->values2D[0][0] * this->values2D[1][1] - this->values2D[1][0] * this->values2D[0][1];

			return temp;
		}
		inline matrix4D inv()
		{
			float deta;
			deta = 1 / det();
			matrix4D new_in_mat;

			new_in_mat[0][0] = (deta * ((values2D[1][1] * values2D[2][2] * values2D[3][3]) + (values2D[1][2] * values2D[2][3] * values2D[3][1]) + (values2D[1][3] * values2D[2][1] * values2D[3][2]) - (values2D[1][1] * values2D[2][3] * values2D[3][2]) - (values2D[1][2] * values2D[2][1] * values2D[3][3]) - (values2D[1][3] * values2D[2][2] * values2D[3][1])));
			new_in_mat[0][1] = (deta * ((values2D[0][1] * values2D[2][3] * values2D[3][2]) + (values2D[0][2] * values2D[2][1] * values2D[3][3]) + (values2D[0][3] * values2D[2][2] * values2D[3][1])
				- (values2D[0][1] * values2D[2][2] * values2D[3][3]) - (values2D[0][2] * values2D[2][3] * values2D[3][1]) - (values2D[0][3] * values2D[2][1] * values2D[3][2])));
			new_in_mat[0][2] = (deta * ((values2D[0][1] * values2D[1][2] * values2D[3][3]) + (values2D[0][2] * values2D[1][3] * values2D[3][1]) + (values2D[0][3] * values2D[1][1] * values2D[3][2])
				- (values2D[0][1] * values2D[1][3] * values2D[3][2]) - (values2D[0][2] * values2D[1][1] * values2D[3][3]) - (values2D[0][3] * values2D[1][2] * values2D[3][1])));
			new_in_mat[0][3] = (deta * ((values2D[0][1] * values2D[1][3] * values2D[2][2]) + (values2D[0][2] * values2D[1][1] * values2D[2][3]) + (values2D[0][3] * values2D[1][2] * values2D[2][1])
				- (values2D[0][1] * values2D[1][2] * values2D[2][3]) - (values2D[0][2] * values2D[1][3] * values2D[2][1]) - (values2D[0][3] * values2D[1][1] * values2D[2][2])));


			new_in_mat[1][0] = (deta * ((values2D[1][0] * values2D[2][3] * values2D[3][2]) + (values2D[1][2] * values2D[2][0] * values2D[3][3]) + (values2D[1][3] * values2D[2][2] * values2D[3][0])
				- (values2D[1][0] * values2D[2][2] * values2D[3][3]) - (values2D[1][2] * values2D[2][3] * values2D[3][0]) - (values2D[1][3] * values2D[2][0] * values2D[3][2])));
			new_in_mat[1][1] = (deta * ((values2D[0][0] * values2D[2][2] * values2D[3][3]) + (values2D[0][2] * values2D[2][3] * values2D[3][0]) + (values2D[0][3] * values2D[2][0] * values2D[3][2])
				- (values2D[0][0] * values2D[2][3] * values2D[3][2]) - (values2D[0][2] * values2D[2][0] * values2D[3][3]) - (values2D[0][3] * values2D[2][2] * values2D[3][0])));
			new_in_mat[1][2] = (deta * ((values2D[0][0] * values2D[1][3] * values2D[3][2]) + (values2D[0][2] * values2D[1][0] * values2D[3][3]) + (values2D[0][3] * values2D[1][2] * values2D[3][0])
				- (values2D[0][0] * values2D[1][2] * values2D[3][3]) - (values2D[0][2] * values2D[1][3] * values2D[3][0]) - (values2D[0][3] * values2D[1][0] * values2D[3][2])));
			new_in_mat[1][3] = (deta * ((values2D[0][0] * values2D[1][2] * values2D[2][3]) + (values2D[0][2] * values2D[1][3] * values2D[2][0]) + (values2D[0][3] * values2D[1][0] * values2D[2][2])
				- (values2D[0][0] * values2D[1][3] * values2D[2][2]) - (values2D[0][2] * values2D[1][0] * values2D[2][3]) - (values2D[0][3] * values2D[1][2] * values2D[2][0])));

			new_in_mat[2][0] = (deta * ((values2D[1][0] * values2D[2][1] * values2D[3][3]) + (values2D[1][1] * values2D[2][3] * values2D[3][0]) + (values2D[1][3] * values2D[2][0] * values2D[3][1])
				- (values2D[1][0] * values2D[2][3] * values2D[3][1]) - (values2D[1][1] * values2D[2][0] * values2D[3][3]) - (values2D[1][3] * values2D[2][1] * values2D[3][0])));
			new_in_mat[2][1] = (deta * ((values2D[0][0] * values2D[2][3] * values2D[3][1]) + (values2D[0][1] * values2D[2][0] * values2D[3][3]) + (values2D[0][3] * values2D[2][1] * values2D[3][0])
				- (values2D[0][0] * values2D[2][1] * values2D[3][3]) - (values2D[0][1] * values2D[2][3] * values2D[3][0]) - (values2D[0][3] * values2D[2][0] * values2D[3][1])));
			new_in_mat[2][2] = (deta * ((values2D[0][0] * values2D[1][1] * values2D[3][3]) + (values2D[0][1] * values2D[1][3] * values2D[3][0]) + (values2D[0][3] * values2D[1][0] * values2D[3][1])
				- (values2D[0][0] * values2D[1][3] * values2D[3][1]) - (values2D[0][1] * values2D[1][0] * values2D[3][3]) - (values2D[0][3] * values2D[1][1] * values2D[3][0])));
			new_in_mat[2][3] = (deta * ((values2D[0][0] * values2D[1][3] * values2D[2][1]) + (values2D[0][1] * values2D[1][0] * values2D[2][3]) + (values2D[0][3] * values2D[1][1] * values2D[2][0])
				- (values2D[0][0] * values2D[1][1] * values2D[2][3]) - (values2D[0][1] * values2D[1][3] * values2D[2][0]) - (values2D[0][3] * values2D[1][0] * values2D[2][1])));

			new_in_mat[3][0] = (deta * ((values2D[1][0] * values2D[2][2] * values2D[3][1]) + (values2D[1][1] * values2D[2][0] * values2D[3][2]) + (values2D[1][2] * values2D[2][1] * values2D[3][0])
				- (values2D[1][0] * values2D[2][1] * values2D[3][2]) - (values2D[1][1] * values2D[2][2] * values2D[3][0]) - (values2D[1][2] * values2D[2][0] * values2D[3][1])));
			new_in_mat[3][1] = (deta * ((values2D[0][0] * values2D[2][1] * values2D[3][2]) + (values2D[0][1] * values2D[2][2] * values2D[3][0]) + (values2D[0][2] * values2D[2][0] * values2D[3][1])
				- (values2D[0][0] * values2D[2][2] * values2D[3][1]) - (values2D[0][1] * values2D[2][0] * values2D[3][2]) - (values2D[0][2] * values2D[2][1] * values2D[3][0])));
			new_in_mat[3][2] = (deta * ((values2D[0][0] * values2D[1][2] * values2D[3][1]) + (values2D[0][1] * values2D[1][0] * values2D[3][2]) + (values2D[0][2] * values2D[1][1] * values2D[3][0])
				- (values2D[0][0] * values2D[1][1] * values2D[3][2]) - (values2D[0][1] * values2D[1][2] * values2D[3][0]) - (values2D[0][2] * values2D[1][0] * values2D[3][1])));
			new_in_mat[3][3] = (deta * ((values2D[0][0] * values2D[1][1] * values2D[2][2]) + (values2D[0][1] * values2D[1][2] * values2D[2][0]) + (values2D[0][2] * values2D[1][0] * values2D[2][1])
				- (values2D[0][0] * values2D[1][2] * values2D[2][1]) - (values2D[0][1] * values2D[1][0] * values2D[2][2]) - (values2D[0][2] * values2D[1][1] * values2D[2][0])));

			return new_in_mat;

		}

		inline matrix4D setFromVector3(vector3D a, vector3D b, vector3D c)
		{
			this->values2D[0][0] = a.Varray[0];
			this->values2D[0][1] = b.Varray[0];
			this->values2D[0][2] = c.Varray[0];

			this->values2D[1][0] = a.Varray[1];
			this->values2D[1][1] = b.Varray[1];
			this->values2D[1][2] = c.Varray[1];

			this->values2D[2][0] = a.Varray[2];
			this->values2D[2][1] = b.Varray[2];
			this->values2D[2][2] = c.Varray[2];
		}

		inline matrix4D quatRotation(vector4D quat)
		{
			matrix4D temp;

			temp[0][0] = 1 - 2 * ((quat[1] * quat[1]) + (quat[2] * quat[2]));
			temp[0][1] = 2 * ((quat[0] * quat[1]) - (quat[2] * quat[3]));
			temp[0][2] = 2 * ((quat[0] * quat[2]) + (quat[1] * quat[3]));
			temp[0][3] = 0;

			temp[1][0] = 2 * ((quat[0] * quat[1]) + (quat[2] * quat[3]));
			temp[1][1] = 1 - 2 * ((quat[0] * quat[0]) + (quat[2] * quat[2]));
			temp[1][2] = 2 * ((quat[1] * quat[2]) - (quat[0] * quat[3]));
			temp[1][3] = 0;

			temp[2][0] = 2 * ((quat[0] * quat[2]) - (quat[1] * quat[3]));
			temp[2][1] = 2 * ((quat[1] * quat[2]) + (quat[0] * quat[3]));
			temp[2][2] = 1 - 2 * ((quat[0] * quat[0]) + (quat[1] * quat[1]));
			temp[2][3] = 0;

			temp[3][0] = 0;
			temp[3][1] = 0;
			temp[3][2] = 0;
			temp[3][3] = 1;


			return temp;

			/*matrix4D mat;

			double qx = quat[0] * quat[0];
			double qy = quat[1] * quat[1];
			double qz = quat[2] * quat[2];
			double qw = quat[3] * quat[3];

			double invs = 1 / (qx + qy + qz + qw);

			mat[0][0] = (qx - qy - qz + qw) * invs;
			mat[1][1] = ((-qx) + qy - qz + qw) * invs;
			mat[2][2] = ((-qx) - qy + qz + qw) * invs;

			double tmp1 = quat[0]*quat[1];
			double tmp2 = quat[2]*quat[3];
			mat[1][0] = 2.0f * (tmp1 + tmp2) * invs;
			mat[0][1] = 2.0f * (tmp1 - tmp2) * invs;

			tmp1 = quat[0]*quat[2];
			tmp2 = quat[1]*quat[3];
			mat[2][0] = 2.0f * (tmp1 - tmp2) * invs;
			mat[0][2] = 2.0f * (tmp1 + tmp2) * invs;
			tmp1 = quat[1]*quat[2];
			tmp2 = quat[0]*quat[3];
			mat[2][1] = 2.0f * (tmp1 + tmp2) * invs;
			mat[1][2] = 2.0f * (tmp1 - tmp2) * invs;
			return mat;*/

		}

		inline matrix4D scaled(vector3D v)
		{
			matrix4D temp = *this;

			temp.values2D[0][0] *= v.x();
			temp.values2D[0][1] *= v.y();
			temp.values2D[0][2] *= v.z();
			temp.values2D[1][0] *= v.x();
			temp.values2D[1][1] *= v.y();
			temp.values2D[1][2] *= v.z();
			temp.values2D[2][0] *= v.x();
			temp.values2D[2][1] *= v.y();
			temp.values2D[2][2] *= v.z();

			return  temp;

		}

		inline void skewSymmetric(vector4D vec)
		{
			this->values2D[0][0] = 0;
			this->values2D[0][1] = -vec.x();
			this->values2D[0][2] = vec.y();
			this->values2D[0][3] = 0;

			this->values2D[1][0] = vec.z();
			this->values2D[1][1] = 0;
			this->values2D[1][2] = -vec.x();
			this->values2D[1][3] = 0;

			this->values2D[2][0] = -vec.y();
			this->values2D[2][1] = vec.x();
			this->values2D[2][2] = 0;
			this->values2D[2][3] = 0;

			this->values2D[3][0] = 0;
			this->values2D[3][1] = 0;
			this->values2D[3][2] = 0;
			this->values2D[3][3] = 0;
		}

		inline matrix4D getRot()
		{
			matrix4D temp = *this;

			temp[3][0] = 0;
			temp[3][1] = 0;
			temp[3][2] = 0;

			return temp;

		}
	};

}
