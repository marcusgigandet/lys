/*
 * Copyright 2026 Marcus Gigandet
 *
 * All rights reserved.
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
			auto component = std::make_unique<T>(std::forward<Args>(args)...);
			T* componentPtr = component.get();
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
