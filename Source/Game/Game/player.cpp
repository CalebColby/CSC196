#include "player.h"
#include "Input/InputSystem.h"

void Player::Update(float dt)
{
	float rotate = 0;
	if (neu::g_inputSystem.GetKeyDown(SDL_SCANCODE_A)) rotate = -1;
	if (neu::g_inputSystem.GetKeyDown(SDL_SCANCODE_D)) rotate = 1;
	m_transform.rotation += rotate * m_turnRate * neu::g_Time.GetDeltaTime();

	float thrust = 0;
	if (neu::g_inputSystem.GetKeyDown(SDL_SCANCODE_W)) thrust = 1;
	if (neu::g_inputSystem.GetKeyDown(SDL_SCANCODE_S)) thrust = -1;

	neu::vec2 forward = neu::vec2{ 0,-1 }.Rotate(m_transform.rotation);
	m_transform.position += forward * m_speed * thrust * neu::g_Time.GetDeltaTime();
	m_transform.position.x = neu::Wrap(m_transform.position.x, (float)neu::g_renderer.GetWidth());
	m_transform.position.y = neu::Wrap(m_transform.position.y, (float)neu::g_renderer.GetHeight());
}
