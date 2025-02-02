#pragma once
#include "MathLib.h"
#include <vector>
#include <string>
#include <assert.h>
#include <algorithm>

#define THICKNESS 6.0f

static void AssertEx(bool bExpression, const std::wstring& Message)
{
	if (bExpression)
		return;

	MessageBoxW(NULL, Message.c_str(), L"Assert", MB_OK);
	assert(bExpression);
}

enum class EClickMode
{
	Create,
	Move,
};

enum class EShapeTypes
{
	Circle,
	Curve,
	Count,
};

enum class ECurveType
{
	Bezier,
	NSpline,
	BSpline,
};