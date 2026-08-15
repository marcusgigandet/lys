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

import :file;
import :metal_shader;
import :rhi_shader;
import :error;

namespace lys::mtl
{
	Shader::~Shader()
	{
	}

	Result<void> Shader::load(std::span<const std::byte> byteCode)
	{
		const std::string source{
			reinterpret_cast<const char*>(byteCode.data()),
			byteCode.size(),
		};
		const auto nsString = NS::String::string(source.c_str(), NS::UTF8StringEncoding);

		if (const ErrorCode status = loadLibrary(nsString); ErrorCode::NoError != status)
		{
			return makeUnexpected(status);
		}
	}

	Result<void> Shader::load(const std::filesystem::path& path)
	{
		const NS::String* nsString{};

		const File				  file{path};
		const Result<std::string> result{file.readText()};

		if (result.has_value())
		{
			nsString = NS::String::string(result.value().c_str(), NS::UTF8StringEncoding);
		}
		else
		{
			// An error occurred when reading the file
			spdlog::warn(
				std::format(
					"An error occurred when loading {} : {}",
					file.path().string(),
					result.error().message));
			return makeUnexpected(ErrorCode::Unknown);
		}

		if (const ErrorCode status = loadLibrary(nsString); ErrorCode::NoError != status)
		{
			return makeUnexpected(status);
		}
	}

	void Shader::reload()
	{
	}

	ErrorCode Shader::loadLibrary(const NS::String* nsString)
	{
		NS::Error* nsError{};

		// Construct the library instance from the given source and check for errors
		m_library = NS::TransferPtr(m_device.newLibrary(nsString, nullptr, &nsError));
		if (!m_library)
		{
			spdlog::error(
				"MetalShader::loadLibrary: Failed to create library {}",
				nsError->description()->cString(NS::UTF8StringEncoding));
			return ErrorCode::Unknown;
		}

		return ErrorCode::NoError;
	}

	ErrorCode Shader::loadFunction(const std::string& entryPoint)
	{
		const auto	   nsEntryPoint{NS::String::string(entryPoint.c_str(), NS::UTF8StringEncoding)};
		MTL::Function* function{m_library->newFunction(nsEntryPoint)};
		if (!function)
		{
			spdlog::error(
				"MetalShader::loadFunction: Failed to create Metal function: '{}'",
				entryPoint);
			return ErrorCode::Unknown;
		}

		m_functions[entryPoint] = NS::TransferPtr(function);
		return ErrorCode::NoError;
	}

	std::vector<std::string> Shader::functionNames() const
	{
		std::vector<std::string> result;

		const NS::Array* functionNames = m_library->functionNames();
		for (NS::UInteger i = 0; i < functionNames->count(); ++i)
		{
			const auto functionName{static_cast<NS::String*>(functionNames->object(i))};
			result.emplace_back(functionName->cString(NS::UTF8StringEncoding));
		}

		return result;
	}
} // namespace lys::mtl
