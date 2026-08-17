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

export module lys:rhi_surface;

import :window;

namespace lys::rhi
{
	export class Surface
	{
	protected:
		const Window& m_window;

	public:
		explicit Surface(const Window& window) : m_window(window) {}
		virtual ~Surface() = default;

		Surface(const Surface&)			   = delete;
		Surface& operator=(const Surface&) = delete;
		Surface(Surface&&)				   = delete;
		Surface& operator=(Surface&&)	   = delete;

		[[nodiscard]] const Window& window() const noexcept { return m_window; }
	};
} // namespace lys::rhi
