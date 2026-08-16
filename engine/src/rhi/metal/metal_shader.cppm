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
import :metal_object;
import :rhi_shader;

namespace lys::mtl
{
	export class Shader final : public Object, public rhi::Shader
	{
		NS::SharedPtr<MTL::Library>										 m_library;
		std::map<std::string, NS::SharedPtr<MTL::Function>, std::less<>> m_functions;

	public:
		explicit Shader(MTL::Device& device, const rhi::ShaderDesc& desc);

		~Shader() override;

		Result<void> load(std::span<const std::byte> byteCode) override;
		Result<void> load(const std::filesystem::path& path) override;
		void		 reload() override;

		[[nodiscard]] MTL::Function* function(std::string_view entryPoint) const;

	private:
		ErrorCode loadLibrary(const NS::String* nsString);
		void	  unloadLibrary() { m_library.reset(); }

		ErrorCode				 loadFunction(const std::string& entryPoint);
		std::vector<std::string> functionNames() const;
	};
} // namespace lys::mtl
