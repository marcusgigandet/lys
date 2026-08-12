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

export module lys:file;

import :error;
import std;

namespace lys
{
	export class File
	{
		std::filesystem::path m_path{};

	public:
		File() = default;
		explicit File(std::filesystem::path path) : m_path(std::move(path)) {}

		[[nodiscard]] const std::filesystem::path& path() const noexcept { return m_path; }
		void path(std::filesystem::path path) { m_path = std::move(path); }

		[[nodiscard]] bool exists() const;

		[[nodiscard]] Result<std::string>			 readText() const;
		[[nodiscard]] Result<std::vector<std::byte>> readBytes() const;

		Result<void> writeText(std::string_view text) const;
		Result<void> writeBytes(std::span<const std::byte> bytes) const;
	};
} // namespace lys
