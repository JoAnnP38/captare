#pragma once
#include "chess.h"

namespace chess
{
	class move_vector : public std::vector<move>
	{
	public:
		move_vector()
		{
			reserve(64);
		}
	};
}

