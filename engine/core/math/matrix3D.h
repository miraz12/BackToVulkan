#pragma once
#include <iostream>
#include "vector3D.h"

#define PI 3.14159265f

namespace Math
{
	class matrix3D
	{
	public:

		//2D array
		float values2D[3][3];

		matrix3D(void)
		{
			this->values2D[0][0] = 1;
			this->values2D[0][1] = 0;
			this->values2D[0][2] = 0;

			this->values2D[1][0] = 0;
			this->values2D[1][1] = 1;
			this->values2D[1][2] = 0;

			this->values2D[2][0] = 0;
			this->values2D[2][1] = 0;
			this->values2D[2][2] = 1;
		}

		~matrix3D() = default;

		inline matrix3D rot_x(float r)
		{
			matrix3D x;
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

			return ((*this) * x);
		}
		inline matrix3D rot_y(float r)
		{
			matrix3D y;
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

			return ((*this) * y);
		}
		inline matrix3D rot_z(float r)
		{
			matrix3D z;
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

			return ((*this) * z);
		}
		inline matrix3D rot_v(vector3D v, float r)
		{
			matrix3D temp;

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



		inline matrix3D operator*(const matrix3D& m)
		{
			matrix3D temp(*this);
			matrix3D m2;

			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					m2.values2D[i][j] = 0;

					for (int k = 0; k < 3; k++)
					{
						m2.values2D[i][j] += temp.values2D[i][k] * m.values2D[k][j];
					}
				}
			}
			return m2;
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
		inline friend std::ostream& operator<<(std::ostream& os, matrix3D& m)
		{
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					os << m.values2D[i][j] << "\t";
				}
				os << std::endl;
			}
			return os;
		}
		inline void setValues(float v)
		{
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					values2D[i][j] = v;
				}
			}
		}
		inline matrix3D operator~()
		{
			matrix3D temp;

			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					temp.values2D[j][i] = values2D[i][j];
				}
			}

			return temp;
		}

		float* operator[](int n)
		{

			return this->values2D[n];

		}
		inline float det(void)
		{
			float a = this->values2D[0][0] * (this->values2D[1][1] * this->values2D[2][2] - this->values2D[2][1] * this->values2D[1][2]);
			float b = this->values2D[0][1] * (this->values2D[1][0] * this->values2D[2][2] - this->values2D[2][0] * this->values2D[1][2]);
			float c = this->values2D[0][2] * (this->values2D[1][0] * this->values2D[2][1] - this->values2D[2][0] * this->values2D[1][1]);

			return a - b + c;
		}
		inline matrix3D adj(void)
		{
			matrix3D temp;

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
		inline matrix3D inv()
		{
			matrix3D temp;
			matrix3D ajd = this->adj();

			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{

					temp.values2D[i][j] = (ajd.values2D[i][j] / this->det());
				}

			}
			return temp;
		}

	};
}

