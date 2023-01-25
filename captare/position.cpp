#include "position.h"

namespace chess
{
	position::position()
	{
		std::memset(board, 0, board_size * sizeof(square));
		std::memset(pieces, 0, static_cast<size_t>(max_colors) * max_pieces * sizeof(bitboard));
		std::memset(units, 0, max_colors * sizeof(bitboard));
		all = 0;
		side_to_move = color_none;
		castling = no_rights;
		enpassant = index_none;
		enpassant_validated = index_none;
		half_move_clock = 0;
		full_move_counter = 0;
		hash = 0;
	}
}