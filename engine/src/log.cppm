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
	/**
	 * @brief Retrieves the global logger instance.
	 *
	 * Configures the logger on the first call to the function.
	 *
	 * @return Reference to the global lum::Logger instance.
	 */
	lum::Logger& logger()
	{
		static std::shared_ptr<lum::Logger> s_logger;

		// Initialize the logger
		if (!s_logger)
		{
			lum::FormatDesc formatDesc{
				.fieldIdOrder =
					{
						lum::LogField::Time,
						lum::LogField::Level,
						lum::LogField::Location,
					},
				.timePattern = "%Y-%m-%d %H:%M:%S",
				.includeMilliseconds = false,
				.colors = {},
				.colorAfterLogFields = false,
			};
			lum::FormatOptions formatOptions{formatDesc};

			s_logger = std::make_shared<lum::Logger>();

			const auto stderrSink{std::make_shared<lum::ConsoleSink>(std::cerr, formatOptions)};
			s_logger->addSink(stderrSink);

			const auto fileSink{std::make_shared<lum::FileSink>("logs.log", formatOptions)};
			s_logger->addSink(fileSink);
		}

		return *s_logger;
	}
} // namespace lys
