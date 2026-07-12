/*
 * Copyright 2026 Marcus Gigandet
 *
 * All rights reserved.
 */

#include <memory>

import lys;
import lum;

int main()
{
	lum::Logger logger;
	lum::FormatOptions formatOptions{
			{lum::LogField::Time, lum::LogField::Level},
			"%Y-%m-%d %H:%M:%S",
			false,
	};

	const auto consoleSink{std::make_shared<lum::ConsoleSink>(formatOptions)};
	logger.addSink(consoleSink);

	logger.debug("Starting editor...");

	return 0;
}
