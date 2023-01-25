#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace chess;

namespace captaretests
{
	TEST_CLASS(movetests)
	{
	public:
		
		TEST_METHOD(default_ctor_test)
		{
			move move;

			Assert::AreEqual(0u, move.get_value());
		}

		TEST_METHOD(detailed_ctor_test)
		{
			move move(pawn, e2, e4, dbl_pawn_move);

			Assert::AreEqual(pawn, move.get_piece());
			Assert::AreEqual(dbl_pawn_move, move.get_type());
			Assert::AreEqual(e2, move.get_from());
			Assert::AreEqual(e4, move.get_to());
			Assert::AreEqual(piece_none, move.get_capture());
			Assert::AreEqual(piece_none, move.get_promote());
		}

		TEST_METHOD(get_value_test)
		{
			const move og(pawn, e2, e4, dbl_pawn_move);
			move copy(og);

			Assert::AreEqual(og.get_value(), copy.get_value());
		}

		TEST_METHOD(op_eq_test)
		{
			const move og(pawn, e2, e4, dbl_pawn_move);
			move copy{};

			copy = og;
			
			Assert::AreEqual(og.get_value(), copy.get_value());
			Assert::AreEqual(og.get_piece(), copy.get_piece());
			Assert::AreEqual(og.get_type(), copy.get_type());
			Assert::AreEqual(og.get_from(), copy.get_from());
			Assert::AreEqual(og.get_to(), copy.get_to());
			Assert::AreEqual(og.get_capture(), copy.get_capture());
			Assert::AreEqual(og.get_promote(), copy.get_promote());
		}

	};
}
