/*
 * Copyright 2026 Marcus Gigandet
 *
 * All rights reserved.
 */

export module lys:component;

import mag;

namespace lys
{
	export class Component
	{
	public:
		virtual ~Component() = default;
		virtual void process(float deltaTime) {}
	};

	export class TransformComponent : public Component
	{
		Vec3 m_position;
		Vec3 m_scale;

	public:
	};
} // namespace lys
