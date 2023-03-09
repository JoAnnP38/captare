// ReSharper disable CppClangTidyPerformanceUnnecessaryValueParam
#include "chess.h"

namespace chess
{
	tt_item::tt_item(const uint64_t hash, const int16_t score, const int8_t depth, const tt_flag flag, const move mv)  // NOLINT(performance-unnecessary-value-param)
	{
		_data.fields.flag = flag;
		_data.fields.best_move = mv.get_value();
		_data.fields.score = static_cast<uint16_t>(score);
		_data.fields.depth = static_cast<uint16_t>(depth);
		_data.fields.age = 0;
		_data.fields.unused = 0;
		_hash = hash ^ _data.value;
	}

	void transposition_table::resize(const int size_mb)
	{
		if (size_mb > 0)
		{
			const int new_capacity = (std::min(size_mb, max_size_mb) * mb_size) / item_size;
			auto* new_table = new tt_item[new_capacity];
			delete[] _table;
			_table = new_table;
			_capacity = new_capacity;
		}
	}

	int transposition_table::index(const uint64_t hash) const
	{
		const int index0 = static_cast<int>(hash % _capacity);
		const int index1 = index0 ^ 1;

		tt_item* e0 = _table + index0;
		tt_item* e1 = _table + index1;

		if (e0->is_valid(hash))
		{
			return index0;
		}

		if (e1->is_valid(hash))
		{
			return index1;
		}

		return static_cast<int>(e0->inc_age()) - e0->depth() > static_cast<int>(e1->inc_age()) - e1->depth() ? index0 : index1;
	}

	bool transposition_table::index(const uint64_t hash, int& index) const
	{
		index = static_cast<int>(hash % _capacity);
		if ((_table + index)->is_valid(hash))
		{
			(_table + index)->age(0);
			return true;
		}

		index ^= 1;

		if (!(_table + index)->is_valid(hash))
		{
			(_table + index)->age(0);
			return true;
		}

		return false;
	}

	std::tuple<bool, int, move> transposition_table::lookup_score(const uint64_t hash, const int depth, 
		const int ply, int& alpha, int& beta) const
	{
		int score = 0, n;
		move mv{ 0 };

		if (index(hash, n))
		{
			const tt_item* item = _table + n;
			if (item->depth() <= depth)
			{
				return std::tuple{false, score, mv};
			}

			score = item->score();
			mv = item->best_move();

			// TODO: Replace with evaluation::is_checkmate() when the valuation class is worked on
			if (score > checkmate_base && score <= checkmate_score)
			{
				score -= sign(score) * ply;
			}

			if (item->flag() == exact)
			{
				return std::tuple{ true, score, mv };
			}

			if (item->flag() == upper_bound)
			{
				beta = std::min(score, beta);
			}
			else
			{
				alpha = std::max(score, alpha);
			}

			return std::tuple{ alpha >= beta, score, mv };
		}

		return std::tuple{ false, score, mv };
	}

	std::tuple<bool, move> transposition_table::lookup_move(const uint64_t hash) const
	{
		int n;
		move mv{ 0 };
		if (index(hash, n))
		{
			mv = (_table + n)->best_move();
			return std::tuple{ true, mv };
		}

		return std::tuple{ false, mv };
	}

	void transposition_table::store(const uint64_t hash, const int depth, const int ply, const int alpha, 
		const int beta, int score, move mv) const
	{
		int n = index(hash);
		tt_item* item = _table + n;

		move best_move{ mv };

		if (item->is_valid(hash))
		{
			if (item->depth() > depth)
			{
				return;
			}
			best_move = best_move == move::empty ? item->best_move() : best_move;
		}

		// TODO: Replace with evaluation::is_checkmate() when the valuation class is worked on
		if (score > checkmate_base && score <= checkmate_score)
		{
			score += sign(score) * ply;
		}

		const auto item_depth = static_cast<int8_t>(depth);
		tt_flag flag = exact;

		if (score <= alpha)
		{
			flag = upper_bound;
		}
		else if (score >= beta)
		{
			flag = lower_bound;
		}

		*item = tt_item{ hash, static_cast<int16_t>(score), item_depth, flag, best_move };
	}

	transposition_table* transposition_table::instance()
	{
		if (_instance == nullptr)
		{
			_instance = new transposition_table{};
		}
		return _instance;
	}

	transposition_table* transposition_table::_instance = nullptr;
}
