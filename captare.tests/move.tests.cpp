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
			Assert::AreEqual(dbl_pawn_move, move.type());
			Assert::AreEqual(e2, move.from());
			Assert::AreEqual(e4, move.to());
			Assert::AreEqual(piece_none, move.capture());
			Assert::AreEqual(piece_none, move.promote());
		}

		TEST_METHOD(get_value_test)
		{
			const move og(pawn, e2, e4, dbl_pawn_move);
			const move copy{ og };

			Assert::AreEqual(og.get_value(), copy.get_value());
		}

		TEST_METHOD(op_eq_test)
		{
			const move og(pawn, e2, e4, dbl_pawn_move);
			move copy{};

			copy = og;
			
			Assert::AreEqual(og.get_value(), copy.get_value());
			Assert::AreEqual(og.get_piece(), copy.get_piece());
			Assert::AreEqual(og.type(), copy.type());
			Assert::AreEqual(og.from(), copy.from());
			Assert::AreEqual(og.to(), copy.to());
			Assert::AreEqual(og.capture(), copy.capture());
			Assert::AreEqual(og.promote(), copy.promote());
		}

	};
}
