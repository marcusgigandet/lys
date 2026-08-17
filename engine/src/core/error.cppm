/*
 * Copyright 2026 Marcus Gigandet
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

module;
#include "typedefs.hpp"
export module lys:error;

import std;

namespace lys
{
	export enum class ErrorCode : std::uint16_t
	{
		NoError,
		Unknown,
		InvalidArgument,
		Unsupported,
		NotImplemented,
		InitializationFailed,
		OutOfMemory,
		FileNotFound,
		FileReadFailure,
		FileWriteFailure,
		FailedToOpenFile,
	};

	export constexpr std::string_view defaultErrorMessage(const ErrorCode code) noexcept
	{
		switch (code)
		{
		case ErrorCode::InvalidArgument:
			return "Invalid argument.";
		case ErrorCode::Unsupported:
			return "Unsupported operation.";
		case ErrorCode::NotImplemented:
			return "Not implemented.";
		case ErrorCode::InitializationFailed:
			return "Initialization failed.";
		case ErrorCode::OutOfMemory:
			return "Out of memory.";
		case ErrorCode::FileNotFound:
			return "Invalid file path.";
		case ErrorCode::FileReadFailure:
			return "An error occurred when reading the file.";
		case ErrorCode::FileWriteFailure:
			return "An error occurred when writing to the file.";
		case ErrorCode::FailedToOpenFile:
			return "An error occurred when opening the file.";
		case ErrorCode::Unknown:
		default:
			return "Unknown error.";
		}
	}

	export struct Error
	{
		ErrorCode	code{ErrorCode::Unknown};
		std::string message{};

		Error() = default;

		explicit Error(const ErrorCode errorCode) :
			code(errorCode), message(defaultErrorMessage(errorCode))
		{
		}

		Error(const ErrorCode errorCode, std::string errorMessage) :
			code(errorCode), message(std::move(errorMessage))
		{
		}
	};

	export template <typename T>
	using Result = std::expected<T, Error>;

	export [[nodiscard]] LYS_INLINE Error makeError(const ErrorCode code)
	{
		return Error{code};
	}

	export [[nodiscard]] LYS_INLINE Error makeError(const ErrorCode code, std::string message)
	{
		return Error{code, std::move(message)};
	}

	export [[nodiscard]] LYS_INLINE std::unexpected<Error> makeUnexpected(const ErrorCode code)
	{
		return std::unexpected<Error>(Error{code});
	}

	export [[nodiscard]] LYS_INLINE std::unexpected<Error>
									makeUnexpected(const ErrorCode code, std::string message)
	{
		return std::unexpected<Error>(Error{code, std::move(message)});
	}
} // namespace lys
