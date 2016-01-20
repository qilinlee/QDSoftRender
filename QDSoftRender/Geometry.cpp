#include "Geometry.h"
#include "Utility.h"

namespace QDSoftRender
{
	VertexBuffer::VertexBuffer(unsigned int iVertexCount)
		: m_arrayVertex(nullptr)
		, m_iVertexCount(iVertexCount)
		, m_bLocked(false)
	{
		m_arrayVertex = new Vertex[iVertexCount];
	}

	VertexBuffer::~VertexBuffer()
	{
		SafeDelete(m_arrayVertex); 
	}

	QDSoftRender::VertexBuffer* VertexBuffer::CreateVertexBuffer(unsigned int iVertexCount)
	{
		VertexBuffer *pBuffer = new VertexBuffer(iVertexCount);
		return pBuffer;
	}

	void VertexBuffer::DestroyVertexBuffer(VertexBuffer *pBuffer)
	{
		SafeDelete(pBuffer);
	}

	bool VertexBuffer::LockVertex(Vertex* &pVertex,unsigned int &length)
	{
		if (!m_bLocked)
		{
			m_bLocked = true;
			pVertex = m_arrayVertex;
			length = m_iVertexCount;
			return true;
		}

		return false;
	}

	void VertexBuffer::UnlockVertex()
	{
		m_bLocked = false;
	}
	
	//
	//IndexBuffer
	//
	IndexBuffer::IndexBuffer(unsigned int iIndexCount)
		: m_arrayIndex(nullptr)
		, m_iIndexCount(iIndexCount)
		, m_bLocked(false)
	{

	}

	IndexBuffer::~IndexBuffer()
	{
		SafeDelete(m_arrayIndex);
	}

	IndexBuffer* IndexBuffer::CreateVertexBuffer(unsigned int iIndexCount)
	{
		IndexBuffer *pBuffer = new IndexBuffer( iIndexCount);
		return pBuffer;
	}

	void IndexBuffer::DestroyVertexBuffer(IndexBuffer *pBuffer)
	{
		SafeDelete(pBuffer);
	}

	bool IndexBuffer::LockVertex(int* &pIndex, unsigned int &length)
	{
		if (!m_bLocked)
		{
			m_bLocked = true;
			pIndex = m_arrayIndex;
			length = m_iIndexCount;
			return true;
		}

		return false;
	}

	void IndexBuffer::UnlockVertex()
	{
		m_bLocked = false;
	}



}