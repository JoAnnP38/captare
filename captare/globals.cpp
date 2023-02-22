#include "chess.h"

namespace chess
{
	const char* _color_to_string[max_colors] = { "white", "black" };
	const char* _piece_to_string[max_pieces] = { "P", "N", "B", "R", "Q", "K" };
	const char* _index_to_string[max_indices] =
	{
		"a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1",
		"a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2",
		"a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3",
		"a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4",
		"a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5",
		"a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6",
		"a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7",
		"a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8"
	};

	std::string trim_string(const std::string& str)
	{
		std::string copy{ str };
		const std::string whiteSpaces = " \t\n\r\f\v";
		const size_t first_non_space = copy.find_first_not_of(whiteSpaces);
		copy.erase(0, first_non_space);
		const size_t last_non_space = copy.find_last_not_of(whiteSpaces);
		copy.erase(last_non_space + 1);
		return copy;
	}

	std::vector<std::string> split_string(const std::string& str)
	{
		std::vector<std::string> output{};
		const std::string delimiters = " \t";
		size_t next = -1;
		do
		{
			const size_t current = next + 1;
			next = str.find_first_of(delimiters, current);
			output.push_back(str.substr(current, next - current));
		} while (next != std::string::npos);

		return output;
	}

	std::string lowercase_string(const std::string& str)
	{
		std::string copy{ str };
		std::ranges::transform(copy, copy.begin(), [](auto c) { return std::tolower(c, std::locale()); });
		return copy;
	}

	index index_parse(const std::string& str)
	{
		const std::string lower = lowercase_string(str);
		const auto file = static_cast<coord>(lower[0] - 'a');
		const auto rank = static_cast<coord>(lower[1] - '1');
		return coord_to_index(file, rank);
	}

	std::string bitboard_to_string(bitboard bb)
	{
		std::string bb_string{};
		for (coord rank = coord_min_value; rank <= coord_max_value; ++rank)
		{
			for (coord file = coord_min_value; file <= coord_max_value; ++file)
			{
				const index i = coord_to_index(file, rank);
				bb_string.push_back(bb & (1ULL << static_cast<int8_t>(i)) ? '1' : '0');
				bb_string.push_back(' ');
			}
			bb_string.push_back('\n');
		}
		return bb_string;
	}

	const square square::empty{};
	const square square::white_pawn{ white, pawn };
	const square square::white_knight{ white, knight };
	const square square::white_bishop{ white, bishop };
	const square square::white_rook{ white, rook };
	const square square::white_queen{ white, queen };
	const square square::white_king{ white, king };
	const square square::black_pawn{ black, pawn };
	const square square::black_knight{ black, knight };
	const square square::black_bishop{ black, bishop };
	const square square::black_rook{ black, rook };
	const square square::black_queen{ black, queen };
	const square square::black_king{ black, king };

	
	std::map<const char, square> notation::piece_map =
	{
		std::pair<const char, square>{'.', square::empty},
		std::pair<const char, square>{'P', square::white_pawn},
		std::pair<const char, square>{'N', square::white_knight},
		std::pair<const char, square>{'B', square::white_bishop},
		std::pair<const char, square>{'R', square::white_rook},
		std::pair<const char, square>{'Q', square::white_queen},
		std::pair<const char, square>{'K', square::white_king},
		std::pair<const char, square>{'p', square::black_pawn},
		std::pair<const char, square>{'n', square::black_knight},
		std::pair<const char, square>{'b', square::black_bishop},
		std::pair<const char, square>{'r', square::black_rook},
		std::pair<const char, square>{'q', square::black_queen},
		std::pair<const char, square>{'k', square::black_king}
	};

	char notation::piece_char_map[max_colors][max_pieces] =
	{
		{ 'P', 'N', 'B', 'R', 'Q', 'K' },
		{ 'p', 'n', 'b', 'r', 'q', 'k' }
	};

}