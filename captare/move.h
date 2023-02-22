// ReSharper disable CppClangTidyCppcoreguidelinesSpecialMemberFunctions
#pragma once

#include "chesstypes.h"

namespace chess
{
	union alignas(uint32_t) move
	{
	private:
		uint32_t value;
		struct alignas(uint32_t)
		{
			uint32_t pc : 3;
			uint32_t type : 4;
			uint32_t from : 6;
			uint32_t to : 6;
			uint32_t capture : 3;
			uint32_t promote : 3;
		} fields{};


	public:
		move() : value(0)
		{ }

		move(const uint32_t value) : value(value)
		{ }

		move(const piece pc, const index from, const index to, const move_type type = normal,
			const piece capture = piece_none, const piece promote = piece_none);

		move(const move& other)
			: value(other.value)
		{ }


		~move() = default;

		move& operator = (const move& other)
		{
			value = other.value;
			return *this;
		}

		bool operator == (const move& other) const
		{
			return value == other.value;
		}

		[[nodiscard]] piece get_piece() const { return static_cast<piece>(static_cast<int>(fields.pc) - 1); }
		[[nodiscard]] move_type type() const { return static_cast<move_type>(fields.type); }
		[[nodiscard]] index from() const { return static_cast<index>(fields.from); }
		[[nodiscard]] index to() const { return static_cast<index>(fields.to); }
		[[nodiscard]] piece capture() const { return static_cast<piece>(static_cast<int>(fields.capture) - 1); }
		[[nodiscard]] piece promote() const { return static_cast<piece>(static_cast<int>(fields.promote) - 1); }
		[[nodiscard]] uint32_t get_value() const { return value; }
		[[nodiscard]] bool is_capture() const { return capture() != piece_none; }
		[[nodiscard]] bool is_promote() const { return promote() != piece_none; }
		[[nodiscard]] bool is_pawn_move() const { return get_piece() == pawn; }
		[[nodiscard]] bool is_quiet() const { return !is_capture() && !is_pawn_move(); }

		static move null_move;
		static move empty;
	};
}
