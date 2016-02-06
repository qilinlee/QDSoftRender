#pragma once

#ifndef __VECTOR_H__
#define __VECTOR_H__

namespace QDSoftRender
{
	class Vector2
	{
	public:
		float X;
		float Y;
	public:
		static const Vector2 ZERO;    // (0,0)
		static const Vector2 UNIT_X;  // (1,0)
		static const Vector2 UNIT_Y;  // (0,1)

		Vector2();
		Vector2(float x, float y);

		// Assignment.
		Vector2& operator= (const Vector2& vec);

		// Arithmetic operations.
		Vector2 operator+ (const Vector2& vec) const;
		Vector2 operator- (const Vector2& vec) const;
		Vector2 operator* (float scalar) const;
		Vector2 operator/ (float scalar) const;
		Vector2 operator- () const;

		friend Vector2 operator* (float scalar, const Vector2& vec);

		// Arithmetic updates.
		Vector2& operator+= (const Vector2& vec);
		Vector2& operator-= (const Vector2& vec);
		Vector2& operator*= (float scalar);
		Vector2& operator/= (float scalar);

		bool operator==(const Vector2& vec);
		bool operator!=(const Vector2& vec);

		// Vector operations.
		float Length() const;
		float SquaredLength() const;
		float Dot(const Vector2& vec) const;
		void Normalize();
		Vector2 UnitCross(const Vector2& vec) const;

		static Vector2 Lerp(const Vector2 &vec1, const Vector2 &vec2, float t);

	};


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

		bool operator==(const Vector3& vec);
		bool operator!=(const Vector3& vec);

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