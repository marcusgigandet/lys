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

module lys:file.impl;

import :error;
import :file;
import std;

namespace lys
{
	bool File::exists() const
	{
		return std::filesystem::exists(m_path);
	}

	Result<std::vector<std::byte>> File::readBytes() const
	{
		std::ifstream input(m_path, std::ios::binary);
		if (!input)
		{
			return makeUnexpected(
				ErrorCode::FileNotFound,
				std::format("Failed to open file for reading: {}", m_path.string()));
		}

		input.seekg(0, std::ios::end);
		const auto endPos{input.tellg()};
		if (endPos < 0)
		{
			return makeUnexpected(
				ErrorCode::FileReadFailure,
				std::format("Failed to determine file size: {}", m_path.string()));
		}

		const auto			   size{static_cast<std::size_t>(endPos)};
		std::vector<std::byte> bytes(size);
		input.seekg(0, std::ios::beg);

		if (!bytes.empty())
		{
			input.read(
				reinterpret_cast<char*>(bytes.data()),
				static_cast<std::streamsize>(bytes.size()));
			if (!input)
			{
				return makeUnexpected(
					ErrorCode::FileReadFailure,
					std::format("Failed to read file contents: {}", m_path.string()));
			}
		}

		return bytes;
	}

	Result<std::string> File::readText() const
	{
		const Result<std::vector<std::byte>> bytesResult{readBytes()};
		if (!bytesResult)
		{
			return std::unexpected(bytesResult.error());
		}

		const auto& bytes{bytesResult.value()};
		return std::string(reinterpret_cast<const char*>(bytes.data()), bytes.size());
	}

	Result<void> File::writeBytes(const std::span<const std::byte> bytes) const
	{
		std::ofstream output(m_path, std::ios::binary | std::ios::trunc);
		if (!output)
		{
			return makeUnexpected(
				ErrorCode::FailedToOpenFile,
				std::format("Failed to open file for writing: {}", m_path.string()));
		}

		if (!bytes.empty())
		{
			output.write(
				reinterpret_cast<const char*>(bytes.data()),
				static_cast<std::streamsize>(bytes.size()));
			if (!output)
			{
				return makeUnexpected(
					ErrorCode::FileWriteFailure,
					std::format("Failed to write file contents: {}", m_path.string()));
			}
		}

		return {};
	}

	Result<void> File::writeText(const std::string_view text) const
	{
		return writeBytes(std::as_bytes(std::span{text.data(), text.size()}));
	}
} // namespace lys
