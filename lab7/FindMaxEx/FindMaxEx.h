#pragma once
#include <vector>

template <typename T, typename Less>
bool FindMax(std::vector<T> const& arr, T& maxValue, Less const& less)
{
	if (arr.empty())
	{
		return false;
	}

	T maxElem = arr[0];
	for (auto elem : arr)
	{
		if (less(maxElem, elem))
		{
			maxElem = elem;
		}
	}
	maxValue = maxElem;

	return true;
}