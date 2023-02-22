// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H

#include <CppUnitTestAssert.h>
#include <CppUnitTestLogger.h>
#include <string>
#include "../captare/chess.h"

namespace Microsoft {
	namespace VisualStudio {
		namespace CppUnitTestFramework {

			template<>
			inline std::wstring ToString(const chess::color& color)
			{
				RETURN_WIDE_STRING(color);
			}

			template<>
			inline std::wstring ToString(const chess::piece& piece)
			{
				RETURN_WIDE_STRING(piece);
			}

			template<>
			inline std::wstring ToString(const chess::move_type& type)
			{
				RETURN_WIDE_STRING(type);
			}

			template<>
			inline std::wstring ToString(const chess::index& index)
			{
				RETURN_WIDE_STRING(index);
			}

			template<>
			inline std::wstring ToString(const chess::castling_rights& castling)
			{
				RETURN_WIDE_STRING(castling);
			}
		}
	}
}

namespace captaretests
{
	inline void WriteLine(std::string s)
	{
		Microsoft::VisualStudio::CppUnitTestFramework::Logger::WriteMessage(s.c_str());
	}

	inline void WriteLine()
	{
		Microsoft::VisualStudio::CppUnitTestFramework::Logger::WriteMessage("\n");
	}
}
#endif //PCH_H
