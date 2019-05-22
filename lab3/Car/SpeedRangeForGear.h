#pragma once

struct SpeedRangeForGear
{
	const int min_speed;
	const int max_speed;
};

const SpeedRangeForGear REVERSE_SPEED_NOT_ZERO = { 1, 20 };
const SpeedRangeForGear FIRST_SPEED_NOT_ZERO = { 1, 30 };
const SpeedRangeForGear ZERO_SPEED = { 0, 0 };
const SpeedRangeForGear FIRST_SPEED = { 0, 30 };
const SpeedRangeForGear SECOND_SPEED = { 20, 50 };
const SpeedRangeForGear THIRD_SPEED = { 30, 60 };
const SpeedRangeForGear FOURTH_SPEED = { 40, 90 };
const SpeedRangeForGear FIFTH_SPEED = { 50, 150 };
