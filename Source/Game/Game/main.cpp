#include "Core/Core.h"
#include "Renderer/ModelManager.h"
#include "Renderer/Renderer.h"
#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"
#include "Framework/Scene.h"
#include "Player.h"
#include "Enemy.h"

#include <iostream>
#include <vector>
#include <thread>
#include <Renderer/Font.h>
#include <Renderer/Text.h>

using namespace std;

class Star
{
public:
	Star(const neu::Vector2 pos, const neu::Vector2 vel) :
		m_pos{ pos },
		m_vel{ vel }
	{}

	void Update(int width, int height)
	{
		m_pos += m_vel * neu::g_Time.GetDeltaTime();

		if (m_pos.x >= width) { m_pos.x = 0; }
		if (m_pos.y >= height) { m_pos.y = 0; }
	}

public:
	neu::Vector2 m_pos;
	neu::Vector2 m_vel;
};


int main(int argc, char* argv[])
{	
	//Initialize Engine Systems
	neu::MemoryTracker::Initialize();

	neu::seedRandom((unsigned int)time(nullptr));
	neu::setFilePath("assets");
	
	neu::g_renderer.Initialize();
	neu::g_renderer.CreateWindow("CSC196", 800,600);

	neu::g_inputSystem.Initialize();

	neu::g_audioSystem.Initialize();
	neu::g_audioSystem.AddAudio("hit", "Explosion.wav");
	neu::g_audioSystem.AddAudio("laser", "Laser_Fire.wav");

	std::shared_ptr<neu::Font> font = std::make_shared<neu::Font>("PaladinFLF.ttf", 24);

	std::unique_ptr<neu::Text> text = std::make_unique<neu::Text>(font);
	text->Create(neu::g_renderer, "NEUMONT", neu::Color{ 1, 1, 1, 1 });

	std::vector<Star> stars;
	for (size_t i = 0; i < 1000; i++)
	{
		neu::Vector2 pos(neu::randomf((float)neu::g_renderer.GetWidth()), neu::randomf((float)neu::g_renderer.GetHeight()));
		neu::Vector2 vel(neu::randomf(100,400), neu::randomf(-200, 200));

		stars.push_back(Star(pos, vel));
	}

	neu::Transform transform{ { 400, 300 }, 0, 3 };
	float speed = 500;
	constexpr float turnRate = neu::DegreesToRadians(180);

	neu::Scene scene;

	std::unique_ptr<Player> player = make_unique<Player>(200, neu::Pi, neu::Transform{ { 400, 300 }, 0, 3 }, neu::g_ModelManager.Get("Ship.txt"));
	player->m_tag = "Player";
	scene.Add(std::move(player));

	for (size_t i = 0; i < 25; i++)
	{
		std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>( neu::randomf(75.0f, 150.0f), neu::Pi, 
			neu::Transform{ { neu::randomf(neu::g_renderer.GetWidth()), neu::randomf(neu::g_renderer.GetHeight()) }, 
			neu::randomf(neu::TwoPi), 3}, neu::g_ModelManager.Get("EnemyShip.txt"));
		enemy->m_tag = "Enemy";
		scene.Add(std::move(enemy));
	}

	//main game loop
	bool quit = false;
	while (!quit)
	{
		//update Engine
		neu::g_Time.Tick();
		neu::g_inputSystem.Update();
		neu::g_audioSystem.Update();
		//update Scene
		scene.Update(neu::g_Time.GetDeltaTime());

		//Detect Input
		if (neu::g_inputSystem.GetKeyDown(SDL_SCANCODE_ESCAPE))
		{
			quit = true;
		}

		
		//draw
		neu::g_renderer.SetColor(0, 0, 0, 0);
		neu::g_renderer.BeginFrame();
		for (auto& star : stars) 
		{
			star.Update(neu::g_renderer.GetWidth(), neu::g_renderer.GetHeight());

			neu::g_renderer.SetColor(neu::random(256), neu::random(256), neu::random(256), 255);
			neu::g_renderer.DrawPoint(star.m_pos.x, star.m_pos.y);
		}

		neu::g_renderer.SetColor(255, 255, 255, 255);
		scene.Draw(neu::g_renderer);
		text->Draw(neu::g_renderer, 400, 300);
		neu::g_renderer.EndFrame();
	}

	stars.clear();
	scene.RemoveAll();
	neu::g_renderer.Shutdown();

	return 0;
}