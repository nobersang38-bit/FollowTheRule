#pragma once

enum class Objects : int64_t
{
	Empty			= 1<<0,
	Space			= 1<<1,
	Wall			= 1<<2,
	Player			= 1<<3,
	RuleDocument	= 1<<4,
	Map				= 1<<5,
	Enemy			= 1<<6,
	Goal			= 1<<7,
	FadedFinger		= 1<<8,
	Talisman		= 1<<9
};