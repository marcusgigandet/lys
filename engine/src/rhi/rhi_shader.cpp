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

module lys:rhi_shader.impl;

import :rhi_shader;

namespace lys::rhi
{
	Shader::Shader(const ShaderDesc& desc) :
		m_stage(desc.stage), m_entryPoint(desc.entryPoint), m_source(desc.source)
	{
	}

	Result<void> Shader::load(const std::string_view file)
	{
		return load(std::filesystem::path{std::string(file)});
	}
} // namespace lys::rhi
