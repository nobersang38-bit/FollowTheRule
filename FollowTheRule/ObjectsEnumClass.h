#pragma once

enum class Objects
{
	Empty	= 1<<0,
	Space	= 1<<1,
	Wall	= 1<<2,
	Player	= 1<<3,
	Document= 1<<4,
	Map		= 1<<5,
};