// ReSharper disable CppClangTidyClangDiagnosticBitfieldEnumConversion
#include "move.h"

namespace chess
{
	move& move::operator = (move&& other) noexcept
	{
		if (this != &other)
		{
			value = other.value;
			other.value = 0;
		}
		return *this;
	}

	move::move(const piece pc, const index from, const index to, const move_type type, 
		const piece capture, const piece promote)
	{
		fields.pc = pc + 1;
		fields.type = type;
		fields.from = from;
		fields.to = to;
		fields.capture = capture + 1;
		fields.promote = promote + 1;
	}

	move move::null_move(piece_none, a1, a1, move_type::null_move, piece_none, piece_none);
}