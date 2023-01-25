#include "chesstypes.h"
#include "square.h"

namespace chess
{
	square::square(const color color, const piece piece)
	{
		if (color == color_none || piece == piece_none)
		{
			data = 0;
		}
		else
		{
			set(color, piece);
		}
	}

	square& square::operator = (square&& other) noexcept
	{
		if (this != &other)
		{
			data = other.data;
			other.data = 0;
		}
		return *this;
	}

	const square& square::set(const color color, const piece piece)
	{
		assert(color != color_none && piece != piece_none);
		fields.occupied = 1;
		fields.color = static_cast<uint_fast8_t>(color);
		fields.piece = static_cast<uint_fast8_t>(piece);
		return *this;
	}
}