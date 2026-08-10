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

import std;

namespace lys::rhi
{
	export enum class ShaderStage
	{
		Vertex,
		Fragment,
		Compute,
	};

	export struct ShaderDesc
	{
		ShaderStage								  stage;
		std::string								  entryPoint{"main"};
		std::optional<std::span<const std::byte>> byteCode;
		std::optional<std::string>				  file;
	};

	export class Shader
	{
		ShaderStage m_stage;
		std::string m_entryPoint;

	public:
		explicit Shader(const ShaderDesc& desc);
		virtual ~Shader() = default;

		Shader(const Shader&)			 = delete;
		Shader& operator=(const Shader&) = delete;
		Shader(Shader&&)				 = default;
		Shader& operator=(Shader&&)		 = default;

		[[nodiscard]] ShaderStage	   stage() const noexcept { return m_stage; }
		[[nodiscard]] std::string_view entryPoint() const noexcept { return m_entryPoint; }
	};
} // namespace lys::rhi
