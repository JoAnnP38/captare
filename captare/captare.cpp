// captare.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <format>
#include "chess.h"

using namespace chess;

extern std::string fmt_ms(uint64_t ms);

int main()
{
	position::init_magics();
	perft test{};

	for (int depth = 1; depth <= 7; ++depth)
	{
		auto start = std::chrono::high_resolution_clock::now();
		uint64_t nodes = test.execute(depth);
		auto stop = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
		long double total_seconds = static_cast<long double>(duration.count()) / 1000.0l;
		double mnps = static_cast<long double>(nodes) / (1000000.0l * total_seconds);
		std::cout
			<< depth
			<< ": Elapsed = "
			<< fmt_ms(duration.count())
			<< ", Mnps: "
			<< std::format("{:6.2f}", mnps)
			<< ", nodes: "
			<< nodes
			<< std::endl;
	}
}

std::string fmt_ms(uint64_t ms)
{
	long double f_hours = static_cast<long double>(ms) / (1000.0 * 60.0 * 60.0);
	int hours = static_cast<int>(floor(f_hours));
	ms -= 1000ULL * 60 * 60 * hours;

	long double f_min = static_cast<long double>(ms) / (1000.0 * 60.0);
	int minutes = static_cast<int>(floor(f_min));
	ms -= 1000ULL * 60ULL * minutes;

	long double f_sec = static_cast<long double>(ms) / 1000.0;
	int seconds = static_cast<int>(floor(f_sec));
	ms -= 1000ULL * seconds;

	std::string s = std::format("{0:0>2}:{1:0>2}:{2:0>2}.{3:0>3}", hours, minutes, seconds, ms);
	return s;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
