#pragma once
#include "Core/Core.h"
#include "Renderer/Model.h"

class Actor 
{
public:
	Actor() = default;
	Actor(const neu::Transform& transform, const neu::Model& model) : 
		m_transform{ transform },
		m_model{ model }
	{}

	virtual void Update(float dt) = 0;
	virtual void Draw(neu::Renderer& renderer);

protected:
	neu::Transform m_transform;
	neu::Model m_model;
};