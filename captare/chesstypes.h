#pragma once

#include <algorithm>
#include <bit>
#include <cassert>
#include <cstdint>
#include <intrin.h>

namespace chess
{
	constexpr auto max_colors = 2;
	constexpr auto max_pieces = 6;
	constexpr auto max_indices = 64;
	constexpr auto max_coords = 8;
	constexpr auto board_size = 64;
	constexpr auto none = -1;

	enum color : int_fast8_t { color_none = none, white, black };
	enum piece : int_fast8_t { piece_none = none, pawn, knight, bishop, rook, queen, king };
	enum index : int_fast8_t
	{
		index_none = none,
		a1, b1, c1, d1, e1, f1, g1, h1,
		a2, b2, c2, d2, e2, f2, g2, h2,
		a3, b3, c3, d3, e3, f3, g3, h3,
		a4, b4, c4, d4, e4, f4, g4, h4,
		a5, b5, c5, d5, e5, f5, g5, h5,
		a6, b6, c6, d6, e6, f6, g6, h6,
		a7, b7, c7, d7, e7, f7, g7, h7,
		a8, b8, c8, d8, e8, f8, g8, h8
	};
	enum move_type : uint_fast8_t
	{
		null_move,
		normal,
		capture,
		castle,
		enpassant,
		pawn_move,
		dbl_pawn_move,
		promote,
		promote_capture
	};

	enum castling_rights : uint_fast8_t
	{
		no_rights,
		white_king_side = 1,
		white_queen_side = 2,
		black_king_side = 4,
		black_queen_side = 8,
		all_rights = white_king_side | white_queen_side | black_king_side | black_queen_side
	};

	typedef int_fast8_t coord;

	extern const wchar_t* _color_to_string[max_colors];
	inline bool color_is_valid(const color c) { return c >= white && c <= black;  }
	inline const wchar_t* color_to_string(const color c) { assert(color_is_valid(c));  return _color_to_string[c]; }
	inline color opposite(const color c) { return static_cast<color>(static_cast<int>(c) ^ 1); }
	
	extern const wchar_t* _piece_to_string[max_pieces];
	inline bool piece_is_valid(const piece p) { return p >= pawn && p <= king; }
	inline const wchar_t* piece_to_string(const piece p) { assert(piece_is_valid(p));  return _piece_to_string[p]; }
	
	extern const wchar_t* _index_to_string[max_indices];
	inline bool index_is_valid(const index i) { return i >= a1 && i <= h8; }
	inline bool coord_is_valid(const coord c) { return c >= 0 && c < 8; }
	inline coord index_to_rank(const index i) { return static_cast<coord>(static_cast<int>(i) >> 3); }
	inline coord index_to_file(const index i) { return static_cast<coord>(static_cast<int>(i) & 7); }
	inline void index_to_coords(const index i, coord& file, coord& rank) { file = index_to_file(i); rank = index_to_rank(i); }
	inline index coord_to_index(const coord file, const coord rank) { return static_cast<index>(rank << 3 | file); }
	inline index index_flip(const index i) { return static_cast<index>(static_cast<int>(i) ^ 56); }
	inline const wchar_t* index_to_string(const index i) { assert(index_is_valid(i));  return _index_to_string[i]; }
	inline int_fast8_t index_distance(const index i1, const index i2)
	{
		coord f1, r1, f2, r2;
		index_to_coords(i1, f1, r1);
		index_to_coords(i2, f2, r2);
		return static_cast<int_fast8_t>(std::max(std::abs(f1 - f2), std::abs(r1 - r2)));
	}
	inline index index_to_normal(const color c, const index i) { return c == white ? i : index_flip(i); }

	typedef uint_fast64_t bitboard;
	inline int bb_popcount(const bitboard bb) { return std::popcount(bb); }
	inline int bb_tzcount(const bitboard bb) { return std::countr_zero(bb); }
	inline int bb_lzcount(const bitboard bb) { return std::countl_zero(bb); }
	inline bitboard bb_resetlsb(const bitboard bb) { return _blsr_u64(bb); }
}
