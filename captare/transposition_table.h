#pragma once

#include "chess.h"

namespace chess
{
	enum tt_flag : uint8_t
	{
		exact,
		upper_bound,
		lower_bound
	};

	struct tt_item
	{
		uint64_t _hash;
		union alignas(uint64_t)
		{
			uint64_t value;
			struct alignas(uint64_t)
			{
				uint64_t flag : 3;
				uint64_t best_move : 25;
				uint64_t score : 16;
				uint64_t depth : 6;
				uint64_t age : 8;
				uint64_t unused : 6;
			} fields;
		} _data{};

		tt_item()
			: _hash{ 0 }
		{ _data.value = 0; }

		tt_item(const uint64_t hash, const int16_t score, const int8_t depth, const tt_flag flag, const move mv);

		[[nodiscard]] uint64_t hash() const { return _hash ^ _data.value; }
		[[nodiscard]] tt_flag flag() const { return static_cast<tt_flag>(_data.fields.flag); }
		[[nodiscard]] move best_move() const { return _data.fields.best_move; }
		[[nodiscard]] int16_t score() const { return static_cast<int16_t>(_data.fields.score); }
		[[nodiscard]] int8_t depth() const { return static_cast<int8_t>(_data.fields.depth); }
		[[nodiscard]] uint8_t age() const { return static_cast<int8_t>(_data.fields.age); }
		[[nodiscard]] bool is_valid(uint64_t hash) const { return (_hash ^ _data.value) == hash; }
		void age(uint8_t age) { _data.fields.age = age; }
		uint8_t inc_age() { return static_cast<uint8_t>(++_data.fields.age); }
	};

	class transposition_table  // NOLINT(cppcoreguidelines-special-member-functions)
	{
	public:
		static constexpr int default_size_mb = 45;
		static constexpr int max_size_mb = 2047;
		static constexpr int item_size = sizeof(tt_item);
		static constexpr int mb_size = 1048576;

	private:
		tt_item* _table;
		int _capacity;
		static transposition_table* _instance;

		explicit transposition_table(const int size_mb = default_size_mb)
		{
			_capacity = (std::min(size_mb, max_size_mb) * mb_size) / item_size;
			_table = new tt_item[_capacity];
		}

		[[nodiscard]] int index(uint64_t hash) const;
		bool index(uint64_t hash, int& index) const;

	public:
		~transposition_table()
		{
			delete[] _table;
		}

		[[nodiscard]] int capacity() const { return _capacity; }

		void clear() const { for (int n = 0; n < _capacity; ++n) _table[n]._data.value = 0; }
		void resize(int size_mb);
		std::tuple<bool, int, move> lookup_score(uint64_t hash, int depth, int ply, int& alpha, int& beta) const;
		std::tuple<bool, move> lookup_move(uint64_t hash) const;
		void store(uint64_t hash, int depth, int ply, int alpha, int beta, int score, move mv) const;
		static transposition_table* instance();

	};
}

