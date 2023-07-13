#include "Enemy.h"
#include "Input/InputSystem.h"

void Enemy::Update(float dt)
{
	neu::vec2 forward = neu::vec2{ 0,-1 }.Rotate(m_transform.rotation);
	m_transform.position += forward * m_speed * neu::g_Time.GetDeltaTime();
	m_transform.position.x = neu::Wrap(m_transform.position.x, (float)neu::g_renderer.GetWidth());
	m_transform.position.y = neu::Wrap(m_transform.position.y, (float)neu::g_renderer.GetHeight());
}