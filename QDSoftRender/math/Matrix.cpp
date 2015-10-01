#include "Matrix.h"
#include <memory.h>
#include <limits>
#include <cmath>
#include "Vector.h"

namespace QDSoftRender
{
	const Matrix Matrix::ZERO = Matrix(
		0.0f, 0.0f, 0.0f, 0.0f, 
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f
		);

	const Matrix Matrix::IDENTITY = Matrix(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
		);

	Matrix::Matrix()
	{
		memset(m_Entry, 0, sizeof(float) * 16);
	}

	Matrix::Matrix(const float mat[16])
	{
		memcpy(m_Entry, mat, sizeof(float) * 16);
	}

	Matrix& Matrix::operator=(const Matrix &mat)
	{
		for (int i = 0; i < 16; ++i)
			m_Entry[i] = mat.m_Entry[i];
		return *this;
	}

	bool Matrix::operator==(const Matrix& mat) const
	{
		return memcmp(m_Entry, mat.m_Entry, sizeof(float) * 16) == 0;
	}

	bool Matrix::operator!= (const Matrix& mat) const
	{
		return memcmp(m_Entry, mat.m_Entry, sizeof(float) * 16) != 0;
	}

	bool Matrix::operator<  (const Matrix& mat) const
	{
		return memcmp(m_Entry, mat.m_Entry, sizeof(float) * 16) < 0;
	}

	bool Matrix::operator<= (const Matrix& mat) const
	{
		return memcmp(m_Entry, mat.m_Entry, sizeof(float) * 16) <= 0;
	}

	bool Matrix::operator>  (const Matrix& mat) const
	{
		return memcmp(m_Entry, mat.m_Entry, sizeof(float) * 16) > 0;
	}

	bool Matrix::operator>= (const Matrix& mat) const
	{
		return memcmp(m_Entry, mat.m_Entry, sizeof(float) * 16) >= 0;
	}

	Matrix Matrix::operator+(const Matrix& mat) const
	{
		Matrix result;
		for (int i = 0; i < 16; ++i)
			result.m_Entry[i] = m_Entry[i] + mat.m_Entry[i];
		return result;
	}

	Matrix Matrix::operator-(const Matrix& mat) const
	{
		Matrix result;
		for (int i = 0; i < 16; ++i)
			result.m_Entry[i] = m_Entry[i] - mat.m_Entry[i];
		return result;
	}

	Matrix Matrix::operator*(float scalar) const
	{
		Matrix result;
		for (int i = 0; i < 16; ++i)
			result.m_Entry[i] = m_Entry[i] * scalar;
		return result;
	}

	Matrix Matrix::operator*(const Matrix& mat) const
	{
		return Matrix(
			m_Entry[ 0] * mat.m_Entry[ 0] +
			m_Entry[ 1] * mat.m_Entry[ 4] +
			m_Entry[ 2] * mat.m_Entry[ 8] +
			m_Entry[ 3] * mat.m_Entry[12],

			m_Entry[ 0] * mat.m_Entry[ 1] +
			m_Entry[ 1] * mat.m_Entry[ 5] +
			m_Entry[ 2] * mat.m_Entry[ 9] +
			m_Entry[ 3] * mat.m_Entry[13],

			m_Entry[ 0] * mat.m_Entry[ 2] +
			m_Entry[ 1] * mat.m_Entry[ 6] +
			m_Entry[ 2] * mat.m_Entry[10] +
			m_Entry[ 3] * mat.m_Entry[14],

			m_Entry[ 0] * mat.m_Entry[ 3] +
			m_Entry[ 1] * mat.m_Entry[ 7] +
			m_Entry[ 2] * mat.m_Entry[11] +
			m_Entry[ 3] * mat.m_Entry[15],

			m_Entry[ 4] * mat.m_Entry[ 0] +
			m_Entry[ 5] * mat.m_Entry[ 4] +
			m_Entry[ 6] * mat.m_Entry[ 8] +
			m_Entry[ 7] * mat.m_Entry[12],

			m_Entry[ 4] * mat.m_Entry[ 1] +
			m_Entry[ 5] * mat.m_Entry[ 5] +
			m_Entry[ 6] * mat.m_Entry[ 9] +
			m_Entry[ 7] * mat.m_Entry[13],

			m_Entry[ 4] * mat.m_Entry[ 2] +
			m_Entry[ 5] * mat.m_Entry[ 6] +
			m_Entry[ 6] * mat.m_Entry[10] +
			m_Entry[ 7] * mat.m_Entry[14],

			m_Entry[ 4] * mat.m_Entry[ 3] +
			m_Entry[ 5] * mat.m_Entry[ 7] +
			m_Entry[ 6] * mat.m_Entry[11] +
			m_Entry[ 7] * mat.m_Entry[15],

			m_Entry[ 8] * mat.m_Entry[ 0] +
			m_Entry[ 9] * mat.m_Entry[ 4] +
			m_Entry[10] * mat.m_Entry[ 8] +
			m_Entry[11] * mat.m_Entry[12],

			m_Entry[ 8] * mat.m_Entry[ 1] +
			m_Entry[ 9] * mat.m_Entry[ 5] +
			m_Entry[10] * mat.m_Entry[ 9] +
			m_Entry[11] * mat.m_Entry[13],

			m_Entry[ 8] * mat.m_Entry[ 2] +
			m_Entry[ 9] * mat.m_Entry[ 6] +
			m_Entry[10] * mat.m_Entry[10] +
			m_Entry[11] * mat.m_Entry[14],

			m_Entry[ 8] * mat.m_Entry[ 3] +
			m_Entry[ 9] * mat.m_Entry[ 7] +
			m_Entry[10] * mat.m_Entry[11] +
			m_Entry[11] * mat.m_Entry[15],

			m_Entry[12] * mat.m_Entry[ 0] +
			m_Entry[13] * mat.m_Entry[ 4] +
			m_Entry[14] * mat.m_Entry[ 8] +
			m_Entry[15] * mat.m_Entry[12],

			m_Entry[12] * mat.m_Entry[ 1] +
			m_Entry[13] * mat.m_Entry[ 5] +
			m_Entry[14] * mat.m_Entry[ 9] +
			m_Entry[15] * mat.m_Entry[13],

			m_Entry[12] * mat.m_Entry[ 2] +
			m_Entry[13] * mat.m_Entry[ 6] +
			m_Entry[14] * mat.m_Entry[10] +
			m_Entry[15] * mat.m_Entry[14],

			m_Entry[12] * mat.m_Entry[ 3] +
			m_Entry[13] * mat.m_Entry[ 7] +
			m_Entry[14] * mat.m_Entry[11] +
			m_Entry[15] * mat.m_Entry[15]);
	}

	Matrix Matrix::operator/(float scalar) const
	{
		Matrix result;
		if (scalar != 0.0f)
		{
			float invScalar = 1.0f / scalar;
			for (int i = 0; i < 16; ++i)
				result.m_Entry[i] = m_Entry[i] * invScalar;
		}
		else
		{
			for (int i = 0; i < 16; ++i)
				result.m_Entry[i] = std::numeric_limits<float>::max();
		}
		return result;
	}

	Matrix Matrix::operator-() const
	{
		Matrix result;
		for (int i = 0; i < 16; ++i)
			result.m_Entry[i] = -m_Entry[i];
		return result;
	}

	Matrix operator* (float scalar, const Matrix& mat)
	{
		return mat * scalar;
	}

	Matrix& Matrix::operator+=(const Matrix& mat)
	{
		for (int i = 0; i < 16; ++i)
			m_Entry[i] += mat.m_Entry[i];

		return *this;
	}

	Matrix& Matrix::operator-=(const Matrix& mat)
	{
		for (int i = 0; i < 16; ++i)
			m_Entry[i] -= mat.m_Entry[i];

		return *this;
	}

	Matrix& Matrix::operator*=(float scalar)
	{
		for (int i = 0; i < 16; ++i)
			m_Entry[i] *= scalar;

		return *this;
	}

	Matrix& Matrix::operator/=(float scalar)
	{
		if (scalar != 0.0f)
		{
			float invScalar = 1.0f / scalar;
			for (int i = 0; i < 16; ++i)
				m_Entry[i] *= invScalar;
		}
		else
		{
			for (int i = 0; i < 16; ++i)
				m_Entry[i] = std::numeric_limits<float>::max();
		}
		return *this;
	}

	void Matrix::MakeZero()
	{
		m_Entry[ 0] = 0.0f; m_Entry[ 1] = 0.0f; m_Entry[ 2] = 0.0f; m_Entry[ 3] = 0.0f;
		m_Entry[ 4] = 0.0f; m_Entry[ 5] = 0.0f; m_Entry[ 6] = 0.0f; m_Entry[ 7] = 0.0f;
		m_Entry[ 8] = 0.0f; m_Entry[ 9] = 0.0f; m_Entry[10] = 0.0f; m_Entry[11] = 0.0f;
		m_Entry[12] = 0.0f; m_Entry[13] = 0.0f; m_Entry[14] = 0.0f; m_Entry[15] = 0.0f;
	}

	void Matrix::MakeIdentity()
	{
		m_Entry[ 0] = 1.0f;  m_Entry[ 1] = 0.0f;  m_Entry[ 2] = 0.0f;  m_Entry[ 3] = 0.0f;
		m_Entry[ 4] = 0.0f;  m_Entry[ 5] = 1.0f;  m_Entry[ 6] = 0.0f;  m_Entry[ 7] = 0.0f;
		m_Entry[ 8] = 0.0f;  m_Entry[ 9] = 0.0f;  m_Entry[10] = 1.0f;  m_Entry[11] = 0.0f;
		m_Entry[12] = 0.0f;  m_Entry[13] = 0.0f;  m_Entry[14] = 0.0f;  m_Entry[15] = 1.0f;
	}

	void Matrix::MakeDiagonal(float m00, float m11, float m22)
	{
		m_Entry[ 0] = m00;   m_Entry[ 1] = 0.0f;  m_Entry[ 2] = 0.0f;  m_Entry[ 3] = 0.0f;
		m_Entry[ 4] = 0.0f;  m_Entry[ 5] = m11;   m_Entry[ 6] = 0.0f;  m_Entry[ 7] = 0.0f;
		m_Entry[ 8] = 0.0f;  m_Entry[ 9] = 0.0f;  m_Entry[10] = m22;   m_Entry[11] = 0.0f;
		m_Entry[12] = 0.0f;  m_Entry[13] = 0.0f;  m_Entry[14] = 0.0f;  m_Entry[15] = 1.0f;
	}

	void Matrix::MakeRotation(const Vector4& axis, float angle)
	{
		float cs = cosf(angle);
		float sn = sinf(angle);
		float oneMinusCos = 1.0f - cs;
		float x2 = axis.X * axis.X;
		float y2 = axis.Y * axis.Y;
		float z2 = axis.Z * axis.Z;
		float xym = axis.X * axis.Y * oneMinusCos;
		float xzm = axis.X * axis.Z * oneMinusCos;
		float yzm = axis.Y * axis.Z * oneMinusCos;
		float xSin = axis.X * sn;
		float ySin = axis.Y * sn;
		float zSin = axis.Z * sn;

		m_Entry[0] = x2*oneMinusCos + cs;
		m_Entry[1] = xym - zSin;
		m_Entry[2] = xzm + ySin;
		m_Entry[3] = 0.0f;
		m_Entry[4] = xym + zSin;
		m_Entry[5] = y2*oneMinusCos + cs;
		m_Entry[6] = yzm - xSin;
		m_Entry[7] = 0.0f;
		m_Entry[8] = xzm - ySin;
		m_Entry[9] = yzm + xSin;
		m_Entry[10] = z2*oneMinusCos + cs;
		m_Entry[11] = 0.0f;
		m_Entry[12] = 0.0f;
		m_Entry[13] = 0.0f;
		m_Entry[14] = 0.0f;
		m_Entry[15] = 1.0f;
	}

	void Matrix::MakeScale(float scalarX, float scalarY, float scalarZ)
	{
		m_Entry[ 0] = scalarX;
		m_Entry[ 5] = scalarY;
		m_Entry[10] = scalarZ;
	}

	void Matrix::MakeTranslate(float x, float y, float z)
	{
		m_Entry[12] = x;
		m_Entry[13] = y;
		m_Entry[14] = z;
	}

	void Matrix::MakeTranslate(const Vector4 &vec)
	{
		m_Entry[12] = vec.X;
		m_Entry[13] = vec.Y;
		m_Entry[14] = vec.Z;
	}

	void Matrix::MakeTranslate(const Vector3 &vec)
	{
		m_Entry[12] = vec.X;
		m_Entry[13] = vec.Y;
		m_Entry[14] = vec.Z;
	}

	Matrix Matrix::Transpose() const
	{
		Matrix result;
		result.m_Entry[ 0] = m_Entry[0];
		result.m_Entry[ 1] = m_Entry[4];
		result.m_Entry[ 2] = m_Entry[8];
		result.m_Entry[ 3] = m_Entry[12];

		result.m_Entry[ 4] = m_Entry[1];
		result.m_Entry[ 5] = m_Entry[5];
		result.m_Entry[ 6] = m_Entry[9];
		result.m_Entry[ 7] = m_Entry[13];

		result.m_Entry[ 8] = m_Entry[2];
		result.m_Entry[ 9] = m_Entry[6];
		result.m_Entry[10] = m_Entry[10];
		result.m_Entry[11] = m_Entry[14];

		result.m_Entry[12] = m_Entry[3];
		result.m_Entry[13] = m_Entry[7];
		result.m_Entry[14] = m_Entry[11];
		result.m_Entry[15] = m_Entry[15];
		return result;
	}

	Matrix Matrix::Inverse(const float epsilon /*= 0.0f*/) const
	{
		float a0 = m_Entry[ 0] * m_Entry[ 5] - m_Entry[ 1] * m_Entry[ 4];
		float a1 = m_Entry[ 0] * m_Entry[ 6] - m_Entry[ 2] * m_Entry[ 4];
		float a2 = m_Entry[ 0] * m_Entry[ 7] - m_Entry[ 3] * m_Entry[ 4];
		float a3 = m_Entry[ 1] * m_Entry[ 6] - m_Entry[ 2] * m_Entry[ 5];
		float a4 = m_Entry[ 1] * m_Entry[ 7] - m_Entry[ 3] * m_Entry[ 5];
		float a5 = m_Entry[ 2] * m_Entry[ 7] - m_Entry[ 3] * m_Entry[ 6];
		float b0 = m_Entry[ 8] * m_Entry[13] - m_Entry[ 9] * m_Entry[12];
		float b1 = m_Entry[ 8] * m_Entry[14] - m_Entry[10] * m_Entry[12];
		float b2 = m_Entry[ 8] * m_Entry[15] - m_Entry[11] * m_Entry[12];
		float b3 = m_Entry[ 9] * m_Entry[14] - m_Entry[10] * m_Entry[13];
		float b4 = m_Entry[ 9] * m_Entry[15] - m_Entry[11] * m_Entry[13];
		float b5 = m_Entry[10] * m_Entry[15] - m_Entry[11] * m_Entry[14];

		float det = a0*b5 - a1*b4 + a2*b3 + a3*b2 - a4*b1 + a5*b0;
		if (fabsf(det) <= epsilon)
		{
			return ZERO;
		}

		Matrix inverse;
		inverse.m_Entry[ 0] = +m_Entry[ 5] * b5 - m_Entry[ 6] * b4 + m_Entry[ 7] * b3;
		inverse.m_Entry[ 4] = -m_Entry[ 4] * b5 + m_Entry[ 6] * b2 - m_Entry[ 7] * b1;
		inverse.m_Entry[ 8] = +m_Entry[ 4] * b4 - m_Entry[ 5] * b2 + m_Entry[ 7] * b0;
		inverse.m_Entry[12] = -m_Entry[ 4] * b3 + m_Entry[ 5] * b1 - m_Entry[ 6] * b0;
		inverse.m_Entry[ 1] = -m_Entry[ 1] * b5 + m_Entry[ 2] * b4 - m_Entry[ 3] * b3;
		inverse.m_Entry[ 5] = +m_Entry[ 0] * b5 - m_Entry[ 2] * b2 + m_Entry[ 3] * b1;
		inverse.m_Entry[ 9] = -m_Entry[ 0] * b4 + m_Entry[ 1] * b2 - m_Entry[ 3] * b0;
		inverse.m_Entry[13] = +m_Entry[ 0] * b3 - m_Entry[ 1] * b1 + m_Entry[ 2] * b0;
		inverse.m_Entry[ 2] = +m_Entry[13] * a5 - m_Entry[14] * a4 + m_Entry[15] * a3;
		inverse.m_Entry[ 6] = -m_Entry[12] * a5 + m_Entry[14] * a2 - m_Entry[15] * a1;
		inverse.m_Entry[10] = +m_Entry[12] * a4 - m_Entry[13] * a2 + m_Entry[15] * a0;
		inverse.m_Entry[14] = -m_Entry[12] * a3 + m_Entry[13] * a1 - m_Entry[14] * a0;
		inverse.m_Entry[ 3] = -m_Entry[ 9] * a5 + m_Entry[10] * a4 - m_Entry[11] * a3;
		inverse.m_Entry[ 7] = +m_Entry[ 8] * a5 - m_Entry[10] * a2 + m_Entry[11] * a1;
		inverse.m_Entry[11] = -m_Entry[ 8] * a4 + m_Entry[ 9] * a2 - m_Entry[11] * a0;
		inverse.m_Entry[15] = +m_Entry[ 8] * a3 - m_Entry[ 9] * a1 + m_Entry[10] * a0;

		float invDet = 1.0f / det;
		inverse.m_Entry[ 0] *= invDet;
		inverse.m_Entry[ 1] *= invDet;
		inverse.m_Entry[ 2] *= invDet;
		inverse.m_Entry[ 3] *= invDet;
		inverse.m_Entry[ 4] *= invDet;
		inverse.m_Entry[ 5] *= invDet;
		inverse.m_Entry[ 6] *= invDet;
		inverse.m_Entry[ 7] *= invDet;
		inverse.m_Entry[ 8] *= invDet;
		inverse.m_Entry[ 9] *= invDet;
		inverse.m_Entry[10] *= invDet;
		inverse.m_Entry[11] *= invDet;
		inverse.m_Entry[12] *= invDet;
		inverse.m_Entry[13] *= invDet;
		inverse.m_Entry[14] *= invDet;
		inverse.m_Entry[15] *= invDet;

		return inverse;
	}

	Matrix Matrix::Adjoint() const
	{
		float a0 = m_Entry[ 0] * m_Entry[ 5] - m_Entry[ 1] * m_Entry[ 4];
		float a1 = m_Entry[ 0] * m_Entry[ 6] - m_Entry[ 2] * m_Entry[ 4];
		float a2 = m_Entry[ 0] * m_Entry[ 7] - m_Entry[ 3] * m_Entry[ 4];
		float a3 = m_Entry[ 1] * m_Entry[ 6] - m_Entry[ 2] * m_Entry[ 5];
		float a4 = m_Entry[ 1] * m_Entry[ 7] - m_Entry[ 3] * m_Entry[ 5];
		float a5 = m_Entry[ 2] * m_Entry[ 7] - m_Entry[ 3] * m_Entry[ 6];
		float b0 = m_Entry[ 8] * m_Entry[13] - m_Entry[ 9] * m_Entry[12];
		float b1 = m_Entry[ 8] * m_Entry[14] - m_Entry[10] * m_Entry[12];
		float b2 = m_Entry[ 8] * m_Entry[15] - m_Entry[11] * m_Entry[12];
		float b3 = m_Entry[ 9] * m_Entry[14] - m_Entry[10] * m_Entry[13];
		float b4 = m_Entry[ 9] * m_Entry[15] - m_Entry[11] * m_Entry[13];
		float b5 = m_Entry[10] * m_Entry[15] - m_Entry[11] * m_Entry[14];

		return Matrix(
			+m_Entry[ 5] * b5 - m_Entry[ 6] * b4 + m_Entry[ 7] * b3,
			-m_Entry[ 1] * b5 + m_Entry[ 2] * b4 - m_Entry[ 3] * b3,
			+m_Entry[13] * a5 - m_Entry[14] * a4 + m_Entry[15] * a3,
			-m_Entry[ 9] * a5 + m_Entry[10] * a4 - m_Entry[11] * a3,
			-m_Entry[ 4] * b5 + m_Entry[ 6] * b2 - m_Entry[ 7] * b1,
			+m_Entry[ 0] * b5 - m_Entry[ 2] * b2 + m_Entry[ 3] * b1,
			-m_Entry[12] * a5 + m_Entry[14] * a2 - m_Entry[15] * a1,
			+m_Entry[ 8] * a5 - m_Entry[10] * a2 + m_Entry[11] * a1,
			+m_Entry[ 4] * b4 - m_Entry[ 5] * b2 + m_Entry[ 7] * b0,
			-m_Entry[ 0] * b4 + m_Entry[ 1] * b2 - m_Entry[ 3] * b0,
			+m_Entry[12] * a4 - m_Entry[13] * a2 + m_Entry[15] * a0,
			-m_Entry[ 8] * a4 + m_Entry[ 9] * a2 - m_Entry[11] * a0,
			-m_Entry[ 4] * b3 + m_Entry[ 5] * b1 - m_Entry[ 6] * b0,
			+m_Entry[ 0] * b3 - m_Entry[ 1] * b1 + m_Entry[ 2] * b0,
			-m_Entry[12] * a3 + m_Entry[13] * a1 - m_Entry[14] * a0,
			+m_Entry[ 8] * a3 - m_Entry[ 9] * a1 + m_Entry[10] * a0);
	}

	float Matrix::Determinant() const
	{
		float a0 = m_Entry[ 0] * m_Entry[ 5] - m_Entry[ 1] * m_Entry[ 4];
		float a1 = m_Entry[ 0] * m_Entry[ 6] - m_Entry[ 2] * m_Entry[ 4];
		float a2 = m_Entry[ 0] * m_Entry[ 7] - m_Entry[ 3] * m_Entry[ 4];
		float a3 = m_Entry[ 1] * m_Entry[ 6] - m_Entry[ 2] * m_Entry[ 5];
		float a4 = m_Entry[ 1] * m_Entry[ 7] - m_Entry[ 3] * m_Entry[ 5];
		float a5 = m_Entry[ 2] * m_Entry[ 7] - m_Entry[ 3] * m_Entry[ 6];
		float b0 = m_Entry[ 8] * m_Entry[13] - m_Entry[ 9] * m_Entry[12];
		float b1 = m_Entry[ 8] * m_Entry[14] - m_Entry[10] * m_Entry[12];
		float b2 = m_Entry[ 8] * m_Entry[15] - m_Entry[11] * m_Entry[12];
		float b3 = m_Entry[ 9] * m_Entry[14] - m_Entry[10] * m_Entry[13];
		float b4 = m_Entry[ 9] * m_Entry[15] - m_Entry[11] * m_Entry[13];
		float b5 = m_Entry[10] * m_Entry[15] - m_Entry[11] * m_Entry[14];
		float det = a0*b5 - a1*b4 + a2*b3 + a3*b2 - a4*b1 + a5*b0;
		return det;
	}

	Matrix Matrix::TransposeTimes(const Matrix& mat) const
	{
		// P = A^T*B
		return Matrix(
			m_Entry[0] * mat.m_Entry[0] +
			m_Entry[4] * mat.m_Entry[4] +
			m_Entry[8] * mat.m_Entry[8] +
			m_Entry[12] * mat.m_Entry[12],

			m_Entry[0] * mat.m_Entry[1] +
			m_Entry[4] * mat.m_Entry[5] +
			m_Entry[8] * mat.m_Entry[9] +
			m_Entry[12] * mat.m_Entry[13],

			m_Entry[0] * mat.m_Entry[2] +
			m_Entry[4] * mat.m_Entry[6] +
			m_Entry[8] * mat.m_Entry[10] +
			m_Entry[12] * mat.m_Entry[14],

			m_Entry[0] * mat.m_Entry[3] +
			m_Entry[4] * mat.m_Entry[7] +
			m_Entry[8] * mat.m_Entry[11] +
			m_Entry[12] * mat.m_Entry[15],

			m_Entry[1] * mat.m_Entry[0] +
			m_Entry[5] * mat.m_Entry[4] +
			m_Entry[9] * mat.m_Entry[8] +
			m_Entry[13] * mat.m_Entry[12],

			m_Entry[1] * mat.m_Entry[1] +
			m_Entry[5] * mat.m_Entry[5] +
			m_Entry[9] * mat.m_Entry[9] +
			m_Entry[13] * mat.m_Entry[13],

			m_Entry[1] * mat.m_Entry[2] +
			m_Entry[5] * mat.m_Entry[6] +
			m_Entry[9] * mat.m_Entry[10] +
			m_Entry[13] * mat.m_Entry[14],

			m_Entry[1] * mat.m_Entry[3] +
			m_Entry[5] * mat.m_Entry[7] +
			m_Entry[9] * mat.m_Entry[11] +
			m_Entry[13] * mat.m_Entry[15],

			m_Entry[2] * mat.m_Entry[0] +
			m_Entry[6] * mat.m_Entry[4] +
			m_Entry[10] * mat.m_Entry[8] +
			m_Entry[14] * mat.m_Entry[12],

			m_Entry[2] * mat.m_Entry[1] +
			m_Entry[6] * mat.m_Entry[5] +
			m_Entry[10] * mat.m_Entry[9] +
			m_Entry[14] * mat.m_Entry[13],

			m_Entry[2] * mat.m_Entry[2] +
			m_Entry[6] * mat.m_Entry[6] +
			m_Entry[10] * mat.m_Entry[10] +
			m_Entry[14] * mat.m_Entry[14],

			m_Entry[2] * mat.m_Entry[3] +
			m_Entry[6] * mat.m_Entry[7] +
			m_Entry[10] * mat.m_Entry[11] +
			m_Entry[14] * mat.m_Entry[15],

			m_Entry[3] * mat.m_Entry[0] +
			m_Entry[7] * mat.m_Entry[4] +
			m_Entry[11] * mat.m_Entry[8] +
			m_Entry[15] * mat.m_Entry[12],

			m_Entry[3] * mat.m_Entry[1] +
			m_Entry[7] * mat.m_Entry[5] +
			m_Entry[11] * mat.m_Entry[9] +
			m_Entry[15] * mat.m_Entry[13],

			m_Entry[3] * mat.m_Entry[2] +
			m_Entry[7] * mat.m_Entry[6] +
			m_Entry[11] * mat.m_Entry[10] +
			m_Entry[15] * mat.m_Entry[14],

			m_Entry[3] * mat.m_Entry[3] +
			m_Entry[7] * mat.m_Entry[7] +
			m_Entry[11] * mat.m_Entry[11] +
			m_Entry[15] * mat.m_Entry[15]);
	}

	Matrix Matrix::TimesTranspose(const Matrix& mat) const
	{
		// P = A*B^T
		return Matrix(
			m_Entry[0] * mat.m_Entry[0] +
			m_Entry[1] * mat.m_Entry[1] +
			m_Entry[2] * mat.m_Entry[2] +
			m_Entry[3] * mat.m_Entry[3],

			m_Entry[0] * mat.m_Entry[4] +
			m_Entry[1] * mat.m_Entry[5] +
			m_Entry[2] * mat.m_Entry[6] +
			m_Entry[3] * mat.m_Entry[7],

			m_Entry[0] * mat.m_Entry[8] +
			m_Entry[1] * mat.m_Entry[9] +
			m_Entry[2] * mat.m_Entry[10] +
			m_Entry[3] * mat.m_Entry[11],

			m_Entry[0] * mat.m_Entry[12] +
			m_Entry[1] * mat.m_Entry[13] +
			m_Entry[2] * mat.m_Entry[14] +
			m_Entry[3] * mat.m_Entry[15],

			m_Entry[4] * mat.m_Entry[0] +
			m_Entry[5] * mat.m_Entry[1] +
			m_Entry[6] * mat.m_Entry[2] +
			m_Entry[7] * mat.m_Entry[3],

			m_Entry[4] * mat.m_Entry[4] +
			m_Entry[5] * mat.m_Entry[5] +
			m_Entry[6] * mat.m_Entry[6] +
			m_Entry[7] * mat.m_Entry[7],

			m_Entry[4] * mat.m_Entry[8] +
			m_Entry[5] * mat.m_Entry[9] +
			m_Entry[6] * mat.m_Entry[10] +
			m_Entry[7] * mat.m_Entry[11],

			m_Entry[4] * mat.m_Entry[12] +
			m_Entry[5] * mat.m_Entry[13] +
			m_Entry[6] * mat.m_Entry[14] +
			m_Entry[7] * mat.m_Entry[15],

			m_Entry[8] * mat.m_Entry[0] +
			m_Entry[9] * mat.m_Entry[1] +
			m_Entry[10] * mat.m_Entry[2] +
			m_Entry[11] * mat.m_Entry[3],

			m_Entry[8] * mat.m_Entry[4] +
			m_Entry[9] * mat.m_Entry[5] +
			m_Entry[10] * mat.m_Entry[6] +
			m_Entry[11] * mat.m_Entry[7],

			m_Entry[8] * mat.m_Entry[8] +
			m_Entry[9] * mat.m_Entry[9] +
			m_Entry[10] * mat.m_Entry[10] +
			m_Entry[11] * mat.m_Entry[11],

			m_Entry[8] * mat.m_Entry[12] +
			m_Entry[9] * mat.m_Entry[13] +
			m_Entry[10] * mat.m_Entry[14] +
			m_Entry[11] * mat.m_Entry[15],

			m_Entry[12] * mat.m_Entry[0] +
			m_Entry[13] * mat.m_Entry[1] +
			m_Entry[14] * mat.m_Entry[2] +
			m_Entry[15] * mat.m_Entry[3],

			m_Entry[12] * mat.m_Entry[4] +
			m_Entry[13] * mat.m_Entry[5] +
			m_Entry[14] * mat.m_Entry[6] +
			m_Entry[15] * mat.m_Entry[7],

			m_Entry[12] * mat.m_Entry[8] +
			m_Entry[13] * mat.m_Entry[9] +
			m_Entry[14] * mat.m_Entry[10] +
			m_Entry[15] * mat.m_Entry[11],

			m_Entry[12] * mat.m_Entry[12] +
			m_Entry[13] * mat.m_Entry[13] +
			m_Entry[14] * mat.m_Entry[14] +
			m_Entry[15] * mat.m_Entry[15]);
	}

	Matrix Matrix::TransposeTimesTranspose(const Matrix& mat) const
	{
		// P = A^T*B^T
		return Matrix(
			m_Entry[0] * mat.m_Entry[0] +
			m_Entry[4] * mat.m_Entry[1] +
			m_Entry[8] * mat.m_Entry[2] +
			m_Entry[12] * mat.m_Entry[3],

			m_Entry[0] * mat.m_Entry[4] +
			m_Entry[4] * mat.m_Entry[5] +
			m_Entry[8] * mat.m_Entry[6] +
			m_Entry[12] * mat.m_Entry[7],

			m_Entry[0] * mat.m_Entry[8] +
			m_Entry[4] * mat.m_Entry[9] +
			m_Entry[8] * mat.m_Entry[10] +
			m_Entry[12] * mat.m_Entry[11],

			m_Entry[0] * mat.m_Entry[12] +
			m_Entry[4] * mat.m_Entry[13] +
			m_Entry[8] * mat.m_Entry[14] +
			m_Entry[12] * mat.m_Entry[15],

			m_Entry[1] * mat.m_Entry[0] +
			m_Entry[5] * mat.m_Entry[1] +
			m_Entry[9] * mat.m_Entry[2] +
			m_Entry[13] * mat.m_Entry[3],

			m_Entry[1] * mat.m_Entry[4] +
			m_Entry[5] * mat.m_Entry[5] +
			m_Entry[9] * mat.m_Entry[6] +
			m_Entry[13] * mat.m_Entry[7],

			m_Entry[1] * mat.m_Entry[8] +
			m_Entry[5] * mat.m_Entry[9] +
			m_Entry[9] * mat.m_Entry[10] +
			m_Entry[13] * mat.m_Entry[11],

			m_Entry[1] * mat.m_Entry[12] +
			m_Entry[5] * mat.m_Entry[13] +
			m_Entry[9] * mat.m_Entry[14] +
			m_Entry[13] * mat.m_Entry[15],

			m_Entry[2] * mat.m_Entry[0] +
			m_Entry[6] * mat.m_Entry[1] +
			m_Entry[10] * mat.m_Entry[2] +
			m_Entry[14] * mat.m_Entry[3],

			m_Entry[2] * mat.m_Entry[4] +
			m_Entry[6] * mat.m_Entry[5] +
			m_Entry[10] * mat.m_Entry[6] +
			m_Entry[14] * mat.m_Entry[7],

			m_Entry[2] * mat.m_Entry[8] +
			m_Entry[6] * mat.m_Entry[9] +
			m_Entry[10] * mat.m_Entry[10] +
			m_Entry[14] * mat.m_Entry[11],

			m_Entry[2] * mat.m_Entry[12] +
			m_Entry[6] * mat.m_Entry[13] +
			m_Entry[10] * mat.m_Entry[14] +
			m_Entry[14] * mat.m_Entry[15],

			m_Entry[3] * mat.m_Entry[0] +
			m_Entry[7] * mat.m_Entry[1] +
			m_Entry[11] * mat.m_Entry[2] +
			m_Entry[15] * mat.m_Entry[3],

			m_Entry[3] * mat.m_Entry[4] +
			m_Entry[7] * mat.m_Entry[5] +
			m_Entry[11] * mat.m_Entry[6] +
			m_Entry[15] * mat.m_Entry[7],

			m_Entry[3] * mat.m_Entry[8] +
			m_Entry[7] * mat.m_Entry[9] +
			m_Entry[11] * mat.m_Entry[10] +
			m_Entry[15] * mat.m_Entry[11],

			m_Entry[3] * mat.m_Entry[12] +
			m_Entry[7] * mat.m_Entry[13] +
			m_Entry[11] * mat.m_Entry[14] +
			m_Entry[15] * mat.m_Entry[15]);
	}

	Matrix Matrix::TimesDiagonal(const Vector4& diag) const
	{
		return Matrix(
			m_Entry[ 0] * diag.X, m_Entry[ 1] * diag.Y, m_Entry[ 2] * diag.Z, m_Entry[ 3],
			m_Entry[ 4] * diag.X, m_Entry[ 5] * diag.Y, m_Entry[ 6] * diag.Z, m_Entry[ 7],
			m_Entry[ 8] * diag.X, m_Entry[ 9] * diag.Y, m_Entry[10] * diag.Z, m_Entry[11],
			m_Entry[12] * diag.X, m_Entry[13] * diag.Y, m_Entry[14] * diag.Z, m_Entry[15]
			);
	}

	Matrix Matrix::DiagonalTimes(const Vector4& diag) const
	{
		return Matrix(
			diag.X * m_Entry[ 0], diag.X * m_Entry[ 1], diag.X * m_Entry[ 2], m_Entry[ 3],
			diag.Y * m_Entry[ 4], diag.X * m_Entry[ 5], diag.Y * m_Entry[ 6], m_Entry[ 7],
			diag.Z * m_Entry[ 8], diag.Z * m_Entry[ 9], diag.Z * m_Entry[10], m_Entry[11],
			m_Entry[12],          m_Entry[13],          m_Entry[14],          m_Entry[15]
			);
	}

	void Matrix::Orthonormalize()
	{
		// Algorithm uses Gram-Schmidt orthogonalization.  If 'this' matrix has
		// upper-left 3x3 block M = [m0|m1|m2], then the orthonormal output matrix
		// is Q = [q0|q1|q2],
		//
		//   q0 = m0/|m0|
		//   q1 = (m1-(q0*m1)q0)/|m1-(q0*m1)q0|
		//   q2 = (m2-(q0*m2)q0-(q1*m2)q1)/|m2-(q0*m2)q0-(q1*m2)q1|
		//
		// where |V| indicates length of vector V and A*B indicates dot
		// product of vectors A and B.

		// Compute q0.
		float invLength = 1.0f / sqrtf(m_Entry[0] * m_Entry[0] +
			m_Entry[4] * m_Entry[4] + m_Entry[8] * m_Entry[8]);

		m_Entry[0] *= invLength;
		m_Entry[4] *= invLength;
		m_Entry[8] *= invLength;

		// Compute q1.
		float dot0 = m_Entry[0] * m_Entry[1] + m_Entry[4] * m_Entry[5] +
			m_Entry[8] * m_Entry[9];

		m_Entry[1] -= dot0*m_Entry[0];
		m_Entry[5] -= dot0*m_Entry[4];
		m_Entry[9] -= dot0*m_Entry[8];

		invLength = 1.0f / sqrtf(m_Entry[1] * m_Entry[1] +
			m_Entry[5] * m_Entry[5] + m_Entry[9] * m_Entry[9]);

		m_Entry[1] *= invLength;
		m_Entry[5] *= invLength;
		m_Entry[9] *= invLength;

		// Compute q2.
		float dot1 = m_Entry[1] * m_Entry[2] + m_Entry[5] * m_Entry[6] +
			m_Entry[9] * m_Entry[10];

		dot0 = m_Entry[0] * m_Entry[2] + m_Entry[4] * m_Entry[6] +
			m_Entry[8] * m_Entry[10];

		m_Entry[2] -= dot0*m_Entry[0] + dot1*m_Entry[1];
		m_Entry[6] -= dot0*m_Entry[4] + dot1*m_Entry[5];
		m_Entry[10] -= dot0*m_Entry[8] + dot1*m_Entry[9];

		invLength = 1.0f / sqrtf(m_Entry[2] * m_Entry[2] +
			m_Entry[6] * m_Entry[6] + m_Entry[10] * m_Entry[10]);

		m_Entry[2] *= invLength;
		m_Entry[6] *= invLength;
		m_Entry[10] *= invLength;
	}

}
