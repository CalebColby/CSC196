#include "Actor.h"

namespace neu
{
	void Actor::Draw(neu::Renderer& renderer)
	{
		m_model.Draw(renderer, m_transform);
	}
}