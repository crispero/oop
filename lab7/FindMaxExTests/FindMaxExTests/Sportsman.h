#pragma once
#include <string>

struct Sportsman
{
	std::string name;
	int height;
	float weight;
};

bool IsLessName(Sportsman const& first, Sportsman const& second)
{
	return first.name < second.name;
}

bool IsLessHeight(Sportsman const& first, Sportsman const& second)
{
	return first.height < second.height;
}

bool IsLessWeight(Sportsman const& first, Sportsman const& second)
{
	return first.weight < second.weight;
}