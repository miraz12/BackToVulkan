#pragma once
#include <iostream>
#include <cmath>

namespace Math
{

	class vector2D
	{
	public:
		float Varray[2];



		vector2D(void)
		{
			Varray[0] = 0;
			Varray[1] = 0;
		}

		vector2D(float v)
		{
			Varray[0] = v;
			Varray[1] = v;
		}

		vector2D(float x, float y)
		{
			Varray[0] = x;
			Varray[1] = y;
		}

		~vector2D(void)
		{

		}
		//Varray to float*. used when writing unifrom arrays.
		operator const float* () { return Varray; }

		float& operator[](int n)
		{

			return this->Varray[n];

		}

		vector2D operator-(const vector2D& m)
		{
			vector2D temp = *this;
			temp.Varray[0] -= m.Varray[0];
			temp.Varray[1] -= m.Varray[1];
			return temp;
		}


		vector2D operator*(float m)
		{
			vector2D temp = *this;

			for (int i = 0; i < 2; i++)
			{
				temp.Varray[i] *= m;
			}
			return temp;
		}

		vector2D operator+(float m)
		{
			vector2D temp = *this;

			for (int i = 0; i < 2; i++)
			{
				temp.Varray[i] += m;
			}
			return temp;
		}

		vector2D operator+(const vector2D& m)
		{

			vector2D temp = *this;

			for (int i = 0; i < 2; i++)
			{
				temp.Varray[i] += m.Varray[i];
			}
			return temp;
		}

		float x()
		{
			return this->Varray[0];
		}

		float y()
		{
			return this->Varray[1];
		}

	};
}
