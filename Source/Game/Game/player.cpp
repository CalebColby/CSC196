#include "Player.h"
#include "Bullet.h"
#include "Input/InputSystem.h"
#include "Framework/Scene.h"

void Player::Update(float dt)
{
	Actor::Update(dt);

	//Movement
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

	// fire weapon
	if (neu::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) &&
		!neu::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE))
	{
		//create bullet
		neu::Transform transform{m_transform.position, m_transform.rotation, 1};
		std::unique_ptr<Bullet> bullet = std::make_unique<Bullet>( 400.0f, transform, m_model );
		bullet->m_tag = "PlayerBullet";
		m_scene->Add(std::move(bullet));
	}

	if (m_health <= 0)
	{
		neu::g_audioSystem.PlayOneShot("hit");
		m_destroyed = true;
	}
}

void Player::OnCollision(Actor* other)
{
	if (other->m_tag == "EnemyBullet")
	{
		m_health -= neu::randomf(0.5f, 5.5f);
	}
}
