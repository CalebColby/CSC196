#include "SpaceGame.h"
#include "Player.h"
#include "Enemy.h"

#include "Framework/Scene.h"
#include "Framework/Emitter.h"

#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Renderer/Text.h"
#include "Renderer/ModelManager.h"

bool SpaceGame::Initialize()
{
	// create font / text objects
	m_font = std::make_shared<neu::Font>("PaladinFLF.ttf", 24);
	m_scoreText = std::make_unique<neu::Text>(m_font);
	m_scoreText->Create(neu::g_renderer, "SCORE 0000", neu::Color{ 1, 0, 1, 1 });

	m_titleText = std::make_unique<neu::Text>(m_font);
	m_titleText->Create(neu::g_renderer, "AZTEROIDS", neu::Color{ 1, 1, 1, 1 });

	// load audio
	neu::g_audioSystem.AddAudio("hit", "Explosion.wav");
	neu::g_audioSystem.AddAudio("laser", "Laser_Fire.wav");

	// create scene
	m_scene = std::make_unique<neu::Scene>();

	return true;
}

void SpaceGame::Shutdown()
{
}

void SpaceGame::Update(float dt)
{
	neu::EmitterData data;
	data.burst = true;
	data.burstCount = 100;
	data.spawnRate = 200;
	data.angle = 0;
	data.angleRange = neu::Pi;
	data.lifetimeMin = 0.5f;
	data.lifetimeMin = 1.5f;
	data.speedMin = 50;
	data.speedMax = 250;
	data.damping = 0.5f;
	data.color = neu::Color{ 1, 0, 0, 1 };
	neu::Transform transform{ { neu::g_inputSystem.GetMousePosition() }, 0, 1 };
	auto emitter = std::make_unique<neu::Emitter>(transform, data);
	emitter->m_lifespan = 1.0f;
	m_scene->Add(std::move(emitter));

	switch (m_state)
	{
	case SpaceGame::eState::Title:
		if (neu::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE))
		{
			m_state = eState::StartGame;
		}
		break;

	case SpaceGame::eState::StartGame:
		m_score = 0;
		m_lives = 3;
		m_state = eState::StartLevel;
		break;

	case SpaceGame::eState::StartLevel:
		m_scene->RemoveAll();
		{
			std::unique_ptr<Player> player = std::make_unique<Player>(200.0f, neu::Pi, neu::Transform{ { 400, 300 }, 0, 4 }, neu::g_ModelManager.Get("Ship.txt"));
			player->m_tag = "Player";
			player->m_game = this;
			m_scene->Add(std::move(player));
		}
		m_state = eState::Game;
		break;
	case SpaceGame::eState::Game:
		m_spawnTimer += dt;
		if (m_spawnTimer >= m_spawnTime)
		{
			m_spawnTimer = 0;
			std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(neu::randomf(75.0f, 150.0f), neu::Pi, neu::Transform{ { neu::random(800), neu::random(600) }, neu::randomf(neu::TwoPi), 3}, neu::g_ModelManager.Get("EnemyShip.txt"));
			enemy->m_tag = "Enemy";
			enemy->m_game = this;
			m_scene->Add(std::move(enemy));
		}
		break;
	case SpaceGame::eState::PlayerDead:
		if (m_lives == 0) m_state = eState::GameOver;
		else m_state = eState::StartLevel;

		break;
	case SpaceGame::eState::GameOver:
		break;
	default:
		break;
	}

	m_scoreText->Create(neu::g_renderer, std::to_string(m_score), { 1, 1, 1, 1 });
	m_scene->Update(dt);
}

void SpaceGame::Draw(neu::Renderer& renderer)
{
	if (m_state == eState::Title)
	{
		m_titleText->Draw(renderer, 400, 300);
	}

	m_scoreText->Draw(renderer, 40, 20);
	m_scene->Draw(renderer);
}