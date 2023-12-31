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
	m_scoreText->Create(neu::g_renderer, "SCORE 0000", neu::Color{ 1, 1, 1, 1 });

	m_titleText = std::make_unique<neu::Text>(m_font);
	m_titleText->Create(neu::g_renderer, "Star Field", neu::Color{ 1, 1, 1, 1 });

	m_gameOverText = std::make_unique<neu::Text>(m_font);
	m_gameOverText->Create(neu::g_renderer, "Game Over", neu::Color{ 1, 1, 1, 1 });

	m_livesText = std::make_unique<neu::Text>(m_font);
	m_livesText->Create(neu::g_renderer, "X Lives Left", neu::Color{ 1, 1, 1, 1 });

	//Load HighScore
	std::string buffer;
	neu::readFile("HighScore.txt", buffer);
	m_highScore = static_cast<size_t>(std::stoi(buffer));


	// load audio
	neu::g_audioSystem.AddAudio("hit", "Explosion.wav");
	neu::g_audioSystem.AddAudio("laser", "Laser_Fire.wav");
	neu::g_audioSystem.AddAudio("PowerUp", "Powerup.wav");
	neu::g_audioSystem.AddAudio("music", "Music.mp3");

	neu::g_audioSystem.PlayOneShot("music", true);

	// create scene
	m_scene = std::make_unique<neu::Scene>();

	m_state = eState::Title;
	return true;
}

void SpaceGame::Shutdown()
{
}

void SpaceGame::Update(float dt)
{
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
			std::unique_ptr<Player> player = std::make_unique<Player>(20.0f, neu::Pi, neu::Transform{ { 400, 300 }, 0, 4 }, neu::g_ModelManager.Get("Ship.txt"));
			player->m_tag = "Player";
			player->m_game = this;
			player->SetDamping(0.9f);
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
	case eState::PlayerDeadStart:
		m_stateTimer = 2;
		if (m_lives <= 0) m_state = eState::GameOver;
		else m_state = eState::PlayerDead;
		break;
	case SpaceGame::eState::PlayerDead:
		m_stateTimer -= dt;
		if (m_stateTimer <= 0)
		{
			m_state = eState::StartLevel;
		}
		break;
	case SpaceGame::eState::GameOver:
		m_stateTimer -= dt;
		if (m_stateTimer <= 0)
		{
			if (m_score > m_highScore)
			{
				m_highScore = m_score;
				std::string scoreString = std::to_string(m_highScore);
				neu::overwriteFile("HighScore.txt", scoreString);
			}
			m_scene->RemoveAll();
			m_state = eState::Title;
		}
		break;
	default:
		break;
	}
	
	m_scoreText->Create(neu::g_renderer, ((m_state == eState::Title) ? "High Score: " + std::to_string(m_highScore) : "Score: " + std::to_string(m_score)), 
		{1, 1, 1, 1});
	m_scene->Update(dt);
}

void SpaceGame::Draw(neu::Renderer& renderer)
{
	if (m_state == eState::Title)
	{
		m_titleText->Draw(renderer, 400, 300);
	}

	if (m_state == eState::GameOver)
	{
		m_gameOverText->Draw(renderer, 400, 300);
	}

	if (m_state == eState::PlayerDead)
	{
		m_livesText->Create(neu::g_renderer, ((m_lives == 1) ? "1 Life Remaining" : std::to_string(m_lives) + " Lives Remaining"), { 1, 1, 1, 1 });
		m_livesText->Draw(renderer, 400, 300);
	}

	m_scoreText->Draw(renderer, 10, 10);
	m_scene->Draw(renderer);
}