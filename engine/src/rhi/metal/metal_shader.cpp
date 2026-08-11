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
#include <Metal/Metal.hpp>
#include <spdlog/spdlog.h>
export module lys:metal_shader.impl;

import :metal_shader;
import :rhi_shader;

namespace lys::metal
{
	void Shader::loadLibrary()
	{
		NS::Error* nsError{};
		m_library.reset();
	}

	rhi::Result<void> Shader::loadFunction(const std::string& entryPoint)
	{
		if (!m_library) // Sanity check to prevent segfault
		{
			spdlog::error("MetalShader::loadFunction: No library.");
			return rhi::makeUnexpected(rhi::ErrorCode::Unknown);
		}

		const auto	   nsEntryPoint{NS::String::string(entryPoint.c_str(), NS::UTF8StringEncoding)};
		MTL::Function* function{m_library->newFunction(nsEntryPoint)};
		if (!function)
		{
			spdlog::error(
				"MetalShader::loadFunction: Failed to create Metal function: '{}'",
				entryPoint);
			return rhi::makeUnexpected(rhi::ErrorCode::Unknown);
		}

		if (m_functions.contains(entryPoint))
		{
			m_functions.erase(entryPoint);
		}

		m_functions[entryPoint] = NS::TransferPtr(function);
		return {};
	}

} // namespace lys::metal
