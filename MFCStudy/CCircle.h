#pragma once
#include "CShape.h"
#include "Common.h"
#include <atlimage.h>

class CCircle :
    public CShape
{
public:
    CCircle(CVector2 CenterPos, float fRadius);

    bool IsOverlapped(const CVector2& MousePos);
    float GetRadius() const { return m_fRadius; }
    void GridCtrlClickEffect(CImage* InImage);

public:
    virtual std::wstring GetName() const;
    virtual void Draw(CImage* InImage);
    virtual bool Save(const std::wstring& FileName);
    virtual bool Load(const std::wstring& FileName);

private:
    float m_fRadius;
};

