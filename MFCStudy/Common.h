#pragma once
#include "MathLib.h"
#include <vector>
#include <string>
#include <assert.h>

static void AssertEx(bool bExpression, const std::wstring& Message)
{
	if (bExpression)
		return;

	MessageBoxW(NULL, Message.c_str(), L"Assert", MB_OK);
	assert(bExpression);
}