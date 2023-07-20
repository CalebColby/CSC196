#include "Enemy.h"
#include "Player.h"
#include "Bullet.h"
#include "Framework/Scene.h"
#include "Input/InputSystem.h"


void Enemy::Update(float dt)
{
	Actor::Update(dt);

	auto player = m_scene->GetActor<Player>();
	if (player)
	{
		neu::vec2 direction = player->m_transform.position - m_transform.position;
		m_transform.rotation = direction.Angle() + neu::HalfPi;
	}

	neu::vec2 forward = neu::vec2{ 0,-1 }.Rotate(m_transform.rotation);
	m_transform.position += forward * m_speed * neu::g_Time.GetDeltaTime();
	m_transform.position.x = neu::Wrap(m_transform.position.x, (float)neu::g_renderer.GetWidth());
	m_transform.position.y = neu::Wrap(m_transform.position.y, (float)neu::g_renderer.GetHeight());

	m_fireTimer -= dt;
	if (m_fireTimer <= 0)
	{
		//create bullet
		neu::Transform transform{m_transform.position, m_transform.rotation, 1};
		std::unique_ptr<Bullet> bullet = std::make_unique<Bullet>(400.0f, transform, m_model);
		bullet->m_tag = "EnemyBullet";
		m_scene->Add(std::move(bullet));
		m_fireTimer = neu::randomf(m_fireRate - 0.5f, m_fireRate + 0.5f);
	}
}

void Enemy::OnCollision(Actor* other)
{
	if(other->m_tag == "PlayerBullet") m_destroyed = true;
}
