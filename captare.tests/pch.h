// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H

#include <CppUnitTestAssert.h>
#include <string>
#include "../captare/chesstypes.h"
#include "../captare/move.h"

namespace Microsoft {
	namespace VisualStudio {
		namespace CppUnitTestFramework {

			template<>
			static inline std::wstring ToString(const chess::color& color)
			{
				RETURN_WIDE_STRING(color);
			}

			template<>
			static inline std::wstring ToString(const chess::piece& piece)
			{
				RETURN_WIDE_STRING(piece);
			}

			template<>
			static inline std::wstring ToString(const chess::move_type& type)
			{
				RETURN_WIDE_STRING(type);
			}

			template<>
			static inline std::wstring ToString(const chess::index& index)
			{
				RETURN_WIDE_STRING(index);
			}
		}
	}
}
#endif //PCH_H
