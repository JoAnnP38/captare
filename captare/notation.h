#pragma once

#include <array>
#include <string>
#include <map>
#include "chesstypes.h"
#include "square.h"


namespace chess
{
	class position;

	class notation
	{
	public:
		notation() = default;
		explicit notation(const std::string& fen_string);
		explicit notation(const chess::position& pos);

		[[nodiscard]] color side_to_move() const { return _side_to_move; }
		[[nodiscard]] castling_rights castling() const { return _castling; }
		[[nodiscard]] index ep() const { return _ep; }
		[[nodiscard]] uint16_t half_move_clock() const { return _half_move_clock; }
		[[nodiscard]] uint16_t full_move_counter() const { return _full_move_counter; }
		[[nodiscard]] const std::string& to_string() const { return _fen_string; }
		[[nodiscard]] const std::array<square, board_size>& squares() const { return _squares; }
		[[nodiscard]] const square& squares(index i) const { return _squares[i]; }

		static bool is_valid_fen(const std::string& fen_string);
		static bool try_parse(const std::string& fen_string, notation& fen);
		static char piece_char_map[max_colors][max_pieces];

	private:
		void parse();
		void parse_squares(const std::string& fen_squares);
		void parse_side_to_move(const std::string& fen_color);
		void parse_castling(const std::string& fen_castling);
		void parse_enpassant(const std::string& fen_ep);

		void format_pieces(std::string& s) const;
		void format_castling(std::string& s) const;


		std::string _fen_string{};
		std::array<square, board_size> _squares{};
		color _side_to_move{ color_none };
		castling_rights _castling{ no_rights };
		index _ep{ index_none };
		uint16_t _half_move_clock{ 0 };
		uint16_t _full_move_counter{ 0 };

		static std::map<const char, square> piece_map;
	};
}
