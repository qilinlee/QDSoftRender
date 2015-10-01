#pragma once
#ifndef __MATRIX_H__
#define __MATRIX_H__
namespace QDSoftRender
{
	class Vector3;
	class Vector4;

	class Matrix
	{
	public:
		Matrix();
		Matrix(const float mat[16]);
		// Input mrc is in row r, column c.
		Matrix(
			float m00, float m01, float m02, float m03,
			float m10, float m11, float m12, float m13,
			float m20, float m21, float m22, float m23,
			float m30, float m31, float m32, float m33);
		Matrix(const Matrix &mat);
		Matrix& operator=(const Matrix &mat);

		inline const float* operator[] (int row) const;
		inline float* operator[] (int row);
		inline const float& operator() (int row, int column) const;
		inline float& operator() (int row, int column);

		// Comparison (for use by STL containers).
		bool operator== (const Matrix& mat) const;
		bool operator!= (const Matrix& mat) const;
		bool operator<  (const Matrix& mat) const;
		bool operator<= (const Matrix& mat) const;
		bool operator>  (const Matrix& mat) const;
		bool operator>= (const Matrix& mat) const;

		// Arithmetic operations.
		Matrix operator+ (const Matrix& mat) const;
		Matrix operator- (const Matrix& mat) const;
		Matrix operator* (float scalar) const;
		Matrix operator/ (float scalar) const;
		Matrix operator- () const;

		friend Matrix operator* (float scalar, const Matrix& mat);

		// Arithmetic updates.
		Matrix& operator+= (const Matrix& mat);
		Matrix& operator-= (const Matrix& mat);
		Matrix& operator*= (float scalar);
		Matrix& operator/= (float scalar);

		// Operations on matrices.
		void MakeZero();  // Z
		void MakeIdentity();  // I
		void MakeDiagonal(float m00, float m11, float m22);  // D
		void MakeRotation(const Vector4& axis, float angle);  // R
		void MakeScale(float scalarX, float scalarY, float scalarZ); // S
		void MakeTranslate(float x, float y, float z);
		void MakeTranslate(const Vector4 &vec);
		void MakeTranslate(const Vector3 &vec);
		Matrix Transpose() const;  // M^T
		Matrix Inverse(const float epsilon = 0.0f) const;  // M^{-1}
		Matrix Adjoint() const;  // M^{adj}
		float Determinant() const;  // det(M)
		Matrix operator* (const Matrix& mat) const;  // M*mat
		Matrix TransposeTimes(const Matrix& mat) const;  // M^T*mat
		Matrix TimesTranspose(const Matrix& mat) const;  // M*mat^T
		Matrix TransposeTimesTranspose(const Matrix& mat) const;  // M^T*mat^T
		Matrix TimesDiagonal(const Vector4& diag) const;  // M*D
		Matrix DiagonalTimes(const Vector4& diag) const;  // D*M
		void Orthonormalize(); // applies to 3x3 upper-left block of M

	public:
		static const Matrix ZERO;
		static const Matrix IDENTITY;
	private:
		// The matrix is stored in row-major order.
		float m_Entry[16];
	};

#include "Matrix.inl"

}
#endif