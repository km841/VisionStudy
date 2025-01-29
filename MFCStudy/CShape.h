#pragma once
#include "Common.h"
class CShape
{
public:
	CShape(const CVector2& Pos)
		: m_Pos(Pos)
		, m_bIsOverlapped(false)
	{}

	virtual ~CShape() {}

public:
	virtual std::wstring GetName() const = 0;
	virtual bool IsOverlapped(const CVector2& MousePos) { return false; }
	virtual void Draw(CImage* InImage) = 0;
	virtual bool Save(const std::wstring& FileName) = 0;
	virtual bool Load(const std::wstring& FileName) = 0;

public:
	CVector2 GetPos() const { return m_Pos; }
	void SetPos(const CVector2& Pos) { m_Pos = Pos; }
	void SetOverlapped(bool bOverlapped) { m_bIsOverlapped = bOverlapped; }

protected:
	CVector2 m_Pos;
	bool m_bIsOverlapped;
};

