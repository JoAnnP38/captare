#pragma once

#include "chesstypes.h"
#include "move.h"
#include "square.h"

namespace chess
{
	class position
	{
	private:
		// members used to track board state and pieces
		square board[board_size]{};
		bitboard pieces[max_colors][max_pieces]{};
		bitboard units[max_colors]{};
		bitboard all;

		// members used to track other aspects of game state
		color side_to_move;
		castling_rights castling;
		index enpassant;
		index enpassant_validated;
		uint_fast16_t half_move_clock;
		uint_fast16_t full_move_counter;
		uint_fast64_t hash;

	public:
		position();



		
	};
}
