#include "Enemy.h"
#include "Player.h"
#include "Bullet.h"
#include "SpaceGame.h"
#include "Framework/Scene.h"
#include "Framework/Emitter.h"
#include "Input/InputSystem.h"


void Enemy::Update(float dt)
{
	Actor::Update(dt);

	auto player = m_scene->GetActor<Player>();
	neu::vec2 forward = neu::vec2{ 0,-1 }.Rotate(m_transform.rotation);
	if (player)
	{
		neu::vec2 direction = player->m_transform.position - m_transform.position;

		float turnAngle = neu::vec2::SignedAngle(forward, direction.Normalized());

		m_transform.rotation += turnAngle * dt;

		float angle = neu::vec2::Angle(forward, direction.Normalized());
		if (angle < neu::DegreesToRadians(30.0f)) 
		{
			//fire
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
	}
	m_transform.position += forward * m_speed * neu::g_Time.GetDeltaTime();
	m_transform.position.x = neu::Wrap(m_transform.position.x, (float)neu::g_renderer.GetWidth());
	m_transform.position.y = neu::Wrap(m_transform.position.y, (float)neu::g_renderer.GetHeight());

	m_fireTimer -= dt;
}

void Enemy::OnCollision(Actor* other)
{
	if (other->m_tag == "PlayerBullet")
	{
		m_destroyed = true;
		m_game->AddPoints(100);
		neu::g_audioSystem.PlayOneShot("hit");
		//Destruction Particles
		neu::EmitterData data;
		data.burst = true;
		data.burstCount = 100;
		data.spawnRate = 0;
		data.angle = 0;
		data.angleRange = neu::Pi;
		data.lifetimeMin = 0.5f;
		data.lifetimeMin = 1.5f;
		data.speedMin = 50;
		data.speedMax = 250;
		data.damping = 0.5f;
		data.color = neu::Color{ 1, 0, 0, 1 };
		//data.color = other->
		neu::Transform transform{ { m_transform.position }, 0, 1 };
		auto emitter = std::make_unique<neu::Emitter>(transform, data, 0.1f);
		m_scene->Add(std::move(emitter));
	}
}
