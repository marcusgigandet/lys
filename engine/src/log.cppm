/*
 * Copyright 2026 Marcus Gigandet
 *
 * All rights reserved.
 */

module;
#include <format> // Fix module issue from std module
export module lys:log;

import lum;
import std;

namespace lys
{
	lum::Logger& logger()
	{
		static std::shared_ptr<lum::Logger> s_logger;

		// Initialize the logger
		if (!s_logger)
		{
			lum::FormatOptions formatOptions{
				{
					lum::LogField::Time,
					lum::LogField::Level,
					lum::LogField::Location,
				},
				"%Y-%m-%d %H:%M:%S",
				false,
			};

			s_logger = std::make_shared<lum::Logger>();

			const auto stderrSink = std::make_shared<lum::ConsoleSink>(std::cerr, formatOptions);
			s_logger->addSink(stderrSink);

			const auto fileSink = std::make_shared<lum::FileSink>("logs.log", formatOptions);
			s_logger->addSink(fileSink);
		}

		return *s_logger;
	}
} // namespace lys
