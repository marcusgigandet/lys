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
export module lys:metal_shader;

import :error;
import :rhi_shader;

namespace lys::metal
{
	export class Shader : public rhi::Shader
	{
		NS::SharedPtr<MTL::Library>										 m_library;
		std::map<std::string, NS::SharedPtr<MTL::Function>, std::less<>> m_functions;

	public:
		explicit Shader(const rhi::ShaderDesc& desc) : rhi::Shader(desc) {}

	private:
		void loadLibrary();
		void unloadLibrary() { m_library.reset(); }

		Result<void> loadFunction(const std::string& entryPoint);
	};
} // namespace lys::metal
