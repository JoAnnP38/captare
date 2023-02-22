#include "pch.h"

#include <iostream>

#include "CppUnitTest.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace chess;

namespace captaretests
{
	TEST_CLASS(positiontests)
	{
	public:
		static constexpr struct { const char* fen_string; uint64_t hash; } params[] =
		{
			{ "rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1", 0x823c9b50fd114196ULL },
			{ "rnbqkbnr/ppp1pppp/8/3p4/4P3/8/PPPP1PPP/RNBQKBNR w KQkq d6 0 2", 0x0756b94461c50fb0ULL },
			{ "rnbqkbnr/ppp1pppp/8/3pP3/8/8/PPPP1PPP/RNBQKBNR b KQkq - 0 2", 0x662fafb965db29d4ULL },
			{ "rnbqkbnr/ppp1p1pp/8/3pPp2/8/8/PPPP1PPP/RNBQKBNR w KQkq f6 0 3", 0x22a48b5a8e47ff78ULL },
			{ "rnbqkbnr/ppp1p1pp/8/3pPp2/8/8/PPPPKPPP/RNBQ1BNR b kq - 0 3", 0x652a607ca3f242c1ULL },
			{ "rnbq1bnr/ppp1pkpp/8/3pPp2/8/8/PPPPKPPP/RNBQ1BNR w - - 0 4", 0x00fdd303c946bdd9ULL },
			{ "rnbqkbnr/p1pppppp/8/8/PpP4P/8/1P1PPPP1/RNBQKBNR b KQkq c3 0 3", 0x3c8123ea7b067637ULL },
			{ "rnbqkbnr/p1pppppp/8/8/P6P/R1p5/1P1PPPP1/1NBQKBNR b Kkq - 0 4", 0x5c3f9b829b279560ULL }
		};

		TEST_METHOD(default_ctor_test)
		{
			position p{};

			Assert::AreEqual(color_none, p.side_to_move());
			Assert::AreEqual(no_rights, p.castling());
			Assert::AreEqual(index_none, p.enpassant());
			Assert::AreEqual(index_none, p.enpassant_validated());
			Assert::AreEqual(static_cast<uint16_t>(0), p.half_move_clock());
			Assert::AreEqual(static_cast<uint16_t>(0), p.full_move_counter());
			Assert::AreEqual(0ull, p.hash());
		}

		TEST_METHOD(fen_ctor_test)
		{
			try
			{
				position p{ fen_start_pos };
				Logger::WriteMessage(p.to_string().c_str());
				Assert::AreEqual(rook, p.board(a1).piece());
				Assert::AreEqual(pawn, p.board(a2).piece());
				Assert::IsFalse(p.board(d4).occupied());
				Assert::IsFalse(p.board(e5).occupied());;
				Assert::AreEqual(pawn, p.board(h7).piece());
				Assert::AreEqual(rook, p.board(h8).piece());
				Assert::AreEqual(0x463b96181691fc9cULL, p.hash());
			}
			catch (std::exception& e)
			{
				Logger::WriteMessage(e.what());
				Assert::Fail(L"Unexpected exception initializing position.");
			}
		}

		TEST_METHOD(load_fen_test)
		{
			position p{};
			for (auto& param : params)
			{
				p.load_fen(param.fen_string);
				Assert::AreEqual(param.hash, p.hash());
			}
		}

		TEST_METHOD(to_fen_test)
		{
			position p{};
			for (auto& param : params)
			{
				p.load_fen(param.fen_string);
				std::string s = p.to_fen();
				Assert::AreEqual(param.fen_string, s.c_str());
			}
		}

		TEST_METHOD(get_piece_moves_knight_test)
		{
			position p{ fen_start_pos };
			bitboard bb = p.get_piece_moves<knight>(b1);
			Logger::WriteMessage(bitboard_to_string(p.pieces(white, knight)).c_str());
			Logger::WriteMessage("\n");
			Logger::WriteMessage(bitboard_to_string(bb).c_str());
			Assert::IsTrue((bb & (1ULL << c3)) != 0);
		}

		TEST_METHOD(get_piece_moves_bishop_test)
		{
			position p{ "rnbqkbnr/pppp1ppp/8/4p3/4P3/8/PPPP1PPP/RNBQKBNR w KQkq e6 0 1" };
			bitboard bb = p.get_piece_moves<bishop>(f1);
			WriteLine(bitboard_to_string(p.pieces(white, bishop)));
			WriteLine();
			WriteLine(bitboard_to_string(bb));
			Assert::IsTrue((bb & (1ULL << c4)) != 0);
		}

		TEST_METHOD(get_piece_moves_king_test)
		{
			position p{ "rnbqkbnr/pppp1ppp/8/4p3/4P3/8/PPPP1PPP/RNBQKBNR w KQkq e6 0 1" };
			bitboard bb = p.get_piece_moves<king>(e1);
			WriteLine(bitboard_to_string(p.pieces(white, king)));
			WriteLine();
			WriteLine(bitboard_to_string(bb));
			Assert::IsTrue((bb & (1ULL << e2)) != 0);
		}

		TEST_METHOD(get_piece_moves_queen_test)
		{
			position p{ "rnbqkbnr/pppp1ppp/8/4p3/4P3/8/PPPP1PPP/RNBQKBNR w KQkq e6 0 1" };
			bitboard bb = p.get_piece_moves<queen>(d1);
			WriteLine(bitboard_to_string(p.pieces(white, queen)));
			WriteLine();
			WriteLine(bitboard_to_string(bb));
			Assert::IsTrue((bb & (1ULL << g4)) != 0);
		}

		TEST_METHOD(get_piece_moves_rook_test)
		{
			position p{ "rnbqk1nr/ppppbppp/8/4p3/4P2P/8/PPPP1PP1/RNBQKBNR w KQkq - 0 1" };
			bitboard bb = p.get_piece_moves<rook>(h1);
			WriteLine(bitboard_to_string(p.pieces(white, rook)));
			WriteLine();
			WriteLine(bitboard_to_string(bb));
			Assert::IsTrue((bb & (1ULL << h4)) != 0);
		}

		TEST_METHOD(generate_pawn_moves_test)
		{
			position p{ fen_start_pos };
			move_vector mv{};
			p.generate_pawn_moves<white>(mv);
			Assert::AreEqual(16, static_cast<int>(mv.size()));

			mv.clear();
			p.generate_pawn_moves<black>(mv);
			Assert::AreEqual(16, static_cast<int>(mv.size()));
		}


		TEST_METHOD(generate_moves_test)
		{
			position p{ fen_start_pos };
			move_vector mv{};
			p.generate_moves<white>(mv);
			Assert::AreEqual(20, static_cast<int>(mv.size()));

			mv.clear();
			p.generate_moves<black>(mv);
			Assert::AreEqual(20, static_cast<int>(mv.size()));
		}
	};
}
