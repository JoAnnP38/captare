#include "perft.h"

namespace chess
{
	perft::details::details(const details& d)
	{
		nodes = d.nodes;
		captures = d.captures;
		enpassants = d.enpassants;
		castles = d.castles;
		checks = d.checks;
		checkmates = d.checkmates;
		stalemates = d.stalemates;
		promotions = d.promotions;
	}

	perft::details& perft::details::operator=(const details& d)
	{
		if (this != &d)
		{
			nodes = d.nodes;
			captures = d.captures;
			enpassants = d.enpassants;
			castles = d.castles;
			checks = d.checks;
			checkmates = d.checkmates;
			stalemates = d.stalemates;
			promotions = d.promotions;
		}
		return *this;
	}

	perft::details perft::details::operator+ (const details& d) const
	{
		details dets;
		dets.nodes = nodes + d.nodes;
		dets.captures = captures + d.captures;
		dets.enpassants = enpassants + d.enpassants;
		dets.castles = castles + d.castles;
		dets.checks = checks + d.checks;
		dets.checkmates = checkmates + d.checkmates;
		dets.stalemates = stalemates + d.stalemates;
		dets.promotions = promotions + d.promotions;
		return dets;
	}
}
