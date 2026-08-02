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

export module lys:entity;

import :component;
import mag;
import std;

namespace lys
{
	export class Entity
	{
		std::vector<std::unique_ptr<Component>> m_components;

	public:
		template <typename T, typename... Args>
			requires(std::is_base_of_v<Component, T>)

		T* addComponent(Args&&... args)
		{
			auto component	  = std::make_unique<T>(std::forward<Args>(args)...);
			T*	 componentPtr = component.get();
			m_components.push_back(std::move(component));
			return componentPtr;
		}

		template <typename T>
		T* getComponent()
		{
			for (auto& component : m_components)
			{
				if (T* result = dynamic_cast<T*>(component.get()))
				{
					return result;
				}
			}
			return nullptr;
		}

		void update(const float delta) const
		{
			for (const auto& component : m_components)
			{
				component->update(delta);
			}
		}
	};
} // namespace lys
