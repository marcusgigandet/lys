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

export module lys:rhi_shader;

import :rhi_error;
import std;

namespace lys::rhi
{
	export enum class ShaderStage
	{
		Vertex,
		Fragment,
		Compute,
	};

	export enum class ShaderLanguage
	{
		Slang,
		Metal,
	};

	export struct ShaderDesc
	{
		ShaderStage								  stage;
		ShaderLanguage							  language;
		std::string								  entryPoint{"main"};
		std::optional<std::span<const std::byte>> byteCode;
		std::optional<std::string>				  file;
	};

	export class Shader
	{
		ShaderStage							 m_stage;
		std::string							 m_entryPoint;
		std::vector<std::byte>				 m_byteCode;
		std::optional<std::filesystem::path> m_file;

	public:
		explicit Shader(const ShaderDesc& desc);
		virtual ~Shader() = default;

		Shader(const Shader&)			 = delete;
		Shader& operator=(const Shader&) = delete;
		Shader(Shader&&)				 = default;
		Shader& operator=(Shader&&)		 = default;

		virtual Result<void>	   load(std::span<const std::byte> byteCode)				   = 0;
		virtual Result<void>	   load(std::variant<std::string, std::filesystem::path> file) = 0;
		[[nodiscard]] Result<void> load(std::string_view file);
		[[nodiscard]] Result<void> load(const std::filesystem::path& file);
		[[nodiscard]] Result<void> reload();

		[[nodiscard]] ShaderStage	   stage() const noexcept { return m_stage; }
		[[nodiscard]] std::string_view entryPoint() const noexcept { return m_entryPoint; }
		[[nodiscard]] bool			   hasByteCode() const noexcept { return !m_byteCode.empty(); }
		[[nodiscard]] std::span<const std::byte> byteCode() const noexcept { return m_byteCode; }
		[[nodiscard]] bool hasFile() const noexcept { return m_file.has_value(); }
		[[nodiscard]] const std::optional<std::filesystem::path>& file() const noexcept
		{
			return m_file;
		}

	protected:
		void setByteCode(std::span<const std::byte> byteCode);
		void setFile(std::filesystem::path file);
	};
} // namespace lys::rhi
