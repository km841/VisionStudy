#include "pch.h"
#include "CCircle.h"

CCircle::CCircle(CVector2 CenterPos, float fRadius)
    : CShape(CenterPos)
	, m_fRadius(fRadius)
{
}

bool CCircle::IsOverlapped(const CVector2& MousePos)
{
	CVector2 Diff = MousePos - m_Pos;
	double fLen = Diff.Length();

	if (fLen <= m_fRadius)
		return true;
	else
		return false;
}

std::wstring CCircle::GetName() const
{
	return TEXT("Circle");
}

void CCircle::Draw(CImage* InImage)
{
	unsigned char* p = (unsigned char*)InImage->GetBits();
	int nPitch = InImage->GetPitch();

	int nWidth = InImage->GetWidth();
	int nHeight = InImage->GetHeight();

	for (int y = m_Pos.y - m_fRadius; y < m_Pos.y + m_fRadius; ++y)
	{
		for (int x = m_Pos.x - m_fRadius; x < m_Pos.x + m_fRadius; ++x)
		{
			if (y < 0 || y >= nHeight || x < 0 || x >= nWidth)
				continue;

			float fDistX = x - m_Pos.x;
			float fDistY = y - m_Pos.y;
			float fDist = fDistX * fDistX + fDistY * fDistY;

			if (fDist < m_fRadius * m_fRadius)
			{
				p[y * nPitch + x] = 0x80;
			}

			if (m_bIsOverlapped)
			{
				if (fDist <= m_fRadius * m_fRadius && 
					fDist >= (m_fRadius - 2) * (m_fRadius - 2))
				{
					p[y * nPitch + x] = 0x00;
				}
			}
		}
	}
}

bool CCircle::Save(const std::wstring& FileName)
{
    return false;
}

bool CCircle::Load(const std::wstring& FileName)
{
    return false;
}
