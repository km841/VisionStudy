#include "pch.h"
#include "CShape.h"

CShape::CShape(const CVector2& Pos, EShapeType eShapeType)
	: m_Pos(Pos)
	, m_bIsOverlapped(false)
	, m_eShapeType(eShapeType)
{
	static UINT64 nGenerateID = 0;
	m_ID = nGenerateID++;
}

