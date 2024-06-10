#pragma once
#include <string>

enum class SubjectType
{
	EMPTY,
	CHINO,
	MYU,
	NEFFY,
	NINA,
	RARA,
	VITTE,
	SOUGHT
};

struct SubjectData
{
	SubjectData(SubjectType type, int handle):
		subType(type),
		subHandle(handle)
	{
	}
	virtual ~SubjectData()
	{
	}

	SubjectType subType = SubjectType::EMPTY;
	int subHandle = -1;
	bool isDisable = false;
};