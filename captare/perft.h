#pragma once
#include "chess.h"
#include "position.h"

namespace chess
{
	class perft
	{
	private:
		chess::position _pos;
		object_pool<move_vector> _vector_pool{ 16 };

	public:
		struct details  // NOLINT(cppcoreguidelines-special-member-functions)
		{
		public:
			uint64_t nodes{ 0 };
			uint64_t captures{ 0 };
			uint64_t enpassants{ 0 };
			uint64_t castles{ 0 };
			uint64_t checks{ 0 };
			uint64_t checkmates{ 0 };
			uint64_t stalemates{ 0 };
			uint64_t promotions{ 0 };

			details() = default;
			details(const details& d);

			details& operator=(const details& d);
			details operator+ (const details& d) const;
			details& operator+=(const details& d)
			{
				*this = *this + d;
				return *this;
			}
		};

		perft(const char* start_pos)
			: _pos{start_pos}
		{ }

		perft()	: perft(fen_start_pos)
		{ }

		uint64_t execute(int depth)
		{
			return _pos.side_to_move() == white ? 
				execute_body<white>(depth) :
				execute_body<black>(depth);
		}

	private:
		template<color C> uint64_t execute_body(int depth);
	};

	template<color C>
	uint64_t perft::execute_body(int depth)
	{
		uint64_t nodes{ 0 };
		move_vector& moves = _vector_pool.get();
		_pos.generate_moves<C>(moves);

		for (const auto& move : moves)
		{
			if (!_pos.make_move(move))
			{
				continue;
			}
			nodes += depth > 1 ? execute_body<~C>(depth - 1) : 1;
			_pos.unmake_move();
		}

		_vector_pool.put(moves);
		return nodes;
	}

}

