// ReSharper disable CppClangTidyCppcoreguidelinesSpecialMemberFunctions
#pragma once

#include "chess.h"
#include "move_vector.h"

namespace chess
{
	class position
	{
		#pragma region position_state

		struct position_state
		{
		public:
			move move;
			color side_to_move; 
			castling_rights castling;
			index enpassant;
			index enpassant_validated;
			uint16_t half_move_clock;
			uint16_t full_move_counter; 
			uint64_t hash;

			position_state();
			position_state(const position& p, const chess::move m);
			void restore(position& p) const;
		};

		#pragma endregion

		#pragma region ray

		struct ray
		{
		public:
			bitboard north;
			bitboard north_east;
			bitboard east;
			bitboard south_east;
			bitboard south;
			bitboard south_west;
			bitboard west;
			bitboard north_west;

			ray(bitboard north, bitboard north_east, bitboard east, bitboard south_east,
				bitboard south, bitboard south_west, bitboard west, bitboard north_west)
					: north(north), north_east(north_east), east(east), south_east(south_east),
					  south(south), south_west(south_west), west(west), north_west(north_west)
			{}
		};

		#pragma endregion

		#pragma region magic_hash

		struct magic_hash
		{
		public:
			int offset;
			uint64_t mask;
			uint64_t hash;

			magic_hash(int offset, uint64_t mask, uint64_t hash)
				: offset(offset), mask(mask), hash(hash)
			{ }
		};

		#pragma endregion

		#pragma region castling_info

		struct castling_info
		{
		public:
			index king_from;
			index king_to;
			index king_move_thru;
			index rook_from;
			index rook_to;
			castling_rights castling_mask;

			castling_info(index king_from, index king_to, index king_move_thru, index rook_from, index rook_to, castling_rights castling_mask)
				:	king_from(king_from), king_to(king_to), king_move_thru(king_move_thru),
					rook_from(rook_from), rook_to(rook_to), castling_mask(castling_mask)
			{ }
		};

		#pragma endregion

	private:
		// members used to track board state and pieces
		std::array<square, board_size> _board{};
		bitboard _pieces[max_colors][max_pieces]{};
		bitboard _units[max_colors]{};
		bitboard _all{0};

		// members used to track other aspects of game state
		color _side_to_move{color_none};
		castling_rights _castling{no_rights};
		index _enpassant{index_none};
		index _enpassant_validated{index_none};
		uint16_t _half_move_clock{0};
		uint16_t _full_move_counter{0};
		zobrist_hash _hash{0};

		std::vector<position_state> _history{};

		position(const position& other);
		void clear();

		[[nodiscard]] bool is_ep_valid(const color c) const 
		{
			return _enpassant != index_none && (pawn_defends[c][_enpassant] & _pieces[c][pawn]) != 0;
		}

		// bitboard masks
		static const bitboard pawn_defends[max_colors][max_indices];
		static const bitboard piece_moves[max_pieces][max_indices];
		static const ray rays[max_indices + 1];
		static const ray revs[max_indices + 1];
		static bitboard magic_lookup[88507];
		static const magic_hash bishop_magics[max_indices];
		static const magic_hash rook_magics[max_indices];
		static const bitboard mask_files[max_indices];
		static const bitboard mask_ranks[max_indices];
		static const index pawn_left[max_colors][max_indices];
		static const index pawn_right[max_colors][max_indices];
		static const index pawn_plus[max_colors][max_indices];
		static const index pawn_double[max_colors][max_indices];
		static const bitboard between[max_indices][max_indices];
		static const int ep_offset[max_colors];
		static const uint8_t castle_mask[max_indices];
		static const castling_info castling_information[4];

	public:
		position();
		explicit position(const char* fen_string);

		[[nodiscard]] const std::array<square, board_size>& board() const { return _board; }
		[[nodiscard]] const square& board(index i) const { return _board[i]; }
		[[nodiscard]] color side_to_move() const { return _side_to_move; }
		[[nodiscard]] color opponent_color() const { return ~_side_to_move; }
		[[nodiscard]] castling_rights castling() const { return _castling; }
		[[nodiscard]] index enpassant() const { return _enpassant; }
		[[nodiscard]] index enpassant_validated() const { return _enpassant_validated; }
		[[nodiscard]] uint16_t half_move_clock() const { return _half_move_clock; }
		[[nodiscard]] uint16_t full_move_counter() const { return _full_move_counter; }
		[[nodiscard]] uint64_t hash() const { return _hash; }
		[[nodiscard]] bitboard pieces(color c, piece pc) const { return _pieces[c][pc]; }
		[[nodiscard]] bitboard units(color c) const { return _units[c]; }
		[[nodiscard]] bitboard all() const { return _all; }

		#pragma region make / unmake moves

		bool make_move(const move& mv);
		void unmake_move();
		void save_state(const move& mv);
		void restore_state();
		[[nodiscard]] bool is_square_attacked_by(const index sq, const color by) const;
		[[nodiscard]] bool is_checked(const color by) const { return is_square_attacked_by(static_cast<index>(bitops::tz_count(_pieces[~by][king])), by); }
		[[nodiscard]] bool is_checked() const { return is_checked(~_side_to_move); }
		static const castling_info* lookup_castling_info(index king_to);
		void update_castling(index from, index to)
		{
			_castling = static_cast<castling_rights>(_castling & castle_mask[from] & castle_mask[to]);
		}

		#pragma endregion

		#pragma region move generation

		template<color C> void generate_moves(move_vector& moves) const;
		template<color C, piece P> void generate_piece_moves(move_vector& moves) const;

		void generate_ep(move_vector& moves) const;

		template<color C> void generate_castling(move_vector& moves) const;
		template<color C> void generate_pawn_moves(move_vector& moves) const;
		template<piece P> [[nodiscard]] bitboard get_piece_moves(index from) const;

		static void add_pawn_move(move_vector& moves, const index from, const index to, move_type flags = pawn_move, 
			const piece capture = piece_none);

		static bitboard get_bishop_attacks(const index from, const bitboard blockers);
		static bitboard get_rook_attacks(const index from, const bitboard blockers);
		static bitboard get_magic_bishop_attacks(const index from, const bitboard blockers)
		{
			return magic_lookup[bishop_index(from, blockers)];
		}
		static bitboard get_magic_rook_attacks(const index from, const bitboard blockers)
		{
			return magic_lookup[rook_index(from, blockers)];
		}

		#pragma endregion

		#pragma region miscellaneous

		[[nodiscard]] const move& last_move() const;
		[[nodiscard]] std::string to_string() const;
		[[nodiscard]] bool reps2(uint64_t hash) const;
		[[nodiscard]] std::vector<move> moves_played() const;
		[[nodiscard]] bool insufficient_material() const;
		[[nodiscard]] position clone() const;

		#pragma endregion

		#pragma region fen processing

		[[nodiscard]] std::string to_fen() const;

		bool load_fen(const char* fen_string);

		#pragma endregion

		#pragma region incremental board updates
		void add_piece(const color c, const piece p, const index i);
		void remove_piece(const color c, const piece p, const index i);
		void update_piece(const color c, const piece p, const index from, const index to)
		{
			remove_piece(c, p, from);
			add_piece(c, p, to);
		}
		#pragma endregion

		#pragma region magic bitboard tables

		static bitboard calc_bishop_attacks(const coord file, const coord rank);
		static bitboard calc_rook_attacks(const coord file, const coord rank);
		static int rook_index(const index sq, const bitboard blockers)
		{
			magic_hash mh = rook_magics[sq];
			return mh.offset + static_cast<int>(((blockers | mh.mask) * mh.hash) >> (64 - 12));
		}
		static int bishop_index(const index sq, const bitboard blockers)
		{
			magic_hash mh = bishop_magics[sq];
			return mh.offset + static_cast<int>(((blockers | mh.mask) * mh.hash) >> (64 - 9));
		}
		static void init_magics();
		#pragma endregion
	};

	template<color C>
	void position::generate_moves(move_vector& moves) const
	{
		generate_ep(moves);
		generate_castling<C>(moves);
		generate_pawn_moves<C>(moves);
		generate_piece_moves<C, knight>(moves);
		generate_piece_moves<C, bishop>(moves);
		generate_piece_moves<C, rook>(moves);
		generate_piece_moves<C, queen>(moves);
		generate_piece_moves<C, king>(moves);
	}

	template<color C, piece P>
	void position::generate_piece_moves(move_vector& moves) const
	{
		for (bitboard bb1 = _pieces[C][P]; bb1; bb1 = bitops::reset_lsb(bb1))
		{
			const auto from = static_cast<index>(bitops::tz_count(bb1));
			const bitboard bb2 = get_piece_moves<P>(from);

			for (bitboard bb3 = bb2 & _units[~C]; bb3; bb3 = bitops::reset_lsb(bb3))
			{
				const auto to = static_cast<index>(bitops::tz_count(bb3));
				moves.emplace_back(P, from, to, capture, _board[to].piece());
			}

			for (bitboard bb3 = bb2 & ~_all; bb3; bb3 = bitops::reset_lsb(bb3))
			{
				const auto to = static_cast<index>(bitops::tz_count(bb3));
				moves.emplace_back(P, from, to);
			}
		}
	}

	template<color C>
	void position::generate_castling(move_vector& moves) const
	{
		if (C == white)
		{
			if ((_castling & white_king_side) != 0 && (between[h1][e1] & _all) == 0)
			{
				moves.emplace_back(king, e1, g1, castle);
			}
			if ((_castling & white_queen_side) != 0 && (between[a1][e1] & _all) == 0)
			{
				moves.emplace_back(king, e1, c1, castle);
			}
		}
		else
		{
			if ((_castling & black_king_side) != 0 && (between[h8][e8] & _all) == 0)
			{
				moves.emplace_back(king, e8, g8, castle);
			}
			if ((_castling & black_queen_side) != 0 && (between[a8][e8] & _all) == 0)
			{
				moves.emplace_back(king, e8, c8, castle);
			}
		}
	}

	template<color C>
	void position::generate_pawn_moves(move_vector& moves) const
	{
		bitboard bb1, bb2, bb3, bb4;
		index from, to;

		const bitboard pawns = _pieces[C][pawn];

		if (C == white)
		{
			bb1 = pawns & ((_units[~C] & ~mask_files[h1]) >> 7);
			bb2 = pawns & ((_units[~C] & ~mask_files[a1]) >> 9);
			bb3 = pawns & ~(_all >> 8);
			bb4 = (bb3 & mask_ranks[a2]) & ~(_all >> 16);
		}
		else
		{
			bb1 = pawns & ((_units[~C] & ~mask_files[h8]) << 9);
			bb2 = pawns & ((_units[~C] & ~mask_files[a8]) << 7);
			bb3 = pawns & ~(_all << 8);
			bb4 = (bb3 & mask_ranks[a7]) & ~(_all << 16);
		}

		for (; bb1; bb1 = bitops::reset_lsb(bb1))
		{
			from = static_cast<index>(bitops::tz_count(bb1));
			to = pawn_left[C][from];
			add_pawn_move(moves, from, to, capture, _board[to].piece());
		}

		for (; bb2; bb2 = bitops::reset_lsb(bb2))
		{
			from = static_cast<index>(bitops::tz_count(bb2));
			to = pawn_right[C][from];
			add_pawn_move(moves, from, to, capture, _board[to].piece());
		}

		for (; bb3; bb3 = bitops::reset_lsb(bb3))
		{
			from = static_cast<index>(bitops::tz_count(bb3));
			to = pawn_plus[C][from];
			add_pawn_move(moves, from, to, pawn_move);
		}

		for (; bb4; bb4 = bitops::reset_lsb(bb4))
		{
			from = static_cast<index>(bitops::tz_count(bb4));
			to = pawn_double[C][from];
			moves.emplace_back(pawn, from, to, dbl_pawn_move);
		}
	}

	template<piece P>
	bitboard position::get_piece_moves(index from) const
	{
		return
			P == knight ? piece_moves[P][from] :
			P == king ? piece_moves[P][from] :
			P == bishop ? get_magic_bishop_attacks(from, _all) :
			P == rook ? get_magic_rook_attacks(from, _all) :
			P == queen ? get_magic_bishop_attacks(from, _all) | get_magic_rook_attacks(from, _all) :
			0ULL;
	}

}
