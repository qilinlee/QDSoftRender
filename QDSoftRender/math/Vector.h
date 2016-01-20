#pragma once

#ifndef __VECTOR_H__
#define __VECTOR_H__
//#include <stdexcept>

namespace QDSoftRender
{
	class Vector3
	{
	public:
		float X;
		float Y;
		float Z;
	public:
		static const Vector3 ZERO;    // (0,0,0)
		static const Vector3 UNIT_X;  // (1,0,0)
		static const Vector3 UNIT_Y;  // (0,1,0)
		static const Vector3 UNIT_Z;  // (0,0,1)

		Vector3();
		Vector3(float x, float y, float z);

		// Assignment.
		Vector3& operator= (const Vector3& vec);

		// Arithmetic operations.
		Vector3 operator+ (const Vector3& vec) const;
		Vector3 operator- (const Vector3& vec) const;
		Vector3 operator* (float scalar) const;
		Vector3 operator/ (float scalar) const;
		Vector3 operator- () const;

		friend Vector3 operator* (float scalar, const Vector3& vec);

		// Arithmetic updates.
		Vector3& operator+= (const Vector3& vec);
		Vector3& operator-= (const Vector3& vec);
		Vector3& operator*= (float scalar);
		Vector3& operator/= (float scalar);

		// Vector operations.
		float Length() const;
		float SquaredLength() const;
		float Dot(const Vector3& vec) const;
		void Normalize();
		Vector3 Cross(const Vector3& vec) const;
		Vector3 UnitCross(const Vector3& vec) const;

		// Inputs must be initialized nonzero vectors.
		static void Orthonormalize(Vector3& vec0, Vector3& vec1, Vector3& vec2);

		// Input vec2 must be a nonzero vector. The output is an orthonormal
		// basis {vec0,vec1,vec2}.  The input vec2 is normalized by this function.
		// If you know that vec2 is already unit length, use the function
		// GenerateComplementBasis to compute vec0 and vec1.
		static void GenerateOrthonormalBasis(Vector3& vec0, Vector3& vec1,
			Vector3& vec2);

		// Input vec0 must be a unit-length vector.  The output vectors
		// {vec0,vec1} are unit length and mutually perpendicular, and
		// {vec0,vec1,vec2} is an orthonormal basis.
		static void GenerateComplementBasis(Vector3& vec0, Vector3& vec1,
			const Vector3& vec2);

		static Vector3 Lerp(const Vector3 &vec1, const Vector3 &vec2, float t);

	};

	class Vector4
	{
	public:
		float X;
		float Y;
		float Z;
		float W;
	public:
		static const Vector4 ZERO;    // (0,0,0,0)
		static const Vector4 UNIT_X;  // (1,0,0,0)
		static const Vector4 UNIT_Y;  // (0,1,0,0)
		static const Vector4 UNIT_Z;  // (0,0,1,0)

		Vector4();
		Vector4(float x, float y, float z, float w = 0.0f);

		// Assignment.
		Vector4& operator= (const Vector4& vec);

		// Arithmetic operations.
		Vector4 operator+ (const Vector4& vec) const;
		Vector4 operator- (const Vector4& vec) const;
		Vector4 operator* (float scalar) const;
		Vector4 operator/ (float scalar) const;
		Vector4 operator- () const;

		friend Vector4 operator* (float scalar, const Vector4& vec);

		// Arithmetic updates.
		Vector4& operator+= (const Vector4& vec);
		Vector4& operator-= (const Vector4& vec);
		Vector4& operator*= (float scalar);
		Vector4& operator/= (float scalar);

		// Vector operations.
		float Length() const;
		float SquaredLength() const;
		float Dot(const Vector4& vec) const;
		void Normalize();
		Vector4 Cross(const Vector4& vec) const;
		Vector4 UnitCross(const Vector4& vec) const;
	};
}
#endif