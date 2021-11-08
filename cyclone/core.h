#pragma once
#include <cmath>
#include "precision.h"

namespace cyclone
{
	class Vector3
	{
	public :
		//x, y, z축 방향 좌표 값
		real x;
		real y;
		real z;
		#pragma region operatorDef
		void operator *=(const real value)
		{
			x *= value;
			y *= value;
			z *= value;
		}
		Vector3 operator *(const real value) const
		{
			return Vector3(x * value, y * value, z * value);
		}

		Vector3 operator /(const real value) const
		{
			return Vector3(x / value, y / value, z / value);
		}

		void operator +=(const Vector3& v)
		{
			x += v.x;
			y += v.y;
			z += v.z;
		}
		Vector3 operator +(const Vector3& v) const
		{
			return Vector3(x + v.x, y + v.y, z + v.z);
		}

		void operator -=(const real value)
		{
			x -= value;
			y -= value;
			z -= value;
		}
		Vector3 operator -(const Vector3& v) const
		{
			return Vector3(x - v.x, y - v.y, z - v.z);
		}

		//DotProduct operator
		real operator *(const Vector3& v) const
		{
			return x * v.x + y * v.y + z * v.z;
		}
		//CrossProduct operator
		void operator %=(const Vector3& v)
		{
			*this = vectorProduct(v);
		}
		Vector3 operator %(const Vector3& v) const
		{
			return Vector3(y * v.z - z * v.y,
				z * v.x - x * v.z,
				x * v.y - y * v.x);
		}
#pragma endregion

	private :
		//4워드 맞춤을 위해 덧붙임
		real pad;

	public :
		Vector3() : x(0), y(0), z(0) {}
		Vector3(const real x, const real y, const real z) : x(x), y(y), z(z) {}

		void clear()
		{
			delete this;
		}

		void invert()
		{
			x -= x;
			y -= y;
			z -= z;
		}

		real magnitude() const
		{
			//추후 수정 필요
			return sqrt(x * x + y * y + z * z);
		}
		real squareMagnitude() const
		{
			return x * x + y * y + z * z;
		}
		void normalize()
		{
			real length = magnitude();
			if (length > 0)
			{
				(*this) *= ((real)1)/length;
			}
		}
		void addScaledVector(const Vector3& vector, real scale)
		{
			x += vector.x * scale;
			y += vector.y * scale;
			z += vector.z * scale;
		}
		//Multiplication of Vector
		Vector3 componentProduct(const Vector3& vector) const
		{
			return Vector3(x * vector.x, y * vector.y, z * vector.z);
		}
		void componentProductUpdate(const Vector3& vector)
		{
			x *= vector.x;
			y *= vector.y;
			z *= vector.z;
		}
		//DotProduct of Vector
		real scalarProduct(const Vector3& vector) const
		{
			return x * vector.x + y * vector.y + z * vector.z;
		}
		//CrossProduct of Vector
		Vector3 vectorProduct(const Vector3& vector) const
		{
			return Vector3(y * vector.z - z * vector.y,
				z * vector.x - x * vector.z,
				x * vector.y - y * vector.x);
		}
	};
}