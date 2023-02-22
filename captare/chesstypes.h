#pragma once

#include <algorithm>
#include <array>
#include <cassert>
#include <chrono>
#include <cstdint>
#include <regex>
#include <tuple>
#include <vector>

namespace chess
{
	constexpr auto max_colors = 2;
	constexpr auto max_pieces = 6;
	constexpr auto max_indices = 64;
	constexpr auto max_coords = 8;
	constexpr auto max_ply = 128;
	constexpr auto board_size = 64;
	constexpr auto none = -1;
	constexpr auto max_game_length = 512;
	constexpr auto checkmate_score = 20000;
	constexpr auto checkmate_base = 19500;
	constexpr auto coord_max_value = 7;
	constexpr auto coord_min_value = 0;

	const std::regex regex_fen{ R"(^\s*([rnbqkpRNBQKP1-8]+/){7}[rnbqkpRNBQKP1-8]+\s[bw]\s(-|K?Q?k?q?)\s(-|[a-h][36])\s\d+\s\d+\s*$)" };
	const std::regex regex_move{ "^[a-h][1-8][a-h][1-8](n|b|r|q)?$" };
	const std::regex regex_index{ "^[a-h][1-8]$" };
	constexpr const char* fen_start_pos = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
	constexpr const char* fen_empty = "8/8/8/8/8/8/8/8 w - - 0 0";
	constexpr char newline = '\n';

	constexpr const char* app_name = "Pedantic";
	constexpr const char* app_version = "v1.0";
	constexpr const char* app_author = "JoAnn D. Peeler";
	constexpr const char* app_url = "https://github.com/JoAnnP38/Pedantic2";

	enum color : int8_t { color_none = none, white, black };
	extern const char* _color_to_string[max_colors];
	inline bool color_is_valid(const color c) { return c >= white && c <= black; }
	inline const char* color_to_string(const color c) { assert(color_is_valid(c));  return _color_to_string[c]; }
	inline color opposite(const color c) { return static_cast<color>(static_cast<int>(c) ^ 1); }
	constexpr color operator~(const color c) { return static_cast<color>(c ^ black); }

	enum piece : int8_t { piece_none = none, pawn, knight, bishop, rook, queen, king };
	extern const char* _piece_to_string[max_pieces];
	inline bool piece_is_valid(const piece p) { return p >= pawn && p <= king; }
	inline const char* piece_to_string(const piece p) { assert(piece_is_valid(p));  return _piece_to_string[p]; }
	inline piece operator++(piece& p) { p = static_cast<piece>(p + 1); return p; }

	typedef int8_t coord;
	inline bool coord_is_valid(const coord c) { return c >= 0 && c < 8; }


	enum index : int8_t
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
	extern const char* _index_to_string[max_indices];
	inline bool index_is_valid(const index i) { return i >= a1 && i <= h8; }
	inline index coord_to_index(const coord file, const coord rank) { return static_cast<index>(rank << 3 | file); }
	inline coord index_to_rank(const index i) { return static_cast<coord>(static_cast<int>(i) >> 3); }
	inline coord index_to_file(const index i) { return static_cast<coord>(static_cast<int>(i) & 7); }
	inline void index_to_coords(const index i, coord& file, coord& rank) { file = index_to_file(i); rank = index_to_rank(i); }
	inline index index_flip(const index i) { return static_cast<index>(static_cast<int>(i) ^ 56); }
	inline const char* index_to_string(const index i) { assert(index_is_valid(i));  return _index_to_string[i]; }
	inline int8_t index_distance(const index i1, const index i2)
	{
		coord f1, r1, f2, r2;
		index_to_coords(i1, f1, r1);
		index_to_coords(i2, f2, r2);
		return static_cast<int8_t>(std::max(std::abs(f1 - f2), std::abs(r1 - r2)));
	}
	inline index index_to_normal(const color c, const index i) { return c == white ? i : index_flip(i); }
	extern index index_parse(const std::string& s);

	enum move_type : uint8_t
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

	enum castling_rights : uint8_t
	{
		no_rights,
		white_king_side = 1,
		white_queen_side = 2,
		black_king_side = 4,
		black_queen_side = 8,
		all_rights = white_king_side | white_queen_side | black_king_side | black_queen_side
	};
	
	typedef uint64_t bitboard;
	extern std::string bitboard_to_string(bitboard bb);

	extern std::string trim_string(const std::string& str);
	extern std::vector<std::string> split_string(const std::string& str);
	extern std::string lowercase_string(const std::string& str);
}
