#include "Actor.h"


void Actor::Draw(neu::Renderer& renderer)
{
	m_model.Draw(renderer, m_transform);
}
