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
export module lys:metal_texture;

import :error;
import :metal_object;
import :rhi_texture;
import std;

namespace lys::mtl
{
	export class Texture : public Object, public rhi::Texture
	{
		NS::SharedPtr<MTL::Texture> m_texture;

	public:
		explicit Texture(MTL::Device& device, const rhi::TextureDesc& desc);
		Texture(MTL::Device& device, MTL::Texture& texture, const rhi::TextureDesc& desc);

		/**
		 * @brief Returns the native backend Texture.
		 * @return Native metal Texture.
		 */
		[[nodiscard]] MTL::Texture* texture() const noexcept { return m_texture.get(); }

		Result<void>
		upload(std::span<const std::byte> data, std::size_t bytesPerRow) noexcept override;

	private:
		void createTexture();
	};
} // namespace lys::mtl
