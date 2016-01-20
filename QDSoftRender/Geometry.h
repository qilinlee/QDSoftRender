#pragma once

#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__
#include "Math/Math.h"
#include "Color.h"

namespace QDSoftRender
{
	struct TextureCoord
	{
		float u;
		float v;
	};

	struct Vertex
	{
		Vector4 pos;
		TextureCoord uv;
		Color color;
		float rhw;

	public:
		Vertex():pos(0,0,0),color(0xFFFFFFFF),rhw(0.0f){}
 	};

	class VertexBuffer
	{
	public:
		static VertexBuffer* CreateVertexBuffer(unsigned int iVertexCount);
		static void DestroyVertexBuffer(VertexBuffer *pBuffer);
		~VertexBuffer();

		bool LockVertex(Vertex* &pVertex,unsigned int &length);
		void UnlockVertex();
	private:
		VertexBuffer(unsigned int iVertexCount);
		VertexBuffer(const VertexBuffer &src);
		VertexBuffer& operator=(const VertexBuffer &src);
	private:
		Vertex *m_arrayVertex;
		unsigned int m_iVertexCount;
		bool m_bLocked;
	};

	class IndexBuffer
	{
	public:
		static IndexBuffer* CreateVertexBuffer(unsigned int iIndexCount);
		static void DestroyVertexBuffer(IndexBuffer *pBuffer);
		~IndexBuffer();
		bool LockVertex(int* &pIndex, unsigned int &length);
		void UnlockVertex();
	private:
		IndexBuffer(unsigned int iIndexCount);
		IndexBuffer(const VertexBuffer &src);
		IndexBuffer& operator=(const VertexBuffer &src);
	private:
		int *m_arrayIndex;
		unsigned int m_iIndexCount;
		bool m_bLocked;
	};
}
#endif