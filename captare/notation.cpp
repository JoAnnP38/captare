// ReSharper disable CppClangTidyBugproneNarrowingConversions
#include <algorithm>
#include <stdexcept>
#include "chess.h"

namespace chess
{
	notation::notation(const std::string& fen_string)
	{
		if (!is_valid_fen(fen_string))
		{
			throw std::invalid_argument{ "invalid notation string" };
		}
		_fen_string = fen_string;
		_squares.fill(square::empty);
		parse();
	}

	notation::notation(const position& pos)
	{
		std::ranges::copy(pos.board(), _squares.begin());
		_side_to_move = pos.side_to_move();
		_castling = pos.castling();
		_ep = pos.enpassant();
		_half_move_clock = pos.half_move_clock();
		_full_move_counter = pos.full_move_counter();

		std::string s{};
		format_pieces(s);
		s.append(_side_to_move == white ? " w " : " b ");
		format_castling(s);
		s.append(_ep == index_none ? "-" : index_to_string(_ep));
		s.append(" ");
		s.append(std::to_string(_half_move_clock));
		s.append(" ");
		s.append(std::to_string(_full_move_counter));
		_fen_string = s;
	}

	bool notation::is_valid_fen(const std::string& fen_string)
	{
		return std::regex_match(fen_string, regex_fen);
	}

	bool notation::try_parse(const std::string& fen_string, notation& fen)
	{
		if (is_valid_fen(fen_string))
		{
			fen = notation{ fen_string };
			return true;
		}
		return false;
	}

	void notation::parse()
	{
		const std::string copy{ _fen_string };
		const std::vector tokens = split_string(trim_string(copy));
		parse_squares(tokens[0]);
		parse_side_to_move(tokens[1]);
		parse_castling(tokens[2]);
		parse_enpassant(tokens[3]);
		_half_move_clock = static_cast<uint16_t>(std::stoi(tokens[4]));
		_full_move_counter = static_cast<uint16_t>(std::stoi(tokens[5]));
	}

	void notation::parse_squares(const std::string& fen_squares)
	{
		coord rank = coord_max_value;
		coord file = coord_min_value;

		for (auto &ch : fen_squares)
		{
			if (ch == '/')
			{
				--rank;
				file = 0;
			}
			else if (isdigit(ch))
			{
				file += static_cast<coord>(ch - '0');
			}
			else
			{
				const index idx = coord_to_index(file++, rank);
				if (index_is_valid(idx))
				{
					_squares[idx] = piece_map[ch];
				}
			}
		}
	}

	void notation::parse_side_to_move(const std::string& fen_color)
	{
		_side_to_move = fen_color[0] == 'w' ? white : black;
	}

	void notation::parse_castling(const std::string& fen_castling)
	{
		uint8_t castling = no_rights;

		for (auto &ch : fen_castling)
		{
			switch (ch)
			{
				case 'K':
					castling |= white_king_side;
					break;

				case 'Q':
					castling |= white_queen_side;
					break;

				case 'k':
					castling |= black_king_side;
					break;

				case 'q':
					castling |= black_queen_side;
					break;

				default: ;
			}
		}
		_castling = static_cast<castling_rights>(castling);
	}

	void notation::parse_enpassant(const std::string& fen_ep)
	{
		_ep = fen_ep[0] == '-' ? index_none : index_parse(fen_ep);
	}

	void notation::format_pieces(std::string& s) const
	{
		for (coord rank = coord_max_value; rank >= coord_min_value; --rank)
		{
			int empty_count = 0;
			for (coord file = coord_min_value; file <= coord_max_value; ++file)
			{
				const index idx = coord_to_index(file, rank);
				const square& sq = _squares[idx];
				if (!sq.occupied())
				{
					++empty_count;
				}
				else
				{
					if (empty_count > 0)
					{
						s.append(std::to_string(empty_count));
						empty_count = 0;
					}
					s.push_back(piece_char_map[sq.color()][sq.piece()]);
				}
			}

			if (empty_count > 0)
			{
				s.append(std::to_string(empty_count));
			}

			if (rank > coord_min_value)
			{
				s.push_back('/');
			}
		}
	}

	void notation::format_castling(std::string& s) const
	{
		if (_castling == no_rights)
		{
			s.push_back('-');
		}
		else
		{
			if (_castling & white_king_side)
			{
				s.push_back('K');
			}

			if (_castling & white_queen_side)
			{
				s.push_back('Q');
			}

			if (_castling & black_king_side)
			{
				s.push_back('k');
			}

			if (_castling & black_queen_side)
			{
				s.push_back('q');
			}
		}
		s.push_back(' ');
	}

}
