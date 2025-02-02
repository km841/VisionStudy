#pragma once
#include "Common.h"
#include "CCircle.h"
#include "CCurve.h"

class CShape;



struct CShapeInfo
{
	CVector2 Pos;
	float fThickness;
	std::vector<CVector2> ControlPoints;
	EShapeTypes eShapeTypes;
};

class CShapes
{
public:
	CShapes(CImage* InImage);
	~CShapes();

public:
	void Draw();
	void RegisterShape(CShape* pShape);
	bool CheckOverlap(CVector2 MousePos);
	CShape* GetOverlapShape(CVector2 MousePos);

	const std::vector<CShape*>& GetShapes() const { return m_vecShapes; }
	CShape* GetClickedShape() { return m_pClickedShape; }
	CCurve* GetCurve() { return m_pCurve; }
	void RemoveClickedShape() { m_pClickedShape = nullptr; }
	int GetShapesCount() { return static_cast<int>(m_vecShapes.size()); }
	bool IsExistsCurve();

	void RedefineCurve(float fThickness, ECurveType eCurveType);
	void RemoveShape(CShape* pShape);

	template<typename T>
	T* AddShape(const CShapeInfo& ShapeInfo);

private:
	CCircle* CreateCircle(CVector2 CenterPos, float fRadius);
	CCurve*  CreateCurve(const std::vector<CVector2>& ControlPoints, float fThickness);

private:
	CImage* m_Image;
	CCurve* m_pCurve;
	CShape* m_pClickedShape;
	std::vector<CShape*> m_vecShapes;
};

template<typename T>
inline T* CShapes::AddShape(const CShapeInfo& ShapeInfo)
{
	EShapeTypes ShapeTypes = ShapeInfo.eShapeTypes;
	CShape* pShape = nullptr;
	
	switch (ShapeTypes)
	{
	case EShapeTypes::Circle:
		pShape = CreateCircle(ShapeInfo.Pos, ShapeInfo.fThickness);
		break;

	case EShapeTypes::Curve:
		pShape = CreateCurve(ShapeInfo.ControlPoints, ShapeInfo.fThickness);
		m_pCurve = static_cast<CCurve*>(pShape);
		break;
	}
	
	AssertEx(pShape != nullptr, _T("CShapes::CreateShape(const CShapeInfo& ShapeInfo) -> Shape 생성 실패!"));
	m_vecShapes.push_back(static_cast<T*>(pShape));

	return static_cast<T*>(pShape);
}
