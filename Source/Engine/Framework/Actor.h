#pragma once
#include "Core/Core.h"
#include "Renderer/Model.h"

namespace neu
{
	class Actor
	{
	public:
		Actor() = default;
		Actor(const neu::Transform& transform, const neu::Model& model) :
			m_transform{ transform },
			m_model{ model }
		{}

		virtual void Update(float dt);
		virtual void Draw(neu::Renderer& renderer);

		friend class Scene;

		neu::Transform m_transform;
	protected:
		bool m_destroyed = false;
		float m_lifespan = -1.0f;

		
		neu::Model m_model;
		class Scene* m_scene = nullptr;
	};
}