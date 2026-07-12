/*
 * Copyright 2026 Marcus Gigandet
 *
 * All rights reserved.
 */

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

			const auto consoleSink{std::make_shared<lum::ConsoleSink>(formatOptions)};
			s_logger->addSink(consoleSink);

			const auto fileSink{std::make_shared<lum::FileSink>("logs.log", formatOptions)};
			s_logger->addSink(consoleSink);
		}

		return *s_logger;
	}
} // namespace lys
