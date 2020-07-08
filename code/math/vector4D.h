#pragma once
#include <iostream>
#include <cmath>
#include "vector3D.h"

namespace Math
{
	class vector4D
	{
	public:
		float Varray[4];

		vector4D(void)
		{
			Varray[0] = 0;
			Varray[1] = 0;
			Varray[2] = 0;
			Varray[3] = 1;
		}

		vector4D(float x, float y, float z, float w)
		{
			Varray[0] = x;
			Varray[1] = y;
			Varray[2] = z;
			Varray[3] = w;
		}
		vector4D(vector3D v)
		{
			Varray[0] = v[0];
			Varray[1] = v[1];
			Varray[2] = v[2];
			Varray[3] = 1.0f;
		}

		~vector4D(void) = default;

		//Varray to float*. used when writing unifrom arrays.
		operator const float* () { return Varray; }

		float& operator[](int n)
		{
			return this->Varray[n];
		}
		vector4D operator+(const vector4D& m)
		{
			vector4D temp = *this;

			temp.Varray[0] += m.Varray[0];
			temp.Varray[1] += m.Varray[1];
			temp.Varray[2] += m.Varray[2];
			//temp.Varray[3] += m.Varray[3];

			return temp;
		}
		vector4D operator-(const vector4D& m)
		{
			vector4D temp = *this;

			for (int i = 0; i < 4; i++)
			{
				temp.Varray[i] -= m.Varray[i];
			}
			return temp;
		}
		vector4D operator*(float m)
		{
			vector4D temp = *this;

			for (int i = 0; i < 4; i++)
			{
				temp.Varray[i] *= m;
			}
			return temp;
		}
		float dott(vector4D m)
		{
			float p = 0;
			for (int i = 0; i < this->length(); i++)
			{
				p += this->Varray[i] * m.Varray[i];
			}
			return p;
		}
		vector4D cross(vector4D m)
		{
			vector4D v;

			v.Varray[0] = (this->Varray[1] * m.Varray[2]) - (this->Varray[2] * m.Varray[1]);
			v.Varray[1] = (this->Varray[2] * m.Varray[0]) - (this->Varray[0] * m.Varray[2]);
			v.Varray[2] = (this->Varray[0] * m.Varray[1]) - (this->Varray[1] * m.Varray[0]);

			return v;
		}
		friend std::ostream& operator<<(std::ostream& os, vector4D m)
		{
			for (int i = 0; i < 3; i++)
			{
				os << m.Varray[i] << "\t";


				os << std::endl;
			}
			return os;
		}
		void setValues(float v)
		{
			for (int i = 0; i < 4; i++)
			{

				this->Varray[i] = v;

			}
		}
		float length(void)
		{
			float l = 0.0f;

			for (int i = 0; i < 4; i++)
			{
				l += powf(this->Varray[i], 2.0f);
			}
			return sqrtf(l);
		}
		float lengthSqr(void)
		{
			float l = 0.0f;

			for (int i = 0; i < 4; i++)
			{
				l += powf(this->Varray[i], 2.0f);
			}
			return (l);
		}
		void normalize(void)
		{
			float l = this->length();

			for (int i = 0; i < 4; i++)
			{
				this->Varray[i] = (this->Varray[i] / l);
			}
		}

		inline void addScaledVector(vector4D v, float scale)
		{
			this->Varray[0] += v[0] * scale;
			this->Varray[1] += v[1] * scale;
			this->Varray[2] += v[2] * scale;
			this->Varray[3] += v[3] * scale;
		}

		inline void addScaledVectorQuat(vector4D v, float scale)
		{
			vector4D q = vector4D(v.x() * scale, v.y() * scale, v.z() * scale, 0.f);

			vector4D q2 = *this;
			float wo = q.w() * w() - q.x() * x() -
				q.y() * y() - q.z() * z();
			float xo = q.w() * x() + q.x() * w() +
				q.y() * z() - q.z() * y();
			float yo = q.w() * y() + q.y() * w() +
				q.z() * x() - q.x() * z();
			float zo = q.w() * z() + q.z() * w() +
				q.x() * y() - q.y() * x();
			q = vector4D(xo, yo, zo, wo);

			this->Varray[0] += q.x() * 0.5f;
			this->Varray[1] += q.y() * 0.5f;
			this->Varray[2] += q.z() * 0.5f;
			this->Varray[3] += q.w() * 0.5f;
		}

		inline float x()
		{
			return this->Varray[0];
		}

		inline float y()
		{
			return this->Varray[1];
		}

		inline float z()
		{
			return this->Varray[2];
		}

		inline float w()
		{
			return this->Varray[3];
		}
	};
}
