#include "chesstypes.h"

namespace chess
{
	const wchar_t* _color_to_string[max_colors] = { L"white", L"black" };
	const wchar_t* _piece_to_string[max_pieces] = { L"P", L"N", L"B", L"R", L"Q", L"K" };
	const wchar_t* _index_to_string[max_indices] =
	{
		L"a1", L"b1", L"c1", L"d1", L"e1", L"f1", L"g1", L"h1",
		L"a2", L"b2", L"c2", L"d2", L"e2", L"f2", L"g2", L"h2",
		L"a3", L"b3", L"c3", L"d3", L"e3", L"f3", L"g3", L"h3",
		L"a4", L"b4", L"c4", L"d4", L"e4", L"f4", L"g4", L"h4",
		L"a5", L"b5", L"c5", L"d5", L"e5", L"f5", L"g5", L"h5",
		L"a6", L"b6", L"c6", L"d6", L"e6", L"f6", L"g6", L"h6",
		L"a7", L"b7", L"c7", L"d7", L"e7", L"f7", L"g7", L"h7",
		L"a8", L"b8", L"c8", L"d8", L"e8", L"f8", L"g8", L"h8"
	};

}