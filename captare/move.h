#pragma once

#include "chesstypes.h"

namespace chess
{
	union alignas(uint_fast32_t) move
	{
	private:
		uint_fast32_t value;
		struct alignas(uint_fast32_t)
		{
			uint_fast32_t pc : 3;
			uint_fast32_t type : 4;
			uint_fast32_t from : 6;
			uint_fast32_t to : 6;
			uint_fast32_t capture : 3;
			uint_fast32_t promote : 3;
		} fields{};


	public:
		move()
		{
			value = 0;
		}

		move(const uint_fast32_t value)
		{
			this->value = value;
		}

		move(const piece pc, const index from, const index to, const move_type type = normal,
			const piece capture = piece_none, const piece promote = piece_none);

		move(const move& other)
			: value(other.value)
		{ }

		move(move&& other) noexcept
			: value(other.value)
		{
			other.value = 0;
		}

		~move() = default;

		move& operator = (const move& other)
		{
			value = other.value;
			return *this;
		}

		move& operator = (move&& other) noexcept;

		bool operator == (const move& other) const
		{
			return value == other.value;
		}

		[[nodiscard]] piece get_piece() const { return static_cast<piece>(static_cast<int>(fields.pc) - 1); }
		[[nodiscard]] move_type get_type() const { return static_cast<move_type>(fields.type); }
		[[nodiscard]] index get_from() const { return static_cast<index>(fields.from); }
		[[nodiscard]] index get_to() const { return static_cast<index>(fields.to); }
		[[nodiscard]] piece get_capture() const { return static_cast<piece>(static_cast<int>(fields.capture) - 1); }
		[[nodiscard]] piece get_promote() const { return static_cast<piece>(static_cast<int>(fields.promote) - 1); }
		[[nodiscard]] uint_fast32_t get_value() const { return value; }

		static move null_move;
	};
}
