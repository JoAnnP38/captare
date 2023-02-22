#pragma once

#include "chesstypes.h"
#include <cassert>
#include <intrin.h>

namespace chess
{
	class bitops
	{
	public:
		static uint64_t get_mask(const index i)
		{
			assert(index_is_valid(i));
			return 1ULL << i;
		}

		static bitboard set_bit(const bitboard bb, const index i)
		{
			return bb | get_mask(i);
		}

		static bitboard reset_bit(const bitboard bb, const index i)
		{
			return bb & ~get_mask(i);
		}

		static int get_bit(const bitboard bb, const index i)
		{
			assert(index_is_valid(i));
			return static_cast<int>((bb >> i) & 1);
		}

		static int tz_count(const bitboard bb)
		{
			return std::countr_zero(bb);
		}

		static int pop_count(const bitboard bb)
		{
			return std::popcount(bb);
		}

		static int lz_count(const bitboard bb)
		{
			return std::countl_zero(bb);
		}

		static bitboard reset_lsb(const bitboard bb)
		{
			return _blsr_u64(bb);
		}
	};
}
