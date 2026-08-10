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

module lys:rhi_texture.impl;

import :rhi_texture;

namespace lys::rhi
{
	Texture::Texture(const TextureDesc& desc) :
		m_type(desc.type), m_width(desc.width), m_height(desc.height),
		m_depthOrLayers(desc.depthOrLayers), m_mipLevels(desc.mipLevels),
		m_pixelFormat(desc.pixelFormat), m_depthFormat(desc.depthFormat)
	{
	}
} // namespace lys::rhi
