#pragma once
#include <iostream>
#include <cmath>

namespace Math
{
	class quaternion
	{
	public:
		float Varray[4];

		quaternion()
		{
			Varray[0] = 0;
			Varray[1] = 0;
			Varray[2] = 0;
			Varray[3] = 1;
		}

		quaternion(float v)
		{
			Varray[0] = v;
			Varray[1] = v;
			Varray[2] = v;
			Varray[3] = 1;
		}

		quaternion(double v)
		{
			Varray[0] = static_cast<float>(v);
			Varray[1] = static_cast<float>(v);
			Varray[2] = static_cast<float>(v);
			Varray[3] = 1;
		}

		quaternion(float x, float y, float z, float w)
		{
			Varray[0] = x;
			Varray[1] = y;
			Varray[2] = z;
			Varray[3] = w;
		}
		quaternion(double x, double y, double z, double w)
		{
			Varray[0] = static_cast<float>(x);
			Varray[1] = static_cast<float>(y);
			Varray[2] = static_cast<float>(z);
			Varray[3] = static_cast<float>(w);
		}

		~quaternion(void) = default;

		//Varray to float*. used when writing unifrom arrays.
		operator const float* () { return Varray; }

		float& operator[](int n)
		{
			return this->Varray[n];
		}
		quaternion operator+(const quaternion& m)
		{
			m;
		}
		quaternion operator-(const quaternion& m)
		{
			m;
		}
		quaternion operator*(float m)
		{
			m;
		}
		
		void setValues(float v)
		{
			for (int i = 0; i < 4; i++)
			{

				this->Varray[i] = v;

			}
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
