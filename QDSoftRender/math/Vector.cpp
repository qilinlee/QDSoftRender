#include "Vector.h"
#include <limits>
#include <cmath>
#include "Util.h"

namespace QDSoftRender
{
	const Vector3 Vector3::ZERO = Vector3();
	const Vector3 Vector3::UNIT_X = Vector3(1.f, 0.f, 0.f);
	const Vector3 Vector3::UNIT_Y = Vector3(0.f, 1.f, 0.f);
	const Vector3 Vector3::UNIT_Z = Vector3(0.f, 0.f, 1.f);

	Vector3::Vector3()
		: X(0.f)
		, Y(0.f)
		, Z(0.f)
	{
	}

	Vector3::Vector3(float x, float y, float z)
		: X(x)
		, Y(y)
		, Z(z)
	{

	}

	Vector3& Vector3::operator=(const Vector3& vec)
	{
		X = vec.X;
		Y = vec.Y;
		Z = vec.Z;
		return *this;
	}

	Vector3 Vector3::operator+(const Vector3& vec) const
	{
		return Vector3(X + vec.X, Y + vec.Y, Z + vec.Z);
	}

	Vector3 Vector3::operator-(const Vector3& vec) const
	{
		return Vector3(X - vec.X, Y - vec.Y, Z - vec.Z);
	}

	Vector3 Vector3::operator*(float scalar) const
	{
		return Vector3(X * scalar, Y * scalar, Z*scalar);
	}

	Vector3 Vector3::operator/(float scalar) const
	{
		if (scalar != 0.f)
		{
			float invScalar = 1.f / scalar;
			return Vector3(X *invScalar, Y * invScalar, Z * invScalar);
		}

		return Vector3(
			std::numeric_limits<float>::max(),
			std::numeric_limits<float>::max(),
			std::numeric_limits<float>::max()
			);
	}

	Vector3 Vector3::operator-() const
	{
		return Vector3(-X, -Y, -Z);
	}

	Vector3& Vector3::operator+=(const Vector3& vec)
	{
		X += vec.X;
		Y += vec.Y;
		Z += vec.Z;
		return *this;
	}

	Vector3& Vector3::operator-=(const Vector3& vec)
	{
		X -= vec.X;
		Y -= vec.Y;
		Z -= vec.Z;
		return *this;
	}

	Vector3& Vector3::operator*=(float scalar)
	{
		X *= scalar;
		Y *= scalar;
		Z *= scalar;
		return *this;
	}

	Vector3& Vector3::operator/=(float scalar)
	{
		if (scalar != 0.f)
		{
			float invScalar = 1.f / scalar;
			X /= invScalar;
			Y /= invScalar;
			Z /= invScalar;

		}
		else
		{
			X = std::numeric_limits<float>::max();
			Y = std::numeric_limits<float>::max();
			Z = std::numeric_limits<float>::max();
		}

		return *this;
	}

	float Vector3::Length() const
	{
		return sqrtf((X * X + Y * Y + Z * Z));
	}

	float Vector3::SquaredLength() const
	{
		return (X * X + Y * Y + Z * Z);
	}

	float Vector3::Dot(const Vector3& vec) const
	{
		return (X * vec.X + Y * vec.Y + Z * vec.Z);
	}

	void Vector3::Normalize()
	{
		float length = Length();
		if (length < std::numeric_limits<float>::min())
		{
			X = 0.f;
			Y = 0.f;
			Z = 0.f;
		}
		else
		{
			float invLength = 1.f / length;
			X *= invLength;
			Y *= invLength;
			Z *= invLength;
		}
	}

	Vector3 Vector3::Cross(const Vector3& vec) const
	{
		return Vector3(
			Y * vec.Z - Z * vec.Y,
			Z * vec.X - X * vec.Z,
			X * vec.Y - Y * vec.X
			);
	}

	Vector3 Vector3::UnitCross(const Vector3& vec) const
	{
		Vector3 result(
			Y * vec.Z - Z * vec.Y,
			Z * vec.X - X * vec.Z,
			X * vec.Y - Y * vec.X);

		result.Normalize();
		return result;
	}

	void Vector3::Orthonormalize(Vector3& vec0, Vector3& vec1, Vector3& vec2)
	{
		// If the input vectors are v0, v1, and v2, then the Gram-Schmidt
		// orthonormalization produces vectors u0, u1, and u2 as follows,
		//
		//   u0 = v0/|v0|
		//   u1 = (v1-(u0*v1)u0)/|v1-(u0*v1)u0|
		//   u2 = (v2-(u0*v2)u0-(u1*v2)u1)/|v2-(u0*v2)u0-(u1*v2)u1|
		//
		// where |A| indicates length of vector A and A*B indicates dot
		// product of vectors A and B.

		// Compute u0.
		vec0.Normalize();

		// Compute u1.
		float dot0 = vec0.Dot(vec1);
		vec1 -= dot0*vec0;
		vec1.Normalize();

		// Compute u2.
		float dot1 = vec1.Dot(vec2);
		dot0 = vec0.Dot(vec2);
		vec2 -= dot0 * vec0 + dot1 * vec1;
		vec2.Normalize();
	}

	void Vector3::GenerateOrthonormalBasis(Vector3& vec0, Vector3& vec1, Vector3& vec2)
	{
		vec2.Normalize();
		GenerateComplementBasis(vec0, vec1, vec2);
	}

	void Vector3::GenerateComplementBasis(Vector3& vec0, Vector3& vec1, const Vector3& vec2)
	{
		float invLength = 0.0f;

		if (fabsf(vec2.X) >= fabsf(vec2.Y))
		{
			// vec2.x or vec2.z is the largest magnitude component, swap them
			invLength = 1.0f / sqrtf(vec2.X * vec2.X + vec2.Z * vec2.Z);
			vec0.X = -vec2.Z * invLength;
			vec0.Y = 0.0f;
			vec0.Z = +vec2.X * invLength;
			vec1.X = vec2.Y * vec0.Z;
			vec1.Y = vec2.Z * vec0.X - vec2.X * vec0.Z;
			vec1.Z = -vec2.Y * vec0.X;
		}
		else
		{
			// vec2.y or vec2.z is the largest magnitude component, swap them
			invLength = 1.0f / sqrtf(vec2.Y * vec2.Y + vec2.Z * vec2.Z);
			vec0.X = 0.0f;
			vec0.Y = +vec2.Z * invLength;
			vec0.Z = -vec2.Y * invLength;
			vec1.X = vec2.Y * vec0.Z - vec2.Z * vec0.Y;
			vec1.Y = -vec2.X * vec0.Z;
			vec1.Z = vec2.X * vec0.Y;
		}
	}

	Vector3 Vector3::Lerp(const Vector3 &vec1, const Vector3 &vec2, float t)
	{
		return Vector3(
			Util::Lerp(vec1.X, vec2.X, t),
			Util::Lerp(vec1.Y, vec2.Y, t),
			Util::Lerp(vec1.Z, vec2.Z, t)
			);
	}

	Vector3 operator* (float scalar, const Vector3& vec)
	{
		return vec * scalar;
	}

	//
	//Vector4
	//
	const Vector4 Vector4::ZERO = Vector4();
	const Vector4 Vector4::UNIT_X = Vector4(1.0f, 0.0f, 0.0f, 0.0f);
	const Vector4 Vector4::UNIT_Y = Vector4(0.0f, 1.0f, 0.0f, 0.0f);
	const Vector4 Vector4::UNIT_Z = Vector4(0.0f, 0.0f, 1.0f, 0.0f);
	Vector4::Vector4()
		: X(0.0f)
		, Y(0.0f)
		, Z(0.0f)
		, W(0.0f)
	{

	}

	Vector4::Vector4(float x, float y, float z, float w)
		: X(x)
		, Y(y)
		, Z(z)
		, W(w)
	{

	}

	Vector4& Vector4::operator=(const Vector4& vec)
	{
		X = vec.X;
		Y = vec.Y;
		Z = vec.Z;
		W = vec.W;
		return *this;
	}

	Vector4 Vector4::operator+(const Vector4& vec) const
	{
		return Vector4(X + vec.X, Y + vec.Y, Z + vec.Z, 0.0f);
	}

	Vector4 Vector4::operator-(const Vector4& vec) const
	{
		return Vector4(X - vec.X, Y - vec.Y, Z - vec.Z, 0.0f);
	}

	Vector4 Vector4::operator*(float scalar) const
	{
		return Vector4(X * scalar, Y * scalar, Z * scalar, 0.0f);
	}

	Vector4 Vector4::operator/(float scalar) const
	{
		if (scalar != 0.0f)
		{
			float invScalar = 1.f / scalar;
			return Vector4(X * invScalar, Y * invScalar, Z*invScalar, 0.0f);
		}
		else
		{
			return Vector4(
				std::numeric_limits<float>::max(),
				std::numeric_limits<float>::max(),
				std::numeric_limits<float>::max()
				);
		}
	}

	Vector4 Vector4::operator-() const
	{
		return Vector4(-X, -Y, -Z, 0.0f);
	}

	Vector4& Vector4::operator+=(const Vector4& vec)
	{
		X += vec.X;
		Y += vec.Y;
		Z += vec.Z;
		W = 0.0f;
		return *this;
	}

	Vector4& Vector4::operator-=(const Vector4& vec)
	{
		X -= vec.X;
		Y -= vec.Y;
		Z -= vec.Z;
		W = 0.0f;
		return *this;
	}

	Vector4& Vector4::operator*=(float scalar)
	{
		X *= scalar;
		Y *= scalar;
		Z *= scalar;
		W = 0.0f;
		return *this;
	}

	Vector4& Vector4::operator/=(float scalar)
	{
		if (scalar != 0.0f)
		{
			float invScalar = 1.f / scalar;
			X *= invScalar;
			Y *= invScalar;
			Z *= invScalar;
			W = 0.0f;
		}
		else
		{
			X = std::numeric_limits<float>::max();
			Y = std::numeric_limits<float>::max();
			Z = std::numeric_limits<float>::max();
			W = 0.0f;
		}
		return *this;
	}


	float Vector4::Length() const
	{
		return sqrtf((X * X + Y * Y + Z * Z));
	}

	float Vector4::SquaredLength() const
	{
		return (X * X + Y * Y + Z * Z);
	}

	float Vector4::Dot(const Vector4& vec) const
	{
		return (X * vec.X + Y * vec.Y + Z * vec.Z);
	}

	void Vector4::Normalize()
	{
		float length = Length();
		if (length < std::numeric_limits<float>::min())
		{
			X = 0.f;
			Y = 0.f;
			Z = 0.f;
		}
		else
		{
			float invLength = 1.f / length;
			X *= invLength;
			Y *= invLength;
			Z *= invLength;
		}
	}

	Vector4 Vector4::Cross(const Vector4& vec) const
	{
		return Vector4(
			Y * vec.Z - Z * vec.Y,
			Z * vec.X - X * vec.Z,
			X * vec.Y - Y * vec.X
			);
	}

	Vector4 Vector4::UnitCross(const Vector4& vec) const
	{
		Vector4 result(
			Y * vec.Z - Z * vec.Y,
			Z * vec.X - X * vec.Z,
			X * vec.Y - Y * vec.X
			);

		result.Normalize();
		return result;
	}

}