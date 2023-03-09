#pragma once
#include "chesstypes.h"
#include <span>

namespace chess
{
	class zobrist_hash
	{
	private:
		static constexpr auto random64_length = 781;
		static constexpr auto castle_hash_map_length = 16;
		static constexpr auto turn_hash_map_length = 2;
		static constexpr auto piece_offset = 0;
		static constexpr auto piece_length = 768;
		static constexpr auto castle_offset = 768;
		static constexpr auto castle_length = 4;
		static constexpr auto ep_offset = 772;
		static constexpr auto ep_length = 8;
		static constexpr auto turn_offset = 780;
		static constexpr auto turn_length = 1;

		uint64_t _hash{ 0 };
		static uint64_t random64[random64_length];
		static uint64_t castle_hash_map[castle_hash_map_length];
		static uint64_t turn_hash_map[turn_hash_map_length];
		static std::span<uint64_t, piece_length> random64_piece;
		static std::span<uint64_t, castle_length> random64_castle;
		static std::span<uint64_t, ep_length> random64_ep;
		static std::span<uint64_t, turn_length> random64_turn;

		static uint64_t get_piece_hash(color c, piece p, index i)
		{
			const size_t pieceKind = p << 1 | (c ^ 1);
			return random64_piece[(pieceKind << 6) + i];
		}

		static uint64_t get_castle_hash(castling_rights castle)
		{
			return castle_hash_map[castle];
		}

		static uint64_t get_ep_hash(index ep)
		{
			return random64_ep[index_to_file(ep)];
		}

		static uint64_t get_turn_hash(color c)
		{
			return turn_hash_map[c];
		}

	public:
		zobrist_hash() = default;
		zobrist_hash(const zobrist_hash& other) = default;

		explicit zobrist_hash(const uint64_t hash)
		{
			_hash = hash;
		}

		zobrist_hash& operator = (const zobrist_hash& other) = default;
		zobrist_hash& operator = (const uint64_t init_hash)
		{
			_hash = init_hash;
			return *this;
		}

		operator uint64_t() const { return _hash; }

		zobrist_hash& hash_piece(color c, piece p, index i)
		{
			_hash ^= get_piece_hash(c, p, i);
			return *this;
		}

		zobrist_hash& hash_castling(castling_rights castling)
		{
			_hash ^= get_castle_hash(castling);
			return *this;
		}

		zobrist_hash& hash_ep(index ep)
		{
			_hash ^= get_ep_hash(ep);
			return *this;
		}

		zobrist_hash& hash_turn(color c)
		{
			_hash ^= get_turn_hash(c);
			return *this;
		}
	};
}
