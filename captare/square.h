#pragma once

#include "chesstypes.h"

namespace chess
{
	union alignas(uint8_t) square
	{
	private:
		uint8_t data;
		struct alignas(uint8_t)
		{
			uint8_t occupied : 1;
			uint8_t color : 1;
			uint8_t piece : 3;
		} fields {};

	public:
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

		square(const chess::color color, const chess::piece piece);

		~square() = default;


		[[nodiscard]] bool occupied() const { return fields.occupied != 0; }
		[[nodiscard]] constexpr color color() const { return static_cast<chess::color>(fields.color); }
		[[nodiscard]] constexpr piece piece() const { return static_cast<chess::piece>(fields.piece); }

		const square& set(const chess::color color, const chess::piece piece);
		const square& clear() { data = 0; return *this; }

		square& operator = (const square& other) { data = other.data; return *this; }
		square& operator = (square&& other) noexcept;
		bool operator == (const square& other) const { return data == other.data; }

		static const square empty;
		static const square white_pawn;
		static const square white_knight;
		static const square white_bishop;
		static const square white_rook;
		static const square white_queen;
		static const square white_king;
		static const square black_pawn;
		static const square black_knight;
		static const square black_bishop;
		static const square black_rook;
		static const square black_queen;
		static const square black_king;
	};
}
