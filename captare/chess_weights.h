#pragma once
#include "chess.h"

constexpr auto max_weights = 940;
constexpr auto op_phase = 0;
constexpr auto eg_phase = 1;
constexpr auto op_mobility = 2;
constexpr auto eg_mobility = 3;
constexpr auto op_king_attack = 4;
constexpr auto eg_king_attack = 7;
// not used 10-11
constexpr auto op_piece_values = 12;
constexpr auto eg_piece_values = 18;
constexpr auto op_pst = 24;
constexpr auto eg_pst = 408;
constexpr auto op_blocked_pawns = 792;
constexpr auto eg_blocked_pawns = 828;
// not used 864-895
constexpr auto op_isolated_pawn = 896;
constexpr auto eg_isolated_pawn = 897;
constexpr auto op_backward_pawn = 898;
constexpr auto eg_backward_pawn = 899;
constexpr auto op_doubled_pawn = 900;
constexpr auto eg_doubled_pawn = 901;
constexpr auto op_knight_outpost = 902;
constexpr auto eg_knight_outpost = 903;
constexpr auto op_bishop_outpost = 904;
constexpr auto eg_bishop_outpost = 905;
constexpr auto op_passed_pawns = 906;
constexpr auto eg_passed_pawns = 912;
constexpr auto op_adjacent_pawns = 918;
constexpr auto eg_adjacent_pawns = 924;
constexpr auto op_bishop_pair = 930;
constexpr auto eg_bishop_pair = 931;
constexpr auto op_pawn_majority = 932;
constexpr auto eg_pawn_majority = 933;
// not used 934-939
// TODO: Rooks on open or half-open files
// TODO: Doubled rooks
// TODO: Pinned Pieces
// TODO: King Near Enemy Passed Pawn
// TODO: Mobility weight per piece type
class chess_weights
{
private:
	
};

