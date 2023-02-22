// ReSharper disable CppClangTidyClangDiagnosticBitfieldEnumConversion
#include "chess.h"

namespace chess
{

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
	move move::empty{};
}