#pragma once

#include "chesstypes.h"

namespace chess
{
	union alignas(uint_fast8_t) square
	{
		uint_fast8_t data;
		struct alignas(uint_fast8_t)
		{
			uint_fast8_t occupied : 1;
			uint_fast8_t color : 1;
			uint_fast8_t piece : 3;
		} fields {};

		square()
		{
			data = 0;
		}

		square(const square& other)
		{
			data = other.data;
		}

		square(square&& other) noexcept
			: data(other.data)
		{
			other.data = 0;
		}

		square(const color color, const piece piece);

		~square() = default;


		[[nodiscard]] bool get_occupied() const { return fields.occupied != 0; }
		[[nodiscard]] color get_color() const { return static_cast<color>(fields.color); }
		[[nodiscard]] piece get_piece() const { return static_cast<piece>(fields.piece); }

		const square& set(const color color, const piece piece);
		const square& clear() { data = 0; return *this; }

		square& operator = (const square& other) { data = other.data; return *this; }
		square& operator = (square&& other) noexcept;
		bool operator == (const square& other) const { return data == other.data; }
	};
}
